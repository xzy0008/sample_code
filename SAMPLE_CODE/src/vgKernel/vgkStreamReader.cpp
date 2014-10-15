


#include <vgStableHeaders.h>
#include <vgKernel/vgkStreamReader.h>


namespace vgKernel {




	//----------------------------------------------------------------
	FileStreamReader::FileStreamReader()
		: StreamReader()
	{
		_isValid = false;
		_filehandle = INVALID_HANDLE_VALUE;
		mSize = 0;
		mName = "";
	}
	//----------------------------------------------------------------
	FileStreamReader::FileStreamReader( const String& filename )
		: StreamReader()
	{
		_isValid = false;
		_filehandle = INVALID_HANDLE_VALUE;

		create( filename );
	}
	//----------------------------------------------------------------
	FileStreamReader::~FileStreamReader()
	{
		if( _isValid == true )
		{
			close();
		}
	}
	//----------------------------------------------------------------
	bool FileStreamReader::create( const String& filename )
	{
		// Open the file
		_filehandle = CreateFile(filename.c_str(),
			GENERIC_READ,
			FILE_SHARE_READ,
			NULL,
			OPEN_EXISTING,
			//FILE_ATTRIBUTE_ARCHIVE | FILE_ATTRIBUTE_HIDDEN | FILE_ATTRIBUTE_READONLY | FILE_ATTRIBUTE_SYSTEM | FILE_FLAG_SEQUENTIAL_SCAN,
			NULL,
			NULL);

		if( _filehandle == INVALID_HANDLE_VALUE)
		{
			return false;
		}

		DWORD err = GetLastError();
		assert( err == ERROR_SUCCESS );

		assert( _filehandle != INVALID_HANDLE_VALUE );

		//------------------------------------------
		// 得到文件的大小
		//------------------------------------------
		DWORD filesize = GetFileSize( _filehandle , NULL);
		assert( filesize >= 0 );
		assert( filesize != INVALID_FILE_SIZE );

		if ( filesize == INVALID_FILE_SIZE )
		{
			assert(0&&"待补充");
			return false;
		}

		//------------------------------------------
		// 最后赋值
		//------------------------------------------
		mSize = filesize;
		mName = filename;

		_isValid = true;

		return true;
	}
	//----------------------------------------------------------------

	size_t FileStreamReader::read( void* buf, size_t count )
	{
		assert( _isValid == true );
		assert( buf != NULL );
		assert( count > 0 );

		DWORD dwBytesRead = 0;
		BOOL bSuccess = ReadFile( _filehandle, 
			buf, 
			(DWORD)count, 
			&dwBytesRead, 
			NULL);

		assert( bSuccess == TRUE );
		if ( bSuccess == FALSE )
		{
			return 0;
		}

		if( count != dwBytesRead )
		{
			assert(0);
		}

		return dwBytesRead;
	}
	//----------------------------------------------------------------
	void FileStreamReader::skip( long count )
	{
		assert( _isValid == true );

		assert( count > 0 );

		DWORD dwCurrentFilePosition; 

		dwCurrentFilePosition = SetFilePointer( 
			_filehandle, // must have GENERIC_READ and/or GENERIC_WRITE 
			count,     // do not move pointer 
			NULL,  // hFile is not large enough to need this pointer 
			FILE_CURRENT);  // provides offset from current position
	}
	//----------------------------------------------------------------
	void FileStreamReader::seek( size_t pos )
	{
		assert( _isValid == true );

		assert( pos >= 0 );

		DWORD dwCurrentFilePosition; 

		dwCurrentFilePosition = SetFilePointer( 
			_filehandle, // must have GENERIC_READ and/or GENERIC_WRITE 
			(LONG)pos,     // do not move pointer 
			NULL,  // hFile is not large enough to need this pointer 
			FILE_BEGIN);  // provides offset from current position 

		assert( dwCurrentFilePosition == pos );
	}
	//----------------------------------------------------------------
	size_t FileStreamReader::tell( void ) 
	{
		if ( _isValid == false )
		{
			assert(0);
		}

		assert( _isValid == true );

		DWORD dwCurrentFilePosition; 

		dwCurrentFilePosition = SetFilePointer( 
			_filehandle, // must have GENERIC_READ and/or GENERIC_WRITE 
			0,     // do not move pointer 
			NULL,  // hFile is not large enough to need this pointer 
			FILE_CURRENT);  // provides offset from current position 

		return dwCurrentFilePosition;
	}
	//----------------------------------------------------------------
	bool FileStreamReader::eof( void ) 
	{
		if ( tell() == mSize )
		{
			return true;
		}

		return false;
	}

	void FileStreamReader::close( void )
	{
		assert( _isValid == true );
		CloseHandle( _filehandle );
		_filehandle = INVALID_HANDLE_VALUE ;
		_isValid = false;
		mSize = 0;
		mName = "";
	}
	//----------------------------------------------------------------

	//----------------------------------------------------------------
	StreamReaderPtr StreamReaderFactory::createFromFile( 
		const String& filename )
	{
#if 1
		FileStreamReader* filereader = new FileStreamReader;
		filereader->create( filename );

		if ( filereader->isValid() == true )
		{
			return StreamReaderPtr( filereader );
		}
#else

		CFile* cfile = new CFile;
		CFileException e;

		if( cfile->Open( filename.c_str() , CFile::modeRead , &e ) )
		{
			CFileStreamReader* cfilereader = 
				new CFileStreamReader( cfile );
			assert( cfilereader->isValid() );

			return StreamReaderPtr( cfilereader );
		}

		TCHAR szError[1024];
		memset( szError , 0 , 1024 );
		e.GetErrorMessage(szError, 1024);


		String ddd   = szError;


		delete cfile;
#endif

		return StreamReaderPtr();
	}
	//----------------------------------------------------------------
#if VGK_STREAMREADER_SUPPORT_CFILE
	CFileStreamReaderPtr StreamReaderFactory::createFromCFile( 
		CFile* cfile , bool deleteondestroy )
	{
		CFileStreamReader* preader = 
			new CFileStreamReader( cfile , deleteondestroy );

		if ( preader->isValid() )
		{
			return CFileStreamReaderPtr( preader );
		}

		delete preader;

		return CFileStreamReaderPtr();
	}
#endif
	//----------------------------------------------------------------

#if VGK_STREAMREADER_SUPPORT_CFILE
	//----------------------------------------------------------------
	CFileStreamReader::CFileStreamReader() : StreamReader()
	{
		setDefault();
	}
	//----------------------------------------------------------------
	CFileStreamReader::CFileStreamReader( CFile* cfile , bool deleteondestroy /*= false */ ) : StreamReader()
	{
		setDefault();

		wrapCFilePointer( cfile , deleteondestroy );
	}
	//----------------------------------------------------------------
	CFileStreamReader::~CFileStreamReader()
	{
		destroy();
	}
	//----------------------------------------------------------------
	String CFileStreamReader::getFileName()
	{
		return _fileAbsolutePath;
	}
	//----------------------------------------------------------------
	bool CFileStreamReader::create( const String& filename )
	{
		destroy();
		return createCFileImpl( filename );
	}
	//----------------------------------------------------------------
	bool CFileStreamReader::isValid()
	{
		return _cFile != NULL;
	}
	//----------------------------------------------------------------
	size_t CFileStreamReader::size( void )
	{
		assert( isValid() );
		return _size;
	}
	//----------------------------------------------------------------
	size_t CFileStreamReader::read( void* buf, size_t count )
	{
		assert( isValid() );
		return _cFile->Read( buf , (UINT)count );
	}
	//----------------------------------------------------------------
	void CFileStreamReader::skip( long count )
	{
		assert( isValid() );
		_cFile->Seek( count , CFile::current );
	}
	//----------------------------------------------------------------
	void CFileStreamReader::seek( size_t pos )
	{
		assert( isValid() );
		_cFile->Seek( pos , CFile::begin );
	}
	//----------------------------------------------------------------
	size_t CFileStreamReader::tell( void )
	{
		assert( isValid() );
		return (size_t)_cFile->GetPosition();
	}
	//----------------------------------------------------------------
	bool CFileStreamReader::eof( void )
	{
		assert( isValid() );
		if ( tell() == _size )
		{
			return true;
		}

		return false;
	}
	//----------------------------------------------------------------
	void CFileStreamReader::close( void )
	{
		assert( isValid() );
		_cFile->Close();
	}
	//----------------------------------------------------------------
	void CFileStreamReader::flush( void )
	{
		assert( isValid() );
		_cFile->Flush();
	}
	//----------------------------------------------------------------
	bool CFileStreamReader::wrapCFilePointer( CFile* cfile , bool deleteondestroy /*= false */ )
	{
		if ( cfile == NULL )
		{
			return false;
		}

		destroy();

		_cFile = cfile;
		assert( cfile != NULL );
		_size = (size_t)cfile->GetLength();
		_deleteOnDestroy = deleteondestroy;
		_fileAbsolutePath = _cFile->GetFilePath();

		return true;
	}
	//----------------------------------------------------------------
	void CFileStreamReader::setDefault()
	{
		_cFile = NULL;
		_size = 0;
		_deleteOnDestroy = false;
		_fileAbsolutePath.clear();
	}
	//----------------------------------------------------------------
	void CFileStreamReader::destroy()
	{
		if ( _deleteOnDestroy )
		{
			if ( _cFile != NULL )
			{
				delete _cFile;
			}
		}

		setDefault();
	}
	//----------------------------------------------------------------
	bool CFileStreamReader::createCFileImpl( const String& filepath )
	{
		assert( isValid() == false );

		_cFile = new CFile;
		BOOL openok = _cFile->Open( filepath.c_str() , CFile::modeRead );

		if ( openok == TRUE )
		{
			_fileAbsolutePath = _cFile->GetFilePath();
			_size = (size_t)_cFile->GetLength();
			_deleteOnDestroy = true;
			return true;
		}

		destroy();

		return false;
	}
	//----------------------------------------------------------------
#endif

}// end of namespace vgKernel
