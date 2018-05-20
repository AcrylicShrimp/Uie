
/*
	2018.05.12
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_UIE_RENDER_CONTEXT_H

#define _CLASS_UIE_RENDER_CONTEXT_H

#include "../UieDLL.h"

#include "../Window.h"

#include <unordered_map>
#include <Windows.h>

namespace Uie::Render
{
	class UIE_DLL Context final
	{
	private:
		static std::unordered_map<HANDLE, Context *> sContextMap;
		Window *pWindow;
		HDC hDeviceContext;
		HGLRC hRenderingContext;
		BYTE nColorBit;
		BYTE nDepthBit;
		BYTE nStencilBit;
		
	public:
		Context(Window *pWindow);
		Context(const Context &sSrc) = delete;
		Context(Context &&sSrc);
		~Context();
		
	public:
		Context &operator=(const Context &sSrc) = delete;
		Context &operator=(Context &&sSrc);
		
	public:
		inline Window *window();
		inline const Window *window() const;
		inline HDC deviceContext() const;
		inline HGLRC renderingContext() const;
		inline BYTE colorBit() const;
		inline bool isCreated() const;
		inline bool isOpenGLContext() const;
		inline static Context *obtainContext();
		bool create(BYTE nColorBit, BYTE nDepthBit, BYTE nStencilBit, bool bIsOpenGLContext = true);
		void release();
		bool enableThread();
		bool enableThread(const Context &sOpenGLContext);
		void disableThread();
	};

	inline Window *Context::window()
	{
		return this->pWindow;
	}

	inline const Window *Context::window() const
	{
		return this->pWindow;
	}

	inline HDC Context::deviceContext() const
	{
		return this->hDeviceContext;
	}

	inline HGLRC Context::renderingContext() const
	{
		return this->hRenderingContext;
	}

	inline BYTE Context::colorBit() const
	{
		return this->nColorBit;
	}

	inline bool Context::isCreated() const
	{
		return this->hDeviceContext != nullptr;
	}

	inline bool Context::isOpenGLContext() const
	{
		return this->hRenderingContext != nullptr;
	}

	inline Context *Context::obtainContext()
	{
		auto iIndex{Context::sContextMap.find(GetCurrentThread())};
		return iIndex == Context::sContextMap.cend() ? nullptr : iIndex->second;
	}
}

#endif