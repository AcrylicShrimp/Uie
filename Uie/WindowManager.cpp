
/*
	2018.04.05
	Created by AcrylicShrimp.
*/

#include "WindowManager.h"

namespace Uie
{
	WindowManager::WindowManager() :
		WindowMessageHandler({WM_CLOSE, WM_DESTROY})
	{
		Window::registerGlobalHandler(this);
	}

	WindowManager::~WindowManager()
	{
		Window::unregisterGlobalHandler(this);
	}

	LRESULT WindowManager::handleWindowMessage(Window *pWindow, HWND hWindow, UINT nMessage, WPARAM wParam, LPARAM lParam)
	{
		switch (nMessage)
		{
		case WM_CLOSE:
		{
			auto iIndex{this->sCloseEventHandlerMap.find(pWindow)};

			if (iIndex != this->sCloseEventHandlerMap.cend())
				iIndex->second(pWindow);
			else
				PostQuitMessage(0);
		}
		break;
		case WM_DESTROY:
		{
			this->unlinkPlacement(pWindow);
			this->unregisterCloseEvent(pWindow);
		}
		break;
		default:
			break;
		}

		return 0;
	}
}