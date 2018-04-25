
/*
	2018.04.25
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_UIE_RENDER_SHADERATTRIB_H

#define _CLASS_UIE_RENDER_SHADERATTRIB_H

#include "../UieDLL.h"

#include <GL/glew.h>

namespace Uie::Render
{
	class ShaderAttrib final
	{
	public:
		enum class Type : GLenum
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
		GLuint nShaderInput;
		GLuint nAttribIndex;

	public:
		ShaderAttrib(GLuint nShaderInput, GLuint nAttribIndex);
		ShaderAttrib(const ShaderAttrib &sSrc) = delete;
		ShaderAttrib(ShaderAttrib &&sSrc);
		~ShaderAttrib();

	public:
		ShaderAttrib &operator=(const ShaderAttrib &sSrc) = delete;
		ShaderAttrib &operator=(ShaderAttrib &&sSrc);

	public:
		template<class T> inline void format(GLint nElementPerVertex, GLuint nAdditionalOffset);
		template<class T> inline void format(GLint nElementPerVertex, GLuint nAdditionalOffset, bool bNormalize);
		template<Type T> inline void format(GLint nElementPerVertex, GLuint nAdditionalOffset);
		template<Type T> inline void format(GLint nElementPerVertex, GLuint nAdditionalOffset, bool bNormalize);
		template<> inline void format<GLbyte>(GLint nElementPerVertex, GLuint nAdditionalOffset);
		template<> inline void format<GLbyte>(GLint nElementPerVertex, GLuint nAdditionalOffset, bool bNormalize);
		template<> inline void format<GLubyte>(GLint nElementPerVertex, GLuint nAdditionalOffset);
		template<> inline void format<GLubyte>(GLint nElementPerVertex, GLuint nAdditionalOffset, bool bNormalize);
		template<> inline void format<GLshort>(GLint nElementPerVertex, GLuint nAdditionalOffset);
		template<> inline void format<GLshort>(GLint nElementPerVertex, GLuint nAdditionalOffset, bool bNormalize);
		template<> inline void format<GLushort>(GLint nElementPerVertex, GLuint nAdditionalOffset);
		template<> inline void format<GLushort>(GLint nElementPerVertex, GLuint nAdditionalOffset, bool bNormalize);
		template<> inline void format<GLint>(GLint nElementPerVertex, GLuint nAdditionalOffset);
		template<> inline void format<GLint>(GLint nElementPerVertex, GLuint nAdditionalOffset, bool bNormalize);
		template<> inline void format<GLuint>(GLint nElementPerVertex, GLuint nAdditionalOffset);
		template<> inline void format<GLuint>(GLint nElementPerVertex, GLuint nAdditionalOffset, bool bNormalize);
		template<> inline void format<GLfloat>(GLint nElementPerVertex, GLuint nAdditionalOffset);
		template<> inline void format<GLfloat>(GLint nElementPerVertex, GLuint nAdditionalOffset, bool bNormalize);
		template<> inline void format<GLdouble>(GLint nElementPerVertex, GLuint nAdditionalOffset);
		template<> inline void format<GLdouble>(GLint nElementPerVertex, GLuint nAdditionalOffset, bool bNormalize);
		void use(GLuint nBufferIndex) const;
	};

	template<class T> inline void ShaderAttrib::format(GLint nElementPerVertex, GLuint nAdditionalOffset)
	{
		static_assert(sizeof(T) == 0, "Unsupported attrib format type.");
	}

	template<class T> inline void ShaderAttrib::format(GLint nElementPerVertex, GLuint nAdditionalOffset, bool bNormalize)
	{
		static_assert(sizeof(T) == 0, "Unsupported attrib format type.");
	}

	template<ShaderAttrib::Type T> inline void ShaderAttrib::format(GLint nElementPerVertex, GLuint nAdditionalOffset)
	{
		switch (T)
		{
		case Type::Byte:
		case Type::uByte:
		case Type::Short:
		case Type::uShort:
		case Type::Int:
		case Type::Int_2AAAr:
		case Type::uInt:
		case Type::uInt_2AAAr:
		{
			glVertexArrayAttribIFormat(this->nIdentifier, this->nAttribIndex, nElementPerVertex, static_cast<GLenum>(eType), nAdditionalOffset);
		}
		break;
		case Type::Fixed:
		case Type::Float:
		case Type::Float_ABBr:
		case Type::Half:
		{
			glVertexArrayAttribFormat(this->nIdentifier, this->nAttribIndex, nElementPerVertex, static_cast<GLenum>(eType), false, nAdditionalOffset);
		}
		break;
		case Type::Double:
		{
			glVertexArrayAttribLFormat(this->nIdentifier, this->nAttribIndex, nElementPerVertex, static_cast<GLenum>(eType), nAdditionalOffset);
		}
		break;
		}
	}

	template<ShaderAttrib::Type T> inline void ShaderAttrib::format(GLint nElementPerVertex, GLuint nAdditionalOffset, bool bNormalize)
	{
		glVertexArrayAttribFormat(this->nShaderInput, this->nAttribIndex, nElementPerVertex, static_cast<GLenum>(eType), bNormalize, nAdditionalOffset);
	}

	template<> inline void ShaderAttrib::format<GLbyte>(GLint nElementPerVertex, GLuint nAdditionalOffset)
	{
		glVertexArrayAttribIFormat(this->nShaderInput, this->nAttribIndex, nElementPerVertex, GL_BYTE, nAdditionalOffset);
	}

	template<> inline void ShaderAttrib::format<GLbyte>(GLint nElementPerVertex, GLuint nAdditionalOffset, bool bNormalize)
	{
		glVertexArrayAttribFormat(this->nShaderInput, this->nAttribIndex, nElementPerVertex, GL_BYTE, bNormalize, nAdditionalOffset);
	}

	template<> inline void ShaderAttrib::format<GLubyte>(GLint nElementPerVertex, GLuint nAdditionalOffset)
	{
		glVertexArrayAttribIFormat(this->nShaderInput, this->nAttribIndex, nElementPerVertex, GL_UNSIGNED_BYTE, nAdditionalOffset);
	}

	template<> inline void ShaderAttrib::format<GLubyte>(GLint nElementPerVertex, GLuint nAdditionalOffset, bool bNormalize)
	{
		glVertexArrayAttribFormat(this->nShaderInput, this->nAttribIndex, nElementPerVertex, GL_UNSIGNED_BYTE, bNormalize, nAdditionalOffset);
	}

	template<> inline void ShaderAttrib::format<GLshort>(GLint nElementPerVertex, GLuint nAdditionalOffset)
	{
		glVertexArrayAttribIFormat(this->nShaderInput, this->nAttribIndex, nElementPerVertex, GL_SHORT, nAdditionalOffset);
	}

	template<> inline void ShaderAttrib::format<GLshort>(GLint nElementPerVertex, GLuint nAdditionalOffset, bool bNormalize)
	{
		glVertexArrayAttribFormat(this->nShaderInput, this->nAttribIndex, nElementPerVertex, GL_SHORT, bNormalize, nAdditionalOffset);
	}

	template<> inline void ShaderAttrib::format<GLushort>(GLint nElementPerVertex, GLuint nAdditionalOffset)
	{
		glVertexArrayAttribIFormat(this->nShaderInput, this->nAttribIndex, nElementPerVertex, GL_UNSIGNED_SHORT, nAdditionalOffset);
	}

	template<> inline void ShaderAttrib::format<GLushort>(GLint nElementPerVertex, GLuint nAdditionalOffset, bool bNormalize)
	{
		glVertexArrayAttribFormat(this->nShaderInput, this->nAttribIndex, nElementPerVertex, GL_UNSIGNED_SHORT, bNormalize, nAdditionalOffset);
	}

	template<> inline void ShaderAttrib::format<GLint>(GLint nElementPerVertex, GLuint nAdditionalOffset)
	{
		glVertexArrayAttribIFormat(this->nShaderInput, this->nAttribIndex, nElementPerVertex, GL_INT, nAdditionalOffset);
	}

	template<> inline void ShaderAttrib::format<GLint>(GLint nElementPerVertex, GLuint nAdditionalOffset, bool bNormalize)
	{
		glVertexArrayAttribFormat(this->nShaderInput, this->nAttribIndex, nElementPerVertex, GL_INT, bNormalize, nAdditionalOffset);
	}

	template<> inline void ShaderAttrib::format<GLuint>(GLint nElementPerVertex, GLuint nAdditionalOffset)
	{
		glVertexArrayAttribIFormat(this->nShaderInput, this->nAttribIndex, nElementPerVertex, GL_UNSIGNED_INT, nAdditionalOffset);
	}

	template<> inline void ShaderAttrib::format<GLuint>(GLint nElementPerVertex, GLuint nAdditionalOffset, bool bNormalize)
	{
		glVertexArrayAttribFormat(this->nShaderInput, this->nAttribIndex, nElementPerVertex, GL_UNSIGNED_INT, bNormalize, nAdditionalOffset);
	}

	template<> inline void ShaderAttrib::format<GLfloat>(GLint nElementPerVertex, GLuint nAdditionalOffset)
	{
		glVertexArrayAttribFormat(this->nShaderInput, this->nAttribIndex, nElementPerVertex, GL_FLOAT, false, nAdditionalOffset);
	}

	template<> inline void ShaderAttrib::format<GLfloat>(GLint nElementPerVertex, GLuint nAdditionalOffset, bool bNormalize)
	{
		glVertexArrayAttribFormat(this->nShaderInput, this->nAttribIndex, nElementPerVertex, GL_FLOAT, bNormalize, nAdditionalOffset);
	}

	template<> inline void ShaderAttrib::format<GLdouble>(GLint nElementPerVertex, GLuint nAdditionalOffset)
	{
		glVertexArrayAttribLFormat(this->nShaderInput, this->nAttribIndex, nElementPerVertex, GL_DOUBLE, nAdditionalOffset);
	}

	template<> inline void ShaderAttrib::format<GLdouble>(GLint nElementPerVertex, GLuint nAdditionalOffset, bool bNormalize)
	{
		glVertexArrayAttribFormat(this->nShaderInput, this->nAttribIndex, nElementPerVertex, GL_DOUBLE, bNormalize, nAdditionalOffset);
	}
}

#endif