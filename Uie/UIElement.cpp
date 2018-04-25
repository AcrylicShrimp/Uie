
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

		std::string sLinkLog;

		this->sShader[Render::SubShaderType::Vertex].compile(
			"#version 450 core\n"
			"layout(location = 0) in vec2 vert_vertex;\n"
			"void main() { gl_Position = vec4(vert_vertex.x, vert_vertex.y, 0.0, 1.0); }\n"
		);
		this->sShader[Render::SubShaderType::Fragment].compile(
			"#version 450 core\n"
			"layout(location = 0) out vec4 frag_output;\n"
			"void main() { frag_output = vec4(1.0, 0.0, 1.0, 0.5); }\n"
		);
		this->sShader.link();

		this->sShaderInput.attach(0, &this->sVertex, 0, sizeof(float) * 2);
		this->sShaderInput[0]->format<float>(2, 0);
		this->sShaderInput[0]->use(0);
	}

	void UIElement::update()
	{
		//Empty.
	}

	void UIElement::render()
	{
		//TODO : Remove below.
		this->sVertex = {
			this->sRect.nL, -this->sRect.nT,
			this->sRect.nL, -this->sRect.nB,
			this->sRect.nR, -this->sRect.nB,
			this->sRect.nR, -this->sRect.nT
		};

		this->sShaderInput.use();
		this->sShader.use();

		glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

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