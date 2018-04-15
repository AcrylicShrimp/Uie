
/*
	2018.04.05
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_UIE_MANAGERBASE_H

#define _CLASS_UIE_MANAGERBASE_H

#include <cassert>
#include <utility>

namespace Uie
{
	template<class T> class ManagerBase
	{
	private:
		static T *pInstance;

	public:
		ManagerBase() = default;
		ManagerBase(const ManagerBase &sSrc) = default;
		virtual ~ManagerBase() = default;

	public:
		ManagerBase &operator=(const ManagerBase &sSrc) = default;

	public:
		inline static T &instance();
		template<class ...P> static void initialize(P &&...tParam);
		static void finalize();
	};

	template<class T> inline T &ManagerBase<T>::instance()
	{
		assert(ManagerBase<T>::pInstance);
		return *ManagerBase<T>::pInstance;
	}
}

#include "ManagerBase.hpp"

#endif