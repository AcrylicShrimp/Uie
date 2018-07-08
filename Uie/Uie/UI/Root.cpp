
/*
	2018.07.06
	Created by AcrylicShrimp.
*/

#include "Root.h"

#include "Element.h"

namespace Uie::UI
{
	void Root::add(Element *pElement)
	{
		auto iIndex{std::find(this->sRootElementList.cbegin(), this->sRootElementList.cend(), pElement)};

		if (iIndex != this->sRootElementList.cend())
			return;

		this->bNeedReorder = true;
		this->sRootElementList.emplace_back(pElement);
	}

	void Root::clear()
	{
		this->bNeedReorder = true;
		this->sRootElementList.clear();
	}

	void Root::remove(Element *pElement)
	{
		auto iIndex{std::find(this->sRootElementList.cbegin(), this->sRootElementList.cend(), pElement)};

		if (iIndex == this->sRootElementList.cend())
			return;

		this->bNeedReorder = true;
		this->sRootElementList.erase(iIndex);
	}

	void Root::update()
	{
		this->reorderIfNeeded();

		for (auto pElement : this->sElementList)
			pElement->update();
	}

	void Root::render()
	{
		for (auto pElement : this->sElementList)
			pElement->render();
	}

	void Root::reorderIfNeeded()
	{
		if (!this->bNeedReorder)
			return;

		this->sElementList.clear();
		this->sElementList.insert(this->sElementList.cend(), this->sRootElementList.begin(), this->sRootElementList.end());

		std::size_t nIndex{0};
		std::size_t nCount{this->sElementList.size()};

		while (nIndex < nCount)
		{
			for (; nIndex < nCount; ++nIndex)
				this->sElementList[nIndex]->reorder(this->sElementList);

			nCount = this->sRootElementList.size();
		}

		this->bNeedReorder = false;
	}
}