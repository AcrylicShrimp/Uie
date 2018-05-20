
/*
	2018.05.10
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_UIE_RENDER_UNIFORMBINDABLE_H

#define _CLASS_UIE_RENDER_UNIFORMBINDABLE_H

#include "../UieDLL.h"

#include <GL/glew.h>

namespace Uie::Render
{
	class UIE_DLL UniformBindable
	{
	protected:
		mutable bool bNeedBind{true};

	public:
		UniformBindable() = default;
		UniformBindable(const UniformBindable &sSrc) = default;
		virtual ~UniformBindable() = default;

	public:
		UniformBindable &operator=(const UniformBindable &sSrc) = default;

	public:
		inline bool needBind() const;
		inline void bindUniform(GLuint nShaderIdentifier, GLint nUniformLocation) const;

	protected:
		virtual void bind(GLuint nShaderIdentifier, GLint nUniformLocation) const = 0;
	};

	inline bool UniformBindable::needBind() const
	{
		return this->bNeedBind;
	}

	inline void UniformBindable::bindUniform(GLuint nShaderIdentifier, GLint nUniformLocation) const
	{
		if (!this->bNeedBind)
			return;

		this->bNeedBind = false;
		this->bindUniform(nShaderIdentifier, nUniformLocation);
	}
}

#endif