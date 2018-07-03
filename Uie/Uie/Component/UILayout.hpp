
namespace Uie::Component
{
	template<class T> UILayout<T>::UILayout(UIPlacement *pPlacement, const std::wstring &sName) :
		UIElement(pPlacement, sName)
	{
		//Empty.
	}

	template<class T> T *UILayout<T>::addChild(UIElement *pChild)
	{
		if (pChild->placement() != this->pPlacement)
			return nullptr;

		for (auto iIndex{this->sChildList.begin()}, iEnd{this->sChildList.end()}; iIndex != iEnd; ++iIndex)
			if (std::get<0>(*iIndex) == pChild)
				return std::get<1>(*iIndex).get();

		this->sChildList.emplace_back(pChild, std::make_unique<T>());
		this->pPlacement->unrootElement(pChild);

		return std::get<1>(this->sChildList.back()).get();
	}

	template<class T> void UILayout<T>::addChild(UIElement *pChild, const T &tLayoutProperties)
	{
		if (pChild->placement() != this->pPlacement)
			return;

		for (auto iIndex{this->sChildList.begin()}, iEnd{this->sChildList.end()}; iIndex != iEnd; ++iIndex)
			if (std::get<0>(*iIndex) == pChild)
			{
				*std::get<1>(*iIndex) = tLayoutProperties;
				return;
			}

		this->sChildList.emplace_back(pChild, std::make_unique<T>(tLayoutProperties));
		this->pPlacement->unrootElement(pChild);
	}

	template<class T> void UILayout<T>::removeChild(UIElement *pChild)
	{
		if (pChild->placement() != this->pPlacement)
			return;

		for (auto iIndex{this->sChildList.cbegin()}, iEnd{this->sChildList.cend()}; iIndex != iEnd; ++iIndex)
			if (std::get<0>(*iIndex) == pChild)
			{
				this->sChildList.erase(iIndex);
				this->pPlacement->rootElement(pChild);
				return;
			}
	}

	template<class T> T *UILayout<T>::obtainLayoutProperties(UIElement *pChild)
	{
		if (pChild->placement() != this->pPlacement)
			return nullptr;

		for (auto iIndex{this->sChildList.begin()}, iEnd{this->sChildList.end()}; iIndex != iEnd; ++iIndex)
			if (std::get<0>(*iIndex) == pChild)
				return std::get<1>(*iIndex).get();

		return nullptr;
	}

	template<class T> const T *UILayout<T>::obtainLayoutProperties(UIElement *pChild) const
	{
		if (pChild->placement() != this->pPlacement)
			return nullptr;

		for (auto iIndex{this->sChildList.cbegin()}, iEnd{this->sChildList.cend()}; iIndex != iEnd; ++iIndex)
			if (std::get<0>(*iIndex) == pChild)
				return std::get<1>(*iIndex).get();

		return nullptr;
	}

	template<class T> void UILayout<T>::update()
	{
		for (auto iIndex{this->sChildList.begin()}, iEnd{this->sChildList.end()}; iIndex != iEnd; ++iIndex)
			this->updateChild(std::get<0>(*iIndex), *std::get<1>(*iIndex));
	}
}