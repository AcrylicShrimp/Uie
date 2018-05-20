
/*
	2018.04.05
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_UIE_RENDERMANAGER_H

#define _CLASS_UIE_RENDERMANAGER_H

#include "UieDLL.h"

#include "Color.h"
#include "ManagerBase.h"
#include "UIPlacement.h"
#include "Window.h"
#include "WindowManager.h"
#include "WindowMessageHandler.h"
#include "Render/Context.h"

#include <unordered_map>
#include <Windows.h>
#include <GL/glew.h>

namespace Uie
{
	struct RenderProperties
	{
		Color sClearColor;
	};

	class UIE_DLL RenderManager final : public ManagerBase<RenderManager>, public WindowMessageHandler
	{
	private:
		bool bInitialized;
		std::unordered_map<Window *, RenderProperties> sRenderPropertiesMap;
		
	public:
		RenderManager();
		RenderManager(const RenderManager &sSrc) = delete;
		~RenderManager();
		
	public:
		RenderManager &operator=(const RenderManager &sSrc) = delete;
		
	public:
		void applyRenderProperties(Window *pWindow, const RenderProperties &sRenderProperties);
		void repaint();
		void repaint(Window *pWindow);
		virtual LRESULT handleWindowMessage(Window *pWindow, HWND hWindow, UINT nMessage, WPARAM wParam, LPARAM lParam) override;

	private:
		void render(Window *pWindow);
	};
}

#endif