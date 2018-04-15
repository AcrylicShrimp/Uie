
/*
	2018.04.15
	Created by AcrylicShrimp.
*/

#include "UIInputEvent.h"

#include <Windows.h>

namespace Uie::Event
{
	UIInputEvent::UIInputEvent() :
		bLeftButtonPressed{static_cast<bool>(GetAsyncKeyState(VK_LBUTTON) & 0x8000)},
		bRightButtonPressed{static_cast<bool>(GetAsyncKeyState(VK_RBUTTON) & 0x8000)},
		bMiddleButtonPressed{static_cast<bool>(GetAsyncKeyState(VK_MBUTTON) & 0x8000)},
		bLAltKeyPressed{static_cast<bool>(GetAsyncKeyState(VK_LMENU) & 0x8000)},
		bRAltKeyPressed{static_cast<bool>(GetAsyncKeyState(VK_RMENU) & 0x8000)},
		bLShiftKeyPressed{static_cast<bool>(GetAsyncKeyState(VK_LSHIFT) & 0x8000)},
		bRShiftKeyPressed{static_cast<bool>(GetAsyncKeyState(VK_RSHIFT) & 0x8000)},
		bLControlKeyPressed{static_cast<bool>(GetAsyncKeyState(VK_LCONTROL) & 0x8000)},
		bRControlKeyPressed{static_cast<bool>(GetAsyncKeyState(VK_RCONTROL) & 0x8000)}
	{
		//Empty.
	}
}