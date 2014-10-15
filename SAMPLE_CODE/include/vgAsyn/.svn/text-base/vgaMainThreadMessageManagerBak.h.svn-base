


#define VGA_USE_LOCKFREE	0


#if VGA_USE_LOCKFREE

	/**
		@date 	2008/06/25  9:58	
		@author  leven
	
		@brief 	负责事项:
			1.IoRequest的dispatchMainThreadFunc()执行之后返回主线程
			执行bool IoRequestTextureLod::mainThreadHandler();函数.
			2.负责每一帧发送的IoRequest数量.
	
		@see    
	*/
	class MainThreadMessageManager : 
		public vgKernel::Singleton<MainThreadMessageManager>
	{
		typedef LockFreeTech::MSQueue<IoRequest*> RequestPipe;
		typedef std::deque<IoRequest*> RequestPipeSender;

		friend class vgKernel::Singleton<MainThreadMessageManager>;
	private:
		MainThreadMessageManager() 
			: Singleton<MainThreadMessageManager>( VGK_SINGLETON_LEFE_MAINTHREADMGR ) 
		{
			VGK_TRACE(_T("MainThreadMessageManager created."));
		}
		~MainThreadMessageManager()
		{
			VGK_TRACE(_T("MainThreadMessageManager destroyed."));
		}

	protected:
		virtual bool initialise()
		{
			return true;
		}
		virtual bool shutdown();

	public:

		void clearAllData();

		/**
			(负责事项1)负责添加其他线程返回主线程的函数处理.
		*/
		void pushMainHandlerOfIoRequest( IoRequest* request );


		/**
			做2件事:
			1.发送每帧的io请求(在这里可以限制发送的数量)
			2.处理其他线程返回的IoRequest来处理mainHandler
		*/
		void doRequests();
	

		/**
			(负责事项2)负责添加IO请求
		*/
		void pushSenderOfIoRequest( IoRequest* request );

	
	private:

		/**
			(负责事项1)负责处理主线程函数
		*/
		void doMainHandlerOfRequests();

		/**
			(负责事项2)负责发送IO请求
		*/
		void doSenderOfRequests();

		/**
			负责收集mainhandler的数据.
		*/
		RequestPipe _requestsOfMainHandler;
		//RequestPipe _requestBufOfMainHandler;


		/**
			负责每帧发送IO请求的Pipe
		*/
		RequestPipeSender _requestsOfSender;

	};
	
#endif


	namespace vgAsyn {

#if VGA_USE_LOCKFREE

		//----------------------------------------------------------------
		void MainThreadMessageManager::doRequests()
		{
			doMainHandlerOfRequests();
			doSenderOfRequests();
		}
		//----------------------------------------------------------------
		void MainThreadMessageManager::pushMainHandlerOfIoRequest( IoRequest* request )
		{
			//bool priority = request->getPriority();


			assert( request != NULL );


			_requestsOfMainHandler.enqueue( request );

			//if ( priority == true )
			//{
			//	_requestsOfMainHandler.push_front( request );
			//}
			//else
			//{
			//	_requestsOfMainHandler.push_back( request );
			//}
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

			const int max_num = 4;
			const int max_null_num = 20;

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

#if _DEBUG

			//if( _requestBufOfMainHandler.empty() == false )
			//{
			//	assert(0);
			//}

			//IoRequest* tmp = NULL;
			//if ( _request)
			//{
			//}

#endif


			//assert( _requestBufOfMainHandler.empty() == true );
			//_requestsSectOfMainHandler.enter();
			//------------------------------------------
			// 从中拷贝一定数量的请求
			//------------------------------------------
			const int max_buf_size = 15;
			IoRequest* treq = NULL;
			for ( int i = 0 ; i < max_buf_size ; ++i )
			{
				if ( _requestsOfMainHandler.dequeue( treq ) == false )
				{
					break;
				}

				treq->handleMainThreadRequest();
			}

			return;
		}
		//----------------------------------------------------------------
		bool MainThreadMessageManager::shutdown()
		{
			clearAllData();

			return true;
		}
		//----------------------------------------------------------------
		void MainThreadMessageManager::clearAllData()
		{
			{
				RequestPipeSender::iterator iter = _requestsOfSender.begin();
				RequestPipeSender::iterator iter_end = _requestsOfSender.end();

				for ( ; iter != iter_end ; ++iter )
				{
					IoRequest* req = *iter;
					delete req;
				}
				_requestsOfSender.clear();
			}



			{

				IoRequest* tmp = NULL;

				while ( _requestsOfMainHandler.dequeue( tmp ) )
				{
					delete tmp;
					tmp = NULL;
				}
			}

			{

				//IoRequest* tmp = NULL;

				//while ( _requestBufOfMainHandler.dequeue( tmp ) )
				//{
				//	delete tmp;
				//	tmp = NULL;
				//}
			}
		}
		//----------------------------------------------------------------

#endif

		}
