
/*
	2018.04.05
	Created by AcrylicShrimp.
*/

#include "UIElement.h"

#include "UIPlacement.h"

namespace Uie
{
	UIElement::UIElement(UIPlacement *pPlacement, const std::wstring &sName) :
		pPlacement{pPlacement},
		nOrder{0},
		sName{sName}
	{
		//Empty.
	}

	void UIElement::update()
	{
		//Empty.
	}

	void UIElement::render()
	{
		//Empty.
	}

	void UIElement::specifyOrder(std::int64_t nOrder)
	{
		this->pPlacement->changeOrder(this, nOrder);
	}
}