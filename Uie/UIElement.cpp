
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

		this->sShader[Render::SubShader::Type::Vertex].compile(
			"#version 450 core\n"

			"layout(std140) uniform Color {\n"
				"vec4 color;\n"
			"} global;\n"

			"layout(location = 0) in vec2 vert_vertex;\n"

			"void main() {\n"
				"gl_Position = vec4(vert_vertex.x, vert_vertex.y, 0.0, 1.0);\n"
			"}\n"
		);
		this->sShader[Render::SubShader::Type::Fragment].compile(
			"#version 450 core\n"

			"layout(std140) uniform Color {\n"
				"vec4 color;\n"
			"} global;\n"

			"layout(location = 0) out vec4 frag_output;\n"

			"void main() {\n"
				"frag_output = global.color;\n"
			"}\n"
		);

		std::string sLinkLog;

		this->sShader.link(&sLinkLog);

		this->sShaderInput.enableUniform("Color", 0);
		this->sShaderInput.attachUniform(&this->sColorBuffer, 0);

		this->sShaderInput[0]->use(0);
		this->sShaderInput[0]->format<float>(2);
		this->sShaderInput.attachAttrib(&this->sVertexBuffer, 0, 2);
	}

	void UIElement::update()
	{
		//Empty.
	}

	void UIElement::render()
	{
		//TODO : Remove below.
		this->sColorBuffer = {
			this->sColor.nR, this->sColor.nG, this->sColor.nB, .35f
		};

		this->sVertexBuffer = {
			this->sRect.nL, -this->sRect.nT,
			this->sRect.nL, -this->sRect.nB,
			this->sRect.nR, -this->sRect.nB,
			this->sRect.nR, -this->sRect.nT
		};

		this->sShader.use(this->sShaderInput);

		glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

		if (!this->bFocused)
			return;

		this->sColorBuffer = {
			1.f, .0f, 1.f, 1.f
		};

		glLineWidth(2.f);
		glDrawArrays(GL_LINE_LOOP, 0, 4);
	}

	void UIElement::specifyOrder(std::int64_t nOrder)
	{
		this->pPlacement->changeOrder(this, nOrder);
	}
}