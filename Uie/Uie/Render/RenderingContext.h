
/*
	2018.07.09
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_UIE_RENDER_RENDERINGCONTEXT_H

#define _CLASS_UIE_RENDER_RENDERINGCONTEXT_H

#include "../UieDLL.h"

#include "Renderer.h"
#include "../Window.h"

#include <cstdint>
#include <Windows.h>

namespace Uie::Render
{
	class UIE_DLL RenderingContext
	{
	protected:
		static std::unordered_map<HANDLE, RenderingContext *> sThreadMap;
		static std::unordered_map<Window *, RenderingContext *> sWindowMap;
		HGLRC hRenderingContext{nullptr};
		HANDLE hAttachedThread{nullptr};
		Window *pAttachedWindow{nullptr};
		Renderer *pRenderer{nullptr};
		
	public:
		RenderingContext() = default;
		RenderingContext(const RenderingContext &sSrc) = delete;
		virtual ~RenderingContext();
		
	public:
		RenderingContext &operator=(const RenderingContext &sSrc) = delete;
		
	public:
		inline HGLRC renderingContext() const;
		inline Window *attachedWindow();
		inline const Window *attachedWindow() const;
		inline Renderer *renderer();
		inline const Renderer *renderer() const;
		inline bool created() const;
		inline bool attached() const;
		inline static RenderingContext *current();
		virtual void destroy();
		virtual bool create(Window *pWindow);
		virtual void detach();
		virtual bool attach(Window *pWindow);
		void redraw();
		static RenderingContext *find(HANDLE hThread);
		static RenderingContext *find(Window *pWindow);

	protected:
		virtual void update() = 0;
		virtual void render() = 0;
		LRESULT handleWindowMessage(Window *pWindow, HWND hWindow, UINT nMessage, WPARAM wParam, LPARAM lParam);
	};

	inline HGLRC RenderingContext::renderingContext() const
	{
		return this->hRenderingContext;
	}

	inline Window *RenderingContext::attachedWindow()
	{
		return this->pAttachedWindow;
	}

	inline const Window *RenderingContext::attachedWindow() const
	{
		return this->pAttachedWindow;
	}

	inline Renderer *RenderingContext::renderer()
	{
		return this->pRenderer;
	}

	inline const Renderer *RenderingContext::renderer() const
	{
		return this->pRenderer;
	}

	inline bool RenderingContext::created() const
	{
		return this->hRenderingContext != nullptr;
	}

	inline bool RenderingContext::attached() const
	{
		return this->pAttachedWindow != nullptr;
	}

	inline RenderingContext *RenderingContext::current()
	{
		return RenderingContext::find(::GetCurrentThread());
	}
}

#endif