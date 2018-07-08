
/*
	2018.04.12
	Created by AcrylicShrimp.
*/

#include "EventManager.h"

namespace Uie::Event
{
	EventManager::EventManager() :
		WindowMessageHandler({
		WM_MOUSEMOVE,
		WM_MOUSELEAVE,
		WM_KEYDOWN,
		WM_SYSKEYDOWN,
		WM_KEYUP,
		WM_SYSKEYUP,
		WM_CHAR,
		WM_SYSCHAR,
		WM_IME_COMPOSITION,
		WM_LBUTTONDOWN,
		WM_LBUTTONUP,
		WM_MBUTTONDOWN,
		WM_MBUTTONUP,
		WM_RBUTTONDOWN,
		WM_RBUTTONUP,
		WM_XBUTTONDOWN,
		WM_XBUTTONUP})
	{
		Window::registerGlobalHandler(this);
	}

	EventManager::~EventManager()
	{
		Window::unregisterGlobalHandler(this);
	}

	LRESULT EventManager::handleWindowMessage(Window *pWindow, HWND hWindow, UINT nMessage, WPARAM wParam, LPARAM lParam)
	{
		//if (nMessage == WM_UIE_LINK_PLACEMENT)
		//{
		//	this->sWindowStateMap.emplace(pWindow, State{false, nullptr, nullptr});
		//	return 0;
		//}
		//else if (nMessage == WM_UIE_UNLINK_PLACEMENT)
		//{
		//	this->sWindowStateMap.erase(pWindow);
		//	return 0;
		//}

		auto pPlacement{WindowManager::instance().findPlacement(pWindow)};

		if (!pPlacement)
			return Window::NoHandler;

		auto iIndex{this->sWindowStateMap.find(pWindow)};

		if (iIndex == this->sWindowStateMap.cend())
			return Window::NoHandler;

		auto &sState{iIndex->second};

		switch (nMessage)
		{
		case WM_MOUSEMOVE:
		{
			if (!sState.bMouseEntered)
			{
				sState.bMouseEntered = true;

				TRACKMOUSEEVENT sTrackMouseEvent;
				sTrackMouseEvent.cbSize = sizeof(sTrackMouseEvent);
				sTrackMouseEvent.dwFlags = TME_LEAVE;
				sTrackMouseEvent.hwndTrack = hWindow;

				TrackMouseEvent(&sTrackMouseEvent);
			}

			auto nX{GET_X_LPARAM(lParam) / static_cast<float>(pWindow->sizeInfo().nClientWidth)};
			auto nY{GET_Y_LPARAM(lParam) / static_cast<float>(pWindow->sizeInfo().nClientHeight)};

			nX = nX * 2.f - 1.f;
			nY = nY * 2.f - 1.f;

			auto pElement{this->raycastElement(pPlacement, nX, nY)};
			UIMouseEvent sMouseEvent{nX, nY};

			if (!pElement)
			{
				if (sState.pMouseEnteredElement)
					sState.pMouseEnteredElement->handleEvent("mouse.leave", &sMouseEvent);
			}
			else if (sState.pMouseEnteredElement == pElement)
				sState.pMouseEnteredElement->handleEvent("mouse.move", &sMouseEvent);
			else
			{
				if (sState.pMouseEnteredElement)
					sState.pMouseEnteredElement->handleEvent("mouse.leave", &sMouseEvent);

				pElement->handleEvent("mouse.enter", &sMouseEvent);
			}

			sState.pMouseEnteredElement = pElement;
		}
		break;
		case WM_MOUSELEAVE:
		{
			sState.bMouseEntered = false;

			if (sState.pMouseEnteredElement)
				sState.pMouseEnteredElement->handleEvent("mouse.leave", nullptr);

			sState.pMouseEnteredElement = nullptr;
		}
		break;
		case WM_KEYDOWN:
		case WM_SYSKEYDOWN:
		{
			if (sState.pFocusedElement)
			{
				UIKeyboardEvent sKeyboardEvent{static_cast<int>(wParam)};
				sState.pFocusedElement->handleEvent("keyboard.down", &sKeyboardEvent);
			}
		}
		break;
		case WM_KEYUP:
		case WM_SYSKEYUP:
		{
			if (sState.pFocusedElement)
			{
				UIKeyboardEvent sKeyboardEvent{static_cast<int>(wParam)};
				sState.pFocusedElement->handleEvent("keyboard.up", &sKeyboardEvent);
			}
		}
		break;
		case WM_CHAR:
		case WM_SYSCHAR:
		{
			if (sState.pFocusedElement)
			{
				UITypeEvent sTypeEvent{UITypeEvent::State::Composed, {static_cast<wchar_t>(wParam)}};
				sState.pFocusedElement->handleEvent("keyboard.type", &sTypeEvent);
			}
		}
		break;
		case WM_IME_COMPOSITION:
		{
			auto hImmContext{ImmGetContext(hWindow)};

			if (lParam & GCS_COMPSTR)
			{
				std::size_t nLength{static_cast<std::size_t>(ImmGetCompositionStringW(hImmContext, GCS_COMPSTR, nullptr, 0))};
				
				std::wstring sString(nLength / sizeof(std::wstring::value_type), L'\0');
				ImmGetCompositionStringW(hImmContext, GCS_COMPSTR, sString.data(), nLength);

				if (sState.pFocusedElement)
				{
					UITypeEvent sTypeEvent{sString.length() ? UITypeEvent::State::Composing : UITypeEvent::State::ComposingCanceled, sString};
					sState.pFocusedElement->handleEvent("keyboard.type", &sTypeEvent);
				}
			}
			else if (lParam & GCS_RESULTSTR)
			{
				std::size_t nLength{static_cast<std::size_t>(ImmGetCompositionStringW(hImmContext, GCS_RESULTSTR, nullptr, 0))};

				std::wstring sString(nLength / sizeof(std::wstring::value_type), L'\0');
				ImmGetCompositionStringW(hImmContext, GCS_RESULTSTR, sString.data(), nLength);

				if (sState.pFocusedElement)
				{
					UITypeEvent sTypeEvent{UITypeEvent::State::Composed, sString};
					sState.pFocusedElement->handleEvent("keyboard.type", &sTypeEvent);
				}
			}
			else if (
				!((GCS_COMPREADSTR |
				GCS_COMPREADATTR |
				GCS_COMPREADCLAUSE |
				GCS_COMPSTR |
				GCS_COMPATTR |
				GCS_COMPCLAUSE |
				GCS_CURSORPOS |
				GCS_DELTASTART |
				GCS_RESULTREADSTR |
				GCS_RESULTREADCLAUSE |
				GCS_RESULTSTR |
				GCS_RESULTCLAUSE) & lParam))
			{
				if (sState.pFocusedElement)
				{
					UITypeEvent sTypeEvent{UITypeEvent::State::ComposingCanceled, L""};
					sState.pFocusedElement->handleEvent("keyboard.type", &sTypeEvent);
				}
			}

			ImmReleaseContext(hWindow, hImmContext);
		}
		break;
		case WM_LBUTTONDOWN:
		case WM_MBUTTONDOWN:
		case WM_RBUTTONDOWN:
		case WM_XBUTTONDOWN:
		{
			auto nX{GET_X_LPARAM(lParam) / static_cast<float>(pWindow->sizeInfo().nClientWidth)};
			auto nY{GET_Y_LPARAM(lParam) / static_cast<float>(pWindow->sizeInfo().nClientHeight)};

			nX = nX * 2.f - 1.f;
			nY = nY * 2.f - 1.f;

			auto pElement{this->raycastElement(pPlacement, nX, nY)};
			UIMouseButtonEvent sMouseButtonEvent
			{
				nX,
				nY,
				nMessage == WM_LBUTTONDOWN ? VK_LBUTTON :
				nMessage == WM_MBUTTONDOWN ? VK_MBUTTON :
				nMessage == WM_RBUTTONDOWN ? VK_RBUTTON :
				GET_XBUTTON_WPARAM(wParam),
				true
			};

			if (pElement != sState.pFocusedElement)
			{
				if (sState.pFocusedElement)
					sState.pFocusedElement->handleEvent("focus.leave", nullptr);

				(sState.pFocusedElement = pElement)->handleEvent("focus.enter", nullptr);
			}

			pElement->handleEvent("mouse.down", &sMouseButtonEvent);
		}
		break;
		case WM_LBUTTONUP:
		case WM_MBUTTONUP:
		case WM_RBUTTONUP:
		case WM_XBUTTONUP:
		{
			auto nX{GET_X_LPARAM(lParam) / static_cast<float>(pWindow->sizeInfo().nClientWidth)};
			auto nY{GET_Y_LPARAM(lParam) / static_cast<float>(pWindow->sizeInfo().nClientHeight)};

			nX = nX * 2.f - 1.f;
			nY = nY * 2.f - 1.f;

			auto pElement{this->raycastElement(pPlacement, nX, nY)};
			UIMouseButtonEvent sMouseButtonEvent
			{
				nX,
				nY,
				nMessage == WM_LBUTTONDOWN ? VK_LBUTTON :
				nMessage == WM_MBUTTONDOWN ? VK_MBUTTON :
				nMessage == WM_RBUTTONDOWN ? VK_RBUTTON :
				GET_XBUTTON_WPARAM(wParam),
				false
			};

			pElement->handleEvent("mouse.up", &sMouseButtonEvent);
		}
		break;
		default:
			return Window::NoHandler;
		}

		return 0;
	}

	Element *EventManager::raycastElement(UIPlacement *pPlacement, float nX, float nY)
	{
		Element *pResult{nullptr};

		pPlacement->iterateAll(UIPlacement::IterationOrder::FrontToBack, [nX, nY, &pResult](Element *pElement)
		{
			if (!pElement->rect().contains(nX, nY))
				return false;

			pResult = pElement;
			return true;
		});

		return pResult;
	}
}