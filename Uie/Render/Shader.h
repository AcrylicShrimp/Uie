
/*
	2018.04.20
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_UIE_RENDER_SHADER_H

#define _CLASS_UIE_RENDER_SHADER_H

#include "../UieDLL.h"

#include "SubShader.h"

#include <string>
#include <utility>
#include <vector>
#include <GL/glew.h>

namespace Uie::Render
{
	class UIE_DLL Shader final
	{
	private:
		GLuint nIdentifier;
		std::vector<SubShader> sSubShaderList;
		
	public:
		Shader();
		Shader(const Shader &sSrc) = delete;
		Shader(Shader &&sSrc);
		~Shader();
		
	public:
		Shader &operator=(const Shader &sSrc) = delete;
		Shader &operator=(Shader &&sSrc);
		SubShader &operator[](SubShaderType eType);
		
	public:
		bool link(std::string *pLinkLog = nullptr);
		void use();
	};
}

#endif