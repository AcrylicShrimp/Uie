
/*
	2018.04.20
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_UIE_EVENT_RENDERER_H

#define _CLASS_UIE_EVENT_RENDERER_H

#include "../UieDLL.h"


#include <GL/glew.h>

namespace Uie::Event
{
	class UIE_DLL Renderer final
	{
	private:

		
	public:
		Renderer();
		Renderer(const Renderer &sSrc);
		Renderer(Renderer &&sSrc);
		~Renderer();

	public:
		Renderer &operator=(const Renderer &sSrc);
		Renderer &operator=(Renderer &&sSrc);
		/*
			TODO : Place other operator overloadings here.
		*/
		
		
	public:
		/*
			TODO : Place the member function declarations here.
		*/
		
	};
}

#endif