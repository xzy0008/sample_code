


#include <vgStableHeaders.h>
#include <vgAsyn/vgaIoRequest.h>
#include <vgAsyn/vgaMainThreadMessageManager.h>

#include <vgAsyn/vgaMemoryFileManager.h>



namespace vgAsyn {
	
	
	
	
	//----------------------------------------------------------------
	IoRequest::IoRequest( FileInfo* fileinfo )
		: _fileInfo( fileinfo ),
		_deleteBufferWhenDestruction( true ),
		_buffer( NULL ),
		_priority( false ),
		_requestStruct( NULL )
	{
		assert( fileinfo != NULL );
		assert( _fileInfo->_fileSize > 0 );

		_requestStruct = new IoRequestStruct( this , 
			fileinfo->_fileOffset , fileinfo->_fileSize );
	}
	//----------------------------------------------------------------
	IoRequest::~IoRequest()
	{
		if ( _fileInfo != NULL )
		{
			delete _fileInfo;
			_fileInfo = NULL;
		}

		if ( _deleteBufferWhenDestruction == true )
		{
			if ( _buffer != NULL )
			{
				delete[] _buffer;
				_buffer = NULL;
			}
		}

		if ( _requestStruct != NULL )
		{
			delete _requestStruct;
			_requestStruct = NULL;
		}
	}
	//----------------------------------------------------------------
	void IoRequest::dispatchMainThreadFunc()
	{
		if ( _requestStruct->isAsynMode() == false )
		{
			// 同步模式时只要直接执行即可.
			handleMainThreadRequest();
		}
		else
		{
			MainThreadMessageManager::getSingleton().pushMainHandlerOfIoRequest( this );
		}
	}
	//----------------------------------------------------------------
	void IoRequest::sendRequestAndDoAsynHandlerFunc(const bool& run_immediately /*= false*/)
	{
		if ( _requestStruct->isAsynMode() == false ||
			run_immediately == true )
		{
			//------------------------------------------
			// 若为同步模式或者run_immediately模式,直接执行即可
			//------------------------------------------
			sendRequestAndDoAsynHandlerFuncImpl();
		}
		else
		{
			//------------------------------------------
			// 限制每一帧发送的数据包的数量
			//------------------------------------------
			MainThreadMessageManager::getSingleton().pushSenderOfIoRequest( this );
		}
	}
	//----------------------------------------------------------------
	void IoRequest::sendRequestAndDoAsynHandlerFuncImpl()
	{
		assert( _fileInfo->_fileHandle != NULL );
		//------------------------------------------
		// 首先从内存文件中进行查找
		//------------------------------------------
		char* bufread = 
			MemoryFileManager::getSingleton().readFromMemory( _fileInfo );

		if ( bufread != NULL )
		{
			// 这个时候直接读到了。
			_buffer = bufread;
			handleRequest();
			return;
		}


		//------------------------------------------
		// buffer在这里申请.
		// 如果在构造函数中申请,有可能会报内存ERROR_NOACCESS错误.
		//------------------------------------------
		if( _buffer != NULL )
		{
			assert(0);
		}

		if ( _buffer == NULL )
		{
			_buffer = new char[ _requestStruct->_readSize ];
		}
		assert( _buffer != NULL );

		//------------------------------------------
		// 开始正式读取数据
		//------------------------------------------
		bool readret = _fileInfo->_fileHandle->doRead( _buffer , _requestStruct );

		assert( readret == true );

		if ( readret == false )
		{
			MessageBox( NULL , "致命错误" , "Error!!" , MB_OK );
			return;
		}
	}
	//----------------------------------------------------------------



}// end of namespace vgAsyn
