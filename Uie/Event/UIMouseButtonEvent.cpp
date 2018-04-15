
/*
	2018.04.15
	Created by AcrylicShrimp.
*/

#include "UIMouseButtonEvent.h"

namespace Uie::Event
{
	UIMouseButtonEvent::UIMouseButtonEvent(float nMouseX, float nMouseY, int nKeycode, bool bPressed) :
		UIMouseEvent(nMouseX, nMouseY),
		nKeycode{nKeycode},
		bPressed{bPressed}
	{
		//Empty.
	}
}