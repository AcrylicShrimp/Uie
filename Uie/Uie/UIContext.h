
/*
	2018.07.02
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_UIE_UICONTEXT_H

#define _CLASS_UIE_UICONTEXT_H

#include "UieDLL.h"

#include "Window.h"
#include "WindowMessageHandler.h"
#include "Render/Renderer.h"
#include "UI/Placement.h"

#include <cstdint>
#include <unordered_map>
#include <Windows.h>

namespace Uie
{
	class UIE_DLL UIContext final : public WindowMessageHandler
	{
	private:
		static std::unordered_map<HANDLE, UIContext *> sThreadRenderingContextMap;
		static std::unordered_map<Window *, UIContext *> sWindowRenderingContextMap;
		HGLRC hRenderingContext{nullptr};
		HANDLE hAttachedThread{nullptr};
		Window *pAttachedWindow{nullptr};
		Render::Renderer *pRenderer{nullptr};
		UI::Placement *pPlacement{nullptr};
		std::unordered_map<std::string, UI::Placement> sPlacementMap;

	public:
		UIContext();
		UIContext(const UIContext &sSrc) = delete;
		~UIContext();

	public:
		UIContext &operator=(const UIContext &sSrc) = delete;

	public:
		inline HGLRC renderingContext() const;
		inline HANDLE attachedThread() const;
		inline Window *attachedWindow();
		inline const Window *attachedWindow() const;
		inline Render::Renderer *renderer();
		inline const Render::Renderer *renderer() const;
		inline bool created() const;
		inline bool attached() const;
		inline static UIContext *current();
		void destroy();
		bool create(Window *pWindow);
		void detach();
		bool attach(Window *pWindow);
		void redraw();
		void inactivePlacement();
		void activePlacement(const std::string &sName);
		UI::Placement *createPlacement(const std::string &sName);
		UI::Placement *findPlacement(const std::string &sName);
		const UI::Placement *findPlacement(const std::string &sName) const;
		void removePlacement(const std::string &sName);
		virtual LRESULT handleWindowMessage(Window *pWindow, HWND hWindow, UINT nMessage, WPARAM wParam, LPARAM lParam) override;
		static UIContext *find(HANDLE hThread);
		static UIContext *find(Window *pWindow);
	};

	inline HGLRC UIContext::renderingContext() const
	{
		return this->hRenderingContext;
	}

	inline HANDLE UIContext::attachedThread() const
	{
		return this->hAttachedThread;
	}

	inline Window *UIContext::attachedWindow()
	{
		return this->pAttachedWindow;
	}

	inline const Window *UIContext::attachedWindow() const
	{
		return this->pAttachedWindow;
	}

	inline Render::Renderer *UIContext::renderer()
	{
		return this->pRenderer;
	}

	inline const Render::Renderer *UIContext::renderer() const
	{
		return this->pRenderer;
	}

	inline bool UIContext::created() const
	{
		return this->hRenderingContext != nullptr;
	}

	inline bool UIContext::attached() const
	{
		return this->hAttachedThread != nullptr && this->pAttachedWindow != nullptr && this->pRenderer != nullptr;
	}

	inline UIContext *UIContext::current()
	{
		return UIContext::find(::GetCurrentThread());
	}
}

#endif