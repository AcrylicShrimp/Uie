
/*
	2018.04.05
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_UIE_WINDOWMANAGER_H

#define _CLASS_UIE_WINDOWMANAGER_H

#include "UieDLL.h"

#include "ManagerBase.h"
#include "UIPlacement.h"
#include "Window.h"
#include "WindowMessageHandler.h"

#include <functional>
#include <unordered_map>
#include <Windows.h>

namespace Uie
{
	class UIE_DLL WindowManager final : public ManagerBase<WindowManager>, public WindowMessageHandler
	{
	private:
		std::unordered_map<Window *, UIPlacement *> sWindowPlacementMap;
		std::unordered_map<Window *, std::function<void(Window *)>> sCloseEventHandlerMap;

	public:
		WindowManager();
		WindowManager(const WindowManager &sSrc) = delete;
		~WindowManager();

	public:
		WindowManager &operator=(const WindowManager &sSrc) = delete;

	public:
		inline void linkPlacement(Window *pWindow, UIPlacement *pPlacement);
		inline void unlinkPlacement(Window *pWindow);
		inline UIPlacement *findPlacement(Window *pWindow);
		inline void registerCloseEvent(Window *pWindow, std::function<void(Window *)> fEventHandler);
		inline void unregisterCloseEvent(Window *pWindow);
		virtual LRESULT handleWindowMessage(Window *pWindow, HWND hWindow, UINT nMessage, WPARAM wParam, LPARAM lParam) override;
	};

	inline void WindowManager::linkPlacement(Window *pWindow, UIPlacement *pPlacement)
	{
		auto &pCurrentPlacement{this->sWindowPlacementMap[pWindow]};

		if (pCurrentPlacement)
			SendMessage(pWindow->windowHandle(), WM_UIE_UNLINK_PLACEMENT, 0, 0);

		pCurrentPlacement = pPlacement;
		SendMessage(pWindow->windowHandle(), WM_UIE_LINK_PLACEMENT, 0, 0);
	}

	inline void WindowManager::unlinkPlacement(Window *pWindow)
	{
		if (this->sWindowPlacementMap[pWindow])
			SendMessage(pWindow->windowHandle(), WM_UIE_UNLINK_PLACEMENT, 0, 0);

		this->sWindowPlacementMap.erase(pWindow);
	}

	inline UIPlacement *WindowManager::findPlacement(Window *pWindow)
	{
		auto iIndex{this->sWindowPlacementMap.find(pWindow)};
		return iIndex == this->sWindowPlacementMap.cend() ? nullptr : iIndex->second;
	}

	inline void WindowManager::registerCloseEvent(Window *pWindow, std::function<void(Window *)> fEventHandler)
	{
		this->sCloseEventHandlerMap.emplace(pWindow, fEventHandler);
	}

	inline void WindowManager::unregisterCloseEvent(Window *pWindow)
	{
		this->sCloseEventHandlerMap.erase(pWindow);
	}
}

#endif