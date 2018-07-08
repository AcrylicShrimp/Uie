
/*
	2018.04.05
	Created by AcrylicShrimp.
*/

#include "../Uie/Uie/Window.h"

#include "../Uie/Uie/UI/Component/UICanvasLayout.h"
#include "../Uie/Uie/UI/Component/UITest.h"
#include "../Uie/Uie/UIContext.h"

#include <Windows.h>

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR pCmdLine, int nCmdShow)
{
	RECT sWorkArea;
	SystemParametersInfoW(SPI_GETWORKAREA, 0, &sWorkArea, 0);

	auto nWidth{sWorkArea.right - sWorkArea.left};
	auto nHeight{sWorkArea.bottom - sWorkArea.top};

	Uie::Window::Attribute sAttribute;
	sAttribute.nX = nWidth / 4;
	sAttribute.nY = nHeight / 4;
	sAttribute.nWidth = nWidth / 2;
	sAttribute.nHeight = nHeight / 2;
	sAttribute.sClassName = L"Uie Basic Example";
	sAttribute.sTitleText = L"Uie Basic Example";
	sAttribute.eClassStyle = Uie::combineEnum(Uie::Window::ClassStyle::OwnDeviceContext, Uie::Window::ClassStyle::HorizontalRedraw, Uie::Window::ClassStyle::VerticalRedraw);

	Uie::Window sWindow;
	sWindow.create(sAttribute);
	sWindow.createContext(32, 0, 0);

	Uie::UIContext sContext;
	sContext.create(&sWindow);
	sContext.attach(&sWindow);

	auto pPlacement{sContext.createPlacement("main")};
	
	auto pTestElement1{pPlacement->create<Uie::UI::Component::UITest>("test_element_1")};
	auto pTestElement2{pPlacement->create<Uie::UI::Component::UITest>("test_element_2")};
	auto pTestElement3{pPlacement->create<Uie::UI::Component::UITest>("test_element_3")};
	auto pCanvasLayout{pPlacement->create<Uie::UI::Component::UICanvasLayout>("canvas_layout")};

	pCanvasLayout->addChild(pTestElement1);
	pCanvasLayout->addChild(pTestElement2);
	pCanvasLayout->addChild(pTestElement3);

	auto pCanvasLayoutProperties1{pCanvasLayout->properties(pTestElement1)};
	auto pCanvasLayoutProperties2{pCanvasLayout->properties(pTestElement2)};
	auto pCanvasLayoutProperties3{pCanvasLayout->properties(pTestElement3)};
	
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

	sContext.activePlacement("main");
	
	sWindow.setVisible(Uie::Window::Visibility::ShowDefault);

	Uie::Window::loopMessage();

	sWindow.setVisible(Uie::Window::Visibility::Hide);
	sWindow.destroy();

	return 0;
}