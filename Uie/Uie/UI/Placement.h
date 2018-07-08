
/*
	2018.07.05
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_UIE_UI_PLACEMENT_H

#define _CLASS_UIE_UI_PLACEMENT_H

#include "../UieDLL.h"

#include "Element.h"
#include "Root.h"

#include <cstdint>
#include <functional>
#include <memory>
#include <string>
#include <unordered_map>
#include <utility>

namespace Uie::UI
{
	class UIE_DLL Placement final
	{
	public:
		enum class Order
		{
			BackToFront,
			FrontToBack
		};

	private:
		std::unordered_map<std::string, std::unique_ptr<Element>> sElementMap;
		Root sRoot;

	public:
		Placement() = default;
		Placement(const Placement &sSrc) = delete;
		Placement(Placement &&sSrc) = default;
		~Placement() = default;

	public:
		Placement &operator=(const Placement &sSrc) = delete;
		Placement &operator=(Placement &&sSrc) = default;

	public:
		template<class T, class ...P> T *create(const std::string &sName, P &&...sParam);
		template<class T> T *find(const std::string &sName);
		template<class T> const T *find(const std::string &sName) const;
		Element *find(const std::string &sName);
		const Element *find(const std::string &sName) const;
		void clear();
		void remove(const std::string &sName);
		void update();
		void render();
		void iterate(Order eOrder, std::function<bool(Element *)> fAction);
	};

	template<class T, class ...P> T *Placement::create(const std::string &sName, P &&...sParam)
	{
		if (this->sElementMap.find(sName) != this->sElementMap.cend())
			return nullptr;

		return static_cast<T *>((this->sElementMap[sName] = std::make_unique<T>(&this->sRoot, sName, std::forward<P>(sParam)...)).get());
	}

	template<class T> T *Placement::find(const std::string &sName)
	{
		return static_cast<T *>(this->find(sName));
	}

	template<class T> const T *Placement::find(const std::string &sName) const
	{
		return static_cast<const T *>(this->find(sName));
	}
}

#endif