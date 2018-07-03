
/*
	2018.04.08
	Created by AcrylicShrimp.
*/

#include "UICanvasLayout.h"

namespace Uie::Component
{
	UICanvasLayout::UICanvasLayout(UIPlacement *pPlacement, const std::wstring &sName) :
		UILayout(pPlacement, sName)
	{
		//Empty.
	}

	void UICanvasLayout::updateChild(UIElement *pChild, CanvasLayoutProperties &tLayoutProperties)
	{
		pChild->rect().setXYWH(tLayoutProperties.nX, tLayoutProperties.nY, tLayoutProperties.nWidth, tLayoutProperties.nHeight);
	}
}