
/*
	2018.05.23
	Created by AcrylicShrimp.
*/

#include "UIGridLayout.h"

namespace Uie::UI::Component
{
	UIGridLayout::UIGridLayout(Root *pRoot, const std::string &sName, float nMargin, float nPadding, std::uint32_t nRow, std::uint32_t nColumn) :
		Layout(pRoot, sName)
	{
		//Empty.
	}
	
	void UIGridLayout::updateChild(Element *pChild, GridLayoutProperties &tLayoutProperties)
	{

	}
}