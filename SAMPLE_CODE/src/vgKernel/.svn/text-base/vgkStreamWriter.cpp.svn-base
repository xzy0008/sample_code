



#include <vgStableHeaders.h>
#include <vgKernel/vgkStreamWriter.h>
#include <vgKernel/vgkStreamReader.h>
#include <vgKernel/vgkWarning.h>


namespace vgKernel {




	//----------------------------------------------------------------
	FileStreamWriter::FileStreamWriter( const String& filename )
		: StreamWriter()
	{
		setDefault();

		create( filename );
	}
	//----------------------------------------------------------------
	size_t FileStreamWriter::write( void* src , const size_t& count )
	{
		assert( isValid() );
		assert( src != NULL );

		DWORD writebytes = 0;

		BOOL writeres = WriteFile(
			hFile,
			src,
			count,
			&writebytes,
			NULL);

		assert( writeres == TRUE );

		return writebytes;
	}
	//----------------------------------------------------------------
	long FileStreamWriter::seek( const long& pos )
	{
		assert( isValid() );

		assert( pos >= 0 );

		DWORD dwCurrentFilePosition; 

		dwCurrentFilePosition = SetFilePointer( 
			hFile, // must have GENERIC_READ and/or GENERIC_WRITE 
			pos,     // do not move pointer 
			NULL,  // hFile is not large enough to need this pointer 
			FILE_BEGIN);  // provides offset from current position 

		return dwCurrentFilePosition;
	}
	//----------------------------------------------------------------
	long FileStreamWriter::seek( const long& offset , const StreamWriterSeekMethod& seekdir )
	{
		assert( isValid() );


		DWORD method;

		if ( seekdir == STREAMWRITER_SEEK_BEGIN )
		{
			method = FILE_BEGIN;
		}
		else if (seekdir == STREAMWRITER_SEEK_CURRENT )
		{
			method = FILE_CURRENT;
		}
		else if (seekdir == STREAMWRITER_SEEK_END )
		{
			method = FILE_END;
		}
		else
		{
			assert(0);
		}

		DWORD dwCurrentFilePosition; 

		dwCurrentFilePosition = SetFilePointer( 
			hFile, // must have GENERIC_READ and/or GENERIC_WRITE 
			offset,     // do not move pointer 
			NULL,  // hFile is not large enough to need this pointer 
			method);  // provides offset from current position 

		return dwCurrentFilePosition;
	}
	//----------------------------------------------------------------
	long FileStreamWriter::tell()
	{
		assert( isValid() );

		DWORD dwCurrentFilePosition; 

		dwCurrentFilePosition = SetFilePointer( 
			hFile, // must have GENERIC_READ and/or GENERIC_WRITE 
			0,     // do not move pointer 
			NULL,  // hFile is not large enough to need this pointer 
			FILE_CURRENT);  // provides offset from current position 

		return dwCurrentFilePosition;
	}
	//----------------------------------------------------------------
	void FileStreamWriter::close()
	{
		if ( mClosed == false )
		{
			assert( hFile != INVALID_HANDLE_VALUE );
			CloseHandle( hFile );
			hFile = INVALID_HANDLE_VALUE;

			mClosed = true;
		}
	}
	//----------------------------------------------------------------

	//----------------------------------------------------------------
	FileStreamWriterPtr StreamWriterFactory::createFromFile( 
		const String& abs_filename ,const bool& warn_exist /*== false*/ )
	{
		if ( warn_exist == true )
		{
			//警告用户
			StreamReaderPtr filereader = 
				StreamReaderFactory::createFromFile( abs_filename );

			if ( filereader.isNull() == false )
			{
				std::ostringstream o;

				o << "文件 " << abs_filename << " 已存在, 写入将覆盖原始文件, 继续吗?";

				int ret = VGK_WARN( vgKernel::Warning::WARN_INTERNAL_WARNING , 
					vgKernel::Warning::BUTTON_YES_NO , 
					o.str(),
					"StreamWriterFactory::createFromFile");

				if ( ret == vgKernel::Warning::RETURN_NO )
				{
					return FileStreamWriterPtr();
				}
			}
		}

		return FileStreamWriterPtr( new FileStreamWriter( abs_filename ) );
	}
	//----------------------------------------------------------------
	//----------------------------------------------------------------
#if VGK_STREAMREADER_SUPPORT_CFILE
	CFileStreamWriterPtr StreamWriterFactory::createFromCFile( CFile* cfile , 
		bool deleteondestroy )
	{
		CFileStreamWriter* pwriter = 
			new CFileStreamWriter( cfile , deleteondestroy );

		if ( pwriter->isValid() )
		{
			return CFileStreamWriterPtr( pwriter );
		}

		delete pwriter;

		return CFileStreamWriterPtr();
	}
#endif
	//----------------------------------------------------------------

#if VGK_STREAMWRITER_SUPPORT_CFILE
	//----------------------------------------------------------------
	CFileStreamWriter::CFileStreamWriter() 
		: StreamWriter()
	{
		setDefault();
	}
	//----------------------------------------------------------------
	CFileStreamWriter::CFileStreamWriter( CFile* cfile , bool deleteondestroy /*= false */ ) 
		: StreamWriter()
	{
		setDefault();

		wrapCFilePointer( cfile , deleteondestroy );
	}
	//----------------------------------------------------------------
	CFileStreamWriter::~CFileStreamWriter()
	{
		destroy();
	}
	//----------------------------------------------------------------
	bool CFileStreamWriter::create( const String& filename )
	{
		destroy();
		return createCFileImpl( filename );
	}
	//----------------------------------------------------------------
	size_t CFileStreamWriter::write( void* src , const size_t& count )
	{
		try
		{
			_cFile->Write( src , count );
		}
		catch (...)
		{
			MessageBox( NULL , "写入失败!" , "ERROR" , MB_OK );
			return 0;
		}

		return count;
	}
	//----------------------------------------------------------------
	long CFileStreamWriter::seek( const long& pos )
	{
		assert( isValid() );
		return _cFile->Seek( pos , CFile::begin );
	}
	//----------------------------------------------------------------
	long CFileStreamWriter::seek( const long& offset , const StreamWriterSeekMethod& seekdir )
	{
		assert( isValid() );

		CFile::SeekPosition method;

		if ( seekdir == STREAMWRITER_SEEK_BEGIN )
		{
			method = CFile::begin;
		}
		else if (seekdir == STREAMWRITER_SEEK_CURRENT )
		{
			method = CFile::current;
		}
		else if (seekdir == STREAMWRITER_SEEK_END )
		{
			method = CFile::end;
		}
		else
		{
			assert(0);
		}

		return _cFile->Seek( offset , method );
	}
	//----------------------------------------------------------------
	void CFileStreamWriter::close()
	{
		assert( isValid() );
		_cFile->Close();
	}
	//----------------------------------------------------------------
	void CFileStreamWriter::flush()
	{
		assert( isValid() );
		_cFile->Flush();
	}
	//----------------------------------------------------------------
	bool CFileStreamWriter::wrapCFilePointer( CFile* cfile , 
		bool deleteondestroy /*= false */ )
	{
		if ( cfile == NULL )
		{
			return false;
		}

		destroy();

		_cFile = cfile;
		assert( cfile != NULL );
		_deleteOnDestroy = deleteondestroy;
		_fileAbsolutePath = _cFile->GetFilePath();
		return true;
	}
	//----------------------------------------------------------------
	void CFileStreamWriter::destroy()
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
	bool CFileStreamWriter::createCFileImpl( const String& filepath )
	{
		assert( isValid() == false );

		_cFile = new CFile;
		BOOL openok = _cFile->Open( filepath.c_str() , 
			CFile::modeWrite | CFile::modeCreate);

		if ( openok == TRUE )
		{
			_fileAbsolutePath = _cFile->GetFilePath();
			_deleteOnDestroy = true;
			return true;
		}

		destroy();
		return false;
	}
	//----------------------------------------------------------------
	long CFileStreamWriter::tell()
	{
		assert( isValid() );
		return _cFile->GetPosition();
	}
	//----------------------------------------------------------------
#endif


}// end of namespace vgKernel
