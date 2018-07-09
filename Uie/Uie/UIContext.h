
/*
	2018.07.02
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_UIE_UICONTEXT_H

#define _CLASS_UIE_UICONTEXT_H

#include "UieDLL.h"

#include "Window.h"
#include "WindowMessageHandler.h"
#include "Render/RenderingContext.h"
#include "UI/Placement.h"

#include <cstdint>
#include <unordered_map>
#include <Windows.h>

namespace Uie
{
	class UIE_DLL UIContext final : public WindowMessageHandler, public Render::RenderingContext
	{
	protected:
		static std::unordered_map<HANDLE, UIContext *> sThreadRenderingContextMap;
		static std::unordered_map<Window *, UIContext *> sWindowRenderingContextMap;
		UI::Placement *pPlacement{nullptr};
		std::unordered_map<std::string, UI::Placement> sPlacementMap;

	public:
		UIContext();
		UIContext(const UIContext &sSrc) = delete;
		~UIContext() = default;

	public:
		UIContext &operator=(const UIContext &sSrc) = delete;

	public:
		inline static UIContext *current();
		virtual void destroy() override;
		virtual void detach() override;
		virtual bool attach(Window *pWindow) override;
		void inactivePlacement();
		void activePlacement(const std::string &sName);
		UI::Placement *createPlacement(const std::string &sName);
		UI::Placement *findPlacement(const std::string &sName);
		const UI::Placement *findPlacement(const std::string &sName) const;
		void removePlacement(const std::string &sName);
		virtual LRESULT handleWindowMessage(Window *pWindow, HWND hWindow, UINT nMessage, WPARAM wParam, LPARAM lParam) override;
		static UIContext *find(HANDLE hThread);
		static UIContext *find(Window *pWindow);

	protected:
		virtual void update() override;
		virtual void render() override;
	};

	inline UIContext *UIContext::current()
	{
		return UIContext::find(::GetCurrentThread());
	}
}

#endif