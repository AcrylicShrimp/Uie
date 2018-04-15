
/*
	2018.04.09
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_UIE_EVENT_UIMOUSEEVENT_H

#define _CLASS_UIE_EVENT_UIMOUSEEVENT_H

#include "../UieDLL.h"

#include "UIInputEvent.h"

namespace Uie::Event
{
	class UIE_DLL UIMouseEvent : public UIInputEvent
	{
	protected:
		float nMouseX;
		float nMouseY;
		
	public:
		UIMouseEvent(float nMouseX, float nMouseY);
		UIMouseEvent(const UIMouseEvent &sSrc) = default;
		~UIMouseEvent() = default;
		
	public:
		UIMouseEvent &operator=(const UIMouseEvent &sSrc) = default;
		
	public:
		inline float mouseX() const;
		inline float mouseY() const;
	};

	inline float UIMouseEvent::mouseX() const
	{
		return this->nMouseX;
	}
	
	inline float UIMouseEvent::mouseY() const
	{
		return this->nMouseY;
	}
}

#endif