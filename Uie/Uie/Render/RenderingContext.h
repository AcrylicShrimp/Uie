
/*
	2018.07.02
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_UIE_RENDER_RENDERINGCONTEXT_H

#define _CLASS_UIE_RENDER_RENDERINGCONTEXT_H

#include "../UieDLL.h"

#include "../Window.h"

#include <unordered_map>
#include <Windows.h>

namespace Uie::Render
{
	class UIE_DLL RenderingContext final
	{
	private:
		static std::unordered_map<HANDLE, RenderingContext *> sThreadRenderingContextMap;
		static std::unordered_map<Window *, RenderingContext *> sWindowRenderingContextMap;
		HGLRC hRenderingContext{nullptr};
		HANDLE hAttachedThread{nullptr};
		Window *pAttachedWindow{nullptr};

	public:
		RenderingContext() = default;
		RenderingContext(const RenderingContext &sSrc) = delete;
		RenderingContext(RenderingContext &&sSrc);
		~RenderingContext();

	public:
		RenderingContext &operator=(const RenderingContext &sSrc) = delete;
		RenderingContext &operator=(RenderingContext &&sSrc);

	public:
		inline HGLRC renderingContext() const;
		inline HANDLE attachedThread() const;
		inline Window *attachedWindow();
		inline const Window *attachedWindow() const;
		inline bool created() const;
		inline bool attached() const;
		inline static RenderingContext *current();
		void destroy();
		bool create(Window *pWindow);
		void detach();
		bool attach(Window *pWindow);
		static RenderingContext *find(HANDLE hThread);
		static RenderingContext *find(Window *pWindow);
	};

	inline HGLRC RenderingContext::renderingContext() const
	{
		return this->hRenderingContext;
	}

	inline HANDLE RenderingContext::attachedThread() const
	{
		return this->hAttachedThread;
	}

	inline Window *RenderingContext::attachedWindow()
	{
		return this->pAttachedWindow;
	}

	inline const Window *RenderingContext::attachedWindow() const
	{
		return this->pAttachedWindow;
	}

	inline bool RenderingContext::created() const
	{
		return this->hRenderingContext != nullptr;
	}

	inline bool RenderingContext::attached() const
	{
		return this->hAttachedThread != nullptr && this->pAttachedWindow != nullptr;
	}

	inline RenderingContext *RenderingContext::current()
	{
		return RenderingContext::find(::GetCurrentThread());
	}
}

#endif