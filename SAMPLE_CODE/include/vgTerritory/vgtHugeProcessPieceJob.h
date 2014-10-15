


#ifndef __VGTHUGEPROCESSPIECEJOB_H__
#define __VGTHUGEPROCESSPIECEJOB_H__


#include <vgTerritory/vgtDefinition.h>
#include <vgImage/vgiDefinition.h>
#include <vgKernel/vgkForward.h>
#include <vgThreads/ThreadRequest.h>
#include <vgThreads/ManualEvent.h>
#include <vgTerritory/vgtHugeProcessCounter.h>
#include <vgKernel/vgkProcessObserver.h>
	
namespace vgTerritory {


	namespace HugeProcess
	{
		
		using namespace vgKernel;

		using namespace vgThreads;
		class HugeJobs;
		class PieceJobRequest;

		class	VGT_EXPORT	PieceJob
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


		class  VGT_EXPORT PieceJobRequest : public ThreadRequest
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

		class  VGT_EXPORT PieceJobString : public PieceJob
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
	
	
}// end of namespace vgTerritory
	


#endif // end of __VGTHUGEPROCESSPIECEJOB_H__