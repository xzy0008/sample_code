



#ifndef __VGAIOREQUEST_H__
#define __VGAIOREQUEST_H__
#include <vgAsyn/vgaDefinition.h>
#include <vgKernel/vgkForward.h>
#include <vgAsyn/vgaIoRequestStruct.h>
#include <vgAsyn/vgaFileInfo.h>


namespace vgAsyn {




	/**
		@date 	2008/06/20  15:39	
		@author  leven
	
		@brief 	
			注意事项:
				1.本类自己负责在ioRequstHandlerFunc或者
				mainThreadHandlerFunc中删除自身,即要执行:
					delete request;
				2.区别2个线程中的不同的操作函数.
				 首先执行ioRequstHandlerFunc,如果在这个函数中
				 执行了dispatchMainThreadFunc,则_mainThreadFunc会执行,
				 反之不予执行,参照IoRequestExtractVgimg类.
				3.对于读取到的buffer,有时候希望自动删除(比如texture创建完成后)
				有时候希望不自动删除(比如顶点数组形式渲染),只要设置标志位即可:
					void setDeleteBufferFlag( const bool& flag )
	
				4.可以实例化,但是注意没有自动删除.
				若要自动删除功能,请在anotherThreadHandler或者mainThreadHandler
				中添加delete this语句.
				
				//08-11-8添加.

		@see    
	*/
	class  VGA_EXPORT IoRequest
	{
	public:
		// 注意,本类负责delete
		IoRequest( FileInfo* fileinfo ); 

		virtual ~IoRequest();

		/**
			若run_immediately = true,此时立即发送,不放入
			队列排队
		*/
		void sendRequestAndDoAsynHandlerFunc( 
			const bool& run_immediately = false );

		/**
			由于每帧发送的数据包很多,故需要做限制
			当数据包堆积很多时,有些io请求就不需要再次发送.
			这个函数会在sendRequestAndDoAsynHandlerFunc之后
			检查,若不需要,则删除自身(在MainThreadMessageManager中).
			默认为发送
			for MainThreadMessageManager only
		*/
		bool isReallyNeedToSend()
		{
			return true;
		}

		/**
			for MainThreadMessageManager only
		*/
		void sendRequestAndDoAsynHandlerFuncImpl();

		void handleRequest()
		{
			anotherThreadHandler();
		}

		void handleMainThreadRequest()
		{
			mainThreadHandler();
		}


		virtual bool anotherThreadHandler()
		{
			return true;
		}

		virtual bool mainThreadHandler()
		{
			return true;
		}

		/**
			是否为异步模式.默认为异步模式
			true --> 异步模式
		*/
		void setAsynchronousMode( const bool& async_mode )
		{
			_requestStruct->setAsynMode( async_mode );
		}

		/**
			得到异步模式标志  
			true --> 异步模式
		*/
		bool getAsynChronousMode() const
		{
			return _requestStruct->isAsynMode();
		}


		void dispatchMainThreadFunc();

		void setDeleteBufferFlag( const bool& flag )
		{
			_deleteBufferWhenDestruction = flag;
		}
	
		char* getBuffer() const
		{
			return _buffer;
		}

		inline long getBufferSize() const
		{
			return _fileInfo->_fileSize;
		}

		inline FileInfo* getFileInfoClone()
		{
			return _fileInfo->clone();
		}

		inline FileInfo* getFileInfoRef() 
		{
			return _fileInfo;
		}

		inline bool getPriority() const
		{
			return _priority;
		}

		inline void setPriority( const bool& priority )
		{
			_priority = priority;
		}

	protected:

		// 优先级
		// true为高优先级
		// false是低优先级
		volatile bool _priority;

		bool _deleteBufferWhenDestruction;

		FileInfo* _fileInfo;

		char* _buffer;

		IoRequestStruct* _requestStruct;
	
	};
	

	typedef std::vector<IoRequest> IoRequestVector;



	
}// end of namespace vgAsyn

#endif // end of __VGAIOREQUEST_H__