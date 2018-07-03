
/*
	2018.04.15
	Created by AcrylicShrimp.
*/

#include "UITypeEvent.h"

namespace Uie::Event
{
	UITypeEvent::UITypeEvent(State eState, const std::wstring &sString) :
		eState{eState},
		sString{sString}
	{
		//Empty.
	}
}