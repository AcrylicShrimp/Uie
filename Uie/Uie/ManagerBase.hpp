
namespace Uie
{
	template<class T> T *ManagerBase<T>::pInstance = nullptr;

	template<class T> template<class ...P> void ManagerBase<T>::initialize(P &&...tParam)
	{
		if (!ManagerBase<T>::pInstance)
			ManagerBase<T>::pInstance = new T(std::forward<P>(tParam)...);
	}

	template<class T> void ManagerBase<T>::finalize()
	{
		if (ManagerBase<T>::pInstance)
			delete ManagerBase<T>::pInstance;

		ManagerBase<T>::pInstance = nullptr;
	}
}