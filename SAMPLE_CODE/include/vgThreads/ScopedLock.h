

#ifndef __SCOPEDLOCK_H__
#define __SCOPEDLOCK_H__

#include <vgThreads/CriticalSection.h>


namespace vgThreads {



	/**
	*	ScopedLock class provides exception safety for critical sections
	*	A helper class that enters a critical section on construction, and leaves
	*  the critical section on destruction.  
	*
	*	@code 
		int i;
		{
			ScopedLock loopGuard(moduleCS);			// enters the critical section
			for(int i=0 ; i < 10 ; i++)
			{
				// Do stuff here				// If an exception is thrown here, loopGuard goes out of scope - calling leave()
			}
		}	// ScopedLock goes out of scope here, destructor calls leave()
	*	@endcode
	*
	*	@author Peter Hancock
	*
	*/
	class  VGK_EXPORT ScopedLock
	{
	public:
		ScopedLock(CriticalSection& sectionName) : cs(sectionName)
		{
			cs.enter();
		}
		~ScopedLock()
		{
			cs.leave();
		}
	private:
		CriticalSection& cs;
		ScopedLock(const ScopedLock& copy);
		ScopedLock& operator=(const ScopedLock& rhs);
	};

	
	
	
}// end of namespace vgThreads

#endif // end of __SCOPEDLOCK_H__