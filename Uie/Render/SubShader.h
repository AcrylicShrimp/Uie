
/*
	2018.04.20
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_UIE_RENDER_SUBSHADER_H

#define _CLASS_UIE_RENDER_SUBSHADER_H

#include "../UieDLL.h"

#include <string>
#include <GL/glew.h>

namespace Uie::Render
{
	enum class SubShaderType : GLenum
	{
		Vertex = GL_VERTEX_SHADER,
		Fragment = GL_FRAGMENT_SHADER,
		Geometry = GL_GEOMETRY_SHADER,
		Compute = GL_COMPUTE_SHADER,
		TessControl = GL_TESS_CONTROL_SHADER,
		TessEvaluation = GL_TESS_EVALUATION_SHADER
	};

	class UIE_DLL SubShader final
	{
	private:
		GLuint nIdentifier;
		GLuint nProgram;
		SubShaderType eType;
		
	public:
		SubShader(GLuint nProgram, SubShaderType eType);
		SubShader(const SubShader &sSrc) = delete;
		SubShader(SubShader &&sSrc);
		~SubShader();
		
	public:
		SubShader &operator=(const SubShader &sSrc) = delete;
		SubShader &operator=(SubShader &&sSrc);
		
	public:
		inline SubShaderType type() const;
		bool compile(const std::string &sSource, std::string *pCompileLog = nullptr);
	};

	inline SubShaderType SubShader::type() const
	{
		return this->eType;
	}
}

#endif