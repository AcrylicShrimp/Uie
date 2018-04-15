
/*
	2018.04.05
	Created by AcrylicShrimp.
*/

#include "RenderManager.h"

namespace Uie
{
	RenderManager::RenderManager() :
		WindowMessageHandler({WM_UIE_CONTEXT_CREAT, WM_UIE_CONTEXT_DESTROY, WM_UIE_OPENGL_CONTEXT_CREAT, WM_UIE_LINK_CONTEXT, WM_ERASEBKGND, WM_PAINT}),
		bInitialized{false}
	{
		Window::registerGlobalHandler(this);
	}

	RenderManager::~RenderManager()
	{
		Window::unregisterGlobalHandler(this);
	}

	void RenderManager::applyRenderProperties(Window *pWindow, const RenderProperties &sRenderProperties)
	{
		this->sRenderPropertiesMap[pWindow] = sRenderProperties;
	}

	void RenderManager::repaint(Window *pWindow)
	{
		RedrawWindow(pWindow->windowHandle(), nullptr, nullptr, RDW_INVALIDATE);
	}

	LRESULT RenderManager::handleWindowMessage(Window *pWindow, HWND hWindow, UINT nMessage, WPARAM wParam, LPARAM lParam)
	{
		switch (nMessage)
		{
		case WM_UIE_CONTEXT_CREAT:
		{
			this->sRenderPropertiesMap.emplace(pWindow, RenderProperties{});
		}
		break;
		case WM_UIE_CONTEXT_DESTROY:
		{
			this->sRenderPropertiesMap.erase(pWindow);
		}
		break;
		case WM_UIE_OPENGL_CONTEXT_CREAT:
		{
			this->bInitialized = false;
		}
		break;
		case WM_UIE_LINK_CONTEXT:
		{
			if (!this->bInitialized && !glewInit())
				this->bInitialized = true;
		}
		break;
		case WM_ERASEBKGND:
			return TRUE;
		case WM_PAINT:
		{
			this->render(pWindow);
			ValidateRect(hWindow, nullptr);
		}
		break;
		default:
			break;
		}

		return 0;
	}

	void RenderManager::render(Window *pWindow)
	{
		auto iRenderPropertiesIndex{this->sRenderPropertiesMap.find(pWindow)};

		if (iRenderPropertiesIndex == this->sRenderPropertiesMap.cend())
			return;

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glDisable(GL_DEPTH_TEST);
		glDisable(GL_CULL_FACE);

		glViewport(0, 0, pWindow->windowInfo().nClientWidth, pWindow->windowInfo().nClientHeight);

		const auto &sRenderProperties{iRenderPropertiesIndex->second};
		glClearColor(
			sRenderProperties.sClearColor.nR,
			sRenderProperties.sClearColor.nG,
			sRenderProperties.sClearColor.nB,
			sRenderProperties.sClearColor.nA);
		glClearDepth(1.f);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		auto pPlacement{WindowManager::instance().findPlacement(pWindow)};

		if (pPlacement)
		{
			pPlacement->updateAll();
			pPlacement->renderAll();
		}

		SwapBuffers(pWindow->windowInfo().hDeviceContext);
	}
}