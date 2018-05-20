
/*
	2018.05.18
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_UIE_RENDER_CONTEXTOBJECT_H

#define _CLASS_UIE_RENDER_CONTEXTOBJECT_H

#include "../UieDLL.h"

#include "Context.h"

#include <exception>

namespace Uie::Render
{
	class UIE_DLL ContextObject
	{
	protected:
		Context *pContext;
		
	public:
		ContextObject();
		ContextObject(const ContextObject &sSrc) = default;
		virtual ~ContextObject() = default;
		
	public:
		ContextObject &operator=(const ContextObject &sSrc) = default;
		
	public:
		inline Context *context();
		inline const Context *context() const;
	};

	inline Context *ContextObject::context()
	{
		return this->pContext;
	}

	inline const Context *ContextObject::context() const
	{
		return this->pContext;
	}
}

#endif