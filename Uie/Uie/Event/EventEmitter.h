
/*
	2018.07.08
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_UIE_EVENT_EVENTEMITTER_H

#define _CLASS_UIE_EVENT_EVENTEMITTER_H

/*
	TODO : Place the include directives here.
*/


#include <utility>

namespace Uie::Event
{
	class EventEmitter
	{
	private:
		/*
			TODO : Place the class member variable declarations here.
		*/
		
		
	public:
		EventEmitter();
		EventEmitter(const EventEmitter &sSrc);
		EventEmitter(EventEmitter &&sSrc);
		~EventEmitter();
		/*
			TODO : Place the declarations of other constructors here.
		*/
		
		
	public:
		EventEmitter &operator=(const EventEmitter &sSrc);
		EventEmitter &operator=(EventEmitter &&sSrc);
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