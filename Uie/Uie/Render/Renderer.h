
/*
	2018.07.03
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_UIE_RENDER_RENDERER_H

#define _CLASS_UIE_RENDER_RENDERER_H

#include "../UieDLL.h"

#include "../Color.h"
#include "../Window.h"

#include <Windows.h>
#include <GL/glew.h>
#include <GL/wglew.h>

namespace Uie::Render
{
	class UIE_DLL Renderer final
	{
	private:
		Window *pWindow{nullptr};
		bool bNeedClearColor{true};
		bool bNeedClearDepth{true};
		bool bNeedClearStencil{false};
		Color sClearColor{Color::Black};
		GLfloat nClearDepth{1.f};
		GLint nClearStencil{0};
		
	public:
		Renderer(Window *pWindow);
		Renderer(const Renderer &sSrc) = delete;
		Renderer(Renderer &&sSrc) = default;
		~Renderer() = default;
		
	public:
		Renderer &operator=(const Renderer &sSrc) = delete;
		Renderer &operator=(Renderer &&sSrc) = default;
		
	public:
		inline void needClearColor(bool bNeedClearColor);
		inline bool needClearColor() const;
		inline void needClearDepth(bool bNeedClearDepth);
		inline bool needClearDepth() const;
		inline void needClearStencil(bool bNeedClearStencil);
		inline bool needClearStencil() const;
		inline void clearColor(Color sClearColor);
		inline Color clearColor() const;
		inline void clearDepth(GLfloat nClearDepth);
		inline GLfloat clearDepth() const;
		inline void clearStencil(GLint nClearStencil);
		inline GLint clearStencil() const;
		void clear();
		void render();
		void flush();
	};

	inline void Renderer::needClearColor(bool bNeedClearColor)
	{
		this->bNeedClearColor = bNeedClearColor;
	}

	inline bool Renderer::needClearColor() const
	{
		return this->bNeedClearColor;
	}

	inline void Renderer::needClearDepth(bool bNeedClearDepth)
	{
		this->bNeedClearDepth = bNeedClearDepth;
	}

	inline bool Renderer::needClearDepth() const
	{
		return this->bNeedClearDepth;
	}

	inline void Renderer::needClearStencil(bool bNeedClearStencil)
	{
		this->bNeedClearStencil = bNeedClearStencil;
	}

	inline bool Renderer::needClearStencil() const
	{
		return this->bNeedClearStencil;
	}

	inline void Renderer::clearColor(Color sClearColor)
	{
		this->sClearColor = sClearColor;
	}

	inline Color Renderer::clearColor() const
	{
		return this->sClearColor;
	}

	inline void Renderer::clearDepth(GLfloat nClearDepth)
	{
		this->nClearDepth = nClearDepth;
	}

	inline GLfloat Renderer::clearDepth() const
	{
		return this->nClearDepth;
	}

	inline void Renderer::clearStencil(GLint nClearStencil)
	{
		this->nClearStencil = nClearStencil;
	}

	inline GLint Renderer::clearStencil() const
	{
		return this->nClearStencil;
	}
}

#endif