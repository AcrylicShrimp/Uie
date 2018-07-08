
/*
	2018.07.02
	Created by AcrylicShrimp.
*/

#include "UIContext.h"

namespace Uie
{
	std::unordered_map<HANDLE, UIContext *> UIContext::sThreadRenderingContextMap;
	std::unordered_map<Window *, UIContext *> UIContext::sWindowRenderingContextMap;

	UIContext::UIContext() :
		WindowMessageHandler{WM_DESTROY, WM_SIZE, WM_SIZING, WM_PAINT, WM_ERASEBKGND}
	{
		//Empty.
	}

	UIContext::~UIContext()
	{
		this->destroy();
	}

	void UIContext::destroy()
	{
		if (!this->created())
			return;

		this->detach();

		this->pPlacement = nullptr;
		this->sPlacementMap.clear();

		::wglDeleteContext(this->hRenderingContext);

		this->hRenderingContext = nullptr;
	}

	bool UIContext::create(Window *pWindow)
	{
		if (this->created())
			return false;

		if (!pWindow)
			return false;

		if (!pWindow->created())
			return false;

		if (!pWindow->contextCreated())
			return false;

		if (!(this->hRenderingContext = ::wglCreateContext(pWindow->context())))
			return false;

		return true;
	}

	void UIContext::detach()
	{
		if (!this->attached())
			return;

		this->pAttachedWindow->unregisterHandler(this);

		delete this->pRenderer;

		UIContext::sThreadRenderingContextMap.erase(this->hAttachedThread);
		UIContext::sWindowRenderingContextMap.erase(this->pAttachedWindow);

		wglMakeCurrent(nullptr, nullptr);

		this->hAttachedThread = nullptr;
		this->pAttachedWindow = nullptr;
		this->pRenderer = nullptr;
	}

	bool UIContext::attach(Window *pWindow)
	{
		if (!this->created())
			return false;

		if (this->attached())
			return false;

		if (!pWindow)
			return false;

		if (!pWindow->created())
			return false;

		if (!pWindow->contextCreated())
			return false;

		if (!wglMakeCurrent(pWindow->context(), this->hRenderingContext))
			return false;

		UIContext::sThreadRenderingContextMap[this->hAttachedThread = ::GetCurrentThread()] = this;
		UIContext::sWindowRenderingContextMap[this->pAttachedWindow = pWindow] = this;

		this->pRenderer = new Render::Renderer();

		this->pAttachedWindow->registerHandler(this);

		return true;
	}

	void UIContext::redraw()
	{
		if (!this->attached())
			return;

		if (this->pPlacement)
			this->pPlacement->update();

		::RedrawWindow(this->pAttachedWindow->handle(), nullptr, nullptr, RDW_INVALIDATE);
	}

	void UIContext::inactivePlacement()
	{
		this->pPlacement = nullptr;
	}

	void UIContext::activePlacement(const std::string &sName)
	{
		auto pPlacement{this->findPlacement(sName)};

		if (pPlacement)
			this->pPlacement = pPlacement;
	}

	UI::Placement *UIContext::createPlacement(const std::string &sName)
	{
		return &this->sPlacementMap[sName];
	}

	UI::Placement *UIContext::findPlacement(const std::string &sName)
	{
		auto iIndex{this->sPlacementMap.find(sName)};

		return iIndex == this->sPlacementMap.cend() ? nullptr : &iIndex->second;
	}

	const UI::Placement *UIContext::findPlacement(const std::string &sName) const
	{
		auto iIndex{this->sPlacementMap.find(sName)};

		return iIndex == this->sPlacementMap.cend() ? nullptr : &iIndex->second;
	}

	void UIContext::removePlacement(const std::string &sName)
	{
		this->sPlacementMap.erase(sName);
	}

	LRESULT UIContext::handleWindowMessage(Window *pWindow, HWND hWindow, UINT nMessage, WPARAM wParam, LPARAM lParam)
	{
		switch (nMessage)
		{
		case WM_DESTROY:
		{
			delete this->pRenderer;

			UIContext::sThreadRenderingContextMap.erase(this->hAttachedThread);
			UIContext::sWindowRenderingContextMap.erase(this->pAttachedWindow);

			wglMakeCurrent(nullptr, nullptr);

			this->hAttachedThread = nullptr;
			this->pAttachedWindow = nullptr;
			this->pRenderer = nullptr;
		}
		break;
		case WM_SIZE:
		case WM_SIZING:
		{
			this->redraw();
		}
		break;
		case WM_PAINT:
		{
			this->pRenderer->clear();

			if (this->pPlacement)
				this->pPlacement->render();

			this->pRenderer->flush();

			::ValidateRect(hWindow, nullptr);
		}
		break;
		case WM_ERASEBKGND:
			return 1;
		default:
			return Window::NoHandler;
		}

		return 0;
	}

	UIContext *UIContext::find(HANDLE hThread)
	{
		auto iIndex{UIContext::sThreadRenderingContextMap.find(hThread)};

		return iIndex == UIContext::sThreadRenderingContextMap.cend() ? nullptr : iIndex->second;
	}

	UIContext *UIContext::find(Window *pWindow)
	{
		auto iIndex{UIContext::sWindowRenderingContextMap.find(pWindow)};

		return iIndex == UIContext::sWindowRenderingContextMap.cend() ? nullptr : iIndex->second;
	}
}