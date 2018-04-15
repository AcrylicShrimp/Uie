
/*
	2018.04.06
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_UIE_COMPONENT_UILAYOUT_H

#define _CLASS_UIE_COMPONENT_UILAYOUT_H

#include "../UIElement.h"
#include "../UIPlacement.h"

#include <algorithm>
#include <memory>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

namespace Uie::Component
{
	template<class T> class UILayout : public UIElement
	{
	protected:
		std::vector<std::tuple<UIElement *, std::unique_ptr<T>>> sChildList;

	public:
		UILayout(UIPlacement *pPlacement, const std::wstring &sName);
		UILayout(const UILayout &sSrc) = delete;
		~UILayout() = default;

	public:
		UILayout &operator=(const UILayout &sSrc) = delete;

	public:
		T *addChild(UIElement *pChild);
		void addChild(UIElement *pChild, const T &tLayoutProperties);
		void removeChild(UIElement *pChild);
		T *obtainLayoutProperties(UIElement *pChild);
		const T *obtainLayoutProperties(UIElement *pChild) const;
		virtual void update() override;

	protected:
		virtual void updateChild(UIElement *pChild, T &tLayoutProperties) = 0;
	};
}

#include "UILayout.hpp"

#endif