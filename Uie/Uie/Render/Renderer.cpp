
/*
	2018.07.03
	Created by AcrylicShrimp.
*/

#include "Renderer.h"

#include "../UIContext.h"

namespace Uie::Render
{
	Renderer::Renderer()
	{
		::glewInit();

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glDisable(GL_DEPTH_TEST);
		glDisable(GL_CULL_FACE);
	}

	Renderer::~Renderer()
	{

	}

	void Renderer::clear()
	{
		GLbitfield vColorClearFlag[2]{0, GL_COLOR_BUFFER_BIT};
		GLbitfield vDepthClearFlag[2]{0, GL_DEPTH_BUFFER_BIT};
		GLbitfield vStencilClearFlag[2]{0, GL_STENCIL_BUFFER_BIT};

		::glClear(
			vColorClearFlag[this->bNeedClearColor] |
			vDepthClearFlag[this->bNeedClearDepth] |
			vStencilClearFlag[this->bNeedClearStencil]
		);
	}

	void Renderer::render()
	{
		this->clear();
	}

	void Renderer::flush()
	{
		SwapBuffers(UIContext::current()->attachedWindow()->context());
	}
}