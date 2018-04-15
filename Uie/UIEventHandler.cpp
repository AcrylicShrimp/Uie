
/*
	2018.04.13
	Created by AcrylicShrimp.
*/

#include "UIEventHandler.h"

namespace Uie
{
	UIEventHandler::UIEventHandler(const UIEventHandler &sSrc) :
		sHandlerMap{sSrc.sHandlerMap},
		sDefaultHandlerList{sSrc.sDefaultHandlerList}
	{
		//Empty.
	}

	UIEventHandler::UIEventHandler(UIEventHandler &&sSrc) :
		sHandlerMap{std::move(sSrc.sHandlerMap)},
		sDefaultHandlerList{std::move(sSrc.sDefaultHandlerList)}
	{
		//Empty.
	}

	UIEventHandler &UIEventHandler::operator=(const UIEventHandler &sSrc)
	{
		if (&sSrc == this)
			return *this;

		this->sHandlerMap = sSrc.sHandlerMap;
		this->sDefaultHandlerList = sSrc.sDefaultHandlerList;

		return *this;
	}

	UIEventHandler &UIEventHandler::operator=(UIEventHandler &&sSrc)
	{
		if (&sSrc == this)
			return *this;

		this->sHandlerMap = std::move(sSrc.sHandlerMap);
		this->sDefaultHandlerList = std::move(sSrc.sDefaultHandlerList);

		return *this;
	}

	void UIEventHandler::addHandler(SubEventHandler fHandler)
	{
		this->sDefaultHandlerList.emplace_back(fHandler);
	}

	void UIEventHandler::addHandler(const std::string &sIdentifier, SubEventHandler fHandler)
	{
		this->sHandlerMap[sIdentifier].emplace_back(fHandler);
	}

	void UIEventHandler::removeHandlerAll()
	{
		this->sHandlerMap.clear();
		this->sDefaultHandlerList.clear();
	}

	void UIEventHandler::removeHandlerAll(const std::string &sIdentifier)
	{
		this->sHandlerMap.erase(sIdentifier);
	}

	void UIEventHandler::removeHandler(SubEventHandler fHandler)
	{
		auto iIndex{this->findIterator(this->sDefaultHandlerList, fHandler)};

		if (iIndex != this->sDefaultHandlerList.cend())
			this->sDefaultHandlerList.erase(iIndex);
	}

	void UIEventHandler::removeHandler(const std::string &sIdentifier, SubEventHandler fHandler)
	{
		auto iMapIndex{this->sHandlerMap.find(sIdentifier)};

		if (iMapIndex == this->sHandlerMap.cend())
			return;

		auto iListIndex{this->findIterator(iMapIndex->second, fHandler)};

		if (iListIndex != iMapIndex->second.cend())
			iMapIndex->second.erase(iListIndex);
	}

	bool UIEventHandler::handleEvent(const std::string &sIdentifier, void *pParam) const
	{
		auto iMapIndex{this->sHandlerMap.find(sIdentifier)};
		return this->handleEvent(iMapIndex == this->sHandlerMap.cend() ? this->sDefaultHandlerList : iMapIndex->second, sIdentifier, pParam);
	}

	bool UIEventHandler::handleEvent(const std::vector<SubEventHandler> &sHandlerList, const std::string &sIdentifier, void *pParam) const
	{
		auto bResult{false};

		for (auto fEventHandler : sHandlerList)
			bResult = fEventHandler(sIdentifier, pParam) || bResult;

		return bResult;
	}

	std::vector<SubEventHandler>::const_iterator UIEventHandler::findIterator(const std::vector<SubEventHandler> &sHandlerList, SubEventHandler fHandler) const
	{
		for (auto iIndex{sHandlerList.cbegin()}, iEnd{sHandlerList.cend()}; iIndex != iEnd; ++iIndex)
			if (fHandler.target<bool(const std::string &, void *)>() == iIndex->target<bool(const std::string &, void *)>())
				return iIndex;

		return sHandlerList.cend();
	}
}