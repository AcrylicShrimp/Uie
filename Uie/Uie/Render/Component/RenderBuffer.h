
/*
	2018.05.01
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_UIE_RENDER_COMPONENT_RENDERBUFFER_H

#define _CLASS_UIE_RENDER_COMPONENT_RENDERBUFFER_H

#include "../../UieDLL.h"

#include "Renderable.h"

#include <utility>
#include <GL/glew.h>

namespace Uie::Render::Component
{
	class UIE_DLL RenderBuffer : public Renderable
	{
	protected:
		GLuint nIdentifier;
		GLsizei nWidth;
		GLsizei nHeight;
		
	public:
		RenderBuffer(GLsizei nWidth, GLsizei nHeight, GLenum nType);
		RenderBuffer(const RenderBuffer &sSrc) = delete;
		RenderBuffer(RenderBuffer &&sSrc);
		~RenderBuffer();
		
	public:
		RenderBuffer &operator=(const RenderBuffer &sSrc) = delete;
		RenderBuffer &operator=(RenderBuffer &&sSrc);
		
	protected:
		virtual GLuint identifier() const override;
		virtual GLsizei width() const override;
		virtual GLsizei height() const override;
		virtual bool texture() const override;
	};
}

#endif