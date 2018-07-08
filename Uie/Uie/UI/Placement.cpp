
/*
	2018.07.05
	Created by AcrylicShrimp.
*/

#include "Placement.h"

namespace Uie::UI
{
	Element *Placement::find(const std::string &sName)
	{
		auto iIndex{this->sElementMap.find(sName)};

		return iIndex == this->sElementMap.cend() ? nullptr : iIndex->second.get();
	}

	const Element *Placement::find(const std::string &sName) const
	{
		auto iIndex{this->sElementMap.find(sName)};

		return iIndex == this->sElementMap.cend() ? nullptr : iIndex->second.get();
	}

	void Placement::clear()
	{
		this->sElementMap.clear();
		this->sRoot.clear();
	}

	void Placement::remove(const std::string &sName)
	{
		auto iIndex{this->sElementMap.find(sName)};

		if (iIndex == this->sElementMap.cend())
			return;

		this->sRoot.remove(iIndex->second.get());
		this->sElementMap.erase(iIndex);
	}

	void Placement::update()
	{
		this->sRoot.update();
	}

	void Placement::render()
	{
		this->sRoot.render();
	}

	void Placement::iterate(Order eOrder, std::function<bool(Element *)> fAction)
	{
		switch (eOrder)
		{
		case Order::BackToFront:
		{
			this->sRoot.reorderIfNeeded();

			for (auto iIndex{this->sRoot.begin()}, iEnd{this->sRoot.end()}; iIndex < iEnd; ++iIndex)
				if (fAction(*iIndex))
					break;
		}
		break;
		case Order::FrontToBack:
		{
			this->sRoot.reorderIfNeeded();

			for (auto iIndex{this->sRoot.rbegin()}, iEnd{this->sRoot.rend()}; iIndex < iEnd; ++iIndex)
				if (fAction(*iIndex))
					break;
		}
		break;
		default:
			break;
		}
	}
}