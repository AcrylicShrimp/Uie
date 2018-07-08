
/*
	2018.07.06
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_UIE_UI_ROOT_H

#define _CLASS_UIE_UI_ROOT_H

#include "../UieDLL.h"

#include <algorithm>
#include <cstddef>
#include <vector>

namespace Uie::UI
{
	class Element;

	class UIE_DLL Root final
	{
	public:
		using It = std::vector<Element *>::iterator;
		using ConstIt = std::vector<Element *>::const_iterator;
		using ItRev = std::vector<Element *>::reverse_iterator;
		using ConstItRev = std::vector<Element *>::const_reverse_iterator;

	private:
		bool bNeedReorder{true};
		std::vector<Element *> sElementList;
		std::vector<Element *> sRootElementList;
		
	public:
		Root() = default;
		Root(const Root &sSrc) = default;
		Root(Root &&sSrc) = default;
		~Root() = default;
		
	public:
		Root &operator=(const Root &sSrc) = default;
		Root &operator=(Root &&sSrc) = default;
		
	public:
		inline void reorder();
		inline It begin();
		inline ConstIt begin() const;
		inline It end();
		inline ConstIt end() const;
		inline ItRev rbegin();
		inline ConstItRev rbegin() const;
		inline ItRev rend();
		inline ConstItRev rend() const;
		void add(Element *pElement);
		void clear();
		void remove(Element *pElement);
		void update();
		void render();
		void reorderIfNeeded();
	};

	inline void Root::reorder()
	{
		this->bNeedReorder = true;
	}

	inline Root::It Root::begin()
	{
		return this->sElementList.begin();
	}

	inline Root::ConstIt Root::begin() const
	{
		return this->sElementList.cbegin();
	}

	inline Root::It Root::end()
	{
		return this->sElementList.end();
	}

	inline Root::ConstIt Root::end() const
	{
		return this->sElementList.cend();
	}

	inline Root::ItRev Root::rbegin()
	{
		return this->sElementList.rbegin();
	}

	inline Root::ConstItRev Root::rbegin() const
	{
		return this->sElementList.crbegin();
	}

	inline Root::ItRev Root::rend()
	{
		return this->sElementList.rend();
	}

	inline Root::ConstItRev Root::rend() const
	{
		return this->sElementList.crend();
	}
}

#endif