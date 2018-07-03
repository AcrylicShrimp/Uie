
/*
	2018.05.23
	Created by AcrylicShrimp.
*/

#include "UIGridLayout.h"

namespace Uie::Component
{
	UIGridLayout::UIGridLayout(UIPlacement *pPlacement, const std::wstring &sName, float nMargin, float nPadding, std::uint32_t nRow, std::uint32_t nColumn) :
		UILayout(pPlacement, sName)
	{
		//Empty.
	}
	
	void UIGridLayout::updateChild(UIElement *pChild, GridLayoutProperties &tLayoutProperties)
	{

	}
}