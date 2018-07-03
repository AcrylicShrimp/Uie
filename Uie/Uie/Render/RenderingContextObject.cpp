
/*
	2018.07.02
	Created by AcrylicShrimp.
*/

#include "RenderingContextObject.h"

namespace Uie::Render
{
	RenderingContextObject::RenderingContextObject() :
		pRenderingContext{RenderingContext::current()}
	{
		//Empty.
	}
}