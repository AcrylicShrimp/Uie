
/*
	2018.04.05
	Created by AcrylicShrimp.
*/

#include "Window.h"

namespace Uie
{
	std::unordered_map<HWND, Window *> Window::sWindowMap;
	std::unordered_map<UINT, std::vector<WindowMessageHandler *>> Window::sGlobalHandlerListMap;

	Window::~Window()
	{
		this->destroyWindow();
	}

	void Window::destroyWindow()
	{
		auto hWindowHandle{this->hWindow};

		DestroyWindow(this->hWindow);
		this->hWindow = nullptr;

		UnregisterClassW(this->sClassName.c_str(), this->hInstance);
		this->hInstance = nullptr;

		if (hWindowHandle)
			Window::sWindowMap.erase(hWindowHandle);
	}

	bool Window::createWindow(const Attribute &sAttribute)
	{
		WNDCLASSW sClass
		{
			static_cast<UINT>(sAttribute.eClassStyle),
			Window::windowMessageProcedure,
			0,
			0,
			this->hInstance = GetModuleHandleW(nullptr),
			sAttribute.hIcon,
			sAttribute.hCursor,
			sAttribute.hBackgroundBrush,
			sAttribute.pMenuName,
			(this->sClassName = sAttribute.sClassName).c_str()
		};

		if (!RegisterClassW(&sClass))
		{
			this->destroyWindow();
			return false;
		}

		RECT sClientRect
		{
			0l,
			0l,
			static_cast<LONG>(sAttribute.nWidth),
			static_cast<LONG>(sAttribute.nHeight)
		};

		if (sAttribute.eSizingMode == SizingMode::ClientAreaOnly)
		{
			AdjustWindowRectEx(&sClientRect, static_cast<DWORD>(sAttribute.eStyle), sAttribute.pMenuName != nullptr, static_cast<DWORD>(sAttribute.eExtendedStyle));

			sClientRect.right -= sClientRect.left;
			sClientRect.bottom -= sClientRect.top;
		}

		if (!(this->hWindow = CreateWindowExW(
			static_cast<DWORD>(sAttribute.eExtendedStyle),
			sAttribute.sClassName.c_str(),
			sAttribute.sTitleText.c_str(),
			static_cast<DWORD>(sAttribute.eStyle),
			sAttribute.nX,
			sAttribute.nY,
			sClientRect.right,
			sClientRect.bottom,
			sAttribute.hParentWindow,
			sAttribute.hMenu,
			this->hInstance,
			sAttribute.pExtraPointer)))
		{
			this->destroyWindow();
			return false;
		}

		Window::sWindowMap.emplace(this->hWindow, this);

		return true;
	}

	bool Window::setVisible(Visibility eNewVisibility)
	{
		return ShowWindow(this->hWindow, static_cast<int>(eNewVisibility));
	}

	void Window::setFileDraggable(bool bNewDraggable)
	{
		DragAcceptFiles(this->hWindow, bNewDraggable);
	}

	bool Window::setTitle(const std::wstring &sNewTitle)
	{
		return SetWindowTextW(this->hWindow, sNewTitle.c_str());
	}

	bool Window::moveWindow(int nNewX, int nNewY, int nNewWidth, int nNewHeight, bool bRepaint)
	{
		return MoveWindow(this->hWindow, nNewX, nNewY, nNewWidth, nNewHeight, bRepaint);
	}

	void Window::registerHandler(WindowMessageHandler *pNewWindowMessageHandler)
	{
		for (auto nMessage : pNewWindowMessageHandler->messageList())
			this->sHandlerListMap[nMessage].emplace_back(pNewWindowMessageHandler);
	}

	void Window::unregisterHandler(WindowMessageHandler *pNewWindowMessageHandler)
	{
		for (auto nMessage : pNewWindowMessageHandler->messageList())
		{
			auto &sHandlerList{this->sHandlerListMap[nMessage]};

			for (auto iIndex{sHandlerList.cbegin()}, iEnd{sHandlerList.cend()}; iIndex != iEnd; ++iIndex)
				if (*iIndex == pNewWindowMessageHandler)
				{
					sHandlerList.erase(iIndex);
					break;
				}
		}
	}

	void Window::unregisterHandlerAll()
	{
		this->sHandlerListMap.clear();
	}

	WPARAM Window::loopMessage()
	{
		MSG sMsg;

		while (GetMessage(&sMsg, nullptr, 0, 0))
		{
			TranslateMessage(&sMsg);
			DispatchMessage(&sMsg);
		}

		return sMsg.wParam;
	}

	LRESULT Window::handleMessage(HWND hWindow, UINT nMessage, WPARAM wParam, LPARAM lParam)
	{
		LRESULT nResult;

		switch (nMessage)
		{
		case WM_MOVE:
		case WM_MOVING:
		case WM_SIZE:
		case WM_SIZING:
		{
			RECT sWindowRect;
			RECT sClientRect;

			GetWindowRect(hWindow, &sWindowRect);
			GetClientRect(hWindow, &sClientRect);

			this->sSizeInfo.nEntireX = sWindowRect.left;
			this->sSizeInfo.nEntireY = sWindowRect.top;
			this->sSizeInfo.nEntireWidth = sWindowRect.right - sWindowRect.left;
			this->sSizeInfo.nEntireHeight = sWindowRect.bottom - sWindowRect.top;

			this->sSizeInfo.nClientWidth = sClientRect.right - sClientRect.left;
			this->sSizeInfo.nClientHeight = sClientRect.bottom - sClientRect.top;

			nResult = 0;
		}
		break;
		default:
		{
			nResult = NoHandler;
		}
		break;
		}

		auto iIndex{this->sHandlerListMap.find(nMessage)};

		if (iIndex != this->sHandlerListMap.cend())
		{
			nResult = 0;

			for (auto pHandler : iIndex->second)
				nResult += pHandler->handleWindowMessage(this, hWindow, nMessage, wParam, lParam);
		}

		return nResult;
	}

	Window *Window::findWindow(HWND hWindow)
	{
		auto iIndex{Window::sWindowMap.find(hWindow)};

		if (iIndex == Window::sWindowMap.cend())
			return nullptr;

		return iIndex->second;
	}

	void Window::registerGlobalHandler(WindowMessageHandler *pNewWindowMessageHandler)
	{
		for (auto nMessage : pNewWindowMessageHandler->messageList())
			Window::sGlobalHandlerListMap[nMessage].emplace_back(pNewWindowMessageHandler);
	}

	void Window::unregisterGlobalHandler(WindowMessageHandler *pNewWindowMessageHandler)
	{
		for (auto nMessage : pNewWindowMessageHandler->messageList())
		{
			auto &sHandlerList{Window::sGlobalHandlerListMap[nMessage]};

			for (auto iIndex{sHandlerList.cbegin()}, iEnd{sHandlerList.cend()}; iIndex != iEnd; ++iIndex)
				if (*iIndex == pNewWindowMessageHandler)
				{
					sHandlerList.erase(iIndex);
					break;
				}
		}
	}

	void Window::unregisterGlobalHandlerAll()
	{
		Window::sGlobalHandlerListMap.clear();
	}

	LRESULT CALLBACK Window::windowMessageProcedure(HWND hWindow, UINT nMessage, WPARAM wParam, LPARAM lParam)
	{
		auto iWindowIndex{Window::sWindowMap.find(hWindow)};

		if (iWindowIndex == Window::sWindowMap.cend())
			return DefWindowProcW(hWindow, nMessage, wParam, lParam);

		//Pass the local handler first.
		auto nResult{iWindowIndex->second->handleMessage(hWindow, nMessage, wParam, lParam)};

		//Pass the global handler later.
		auto iHandlerIndex{Window::sGlobalHandlerListMap.find(nMessage)};

		if (iHandlerIndex != Window::sGlobalHandlerListMap.cend())
		{
			nResult = 0;

			for (auto pHandler : iHandlerIndex->second)
				nResult += pHandler->handleWindowMessage(iWindowIndex->second, hWindow, nMessage, wParam, lParam);
		}

		return nResult == Window::NoHandler ? DefWindowProcW(hWindow, nMessage, wParam, lParam) : nResult;
	}
}