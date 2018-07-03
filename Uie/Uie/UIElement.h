
/*
	2018.04.05
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_UIE_UIELEMENT_H

#define _CLASS_UIE_UIELEMENT_H

#include "UieDLL.h"

#include "Rect.h"
#include "Event/UIEvents.h"
#include "UIEventHandler.h"

#include <cstdint>
#include <string>

namespace Uie
{
	class UIPlacement;

	class UIE_DLL UIElement : public UIEventHandler
	{
	protected:
		UIPlacement *pPlacement;
		std::int64_t nOrder;
		std::wstring sName;
		Rect sRect;

	public:
		UIElement(UIPlacement *pPlacement, const std::wstring &sName);
		UIElement(const UIElement &sSrc) = delete;
		virtual ~UIElement() = default;

	public:
		UIElement &operator=(const UIElement &sSrc) = delete;

	public:
		inline UIPlacement *placement() const;
		inline std::int64_t order() const;
		inline const std::wstring &name() const;
		inline Rect &rect();
		inline const Rect &rect() const;
		virtual void update();
		virtual void render();
		void specifyOrder(std::int64_t nOrder);
	};

	inline UIPlacement *UIElement::placement() const
	{
		return this->pPlacement;
	}

	inline std::int64_t UIElement::order() const
	{
		return this->nOrder;
	}

	inline const std::wstring &UIElement::name() const
	{
		return this->sName;
	}

	inline Rect &UIElement::rect()
	{
		return this->sRect;
	}

	inline const Rect &UIElement::rect() const
	{
		return this->sRect;
	}
}

#endif