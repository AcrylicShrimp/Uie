
/*
	2018.05.10
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_UIE_RENDER_DEPTHRENDERBUFFER_H

#define _CLASS_UIE_RENDER_DEPTHRENDERBUFFER_H

#include "../UieDLL.h"

#include "RenderBuffer.h"

#include <GL/glew.h>

namespace Uie::Render
{
	class UIE_DLL DepthRenderBuffer final : public RenderBuffer
	{
	public:
		enum class Format : GLenum
		{
			Auto = GL_DEPTH_COMPONENT,
			Depth16 = GL_DEPTH_COMPONENT16,
			Depth24 = GL_DEPTH_COMPONENT24,
			Depth32 = GL_DEPTH_COMPONENT32,
			Depth32F = GL_DEPTH_COMPONENT32F
		};

	protected:
		Format eFormat;

	public:
		DepthRenderBuffer(GLsizei nWidth, GLsizei nHeight, Format eFormat);
		DepthRenderBuffer(const DepthRenderBuffer &sSrc) = delete;
		DepthRenderBuffer(DepthRenderBuffer &&sSrc) = default;
		~DepthRenderBuffer() = default;
		
	public:
		DepthRenderBuffer &operator=(const DepthRenderBuffer &sSrc) = delete;
		DepthRenderBuffer &operator=(DepthRenderBuffer &&sSrc) = default;

	public:
		inline Format format() const;
	};

	inline DepthRenderBuffer::Format DepthRenderBuffer::format() const
	{
		return this->eFormat;
	}
}

#endif