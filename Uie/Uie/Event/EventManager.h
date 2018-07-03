
/*
	2018.04.12
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_UIE_EVENT_EVENTMANAGER_H

#define _CLASS_UIE_EVENT_EVENTMANAGER_H

#include "../UieDLL.h"

#include "../ManagerBase.h"
#include "../UIElement.h"
#include "../Window.h"
#include "../WindowManager.h"
#include "../WindowMessageHandler.h"
#include "UIEvents.h"

#include <tuple>
#include <unordered_map>
#include <Windows.h>
#include <windowsx.h>

namespace Uie::Event
{
	class UIE_DLL EventManager final : public ManagerBase<EventManager>, public WindowMessageHandler
	{
	public:
		struct State
		{
			bool bMouseEntered;
			UIElement *pFocusedElement;
			UIElement *pMouseEnteredElement;
		};

	private:
		std::unordered_map<Window *, State> sWindowStateMap;

	public:
		EventManager();
		EventManager(const EventManager &sSrc) = default;
		~EventManager();

	public:
		EventManager &operator=(const EventManager &sSrc) = default;

	public:
		virtual LRESULT handleWindowMessage(Window *pWindow, HWND hWindow, UINT nMessage, WPARAM wParam, LPARAM lParam) override;
		
	private:
		UIElement *raycastElement(UIPlacement *pPlacement, float nX, float nY);
	};
}

#endif