


#ifndef __VGIHUGEPROCESSPIECEJOB_H__
#define __VGIHUGEPROCESSPIECEJOB_H__
#include <vgImage/vgiDefinition.h>
#include <vgKernel/vgkForward.h>
#include <vgThreads/CriticalSection.h>
#include <vgThreads/ThreadPool.h>
#include <vgKernel/vgkProcessObserver.h>
	
namespace vgImage {


	namespace HugeProcess
	{

		class Counter;

		using namespace vgKernel;

		using namespace vgThreads;
		class HugeJobs;
		class PieceJobRequest;

		class PieceJob
		{
			friend class HugeJobs;
		public:
			PieceJob( HugeJobs * boss );
			virtual ~PieceJob();


		public:

			virtual void doJob() = 0;

		private:

			ThreadRequest* createRequest( Counter* counter ,
				ManualEvent* mevent );

		protected:

			HugeJobs* _boss;

		};


		class  VGI_EXPORT PieceJobRequest : public ThreadRequest
		{
		public:
			PieceJobRequest( PieceJob* job , Counter* counter , 
				ManualEvent* job_done_event );
			virtual ~PieceJobRequest();

			virtual void operator()(int threadId);

		private:

			PieceJob* _pieceJob;
			Counter* _counter;
			ManualEvent* _event;

		};


		//------------------------------------------
		// example
		// 返回的是一个String值,这个值需要保存到
		// HugeJobStringVector中.
		//------------------------------------------
		class HugeJobsStringVector;

		class  VGI_EXPORT PieceJobString : public PieceJob
		{
		public:
			PieceJobString( HugeJobsStringVector* boss , 
				vgKernel::ProcessNotifier* notifier );
			virtual ~PieceJobString();

			virtual String doJobRetString() = 0;

			virtual void doJob();

		private:

			vgKernel::ProcessNotifier* _notifier;
			HugeJobsStringVector* _jobBoss;
			StringVector* _strVec;
			CriticalSection* _sect;

		};

	}
	
	
	
}// end of namespace vgImage
	


#endif // end of __VGIHUGEPROCESSPIECEJOB_H__