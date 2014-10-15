


#include <vgStableHeaders.h>
#include <vgAsyn/vgaIoRequest.h>
#include <vgAsyn/vgaFileHandle.h>
#include <vgAsyn/vgaIoRequestStruct.h>
#include <vgAsyn/vgaFileInfo.h>
#include <vgAsyn/vgaIoServer.h>
#include <vgKernel/vgkStreamWriter.h>
#include <vgKernel/vgkStreamReader.h>

namespace vgAsyn {
	
	
	
	
	//----------------------------------------------------------------
	FileHandle::FileHandle( String filepath )
	{
		_filePath = filepath;
		_fileHandle = INVALID_HANDLE_VALUE;
		_isOpened = false;
		setOpenAccess( FILEHANDLE_OPENACESS_READ );
	}
	//----------------------------------------------------------------
	FileHandle::~FileHandle()
	{
		close();
	}
	//----------------------------------------------------------------
	bool FileHandle::copyWholeFile( const String& out_filename )
	{
		assert( isOpened() );
		if ( isOpened() == false )
		{
			return false;
		}

		vgKernel::StreamWriterPtr pwriter =
			vgKernel::StreamWriterFactory::createFromFile( out_filename );

		if ( pwriter.isNull() )
		{
			return false;
		}

		DWORD filesize = getFileSize();
		assert( filesize > 0 );
		if ( filesize <= 0 )
		{
			return false;
		}




		// 默认取16M为读取的单位
		const int metasize = 1024 * 1024 * 16; 

		char* buf = new char[ metasize ];

		int i = 0;
		int metanum = (filesize + metasize ) / metasize;

		for ( ; i < metanum ; ++ i )
		{
			long readsize = metasize;
			if ( ( i + 1 ) == metanum )
			{
				readsize = filesize % metasize;
			}

			IoRequestStruct iostruct( NULL , metasize * i , readsize );
			iostruct.setAsynMode( false );

			bool readok = doRead( buf , &iostruct );
			assert( readok == true );

			if ( readok == false )
			{
				delete[] buf;

				return false;
			}
			else
			{
				pwriter->write( buf, readsize );
			}
		}

		return true;
	}
	//----------------------------------------------------------------


	//----------------------------------------------------------------
	HANDLE FileHandle::getHandle()
	{
		if ( _isOpened == false )
		{
			bool ret = open();
			if ( ret == false )
			{
				assert(0);
			}
		}

		if ( _fileHandle == INVALID_HANDLE_VALUE )
		{
			assert(0);
		}

		return _fileHandle;
	}
	//----------------------------------------------------------------
	bool FileHandle::doRead( char* buf , IoRequestStruct *prequest )
	{
		assert( (_openAccess & FILEHANDLE_OPENACESS_READ) != 0 );
		assert( buf != NULL );

		if ( _isOpened == false)
		{ 
			assert(0);

			//bool ret = open();
			//assert( ret == true );

			//// 再次检查
			//if ( _isOpened == false )
			//{
				return false;
			//}
		}

		DWORD NumberOfBytesRead = 0; 

		int err;

		err = GetLastError();


		assert( _fileHandle != INVALID_HANDLE_VALUE );
		// Request the data
		BOOL bResult = ReadFile(
			_fileHandle,
			buf,
			prequest->_readSize,
			&NumberOfBytesRead,
			prequest );


		err = GetLastError();

		if ( err == ERROR_ACCESS_DENIED )
		{
			// 此时进行重试
			int tries = 0;
			do 
			{
				Sleep( 100 );

				BOOL bResult = ReadFile(
					_fileHandle,
					buf,
					prequest->_readSize,
					&NumberOfBytesRead,
					prequest );

				tries++;
				if ( tries > 4 )
					break;

				err = GetLastError();

			} while( err == ERROR_ACCESS_DENIED );
		}

		if ( err != ERROR_IO_PENDING&&
			err != ERROR_SUCCESS  )
		{
			assert(0&&"err == ERROR_IO_PENDING||err == ERROR_SUCCESS");
		}

		//------------------------------------------
		// 如果直接返回,情况如下:
		// 1.多线程条件下,表示正确处理了request或者表示
		//   hEvent最低位置1情况下不引发IOCP packet情形.
		// 2.单线程条件下,表示正确处理了请求,可以处理数据.
		//------------------------------------------
		if ( prequest->hEvent != 0 )
		{
			::WaitForSingleObject( prequest->hEvent , INFINITE );
			assert(err == ERROR_IO_PENDING||
				err == ERROR_SUCCESS );


#if _DEBUG
			if ( bResult == TRUE )
			{
				assert( prequest->_readSize == NumberOfBytesRead );
			}
#endif
			// 此时为同步操作
			if( prequest->getIoRequest() != NULL )
			{
				prequest->getIoRequest()->handleRequest();
			}

			return true;
		}


		// It succeeded immediately, but do not process it
		// here, wait for the completion packet.
		if ( bResult == TRUE )
		{
			if ( IoServer::getSingleton().isMultithreadMode() == false )
			{
				assert( err == ERROR_SUCCESS );

				// 此时为同步操作
				assert( prequest->_readSize == NumberOfBytesRead );
				if( prequest->getIoRequest() != NULL )
				{
					prequest->getIoRequest()->handleRequest();
				}
			}
			else
			{
				assert(err == ERROR_IO_PENDING||
					err == ERROR_SUCCESS );
			}

			return true;
		}

		// This is what we want to happen, it's not an error
		if (err == ERROR_IO_PENDING)
		{
			return true;
		}

		//------------------------------------------
		// 到了这里,不正常
		//------------------------------------------
		assert(0);


		return false;
	}
	//----------------------------------------------------------------
	void FileHandle::close()
	{
		if ( _isOpened == false)
		{
			return;
		}

		if ( _fileHandle != INVALID_HANDLE_VALUE)
		{
			CloseHandle( _fileHandle );
			_fileHandle = INVALID_HANDLE_VALUE;
		}
	}
	//----------------------------------------------------------------
	bool FileHandle::open()
	{
		if ( _isOpened == true)
		{
			return true;
		}

		if ( IoServer::getSingleton().isMultithreadMode() == true )
		{
			_fileHandle = CreateFile(
				_filePath.c_str() , _openAccess,
				FILE_SHARE_READ /*| FILE_SHARE_WRITE*/, NULL , 
				OPEN_EXISTING , FILE_FLAG_OVERLAPPED , NULL );
		}
		else
		{
			_fileHandle = CreateFile(
				_filePath.c_str() , _openAccess ,
				FILE_SHARE_READ , NULL , 
				OPEN_EXISTING , NULL/*FILE_FLAG_OVERLAPPED*/ , NULL );
		}


		VG_ASYN_VERIFY( _fileHandle );

		assert( _fileHandle != INVALID_HANDLE_VALUE );

		_isOpened = true;
		return true;
	}
	//----------------------------------------------------------------
	DWORD FileHandle::getFileSize()
	{
		if ( _isOpened == false)
		{ 
			bool ret = open();
			assert( ret == true );

			// 再次检查
			if ( _isOpened == false )
			{
				return NULL;
			}
		}

		return GetFileSize( _fileHandle , NULL );
	}
	//----------------------------------------------------------------
	bool FileHandle::doWrite( char* buf, IoRequestStruct* prequest )
	{
		assert( (_openAccess & FILEHANDLE_OPENACESS_WRITE ) != 0 );
		assert( buf != NULL );

		if ( _isOpened == false)
		{ 
			assert(0);

			//bool ret = open();
			//assert( ret == true );

			//// 再次检查
			//if ( _isOpened == false )
			//{
			return false;
			//}
		}

		// 确定是同步模式.
		assert( prequest->getIoRequest()->getAsynChronousMode() == false );

		DWORD NumberOfBytesWrite = 0; 


		assert( _fileHandle != INVALID_HANDLE_VALUE );
		// Request the data
		BOOL bResult = WriteFile(
			_fileHandle,
			buf,
			prequest->_readSize,
			&NumberOfBytesWrite,
			prequest );


		int err = GetLastError();

		//------------------------------------------
		// 如果直接返回,情况如下:
		// 1.多线程条件下,表示正确处理了request或者表示
		//   hEvent最低位置1情况下不引发IOCP packet情形.
		// 2.单线程条件下,表示正确处理了请求,可以处理数据.
		//------------------------------------------
		assert(  prequest->hEvent != 0 ); // 确定是同步模式.
		if ( prequest->hEvent != 0 )
		{
			::WaitForSingleObject( prequest->hEvent , INFINITE );
			if(err == ERROR_IO_PENDING||
				err == ERROR_SUCCESS )
			{

			}
			else
			{
				assert(0);
			}


#if _DEBUG
			if ( bResult == TRUE )
			{
				assert( prequest->_readSize == NumberOfBytesWrite );
			}
#endif
			// 此时为同步操作
			prequest->getIoRequest()->handleRequest();

			return true;
		}

		assert(0);

		return false;
#if 0

		// It succeeded immediately, but do not process it
		// here, wait for the completion packet.
		if ( bResult == TRUE )
		{
			if ( IoServer::getSingleton().isMultithreadMode() == false )
			{
				assert( err == ERROR_SUCCESS );

				// 此时为同步操作
				assert( prequest->_readSize == NumberOfBytesWrite );
				prequest->getIoRequest()->handleRequest();
			}
			else
			{
				assert(err == ERROR_IO_PENDING||
					err == ERROR_SUCCESS );
			}

			return true;
		}

		// This is what we want to happen, it's not an error
		if (err == ERROR_IO_PENDING)
		{
			return true;
		}

		//------------------------------------------
		// 到了这里,不正常
		//------------------------------------------
		assert(0);


		return false;

#endif
	}
	//----------------------------------------------------------------
	bool FileHandle::readWholeFileToMemory( char*& out_buf, long& out_filesize )
	{
		assert( isOpened() );
		if ( isOpened() == false )
		{
			return false;
		}

		DWORD filesize = getFileSize();
		assert( filesize > 0 );
		if ( filesize <= 0 )
		{
			return false;
		}

		char* buf = new char[ filesize ];


		// 默认取16M为读取的单位
		const int metasize = 1024 * 1024 * 16; 

		int i = 0;
		int metanum = (filesize + metasize ) / metasize;

		for ( ; i < metanum ; ++ i )
		{
			long readsize = metasize;
			if ( ( i + 1 ) == metanum )
			{
				readsize = filesize % metasize;
			}

			IoRequestStruct iostruct( NULL , metasize * i , readsize );
			iostruct.setAsynMode( false );

			bool readok = doRead( buf + metasize * i , &iostruct );
			assert( readok == true );

			if ( readok == false )
			{
				delete[] buf;
				return false;
			}
		}

		out_buf = buf;
		out_filesize = filesize;

		return true;
	}
	//----------------------------------------------------------------





}// end of namespace vgAsyn
