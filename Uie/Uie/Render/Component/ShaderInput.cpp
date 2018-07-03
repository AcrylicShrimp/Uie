
/*
	2018.04.22
	Created by AcrylicShrimp.
*/

#include "ShaderInput.h"

namespace Uie::Render::Component
{
	ShaderInput::ShaderInput()
	{
		glCreateVertexArrays(1, &this->nIdentifier);
	}

	ShaderInput::ShaderInput(ShaderInput &&sSrc) :
		nIdentifier{sSrc.nIdentifier},
		sAttribMap{std::move(sSrc.sAttribMap)},
		sAttribBufferMap{std::move(sSrc.sAttribBufferMap)},
		sAttribBufferIndexMap{std::move(sSrc.sAttribBufferIndexMap)}
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

		if (this->nIdentifier)
			glDeleteVertexArrays(1, &this->nIdentifier);

		this->nIdentifier = sSrc.nIdentifier;
		this->sAttribMap = std::move(sSrc.sAttribMap);
		this->sAttribBufferMap = std::move(sSrc.sAttribBufferMap);
		this->sAttribBufferIndexMap = std::move(sSrc.sAttribBufferIndexMap);

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

	void ShaderInput::attachAttrib(GLuint nBufferIndex, const BufferBase *pBufferBase, GLint nElementPerVertex, GLintptr nOffset, GLsizei nStride, GLuint nInstancePerAdvance)
	{
		glVertexArrayBindingDivisor(this->nIdentifier, nBufferIndex, nInstancePerAdvance);
		glVertexArrayVertexBuffer(this->nIdentifier, nBufferIndex, pBufferBase->identifier(), nOffset, nStride ? nStride : (pBufferBase->elementSize() * nElementPerVertex));

		this->sAttribBufferMap[nBufferIndex] = pBufferBase;

		for (auto nIndex : this->sAttribBufferIndexMap[pBufferBase])
			if (nIndex == nBufferIndex)
				return;

		this->sAttribBufferIndexMap[pBufferBase].emplace_back(nBufferIndex);
	}

	void ShaderInput::detachAttrib(GLuint nBufferIndex)
	{
		auto iIndex{this->sAttribBufferMap.find(nBufferIndex)};

		if (iIndex == this->sAttribBufferMap.cend())
			return;

		for (auto nIndex : this->sAttribBufferIndexMap[iIndex->second])
		{
			this->sAttribBufferMap.erase(nIndex);
			glVertexArrayVertexBuffer(this->nIdentifier, nIndex, 0, 0, 0);
		}

		this->sAttribBufferIndexMap.erase(iIndex->second);
	}

	void ShaderInput::detachAttrib(const BufferBase *pBufferBase)
	{
		auto iIndex{this->sAttribBufferIndexMap.find(pBufferBase)};

		if (iIndex == this->sAttribBufferIndexMap.cend())
			return;

		for (auto nIndex : iIndex->second)
		{
			this->sAttribBufferMap.erase(nIndex);
			glVertexArrayVertexBuffer(this->nIdentifier, nIndex, 0, 0, 0);
		}

		this->sAttribBufferIndexMap.erase(pBufferBase);
	}

	void ShaderInput::attachUniform(const BufferBase *pBufferBase, GLuint nBufferIndex)
	{
		glBindBufferBase(GL_UNIFORM_BUFFER, nBufferIndex, pBufferBase->identifier());

		this->sUniformBufferMap[nBufferIndex] = pBufferBase;

		for (auto nIndex : this->sUniformBufferIndexMap[pBufferBase])
			if (nIndex == nBufferIndex)
				return;

		this->sUniformBufferIndexMap[pBufferBase].emplace_back(nBufferIndex);
	}

	void ShaderInput::attachUniform(const std::string &sUniformName, const UniformBindable *pUniformBindable)
	{
		this->sUniformBindableMap[sUniformName] = pUniformBindable;
	}

	void ShaderInput::detachUniform(GLuint nBufferIndex)
	{
		auto iIndex{this->sUniformBufferMap.find(nBufferIndex)};

		if (iIndex == this->sUniformBufferMap.cend())
			return;

		for (auto nIndex : this->sUniformBufferIndexMap[iIndex->second])
		{
			this->sUniformBufferMap.erase(nIndex);
			glBindBufferBase(GL_UNIFORM_BUFFER, nIndex, 0);
		}

		this->sUniformBufferIndexMap.erase(iIndex->second);
	}

	void ShaderInput::detachUniform(const BufferBase *pBufferBase)
	{
		auto iIndex{this->sUniformBufferIndexMap.find(pBufferBase)};

		if (iIndex == this->sUniformBufferIndexMap.cend())
			return;

		for (auto nIndex : iIndex->second)
		{
			this->sUniformBufferMap.erase(nIndex);
			glBindBufferBase(GL_UNIFORM_BUFFER, nIndex, 0);
		}

		this->sUniformBufferIndexMap.erase(pBufferBase);
	}

	void ShaderInput::detachUniform(const std::string &sUniformName)
	{
		this->sUniformBindableMap.erase(sUniformName);
	}

	void ShaderInput::enableUniform(const std::string &sUniformName, GLuint nBufferIndex)
	{
		this->sUniformMap[sUniformName] = nBufferIndex;
	}

	void ShaderInput::disableUniform(const std::string &sUniformName)
	{
		this->sUniformMap.erase(sUniformName);
	}

	void ShaderInput::activateUniform(std::function<void(const std::string &, GLuint)> fActivator) const
	{
		for (const auto &sPair : this->sUniformMap)
			fActivator(sPair.first, sPair.second);
	}

	void ShaderInput::bindUniformBindable(GLuint nShaderIdentifier, std::function<GLint(const std::string &)> fUniformLocationGenerator) const
	{
		for (const auto &sPair : this->sUniformBindableMap)
			sPair.second->bindUniform(nShaderIdentifier, fUniformLocationGenerator(sPair.first));
	}
}