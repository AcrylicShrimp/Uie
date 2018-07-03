
/*
	2018.05.11
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_UIE_RENDER_COMPONENT_COLORRENDERBUFFER_H

#define _CLASS_UIE_RENDER_COMPONENT_COLORRENDERBUFFER_H

#include "../../UieDLL.h"

#include "RenderBuffer.h"

#include <GL/glew.h>

namespace Uie::Render::Component
{
	class UIE_DLL ColorRenderBuffer final : public RenderBuffer
	{
	public:
		enum class Format : GLenum
		{
			R = GL_RED,
			R8 = GL_R8,
			R8SN = GL_R8_SNORM,
			R16 = GL_R16,
			R16SN = GL_R16_SNORM,
			RG = GL_RG,
			RG88 = GL_RG8,
			RG88SN = GL_RG8_SNORM,
			RGB = GL_RGB,
			RGB332 = GL_R3_G3_B2,
			RGB444 = GL_RGB4,
			RGB555 = GL_RGB5,
			RGB888 = GL_RGB8,
			RGB888SN = GL_RGB8_SNORM,
			RGB101010 = GL_RGB10,
			RGB121212 = GL_RGB12,
			RGB161616SN = GL_RGB16_SNORM,
			RGBA = GL_RGBA,
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

	protected:
		Format eFormat;
		
	public:
		ColorRenderBuffer(GLsizei nWidth, GLsizei nHeight, Format eFormat);
		ColorRenderBuffer(const ColorRenderBuffer &sSrc) = delete;
		ColorRenderBuffer(ColorRenderBuffer &&sSrc) = default;
		~ColorRenderBuffer() = default;
		
	public:
		ColorRenderBuffer &operator=(const ColorRenderBuffer &sSrc) = delete;
		ColorRenderBuffer &operator=(ColorRenderBuffer &&sSrc) = default;
		
	public:
		inline Format format() const;
	};

	inline ColorRenderBuffer::Format ColorRenderBuffer::format() const
	{
		return this->eFormat;
	}
}

#endif