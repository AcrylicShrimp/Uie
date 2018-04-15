
/*
	2018.04.05
	Created by AcrylicShrimp.
*/

#include "UIElement.h"

#include "UIPlacement.h"

namespace Uie
{
	UIElement::UIElement(UIPlacement *pPlacement, const std::wstring &sName) :
		pPlacement{pPlacement},
		nOrder{0},
		sName{sName}
	{
		this->bFocused = false;
		this->sColor = Color(.0f, .0f, .0f, .25f);

		this->UIEventHandler::addHandler("mouse.enter", [this](const std::string &sIdentifier, void *pParam)
		{
			this->sColor = Color(1.f, .0f, .0f, .25f);
			return true;
		});

		this->UIEventHandler::addHandler("mouse.leave", [this](const std::string &sIdentifier, void *pParam)
		{
			this->sColor = Color(.0f, .0f, .0f, .25f);
			return true;
		});

		this->UIEventHandler::addHandler("keyboard.down", [this](const std::string &sIdentifier, void *pParam)
		{
			this->sColor = Color(1.f, .0f, .0f, .25f);
			return true;
		});

		this->UIEventHandler::addHandler("keyboard.up", [this](const std::string &sIdentifier, void *pParam)
		{
			this->sColor = Color(.0f, .0f, .0f, .25f);
			return true;
		});

		this->UIEventHandler::addHandler("focus.enter", [this](const std::string &sIdentifier, void *pParam)
		{
			this->bFocused = true;
			return true;
		});

		this->UIEventHandler::addHandler("focus.leave", [this](const std::string &sIdentifier, void *pParam)
		{
			this->bFocused = false;
			return true;
		});

		this->UIEventHandler::addHandler("keyboard.type", [this](const std::string &sIdentifier, void *pParam)
		{
			auto pTypeEvent{reinterpret_cast<Event::UITypeEvent *>(pParam)};
			std::wstring sString{pTypeEvent->string()};

			if (pTypeEvent->state() == Event::UITypeEvent::State::Composing)
				sString += L" (composing)\n";
			else if (pTypeEvent->state() == Event::UITypeEvent::State::Composed)
				sString += L" (composed)\n";
			else
				sString += L" (canceled)\n";

			OutputDebugStringW(sString.c_str());
			return true;
		});
	}

	void UIElement::update()
	{
		//Empty.
	}

	void UIElement::render()
	{
		//TODO : Remove below.
		glBegin(GL_QUADS);

		glColor4f(this->sColor.nR, this->sColor.nG, this->sColor.nB, this->sColor.nA);
		glVertex2f(this->sRect.nL, -this->sRect.nT);
		glVertex2f(this->sRect.nL, -this->sRect.nB);
		glVertex2f(this->sRect.nR, -this->sRect.nB);
		glVertex2f(this->sRect.nR, -this->sRect.nT);

		glEnd();

		if (!this->bFocused)
			return;

		glLineWidth(1.f);

		glBegin(GL_LINE_LOOP);

		glColor4f(.0f, .0f, 1.f, 1.f);
		glVertex2f(this->sRect.nL, -this->sRect.nT);
		glVertex2f(this->sRect.nL, -this->sRect.nB);
		glVertex2f(this->sRect.nR, -this->sRect.nB);
		glVertex2f(this->sRect.nR, -this->sRect.nT);

		glEnd();
	}

	void UIElement::specifyOrder(std::int64_t nOrder)
	{
		this->pPlacement->changeOrder(this, nOrder);
	}
}