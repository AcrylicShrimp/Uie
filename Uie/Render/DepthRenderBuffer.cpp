
/*
	2018.05.10
	Created by AcrylicShrimp.
*/

#include "DepthRenderBuffer.h"

namespace Uie::Render
{
	DepthRenderBuffer::DepthRenderBuffer(GLsizei nWidth, GLsizei nHeight, Format eFormat) :
		RenderBuffer(nWidth, nHeight, static_cast<GLenum>(eFormat)),
		eFormat{eFormat}
	{
		//Empty.
	}
}