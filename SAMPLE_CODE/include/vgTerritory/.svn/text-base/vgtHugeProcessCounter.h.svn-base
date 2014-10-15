




#ifndef __VGTHUGEPROCESSCOUNTER_H__
#define __VGTHUGEPROCESSCOUNTER_H__


#include <vgTerritory/vgtDefinition.h>
#include <vgKernel/vgkForward.h>
#include <vgThreads/CriticalSection.h>

	
namespace vgTerritory {


	using namespace vgThreads;

	namespace HugeProcess
	{
		class  VGT_EXPORT Counter
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
	
	
}// end of namespace vgTerritory
	


#endif // end of __VGTHUGEPROCESSCOUNTER_H__