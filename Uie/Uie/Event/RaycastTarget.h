
/*
	2018.07.07
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_UIE_EVENT_RAYCASTTARGET_H

#define _CLASS_UIE_EVENT_RAYCASTTARGET_H

#include "../UieDLL.h"

#include "../Rect.h"

namespace Uie::Event
{
	class UIE_DLL RaycastTarget
	{
	protected:
		Rect sRect;
		
	public:
		RaycastTarget() = default;
		RaycastTarget(const RaycastTarget &sSrc) = default;
		virtual ~RaycastTarget() = default;
		
	public:
		RaycastTarget &operator=(const RaycastTarget &sSrc) = default;
		
	public:
		inline Rect &rect();
		inline const Rect &rect() const;
		bool raycast(float nX, float nY) const;
		bool overlap(const Rect &sRect) const;
		bool overlap(const RaycastTarget &sRaycastTarget) const;
		bool contain(const Rect &sRect) const;
		bool contain(const RaycastTarget &sRaycastTarget) const;
	};

	inline Rect &RaycastTarget::rect()
	{
		return sRect;
	}

	inline const Rect &RaycastTarget::rect() const
	{
		return sRect;
	}
}

#endif