
/*
	2018.04.15
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_UIE_EVENT_UITYPEEVENT_H

#define _CLASS_UIE_EVENT_UITYPEEVENT_H

#include "../UieDLL.h"

#include <string>

namespace Uie::Event
{
	class UIE_DLL UITypeEvent
	{
	public:
		enum class State
		{
			Composed,
			Composing,
			ComposingCanceled
		};

	private:
		State eState;
		std::wstring sString;
		
	public:
		UITypeEvent(State eState, const std::wstring &sString);
		UITypeEvent(const UITypeEvent &sSrc) = default;
		~UITypeEvent() = default;
		
	public:
		UITypeEvent &operator=(const UITypeEvent &sSrc) = default;
		
	public:
		inline State state() const;
		inline const std::wstring &string() const;
	};

	inline UITypeEvent::State UITypeEvent::state() const
	{
		return this->eState;
	}

	inline const std::wstring &UITypeEvent::string() const
	{
		return this->sString;
	}
}

#endif