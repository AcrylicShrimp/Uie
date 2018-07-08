
/*
	2018.04.05
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_UIE_UI_ELEMENT_H

#define _CLASS_UIE_UI_ELEMENT_H

#include "../UieDLL.h"

#include "Root.h"
#include "../Event/EventHandler.h"
#include "../Event/RaycastTarget.h"

#include <string>
#include <vector>

namespace Uie::UI
{
	class UIE_DLL Element : public Event::EventHandler, public Event::RaycastTarget
	{
	protected:
		Root *pRoot;
		const std::string sName;

	public:
		Element(Root *pRoot, const std::string &sName);
		Element(const Element &sSrc) = delete;
		virtual ~Element() = default;

	public:
		Element &operator=(const Element &sSrc) = delete;

	public:
		inline Root *root();
		inline const Root *root() const;
		inline const std::string &name() const;
		virtual void reorder(std::vector<Element *> &sElementList);
		virtual void update();
		virtual void render();
	};

	inline Root *Element::root()
	{
		return this->pRoot;
	}

	inline const Root *Element::root() const
	{
		return this->pRoot;
	}

	inline const std::string &Element::name() const
	{
		return this->sName;
	}
}

#endif