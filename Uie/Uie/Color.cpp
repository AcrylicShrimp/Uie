
/*
	2018.04.05
	Created by AcrylicShrimp.
*/

#include "Color.h"

namespace Uie
{
	const Color Color::Black{.0f, .0f, .0f};
	const Color Color::White{1.f, 1.f, 1.f};
	const Color Color::Red{1.f, .0f, .0f};
	const Color Color::Green{.0f, 1.f, .0f};
	const Color Color::Blue{.0f, .0f, 1.f};
	const Color Color::Cyan{.0f, 1.f, 1.f};
	const Color Color::Magenta{1.f, .0f, 1.f};
	const Color Color::Yellow{1.f, 1.f, .0f};

	Color::Color() :
		nR{.0f},
		nG{.0f},
		nB{.0f},
		nA{.0f}
	{
		//Empty.
	}

	Color::Color(std::uint32_t nColorCode) :
		nR{((nColorCode & 0xFF000000) >> 24) / 255.f},
		nG{((nColorCode & 0x00FF0000) >> 16) / 255.f},
		nB{((nColorCode & 0x0000FF00) >> 8) / 255.f},
		nA{(nColorCode & 0x000000FF) / 255.f}
	{
		//Empty.
	}

	Color::Color(std::uint8_t nR, std::uint8_t nG, std::uint8_t nB) :
		nR{std::min(nR / .255f, 1.f)},
		nG{std::min(nG / .255f, 1.f)},
		nB{std::min(nB / .255f, 1.f)},
		nA{1.f}
	{
		//Empty.
	}

	Color::Color(std::uint8_t nR, std::uint8_t nG, std::uint8_t nB, std::uint8_t nA) :
		nR{std::min(nR / .255f, 1.f)},
		nG{std::min(nG / .255f, 1.f)},
		nB{std::min(nB / .255f, 1.f)},
		nA{std::min(nA / .255f, 1.f)}
	{
		//Empty.
	}

	Color::Color(float nR, float nG, float nB) :
		nR{std::min(std::max(nR, .0f), 1.f)},
		nG{std::min(std::max(nG, .0f), 1.f)},
		nB{std::min(std::max(nB, .0f), 1.f)},
		nA{1.f}
	{
		//Empty.
	}

	Color::Color(float nR, float nG, float nB, float nA) :
		nR{std::min(std::max(nR, .0f), 1.f)},
		nG{std::min(std::max(nG, .0f), 1.f)},
		nB{std::min(std::max(nB, .0f), 1.f)},
		nA{std::min(std::max(nA, .0f), 1.f)}
	{
		//Empty.
	}

	Color::Color(const Color &sSrc) :
		nR{std::min(std::max(sSrc.nR, .0f), 1.f)},
		nG{std::min(std::max(sSrc.nG, .0f), 1.f)},
		nB{std::min(std::max(sSrc.nB, .0f), 1.f)},
		nA{std::min(std::max(sSrc.nA, .0f), 1.f)}
	{
		//Empty.
	}

	Color &Color::operator=(std::uint32_t nColorCode)
	{
		this->nR = ((nColorCode & 0xFF000000) >> 24) / 255.f;
		this->nG = ((nColorCode & 0x00FF0000) >> 16) / 255.f;
		this->nB = ((nColorCode & 0x0000FF00) >> 8) / 255.f;
		this->nA = (nColorCode & 0x000000FF) / 255.f;

		return *this;
	}

	Color &Color::operator=(const Color &sSrc)
	{
		if (&sSrc == this)
			return *this;

		this->nR = std::min(std::max(sSrc.nR, .0f), 1.f);
		this->nG = std::min(std::max(sSrc.nG, .0f), 1.f);
		this->nB = std::min(std::max(sSrc.nB, .0f), 1.f);
		this->nA = std::min(std::max(sSrc.nA, .0f), 1.f);

		return *this;
	}

	Color &Color::operator+=(const Color &sColor)
	{
		this->nR = std::min(std::max(this->nR + sColor.nR, .0f), 1.f);
		this->nG = std::min(std::max(this->nG + sColor.nG, .0f), 1.f);
		this->nB = std::min(std::max(this->nB + sColor.nB, .0f), 1.f);
		this->nA = std::min(std::max(this->nA + sColor.nA, .0f), 1.f);

		return *this;
	}

	Color &Color::operator-=(const Color &sColor)
	{
		this->nR = std::min(std::max(this->nR - sColor.nR, .0f), 1.f);
		this->nG = std::min(std::max(this->nG - sColor.nG, .0f), 1.f);
		this->nB = std::min(std::max(this->nB - sColor.nB, .0f), 1.f);
		this->nA = std::min(std::max(this->nA - sColor.nA, .0f), 1.f);

		return *this;
	}

	Color &Color::operator*=(const Color &sColor)
	{
		this->nR = std::min(std::max(this->nR * sColor.nR, .0f), 1.f);
		this->nG = std::min(std::max(this->nG * sColor.nG, .0f), 1.f);
		this->nB = std::min(std::max(this->nB * sColor.nB, .0f), 1.f);
		this->nA = std::min(std::max(this->nA * sColor.nA, .0f), 1.f);

		return *this;
	}

	Color &Color::operator*=(std::uint8_t nFactor)
	{
		auto nNormalizedFactor{nFactor / 255.f};

		this->nR = std::min(std::max(this->nR * nNormalizedFactor, .0f), 1.f);
		this->nG = std::min(std::max(this->nG * nNormalizedFactor, .0f), 1.f);
		this->nB = std::min(std::max(this->nB * nNormalizedFactor, .0f), 1.f);
		this->nA = std::min(std::max(this->nA * nNormalizedFactor, .0f), 1.f);

		return *this;
	}

	Color &Color::operator*=(float nFactor)
	{
		this->nR = std::min(std::max(this->nR * nFactor, .0f), 1.f);
		this->nG = std::min(std::max(this->nG * nFactor, .0f), 1.f);
		this->nB = std::min(std::max(this->nB * nFactor, .0f), 1.f);
		this->nA = std::min(std::max(this->nA * nFactor, .0f), 1.f);

		return *this;
	}

	float &Color::operator[](std::size_t nIndex)
	{
		switch (nIndex)
		{
		case 0:
			return this->nR;

		case 1:
			return this->nG;

		case 2:
			return this->nB;

		default:
			return this->nA;
		}
	}

	float Color::operator[](std::size_t nIndex) const
	{
		switch (nIndex)
		{
		case 0:
			return this->nR;

		case 1:
			return this->nG;

		case 2:
			return this->nB;

		default:
			return this->nA;
		}
	}

	Color operator+(const Color &sLeft, const Color &sRight)
	{
		return
		{
			std::min(std::max(sLeft.nR + sRight.nR, .0f), .1f),
			std::min(std::max(sLeft.nG + sRight.nG, .0f), .1f),
			std::min(std::max(sLeft.nB + sRight.nB, .0f), .1f),
			std::min(std::max(sLeft.nA + sRight.nA, .0f), .1f)
		};
	}

	Color operator-(const Color &sLeft, const Color &sRight)
	{
		return
		{
			std::min(std::max(sLeft.nR - sRight.nR, .0f), .1f),
			std::min(std::max(sLeft.nG - sRight.nG, .0f), .1f),
			std::min(std::max(sLeft.nB - sRight.nB, .0f), .1f),
			std::min(std::max(sLeft.nA - sRight.nA, .0f), .1f)
		};
	}

	Color operator*(const Color &sLeft, const Color &sRight)
	{
		return
		{
			std::min(std::max(sLeft.nR * sRight.nR, .0f), .1f),
			std::min(std::max(sLeft.nG * sRight.nG, .0f), .1f),
			std::min(std::max(sLeft.nB * sRight.nB, .0f), .1f),
			std::min(std::max(sLeft.nA * sRight.nA, .0f), .1f)
		};
	}

	Color operator*(const Color &sLeft, std::uint8_t nRight)
	{
		auto nNormalizedFactor{nRight / 255.f};

		return
		{
			std::min(std::max(sLeft.nR * nNormalizedFactor, .0f), .1f),
			std::min(std::max(sLeft.nG * nNormalizedFactor, .0f), .1f),
			std::min(std::max(sLeft.nB * nNormalizedFactor, .0f), .1f),
			std::min(std::max(sLeft.nA * nNormalizedFactor, .0f), .1f)
		};
	}

	Color operator*(std::uint8_t nLeft, const Color &sRight)
	{
		auto nNormalizedFactor{nLeft / 255.f};

		return
		{
			std::min(std::max(nNormalizedFactor * sRight.nR, .0f), .1f),
			std::min(std::max(nNormalizedFactor * sRight.nG, .0f), .1f),
			std::min(std::max(nNormalizedFactor * sRight.nB, .0f), .1f),
			std::min(std::max(nNormalizedFactor * sRight.nA, .0f), .1f)
		};
	}

	Color operator*(const Color &sLeft, float nRight)
	{
		return
		{
			std::min(std::max(sLeft.nR * nRight, .0f), .1f),
			std::min(std::max(sLeft.nG * nRight, .0f), .1f),
			std::min(std::max(sLeft.nB * nRight, .0f), .1f),
			std::min(std::max(sLeft.nA * nRight, .0f), .1f)
		};
	}

	Color operator*(float nLeft, const Color &sRight)
	{
		return
		{
			std::min(std::max(nLeft * sRight.nR, .0f), .1f),
			std::min(std::max(nLeft * sRight.nG, .0f), .1f),
			std::min(std::max(nLeft * sRight.nB, .0f), .1f),
			std::min(std::max(nLeft * sRight.nA, .0f), .1f)
		};
	}
}