
/*
	2018.04.22
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_UIE_RENDER_SHADERINPUT_H

#define _CLASS_UIE_RENDER_SHADERINPUT_H

#include "../UieDLL.h"

#include "Buffer.h"
#include "ShaderAttrib.h"

#include <string>
#include <unordered_map>
#include <utility>
#include <vector>
#include <GL/glew.h>

namespace Uie::Render
{
	class ShaderInput final
	{
	private:
		GLuint nIdentifier;
		std::unordered_map<GLuint, ShaderAttrib> sAttribMap;
		std::unordered_map<GLuint, const BufferBase *> sBufferMap;
		std::unordered_map<const BufferBase *, std::vector<GLuint>> sBufferIndexMap;
		
	public:
		ShaderInput();
		ShaderInput(const ShaderInput &sSrc) = delete;
		ShaderInput(ShaderInput &&sSrc);
		~ShaderInput();
		
	public:
		ShaderInput &operator=(const ShaderInput &sSrc) = delete;
		ShaderInput &operator=(ShaderInput &&sSrc);
		ShaderAttrib *operator[](GLuint nAttribIndex);
		const ShaderAttrib *operator[](GLuint nAttribIndex) const;
		
	public:
		void use() const;
		void disable(GLuint nAttribIndex);
		void attach(GLuint nBufferIndex, const BufferBase *pBufferBase, GLintptr nOffset = 0, GLsizei nStride = 0, GLuint nInstancePerAdvance = 0);
		void detach(GLuint nBufferIndex);
		void detach(const BufferBase *pBufferBase);
	};
}

#endif