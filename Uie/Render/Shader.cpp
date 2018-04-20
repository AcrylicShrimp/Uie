
/*
	2018.04.20
	Created by AcrylicShrimp.
*/

#include "Shader.h"

namespace Uie::Render
{
	Shader::Shader() :
		nIdentifier{glCreateProgram()}
	{
		this->sSubShaderList.reserve(3);
	}

	Shader::Shader(Shader &&sSrc) :
		nIdentifier{sSrc.nIdentifier},
		sSubShaderList{std::move(sSrc.sSubShaderList)}
	{
		sSrc.nIdentifier = 0;
	}

	Shader::~Shader()
	{
		if (this->nIdentifier)
			glDeleteProgram(this->nIdentifier);

		this->nIdentifier = 0;
	}

	Shader &Shader::operator=(Shader &&sSrc)
	{
		if (&sSrc == this)
			return *this;

		this->sSubShaderList = std::move(sSrc.sSubShaderList);
		this->~Shader();

		this->nIdentifier = sSrc.nIdentifier;
		sSrc.nIdentifier = 0;

		return *this;
	}

	SubShader &Shader::operator[](SubShaderType eType)
	{
		for (auto &sSubShader : this->sSubShaderList)
			if (sSubShader.type() == eType)
				return sSubShader;

		this->sSubShaderList.emplace_back(this->nIdentifier, eType);
		return this->sSubShaderList.back();
	}

	bool Shader::link(std::string *pLinkLog)
	{
		glLinkProgram(this->nIdentifier);

		GLint nResult;
		glGetProgramiv(this->nIdentifier, GL_LINK_STATUS, &nResult);

		if (pLinkLog)
		{
			auto &sLinkLog{*pLinkLog};

			GLint nLength;
			glGetProgramiv(this->nIdentifier, GL_INFO_LOG_LENGTH, &nLength);

			sLinkLog.resize(nLength, '\0');
			glGetProgramInfoLog(this->nIdentifier, nLength, nullptr, sLinkLog.data());
		}

		return nResult == GL_TRUE;
	}

	void Shader::use()
	{
		glUseProgram(this->nIdentifier);
	}
}