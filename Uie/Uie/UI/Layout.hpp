
namespace Uie::UI
{
	template<class T> Layout<T>::Layout(Root *pRoot, const std::string &sName) :
		Hierarchy(pRoot, sName)
	{
		//Empty.
	}

	template<class T> void Layout<T>::addChild(Element *pChild)
	{
		this->Hierarchy::addChild(pChild);

		if (pChild->root() != this->pRoot)
			return;

		this->sPropertiesList.emplace_back();
	}

	template<class T> void Layout<T>::clearChild()
	{
		this->Hierarchy::clearChild();

		this->sPropertiesList.clear();
	}

	template<class T> void Layout<T>::removeChild(Element *pChild)
	{
		const auto iIndex{std::find(this->sChildList.cbegin(), this->sChildList.cend(), pChild)};

		if (iIndex != this->sChildList.cend())
			this->sPropertiesList.erase(this->sPropertiesList.cbegin() + std::distance(this->sChildList.cbegin(), iIndex));

		this->Hierarchy::removeChild(pChild);
	}

	template<class T> void Layout<T>::update()
	{
		this->Hierarchy::update();

		std::size_t nIndex{0};

		for (auto pChild : this->sChildList)
			this->updateChild(pChild, this->sPropertiesList[nIndex++]);
	}

	template<class T> void Layout<T>::render()
	{
		this->Hierarchy::render();
	}
}