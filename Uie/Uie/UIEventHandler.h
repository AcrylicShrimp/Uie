
/*
	2018.04.13
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_UIE_UIEVENTHANDLER_H

#define _CLASS_UIE_UIEVENTHANDLER_H

#include "UieDLL.h"

#include <functional>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

namespace Uie
{
	using SubEventHandler = std::function<bool(const std::string &, void *)>;

	class UIE_DLL UIEventHandler
	{
	protected:
		std::unordered_map<std::string, std::vector<SubEventHandler>> sHandlerMap;
		std::vector<SubEventHandler> sDefaultHandlerList;
		
	public:
		UIEventHandler() = default;
		UIEventHandler(const UIEventHandler &sSrc);
		UIEventHandler(UIEventHandler &&sSrc);
		virtual ~UIEventHandler() = default;
		
	public:
		UIEventHandler &operator=(const UIEventHandler &sSrc);
		UIEventHandler &operator=(UIEventHandler &&sSrc);
		
	public:
		void addHandler(SubEventHandler fHandler);
		void addHandler(const std::string &sIdentifier, SubEventHandler fHandler);
		void removeHandlerAll();
		void removeHandlerAll(const std::string &sIdentifier);
		void removeHandler(SubEventHandler fHandler);
		void removeHandler(const std::string &sIdentifier, SubEventHandler fHandler);
		bool handleEvent(const std::string &sIdentifier, void *pParam) const;

	private:
		bool handleEvent(const std::vector<SubEventHandler> &sHandlerList, const std::string &sIdentifier, void *pParam) const;
		std::vector<SubEventHandler>::const_iterator findIterator(const std::vector<SubEventHandler> &sHandlerList, SubEventHandler fHandler) const;
	};
}

#endif