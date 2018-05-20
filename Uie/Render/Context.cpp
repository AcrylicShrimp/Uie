
/*
	2018.05.12
	Created by AcrylicShrimp.
*/

#include "Context.h"

namespace Uie::Render
{
	std::unordered_map<HANDLE, Context *> Context::sContextMap;

	Context::Context(Window *pWindow) :
		pWindow{pWindow},
		hDeviceContext{nullptr},
		hRenderingContext{nullptr},
		nColorBit{0},
		nDepthBit{0},
		nStencilBit{0}
	{
		//Empty.
	}

	Context::Context(Context &&sSrc) :
		pWindow{sSrc.pWindow},
		hDeviceContext{sSrc.hDeviceContext},
		hRenderingContext{sSrc.hRenderingContext},
		nColorBit{sSrc.nColorBit},
		nDepthBit{sSrc.nDepthBit},
		nStencilBit{sSrc.nStencilBit}
	{
		sSrc.pWindow = nullptr;
		sSrc.hDeviceContext = nullptr;
		sSrc.hRenderingContext = nullptr;
		sSrc.nColorBit = 0;
		sSrc.nDepthBit = 0;
		sSrc.nStencilBit = 0;

		for (auto &sPair : Context::sContextMap)
			if (sPair.second == &sSrc)
				sPair.second = this;
	}

	Context::~Context()
	{
		this->release();
	}

	Context &Context::operator=(Context &&sSrc)
	{
		if (&sSrc == this)
			return *this;

		this->~Context();

		this->pWindow = sSrc.pWindow;
		this->hDeviceContext = sSrc.hDeviceContext;
		this->hRenderingContext = sSrc.hRenderingContext;
		this->nColorBit = sSrc.nColorBit;
		this->nDepthBit = sSrc.nDepthBit;
		this->nStencilBit = sSrc.nStencilBit;

		sSrc.pWindow = nullptr;
		sSrc.hDeviceContext = nullptr;
		sSrc.hRenderingContext = nullptr;
		sSrc.nColorBit = 0;
		sSrc.nDepthBit = 0;
		sSrc.nStencilBit = 0;

		for (auto &sPair : Context::sContextMap)
			if (sPair.second == &sSrc)
				sPair.second = this;

		return *this;
	}

	bool Context::create(BYTE nColorBit, BYTE nDepthBit, BYTE nStencilBit, bool bIsOpenGLContext)
	{
		if (this->isCreated())
			this->release();

		if (!(this->hDeviceContext = GetDC(this->pWindow->windowHandle())))
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

		auto nPixelFormat{ChoosePixelFormat(this->hDeviceContext, &sFormat)};

		if (!nPixelFormat)
		{
			this->release();
			return false;
		}

		if (!SetPixelFormat(this->hDeviceContext, nPixelFormat, &sFormat))
		{
			this->release();
			return false;
		}

		SendMessageW(this->pWindow->windowHandle(), WM_UIE_CONTEXT_CREATE, 0, 0);

		if (!bIsOpenGLContext)
			return true;

		if (!(this->hRenderingContext = wglCreateContext(this->hDeviceContext)))
		{
			this->release();
			return false;
		}

		SendMessageW(this->pWindow->windowHandle(), WM_UIE_OPENGL_CONTEXT_CREATE, 0, 0);

		return true;
	}

	void Context::release()
	{
		this->disableThread();

		if (this->hRenderingContext)
		{
			wglDeleteContext(this->hRenderingContext);
			this->hRenderingContext = nullptr;

			SendMessageW(this->pWindow->windowHandle(), WM_UIE_OPENGL_CONTEXT_DESTROY, 0, 0);
		}

		if (this->hDeviceContext)
		{
			ReleaseDC(this->pWindow->windowHandle(), this->hDeviceContext);
			this->hDeviceContext = nullptr;

			SendMessageW(this->pWindow->windowHandle(), WM_UIE_CONTEXT_DESTROY, 0, 0);
		}

		for (auto iIndex{Context::sContextMap.cbegin()}, iEnd{Context::sContextMap.cend()}; iIndex != iEnd; )
			if (iIndex->second == this)
				Context::sContextMap.erase(iIndex++);
			else
				++iIndex;
	}

	bool Context::enableThread()
	{
		if (!this->isOpenGLContext())
			return false;

		if (wglMakeCurrent(this->hDeviceContext, this->hRenderingContext))
		{
			Context::sContextMap[GetCurrentThread()] = this;
			SendMessageW(this->pWindow->windowHandle(), WM_UIE_LINK_CONTEXT, 0, 0);
			return true;
		}

		return false;
	}

	bool Context::enableThread(const Context &sOpenGLContext)
	{
		if (!this->isCreated() || !sOpenGLContext.isOpenGLContext())
			return false;

		if (wglMakeCurrent(this->hDeviceContext, this->hRenderingContext))
		{
			Context::sContextMap[GetCurrentThread()] = this;
			SendMessageW(this->pWindow->windowHandle(), WM_UIE_LINK_CONTEXT, 0, 0);
			return true;
		}

		return false;
	}

	void Context::disableThread()
	{
		SendMessageW(this->pWindow->windowHandle(), WM_UIE_UNLINK_CONTEXT, 0, 0);
		Context::sContextMap.erase(GetCurrentThread());
		wglMakeCurrent(nullptr, nullptr);
	}
}