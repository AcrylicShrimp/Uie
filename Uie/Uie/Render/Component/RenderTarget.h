
/*
	2018.05.01
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_UIE_RENDER_COMPONENT_RENDERTARGET_H

#define _CLASS_UIE_RENDER_COMPONENT_RENDERTARGET_H

#include "../../UieDLL.h"

#include "../RenderingContext.h"
#include "Renderable.h"

#include <cstdint>
#include <initializer_list>
#include <unordered_map>
#include <utility>
#include <vector>
#include <GL/glew.h>

namespace Uie::Render::Component
{
	class UIE_DLL RenderTarget final
	{
	public:
		enum class Target : GLenum
		{
			None = GL_NONE,
			Color = GL_COLOR_ATTACHMENT0,
			Color0 = GL_COLOR_ATTACHMENT0,
			Color1 = GL_COLOR_ATTACHMENT1,
			Color2 = GL_COLOR_ATTACHMENT2,
			Color3 = GL_COLOR_ATTACHMENT3,
			Color4 = GL_COLOR_ATTACHMENT4,
			Color5 = GL_COLOR_ATTACHMENT5,
			Color6 = GL_COLOR_ATTACHMENT6,
			Color7 = GL_COLOR_ATTACHMENT7,
			Color8 = GL_COLOR_ATTACHMENT8,
			Color9 = GL_COLOR_ATTACHMENT9,
			Color10 = GL_COLOR_ATTACHMENT10,
			Color11 = GL_COLOR_ATTACHMENT11,
			Color12 = GL_COLOR_ATTACHMENT12,
			Color13 = GL_COLOR_ATTACHMENT13,
			Color14 = GL_COLOR_ATTACHMENT14,
			Color15 = GL_COLOR_ATTACHMENT15
		};

		enum class DefaultTarget : GLenum
		{
			None = GL_NONE,
			Front = GL_FRONT_LEFT,
			Back = GL_BACK_LEFT
		};

	private:
		GLuint nIdentifier;
		Renderable *pRenderableDepth;
		Renderable *pRenderableStencil;
		std::unordered_map<GLuint, Renderable *> sRenderableColorMap;
		
	public:
		RenderTarget();
		RenderTarget(const RenderTarget &sSrc) = delete;
		RenderTarget(RenderTarget &&sSrc);
		~RenderTarget();
		
	public:
		RenderTarget &operator=(const RenderTarget &sSrc) = delete;
		RenderTarget &operator=(RenderTarget &&sSrc);
		
	public:
		inline GLsizei width() const;
		inline GLsizei height() const;
		inline Renderable *depth();
		inline const Renderable *depth() const;
		inline Renderable *stencil();
		inline const Renderable *stencil() const;
		inline Renderable *color(GLuint nIndex);
		inline const Renderable *color(GLuint nIndex) const;
		void depth(Renderable *pRenderableDepth);
		void stencil(Renderable *pRenderableStencil);
		void depthStencil(Renderable *pRenderableDepthStencil);
		void color(GLuint nIndex, Renderable *pRenderableColor);
		void use(std::initializer_list<Target> sTargetList);
		static void useDefault(std::initializer_list<DefaultTarget> sTargetList);
	};

	inline GLsizei RenderTarget::width() const
	{
		if (!this->sRenderableColorMap.empty())
			return this->sRenderableColorMap.begin()->second->width();
		else if (this->pRenderableDepth)
			return this->pRenderableDepth->width();
		else if (this->pRenderableStencil)
			return this->pRenderableStencil->width();
		
		return 0;
	}

	inline GLsizei RenderTarget::height() const
	{
		if (!this->sRenderableColorMap.empty())
			return this->sRenderableColorMap.begin()->second->height();
		else if (this->pRenderableDepth)
			return this->pRenderableDepth->height();
		else if (this->pRenderableStencil)
			return this->pRenderableStencil->height();

		return 0;
	}

	inline Renderable *RenderTarget::depth()
	{
		return this->pRenderableDepth;
	}

	inline const Renderable *RenderTarget::depth() const
	{
		return this->pRenderableDepth;
	}

	inline Renderable *RenderTarget::stencil()
	{
		return this->pRenderableStencil;
	}

	inline const Renderable *RenderTarget::stencil() const
	{
		return this->pRenderableStencil;
	}

	inline Renderable *RenderTarget::color(GLuint nIndex)
	{
		auto iIndex{this->sRenderableColorMap.find(nIndex)};
		return iIndex == this->sRenderableColorMap.cend() ? nullptr : iIndex->second;
	}

	inline const Renderable *RenderTarget::color(GLuint nIndex) const
	{
		auto iIndex{this->sRenderableColorMap.find(nIndex)};
		return iIndex == this->sRenderableColorMap.cend() ? nullptr : iIndex->second;
	}
}

#endif