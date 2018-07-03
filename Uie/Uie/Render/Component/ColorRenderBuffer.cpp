
/*
	2018.05.11
	Created by AcrylicShrimp.
*/

#include "ColorRenderBuffer.h"

namespace Uie::Render::Component
{
	ColorRenderBuffer::ColorRenderBuffer(GLsizei nWidth, GLsizei nHeight, Format eFormat) :
		RenderBuffer(nWidth, nHeight, static_cast<GLenum>(eFormat)),
		eFormat{eFormat}
	{
		//Empty.
	}
}