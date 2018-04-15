
/*
	2018.04.08
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_UIE_UIMANAGER_H

#define _CLASS_UIE_UIMANAGER_H

#include "UieDLL.h"

#include "ManagerBase.h"
#include "UIPlacement.h"

#include <memory>
#include <string>
#include <unordered_map>
#include <utility>

namespace Uie
{
	class UIE_DLL UIManager final : public ManagerBase<UIManager>
	{
	private:
		std::unordered_map<std::wstring, std::unique_ptr<UIPlacement>> sPlacementMap;
		
	public:
		UIManager() = default;
		UIManager(const UIManager &sSrc) = delete;
		~UIManager() = default;
		
	public:
		UIManager &operator=(const UIManager &sSrc) = delete;
		
	public:
		void deinstantiateAll();
		void deinstantiate(const std::wstring &sName);
		UIPlacement *instantiate(const std::wstring &sName);
		UIPlacement *find(const std::wstring &sName);
	};
}

#endif