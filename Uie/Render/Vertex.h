
/*
	2018.04.19
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_UIE_RENDER_VERTEX_H

#define _CLASS_UIE_RENDER_VERTEX_H

#include "../UieDLL.h"

#include <algorithm>
#include <cstddef>
#include <initializer_list>
#include <utility>
#include <vector>
#include <GL/glew.h>

namespace Uie::Render
{
	class UIE_DLL Vertex final
	{
	private:
		GLuint nIdentifier;
		std::size_t nSize;
		
	public:
		Vertex();
		Vertex(std::initializer_list<float> sSrc);
		Vertex(const std::vector<float> &sSrc);
		Vertex(const Vertex &sSrc);
		Vertex(Vertex &&sSrc);
		~Vertex();
		
	public:
		Vertex &operator=(std::initializer_list<float> sSrc);
		Vertex &operator=(const std::vector<float> &sSrc);
		Vertex &operator=(const Vertex &sSrc);
		Vertex &operator=(Vertex &&sSrc);
		
	public:
		inline GLuint identifier() const;
		inline std::size_t size() const;
		void insert(std::initializer_list<float> sVertex, std::size_t nIndex);
		void insert(const std::vector<float> &sVertex, std::size_t nIndex);
		void insert(const Vertex &sVertex, std::size_t nIndex);
	};

	inline GLuint Vertex::identifier() const
	{
		return this->nIdentifier;
	}

	inline std::size_t Vertex::size() const
	{
		return this->nSize;
	}
}

#endif