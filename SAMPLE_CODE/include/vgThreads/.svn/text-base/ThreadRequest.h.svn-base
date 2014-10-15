



#ifndef __THREADREQUEST_H__
#define __THREADREQUEST_H__

//#include <windows.h>


namespace vgThreads {

	/**
	*	Interface to the threadpool.  
	*	This MUST be derived from with the execute method overridden to use your own custom
	*	handler.  
	* 
	*	@warning execute is declared as throwing no exceptions.  This means that you MUST deal with exceptions in the 
	*           command object.
	* 
	*	@author Peter Hancock
	*
	*/
	class  VGK_EXPORT ThreadRequest
	{
	public:
		ThreadRequest(){}
		virtual ~ThreadRequest(void){}
		virtual void operator()(int threadId) throw() = 0;			 ///< Must be overridden by your custom dispatch function.
	};
	
	
	
}// end of namespace vgThreads

#endif // end of __THREADREQUEST_H__

