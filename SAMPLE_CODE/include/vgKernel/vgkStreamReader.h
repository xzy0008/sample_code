


#ifndef __VGKSTREAMREADER_H__
#define __VGKSTREAMREADER_H__

#include <vgKernel/vgkForward.h>
#include <vgKernel/vgkSharePtr.h>


#ifdef VGK_NO_SUPPORT_MFC
#	define  VGK_STREAMREADER_SUPPORT_CFILE	0
#else
#	define  VGK_STREAMREADER_SUPPORT_CFILE	1
#endif

#define  VGK_FILESTREAMREADER_DESC  "FileStreamReader"
#define  VGK_CFILESTREAMREADER_DESC  "CFileStreamReader"

namespace vgKernel {


	class StreamReader
	{
	public:
		StreamReader()
		{

		}

		virtual ~StreamReader()
		{

		}

		virtual String getDescription() = 0;

		virtual String getFileName() = 0;

		virtual bool create( const String& filename ) = 0;

		virtual bool isValid()  = 0;

		virtual size_t size(void) = 0;

		virtual size_t read( void* buf, size_t count ) = 0;

		virtual void skip(long count) = 0;

		virtual void seek( size_t pos ) = 0;

		virtual size_t tell(void)  = 0;

		virtual bool eof(void)  = 0;

		virtual void close(void) = 0;

		virtual void flush(void) = 0;

	};


	/**
		@date 	2008/08/01  19:02	
		@author  xy

		@brief 	win32 ReadFileµÄ·â×°

		@see    
	*/
	class  VGK_EXPORT FileStreamReader : public StreamReader
	{
	public:
		FileStreamReader();
		FileStreamReader(const String& filename);

		virtual ~FileStreamReader();

		virtual String getDescription()
		{
			return VGK_FILESTREAMREADER_DESC;
		}

		virtual String getFileName()
		{
			return mName;
		}

		virtual bool create( const String& filename );

		virtual bool isValid() 
		{
			return _isValid;
		}

		virtual size_t size(void) 
		{
			return mSize;
		}

		virtual size_t read( void* buf, size_t count );

		virtual void skip(long count);

		virtual void seek( size_t pos );

		virtual size_t tell(void);

		virtual bool eof(void);

		virtual void close(void);

		virtual void flush(void) {}

	private:

		size_t  mSize;
		String mName;
		bool _isValid;
		HANDLE _filehandle;
	};


#if VGK_STREAMREADER_SUPPORT_CFILE

	class  VGK_EXPORT CFileStreamReader : public StreamReader
	{
	public:
		CFileStreamReader();

		CFileStreamReader( CFile* cfile , bool deleteondestroy = false );

		virtual ~CFileStreamReader();

		virtual String getFileName();

		virtual String getDescription()
		{
			return VGK_CFILESTREAMREADER_DESC;
		}

		virtual bool create( const String& filename );

		virtual bool isValid();

		virtual size_t size(void);

		virtual size_t read( void* buf, size_t count );

		virtual void skip(long count);

		virtual void seek( size_t pos );

		virtual size_t tell(void);

		virtual bool eof(void);

		virtual void close(void);

		virtual void flush(void);

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

		void setDefault();
		void destroy();
		bool createCFileImpl( const String& filepath );

	private:

		CFile* _cFile;
		size_t  _size;
		String _fileAbsolutePath;
		bool _deleteOnDestroy;
	};
#endif

	typedef SharePtr<StreamReader> StreamReaderPtr;
	typedef SharePtr<FileStreamReader> FileStreamReaderPtr;

#if VGK_STREAMREADER_SUPPORT_CFILE
	typedef SharePtr<CFileStreamReader> CFileStreamReaderPtr;
#endif

	class  VGK_EXPORT StreamReaderFactory
	{
	private:
		StreamReaderFactory()
		{
			
		}
	public:

		~StreamReaderFactory()
		{
			
		}
	
	public:

		static StreamReaderPtr createFromFile( const String& filename );
	
#if VGK_STREAMREADER_SUPPORT_CFILE

		static CFileStreamReaderPtr createFromCFile( CFile* cfile , bool deleteondestroy );

#endif
	};

}// end of namespace vgKernel



#endif // end of __VGKSTREAMREADER_H__