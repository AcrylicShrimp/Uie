
/*
	2018.07.09
	Created by AcrylicShrimp.
*/

#include "RenderingContext.h"

namespace Uie::Render
{
	std::unordered_map<HANDLE, RenderingContext *> RenderingContext::sThreadMap;
	std::unordered_map<Window *, RenderingContext *> RenderingContext::sWindowMap;

	RenderingContext::~RenderingContext()
	{
		this->destroy();
	}

	void RenderingContext::destroy()
	{
		if (!this->created())
			return;

		this->detach();

		::wglDeleteContext(this->hRenderingContext);

		this->hRenderingContext = nullptr;
	}

	bool RenderingContext::create(Window *pWindow)
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

	void RenderingContext::detach()
	{
		if (!this->attached())
			return;

		RenderingContext::sThreadMap.erase(this->hAttachedThread);
		RenderingContext::sWindowMap.erase(this->pAttachedWindow);

		delete this->pRenderer;

		wglMakeCurrent(nullptr, nullptr);

		this->hAttachedThread = nullptr;
		this->pAttachedWindow = nullptr;
		this->pRenderer = nullptr;
	}

	bool RenderingContext::attach(Window *pWindow)
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

		this->pRenderer = new Render::Renderer(pWindow);

		RenderingContext::sThreadMap[this->hAttachedThread = ::GetCurrentThread()] = this;
		RenderingContext::sWindowMap[this->pAttachedWindow = pWindow] = this;

		return true;
	}

	void RenderingContext::redraw()
	{
		if (!this->attached())
			return;

		this->update();

		::RedrawWindow(this->pAttachedWindow->handle(), nullptr, nullptr, RDW_INVALIDATE);
	}

	RenderingContext *RenderingContext::find(HANDLE hThread)
	{
		auto iIndex{RenderingContext::sThreadMap.find(hThread)};

		return iIndex == RenderingContext::sThreadMap.cend() ? nullptr : iIndex->second;
	}

	RenderingContext *RenderingContext::find(Window *pWindow)
	{
		auto iIndex{RenderingContext::sWindowMap.find(pWindow)};

		return iIndex == RenderingContext::sWindowMap.cend() ? nullptr : iIndex->second;
	}

	LRESULT RenderingContext::handleWindowMessage(Window *pWindow, HWND hWindow, UINT nMessage, WPARAM wParam, LPARAM lParam)
	{
		if (!this->attached())
			return Window::NoHandler;

		if (pWindow != this->pAttachedWindow)
			return Window::NoHandler;

		switch (nMessage)
		{
		case WM_SIZE:
		case WM_SIZING:
		{
			this->update();
		}
		break;
		case WM_PAINT:
		{
			this->render();
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
}