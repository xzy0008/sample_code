


#include <vgStableHeaders.h>
#include <vgImage/vgiHugeProcessHugeJobs.h>
#include <vgImage/vgiHugeProcessCounter.h>
#include <vgImage/vgiHugeProcessPieceJob.h>

namespace vgImage {
	
	


	//----------------------------------------------------------------
	HugeProcess::HugeJobs::HugeJobs( vgKernel::ProcessNotifier* notifier )
	{
		_notifier = notifier;
		_threadPool = NULL;
		_counter = NULL;
	}
	//----------------------------------------------------------------
	HugeProcess::HugeJobs::~HugeJobs()
	{
		clearJobs();
	}
	//----------------------------------------------------------------
	//----------------------------------------------------------------
	void HugeProcess::HugeJobs::submit( PieceJob* job )
	{
		_jobs.push_back( job );
	}
	//----------------------------------------------------------------
	void HugeProcess::HugeJobs::doAndWait()
	{
		if ( _jobs.empty() == true )
		{
			return;
		}

		if ( _notifier != NULL )
		{
			_notifier->notifyProcessObserversStart( "" , 0 ,_jobs.size() );
		}

		//------------------------------------------
		// 创建ThreadPool
		//------------------------------------------
		assert( _threadPool  == NULL );
		if ( _threadPool == NULL )
		{
#if VGT_USE_MULTITHREAD
			long threadnum = VGT_THREAD_NUM;
#else
			long threadnum = 0;
#endif
			_threadPool = new ThreadPool( threadnum );
			_threadPool->initialize();
		}

		assert( _counter == NULL );
		_counter = new Counter( _jobs.size() );
		_event.reset();

		for ( int i = 0 ; i < _jobs.size() ; ++ i )
		{
			PieceJob* job = _jobs[i];
			ThreadRequest* req = job->createRequest( _counter , &_event );
			_threadPool->submitRequest( req );
		}

		//------------------------------------------
		// 等待完成
		//------------------------------------------
		bool outwhile = false;
		while ( 1 )
		{
			switch(::WaitForSingleObject( _event.getHandle() , 
				VGI_MULTITHREAD_UI_REFRESH_WAIT ) )
			{
			case WAIT_OBJECT_0:
				outwhile = true;
				break;
			case WAIT_TIMEOUT:

				if ( _notifier != NULL )
				{
					_notifier->notifyCurrentProcessObserversPos();
				}

				continue;

			case WAIT_ABANDONED:	   
			default:
				assert(0);
			}

			if ( outwhile )	{break;}
		}

		//------------------------------------------
		// 关闭并且清理
		//------------------------------------------
		clearJobs();

		_threadPool->shutdown();

		delete _counter;
		_counter = NULL;
		delete _threadPool;
		_threadPool = NULL;

		if ( _notifier != NULL )
		{
			_notifier->notfiyProcessObserversFinish("");
		}

		return;
	}	
	//----------------------------------------------------------------
	void HugeProcess::HugeJobs::clearJobs()
	{
		std::vector<PieceJob*>::iterator iter = _jobs.begin();
		std::vector<PieceJob*>::iterator iter_end = _jobs.end();

		for ( ; iter != iter_end ; ++ iter )
		{
			delete *iter;
		}

		_jobs.clear();
	}
	//----------------------------------------------------------------

	
}// end of namespace vgImage
