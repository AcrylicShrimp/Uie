
/*
	2018.07.07
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_UIE_UI_HIERARCHY_H

#define _CLASS_UIE_UI_HIERARCHY_H

#include "../UieDLL.h"

#include "Element.h"
#include "Root.h"

#include <algorithm>
#include <cstddef>
#include <string>
#include <vector>

namespace Uie::UI
{
	class UIE_DLL Hierarchy : public Element
	{
	protected:
		std::vector<Element *> sChildList;
		
	public:
		Hierarchy(Root *pRoot, const std::string &sName);
		Hierarchy(const Hierarchy &sSrc) = delete;
		~Hierarchy() = default;
		
	public:
		Hierarchy &operator=(const Hierarchy &sSrc) = delete;
		
	public:
		inline std::size_t childCount() const;
		virtual void addChild(Element *pChild);
		virtual void clearChild();
		virtual void removeChild(Element *pChild);
		virtual void reorder(std::vector<Element *> &sElementList) override;
		virtual void update() override;
		virtual void render() override;
	};

	inline std::size_t Hierarchy::childCount() const
	{
		return this->sChildList.size();
	}
}

#endif