
/*
	2018.05.01
	Created by AcrylicShrimp.
*/

#include "Texture.h"

namespace Uie::Render
{
	Texture::Texture(GLsizei nWidth, GLsizei nHeight, Format eFormat, bool bMipmap) :
		nWidth{nWidth},
		nHeight{nHeight},
		eFormat{eFormat},
		bMipmap{bMipmap}
	{
		glCreateTextures(GL_TEXTURE_2D, 1, &this->nIdentifier);
		glTextureStorage2D(this->nIdentifier, 0, static_cast<GLenum>(this->eFormat), this->nWidth, this->nHeight);

		glCreateSamplers(1, &this->nSamplerIdentifier);

		this->filterMode(FilterMode::Point);
		this->wrappingMode(WrappingMode::Edge, WrappingMode::Edge);
	}

	Texture::Texture(Texture &&sSrc) :
		nIdentifier{sSrc.nIdentifier},
		nSamplerIdentifier{sSrc.nSamplerIdentifier},
		nWidth{sSrc.nWidth},
		nHeight{sSrc.nHeight},
		eFormat{sSrc.eFormat},
		bMipmap{sSrc.bMipmap}
	{
		sSrc.nIdentifier = 0;
		sSrc.nSamplerIdentifier = 0;
		sSrc.nWidth = 0;
		sSrc.nHeight = 0;
	}

	Texture::~Texture()
	{
		if (this->nIdentifier)
			glDeleteTextures(1, &this->nIdentifier);

		if (this->nSamplerIdentifier)
			glDeleteSamplers(1, &this->nSamplerIdentifier);

		this->nIdentifier = 0;
		this->nSamplerIdentifier = 0;
		this->nWidth = 0;
		this->nHeight = 0;
	}

	Texture &Texture::operator=(Texture &&sSrc)
	{
		if (&sSrc == this)
			return *this;

		this->~Texture();

		this->nIdentifier = sSrc.nIdentifier;
		this->nSamplerIdentifier = sSrc.nSamplerIdentifier;
		this->nWidth = sSrc.nWidth;
		this->nHeight = sSrc.nHeight;
		this->eFormat = sSrc.eFormat;
		this->bMipmap = sSrc.bMipmap;

		sSrc.nIdentifier = 0;
		sSrc.nSamplerIdentifier = 0;
		sSrc.nWidth = 0;
		sSrc.nHeight = 0;

		return *this;
	}

	void Texture::use(GLint nIndex) const
	{
		glActiveTexture(GL_TEXTURE0 + nIndex);
		glBindTexture(GL_TEXTURE_2D, this->nIdentifier);
		glBindSampler(nIndex, this->nSamplerIdentifier);
	}

	void Texture::filterMode(FilterMode eFilterMode)
	{
		glSamplerParameteri(this->nSamplerIdentifier, GL_TEXTURE_MAG_FILTER, (this->eFilterMode = eFilterMode) == FilterMode::Trilinear ? GL_LINEAR : static_cast<GLint>(eFilterMode));
		glSamplerParameteri(this->nSamplerIdentifier, GL_TEXTURE_MIN_FILTER, !this->bMipmap && this->eFilterMode == FilterMode::Trilinear ? GL_LINEAR : static_cast<GLint>(eFilterMode));
	}

	void Texture::wrappingMode(WrappingMode eWrappingModeS, WrappingMode eWrappingModeT)
	{
		glSamplerParameteri(this->nSamplerIdentifier, GL_TEXTURE_WRAP_S, static_cast<GLint>(this->eWrappingModeS = eWrappingModeS));
		glSamplerParameteri(this->nSamplerIdentifier, GL_TEXTURE_WRAP_T, static_cast<GLint>(this->eWrappingModeT = eWrappingModeT));
	}

	void Texture::anisotropicFiltering(float nAnisotropicFiltering)
	{
		glSamplerParameterf(this->nSamplerIdentifier, GL_TEXTURE_MAX_ANISOTROPY_EXT, this->nAnisotropicFiltering = nAnisotropicFiltering);
	}
}