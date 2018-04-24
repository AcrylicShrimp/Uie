
/*
	2018.04.22
	Created by AcrylicShrimp.
*/

#include "ShaderInput.h"

namespace Uie::Render
{
	ShaderInput::ShaderInput()
	{
		glGenVertexArrays(1, &this->nIdentifier);
	}

	ShaderInput::ShaderInput(ShaderInput &&sSrc) :
		nIdentifier{sSrc.nIdentifier},
		sInputList{std::move(sSrc.sInputList)}
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
		this->sInputList = std::move(sSrc.sInputList);

		sSrc.nIdentifier = 0;

		return *this;
	}

	template<> void ShaderInput::setAttribFormat<GLbyte>(GLuint nAttribLocation, GLint nElementPerVertex, GLuint nOffset, bool bNormalize)
	{
		if (bNormalize)
			glVertexArrayAttribFormat(this->nIdentifier, nAttribLocation, nElementPerVertex, GL_BYTE, true, nOffset);
		else
			glVertexArrayAttribIFormat(this->nIdentifier, nAttribLocation, nElementPerVertex, GL_BYTE, nOffset);
	}

	template<> void ShaderInput::setAttribFormat<GLubyte>(GLuint nAttribLocation, GLint nElementPerVertex, GLuint nOffset, bool bNormalize)
	{
		if (bNormalize)
			glVertexArrayAttribFormat(this->nIdentifier, nAttribLocation, nElementPerVertex, GL_UNSIGNED_BYTE, true, nOffset);
		else
			glVertexArrayAttribIFormat(this->nIdentifier, nAttribLocation, nElementPerVertex, GL_UNSIGNED_BYTE, nOffset);
	}

	template<> void ShaderInput::setAttribFormat<GLshort>(GLuint nAttribLocation, GLint nElementPerVertex, GLuint nOffset, bool bNormalize)
	{
		if (bNormalize)
			glVertexArrayAttribFormat(this->nIdentifier, nAttribLocation, nElementPerVertex, GL_SHORT, true, nOffset);
		else
			glVertexArrayAttribIFormat(this->nIdentifier, nAttribLocation, nElementPerVertex, GL_SHORT, nOffset);
	}

	template<> void ShaderInput::setAttribFormat<GLushort>(GLuint nAttribLocation, GLint nElementPerVertex, GLuint nOffset, bool bNormalize)
	{
		if (bNormalize)
			glVertexArrayAttribFormat(this->nIdentifier, nAttribLocation, nElementPerVertex, GL_UNSIGNED_SHORT, true, nOffset);
		else
			glVertexArrayAttribIFormat(this->nIdentifier, nAttribLocation, nElementPerVertex, GL_UNSIGNED_SHORT, nOffset);
	}

	template<> void ShaderInput::setAttribFormat<GLint>(GLuint nAttribLocation, GLint nElementPerVertex, GLuint nOffset, bool bNormalize)
	{
		if (bNormalize)
			glVertexArrayAttribFormat(this->nIdentifier, nAttribLocation, nElementPerVertex, GL_INT, true, nOffset);
		else
			glVertexArrayAttribIFormat(this->nIdentifier, nAttribLocation, nElementPerVertex, GL_INT, nOffset);
	}

	template<> void ShaderInput::setAttribFormat<GLuint>(GLuint nAttribLocation, GLint nElementPerVertex, GLuint nOffset, bool bNormalize)
	{
		if (bNormalize)
			glVertexArrayAttribFormat(this->nIdentifier, nAttribLocation, nElementPerVertex, GL_UNSIGNED_INT, true, nOffset);
		else
			glVertexArrayAttribIFormat(this->nIdentifier, nAttribLocation, nElementPerVertex, GL_UNSIGNED_INT, nOffset);
	}

	template<> void ShaderInput::setAttribFormat<GLfloat>(GLuint nAttribLocation, GLint nElementPerVertex, GLuint nOffset, bool bNormalize)
	{
		glVertexArrayAttribFormat(this->nIdentifier, nAttribLocation, nElementPerVertex, GL_FLOAT, bNormalize, nOffset);
	}

	template<> void ShaderInput::setAttribFormat<GLdouble>(GLuint nAttribLocation, GLint nElementPerVertex, GLuint nOffset, bool bNormalize)
	{
		if (bNormalize)
			glVertexArrayAttribFormat(this->nIdentifier, nAttribLocation, nElementPerVertex, GL_DOUBLE, true, nOffset);
		else
			glVertexArrayAttribLFormat(this->nIdentifier, nAttribLocation, nElementPerVertex, GL_DOUBLE, nOffset);
	}

	void ShaderInput::use() const
	{
		glBindVertexArray(this->nIdentifier);
	}
}