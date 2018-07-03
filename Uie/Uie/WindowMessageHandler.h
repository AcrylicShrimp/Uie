
/*
	2018.04.05
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_UIE_WINDOWMESSAGEHANDLER_H

#define _CLASS_UIE_WINDOWMESSAGEHANDLER_H

#include "UieDLL.h"

#include <initializer_list>
#include <vector>
#include <Windows.h>
#include <windowsx.h>

namespace Uie
{
	class Window;

	class UIE_DLL WindowMessageHandler
	{
	protected:
		std::vector<UINT> sMessageList;
		
	public:
		WindowMessageHandler(std::initializer_list<UINT> sMessageList);
		WindowMessageHandler(const WindowMessageHandler &sSrc);
		virtual ~WindowMessageHandler() = default;
		
	public:
		WindowMessageHandler &operator=(const WindowMessageHandler &sSrc);
		
	public:
		inline const std::vector<UINT> &messageList() const;
		virtual LRESULT handleWindowMessage(Window *pWindow, HWND hWindow, UINT nMessage, WPARAM wParam, LPARAM lParam) = 0;
	};

	inline const std::vector<UINT> &WindowMessageHandler::messageList() const
	{
		return this->sMessageList;
	}
}

#endif