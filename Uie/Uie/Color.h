
/*
	2018.04.05
	Created by AcrylicShrimp.
*/

#ifndef _STRUCT_UIE_COLOR_H

#define _STRUCT_UIE_COLOR_H

#include "UieDLL.h"

#include <algorithm>
#include <cstddef>
#include <cstdint>

namespace Uie
{
	struct UIE_DLL Color final
	{
	public:
		static const Color Black;
		static const Color White;
		static const Color Red;
		static const Color Green;
		static const Color Blue;
		static const Color Cyan;
		static const Color Magenta;
		static const Color Yellow;

	public:
		float nR;
		float nG;
		float nB;
		float nA;

	public:
		Color();
		Color(std::uint32_t nColorCode);
		Color(std::uint8_t nR, std::uint8_t nG, std::uint8_t nB);
		Color(std::uint8_t nR, std::uint8_t nG, std::uint8_t nB, std::uint8_t nA);
		Color(float nR, float nG, float nB);
		Color(float nR, float nG, float nB, float nA);
		Color(const Color &sSrc);
		~Color() = default;

	public:
		Color &operator=(std::uint32_t nColorCode);
		Color &operator=(const Color &sSrc);
		Color &operator+=(const Color &sColor);
		Color &operator-=(const Color &sColor);
		Color &operator*=(const Color &sColor);
		Color &operator*=(std::uint8_t nFactor);
		Color &operator*=(float nFactor);
		float &operator[](std::size_t nIndex);
		float operator[](std::size_t nIndex) const;

	public:
		inline void red(std::uint8_t nR);
		inline void green(std::uint8_t nG);
		inline void blue(std::uint8_t nB);
		inline void alpha(std::uint8_t nA);
		inline std::uint8_t red() const;
		inline std::uint8_t green() const;
		inline std::uint8_t blue() const;
		inline std::uint8_t alpha() const;
	};

	Color operator+(const Color &sLeft, const Color &sRight);
	Color operator-(const Color &sLeft, const Color &sRight);
	Color operator*(const Color &sLeft, const Color &sRight);
	Color operator*(const Color &sLeft, std::uint8_t nRight);
	Color operator*(std::uint8_t nLeft, const Color &sRight);
	Color operator*(const Color &sLeft, float nRight);
	Color operator*(float nLeft, const Color &sRight);

	inline void Color::red(std::uint8_t nR)
	{
		this->nR = std::min(std::max(nR / 255.f, .0f), 1.f);
	}

	inline void Color::green(std::uint8_t nG)
	{
		this->nG = std::min(std::max(nG / 255.f, .0f), 1.f);
	}

	inline void Color::blue(std::uint8_t nB)
	{
		this->nB = std::min(std::max(nB / 255.f, .0f), 1.f);
	}

	inline void Color::alpha(std::uint8_t nA)
	{
		this->nA = std::min(std::max(nA / 255.f, .0f), 1.f);
	}

	inline std::uint8_t Color::red() const
	{
		return static_cast<std::uint8_t>(std::min(std::max(this->nR, .0f), 1.f) * 255.f + .5f);
	}

	inline std::uint8_t Color::green() const
	{
		return static_cast<std::uint8_t>(std::min(std::max(this->nG, .0f), 1.f) * 255.f + .5f);
	}

	inline std::uint8_t Color::blue() const
	{
		return static_cast<std::uint8_t>(std::min(std::max(this->nB, .0f), 1.f) * 255.f + .5f);
	}

	inline std::uint8_t Color::alpha() const
	{
		return static_cast<std::uint8_t>(std::min(std::max(this->nA, .0f), 1.f) * 255.f + .5f);
	}
}

#endif