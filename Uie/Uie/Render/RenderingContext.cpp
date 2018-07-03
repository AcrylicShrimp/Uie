
/*
	2018.07.02
	Created by AcrylicShrimp.
*/

#include "RenderingContext.h"

namespace Uie::Render
{
	std::unordered_map<HANDLE, RenderingContext *> RenderingContext::sThreadRenderingContextMap;
	std::unordered_map<Window *, RenderingContext *> RenderingContext::sWindowRenderingContextMap;

	RenderingContext::RenderingContext(RenderingContext &&sSrc) :
		hRenderingContext{sSrc.hRenderingContext},
		hAttachedThread{sSrc.hAttachedThread},
		pAttachedWindow{sSrc.pAttachedWindow}
	{
		sSrc.hRenderingContext = nullptr;
		sSrc.hAttachedThread = nullptr;
		sSrc.pAttachedWindow = nullptr;

		if (this->attached())
		{
			RenderingContext::sThreadRenderingContextMap[this->hAttachedThread] = this;
			RenderingContext::sWindowRenderingContextMap[this->pAttachedWindow] = this;
		}
	}

	RenderingContext::~RenderingContext()
	{
		this->destroy();
	}

	RenderingContext &RenderingContext::operator=(RenderingContext &&sSrc)
	{
		if (&sSrc == this)
			return *this;

		this->destroy();

		this->hRenderingContext = sSrc.hRenderingContext;
		this->hAttachedThread = sSrc.hAttachedThread;
		this->pAttachedWindow = sSrc.pAttachedWindow;

		sSrc.hRenderingContext = nullptr;
		sSrc.hAttachedThread = nullptr;
		sSrc.pAttachedWindow = nullptr;

		if (this->attached())
		{
			RenderingContext::sThreadRenderingContextMap[this->hAttachedThread] = this;
			RenderingContext::sWindowRenderingContextMap[this->pAttachedWindow] = this;
		}

		return *this;
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

		RenderingContext::sThreadRenderingContextMap.erase(this->hAttachedThread);
		RenderingContext::sWindowRenderingContextMap.erase(this->pAttachedWindow);

		wglMakeCurrent(nullptr, nullptr);

		this->hAttachedThread = nullptr;
		this->pAttachedWindow = nullptr;
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

		RenderingContext::sThreadRenderingContextMap[this->hAttachedThread = ::GetCurrentThread()] = this;
		RenderingContext::sWindowRenderingContextMap[this->pAttachedWindow = pWindow] = this;

		return true;
	}

	RenderingContext *RenderingContext::find(HANDLE hThread)
	{
		auto iIndex{RenderingContext::sThreadRenderingContextMap.find(hThread)};

		return iIndex == RenderingContext::sThreadRenderingContextMap.cend() ? nullptr : iIndex->second;
	}

	RenderingContext *RenderingContext::find(Window *pWindow)
	{
		auto iIndex{RenderingContext::sWindowRenderingContextMap.find(pWindow)};

		return iIndex == RenderingContext::sWindowRenderingContextMap.cend() ? nullptr : iIndex->second;
	}
}