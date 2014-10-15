




#ifndef __MANUAxyT_H__
#define __MANUAxyT_H__


#include "event.h"
#include <cassert>

namespace vgThreads {

	/**
		@date 	2007/12/22  17:35	
		@author  xy
	
		@brief 	
	
		@see    
	*/

	/** 
	*	Provides a wrapper around the WIN32 event objects
	*	
	*	@author Peter Hancock
	*/
	class  VGK_EXPORT Manuaxyt :	public Event
	{
	public:
		/**
		*	Create an event.
		*	@param eventName	Name of the event for external processes
		*	@throw EventException	Thrown when the event can't be created
		*	@note If using named events, the name is GLOBAL.  ie - you will not be able to run more
		*	than one process with the same name.  An event is a kernel object.
		*/
		Manuaxyt(const char* eventName=NULL)
		{
			// Note that the handle is closed in the base Event class.
			handle = ::CreateEvent(NULL, true, false, eventName);
			if(handle == NULL)
				throw EventException(eventName);
			assert(handle);
		}
		/** 
		*	Signal the event.
		*/
		void signal() throw()
		{
			assert(handle);
			::SetEvent(handle);
		}
		/**
		*	Reset the event to the non-signaled state
		*/
		void reset() throw()
		{
			assert(handle);
			::ResetEvent(handle);
		}
	};

	
	
	
}// end of namespace vgThreads

#endif // end of __MANUAxyT_H__




