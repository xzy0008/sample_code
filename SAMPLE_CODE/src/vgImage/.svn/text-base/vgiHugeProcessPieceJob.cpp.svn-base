


#include <vgStableHeaders.h>
#include <vgImage/vgiHugeProcessPieceJob.h>
#include <vgImage/vgiHugeProcessCounter.h>
#include <vgImage/vgiHugeProcessHugeJobs.h>


namespace vgImage {
	

	//----------------------------------------------------------------
	HugeProcess::PieceJob::PieceJob(HugeJobs * boss ) 
	{
		_boss = boss;
	}
	//----------------------------------------------------------------
	HugeProcess::PieceJob::~PieceJob()
	{

	}
	//----------------------------------------------------------------
	ThreadRequest* HugeProcess::PieceJob::createRequest( Counter* counter,
		ManualEvent* mevent  )
	{
		ThreadRequest* ret = new PieceJobRequest( this , counter , mevent );
		return ret;
	}
	//----------------------------------------------------------------




	//----------------------------------------------------------------
	void HugeProcess::PieceJobRequest::operator()( int threadId )
	{
		_pieceJob->doJob();

		_counter->addCount();

		if ( _counter->checkCount() == true )
		{
			_event->signal();
		}
	}
	//----------------------------------------------------------------
	HugeProcess::PieceJobRequest::PieceJobRequest( 
		PieceJob* job , Counter* counter , 
		ManualEvent* job_done_event  ) 
		: ThreadRequest()
	{
		_pieceJob = job;
		_event = job_done_event;
		_counter = counter;
	}
	//----------------------------------------------------------------
	HugeProcess::PieceJobRequest::~PieceJobRequest()
	{

	}
	//----------------------------------------------------------------


	//----------------------------------------------------------------
	HugeProcess::PieceJobString::PieceJobString( 
		HugeJobsStringVector* boss , 
		vgKernel::ProcessNotifier* notifier )
		: PieceJob( boss )
	{
		_notifier = notifier;
		_jobBoss = boss;
		_strVec = _jobBoss->getStringVectorPtr();
		_sect = _jobBoss->getCriticalSectPtr();
	}
	//----------------------------------------------------------------
	void HugeProcess::PieceJobString::doJob()
	{
		String ret = doJobRetString();

		if ( ret != "" )
		{
			if ( _notifier != NULL )
			{
				long count = _jobBoss->getCounter()->getCount();
				_notifier->setCurrentProcessPos(  ret , count );
			}

			_sect->enter();
			_strVec->push_back( ret );
			_sect->leave();
		}
	}
	//----------------------------------------------------------------
	HugeProcess::PieceJobString::~PieceJobString()
	{

	}
	//----------------------------------------------------------------
	
	
}// end of namespace vgImage
