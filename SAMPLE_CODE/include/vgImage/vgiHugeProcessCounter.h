


#ifndef __VGIHUGEPROCESSCOUNTER_H__
#define __VGIHUGEPROCESSCOUNTER_H__

#include <vgImage/vgiDefinition.h>
#include <vgKernel/vgkForward.h>
#include <vgThreads/CriticalSection.h>

	
namespace vgImage {

	/**
		@date 	2009/06/04  10:19	
		@author  leven
	
		@brief 	
	
		@see    
	*/

	using namespace vgThreads;

	namespace HugeProcess
	{
		class  VGI_EXPORT Counter
		{
		public:
			Counter( long aimCount );
			~Counter();

		public:

			void addCount();

			bool checkCount();

			long getCount();

		private:

			CriticalSection _sect;

			long _count;

			long _aimCount;
		};
	}
	
	
}// end of namespace vgImage
	


#endif // end of __VGIHUGEPROCESSCOUNTER_H__