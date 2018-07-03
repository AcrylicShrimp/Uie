
/*
	2018.05.11
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_UIE_RENDER_COMPONENT_DEPTHSTENCILRENDERBUFFER_H

#define _CLASS_UIE_RENDER_COMPONENT_DEPTHSTENCILRENDERBUFFER_H

#include "../../UieDLL.h"

#include "RenderBuffer.h"

#include <GL/glew.h>

namespace Uie::Render::Component
{
	class UIE_DLL DepthStencilRenderBuffer final : public RenderBuffer
	{
	public:
		enum class Format : GLenum
		{
			Auto = GL_DEPTH_STENCIL,
			DepthStencil248 = GL_DEPTH24_STENCIL8,
			DepthStencil32F8 = GL_DEPTH32F_STENCIL8,
		};

	protected:
		Format eFormat;
		
	public:
		DepthStencilRenderBuffer(GLsizei nWidth, GLsizei nHeight, Format eFormat);
		DepthStencilRenderBuffer(const DepthStencilRenderBuffer &sSrc) = delete;
		DepthStencilRenderBuffer(DepthStencilRenderBuffer &&sSrc) = default;
		~DepthStencilRenderBuffer() = default;
		
	public:
		DepthStencilRenderBuffer &operator=(const DepthStencilRenderBuffer &sSrc) = delete;
		DepthStencilRenderBuffer &operator=(DepthStencilRenderBuffer &&sSrc) = default;
		
	public:
		inline Format format() const;
	};

	inline DepthStencilRenderBuffer::Format DepthStencilRenderBuffer::format() const
	{
		return this->eFormat;
	}
}

#endif