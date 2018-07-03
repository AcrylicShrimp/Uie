
/*
	2018.05.11
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_UIE_RENDER_COMPONENT_STENCILRENDERBUFFER_H

#define _CLASS_UIE_RENDER_COMPONENT_STENCILRENDERBUFFER_H

#include "../../UieDLL.h"

#include "RenderBuffer.h"

#include <GL/glew.h>

namespace Uie::Render::Component
{
	class UIE_DLL StencilRenderBuffer final : public RenderBuffer
	{
	public:
		enum class Format : GLenum
		{
			Auto = GL_STENCIL_INDEX,
			Stencil1 = GL_STENCIL_INDEX1,
			Stencil4 = GL_STENCIL_INDEX4,
			Stencil8 = GL_STENCIL_INDEX8,
			Stencil16 = GL_STENCIL_INDEX16,
		};

	protected:
		Format eFormat;
		
	public:
		StencilRenderBuffer(GLsizei nWidth, GLsizei nHeight, Format eFormat);
		StencilRenderBuffer(const StencilRenderBuffer &sSrc) = delete;
		StencilRenderBuffer(StencilRenderBuffer &&sSrc) = default;
		~StencilRenderBuffer() = default;
		
	public:
		StencilRenderBuffer &operator=(const StencilRenderBuffer &sSrc) = delete;
		StencilRenderBuffer &operator=(StencilRenderBuffer &&sSrc) = default;
		
	public:
		inline Format format() const;
	};

	inline StencilRenderBuffer::Format StencilRenderBuffer::format() const
	{
		return this->eFormat;
	}
}

#endif