
/*
	2018.04.05
	Created by AcrylicShrimp.
*/

#include "WindowManager.h"
#include "RenderManager.h"
#include "UIManager.h"
#include "Event/EventManager.h"

#include <Windows.h>
#include <GL/glew.h>

BOOL WINAPI DllMain(HINSTANCE hDllInstance, DWORD nReason, LPVOID pReserved)
{
	switch (nReason)
	{
	case DLL_PROCESS_ATTACH:
	{
		Uie::WindowManager::initialize();
		Uie::RenderManager::initialize();
		Uie::UIManager::initialize();
		Uie::Event::EventManager::initialize();
	}
	break;
	case DLL_PROCESS_DETACH:
	{
		Uie::Event::EventManager::finalize();
		Uie::UIManager::finalize();
		Uie::RenderManager::finalize();
		Uie::WindowManager::finalize();
	}
	break;
	default:
		break;
	}

	return TRUE;
}