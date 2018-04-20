
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

		this->sShader[Render::SubShaderType::Vertex].compile(
			"#version 450 core\n"
			"layout(location = 0) in vec2 vert_vertex;\n"
			//"layout(location = 1) in vec4 vert_color;\n"
			//"smooth out vec4 frag_color;"
			"void main() { gl_Position = vec4(vert_vertex.x, vert_vertex.y, 0.0, 1.0); }\n"
		);
		this->sShader[Render::SubShaderType::Fragment].compile(
			"#version 450 core\n"
			//"smooth in vec4 frag_color;"
			"out vec4 output;"
			"void main() { output = vec4(1.0, 0.0, 1.0, 0.75); }\n"
		);
		this->sShader.link();
	}

	void UIElement::update()
	{
		//Empty.
	}

	void UIElement::render()
	{
		//TODO : Remove below.
		this->sVertex = {this->sRect.nL, -this->sRect.nT, this->sRect.nL, -this->sRect.nB, this->sRect.nR, -this->sRect.nB, this->sRect.nR, -this->sRect.nT};
		this->sShader.use();

		glBindBuffer(GL_ARRAY_BUFFER, this->sVertex.identifier());
		glDrawArrays(GL_QUADS, 0, 4);

		if (!this->bFocused)
			return;

		glLineWidth(1.f);
		glDrawArrays(GL_LINE_LOOP, 0, 4);
	}

	void UIElement::specifyOrder(std::int64_t nOrder)
	{
		this->pPlacement->changeOrder(this, nOrder);
	}
}