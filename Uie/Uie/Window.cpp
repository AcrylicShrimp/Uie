
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
		this->destroy();
	}

	void Window::destroy()
	{
		this->destroyContext();

		auto hWindowHandle{this->hHandle};

		::DestroyWindow(this->hHandle);
		this->hHandle = nullptr;

		::UnregisterClassW(this->sClassName.c_str(), this->hInstance);
		this->hInstance = nullptr;

		if (hWindowHandle)
			Window::sWindowMap.erase(hWindowHandle);
	}

	bool Window::create(const Attribute &sAttribute)
	{
		if (this->created())
			return false;

		WNDCLASSW sClass
		{
			static_cast<UINT>(sAttribute.eClassStyle),
			Window::windowMessageProcedure,
			0,
			0,
			this->hInstance = ::GetModuleHandleW(nullptr),
			sAttribute.hIcon,
			sAttribute.hCursor,
			sAttribute.hBackgroundBrush,
			sAttribute.pMenuName,
			(this->sClassName = sAttribute.sClassName).c_str()
		};

		if (!::RegisterClassW(&sClass))
		{
			this->destroy();
			return false;
		}

		RECT sClientRect
		{
			0,
			0,
			static_cast<LONG>(sAttribute.nWidth),
			static_cast<LONG>(sAttribute.nHeight)
		};

		if (sAttribute.eSizingMode == SizingMode::ClientAreaOnly)
		{
			::AdjustWindowRectEx(&sClientRect, static_cast<DWORD>(sAttribute.eStyle), sAttribute.pMenuName != nullptr, static_cast<DWORD>(sAttribute.eExtendedStyle));

			sClientRect.right -= sClientRect.left;
			sClientRect.bottom -= sClientRect.top;
		}

		if (!(this->hHandle = ::CreateWindowExW(
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
			this->destroy();
			return false;
		}

		Window::sWindowMap.emplace(this->hHandle, this);

		return true;
	}

	void Window::destroyContext()
	{
		if (!this->hContext)
			return;

		::ReleaseDC(this->hHandle, this->hContext);
		this->hContext = nullptr;
	}

	bool Window::createContext(BYTE nColorBit, BYTE nDepthBit, BYTE nStencilBit)
	{
		if (this->contextCreated())
			return false;

		if (!(this->hContext = ::GetDC(this->hHandle)))
			return false;

		DWORD nFlag = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_GENERIC_ACCELERATED | PFD_DOUBLEBUFFER;

		if (!nDepthBit)
			nFlag |= PFD_DEPTH_DONTCARE;

		PIXELFORMATDESCRIPTOR sFormat
		{
			sizeof(PIXELFORMATDESCRIPTOR),
			1,
			nFlag,
			PFD_TYPE_RGBA,
			this->nColorBit = nColorBit,
			0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0,
			this->nDepthBit = nDepthBit,
			this->nStencilBit = nStencilBit,
			0,
			0,
			0,
			0, 0, 0
		};

		auto nPixelFormat{::ChoosePixelFormat(this->hContext, &sFormat)};

		if (!nPixelFormat)
		{
			this->destroyContext();
			return false;
		}

		if (!::SetPixelFormat(this->hContext, nPixelFormat, &sFormat))
		{
			this->destroyContext();
			return false;
		}
	}

	bool Window::setVisible(Visibility eNewVisibility)
	{
		return ::ShowWindow(this->hHandle, static_cast<int>(eNewVisibility));
	}

	void Window::setFileDraggable(bool bNewDraggable)
	{
		::DragAcceptFiles(this->hHandle, bNewDraggable);
	}

	bool Window::setTitle(const std::wstring &sNewTitle)
	{
		return ::SetWindowTextW(this->hHandle, sNewTitle.c_str());
	}

	bool Window::moveWindow(int nNewX, int nNewY, int nNewWidth, int nNewHeight, bool bRepaint)
	{
		return ::MoveWindow(this->hHandle, nNewX, nNewY, nNewWidth, nNewHeight, bRepaint);
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

	bool Window::peekMessage()
	{
		MSG sMsg;

		if (!::PeekMessageW(&sMsg, nullptr, 0, 0, PM_REMOVE))
			return false;

		::TranslateMessage(&sMsg);
		::DispatchMessageW(&sMsg);

		return true;
	}

	WPARAM Window::loopMessage()
	{
		MSG sMsg;

		while (::GetMessageW(&sMsg, nullptr, 0, 0))
		{
			::TranslateMessage(&sMsg);
			::DispatchMessageW(&sMsg);
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

			::GetWindowRect(hWindow, &sWindowRect);
			::GetClientRect(hWindow, &sClientRect);

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
			return ::DefWindowProcW(hWindow, nMessage, wParam, lParam);

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

		return nResult == Window::NoHandler ? ::DefWindowProcW(hWindow, nMessage, wParam, lParam) : nResult;
	}
}