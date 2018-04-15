
/*
	2018.04.15
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_UIE_EVENT_UIKEYBOARDEVENT_H

#define _CLASS_UIE_EVENT_UIKEYBOARDEVENT_H

#include "../UieDLL.h"

#include "UIInputEvent.h"

namespace Uie::Event
{
	class UIE_DLL UIKeyboardEvent : public UIInputEvent
	{
	protected:
		int nKeycode;

	public:
		UIKeyboardEvent(int nKeycode);
		UIKeyboardEvent(const UIKeyboardEvent &sSrc) = default;
		~UIKeyboardEvent() = default;
		
	public:
		UIKeyboardEvent &operator=(const UIKeyboardEvent &sSrc) = default;
		
	public:
		inline int keycode() const;
	};

	inline int UIKeyboardEvent::keycode() const
	{
		return this->nKeycode;
	}
}

#endif