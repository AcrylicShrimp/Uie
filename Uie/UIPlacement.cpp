
/*
	2018.04.08
	Created by AcrylicShrimp.
*/

#include "UIPlacement.h"

namespace Uie
{
	UIElement *UIPlacement::find(const std::wstring &sName) const
	{
		auto iIndex{this->sElementMap.find(sName)};
		return iIndex == this->sElementMap.cend() ? nullptr : iIndex->second.get();
	}

	void UIPlacement::deinstantiate(const std::wstring &sName)
	{
		auto pElement{this->find(sName)};

		if (!pElement)
			return;

		auto &sOrderList{this->sElementOrderMap[pElement->order()]};
		auto iIndex{std::find(sOrderList.cbegin(), sOrderList.cend(), pElement)};

		if (iIndex != sOrderList.cend())
			sOrderList.erase(iIndex);

		this->sRootElementSet.erase(pElement);
		this->sElementMap.erase(sName);
	}

	void UIPlacement::deinstantiateAll()
	{
		this->sElementMap.clear();
		this->sElementOrderMap.clear();
		this->sRootElementSet.clear();
	}

	void UIPlacement::rootElement(UIElement *pElement)
	{
		this->sRootElementSet.emplace(pElement);
	}

	void UIPlacement::unrootElement(UIElement *pElement)
	{
		this->sRootElementSet.erase(pElement);
	}

	void UIPlacement::changeOrder(UIElement *pElement, int64_t nOrder)
	{
		auto &sOrderList{this->sElementOrderMap[pElement->order()]};
		auto iIndex{std::find(sOrderList.cbegin(), sOrderList.cend(), pElement)};

		if (iIndex != sOrderList.cend())
			sOrderList.erase(iIndex);

		this->sElementOrderMap[nOrder].emplace_back(pElement);
	}

	void UIPlacement::iterateAll(IterationOrder eIterateOrder, std::function<bool(UIElement *)> fIterateFunc)
	{
		if (eIterateOrder == IterationOrder::FrontToBack)
		{
			for (auto iMapIndex{this->sElementOrderMap.rbegin()}, iMapEnd{this->sElementOrderMap.rend()}; iMapIndex != iMapEnd; ++iMapIndex)
				for (auto iIndex{iMapIndex->second.rbegin()}, iEnd{iMapIndex->second.rend()}; iIndex != iEnd; ++iIndex)
					if (fIterateFunc(*iIndex))
						return;
		}
		else
		{
			for (auto &sPair : this->sElementOrderMap)
				for (auto pElement : sPair.second)
					if (fIterateFunc(pElement))
						return;
		}
	}

	void UIPlacement::renderAll()
	{
		for (auto &sPair : this->sElementOrderMap)
			for (auto pElement : sPair.second)
				pElement->render();
	}

	void UIPlacement::updateAll()
	{
		for (auto pElement : this->sRootElementSet)
		{
			pElement->rect().set(-1.f, 1.f);
			pElement->update();
		}
	}
}