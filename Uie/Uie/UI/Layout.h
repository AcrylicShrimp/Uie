
/*
	2018.07.06
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_UIE_UI_LAYOUT_H

#define _CLASS_UIE_UI_LAYOUT_H

#include "Hierarchy.h"
#include "Root.h"

#include <algorithm>
#include <cstddef>
#include <iterator>
#include <string>
#include <vector>

namespace Uie::UI
{
	template<class T> class Layout : public Hierarchy
	{
	protected:
		std::vector<T> sPropertiesList;

	public:
		Layout(Root *pRoot, const std::string &sName);
		Layout(const Layout &sSrc) = delete;
		~Layout() = default;

	public:
		Layout &operator=(const Layout &sSrc) = delete;

	public:
		inline T *properties(Element *pChild);
		inline const T *properties(Element *pChild) const;
		virtual void addChild(Element *pChild) override;
		virtual void clearChild() override;
		virtual void removeChild(Element *pChild) override;
		virtual void update() override;
		virtual void render() override;

	protected:
		virtual void updateChild(Element *pChild, T &tProperties) = 0;
	};

	template<class T> inline T *Layout<T>::properties(Element *pChild)
	{
		auto iIndex{std::find(this->sChildList.begin(), this->sChildList.end(), pChild)};

		return iIndex == this->sChildList.cend() ? nullptr : &this->sPropertiesList[std::distance(this->sChildList.begin(), iIndex)];
	}

	template<class T> inline const T *Layout<T>::properties(Element *pChild) const
	{
		auto iIndex{std::find(this->sChildList.cbegin(), this->sChildList.cend(), pChild)};

		return iIndex == this->sChildList.cend() ? nullptr : &this->sPropertiesList[std::distance(this->sChildList.cbegin(), iIndex)];
	}
}

#include "Layout.hpp"

#endif