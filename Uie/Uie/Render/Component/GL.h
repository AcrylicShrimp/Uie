
/*
	2018.05.04
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_UIE_RENDER_COMPONENT_GL_H

#define _CLASS_UIE_RENDER_COMPONENT_GL_H

#include "../../UieDLL.h"

#include <GL/glew.h>

namespace Uie::Render::Component
{
	class UIE_DLL GL final
	{
	public:
		enum class Type : GLenum
		{
			Byte = GL_BYTE,
			uByte = GL_UNSIGNED_BYTE,
			uByte332 = GL_UNSIGNED_BYTE_3_3_2,
			uByte233r = GL_UNSIGNED_BYTE_2_3_3_REV,
			Short = GL_SHORT,
			uShort = GL_UNSIGNED_SHORT,
			uShort565 = GL_UNSIGNED_SHORT_5_6_5,
			uShort565r = GL_UNSIGNED_SHORT_5_6_5_REV,
			uShort4444 = GL_UNSIGNED_SHORT_4_4_4_4,
			uShort4444r = GL_UNSIGNED_SHORT_4_4_4_4_REV,
			uShort5551 = GL_UNSIGNED_SHORT_5_5_5_1,
			uShort1555r = GL_UNSIGNED_SHORT_1_5_5_5_REV,
			Int = GL_INT,
			Int2AAAr = GL_INT_2_10_10_10_REV,
			uInt = GL_UNSIGNED_INT,
			uInt8888 = GL_UNSIGNED_INT_8_8_8_8,
			uInt8888r = GL_UNSIGNED_INT_8_8_8_8_REV,
			uIntAAA2 = GL_UNSIGNED_INT_10_10_10_2,
			uInt2AAAr = GL_UNSIGNED_INT_2_10_10_10_REV,
			Half = GL_HALF_FLOAT,
			Fixed = GL_FIXED,
			Float = GL_FLOAT,
			FloatABBr = GL_UNSIGNED_INT_10F_11F_11F_REV,
			Double = GL_DOUBLE
		};

	public:
		GL() = delete;
		GL(const GL &sSrc) = delete;
		~GL() = delete;
		
	public:
		GL &operator=(const GL &sSrc) = delete;
		
	public:
		template<class T> static constexpr GLenum type();
		template<Type T> static constexpr GLenum type();
		template<> static constexpr GLenum type<GLbyte>();
		template<> static constexpr GLenum type<GLubyte>();
		template<> static constexpr GLenum type<GLshort>();
		template<> static constexpr GLenum type<GLushort>();
		template<> static constexpr GLenum type<GLint>();
		template<> static constexpr GLenum type<GLuint>();
		template<> static constexpr GLenum type<GLfloat>();
		template<> static constexpr GLenum type<GLdouble>();
		template<Type T> static constexpr GLint size();
		template<> static constexpr GLint size<Type::Byte>();
		template<> static constexpr GLint size<Type::uByte>();
		template<> static constexpr GLint size<Type::uByte332>();
		template<> static constexpr GLint size<Type::uByte233r>();
		template<> static constexpr GLint size<Type::Short>();
		template<> static constexpr GLint size<Type::uShort>();
		template<> static constexpr GLint size<Type::uShort565>();
		template<> static constexpr GLint size<Type::uShort565r>();
		template<> static constexpr GLint size<Type::uShort4444>();
		template<> static constexpr GLint size<Type::uShort4444r>();
		template<> static constexpr GLint size<Type::uShort5551>();
		template<> static constexpr GLint size<Type::uShort1555r>();
		template<> static constexpr GLint size<Type::Int>();
		template<> static constexpr GLint size<Type::Int2AAAr>();
		template<> static constexpr GLint size<Type::uInt>();
		template<> static constexpr GLint size<Type::uInt8888>();
		template<> static constexpr GLint size<Type::uInt8888r>();
		template<> static constexpr GLint size<Type::uIntAAA2>();
		template<> static constexpr GLint size<Type::uInt2AAAr>();
		template<> static constexpr GLint size<Type::Half>();
		template<> static constexpr GLint size<Type::Fixed>();
		template<> static constexpr GLint size<Type::Float>();
		template<> static constexpr GLint size<Type::FloatABBr>();
		template<> static constexpr GLint size<Type::Double>();
		template<Type T> static constexpr GLint elementCount();
		template<> static constexpr GLint elementCount<Type::Byte>();
		template<> static constexpr GLint elementCount<Type::uByte>();
		template<> static constexpr GLint elementCount<Type::uByte332>();
		template<> static constexpr GLint elementCount<Type::uByte233r>();
		template<> static constexpr GLint elementCount<Type::Short>();
		template<> static constexpr GLint elementCount<Type::uShort>();
		template<> static constexpr GLint elementCount<Type::uShort565>();
		template<> static constexpr GLint elementCount<Type::uShort565r>();
		template<> static constexpr GLint elementCount<Type::uShort4444>();
		template<> static constexpr GLint elementCount<Type::uShort4444r>();
		template<> static constexpr GLint elementCount<Type::uShort5551>();
		template<> static constexpr GLint elementCount<Type::uShort1555r>();
		template<> static constexpr GLint elementCount<Type::Int>();
		template<> static constexpr GLint elementCount<Type::Int2AAAr>();
		template<> static constexpr GLint elementCount<Type::uInt>();
		template<> static constexpr GLint elementCount<Type::uInt8888>();
		template<> static constexpr GLint elementCount<Type::uInt8888r>();
		template<> static constexpr GLint elementCount<Type::uIntAAA2>();
		template<> static constexpr GLint elementCount<Type::uInt2AAAr>();
		template<> static constexpr GLint elementCount<Type::Half>();
		template<> static constexpr GLint elementCount<Type::Fixed>();
		template<> static constexpr GLint elementCount<Type::Float>();
		template<> static constexpr GLint elementCount<Type::FloatABBr>();
		template<> static constexpr GLint elementCount<Type::Double>();
	};
}

#include "GL.hpp"

#endif