
/*
	2018.05.18
	Created by AcrylicShrimp.
*/

#include "ContextObject.h"

namespace Uie::Render
{
	ContextObject::ContextObject() :
		pContext{Context::obtainContext()}
	{
		if (!pContext)
			throw new std::exception("context is required");
	}
}