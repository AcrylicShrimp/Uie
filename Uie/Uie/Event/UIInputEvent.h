
/*
	2018.04.15
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_UIE_EVENT_UIINPUTEVENT_H

#define _CLASS_UIE_EVENT_UIINPUTEVENT_H

#include "../UieDLL.h"

namespace Uie::Event
{
	class UIE_DLL UIInputEvent
	{
	protected:
		bool bLeftButtonPressed;
		bool bRightButtonPressed;
		bool bMiddleButtonPressed;
		bool bLAltKeyPressed;
		bool bRAltKeyPressed;
		bool bLShiftKeyPressed;
		bool bRShiftKeyPressed;
		bool bLControlKeyPressed;
		bool bRControlKeyPressed;
		
	public:
		UIInputEvent();
		UIInputEvent(const UIInputEvent &sSrc) = default;
		virtual ~UIInputEvent() = default;
		
	public:
		UIInputEvent &operator=(const UIInputEvent &sSrc) = default;
		
	public:
		inline bool leftButtonPressed() const;
		inline bool rightButtonPressed() const;
		inline bool middleButtonPressed() const;
		inline bool altKeyPressed() const;
		inline bool leftAltKeyPressed() const;
		inline bool rightAltKeyPressed() const;
		inline bool shiftKeyPressed() const;
		inline bool leftShiftKeyPressed() const;
		inline bool rightShiftKeyPressed() const;
		inline bool controlKeyPressed() const;
		inline bool leftControlKeyPressed() const;
		inline bool rightControlKeyPressed() const;
	};

	inline bool UIInputEvent::leftButtonPressed() const
	{
		return this->bLeftButtonPressed;
	}

	inline bool UIInputEvent::rightButtonPressed() const
	{
		return this->bRightButtonPressed;
	}

	inline bool UIInputEvent::middleButtonPressed() const
	{
		return this->bMiddleButtonPressed;
	}

	inline bool UIInputEvent::altKeyPressed() const
	{
		return this->bLAltKeyPressed || this->bRAltKeyPressed;
	}

	inline bool UIInputEvent::leftAltKeyPressed() const
	{
		return this->bLAltKeyPressed;
	}

	inline bool UIInputEvent::rightAltKeyPressed() const
	{
		return this->bLAltKeyPressed;
	}

	inline bool UIInputEvent::shiftKeyPressed() const
	{
		return this->bLShiftKeyPressed || this->bRShiftKeyPressed;
	}

	inline bool UIInputEvent::leftShiftKeyPressed() const
	{
		return this->bLShiftKeyPressed;
	}

	inline bool UIInputEvent::rightShiftKeyPressed() const
	{
		return this->bRShiftKeyPressed;
	}

	inline bool UIInputEvent::controlKeyPressed() const
	{
		return this->bLControlKeyPressed || this->bRControlKeyPressed;
	}

	inline bool UIInputEvent::leftControlKeyPressed() const
	{
		return this->bLControlKeyPressed;
	}

	inline bool UIInputEvent::rightControlKeyPressed() const
	{
		return this->bRControlKeyPressed;
	}
}

#endif