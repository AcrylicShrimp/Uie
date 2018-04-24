
/*
	2018.04.22
	Created by AcrylicShrimp.
*/

#ifndef _INTERFACE_UIE_RENDER_ISHADERINPUT_H

#define _INTERFACE_UIE_RENDER_ISHADERINPUT_H

#include "../UieDLL.h"

#include <GL/glew.h>

namespace Uie::Render
{
	class UIE_DLL IShaderInput
	{
	protected:
		bool bDirty{true};

	public:
		IShaderInput() = default;
		IShaderInput(const IShaderInput &sSrc) = default;
		virtual ~IShaderInput() = default;
		
	public:
		IShaderInput &operator=(const IShaderInput &sSrc) = default;

	public:
		inline bool dirty() const;
		inline void dirty(bool bDirty);

	};

	inline bool IShaderInput::dirty() const
	{
		return this->bDirty;
	}

	inline void IShaderInput::dirty(bool bDirty)
	{
		this->bDirty = bDirty;
	}
}

#endif