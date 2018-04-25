
/*
	2018.04.22
	Created by AcrylicShrimp.
*/

#include "ShaderInput.h"

namespace Uie::Render
{
	ShaderInput::ShaderInput()
	{
		glCreateVertexArrays(1, &this->nIdentifier);
	}

	ShaderInput::ShaderInput(ShaderInput &&sSrc) :
		nIdentifier{sSrc.nIdentifier},
		sAttribMap{std::move(sSrc.sAttribMap)},
		sBufferMap{std::move(sSrc.sBufferMap)},
		sBufferIndexMap{std::move(sSrc.sBufferIndexMap)}
	{
		sSrc.nIdentifier = 0;
	}

	ShaderInput::~ShaderInput()
	{
		if (this->nIdentifier)
			glDeleteVertexArrays(1, &this->nIdentifier);

		this->nIdentifier = 0;
	}

	ShaderInput &ShaderInput::operator=(ShaderInput &&sSrc)
	{
		if (&sSrc == this)
			return *this;

		this->~ShaderInput();

		this->nIdentifier = sSrc.nIdentifier;
		this->sAttribMap = std::move(sSrc.sAttribMap);
		this->sBufferMap = std::move(sSrc.sBufferMap);
		this->sBufferIndexMap = std::move(sSrc.sBufferIndexMap);

		sSrc.nIdentifier = 0;

		return *this;
	}

	ShaderAttrib *ShaderInput::operator[](GLuint nAttribIndex)
	{
		auto iIndex{this->sAttribMap.find(nAttribIndex)};

		if (iIndex != this->sAttribMap.cend())
			return &iIndex->second;

		return &this->sAttribMap.emplace(nAttribIndex, ShaderAttrib{this->nIdentifier, nAttribIndex}).first->second;
	}

	const ShaderAttrib *ShaderInput::operator[](GLuint nAttribIndex) const
	{
		auto iIndex{this->sAttribMap.find(nAttribIndex)};
		return iIndex == this->sAttribMap.cend() ? nullptr : &iIndex->second;
	}

	void ShaderInput::use() const
	{
		glBindVertexArray(this->nIdentifier);
	}

	void ShaderInput::disable(GLuint nAttribIndex)
	{
		this->sAttribMap.erase(nAttribIndex);
	}

	void ShaderInput::attach(GLuint nBufferIndex, const BufferBase *pBufferBase, GLintptr nOffset, GLsizei nStride, GLuint nInstancePerAdvance)
	{
		glVertexArrayBindingDivisor(this->nIdentifier, nBufferIndex, nInstancePerAdvance);
		glVertexArrayVertexBuffer(this->nIdentifier, nBufferIndex, pBufferBase->identifier(), nOffset, nStride ? nStride : pBufferBase->elementSize());

		this->sBufferMap[nBufferIndex] = pBufferBase;

		for (auto nIndex : this->sBufferIndexMap[pBufferBase])
			if (nIndex == nBufferIndex)
				return;

		this->sBufferIndexMap[pBufferBase].emplace_back(nBufferIndex);
	}

	void ShaderInput::detach(GLuint nBufferIndex)
	{
		auto iIndex{this->sBufferMap.find(nBufferIndex)};

		if (iIndex == this->sBufferMap.cend())
			return;

		for (auto nIndex : this->sBufferIndexMap[iIndex->second])
		{
			this->sBufferMap.erase(nIndex);
			glVertexArrayVertexBuffer(this->nIdentifier, nIndex, 0, 0, 0);
		}

		this->sBufferIndexMap.erase(iIndex->second);
	}

	void ShaderInput::detach(const BufferBase *pBufferBase)
	{
		auto iIndex{this->sBufferIndexMap.find(pBufferBase)};

		if (iIndex == this->sBufferIndexMap.cend())
			return;

		for (auto nIndex : iIndex->second)
		{
			this->sBufferMap.erase(nIndex);
			glVertexArrayVertexBuffer(this->nIdentifier, nIndex, 0, 0, 0);
		}

		this->sBufferIndexMap.erase(pBufferBase);
	}
}