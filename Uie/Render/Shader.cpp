
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

	SubShader &Shader::operator[](SubShader::Type eType)
	{
		for (auto &sSubShader : this->sSubShaderList)
			if (sSubShader.type() == eType)
				return sSubShader;

		this->sSubShaderList.emplace_back(this->nIdentifier, eType);
		return this->sSubShaderList.back();
	}

	void Shader::use(const ShaderInput &sShaderInput) const
	{
		sShaderInput.activateUniform([this](const std::string &sUniformName, GLuint nBufferIndex)
		{
			glUniformBlockBinding(this->nIdentifier, glGetUniformBlockIndex(this->nIdentifier, sUniformName.c_str()), nBufferIndex);
		});

		sShaderInput.use();
		glUseProgram(this->nIdentifier);
	}

	bool Shader::link(std::string *pLinkLog) const
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

	GLint Shader::getAttribLocation(const std::string &sAttribName) const
	{
		return glGetAttribLocation(this->nIdentifier, sAttribName.c_str());
	}

	GLint Shader::getUniformLocation(const std::string &sUniformName) const
	{
		return glGetUniformLocation(this->nIdentifier, sUniformName.c_str());
	}
}