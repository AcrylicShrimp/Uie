
/*
	2018.04.05
	Created by AcrylicShrimp.
*/

#include "WindowMessageHandler.h"

namespace Uie
{
	WindowMessageHandler::WindowMessageHandler(std::initializer_list<UINT> sMessageList) :
		sMessageList(sMessageList)
	{
		//Empty.
	}

	WindowMessageHandler::WindowMessageHandler(const WindowMessageHandler &sSrc) :
		sMessageList(sSrc.sMessageList)
	{
		//Empty.
	}

	WindowMessageHandler &WindowMessageHandler::operator=(const WindowMessageHandler &sSrc)
	{
		if (&sSrc == this)
			return *this;

		this->sMessageList = sSrc.sMessageList;

		return *this;
	}
}