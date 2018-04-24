
/*
	2018.04.22
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_UIE_RENDER_SHADERINPUT_H

#define _CLASS_UIE_RENDER_SHADERINPUT_H

#include "../UieDLL.h"

#include "Buffer.h"
#include "IShaderInput.h"

#include <string>
#include <tuple>
#include <utility>
#include <vector>
#include <GL/glew.h>

namespace Uie::Render
{
	class ShaderInput
	{
	public:
		enum class Format : GLenum
		{
			Byte = GL_BYTE,
			uByte = GL_UNSIGNED_BYTE,
			Short = GL_SHORT,
			uShort = GL_UNSIGNED_SHORT,
			Int = GL_INT,
			Int_2AAAr = GL_INT_2_10_10_10_REV,
			uInt = GL_UNSIGNED_INT,
			uInt_2AAAr = GL_UNSIGNED_INT_2_10_10_10_REV,
			Fixed = GL_FIXED,
			Float = GL_FLOAT,
			Float_ABBr = GL_UNSIGNED_INT_10F_11F_11F_REV,
			Half = GL_HALF_FLOAT,
			Double = GL_DOUBLE,
		};

	private:
		GLuint nIdentifier;
		
	public:
		ShaderInput();
		ShaderInput(const ShaderInput &sSrc) = delete;
		ShaderInput(ShaderInput &&sSrc);
		~ShaderInput();
		
	public:
		ShaderInput &operator=(const ShaderInput &sSrc) = delete;
		ShaderInput &operator=(ShaderInput &&sSrc);
		
	public:
		template<class T> inline void setAttribFormat(GLuint nAttribLocation, GLint nElementPerVertex, GLuint nOffset = 0, bool bNormalize = false);
		template<class T> inline void setAttribFormat(const std::string &sAttribName, GLint nElementPerVertex, GLuint nOffset = 0, bool bNormalize = false);
		template<Format eFormat> inline void setAttribFormat(GLuint nAttribLocation, GLint nElementPerVertex, GLuint nOffset = 0, bool bNormalize = false);
		template<Format eFormat> inline void setAttribFormat(const std::string &sAttribName, GLint nElementPerVertex, GLuint nOffset = 0, bool bNormalize = false);
		template<> void setAttribFormat<GLbyte>(GLuint nAttribLocation, GLint nElementPerVertex, GLuint nOffset, bool bNormalize);
		template<> void setAttribFormat<GLubyte>(GLuint nAttribLocation, GLint nElementPerVertex, GLuint nOffset, bool bNormalize);
		template<> void setAttribFormat<GLshort>(GLuint nAttribLocation, GLint nElementPerVertex, GLuint nOffset, bool bNormalize);
		template<> void setAttribFormat<GLushort>(GLuint nAttribLocation, GLint nElementPerVertex, GLuint nOffset, bool bNormalize);
		template<> void setAttribFormat<GLint>(GLuint nAttribLocation, GLint nElementPerVertex, GLuint nOffset, bool bNormalize);
		template<> void setAttribFormat<GLuint>(GLuint nAttribLocation, GLint nElementPerVertex, GLuint nOffset, bool bNormalize);
		template<> void setAttribFormat<GLfloat>(GLuint nAttribLocation, GLint nElementPerVertex, GLuint nOffset, bool bNormalize);
		template<> void setAttribFormat<GLdouble>(GLuint nAttribLocation, GLint nElementPerVertex, GLuint nOffset, bool bNormalize);
		void use() const;
	};

	template<class T> inline void ShaderInput::setAttribFormat(GLuint nAttribLocation, GLint nElementPerVertex, GLuint nOffset, bool bNormalize)
	{
#error "Unsupported attrib format type."
	}

	template<class T> inline void ShaderInput::setAttribFormat(const std::string &sAttribName, GLint nElementPerVertex, GLuint nOffset, bool bNormalize)
	{
		this->setAttribFormat<T>(static_cast<GLuint>(this->getAttribLocation(sAttribName)), nElementPerVertex, nOffset, bNormalize);
	}

	template<ShaderInput::Format eFormat> inline void ShaderInput::setAttribFormat(GLuint nAttribLocation, GLint nElementPerVertex, GLuint nOffset, bool bNormalize)
	{
		if (bNormalize)
			glVertexArrayAttribFormat(this->nIdentifier, nAttribLocation, nElementPerVertex, static_cast<GLenum>(eType), true, nOffset);
		else
			switch (eFormat)
			{
			case Format::Byte:
			case Format::uByte:
			case Format::Short:
			case Format::uShort:
			case Format::Int:
			case Format::Int_2AAAr:
			case Format::uInt:
			case Format::uInt_2AAAr:
			{
				glVertexArrayAttribIFormat(this->nIdentifier, nAttribLocation, nElementPerVertex, static_cast<GLenum>(eType), nOffset);
			}
			break;
			case Format::Fixed:
			case Format::Float:
			case Format::Float_ABBr:
			case Format::Half:
			{
				glVertexArrayAttribFormat(this->nIdentifier, nAttribLocation, nElementPerVertex, static_cast<GLenum>(eType), bNormalize, nOffset);
			}
			break;
			case Format::Double:
			{
				glVertexArrayAttribLFormat(this->nIdentifier, nAttribLocation, nElementPerVertex, static_cast<GLenum>(eType), nOffset);
			}
			break;
			}
	}

	template<ShaderInput::Format eFormat> inline void ShaderInput::setAttribFormat(const std::string &sAttribName, GLint nElementPerVertex, GLuint nOffset, bool bNormalize)
	{
		this->setAttribFormat<eFormat>(static_cast<GLuint>(this->getAttribLocation(sAttribName)), nElementPerVertex, nOffset, bNormalize);
	}
}

#endif