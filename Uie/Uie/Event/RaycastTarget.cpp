
/*
	2018.07.07
	Created by AcrylicShrimp.
*/

#include "RaycastTarget.h"

namespace Uie::Event
{
	bool RaycastTarget::raycast(float nX, float nY) const
	{
		return
			this->sRect.nL <= nX && nX <= this->sRect.nR &&
			this->sRect.nT <= nY && nY <= this->sRect.nB;
	}

	bool RaycastTarget::overlap(const Rect &sRect) const
	{
		return
			this->sRect.nL <= sRect.nR && sRect.nL <= this->sRect.nR &&
			this->sRect.nT <= sRect.nB && sRect.nT <= this->sRect.nB;
	}

	bool RaycastTarget::overlap(const RaycastTarget &sRaycastTarget) const
	{
		return this->overlap(sRaycastTarget.sRect);
	}

	bool RaycastTarget::contain(const Rect &sRect) const
	{
		return
			this->sRect.nL <= sRect.nL && sRect.nR <= this->sRect.nR &&
			this->sRect.nT <= sRect.nT && sRect.nB <= this->sRect.nB;
	}

	bool RaycastTarget::contain(const RaycastTarget &sRaycastTarget) const
	{
		return this->contain(sRaycastTarget.sRect);
	}
}