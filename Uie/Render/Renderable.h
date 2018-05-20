
/*
	2018.05.10
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_UIE_RENDER_RENDERABLE_H

#define _CLASS_UIE_RENDER_RENDERABLE_H

#include "../UieDLL.h"

#include <GL/glew.h>

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
		virtual GLuint identifier() const = 0;
		virtual GLsizei width() const = 0;
		virtual GLsizei height() const = 0;
		virtual bool texture() const = 0;
	};
}

#endif