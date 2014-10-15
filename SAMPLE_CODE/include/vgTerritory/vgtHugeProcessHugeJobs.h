



#ifndef __VGTHUGEPROCESSHUGEJOBS_H__
#define __VGTHUGEPROCESSHUGEJOBS_H__


#include <vgTerritory/vgtDefinition.h>
#include <vgKernel/vgkForward.h>
#include <vgTerritory/vgtHugeProcessPieceJob.h>
#include <vgThreads/ThreadPool.h>
#include <vgTerritory/vgtDefinition.h>

	
namespace vgTerritory {


	namespace HugeProcess
	{

		class  VGT_EXPORT HugeJobs
		{
		public:
			HugeJobs( vgKernel::ProcessNotifier* notifier );
			virtual ~HugeJobs();

		public:

			void submit( PieceJob* job );

			void doAndWait();
		
			Counter* getCounter()
			{
				assert( _counter != NULL );
				return _counter;
			}

			vgKernel::ProcessNotifier* getNotifier()
			{
				return _notifier;
			}
		private:

			void clearJobs();

		private:
		
			vgKernel::ProcessNotifier* _notifier;
			ThreadPool* _threadPool;
			ManualEvent _event;
			Counter* _counter;


			std::vector<PieceJob*> _jobs;
		};
		

		//------------------------------------------
		// example
		//------------------------------------------
		class  VGT_EXPORT HugeJobsStringVector : public HugeJobs
		{
		public:
			HugeJobsStringVector( StringVector* strvec ,
				 vgKernel::ProcessNotifier* notifier )
				 : HugeJobs( notifier )
			{
				_stringVector = strvec;
			}
			virtual ~HugeJobsStringVector()
			{
				
			}
		
		public:


			StringVector* getStringVectorPtr() const 
			{
				return _stringVector;
			}
			CriticalSection* getCriticalSectPtr()
			{
				return &_sect;
			}

		private:
		
			StringVector* _stringVector;

			CriticalSection _sect;
		
		};

		


	}
	
	
}// end of namespace vgTerritory
	


#endif // end of __VGTHUGEPROCESSHUGEJOBS_H__