
/*
	2018.04.08
	Created by AcrylicShrimp.
*/

#include "Rect.h"

namespace Uie
{
	Rect::Rect() :
		nL{.0f},
		nR{.0f},
		nT{.0f},
		nB{.0f}
	{
		//Empty.
	}

	Rect::Rect(float nLT, float nRB) :
		nL{nLT},
		nR{nRB},
		nT{nLT},
		nB{nRB}
	{
		//Empty.
	}

	Rect::Rect(float nL, float nR, float nT, float nB) :
		nL{nL},
		nR{nR},
		nT{nT},
		nB{nB}
	{
		//Empty.
	}
	
	Rect::Rect(const Rect &sSrc) :
		nL{sSrc.nL},
		nR{sSrc.nR},
		nT{sSrc.nT},
		nB{sSrc.nB}
	{
		//Empty.
	}

	Rect &Rect::operator=(const Rect &sSrc)
	{
		if (&sSrc == this)
			return *this;
		
		this->nL = sSrc.nL;
		this->nR = sSrc.nR;
		this->nT = sSrc.nT;
		this->nB = sSrc.nB;
		
		return *this;
	}

	void Rect::setLT(float nLT)
	{
		this->nL = this->nT = nLT;
	}

	void Rect::setLT(float nL, float nT)
	{
		this->nL = nL;
		this->nT = nT;
	}

	void Rect::setRB(float nRB)
	{
		this->nR = this->nB = nRB;
	}

	void Rect::setRB(float nR, float nB)
	{
		this->nR = nR;
		this->nB = nB;
	}

	void Rect::set(float nLT, float nRB)
	{
		this->nL = this->nT = nLT;
		this->nR = this->nB = nRB;
	}

	void Rect::set(float nL, float nR, float nT, float nB)
	{
		this->nL = nL;
		this->nT = nT;
		this->nR = nR;
		this->nB = nB;
	}

	void Rect::setXYWH(float nX, float nY, float nWidth, float nHeight)
	{
		this->nL = nX;
		this->nT = nY;
		this->nR = nX + nWidth;
		this->nB = nY + nHeight;
	}

	bool Rect::contains(float nX, float nY)
	{
		return
			this->nL <= nX && nX <= this->nR &&
			this->nT <= nY && nY <= this->nB;
	}
}