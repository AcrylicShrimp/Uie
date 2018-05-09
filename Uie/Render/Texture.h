
/*
	2018.05.01
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_UIE_RENDER_TEXTURE_H

#define _CLASS_UIE_RENDER_TEXTURE_H

#include "../UieDLL.h"

#include "GL.h"
#include "UniformBindable.h"

#include <algorithm>
#include <cmath>
#include <cstddef>
#include <GL/glew.h>

#include <Windows.h>

namespace Uie::Render
{
	class Texture final : public UniformBindable
	{
	public:
		enum class DataFormat : GLenum
		{
			R = GL_RED,
			RG = GL_RG,
			RGB = GL_RGB,
			BGR = GL_BGR,
			RGBA = GL_RGBA,
			BGRA = GL_BGRA,
			Depth = GL_DEPTH_COMPONENT,
			DepthStencil = GL_DEPTH_STENCIL
		};

		enum class Format : GLenum
		{
			R = GL_RED,
			RG = GL_RG,
			RGB = GL_RGB,
			RGBA = GL_RGBA,
			Depth = GL_DEPTH_COMPONENT,
			DepthStencil = GL_DEPTH_STENCIL,
			R8 = GL_R8,
			R8SN = GL_R8_SNORM,
			R16 = GL_R16,
			R16SN = GL_R16_SNORM,
			RG88 = GL_RG8,
			RG88SN = GL_RG8_SNORM,
			RGB332 = GL_R3_G3_B2,
			RGB444 = GL_RGB4,
			RGB555 = GL_RGB5,
			RGB888 = GL_RGB8,
			RGB888SN = GL_RGB8_SNORM,
			RGB101010 = GL_RGB10,
			RGB121212 = GL_RGB12,
			RGB161616SN = GL_RGB16_SNORM,
			RGBA2222 = GL_RGBA2,
			RGBA4444 = GL_RGBA4,
			RGBA5551 = GL_RGB5_A1,
			RGBA8888 = GL_RGBA8,
			RGBA888SN = GL_RGBA8_SNORM,
			RGBA1010102 = GL_RGB10_A2,
			RGBA1010102U = GL_RGB10_A2UI,
			RGBA12121212 = GL_RGBA12,
			RGBA16161616 = GL_RGBA16,
			sRGB8888 = GL_SRGB8,
			sRGBA8888 = GL_SRGB8_ALPHA8,
			R16F = GL_R16F,
			RG1616F = GL_RG16F,
			RGB161616F = GL_RGB16F,
			RGBA16161616F = GL_RGBA16F,
			R32F = GL_R32F,
			RG3232F = GL_RG32F,
			RGB323232F = GL_RGB32F,
			RGBA32323232F = GL_RGBA32F,
			RGB111110F = GL_R11F_G11F_B10F,
			RGBE9995 = GL_RGB9_E5,
			R8I = GL_R8I,
			R8U = GL_R8UI,
			R16I = GL_R16I,
			R16U = GL_R16UI,
			R32I = GL_R32I,
			R32U = GL_R32UI,
			RG88I = GL_RG8I,
			RG88U = GL_RG8UI,
			RG1616I = GL_RG16I,
			RG1616U = GL_RG16UI,
			RG3232I = GL_RG32I,
			RG3232U = GL_RG32UI,
			RGB888I = GL_RGB8I,
			RGB888U = GL_RGB8UI,
			RGB161616I = GL_RGB16I,
			RGB161616U = GL_RGB16UI,
			RGB323232I = GL_RGB32I,
			RGB323232U = GL_RGB32UI,
			RGBA8888I = GL_RGBA8I,
			RGBA8888U = GL_RGBA8UI,
			RGBA16161616I = GL_RGBA16I,
			RGBA16161616U = GL_RGBA16UI,
			RGBA32323232I = GL_RGBA32I,
			RGBA32323232U = GL_RGBA32UI,
			Rc = GL_COMPRESSED_RED,
			RGc = GL_COMPRESSED_RG,
			RGBc = GL_COMPRESSED_RGB,
			RGBAc = GL_COMPRESSED_RGBA,
			sRGBc = GL_COMPRESSED_SRGB,
			sRGBAc = GL_COMPRESSED_SRGB_ALPHA,
			Rc1 = GL_COMPRESSED_RED_RGTC1,
			Rc1S = GL_COMPRESSED_SIGNED_RED_RGTC1,
			RGc2 = GL_COMPRESSED_RG_RGTC2,
			RGc2S = GL_COMPRESSED_RG_RGTC2,
			RGBAc4UN = GL_COMPRESSED_RGBA_BPTC_UNORM,
			sRGBAc4UN = GL_COMPRESSED_SRGB_ALPHA_BPTC_UNORM,
			RGBc3SF = GL_COMPRESSED_RGB_BPTC_SIGNED_FLOAT,
			RGBc3UF = GL_COMPRESSED_RGB_BPTC_UNSIGNED_FLOAT
		};

		enum class FilterMode : GLint
		{
			Point = GL_NEAREST,
			Bilinear = GL_LINEAR,
			Trilinear = GL_LINEAR_MIPMAP_LINEAR
		};

		enum class WrappingMode : GLint
		{
			Border = GL_CLAMP_TO_BORDER,
			Edge = GL_CLAMP_TO_EDGE,
			Mirror = GL_MIRRORED_REPEAT,
			MirrorEdge = GL_MIRROR_CLAMP_TO_EDGE,
			Repeat = GL_REPEAT
		};

	protected:
		GLuint nIdentifier;
		GLuint nSamplerIdentifier;
		GLsizei nWidth;
		GLsizei nHeight;
		Format eFormat;
		bool bMipmap;
		FilterMode eFilterMode;
		WrappingMode eWrappingModeS;
		WrappingMode eWrappingModeT;
		GLfloat nAnisotropicFiltering;
		GLint nLastActiveIndex;

	public:
		Texture(GLsizei nWidth, GLsizei nHeight, Format eFormat, bool bMipmap = false);
		Texture(const Texture &sSrc) = delete;
		Texture(Texture &&sSrc);
		~Texture();

	public:
		Texture &operator=(const Texture &sSrc) = delete;
		Texture &operator=(Texture &&sSrc);

	public:
		inline GLsizei width() const;
		inline GLsizei height() const;
		inline Format format() const;
		inline bool mipmap() const;
		inline FilterMode filterMode() const;
		inline WrappingMode wrappingModeS() const;
		inline WrappingMode wrappingModeT() const;
		inline GLfloat anisotropicFiltering() const;
		void use(GLint nIndex);
		void filterMode(FilterMode eFilterMode);
		void wrappingMode(WrappingMode eWrappingModeS, WrappingMode eWrappingModeT);
		void anisotropicFiltering(float nAnisotropicFiltering);
		template<class T> inline void fill(DataFormat eDataFormat, const T *pPixel);
		template<GL::Type T> inline void fill(DataFormat eDataFormat, const void *pPixel);
		template<class T> inline void fill(GLint nX, GLint nY, GLsizei nWidth, GLsizei nHeight, DataFormat eDataFormat, const T *pPixel);
		template<GL::Type T> inline void fill(GLint nX, GLint nY, GLsizei nWidth, GLsizei nHeight, DataFormat eDataFormat, const void *pPixel);
		template<class T> static inline GLint largestAlignment(GLsizei nWidth, DataFormat eDataFormat, const T *pPixel);
		template<GL::Type T> static inline GLint largestAlignment(GLsizei nWidth, DataFormat eDataFormat, const void *pPixel);
		template<DataFormat T> static constexpr std::size_t elementPerPixel();
		template<> static constexpr std::size_t elementPerPixel<DataFormat::R>();
		template<> static constexpr std::size_t elementPerPixel<DataFormat::RG>();
		template<> static constexpr std::size_t elementPerPixel<DataFormat::RGB>();
		template<> static constexpr std::size_t elementPerPixel<DataFormat::BGR>();
		template<> static constexpr std::size_t elementPerPixel<DataFormat::RGBA>();
		template<> static constexpr std::size_t elementPerPixel<DataFormat::BGRA>();
		template<> static constexpr std::size_t elementPerPixel<DataFormat::Depth>();
		template<> static constexpr std::size_t elementPerPixel<DataFormat::DepthStencil>();

	protected:
		virtual void bind(GLuint nShaderIdentifier, GLint nUniformLocation) const override;
	};

	inline GLsizei Texture::width() const
	{
		return this->nWidth;
	}

	inline GLsizei Texture::height() const
	{
		return this->nHeight;
	}

	inline Texture::Format Texture::format() const
	{
		return this->eFormat;
	}

	inline bool Texture::mipmap() const
	{
		return this->bMipmap;
	}

	inline Texture::FilterMode Texture::filterMode() const
	{
		return this->eFilterMode;
	}

	inline Texture::WrappingMode Texture::wrappingModeS() const
	{
		return this->eWrappingModeS;
	}

	inline Texture::WrappingMode Texture::wrappingModeT() const
	{
		return this->eWrappingModeT;
	}

	inline GLfloat Texture::anisotropicFiltering() const
	{
		return this->nAnisotropicFiltering;
	}

	template<class T> inline void Texture::fill(DataFormat eDataFormat, const T *pPixel)
	{
		glPixelStorei(GL_UNPACK_ALIGNMENT, Texture::largestAlignment<T>(this->nWidth, eDataFormat, pPixel));
		glTextureSubImage2D(this->nIdentifier, 0, 0, 0, this->nWidth, this->nHeight, static_cast<GLenum>(eDataFormat), GL::type<T>(), pPixel);

		if (this->bMipmap)
			glGenerateTextureMipmap(this->nIdentifier);
	}

	template<GL::Type T> inline void Texture::fill(DataFormat eDataFormat, const void *pPixel)
	{
		glPixelStorei(GL_UNPACK_ALIGNMENT, Texture::largestAlignment<T>(this->nWidth, eDataFormat, pPixel));
		glTextureSubImage2D(this->nIdentifier, 0, 0, 0, this->nWidth, this->nHeight, static_cast<GLenum>(eDataFormat), GL::type<T>(), pPixel);

		if (this->bMipmap)
			glGenerateTextureMipmap(this->nIdentifier);
	}

	template<class T> inline void Texture::fill(GLint nX, GLint nY, GLsizei nWidth, GLsizei nHeight, DataFormat eDataFormat, const T *pPixel)
	{
		glPixelStorei(GL_UNPACK_ALIGNMENT, Texture::largestAlignment<T>(nWidth, eDataFormat, pPixel));
		glTextureSubImage2D(this->nIdentifier, 0, nX, nY, nWidth, nHeight, static_cast<GLenum>(eDataFormat), GL::type<T>(), pPixel);

		if (this->bMipmap)
			glGenerateTextureMipmap(this->nIdentifier);
	}

	template<GL::Type T> inline void Texture::fill(GLint nX, GLint nY, GLsizei nWidth, GLsizei nHeight, DataFormat eDataFormat, const void *pPixel)
	{
		glPixelStorei(GL_UNPACK_ALIGNMENT, Texture::largestAlignment<T>(nWidth, eDataFormat, pPixel));
		glTextureSubImage2D(this->nIdentifier, 0, nX, nY, nWidth, nHeight, static_cast<GLenum>(eDataFormat), GL::type<T>(), pPixel);

		if (this->bMipmap)
			glGenerateTextureMipmap(this->nIdentifier);
	}

	template<class T> inline GLint Texture::largestAlignment(GLsizei nWidth, DataFormat eDataFormat, const T *pPixel)
	{
		std::size_t nElementPerPixel;

		switch (eDataFormat)
		{
		case DataFormat::R:
			nElementPerPixel = Texture::elementPerPixel<DataFormat::R>();
			break;

		case DataFormat::RG:
			nElementPerPixel = Texture::elementPerPixel<DataFormat::RG>();
			break;

		case DataFormat::RGB:
			nElementPerPixel = Texture::elementPerPixel<DataFormat::RGB>();
			break;

		case DataFormat::BGR:
			nElementPerPixel = Texture::elementPerPixel<DataFormat::BGR>();
			break;

		default:
		case DataFormat::RGBA:
			nElementPerPixel = Texture::elementPerPixel<DataFormat::RGBA>();
			break;

		case DataFormat::BGRA:
			nElementPerPixel = Texture::elementPerPixel<DataFormat::BGRA>();
			break;

		case DataFormat::Depth:
			nElementPerPixel = Texture::elementPerPixel<DataFormat::Depth>();
			break;

		case DataFormat::DepthStencil:
			nElementPerPixel = Texture::elementPerPixel<DataFormat::DepthStencil>();
			break;
		}

		auto nRowStart{reinterpret_cast<std::size_t>(pPixel)};
		auto nRowSize{nWidth * nElementPerPixel * sizeof(T)};

		if (!(nRowStart % 8) && !(nRowSize % 8))
			return 8;

		if (!(nRowStart % 4) && !(nRowSize % 4))
			return 4;

		if (!(nRowStart & 1) && !(nRowSize & 1))
			return 2;

		return 1;
	}

	template<GL::Type T> inline GLint Texture::largestAlignment(GLsizei nWidth, DataFormat eDataFormat, const void *pPixel)
	{
		std::size_t nElementPerPixel;

		switch (eDataFormat)
		{
		case DataFormat::R:
			nElementPerPixel = Texture::elementPerPixel<DataFormat::R>();
			break;

		case DataFormat::RG:
			nElementPerPixel = Texture::elementPerPixel<DataFormat::RG>();
			break;

		case DataFormat::RGB:
			nElementPerPixel = Texture::elementPerPixel<DataFormat::RGB>();
			break;

		case DataFormat::BGR:
			nElementPerPixel = Texture::elementPerPixel<DataFormat::BGR>();
			break;

		default:
		case DataFormat::RGBA:
			nElementPerPixel = Texture::elementPerPixel<DataFormat::RGBA>();
			break;

		case DataFormat::BGRA:
			nElementPerPixel = Texture::elementPerPixel<DataFormat::BGRA>();
			break;

		case DataFormat::Depth:
			nElementPerPixel = Texture::elementPerPixel<DataFormat::Depth>();
			break;

		case DataFormat::DepthStencil:
			nElementPerPixel = Texture::elementPerPixel<DataFormat::DepthStencil>();
			break;
		}

		auto nRowStart{reinterpret_cast<std::size_t>(pPixel)};
		auto nRowSize{nWidth * nElementPerPixel / GL::elementCount<T>() * GL::size<T>()};

		if (!(nRowStart % 8) && !(nRowSize % 8))
			return 8;

		if (!(nRowStart % 4) && !(nRowSize % 4))
			return 4;

		if (!(nRowStart & 1) && !(nRowSize & 1))
			return 2;

		return 1;
	}

	template<Texture::DataFormat T> constexpr std::size_t Texture::elementPerPixel()
	{
		static_assert(sizeof(T) == 0, "Unsupported data format type.");
	}

	template<> constexpr std::size_t Texture::elementPerPixel<Texture::DataFormat::R>()
	{
		return 1;
	}

	template<> constexpr std::size_t Texture::elementPerPixel<Texture::DataFormat::RG>()
	{
		return 2;
	}

	template<> constexpr std::size_t Texture::elementPerPixel<Texture::DataFormat::RGB>()
	{
		return 3;
	}

	template<> constexpr std::size_t Texture::elementPerPixel<Texture::DataFormat::BGR>()
	{
		return 3;
	}

	template<> constexpr std::size_t Texture::elementPerPixel<Texture::DataFormat::RGBA>()
	{
		return 4;
	}

	template<> constexpr std::size_t Texture::elementPerPixel<Texture::DataFormat::BGRA>()
	{
		return 4;
	}

	template<> constexpr std::size_t Texture::elementPerPixel<Texture::DataFormat::Depth>()
	{
		return 1;
	}

	template<> constexpr std::size_t Texture::elementPerPixel<Texture::DataFormat::DepthStencil>()
	{
		return 2;
	}
}

#endif