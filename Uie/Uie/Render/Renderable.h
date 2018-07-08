
/*
	2018.07.07
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_UIE_RENDER_RENDERABLE_H

#define _CLASS_UIE_RENDER_RENDERABLE_H

#include "../UieDLL.h"

#include <vector>

namespace Uie::Render
{
	class UIE_DLL Renderable
	{
	public:
		Renderable() = default;
		Renderable(const Renderable &sSrc) = default;
		virtual ~Renderable() = default;

	public:
		Renderable &operator=(const Renderable &sSrc) = default;

	public:
		virtual void reorder(std::vector<Renderable *> &sRenderableList) = 0;
		virtual void update() = 0;
		virtual void render() = 0;
	};
}

#endif