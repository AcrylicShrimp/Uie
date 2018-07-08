
/*
	2018.07.05
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_UIE_EVENT_EVENTHANDLER_H

#define _CLASS_UIE_EVENT_EVENTHANDLER_H

#include "../UieDLL.h"

#include <functional>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

namespace Uie::Event
{
	class UIE_DLL EventHandler
	{
	public:
		using Handler = std::function<bool(const std::string &, void *)>;

	protected:
		std::unordered_map<std::string, std::vector<Handler>> sHandlerMap;
		std::vector<Handler> sDefaultHandlerList;
		
	public:
		EventHandler() = default;
		EventHandler(const EventHandler &sSrc) = default;
		EventHandler(EventHandler &&sSrc) = default;
		virtual ~EventHandler() = default;
		
	public:
		EventHandler &operator=(const EventHandler &sSrc) = default;
		EventHandler &operator=(EventHandler &&sSrc) = default;
		
	public:
		void addHandler(Handler fHandler);
		void addHandler(const std::string &sIdentifier, Handler fHandler);
		void clearHandler();
		void removeHandler(Handler fHandler);
		void removeHandler(const std::string &sIdentifier);
		void removeHandler(const std::string &sIdentifier, Handler fHandler);
		bool handleEvent(const std::string &sIdentifier, void *pParam) const;

	private:
		bool handleEvent(const std::vector<Handler> &sHandlerList, const std::string &sIdentifier, void *pParam) const;
		std::vector<Handler>::const_iterator findHandlerIterator(const std::vector<Handler> &sHandlerList, Handler fHandler) const;
	};
}

#endif