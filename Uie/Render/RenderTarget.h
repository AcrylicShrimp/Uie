
/*
	2018.05.01
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_UIE_RENDER_RENDERTARGET_H

#define _CLASS_UIE_RENDER_RENDERTARGET_H

#include "../UieDLL.h"

#include <unordered_map>
#include <utility>
#include <GL/glew.h>

namespace Uie::Render
{
	class UIE_DLL RenderTarget final
	{
	public:
		enum class AttachmentType : GLenum
		{
			Color = GL_COLOR_ATTACHMENT0,
			Depth = GL_DEPTH_ATTACHMENT,
			Stencil = GL_STENCIL_ATTACHMENT,
			DepthStencil = GL_DEPTH_STENCIL_ATTACHMENT
		};

	private:
		GLuint nIdentifier;
		
	public:
		RenderTarget();
		RenderTarget(const RenderTarget &sSrc) = delete;
		RenderTarget(RenderTarget &&sSrc);
		~RenderTarget();
		
	public:
		RenderTarget &operator=(const RenderTarget &sSrc) = delete;
		RenderTarget &operator=(RenderTarget &&sSrc);
		
	public:

	};
}

#endif