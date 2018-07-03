
/*
	2018.04.15
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_UIE_EVENT_UIMOUSEBUTTONEVENT_H

#define _CLASS_UIE_EVENT_UIMOUSEBUTTONEVENT_H

#include "../UieDLL.h"

#include "UIMouseEvent.h"

namespace Uie::Event
{
	class UIE_DLL UIMouseButtonEvent : public UIMouseEvent
	{
	protected:
		int nKeycode;
		bool bPressed;
		
	public:
		UIMouseButtonEvent(float nMouseX, float nMouseY, int nKeycode, bool bPressed);
		UIMouseButtonEvent(const UIMouseButtonEvent &sSrc) = default;
		~UIMouseButtonEvent() = default;
		
	public:
		UIMouseButtonEvent &operator=(const UIMouseButtonEvent &sSrc) = default;
		
	public:
		inline int keycode() const;
		inline bool pressed() const;
	};

	inline int UIMouseButtonEvent::keycode() const
	{
		return this->nKeycode;
	}

	inline bool UIMouseButtonEvent::pressed() const
	{
		return this->bPressed;
	}
}

#endif