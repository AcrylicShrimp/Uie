
/*
	2018.04.22
	Created by AcrylicShrimp.
*/

namespace Uie::Render
{
	template<class T> Buffer<T>::Buffer() :
		nSize{0}
	{
		glCreateBuffers(1, &this->nIdentifier);
	}

	template<class T> Buffer<T>::Buffer(std::initializer_list<T> sSrc) :
		Buffer()
	{
		glNamedBufferData(this->nIdentifier, sizeof(T) * (this->nSize = sSrc.size()), sSrc.begin(), GL_DYNAMIC_DRAW);
	}

	template<class T> Buffer<T>::Buffer(const std::vector<T> &sSrc) :
		Buffer()
	{
		glNamedBufferData(this->nIdentifier, sizeof(T) * (this->nSize = sSrc.size()), sSrc.data(), GL_DYNAMIC_DRAW);
	}

	template<class T> Buffer<T>::Buffer(const Buffer<T> &sSrc) :
		Buffer()
	{
		glNamedBufferData(this->nIdentifier, sizeof(T) * (this->nSize = sSrc.nSize), nullptr, GL_DYNAMIC_DRAW);
		glCopyNamedBufferSubData(sSrc.nIdentifier, this->nIdentifier, 0, 0, sizeof(T) * this->nSize);
	}

	template<class T> Buffer<T>::Buffer(Buffer<T> &&sSrc) :
		nIdentifier{sSrc.nIdentifier},
		nSize{sSrc.nSize}
	{
		sSrc.nIdentifier = 0;
		sSrc.nSize = 0;
	}

	template<class T> Buffer<T>::~Buffer()
	{
		if (this->nIdentifier)
			glDeleteBuffers(1, &this->nIdentifier);

		this->nIdentifier = 0;
		this->nSize = 0;
	}

	template<class T> Buffer<T> &Buffer<T>::operator=(std::initializer_list<T> sSrc)
	{
		glNamedBufferData(this->nIdentifier, sizeof(T) * (this->nSize = sSrc.size()), sSrc.begin(), GL_DYNAMIC_DRAW);
		return *this;
	}

	template<class T> Buffer<T> &Buffer<T>::operator=(const std::vector<T> &sSrc)
	{
		glNamedBufferData(this->nIdentifier, sizeof(T) * (this->nSize = sSrc.size()), sSrc.data(), GL_DYNAMIC_DRAW);
		return *this;
	}

	template<class T> Buffer<T> &Buffer<T>::operator=(const Buffer<T> &sSrc)
	{
		if (&sSrc == this)
			return *this;

		glNamedBufferData(this->nIdentifier, sizeof(T) * (this->nSize = sSrc.nSize), nullptr, GL_DYNAMIC_DRAW);
		glCopyNamedBufferSubData(sSrc.nIdentifier, this->nIdentifier, 0, 0, sizeof(T) * this->nSize);

		return *this;
	}

	template<class T> Buffer<T> &Buffer<T>::operator=(Buffer<T> &&sSrc)
	{
		if (&sSrc == this)
			return *this;

		this->~Buffer();

		this->nIdentifier = sSrc.nIdentifier;
		this->nSize = sSrc.nSize;

		sSrc.nIdentifier = 0;
		sSrc.nSize = 0;

		return *this;
	}

	template<class T> void Buffer<T>::insert(std::initializer_list<T> sBuffer, std::size_t nIndex)
	{
		if (nIndex < this->nSize)
			glNamedBufferSubData(this->nIdentifier, nIndex, sizeof(T) * std::min(sBuffer.size(), this->nSize - nIndex), sBuffer.begin());
	}

	template<class T> void Buffer<T>::insert(const std::vector<T> &sBuffer, std::size_t nIndex)
	{
		if (nIndex < this->nSize)
			glNamedBufferSubData(this->nIdentifier, nIndex, sizeof(T) * std::min(sBuffer.size(), this->nSize - nIndex), sBuffer.data());
	}

	template<class T> void Buffer<T>::insert(const Buffer<T> &sBuffer, std::size_t nIndex)
	{
		if (nIndex < this->nSize)
			glCopyBufferSubData(sBuffer.nIdentifier, this->nIdentifier, 0, nIndex, sizeof(T) * std::min(sBuffer.nSize, this->nSize - nIndex));
	}
}