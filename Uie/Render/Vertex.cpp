
/*
	2018.04.19
	Created by AcrylicShrimp.
*/

#include "Vertex.h"

namespace Uie::Render
{
	Vertex::Vertex() :
		nSize{0}
	{
		glGenBuffers(1, &this->nIdentifier);
	}

	Vertex::Vertex(std::initializer_list<float> sSrc) :
		Vertex()
	{
		glNamedBufferData(this->nIdentifier, sizeof(float) * (this->nSize = sSrc.size()), sSrc.begin(), GL_DYNAMIC_DRAW);
	}

	Vertex::Vertex(const std::vector<float> &sSrc) :
		Vertex()
	{
		glNamedBufferData(this->nIdentifier, sizeof(float) * (this->nSize = sSrc.size()), sSrc.data(), GL_DYNAMIC_DRAW);
	}

	Vertex::Vertex(const Vertex &sSrc) :
		Vertex()
	{
		glNamedBufferData(this->nIdentifier, sizeof(float) * (this->nSize = sSrc.nSize), nullptr, GL_DYNAMIC_DRAW);
		glCopyNamedBufferSubData(sSrc.nIdentifier, this->nIdentifier, 0, 0, sizeof(float) * this->nSize);
	}

	Vertex::Vertex(Vertex &&sSrc) :
		nIdentifier{sSrc.nIdentifier},
		nSize{sSrc.nSize}
	{
		sSrc.nIdentifier = 0;
	}

	Vertex::~Vertex()
	{
		if (this->nIdentifier)
			glDeleteBuffers(1, &this->nIdentifier);

		this->nIdentifier = 0;
	}

	Vertex &Vertex::operator=(std::initializer_list<float> sSrc)
	{
		glNamedBufferData(this->nIdentifier, sizeof(float) * sSrc.size(), sSrc.begin(), GL_DYNAMIC_DRAW);
		return *this;
	}

	Vertex &Vertex::operator=(const std::vector<float> &sSrc)
	{
		glNamedBufferData(this->nIdentifier, sizeof(float) * sSrc.size(), sSrc.data(), GL_DYNAMIC_DRAW);
		return *this;
	}

	Vertex &Vertex::operator=(const Vertex &sSrc)
	{
		if (&sSrc == this)
			return *this;

		glNamedBufferData(this->nIdentifier, sizeof(float) * (this->nSize = sSrc.nSize), nullptr, GL_DYNAMIC_DRAW);
		glCopyNamedBufferSubData(sSrc.nIdentifier, this->nIdentifier, 0, 0, sizeof(float) * this->nSize);

		return *this;
	}

	Vertex &Vertex::operator=(Vertex &&sSrc)
	{
		if (&sSrc == this)
			return *this;

		this->~Vertex();

		this->nIdentifier = sSrc.nIdentifier;
		this->nSize = sSrc.nSize;

		sSrc.nIdentifier = 0;

		return *this;
	}

	void Vertex::insert(std::initializer_list<float> sVertex, std::size_t nIndex)
	{
		if (nIndex < this->nSize)
			glNamedBufferSubData(this->nIdentifier, nIndex, sizeof(float) * std::min(sVertex.size(), this->nSize - nIndex), sVertex.begin());
	}

	void Vertex::insert(const std::vector<float> &sVertex, std::size_t nIndex)
	{
		if (nIndex < this->nSize)
			glNamedBufferSubData(this->nIdentifier, nIndex, sizeof(float) * std::min(sVertex.size(), this->nSize - nIndex), sVertex.data());
	}

	void Vertex::insert(const Vertex &sVertex, std::size_t nIndex)
	{
		if (nIndex < this->nSize)
			glCopyBufferSubData(sVertex.nIdentifier, this->nIdentifier, 0, nIndex, sizeof(float) * std::min(sVertex.nSize, this->nSize - nIndex));
	}
}