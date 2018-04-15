
/*
	2018.04.08
	Created by AcrylicShrimp.
*/

#include "UIManager.h"

namespace Uie
{
	void UIManager::deinstantiateAll()
	{
		this->sPlacementMap.clear();
	}

	void UIManager::deinstantiate(const std::wstring &sName)
	{
		this->sPlacementMap.erase(sName);
	}

	UIPlacement *UIManager::instantiate(const std::wstring &sName)
	{
		auto pPlacement{this->find(sName)};

		if (pPlacement)
			return pPlacement;

		return this->sPlacementMap.emplace(sName, new UIPlacement()).first->second.get();
	}

	UIPlacement *UIManager::find(const std::wstring &sName)
	{
		auto iIndex{this->sPlacementMap.find(sName)};
		return iIndex == this->sPlacementMap.cend() ? nullptr : iIndex->second.get();
	}
}