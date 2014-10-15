


#ifndef __VGKSTREAMWRITER_H__
#define __VGKSTREAMWRITER_H__

#include <vgKernel/vgkForward.h>
#include <vgKernel/vgkSharePtr.h>

#ifdef VGK_NO_SUPPORT_MFC
#	define  VGK_STREAMWRITER_SUPPORT_CFILE	0
#else
#	define  VGK_STREAMWRITER_SUPPORT_CFILE	1
#endif

#define  VGK_FILESTREAMWRITER_DESC  "FileStreamWriter"
#define  VGK_CFILESTREAMWRITER_DESC  "CFileStreamWriter"

	
namespace vgKernel {

	enum StreamWriterSeekMethod
	{
		STREAMWRITER_SEEK_BEGIN,
		STREAMWRITER_SEEK_END,
		STREAMWRITER_SEEK_CURRENT
	};

	/**
		@date 	2008/08/02  11:17	
		@author  xy
	
		@brief 	
	
		@see    
	*/
	class StreamWriter
	{
	public:
		StreamWriter()
		{}

		virtual ~StreamWriter()
		{}

		virtual String getDescription() = 0;

		virtual bool create( const String& filename ) = 0;

		virtual size_t write( void* src , const size_t& count ) = 0;

		virtual long seek( const long& pos ) = 0;

		virtual long seek( const long& offset ,
			const StreamWriterSeekMethod& seekdir ) = 0;

		virtual long tell() = 0;

		virtual void close() = 0;

		virtual void flush() = 0;

		virtual bool isValid() = 0;
	};


	class  VGK_EXPORT FileStreamWriter : public StreamWriter
	{
	public:
		FileStreamWriter( const String& filename );

		virtual ~FileStreamWriter()
		{
			close();
		}

		virtual String getDescription()
		{
			return VGK_FILESTREAMWRITER_DESC;
		}

		virtual bool create( const String& filename )
		{
			destroy();

			// Open the file
			hFile = CreateFile( filename.c_str() ,
				GENERIC_WRITE,          // open for writing
				0,                      // do not share
				NULL,                   // default security
				CREATE_ALWAYS,          // overwrite existing
				FILE_ATTRIBUTE_NORMAL, // normal file
				NULL);

			DWORD dwErrorCode = NULL;

			if(hFile == INVALID_HANDLE_VALUE)
			{
				assert(0);
				dwErrorCode = GetLastError();

				setDefault();
				return false;
			}
			else
			{
				mClosed = false;
			}

			return true;
		}

		size_t write( void* src , const size_t& count );

		long seek( const long& pos );

		long seek( const long& offset ,
			const StreamWriterSeekMethod& seekdir );

		long tell();

		void close();

		void flush()	{}

		bool isValid()
		{
			return !mClosed;
		}

		void destroy()
		{
			if ( mClosed == false )
			{
				assert( hFile != INVALID_HANDLE_VALUE );
				CloseHandle( hFile );
				hFile = INVALID_HANDLE_VALUE;

				mClosed = true;
			}
		}

	private:

		void setDefault()
		{
			hFile = INVALID_HANDLE_VALUE;
			mClosed = true;
		}
	private:

		HANDLE hFile;
		bool mClosed;
	};



#if VGK_STREAMWRITER_SUPPORT_CFILE

	class  VGK_EXPORT CFileStreamWriter : public StreamWriter
	{
	public:
		CFileStreamWriter();

		CFileStreamWriter( CFile* cfile , bool deleteondestroy = false );

		virtual ~CFileStreamWriter();

		virtual String getDescription()
		{
			return VGK_CFILESTREAMWRITER_DESC;
		}

		virtual bool create( const String& filename );

		virtual size_t write( void* src , const size_t& count );

		virtual long seek( const long& pos );

		virtual long seek( const long& offset ,
			const StreamWriterSeekMethod& seekdir );

		virtual long tell();

		virtual void close();

		virtual void flush();

		virtual bool isValid()
		{
			return _cFile != NULL;
		}

		CFile* getCFilePointer()
		{
			return _cFile;
		}

		void setDeleteOnDestroy( const bool& deleteit )
		{
			_deleteOnDestroy = deleteit;
		}

		bool wrapCFilePointer( CFile* cfile , bool deleteondestroy = false );

	private:

		void setDefault()
		{
			_cFile = NULL;
			_deleteOnDestroy = false;
			_fileAbsolutePath.clear();
		}

		void destroy();
		bool createCFileImpl( const String& filepath );

	private:

		CFile* _cFile;
		String _fileAbsolutePath;
		bool _deleteOnDestroy;
	};



#endif


	typedef SharePtr<StreamWriter> StreamWriterPtr;

	typedef SharePtr<FileStreamWriter> FileStreamWriterPtr;

#if VGK_STREAMWRITER_SUPPORT_CFILE
	typedef SharePtr<CFileStreamWriter> CFileStreamWriterPtr;
#endif


	class  VGK_EXPORT StreamWriterFactory
	{
	private:
		StreamWriterFactory()
		{
			
		}
	public:
		~StreamWriterFactory()
		{
			
		}
	
	
	public:

		static FileStreamWriterPtr createFromFile( const String& abs_filename ,
			const bool& warn_exist = false );
	
#if VGK_STREAMWRITER_SUPPORT_CFILE
		static CFileStreamWriterPtr createFromCFile( CFile* cfile , bool deleteondestroy );
#endif
	
	};

	
	
}// end of namespace vgKernel


#endif // end of __VGKSTREAMWRITER_H__