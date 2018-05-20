
/*
	2018.04.05
	Created by AcrylicShrimp.
*/

#define STB_IMAGE_IMPLEMENTATION

#include "UIElement.h"

#include "RenderManager.h"
#include "UIPlacement.h"

namespace Uie
{
	UIElement::UIElement(UIPlacement *pPlacement, const std::wstring &sName) :
		pPlacement{pPlacement},
		nOrder{0},
		sName{sName},
		sTexture{1200, 630, Render::Texture::Format::RGB888},
		sBlurredTexture{512, 512, Render::Texture::Format::RGBA8888}
	{
		this->bFocused = false;
		this->sColor = Color(.5f, .5f, .5f, .75f);

		this->UIEventHandler::addHandler("mouse.enter", [this](const std::string &sIdentifier, void *pParam)
		{
			this->sColor = Color(1.f, .5f, .5f, .75f);
			RenderManager::instance().repaint();
			return true;
		});

		this->UIEventHandler::addHandler("mouse.leave", [this](const std::string &sIdentifier, void *pParam)
		{
			this->sColor = Color(.5f, .5f, .5f, .75f);
			RenderManager::instance().repaint();
			return true;
		});

		this->UIEventHandler::addHandler("keyboard.down", [this](const std::string &sIdentifier, void *pParam)
		{
			this->sColor = Color(1.f, .5f, .5f, .75f);
			RenderManager::instance().repaint();
			return true;
		});

		this->UIEventHandler::addHandler("keyboard.up", [this](const std::string &sIdentifier, void *pParam)
		{
			this->sColor = Color(.5f, .5f, .5f, .75f);
			RenderManager::instance().repaint();
			return true;
		});

		this->UIEventHandler::addHandler("focus.enter", [this](const std::string &sIdentifier, void *pParam)
		{
			this->bFocused = true;
			RenderManager::instance().repaint();
			return true;
		});

		this->UIEventHandler::addHandler("focus.leave", [this](const std::string &sIdentifier, void *pParam)
		{
			this->bFocused = false;
			RenderManager::instance().repaint();
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

			RenderManager::instance().repaint();

			return true;
		});

		{
			stbi_set_flip_vertically_on_load(1);

			std::ifstream sInput{L"cat.jpg", std::ifstream::ate | std::ifstream::binary | std::ifstream::in};
			auto nTextureSize{sInput.tellg()};

			auto *const pTexture{new uint8_t[static_cast<std::size_t>(nTextureSize)]};

			sInput.seekg(0, std::ifstream::_Seekdir::_Seekbeg);
			sInput.read(reinterpret_cast<char *const>(pTexture), nTextureSize);

			int nWidth, nHeight, nChannel;

			auto *pPixel{stbi_load_from_memory(pTexture, static_cast<int>(nTextureSize), &nWidth, &nHeight, &nChannel, 0)};
			delete pTexture;

			this->sTexture.fill(Render::Texture::DataFormat::RGB, pPixel);

			stbi_image_free(pPixel);
		}

		this->sTexture.filterMode(Render::Texture::FilterMode::Trilinear);
		this->sTexture.wrappingMode(Render::Texture::WrappingMode::Edge, Render::Texture::WrappingMode::Edge);
		this->sTexture.anisotropicFiltering(1.f);

		this->sBlurredTexture.filterMode(Render::Texture::FilterMode::Trilinear);
		this->sBlurredTexture.wrappingMode(Render::Texture::WrappingMode::Edge, Render::Texture::WrappingMode::Edge);
		this->sBlurredTexture.anisotropicFiltering(1.f);

		this->sOffscreen.color(0, &this->sBlurredTexture);

		this->sBlurShader[Render::SubShader::Type::Vertex].compile(
			"#version 450 core\n"

			"uniform sampler2D uniform_texture;\n"

			"layout(location = 0) in vec2 vert_vertex;\n"
			"layout(location = 1) in vec2 vert_uv;\n"

			"smooth out vec2 frag_uv;\n"

			"void main() {\n"
			"gl_Position = vec4(vert_vertex.xy, 0.0, 1.0);\n"
			"frag_uv = vert_uv;\n"
			"}\n"
		);
		this->sBlurShader[Render::SubShader::Type::Fragment].compile(
			"#version 450 core\n"

			"uniform sampler2D uniform_texture;\n"

			"smooth in vec2 frag_uv;\n"

			"layout(location = 0) out vec4 frag_output;\n"

			"void main() {\n"
			"frag_output = vec4(texture(uniform_texture, frag_uv).rgb, 1.0);\n"
			"}\n"
		);

		std::string sBlurLinkLog;
		this->sBlurShader.link(&sBlurLinkLog);

		this->sBlurShaderInput.attachUniform("uniform_texture", &this->sTexture);

		this->sBlurShaderInput[0]->format<float>(2);
		this->sBlurShaderInput[0]->use(0);
		this->sBlurShaderInput.attachAttrib(0, &this->sBlurVertexBuffer, 2);

		this->sBlurShaderInput[1]->format<float>(2);
		this->sBlurShaderInput[1]->use(1);
		this->sBlurShaderInput.attachAttrib(1, &this->sBlurUVBuffer, 2);

		this->sNormalShader[Render::SubShader::Type::Vertex].compile(
			"#version 450 core\n"

			"uniform sampler2D uniform_texture;\n"

			"layout(location = 0) in vec2 vert_vertex;\n"
			"layout(location = 1) in vec2 vert_uv;\n"
			"layout(location = 2) in vec4 vert_color;\n"

			"smooth out vec2 frag_uv;\n"
			"smooth out vec4 frag_color;\n"

			"void main() {\n"
			"gl_Position = vec4(vert_vertex.xy, 0.0, 1.0);\n"
			"frag_uv = vert_uv;\n"
			"frag_color = vert_color;\n"
			"}\n"
		);
		this->sNormalShader[Render::SubShader::Type::Fragment].compile(
			"#version 450 core\n"

			"uniform sampler2D uniform_texture;\n"

			"smooth in vec2 frag_uv;\n"
			"smooth in vec4 frag_color;\n"

			"layout(location = 0) out vec4 frag_output;\n"

			"void main() {\n"
			"frag_output = vec4(texture(uniform_texture, frag_uv).rgb * frag_color.rgb, frag_color.a);\n"
			"}\n"
		);

		std::string sNormalLinkLog;
		this->sNormalShader.link(&sNormalLinkLog);

		this->sNormalShaderInput.attachUniform("uniform_texture", &this->sBlurredTexture);

		this->sNormalShaderInput[0]->format<float>(2);
		this->sNormalShaderInput[0]->use(0);
		this->sNormalShaderInput.attachAttrib(0, &this->sVertexBuffer, 2);

		this->sNormalShaderInput[1]->format<float>(2);
		this->sNormalShaderInput[1]->use(1);
		this->sNormalShaderInput.attachAttrib(1, &this->sUVBuffer, 2);

		this->sNormalShaderInput[2]->format<float>(4);
		this->sNormalShaderInput[2]->use(2);
		this->sNormalShaderInput.attachAttrib(2, &this->sColorBuffer, 4, 0, 0, 1);
	}

	void UIElement::update()
	{
		//Empty.
	}

	void UIElement::render()
	{
		//TODO : Remove below.

		glViewport(0, 0, 512, 512);
		this->sTexture.use(0);
		this->sOffscreen.use({Render::RenderTarget::Target::Color});
		this->sBlurShader.use(this->sBlurShaderInput);

		this->sBlurVertexBuffer = {
			-1.f, 1.f,
			-1.f, -1.f,
			1.f, -1.f,
			1.f, 1.f
		};
		this->sBlurUVBuffer = {
			.0f, 1.f,
			.0f, .0f,
			1.f, .0f,
			1.f, 1.f
		};

		glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

		//glViewport(0, 0, )
		this->sBlurredTexture.use(0);
		Render::RenderTarget::useDefault({Render::RenderTarget::DefaultTarget::Back});
		this->sNormalShader.use(this->sNormalShaderInput);

		this->sVertexBuffer = {
			this->sRect.nL, -this->sRect.nT,
			this->sRect.nL, -this->sRect.nB,
			this->sRect.nR, -this->sRect.nB,
			this->sRect.nR, -this->sRect.nT
		};
		this->sUVBuffer = {
			.0f, 1.f,
			.0f, .0f,
			1.f, .0f,
			1.f, 1.f
		};
		this->sColorBuffer = {
			this->sColor.nR, this->sColor.nG, this->sColor.nB, this->sColor.nA
		};

		glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

		if (!this->bFocused)
			return;

		glLineWidth(2.f);
		glDrawArrays(GL_LINE_LOOP, 0, 4);
	}

	void UIElement::specifyOrder(std::int64_t nOrder)
	{
		this->pPlacement->changeOrder(this, nOrder);
	}
}