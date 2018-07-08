
/*
	2018.07.04
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_UIE_RENDER_SHADERCONTAINER_H

#define _CLASS_UIE_RENDER_SHADERCONTAINER_H

#include "../UieDLL.h"

#include "Component/Shader.h"

#include <string>
#include <unordered_map>

namespace Uie::Render
{
	class UIE_DLL ShaderContainer final
	{
	private:

		std::unordered_map<std::string, Component::Shader> sShaderMap;
		
	public:
		ShaderContainer() = default;
		ShaderContainer(const ShaderContainer &sSrc) = delete;
		ShaderContainer(ShaderContainer &&sSrc) = default;
		virtual ~ShaderContainer();
		
	public:
		ShaderContainer &operator=(const ShaderContainer &sSrc) = delete;
		ShaderContainer &operator=(ShaderContainer &&sSrc) = default;
		
	public:
		
	};
}

#endif