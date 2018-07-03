
/*
	2018.04.08
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_UIE_RECT_H

#define _CLASS_UIE_RECT_H

#include "UieDLL.h"

namespace Uie
{
	struct UIE_DLL Rect final
	{
	public:
		float nL;
		float nR;
		float nT;
		float nB;
		
	public:
		Rect();
		Rect(float nLT, float nRB);
		Rect(float nL, float nR, float nT, float nB);
		Rect(const Rect &sSrc);
		~Rect() = default;
		
	public:
		Rect &operator=(const Rect &sSrc);
		
	public:
		inline float width() const;
		inline float height() const;
		void setLT(float nLT);
		void setLT(float nL, float nT);
		void setRB(float nRB);
		void setRB(float nR, float nB);
		void set(float nLT, float nRB);
		void set(float nL, float nR, float nT, float nB);
		void setXYWH(float nX, float nY, float nWidth, float nHeight);
		bool contains(float nX, float nY);
	};

	inline float Rect::width() const
	{
		return this->nR - this->nL;
	}

	inline float Rect::height() const
	{
		return this->nB - this->nT;
	}
}

#endif