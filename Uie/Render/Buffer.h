
/*
	2018.04.22
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_UIE_RENDER_BUFFER_H

#define _CLASS_UIE_RENDER_BUFFER_H

#include <algorithm>
#include <cstddef>
#include <initializer_list>
#include <vector>
#include <GL/glew.h>

namespace Uie::Render
{
	template<class T> class Buffer final
	{
	private:
		GLuint nIdentifier;
		std::size_t nSize;
		
	public:
		Buffer();
		Buffer(std::initializer_list<T> sSrc);
		Buffer(const std::vector<T> &sSrc);
		Buffer(const Buffer<T> &sSrc);
		Buffer(Buffer<T> &&sSrc);
		~Buffer();
		
	public:
		Buffer<T> &operator=(std::initializer_list<T> sSrc);
		Buffer<T> &operator=(const std::vector<T> &sSrc);
		Buffer<T> &operator=(const Buffer<T> &sSrc);
		Buffer<T> &operator=(Buffer<T> &&sSrc);
		
	public:
		inline GLuint identifier() const;
		inline std::size_t size() const;
		void insert(std::initializer_list<T> sBuffer, std::size_t nIndex);
		void insert(const std::vector<T> &sBuffer, std::size_t nIndex);
		void insert(const Buffer<T> &sBuffer, std::size_t nIndex);
	};

	template<class T> inline GLuint Buffer<T>::identifier() const
	{
		return this->nIdentifier;
	}

	template<class T> inline GLuint Buffer<T>::size() const
	{
		return this->nSize;
	}
}

#include "Buffer.hpp"

#endif