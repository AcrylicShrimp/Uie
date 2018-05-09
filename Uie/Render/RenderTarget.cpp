
/*
	2018.05.01
	Created by AcrylicShrimp.
*/

#include "RenderTarget.h"

namespace Uie::Render
{
	RenderTarget::RenderTarget()
	{

	}
	
	RenderTarget::RenderTarget(RenderTarget &&sSrc)
	{

	}
	
	RenderTarget::~RenderTarget()
	{

	}
	
	RenderTarget &RenderTarget::operator=(RenderTarget &&sSrc)
	{
		if (&sSrc == this)
			return *this;


		
		return *this;
	}
}