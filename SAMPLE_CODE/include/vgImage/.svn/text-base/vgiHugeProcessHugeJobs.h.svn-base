


#ifndef __VGIHUGEPROCESSHUGEJOBS_H__
#define __VGIHUGEPROCESSHUGEJOBS_H__

#include <vgImage/vgiDefinition.h>
#include <vgKernel/vgkForward.h>
#include <vgThreads/CriticalSection.h>
#include <vgKernel/vgkProcessObserver.h>
#include <vgThreads/ThreadPool.h>
#include <vgKernel/vgkStringVector.h>

	
namespace vgImage {


	namespace HugeProcess
	{

		using namespace vgKernel;
		using namespace vgThreads;
		class Counter;

		class PieceJob;

		class  VGI_EXPORT HugeJobs
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
		class  VGI_EXPORT HugeJobsStringVector : public HugeJobs
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
	
	
}// end of namespace vgImage
	


#endif // end of __VGIHUGEPROCESSHUGEJOBS_H__