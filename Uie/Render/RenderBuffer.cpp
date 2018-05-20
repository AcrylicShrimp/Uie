
/*
	2018.05.01
	Created by AcrylicShrimp.
*/

#include "RenderBuffer.h"

namespace Uie::Render
{
	RenderBuffer::RenderBuffer(GLsizei nWidth, GLsizei nHeight, GLenum nType) :
		nWidth{nWidth},
		nHeight{nHeight}
	{
		glCreateRenderbuffers(1, &this->nIdentifier);
		glNamedRenderbufferStorage(this->nIdentifier, nType, this->nWidth, this->nHeight);
	}
	
	RenderBuffer::RenderBuffer(RenderBuffer &&sSrc) :
		nIdentifier{sSrc.nIdentifier},
		nWidth{sSrc.nWidth},
		nHeight{sSrc.nHeight}
	{
		sSrc.nIdentifier = 0;
		sSrc.nWidth = 0;
		sSrc.nHeight = 0;
	}
	
	RenderBuffer::~RenderBuffer()
	{
		if (this->nIdentifier)
			glDeleteRenderbuffers(1, &this->nIdentifier);

		this->nIdentifier = 0;
		this->nWidth = 0;
		this->nHeight = 0;
	}
	
	RenderBuffer &RenderBuffer::operator=(RenderBuffer &&sSrc)
	{
		if (&sSrc == this)
			return *this;

		this->Renderable::operator=(std::move(sSrc));
		this->ContextObject::operator=(std::move(sSrc));

		this->~RenderBuffer();

		this->nIdentifier = sSrc.nIdentifier;
		this->nWidth = sSrc.nWidth;
		this->nHeight = sSrc.nHeight;

		sSrc.nIdentifier = 0;
		sSrc.nWidth = 0;
		sSrc.nHeight = 0;
		
		return *this;
	}

	GLuint RenderBuffer::identifier() const
	{
		return this->nIdentifier;
	}

	GLsizei RenderBuffer::width() const
	{
		return this->nWidth;
	}

	GLsizei RenderBuffer::height() const
	{
		return this->nHeight;
	}

	bool RenderBuffer::texture() const
	{
		return false;
	}
}