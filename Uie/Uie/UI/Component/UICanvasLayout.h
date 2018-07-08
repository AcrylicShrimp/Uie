
/*
	2018.04.08
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_UIE_UI_COMPONENT_UICANVASLAYOUT_H

#define _CLASS_UIE_UI_COMPONENT_UICANVASLAYOUT_H

#include "../../UieDLL.h"

#include "../Layout.h"
#include "../Root.h"

#include <string>

namespace Uie::UI::Component
{
	struct UIE_DLL CanvasLayoutProperties
	{
		float nX;
		float nY;
		float nWidth;
		float nHeight;
	};

	class UIE_DLL UICanvasLayout : public Layout<CanvasLayoutProperties>
	{
	public:
		UICanvasLayout(Root *pRoot, const std::string &sName);
		UICanvasLayout(const UICanvasLayout &sSrc) = delete;
		~UICanvasLayout() = default;
		
	public:
		UICanvasLayout &operator=(const UICanvasLayout &sSrc) = delete;
		
	public:
		virtual void updateChild(Element *pChild, CanvasLayoutProperties &tLayoutProperties) override;
	};
}

#endif