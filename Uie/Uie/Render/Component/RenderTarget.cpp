
/*
	2018.05.01
	Created by AcrylicShrimp.
*/

#include "RenderTarget.h"

namespace Uie::Render::Component
{
	RenderTarget::RenderTarget() :
		pRenderableDepth{nullptr},
		pRenderableStencil{nullptr}
	{
		glCreateFramebuffers(1, &this->nIdentifier);
	}

	RenderTarget::RenderTarget(RenderTarget &&sSrc) :
		nIdentifier{sSrc.nIdentifier},
		pRenderableDepth{sSrc.pRenderableDepth},
		pRenderableStencil{sSrc.pRenderableStencil},
		sRenderableColorMap{std::move(sSrc.sRenderableColorMap)}
	{
		sSrc.nIdentifier = 0;
		sSrc.pRenderableDepth = nullptr;
		sSrc.pRenderableStencil = nullptr;
		sSrc.sRenderableColorMap.clear();
	}

	RenderTarget::~RenderTarget()
	{
		if (this->nIdentifier)
			glDeleteFramebuffers(1, &this->nIdentifier);

		this->nIdentifier = 0;
		this->pRenderableDepth = nullptr;
		this->pRenderableStencil = nullptr;
	}

	RenderTarget &RenderTarget::operator=(RenderTarget &&sSrc)
	{
		if (&sSrc == this)
			return *this;

		if (this->nIdentifier)
			glDeleteFramebuffers(1, &this->nIdentifier);

		this->nIdentifier = sSrc.nIdentifier;
		this->pRenderableDepth = sSrc.pRenderableDepth;
		this->pRenderableStencil = sSrc.pRenderableStencil;
		this->sRenderableColorMap = std::move(sSrc.sRenderableColorMap);

		sSrc.nIdentifier = 0;
		sSrc.pRenderableDepth = nullptr;
		sSrc.pRenderableStencil = nullptr;

		return *this;
	}

	void RenderTarget::depth(Renderable *pRenderableDepth)
	{
		if ((this->pRenderableDepth = pRenderableDepth)->texture())
			glNamedFramebufferTexture(this->nIdentifier, GL_DEPTH_ATTACHMENT, pRenderableDepth->identifier(), 0);
		else
			glNamedFramebufferRenderbuffer(this->nIdentifier, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, pRenderableDepth->identifier());
	}

	void RenderTarget::stencil(Renderable *pRenderableStencil)
	{
		if ((this->pRenderableStencil = pRenderableStencil)->texture())
			glNamedFramebufferTexture(this->nIdentifier, GL_STENCIL_ATTACHMENT, pRenderableStencil->identifier(), 0);
		else
			glNamedFramebufferRenderbuffer(this->nIdentifier, GL_STENCIL_ATTACHMENT, GL_RENDERBUFFER, pRenderableStencil->identifier());
	}

	void RenderTarget::depthStencil(Renderable *pRenderableDepthStencil)
	{
		this->depth(pRenderableDepthStencil);
		this->stencil(pRenderableDepthStencil);
	}

	void RenderTarget::color(GLuint nIndex, Renderable *pRenderableColor)
	{
		if ((this->sRenderableColorMap[nIndex] = pRenderableColor)->texture())
			glNamedFramebufferTexture(this->nIdentifier, GL_COLOR_ATTACHMENT0 + nIndex, pRenderableColor->identifier(), 0);
		else
			glNamedFramebufferRenderbuffer(this->nIdentifier, GL_COLOR_ATTACHMENT0 + nIndex, GL_RENDERBUFFER, pRenderableColor->identifier());
	}

	void RenderTarget::use(std::initializer_list<Target> sTargetList)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, this->nIdentifier);
		glNamedFramebufferDrawBuffers(this->nIdentifier, sTargetList.size(), reinterpret_cast<const GLenum *>(sTargetList.begin()));

		glViewport(0, 0, this->width(), this->height());
	}

	void RenderTarget::useDefault(std::initializer_list<DefaultTarget> sTargetList)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glNamedFramebufferDrawBuffers(0, sTargetList.size(), reinterpret_cast<const GLenum *>(sTargetList.begin()));

		auto pRenderingContext{RenderingContext::current()};
		
		glViewport(0, 0, pRenderingContext->attachedWindow()->sizeInfo().nClientWidth, pRenderingContext->attachedWindow()->sizeInfo().nClientHeight);
	}
}