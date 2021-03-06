
/*
	2018.05.23
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_UIE_UI_COMPONENT_UIGRIDLAYOUT_H

#define _CLASS_UIE_UI_COMPONENT_UIGRIDLAYOUT_H

#include "../../UieDLL.h"

#include "../Layout.h"
#include "../Root.h"

#include <string>

namespace Uie::UI::Component
{
	struct UIE_DLL GridLayoutProperties
	{
		std::uint32_t nHorizontalPosition;
		std::uint32_t nVerticalPosition;
	};

	class UIE_DLL UIGridLayout : public Layout<GridLayoutProperties>
	{
	protected:
		float nMargin;
		float nPadding;
		std::uint32_t nRow;
		std::uint32_t nColumn;

	public:
		UIGridLayout(Root *pRoot, const std::string &sName, float nMargin, float nPadding, std::uint32_t nRow, std::uint32_t nColumn);
		UIGridLayout(const UIGridLayout &sSrc) = delete;
		~UIGridLayout() = default;
		
	public:
		inline float margin() const;
		inline float padding() const;
		inline std::uint32_t row() const;
		inline std::uint32_t column() const;
		UIGridLayout &operator=(const UIGridLayout &sSrc) = delete;
		
	public:
		virtual void updateChild(Element *pChild, GridLayoutProperties &tLayoutProperties) override;
	};

	inline float UIGridLayout::margin() const
	{
		return this->nMargin;
	}

	inline float UIGridLayout::padding() const
	{
		return this->nPadding;
	}

	inline std::uint32_t UIGridLayout::row() const
	{
		return this->nRow;
	}

	inline std::uint32_t UIGridLayout::column() const
	{
		return this->nColumn;
	}
}

#endif