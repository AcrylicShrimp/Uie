
/*
	2018.05.23
	Created by AcrylicShrimp.
*/

#define STB_IMAGE_IMPLEMENTATION

#include "UITest.h"

namespace Uie::UI::Component
{
	Render::Component::Shader *UITest::pShader{nullptr};
	Render::Component::Texture *UITest::pTexture{nullptr};
	std::uint64_t UITest::nReferenceCount{0};

	UITest::UITest(Root *pRoot, const std::string &sName) :
		Element(pRoot, sName)
	{
		this->bFocused = false;
		this->sRenderingColor = Color(.5f, .5f, .5f, .75f);

		this->EventHandler::addHandler("mouse.enter", [this](const std::string &sIdentifier, void *pParam)
		{
			this->sRenderingColor = Color(1.f, .5f, .5f, .75f);
			UIContext::current()->redraw();
			return true;
		});

		this->EventHandler::addHandler("mouse.leave", [this](const std::string &sIdentifier, void *pParam)
		{
			this->sRenderingColor = Color(.5f, .5f, .5f, .75f);
			UIContext::current()->redraw();
			return true;
		});

		this->EventHandler::addHandler("keyboard.down", [this](const std::string &sIdentifier, void *pParam)
		{
			this->sRenderingColor = Color(1.f, .5f, .5f, .75f);
			UIContext::current()->redraw();
			return true;
		});

		this->EventHandler::addHandler("keyboard.up", [this](const std::string &sIdentifier, void *pParam)
		{
			this->sRenderingColor = Color(.5f, .5f, .5f, .75f);
			UIContext::current()->redraw();
			return true;
		});

		this->EventHandler::addHandler("focus.enter", [this](const std::string &sIdentifier, void *pParam)
		{
			this->bFocused = true;
			UIContext::current()->redraw();
			return true;
		});

		this->EventHandler::addHandler("focus.leave", [this](const std::string &sIdentifier, void *pParam)
		{
			this->bFocused = false;
			UIContext::current()->redraw();
			return true;
		});

		UITest::refCountUp();

		this->sShaderInput.attachUniform("uniform_texture", UITest::pTexture);

		this->sShaderInput[0]->format<float>(2);
		this->sShaderInput[0]->use(0);
		this->sShaderInput.attachAttrib(0, &this->sVertexBuffer, 2);

		this->sShaderInput[1]->format<float>(2);
		this->sShaderInput[1]->use(1);
		this->sShaderInput.attachAttrib(1, &this->sUVBuffer, 2);

		this->sShaderInput[2]->format<float>(4);
		this->sShaderInput[2]->use(2);
		this->sShaderInput.attachAttrib(2, &this->sColorBuffer, 4, 0, 0, 1);
	}

	UITest::~UITest()
	{
		UITest::refCountDown();
	}

	void UITest::render()
	{
		UITest::pTexture->use(0);
		Render::Component::RenderTarget::useDefault({Render::Component::RenderTarget::DefaultTarget::Back});

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
			this->sRenderingColor.nR,
			this->sRenderingColor.nG,
			this->sRenderingColor.nB,
			this->sRenderingColor.nA
		};

		UITest::pShader->use(this->sShaderInput);

		glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

		if (!this->bFocused)
			return;

		glLineWidth(2.f);
		glDrawArrays(GL_LINE_LOOP, 0, 4);
	}

	void UITest::refCountUp()
	{
		if (UITest::nReferenceCount++)
			return;

		//Init shader.
		{
			UITest::pShader = new Render::Component::Shader();
			(*UITest::pShader)[Render::Component::SubShader::Type::Vertex].compile(
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
			(*UITest::pShader)[Render::Component::SubShader::Type::Fragment].compile(
				"#version 450 core\n"

				"uniform sampler2D uniform_texture;\n"

				"smooth in vec2 frag_uv;\n"
				"smooth in vec4 frag_color;\n"

				"layout(location = 0) out vec4 frag_output;\n"

				"void main() {\n"
				"frag_output = vec4(texture(uniform_texture, frag_uv).rgb * frag_color.rgb, frag_color.a);\n"
				"}\n"
			);

			UITest::pShader->link();
		}

		//Init texture.
		{
			stbi_set_flip_vertically_on_load(1);

			std::ifstream sInput{L"test.png", std::ifstream::ate | std::ifstream::binary | std::ifstream::in};
			auto nTextureSize{sInput.tellg()};

			auto *const pTexture{new uint8_t[static_cast<std::size_t>(nTextureSize)]};

			sInput.seekg(0, std::ifstream::_Seekdir::_Seekbeg);
			sInput.read(reinterpret_cast<char *const>(pTexture), nTextureSize);

			int nWidth, nHeight, nChannel;

			auto *pPixel{stbi_load_from_memory(pTexture, static_cast<int>(nTextureSize), &nWidth, &nHeight, &nChannel, 3)};
			delete pTexture;

			UITest::pTexture = new Render::Component::Texture(nWidth, nHeight, Render::Component::Texture::Format::RGB888);
			UITest::pTexture->fill(Render::Component::Texture::DataFormat::RGB, pPixel);

			stbi_image_free(pPixel);

			UITest::pTexture->filterMode(Render::Component::Texture::FilterMode::Trilinear);
			UITest::pTexture->wrappingMode(Render::Component::Texture::WrappingMode::Edge, Render::Component::Texture::WrappingMode::Edge);
			UITest::pTexture->anisotropicFiltering(1.f);
		}
	}

	void UITest::refCountDown()
	{
		if (--UITest::nReferenceCount)
			return;

		delete UITest::pShader;
		delete UITest::pTexture;

		UITest::pShader = nullptr;
		UITest::pTexture = nullptr;
	}
}