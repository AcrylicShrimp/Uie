
/*
	2018.04.08
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_UIE_UIPLACEMENT_H

#define _CLASS_UIE_UIPLACEMENT_H

#include "UieDLL.h"

#include "UIElement.h"

#include <algorithm>
#include <cstdint>
#include <functional>
#include <map>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

namespace Uie
{
	class UIE_DLL UIPlacement final
	{
	public:
		enum class IterateOrder
		{
			FrontToBack,
			BackToFront
		};

	private:
		std::unordered_map<std::wstring, std::unique_ptr<UIElement>> sElementMap;
		std::map<std::int64_t, std::vector<UIElement *>> sElementOrderMap;
		std::unordered_set<UIElement *> sRootElementSet;
		
	public:
		UIPlacement() = default;
		UIPlacement(const UIPlacement &sSrc) = delete;
		~UIPlacement() = default;
		
	public:
		UIPlacement &operator=(const UIPlacement &sSrc) = delete;
		
	public:
		template<class T, class ...P> T *instantiate(P &&...tParam);
		template<class T> T *find(const std::wstring &sName) const;
		UIElement *find(const std::wstring &sName) const;
		void deinstantiate(const std::wstring &sName);
		void deinstantiateAll();
		void rootElement(UIElement *pElement);
		void unrootElement(UIElement *pElement);
		void changeOrder(UIElement *pElement, int64_t nOrder);
		void iterateAll(IterateOrder eIterateOrder, std::function<bool(UIElement *)> fIterateFunc);
		void renderAll();
		void updateAll();
	};

	template<class T, class ...P> T *UIPlacement::instantiate(P &&...tParam)
	{
		auto pElement{new T(this, std::forward<P>(tParam)...)};

		this->sElementMap.emplace(pElement->name(), pElement);
		this->sElementOrderMap[pElement->order()].emplace_back(pElement);
		this->sRootElementSet.emplace(pElement);
		
		return pElement;
	}

	template<class T> T *UIPlacement::find(const std::wstring &sName) const
	{
		auto iIndex{this->sElementMap.find(sName)};
		return iIndex == this->sElementMap.cend() ? nullptr : static_cast<T *>(iIndex->second.get());
	}
}

#endif