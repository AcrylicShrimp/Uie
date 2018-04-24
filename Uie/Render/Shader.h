
/*
	2018.04.20
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_UIE_RENDER_SHADER_H

#define _CLASS_UIE_RENDER_SHADER_H

#include "../UieDLL.h"

#include "SubShader.h"

#include <string>
#include <utility>
#include <vector>
#include <GL/glew.h>

namespace Uie::Render
{
	class UIE_DLL Shader final
	{
	private:
		GLuint nIdentifier;
		std::vector<SubShader> sSubShaderList;

	public:
		Shader();
		Shader(const Shader &sSrc) = delete;
		Shader(Shader &&sSrc);
		~Shader();

	public:
		Shader &operator=(const Shader &sSrc) = delete;
		Shader &operator=(Shader &&sSrc);
		SubShader &operator[](SubShaderType eType);

	public:
		void use() const;
		bool link(std::string *pLinkLog = nullptr) const;
		GLint getAttribLocation(const std::string &sAttribName) const;
		GLint getUniformLocation(const std::string &sUniformName) const;
	};

	template<class T> inline void Shader::setAttribFormat(GLuint nAttribLocation, GLint nElementPerVertex, GLuint nOffset, bool bNormalize)
	{
#error "Unsupported attrib format type."
	}

	template<class T> inline void Shader::setAttribFormat(const std::string &sAttribName, GLint nElementPerVertex, GLuint nOffset, bool bNormalize)
	{
		this->setAttribFormat<T>(static_cast<GLuint>(this->getAttribLocation(sAttribName)), nElementPerVertex, nOffset, bNormalize);
	}

	template<Shader::FormatType eType> inline void Shader::setAttribFormat(GLuint nAttribLocation, GLint nElementPerVertex, GLuint nOffset, bool bNormalize)
	{
		if (bNormalize)
			glVertexArrayAttribFormat(this->nIdentifier, nAttribLocation, nElementPerVertex, static_cast<GLenum>(eType), true, nOffset);
		else
			switch (eType)
			{
			case FormatType::Byte:
			case FormatType::uByte:
			case FormatType::Short:
			case FormatType::uShort:
			case FormatType::Int:
			case FormatType::Int_2AAAr:
			case FormatType::uInt:
			case FormatType::uInt_2AAAr:
			{
				glVertexArrayAttribIFormat(this->nIdentifier, nAttribLocation, nElementPerVertex, static_cast<GLenum>(eType), nOffset);
			}
			break;
			case FormatType::Fixed:
			case FormatType::Float:
			case FormatType::Float_ABBr:
			case FormatType::Half:
			{
				glVertexArrayAttribFormat(this->nIdentifier, nAttribLocation, nElementPerVertex, static_cast<GLenum>(eType), bNormalize, nOffset);
			}
			break;
			case FormatType::Double:
			{
				glVertexArrayAttribLFormat(this->nIdentifier, nAttribLocation, nElementPerVertex, static_cast<GLenum>(eType), nOffset);
			}
			break;
			}
	}

	template<Shader::FormatType eType> inline void Shader::setAttribFormat(const std::string &sAttribName, GLint nElementPerVertex, GLuint nOffset, bool bNormalize)
	{
		this->setAttribFormat<eType>(static_cast<GLuint>(this->getAttribLocation(sAttribName)), nElementPerVertex, nOffset, bNormalize);
	}
}

#endif