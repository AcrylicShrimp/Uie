
/*
	2018.05.23
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_UIE_UI_COMPONENT_UITEST_H

#define _CLASS_UIE_UI_COMPONENT_UITEST_H

#include "../../UieDLL.h"

#include "../Element.h"
#include "../Root.h"
#include "../../Color.h"
#include "../../UIContext.h"

#include "../../Render/Component/Buffer.h"
#include "../../Render/Component/RenderTarget.h"
#include "../../Render/Component/Shader.h"
#include "../../Render/Component/ShaderAttrib.h"
#include "../../Render/Component/ShaderInput.h"
#include "../../Render/Component/SubShader.h"
#include "../../Render/Component/Texture.h"

#include <cstdint>
#include <fstream>
#include <stb/stb_image.h>
#include <Gl/glew.h>
#include <Windows.h>

namespace Uie::UI::Component
{
	class UIE_DLL UITest : public Element
	{
	protected:
		static Render::Component::Shader *pShader;
		static Render::Component::Texture *pTexture;
		static std::uint64_t nReferenceCount;

	protected:
		bool bFocused;
		Color sRenderingColor;

		Render::Component::ShaderInput sShaderInput;
		Render::Component::Buffer<float> sVertexBuffer;
		Render::Component::Buffer<float> sUVBuffer;
		Render::Component::Buffer<float> sColorBuffer;
		
	public:
		UITest(Root *pRoot, const std::string &sName);
		UITest(const UITest &sSrc) = delete;
		~UITest();
		
	public:
		UITest &operator=(const UITest &sSrc) = delete;
		
	public:
		virtual void render() override;
		static void refCountUp();
		static void refCountDown();
	};
}

#endif