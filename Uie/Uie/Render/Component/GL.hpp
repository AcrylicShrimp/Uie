
/*
	2018.05.04
	Created by AcrylicShrimp.
*/

namespace Uie::Render::Component
{
	template<class T> constexpr GLenum GL::type()
	{
		static_assert(sizeof(T) == 0, "Unsupported format type.");
	}

	template<GL::Type T> constexpr GLenum GL::type()
	{
		return static_cast<GLenum>(T);
	}

	template<> constexpr GLenum GL::type<GLbyte>()
	{
		return GL_BYTE;
	}

	template<> constexpr GLenum GL::type<GLubyte>()
	{
		return GL_UNSIGNED_BYTE;
	}

	template<> constexpr GLenum GL::type<GLshort>()
	{
		return GL_SHORT;
	}

	template<> constexpr GLenum GL::type<GLushort>()
	{
		return GL_UNSIGNED_SHORT;
	}

	template<> constexpr GLenum GL::type<GLint>()
	{
		return GL_INT;
	}

	template<> constexpr GLenum GL::type<GLuint>()
	{
		return GL_UNSIGNED_INT;
	}

	template<> constexpr GLenum GL::type<GLfloat>()
	{
		return GL_FLOAT;
	}

	template<> constexpr GLenum GL::type<GLdouble>()
	{
		return GL_DOUBLE;
	}

	template<GL::Type T> constexpr GLint GL::size()
	{
		static_assert(sizeof(T) == 0, "Unsupported format type.");
	}

	template<> constexpr GLint GL::size<GL::Type::Byte>()
	{
		return sizeof(GLbyte);
	}

	template<> constexpr GLint GL::size<GL::Type::uByte>()
	{
		return sizeof(GLubyte);
	}

	template<> constexpr GLint GL::size<GL::Type::uByte332>()
	{
		return sizeof(GLubyte);
	}

	template<> constexpr GLint GL::size<GL::Type::uByte233r>()
	{
		return sizeof(GLubyte);
	}

	template<> constexpr GLint GL::size<GL::Type::Short>()
	{
		return sizeof(GLshort);
	}

	template<> constexpr GLint GL::size<GL::Type::uShort>()
	{
		return sizeof(GLushort);
	}

	template<> constexpr GLint GL::size<GL::Type::uShort565>()
	{
		return sizeof(GLushort);
	}

	template<> constexpr GLint GL::size<GL::Type::uShort565r>()
	{
		return sizeof(GLushort);
	}

	template<> constexpr GLint GL::size<GL::Type::uShort4444>()
	{
		return sizeof(GLushort);
	}

	template<> constexpr GLint GL::size<GL::Type::uShort4444r>()
	{
		return sizeof(GLushort);
	}

	template<> constexpr GLint GL::size<GL::Type::uShort5551>()
	{
		return sizeof(GLushort);
	}

	template<> constexpr GLint GL::size<GL::Type::uShort1555r>()
	{
		return sizeof(GLushort);
	}

	template<> constexpr GLint GL::size<GL::Type::Int>()
	{
		return sizeof(GLint);
	}

	template<> constexpr GLint GL::size<GL::Type::Int2AAAr>()
	{
		return sizeof(GLint);
	}

	template<> constexpr GLint GL::size<GL::Type::uInt>()
	{
		return sizeof(GLuint);
	}

	template<> constexpr GLint GL::size<GL::Type::uInt8888>()
	{
		return sizeof(GLuint);
	}

	template<> constexpr GLint GL::size<GL::Type::uInt8888r>()
	{
		return sizeof(GLuint);
	}

	template<> constexpr GLint GL::size<GL::Type::uIntAAA2>()
	{
		return sizeof(GLuint);
	}

	template<> constexpr GLint GL::size<GL::Type::uInt2AAAr>()
	{
		return sizeof(GLuint);
	}

	template<> constexpr GLint GL::size<GL::Type::Half>()
	{
		return sizeof(GLhalf);
	}

	template<> constexpr GLint GL::size<GL::Type::Fixed>()
	{
		return sizeof(GLfixed);
	}

	template<> constexpr GLint GL::size<GL::Type::Float>()
	{
		return sizeof(GLfloat);
	}

	template<> constexpr GLint GL::size<GL::Type::FloatABBr>()
	{
		return sizeof(GLfloat);
	}

	template<> constexpr GLint GL::size<GL::Type::Double>()
	{
		return sizeof(GLdouble);
	}

	template<GL::Type T> constexpr GLint GL::elementCount()
	{
		static_assert(sizeof(T) == 0, "Unsupported format type.");
	}

	template<> constexpr GLint GL::elementCount<GL::Type::Byte>()
	{
		return 1;
	}

	template<> constexpr GLint GL::elementCount<GL::Type::uByte>()
	{
		return 1;
	}

	template<> constexpr GLint GL::elementCount<GL::Type::uByte332>()
	{
		return 3;
	}

	template<> constexpr GLint GL::elementCount<GL::Type::uByte233r>()
	{
		return 3;
	}

	template<> constexpr GLint GL::elementCount<GL::Type::Short>()
	{
		return 1;
	}

	template<> constexpr GLint GL::elementCount<GL::Type::uShort>()
	{
		return 1;
	}

	template<> constexpr GLint GL::elementCount<GL::Type::uShort565>()
	{
		return 3;
	}

	template<> constexpr GLint GL::elementCount<GL::Type::uShort565r>()
	{
		return 3;
	}

	template<> constexpr GLint GL::elementCount<GL::Type::uShort4444>()
	{
		return 4;
	}

	template<> constexpr GLint GL::elementCount<GL::Type::uShort4444r>()
	{
		return 4;
	}

	template<> constexpr GLint GL::elementCount<GL::Type::uShort5551>()
	{
		return 4;
	}

	template<> constexpr GLint GL::elementCount<GL::Type::uShort1555r>()
	{
		return 4;
	}

	template<> constexpr GLint GL::elementCount<GL::Type::Int>()
	{
		return 1;
	}

	template<> constexpr GLint GL::elementCount<GL::Type::Int2AAAr>()
	{
		return 4;
	}

	template<> constexpr GLint GL::elementCount<GL::Type::uInt>()
	{
		return 1;
	}

	template<> constexpr GLint GL::elementCount<GL::Type::uInt8888>()
	{
		return 4;
	}

	template<> constexpr GLint GL::elementCount<GL::Type::uInt8888r>()
	{
		return 4;
	}

	template<> constexpr GLint GL::elementCount<GL::Type::uIntAAA2>()
	{
		return 4;
	}

	template<> constexpr GLint GL::elementCount<GL::Type::uInt2AAAr>()
	{
		return 4;
	}

	template<> constexpr GLint GL::elementCount<GL::Type::Half>()
	{
		return 1;
	}

	template<> constexpr GLint GL::elementCount<GL::Type::Fixed>()
	{
		return 1;
	}

	template<> constexpr GLint GL::elementCount<GL::Type::Float>()
	{
		return 1;
	}

	template<> constexpr GLint GL::elementCount<GL::Type::FloatABBr>()
	{
		return 3;
	}

	template<> constexpr GLint GL::elementCount<GL::Type::Double>()
	{
		return 1;
	}
}