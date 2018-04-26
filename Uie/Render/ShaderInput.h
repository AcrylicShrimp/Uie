
/*
	2018.04.22
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_UIE_RENDER_SHADERINPUT_H

#define _CLASS_UIE_RENDER_SHADERINPUT_H

#include "../UieDLL.h"

#include "Buffer.h"
#include "ShaderAttrib.h"

#include <functional>
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
		std::unordered_map<GLuint, const BufferBase *> sAttribBufferMap;
		std::unordered_map<const BufferBase *, std::vector<GLuint>> sAttribBufferIndexMap;
		std::unordered_map<std::string, GLuint> sUniformMap;
		std::unordered_map<GLuint, const BufferBase *> sUniformBufferMap;
		std::unordered_map<const BufferBase *, std::vector<GLuint>> sUniformBufferIndexMap;
		
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
		void attachAttrib(const BufferBase *pBufferBase, GLuint nBufferIndex, GLint nElementPerVertex, GLintptr nOffset = 0, GLsizei nStride = 0, GLuint nInstancePerAdvance = 0);
		void detachAttrib(GLuint nBufferIndex);
		void detachAttrib(const BufferBase *pBufferBase);
		void attachUniform(const BufferBase *pBufferBase, GLuint nBufferIndex);
		void detachUniform(GLuint nBufferIndex);
		void detachUniform(const BufferBase *pBufferBase);
		void enableUniform(const std::string &sUniformName, GLuint nBufferIndex);
		void disableUniform(const std::string &sUniformName);
		void activateUniform(std::function<void(const std::string &, GLuint)> fActivator) const;
	};
}

#endif