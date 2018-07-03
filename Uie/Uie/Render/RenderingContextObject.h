
/*
	2018.07.02
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_UIE_RENDER_RENDERINGCONTEXTOBJECT_H

#define _CLASS_UIE_RENDER_RENDERINGCONTEXTOBJECT_H

#include "../UieDLL.h"

#include "RenderingContext.h"

namespace Uie::Render
{
	class UIE_DLL RenderingContextObject
	{
	protected:
		RenderingContext *pRenderingContext;
		
	public:
		RenderingContextObject();
		RenderingContextObject(const RenderingContextObject &sSrc) = default;
		virtual ~RenderingContextObject() = default;
		
	public:
		RenderingContextObject &operator=(const RenderingContextObject &sSrc) = default;
		
	public:
		inline RenderingContext *renderingContext();
		inline const RenderingContext *renderingContext() const;
	};

	inline RenderingContext *RenderingContextObject::renderingContext()
	{
		return this->pRenderingContext;
	}

	inline const RenderingContext *RenderingContextObject::renderingContext() const
	{
		return this->pRenderingContext;
	}
}

#endif