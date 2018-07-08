
/*
	2018.04.05
	Created by AcrylicShrimp.
*/

#include "Element.h"

namespace Uie::UI
{
	Element::Element(Root *pRoot, const std::string &sName) :
		pRoot{pRoot},
		sName{sName}
	{
		this->pRoot->add(this);
	}

	void Element::reorder(std::vector<Element *> &sElementList)
	{
		//Empty.
	}

	void Element::update()
	{
		//Empty.
	}

	void Element::render()
	{
		//Empty.
	}
}