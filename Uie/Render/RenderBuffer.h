
/*
	2018.05.01
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_UIE_RENDER_RENDERBUFFER_H

#define _CLASS_UIE_RENDER_RENDERBUFFER_H

/*
	TODO : Place the include directives here.
*/


#include <utility>

namespace Uie::Render
{
	class RenderBuffer
	{
	private:
		/*
			TODO : Place the class member variable declarations here.
		*/
		
		
	public:
		RenderBuffer();
		RenderBuffer(const RenderBuffer &sSrc);
		RenderBuffer(RenderBuffer &&sSrc);
		~RenderBuffer();
		/*
			TODO : Place the declarations of other constructors here.
		*/
		
		
	public:
		RenderBuffer &operator=(const RenderBuffer &sSrc);
		RenderBuffer &operator=(RenderBuffer &&sSrc);
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