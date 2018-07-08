
/*
	2018.07.07
	Created by AcrylicShrimp.
*/

#include "Hierarchy.h"

namespace Uie::UI
{
	Hierarchy::Hierarchy(Root *pRoot, const std::string &sName) :
		Element(pRoot, sName)
	{
		//Empty.
	}

	void Hierarchy::addChild(Element *pChild)
	{
		if (pChild->root() != this->pRoot)
			return;

		this->pRoot->reorder();
		this->pRoot->remove(pChild);
		this->sChildList.emplace_back(pChild);
	}

	void Hierarchy::clearChild()
	{
		for (auto pChild : this->sChildList)
			this->pRoot->add(pChild);

		this->pRoot->reorder();
		this->sChildList.clear();
	}

	void Hierarchy::removeChild(Element *pChild)
	{
		const auto iIndex{std::find(this->sChildList.cbegin(), this->sChildList.cend(), pChild)};

		if (iIndex == this->sChildList.cend())
			return;

		this->pRoot->reorder();
		this->pRoot->add(pChild);
		this->sChildList.erase(iIndex);
	}

	void Hierarchy::reorder(std::vector<Element *> &sElementList)
	{
		for (auto pChild : this->sChildList)
			sElementList.emplace_back(pChild);
	}

	void Hierarchy::update()
	{
		for (auto pChild : this->sChildList)
			pChild->update();
	}

	void Hierarchy::render()
	{
		for (auto pChild : this->sChildList)
			pChild->render();
	}
}