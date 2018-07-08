
/*
	2018.04.08
	Created by AcrylicShrimp.
*/

#include "UICanvasLayout.h"

namespace Uie::UI::Component
{
	UICanvasLayout::UICanvasLayout(Root *pRoot, const std::string &sName) :
		Layout(pRoot, sName)
	{
		//Empty.
	}

	void UICanvasLayout::updateChild(Element *pChild, CanvasLayoutProperties &tLayoutProperties)
	{
		pChild->rect().setXYWH(tLayoutProperties.nX, tLayoutProperties.nY, tLayoutProperties.nWidth, tLayoutProperties.nHeight);
	}
}