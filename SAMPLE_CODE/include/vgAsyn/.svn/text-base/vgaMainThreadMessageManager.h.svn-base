


#ifndef __VGAMAINTHREADMESSAGEMANAGER_H__
#define __VGAMAINTHREADMESSAGEMANAGER_H__
#include <vgAsyn/vgaDefinition.h>
#include <vgKernel/vgkForward.h>
#include <vgKernel/vgkSingleton.h>
#include <vgKernel/vgkTrace.h>
#include <vgThreads/CriticalSection.h>
#include <vgAsyn/vgaIoRequest.h>

#include <vgAsyn/LockFreeQ.h>
#include <vgKernel/vgkRenderCommand.h>

namespace vgAsyn {



	/**
		@date 	2008/06/25  9:58	
		@author  leven
	
		@brief 	负责事项:
			1.IoRequest的dispatchMainThreadFunc()执行之后返回主线程
			执行bool IoRequestTextureLod::mainThreadHandler();函数.
			2.负责每一帧发送的IoRequest数量.
	
		@see    
	*/
	class  VGA_EXPORT MainThreadMessageManager : 
		public vgKernel::Singleton<MainThreadMessageManager>
	{
		typedef std::deque<IoRequest*> RequestPipe;

		friend class vgKernel::Singleton<MainThreadMessageManager>;
	private:
		MainThreadMessageManager();
		~MainThreadMessageManager();

	protected:
		virtual bool initialise();
		virtual bool shutdown();

	public:

		virtual void reset(){};//need to write

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


		int getNumOfRequestToSend() const
		{ 
			return _numOfRequestToSend; 
		}

		void setNumOfRequestToSend( const int& val ) 
		{ 
			_numOfRequestToSend = val; 
		}
		int getNumOfNullRequestToSkip() const
		{ 
			return _numOfNullRequestToSkip; 
		}

		void setNumOfNullRequestToSkip( const int& val ) 
		{ 
			_numOfNullRequestToSkip = val; 
		}

		int getNumOfMainHandlerToProcess() const
		{ 
			return _numOfMainHandlerToProcess; 
		}

		void setNumOfMainHandlerToProcess( const int& val ) 
		{ 
			_numOfMainHandlerToProcess = val; 
		}

		void renderBegin();

		void forceToSynModeAndDealWithAllRequests();

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
		RequestPipe _requestBufOfMainHandler;
		vgThreads::CriticalSection _requestsSectOfMainHandler;

		/**
			负责每帧发送IO请求的Pipe
		*/
		RequestPipe _requestsOfSender;

		int _numOfRequestToSend;
		int _numOfNullRequestToSkip;
		int _numOfMainHandlerToProcess;

		bool _forceToSynMode;

		vgKernel::RenderCommand *m_renderBeginCommand;

	};
	

	
	
}// end of namespace vgAsyn

#endif // end of __VGAMAINTHREADMESSAGEMANAGER_H__