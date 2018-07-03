
/*
	2018.05.11
	Created by AcrylicShrimp.
*/

#include "StencilRenderBuffer.h"

namespace Uie::Render::Component
{
	StencilRenderBuffer::StencilRenderBuffer(GLsizei nWidth, GLsizei nHeight, Format eFormat) :
		RenderBuffer(nWidth, nHeight, static_cast<GLenum>(eFormat)),
		eFormat{eFormat}
	{
		//Empty.
	}
}