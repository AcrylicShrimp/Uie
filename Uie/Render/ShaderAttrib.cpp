
/*
	2018.04.25
	Created by AcrylicShrimp.
*/

#include "ShaderAttrib.h"

namespace Uie::Render
{
	ShaderAttrib::ShaderAttrib(GLuint nShaderInput, GLuint nAttribIndex) :
		nShaderInput{nShaderInput},
		nAttribIndex{nAttribIndex}
	{
		glEnableVertexArrayAttrib(this->nShaderInput, this->nAttribIndex);
	}

	ShaderAttrib::ShaderAttrib(ShaderAttrib &&sSrc) :
		nShaderInput{sSrc.nShaderInput},
		nAttribIndex{sSrc.nAttribIndex}
	{
		sSrc.nShaderInput = 0;
		sSrc.nAttribIndex = 0;
	}

	ShaderAttrib::~ShaderAttrib()
	{
		if (this->nShaderInput)
			glDisableVertexArrayAttrib(this->nShaderInput, this->nAttribIndex);

		this->nShaderInput = 0;
		this->nAttribIndex = 0;
	}

	ShaderAttrib &ShaderAttrib::operator=(ShaderAttrib &&sSrc)
	{
		if (&sSrc == this)
			return *this;

		this->~ShaderAttrib();

		this->nShaderInput = sSrc.nShaderInput;
		this->nAttribIndex = sSrc.nAttribIndex;

		sSrc.nShaderInput = 0;
		sSrc.nAttribIndex = 0;

		return *this;
	}

	void ShaderAttrib::use(GLuint nBufferIndex) const
	{
		glVertexArrayAttribBinding(this->nShaderInput, this->nAttribIndex, nBufferIndex);
	}
}