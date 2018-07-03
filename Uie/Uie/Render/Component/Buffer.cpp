
/*
	2018.04.25
	Created by AcrylicShrimp.
*/

#include "Buffer.h"

namespace Uie::Render::Component
{
	BufferBase::BufferBase()
	{
		glCreateBuffers(1, &this->nIdentifier);
	}

	BufferBase::BufferBase(BufferBase &&sSrc) :
		nIdentifier{sSrc.nIdentifier}
	{
		sSrc.nIdentifier = 0;
	}

	BufferBase::~BufferBase()
	{
		if (this->nIdentifier)
			glDeleteBuffers(1, &this->nIdentifier);

		this->nIdentifier = 0;
	}

	BufferBase &BufferBase::operator=(BufferBase &&sSrc)
	{
		if (&sSrc == this)
			return *this;

		if (this->nIdentifier)
			glDeleteBuffers(1, &this->nIdentifier);

		this->nIdentifier = sSrc.nIdentifier;
		sSrc.nIdentifier = 0;

		return *this;
	}
}