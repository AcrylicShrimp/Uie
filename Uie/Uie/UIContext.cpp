
/*
	2018.07.02
	Created by AcrylicShrimp.
*/

#include "UIContext.h"

namespace Uie
{
	std::unordered_map<HANDLE, UIContext *> UIContext::sThreadRenderingContextMap;
	std::unordered_map<Window *, UIContext *> UIContext::sWindowRenderingContextMap;

	UIContext::UIContext() :
		WindowMessageHandler{WM_DESTROY, WM_SIZE, WM_SIZING, WM_PAINT, WM_ERASEBKGND}
	{
		//Empty.
	}

	void UIContext::destroy()
	{
		if (this->created())
		{
			this->pPlacement = nullptr;
			this->sPlacementMap.clear();
		}

		this->RenderingContext::destroy();
	}

	void UIContext::detach()
	{
		if (this->attached())
		{
			this->pAttachedWindow->unregisterHandler(this);

			UIContext::sThreadRenderingContextMap.erase(this->hAttachedThread);
			UIContext::sWindowRenderingContextMap.erase(this->pAttachedWindow);
		}

		this->RenderingContext::detach();
	}

	bool UIContext::attach(Window *pWindow)
	{
		if (!this->RenderingContext::attach(pWindow))
			return false;

		UIContext::sThreadRenderingContextMap[this->hAttachedThread = ::GetCurrentThread()] = this;
		UIContext::sWindowRenderingContextMap[this->pAttachedWindow = pWindow] = this;

		this->pAttachedWindow->registerHandler(this);

		return true;
	}

	void UIContext::inactivePlacement()
	{
		this->pPlacement = nullptr;
	}

	void UIContext::activePlacement(const std::string &sName)
	{
		auto pPlacement{this->findPlacement(sName)};

		if (pPlacement)
			this->pPlacement = pPlacement;
	}

	UI::Placement *UIContext::createPlacement(const std::string &sName)
	{
		return &this->sPlacementMap[sName];
	}

	UI::Placement *UIContext::findPlacement(const std::string &sName)
	{
		auto iIndex{this->sPlacementMap.find(sName)};

		return iIndex == this->sPlacementMap.cend() ? nullptr : &iIndex->second;
	}

	const UI::Placement *UIContext::findPlacement(const std::string &sName) const
	{
		auto iIndex{this->sPlacementMap.find(sName)};

		return iIndex == this->sPlacementMap.cend() ? nullptr : &iIndex->second;
	}

	void UIContext::removePlacement(const std::string &sName)
	{
		this->sPlacementMap.erase(sName);
	}

	LRESULT UIContext::handleWindowMessage(Window *pWindow, HWND hWindow, UINT nMessage, WPARAM wParam, LPARAM lParam)
	{
		LRESULT sRenderingContextResult{this->RenderingContext::handleWindowMessage(pWindow, hWindow, nMessage, wParam, lParam)};

		if (!this->attached())
			return sRenderingContextResult;

		if (pWindow != this->pAttachedWindow)
			return sRenderingContextResult;

		switch (nMessage)
		{
		case WM_DESTROY:
		{
			if (this->attached())
			{
				UIContext::sThreadRenderingContextMap.erase(this->hAttachedThread);
				UIContext::sWindowRenderingContextMap.erase(this->pAttachedWindow);
			}

			this->RenderingContext::detach();
		}
		break;
		default:
			return sRenderingContextResult;
		}

		return sRenderingContextResult == Window::NoHandler ? 0 : sRenderingContextResult;
	}

	UIContext *UIContext::find(HANDLE hThread)
	{
		auto iIndex{UIContext::sThreadRenderingContextMap.find(hThread)};

		return iIndex == UIContext::sThreadRenderingContextMap.cend() ? nullptr : iIndex->second;
	}

	UIContext *UIContext::find(Window *pWindow)
	{
		auto iIndex{UIContext::sWindowRenderingContextMap.find(pWindow)};

		return iIndex == UIContext::sWindowRenderingContextMap.cend() ? nullptr : iIndex->second;
	}

	void UIContext::update()
	{
		if (this->pPlacement)
			this->pPlacement->update();
	}

	void UIContext::render()
	{
		this->pRenderer->clear();

		if (this->pPlacement)
			this->pPlacement->render();
	}
}