
/*
	2018.04.20
	Created by AcrylicShrimp.
*/

#include "SubShader.h"

namespace Uie::Render
{
	SubShader::SubShader(GLuint nProgram, Type eType) :
		nProgram{nProgram},
		nIdentifier{glCreateShader(static_cast<GLenum>(eType))},
		eType{eType}
	{
		glAttachShader(this->nProgram, this->nIdentifier);
	}

	SubShader::SubShader(SubShader &&sSrc) :
		nProgram{sSrc.nProgram},
		nIdentifier{sSrc.nIdentifier},
		eType{sSrc.eType}
	{
		sSrc.nIdentifier = 0;
	}

	SubShader::~SubShader()
	{
		if (!this->nIdentifier)
			return;

		glDetachShader(this->nProgram, this->nIdentifier);
		glDeleteShader(this->nIdentifier);

		this->nIdentifier = 0;
	}

	SubShader &SubShader::operator=(SubShader &&sSrc)
	{
		if (&sSrc == this)
			return *this;

		if (sSrc.nProgram != this->nProgram)
			return *this;

		this->~SubShader();

		this->nIdentifier = sSrc.nIdentifier;
		this->eType = sSrc.eType;

		sSrc.nIdentifier = 0;

		return *this;
	}

	bool SubShader::compile(const std::string &sSource, std::string *pCompileLog)
	{
		const auto pSource{sSource.data()};

		glShaderSource(this->nIdentifier, 1, &pSource, nullptr);
		glCompileShader(this->nIdentifier);

		GLint nResult;
		glGetShaderiv(this->nIdentifier, GL_COMPILE_STATUS, &nResult);

		if (pCompileLog)
		{
			auto &sCompileLog{*pCompileLog};

			GLint nLength;
			glGetShaderiv(this->nIdentifier, GL_INFO_LOG_LENGTH, &nLength);

			sCompileLog.resize(nLength, '\0');
			glGetShaderInfoLog(this->nIdentifier, nLength, nullptr, sCompileLog.data());
		}

		return nResult == GL_TRUE;
	}
}