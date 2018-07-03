
/*
	2018.04.08
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_UIE_COMPONENT_UICANVASLAYOUT_H

#define _CLASS_UIE_COMPONENT_UICANVASLAYOUT_H

#include "../UieDLL.h"

#include "UILayout.h"

#include <string>

namespace Uie::Component
{
	struct UIE_DLL CanvasLayoutProperties
	{
		float nX;
		float nY;
		float nWidth;
		float nHeight;
	};

	class UIE_DLL UICanvasLayout : public UILayout<CanvasLayoutProperties>
	{
	public:
		UICanvasLayout(UIPlacement *pPlacement, const std::wstring &sName);
		UICanvasLayout(const UICanvasLayout &sSrc) = delete;
		~UICanvasLayout() = default;
		
	public:
		UICanvasLayout &operator=(const UICanvasLayout &sSrc) = delete;
		
	public:
		virtual void updateChild(UIElement *pChild, CanvasLayoutProperties &tLayoutProperties) override;
	};
}

#endif