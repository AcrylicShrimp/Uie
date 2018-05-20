
/*
	2018.05.11
	Created by AcrylicShrimp.
*/

#include "DepthStencilRenderBuffer.h"

namespace Uie::Render
{
	DepthStencilRenderBuffer::DepthStencilRenderBuffer(GLsizei nWidth, GLsizei nHeight, Format eFormat) :
		RenderBuffer(nWidth, nHeight, static_cast<GLenum>(eFormat)),
		eFormat{eFormat}
	{
		//Empty.
	}
}