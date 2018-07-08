
/*
	2018.07.05
	Created by AcrylicShrimp.
*/

#include "EventHandler.h"

namespace Uie::Event
{
	void EventHandler::addHandler(Handler fHandler)
	{
		this->sDefaultHandlerList.emplace_back(fHandler);
	}

	void EventHandler::addHandler(const std::string &sIdentifier, Handler fHandler)
	{
		this->sHandlerMap[sIdentifier].emplace_back(fHandler);
	}

	void EventHandler::clearHandler()
	{
		this->sHandlerMap.clear();
		this->sDefaultHandlerList.clear();
	}

	void EventHandler::removeHandler(Handler fHandler)
	{
		auto iIndex{this->findHandlerIterator(this->sDefaultHandlerList, fHandler)};

		if (iIndex != this->sDefaultHandlerList.cend())
			this->sDefaultHandlerList.erase(iIndex);
	}

	void EventHandler::removeHandler(const std::string &sIdentifier)
	{
		this->sHandlerMap.erase(sIdentifier);
	}

	void EventHandler::removeHandler(const std::string &sIdentifier, Handler fHandler)
	{
		auto iMapIndex{this->sHandlerMap.find(sIdentifier)};

		if (iMapIndex == this->sHandlerMap.cend())
			return;

		auto iListIndex{this->findHandlerIterator(iMapIndex->second, fHandler)};

		if (iListIndex != iMapIndex->second.cend())
			iMapIndex->second.erase(iListIndex);
	}

	bool EventHandler::handleEvent(const std::string &sIdentifier, void *pParam) const
	{
		auto iMapIndex{this->sHandlerMap.find(sIdentifier)};
		return this->handleEvent(iMapIndex == this->sHandlerMap.cend() ? this->sDefaultHandlerList : iMapIndex->second, sIdentifier, pParam);
	}

	bool EventHandler::handleEvent(const std::vector<Handler> &sHandlerList, const std::string &sIdentifier, void *pParam) const
	{
		auto bResult{false};

		for (auto fEventHandler : sHandlerList)
			bResult = bResult || fEventHandler(sIdentifier, pParam);

		return bResult;
	}

	std::vector<EventHandler::Handler>::const_iterator EventHandler::findHandlerIterator(const std::vector<Handler> &sHandlerList, Handler fHandler) const
	{
		for (auto iIndex{sHandlerList.cbegin()}, iEnd{sHandlerList.cend()}; iIndex != iEnd; ++iIndex)
			if (fHandler.target<bool(const std::string &, void *)>() == iIndex->target<bool(const std::string &, void *)>())
				return iIndex;

		return sHandlerList.cend();
	}
}