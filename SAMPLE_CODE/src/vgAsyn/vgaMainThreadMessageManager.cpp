



#include <vgStableHeaders.h>
#include <vgAsyn/vgaMainThreadMessageManager.h>
#include <vgAsyn/vgaIoRequest.h>
#include <vgKernel/vgkCamMgrImpl.h>
#include <vgKernel/vgkCamMgrHolder.h>
#include <vgAsyn/vgaRenderCommand.h>


namespace vgAsyn {


	//----------------------------------------------------------------
	MainThreadMessageManager::MainThreadMessageManager()
		: Singleton<MainThreadMessageManager>( 
		VGK_SINGLETON_LEFE_MAINTHREADMGR )
	{
		_forceToSynMode = false;

		_numOfRequestToSend = 4;
		_numOfNullRequestToSkip = 20;
		_numOfMainHandlerToProcess = 15;

		m_renderBeginCommand = new AsynBeginCommand;
		vgKernel::RenderCommandFacade::AddCommand(m_renderBeginCommand);

		VGK_TRACE(_T("MainThreadMessageManager created."));
	}

	MainThreadMessageManager::~MainThreadMessageManager()
	{
		clearAllData();
		vgKernel::RenderCommandFacade::RemoveCommand(m_renderBeginCommand);

		VGK_TRACE(_T("MainThreadMessageManager destroyed."));
	}

	bool MainThreadMessageManager::initialise()
	{
		return true;
	}

	//----------------------------------------------------------------
	void MainThreadMessageManager::doRequests()
	{
		doSenderOfRequests();
		doMainHandlerOfRequests();
	}
	//----------------------------------------------------------------
	void MainThreadMessageManager::pushMainHandlerOfIoRequest( IoRequest* request )
	{
		bool priority = request->getPriority();

		vgThreads::ScopedLock lock( _requestsSectOfMainHandler );

		assert( request != NULL );
		if ( priority == true )
		{
			_requestsOfMainHandler.push_front( request );
		}
		else
		{
			_requestsOfMainHandler.push_back( request );
		}
	}
	//----------------------------------------------------------------
	void MainThreadMessageManager::pushSenderOfIoRequest( 
		IoRequest* request )
	{
		if ( request->getPriority() == true )
		{
			_requestsOfSender.push_front( request );
		}
		else
		{
			_requestsOfSender.push_back( request );
		}
	}
	//----------------------------------------------------------------
	void MainThreadMessageManager::doSenderOfRequests()
	{
#if 0
		//------------------------------------------
		// 始终发送的版本
		//------------------------------------------
		const int max_num = 1000000;
		for ( int i = 0 ; i < max_num ; ++ i )
		{
			if ( _requestsOfSender.empty() == true )
			{
				break;
			}

			IoRequest* request = _requestsOfSender.front();
			request->sendRequestAndDoAsynHandlerFuncImpl();

			_requestsOfSender.pop_front();
		}
#else

		const int max_num = _numOfRequestToSend;
		const int max_null_num = _numOfNullRequestToSkip;

		int num_counter = 0;
		int null_rq_counter = 0;

		while ( num_counter != max_num && 
			null_rq_counter != max_null_num )
		{
			if ( _requestsOfSender.empty() == true )
			{
				break;
			}

			IoRequest* request = _requestsOfSender.front();
			if ( request->isReallyNeedToSend() == true )
			{
				if ( _forceToSynMode )
				{
					request->setAsynchronousMode( false );
				}

				request->sendRequestAndDoAsynHandlerFuncImpl();
				++num_counter;
			}
			else
			{
				++null_rq_counter;
				delete request;
			}
			
			_requestsOfSender.pop_front();
		}

#endif

		return;
	}
	//----------------------------------------------------------------
	void MainThreadMessageManager::doMainHandlerOfRequests()
	{

		//------------------------------------------
		// 1.先从队列中拷贝出来,减少加锁的时间
		//------------------------------------------
		// request类自身负责删除

		if( _requestBufOfMainHandler.empty() == false )
		{
			assert(0&&"MainThreadMessageManager::doMainHandlerOfRequests");
		}

		//assert( _requestBufOfMainHandler.empty() == true );
		_requestsSectOfMainHandler.enter();
		//------------------------------------------
		// 从中拷贝一定数量的请求
		//------------------------------------------
//#if 1
		const int max_buf_size = _numOfMainHandlerToProcess;

		if ( max_buf_size == -1 )
		{
			//------------------------------------------
			// 全部交换
			//------------------------------------------
			_requestsOfMainHandler.swap( _requestBufOfMainHandler );
		}
		else
		{
			for ( int i = 0 ; i < max_buf_size ; ++i )
			{
				if ( _requestsOfMainHandler.empty() == true )
				{
					break;
				}

				IoRequest* request = _requestsOfMainHandler.front();
				_requestBufOfMainHandler.push_back( request );
				_requestsOfMainHandler.pop_front();
			}
		}

//#else
//		_requestsOfMainHandler.swap( _requestBufOfMainHandler );
//#endif

		_requestsSectOfMainHandler.leave();

		//------------------------------------------
		// 2.处理这些数据
		//------------------------------------------

		RequestPipe::iterator iter = _requestBufOfMainHandler.begin();
		RequestPipe::iterator iter_end = _requestBufOfMainHandler.end();
		for ( ; iter != iter_end ; ++ iter )
		{
			(*iter)->handleMainThreadRequest();
		}

		_requestBufOfMainHandler.clear();
	}
	//----------------------------------------------------------------
	bool MainThreadMessageManager::shutdown()
	{
		return true;
	}
	//----------------------------------------------------------------
	void MainThreadMessageManager::clearAllData()
	{
		{
			RequestPipe::iterator iter = _requestsOfSender.begin();
			RequestPipe::iterator iter_end = _requestsOfSender.end();

			for ( ; iter != iter_end ; ++iter )
			{
				IoRequest* req = *iter;
				delete req;
			}
			_requestsOfSender.clear();
		}

		vgThreads::ScopedLock lock( _requestsSectOfMainHandler );

		{
			RequestPipe::iterator iter = _requestsOfMainHandler.begin();
			RequestPipe::iterator iter_end = _requestsOfMainHandler.end();

			for ( ; iter != iter_end ; ++iter )
			{
				IoRequest* req = *iter;
				delete req;
			}
			_requestsOfMainHandler.clear();
		}

		{
			RequestPipe::iterator iter = _requestBufOfMainHandler.begin();
			RequestPipe::iterator iter_end = _requestBufOfMainHandler.end();

			for ( ; iter != iter_end ; ++iter )
			{
				IoRequest* req = *iter;
				delete req;
			}
			_requestBufOfMainHandler.clear();
		}
	}
	//----------------------------------------------------------------
	void MainThreadMessageManager::renderBegin()
	{
		vgKernel::CamMgrImpl* cam = 
			vgKernel::CamMgrHolder::getSingleton().getCamManager();

		if ( cam != NULL )
		{
			if( cam->isControlling() )
			{
				_numOfRequestToSend = 3;
				_numOfNullRequestToSkip = 20;
				_numOfMainHandlerToProcess = 10;
			}
			else
			{
				_numOfRequestToSend = 50;
				_numOfNullRequestToSkip = 300;
				_numOfMainHandlerToProcess = 500;
			}
		}
		else
		{
			_numOfRequestToSend = 4;
			_numOfNullRequestToSkip = 30;
			_numOfMainHandlerToProcess = 15;
		}

	}
	//----------------------------------------------------------------
	void MainThreadMessageManager::forceToSynModeAndDealWithAllRequests()
	{
		_forceToSynMode = true;

		int baknumOfRequestToSend = _numOfRequestToSend;
		int baknumOfNullRequestToSkip = _numOfNullRequestToSkip;
		int baknumOfMainHandlerToProcess = _numOfMainHandlerToProcess;

		_numOfRequestToSend = -1;
		_numOfNullRequestToSkip = -1;
		_numOfMainHandlerToProcess = -1;

		doRequests();

		_numOfRequestToSend = baknumOfRequestToSend;
		_numOfNullRequestToSkip = baknumOfNullRequestToSkip;
		_numOfMainHandlerToProcess = baknumOfMainHandlerToProcess;

		_forceToSynMode = false;
	}
	//----------------------------------------------------------------

	
}// end of namespace vgAsyn
