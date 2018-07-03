
/*
	2018.04.05
	Created by AcrylicShrimp.
*/

#include "../Uie/Uie/Color.h"

#include "../Uie/Uie/Window.h"
#include "../Uie/Uie/WindowManager.h"
#include "../Uie/Uie/WindowMessageHandler.h"

#include "../Uie/Uie/RenderManager.h"

#include "../Uie/Uie/UIManager.h"

#include "../Uie/Uie/Component/UICanvasLayout.h"
#include "../Uie/Uie/Component/UITest.h"

#include <Windows.h>

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR pCmdLine, int nCmdShow)
{
	RECT sWorkArea;
	SystemParametersInfo(SPI_GETWORKAREA, 0, &sWorkArea, 0);

	auto nWidth{sWorkArea.right - sWorkArea.left};
	auto nHeight{sWorkArea.bottom - sWorkArea.top};

	Uie::Window::Attribute sAttribute;
	sAttribute.nX = nWidth / 4;
	sAttribute.nY = nHeight / 4;
	sAttribute.nWidth = nWidth / 2;
	sAttribute.nHeight = nHeight / 2;
	sAttribute.eSizingMode = Uie::Window::SizingMode::ClientAreaOnly;
	sAttribute.hMenu = nullptr;
	sAttribute.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
	sAttribute.hCursor = LoadCursor(nullptr, IDC_ARROW);
	sAttribute.hBackgroundBrush = nullptr;
	sAttribute.hParentWindow = nullptr;
	sAttribute.pMenuName = nullptr;
	sAttribute.sClassName = L"Uie Basic Example";
	sAttribute.sTitleText = L"Uie Basic Example";
	sAttribute.eClassStyle = Uie::combineEnum(Uie::Window::ClassStyle::OwnDeviceContext, Uie::Window::ClassStyle::HorizontalRedraw, Uie::Window::ClassStyle::VerticalRedraw);
	sAttribute.eStyle = Uie::combineEnum(Uie::Window::Style::TitledWindow);
	sAttribute.eExtendedStyle = Uie::combineEnum(Uie::Window::ExtendedStyle::Empty);
	sAttribute.pExtraPointer = nullptr;

	Uie::Window sWindow;
	sWindow.create(sAttribute);

	Uie::RenderProperties sProperties;
	sProperties.sClearColor = 0x000000FF;
	Uie::RenderManager::instance().applyRenderProperties(&sWindow, sProperties);

	auto pPlacement{Uie::UIManager::instance().instantiate(L"main")};
	Uie::WindowManager::instance().linkPlacement(&sWindow, pPlacement);

	auto pTestElement1{pPlacement->instantiate<Uie::Component::UITest>(L"test_element_1")};
	auto pTestElement2{pPlacement->instantiate<Uie::Component::UITest>(L"test_element_2")};
	auto pTestElement3{pPlacement->instantiate<Uie::Component::UITest>(L"test_element_3")};
	auto pCanvasLayout{pPlacement->instantiate<Uie::Component::UICanvasLayout>(L"canvas_layout")};

	auto pCanvasLayoutProperties1{pCanvasLayout->addChild(pTestElement1)};
	auto pCanvasLayoutProperties2{pCanvasLayout->addChild(pTestElement2)};
	auto pCanvasLayoutProperties3{pCanvasLayout->addChild(pTestElement3)};

	pCanvasLayoutProperties1->nX = -.25f;
	pCanvasLayoutProperties1->nY = .0f;
	pCanvasLayoutProperties1->nWidth = .5f;
	pCanvasLayoutProperties1->nHeight = .5f;

	pCanvasLayoutProperties2->nX = -.7f;
	pCanvasLayoutProperties2->nY = -.5f;
	pCanvasLayoutProperties2->nWidth = 1.f;
	pCanvasLayoutProperties2->nHeight = .75f;

	pCanvasLayoutProperties3->nX = .0f;
	pCanvasLayoutProperties3->nY = -.95f;
	pCanvasLayoutProperties3->nWidth = .2f;
	pCanvasLayoutProperties3->nHeight = 1.8f;

	pCanvasLayout->specifyOrder(0);
	pTestElement1->specifyOrder(1);
	pTestElement2->specifyOrder(2);
	pTestElement3->specifyOrder(3);

	sWindow.setVisible(Uie::Window::Visibility::ShowDefault);

	sWindow.loopMessage();

	sWindow.setVisible(Uie::Window::Visibility::Hide);
	sWindow.destroy();

	return 0;
}