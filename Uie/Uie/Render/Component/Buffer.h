
/*
	2018.04.22
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_UIE_RENDER_COMPONENT_BUFFER_H

#define _CLASS_UIE_RENDER_COMPONENT_BUFFER_H

#include <algorithm>
#include <cstddef>
#include <initializer_list>
#include <utility>
#include <vector>
#include <GL/glew.h>

namespace Uie::Render::Component
{
	class BufferBase
	{
	protected:
		GLuint nIdentifier;

	public:
		BufferBase();
		BufferBase(const BufferBase &sSrc) = delete;
		BufferBase(BufferBase &&sSrc);
		virtual ~BufferBase();

	public:
		BufferBase &operator=(const BufferBase &sSrc) = delete;
		BufferBase &operator=(BufferBase &&sSrc);

	public:
		inline GLuint identifier() const;
		virtual GLsizei elementSize() const = 0;
	};

	inline GLuint BufferBase::identifier() const
	{
		return this->nIdentifier;
	}

	template<class T> class Buffer final : public BufferBase
	{
	protected:
		std::size_t nSize;
		
	public:
		Buffer();
		Buffer(std::initializer_list<T> sSrc);
		Buffer(const std::vector<T> &sSrc);
		Buffer(const Buffer<T> &sSrc);
		Buffer(Buffer<T> &&sSrc);
		~Buffer() = default;
		
	public:
		Buffer<T> &operator=(std::initializer_list<T> sSrc);
		Buffer<T> &operator=(const std::vector<T> &sSrc);
		Buffer<T> &operator=(const Buffer<T> &sSrc);
		Buffer<T> &operator=(Buffer<T> &&sSrc);
		
	public:
		inline std::size_t size() const;
		virtual GLsizei elementSize() const override;
		void insert(std::initializer_list<T> sBuffer, std::size_t nIndex);
		void insert(const std::vector<T> &sBuffer, std::size_t nIndex);
		void insert(const Buffer<T> &sBuffer, std::size_t nIndex);
	};

	template<class T> inline GLuint Buffer<T>::size() const
	{
		return this->nSize;
	}
}

#include "Buffer.hpp"

#endif