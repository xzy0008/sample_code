

#ifndef __TVGSTREAMWRITER_H__
#define __TVGSTREAMWRITER_H__

#include <vgCore/vgPrerequisites.h>

#include <vgTex/tvgStreamReader.h>
#include <vgCore/vgSharedPtr.h>
#include <vgTex/tvgImageUtil.h>

//#include <vgTrace.h>
#include <vgCore/vgWarning.h>



namespace vgCore {



	class StreamWriter
	{
	public:
		StreamWriter()
		{
		}
		virtual ~StreamWriter()
		{
		}

		virtual StreamWriter& write( const char* src , const size_t& count ) = 0 ;

		virtual StreamWriter& flush( void ) = 0 ;

		virtual StreamWriter& seek( const StreamPos& pos ) = 0 ;

		virtual StreamWriter& seek( const StreamPos& offset ,
			const StreamWriterSeekDir& seekdir ) = 0 ;

		virtual StreamPos tell() const = 0 ;

		virtual void close() = 0 ;

		// 注意对MemoryStreamReader来说内存要注意是否释放的问题
		//virtual StreamReaderPtr getStreamReader() = 0;

	};

	typedef SharedPtr<StreamWriter> StreamWriterPtr;


	class MemoryStreamWriter : public StreamWriter
	{
	public:
		MemoryStreamWriter()
		{
			this->setParametersDefault();
			//VG_TRACE("MemoryStreamWriter created!");
		}

		MemoryStreamWriter( size_t buf_size )
		{
			mpBuffer = new vector<byte>( buf_size );
			assert( mpBuffer!=NULL );
			this->mIterCurPos = mpBuffer->begin();
			this->mClosed = false;

			//VG_TRACE("MemoryStreamWriter created!");
		}

		MemoryStreamWriter( size_t buf_size , byte val )
		{
			mpBuffer = new vector<byte>( buf_size , val );
			assert( mpBuffer!=NULL );
			this->mIterCurPos = mpBuffer->begin();
			this->mClosed = false;

			//VG_TRACE("MemoryStreamWriter created!");
		}

		~MemoryStreamWriter()
		{
			this->close();
			//VG_TRACE("MemoryStreamWriter deleted!");
		}
	
		virtual StreamWriter& flush( void )
		{
			return *this;
		}
		virtual StreamWriter& write( const char* src , const size_t& count )
		{
			// 注意！目前为效率不高的方式！以后更改！
			assert( isValid() );

			const char* cur = src;

			for ( size_t i = 0 ; i < count ; ++ i )
			{
				if ( this->mIterCurPos == mpBuffer->end() )
				{
					this->mpBuffer->push_back( *(cur++) );
					this->mIterCurPos = mpBuffer->end();
				}
				else
				{
					*mIterCurPos++ = *(cur++);
				}
			}

			return *this;
		}

		virtual StreamWriter& seek( const StreamPos& pos ) 
		{
			assert( isValid() );
			ulong ipos = pos;
			//assert( ipos >= 0 );

			if ( this->mpBuffer->size() <= ipos)
			{
				mIterCurPos = mpBuffer->end();
				return *this;
			}
			
			mIterCurPos = mpBuffer->begin() + pos;
			return *this;
		}

		virtual StreamWriter& seek( const StreamPos& offset ,
			const StreamWriterSeekDir& seekdir ) 
		{
			assert( isValid() );
			assert(0);
			return *this;
		}

		virtual StreamPos tell() const
		{
			assert( isValid() );
			return ( mIterCurPos - mpBuffer->begin() );
		}

		virtual void close()
		{
			if ( this->mClosed == false )
			{
				delete mpBuffer;
				mpBuffer = NULL;
				this->mClosed = true;
			}
		}

		//virtual StreamReaderPtr getStreamReader()
		//{
		//	assert( isValid() );
		//	
		//	void* buffer_beg = reinterpret_cast<void*>( &this->mpBuffer->operator [](0) );

		//	const size_t& size = this->mpBuffer->size();

		//	StreamReaderPtr ret( new MemoryStreamReader( buffer_beg , size , false ) );
		//	return ret;
		//}
	
	private:

		void setParametersDefault()
		{
			mpBuffer = new vector<byte>;
			assert( mpBuffer!=NULL );
			this->mIterCurPos = mpBuffer->begin();
			this->mClosed = false;
		}

		bool isValid() const
		{
			if ( this->mClosed == true )
			{
				return false;
			}
			if ( this->mpBuffer == NULL )
			{
				return false;
			}
			return true;
		}


	private:
	public:

		vector<byte>*  mpBuffer;

		vector<byte>::iterator mIterCurPos;

		bool   mClosed;
	};




	/**
	@date 	2007/05/16  15:24	
	@author  Leven

	@brief 	

	@see    
	*/
	class FileStreamWriter : public StreamWriter
	{
	public:

		FileStreamWriter( const String& filename )
		{
			hFile = INVALID_HANDLE_VALUE;
			mClosed = false;

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
			}
		}

		virtual ~FileStreamWriter()
		{
			close();
		}

		virtual StreamWriter& flush( void )
		{
			return *this;
		}

		virtual StreamWriter& write( const char* src , const size_t& count )
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

			return *this;
		}

		virtual StreamWriter& seek( const StreamPos& pos )
		{
			assert( isValid() );

			assert( pos >= 0 );

			DWORD dwCurrentFilePosition; 

			dwCurrentFilePosition = SetFilePointer( 
				hFile, // must have GENERIC_READ and/or GENERIC_WRITE 
				pos,     // do not move pointer 
				NULL,  // hFile is not large enough to need this pointer 
				FILE_BEGIN);  // provides offset from current position 

			assert( dwCurrentFilePosition == pos );

			return (*this);
		}

		virtual StreamWriter& seek( const StreamPos& offset ,
			const StreamWriterSeekDir& seekdir )
		{
			assert( isValid() );


			DWORD method;

			if ( seekdir == ios_base::beg )
			{
				method = FILE_BEGIN;
			}
			else if (seekdir == ios_base::cur )
			{
				method = FILE_CURRENT;
			}
			else if (seekdir == ios_base::end)
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

			assert( dwCurrentFilePosition == offset );

			return *this;
		}

		virtual StreamPos tell() const
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

		//virtual StreamReaderPtr getStreamReader()
		//{
		//	assert( isValid() );

		//	assert( this->mFilename.empty() == false );

		//	const String file = this->mFilename;

		//	//this->close();

		//	std::ifstream* s = new std::ifstream( file.c_str() , 
		//		ifstream::binary );

		//	if ( s->fail() )
		//	{
		//		delete s;
		//		return StreamReaderPtr();
		//	}

		//	StreamReaderPtr ret(
		//		new FileStreamReader( file , s , true ) );
		//	return ret;
		//}


		virtual void close()
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

		bool isValid() const
		{
			return !mClosed;
		}

	private:

		HANDLE hFile;
		bool mClosed;
	};


#if 0
	/**
		@date 	2007/05/16  15:24	
		@author  Leven
	
		@brief 	
	
		@see    
	*/
	class FileStreamWriter : public StreamWriter
	{
	public:
		FileStreamWriter()
		{
			this->setDefault();
			VG_TRACE("FileStreamWriter construected");
		}

		// 还是要有文件名。
		//FileStreamWriter( std::fstream* s, 
		//	bool freeOnClose = true )
		//{
		//	//this->setDefault();
		//	assert( s!= NULL);
		//	this->mpStream = s;
		//	this->mFreeOnClose = freeOnClose;
		//	VG_TRACE("FileStreamWriter construected");
		//}

		FileStreamWriter( const String& filename )
		{
			this->setDefault();
			this->create( filename );
			VG_TRACE("FileStreamWriter construected");
		}

		virtual ~FileStreamWriter()
		{
			this->close();
			VG_TRACE("FileStreamWriter destructed");
		}

		template<typename T> 
		FileStreamWriter& operator << (T& val)
		{
			assert( isValid() );
			/// 注意这里不能用String类型.虽然标准的std::fstream可以.
			/// template不允许重载的.
			(*this->mpStream) << val;
			return *this;
		}

		virtual StreamWriter& flush( void )
		{
			return *this;
		}

		virtual StreamWriter& write( const char* src , const size_t& count )
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

			return *this;
		}

		virtual StreamWriter& seek( const StreamPos& pos )
		{
			assert( isValid() );

			assert( pos > 0 );

			DWORD dwCurrentFilePosition; 

			dwCurrentFilePosition = SetFilePointer( 
				hFile, // must have GENERIC_READ and/or GENERIC_WRITE 
				pos,     // do not move pointer 
				NULL,  // hFile is not large enough to need this pointer 
				FILE_BEGIN);  // provides offset from current position 

			assert( dwCurrentFilePosition == pos );

			return (*this);
		}

		//virtual StreamWriter& seek( const StreamPos& offset ,
		//	const StreamWriterSeekDir& seekdir )
		//{
		//	assert( isValid() );
		//	this->mpStream->seekp( offset , (std::ios_base::seekdir)seekdir );
		//	return *this;
		//}

		virtual StreamPos tell() const
		{
			assert( isValid() );
			this->mpStream->clear();
			return this->mpStream->tellp();
		}

		virtual StreamReaderPtr getStreamReader()
		{
			assert( isValid() );

			assert( this->mFilename.empty() == false );

			const String file = this->mFilename;

			//this->close();

			std::ifstream* s = new std::ifstream( file.c_str() , 
				ifstream::binary );

			if ( s->fail() )
			{
				delete s;
				return StreamReaderPtr();
			}

			StreamReaderPtr ret(
				new FileStreamReader( file , s , true ) );
			return ret;
		}


		bool create( const String& filename )
		{
			assert( !isValid() );

			this->mpStream = new std::fstream;

			mpStream->open( filename.c_str() , ofstream::out);
			mpStream->close();
			mpStream->open( filename.c_str() ,
				ofstream::in|ofstream::out|ofstream::trunc | ofstream::binary);

			if ( mpStream->fail() )
			{
				VG_EXCEPT(Exception::ERR_ITEM_NOT_FOUND,
					"文件打开失败！" ,"FileStreamWriter::createFromFile()");
				return false;
			}

			this->mFilename = filename;
			this->mClosed = false;
			return true;
		}
	
		virtual void close()
		{
			if (mpStream)
			{
				if ( mClosed == false )
				{
					mpStream->close();
					mClosed = true;
					if (mFreeOnClose)
					{
						// delete the stream too
						delete mpStream;
						mpStream = NULL;
						mFilename = "";
					}
				}
			}
		}
	private:

		bool isValid() const
		{
			return !mClosed;
		}
		void setDefault()
		{
			mpStream = NULL;
			mFreeOnClose = true;
			mClosed = true;
		}

	private:

		String mFilename;

		std::fstream* mpStream;
		bool mFreeOnClose;

		bool mClosed;
	};
	
#endif


	struct WriterInfo 
	{
		// 这些是输入数据
		String aimFilename;
		StreamPos absoluteBeginPos;
		StreamWriterPtr streamWriterPtr;
		DdsFormat ddsFormat;

		// 这些由输出所填写
		String originalFilename;
		StreamPos absoluteEndPos;
		ulong  fileLength;

		WriterInfo()
		{
			this->setParametersDefault();
		}

		String getDetails() const
		{
			std::ostringstream o;
			o << "WriterInfo : "
				<< " , filename = " << this->originalFilename 
				<< " , streamWriter.isNull()? = " << this->streamWriterPtr.isNull() 
				<< " , absoluteBeginPos = " << this->absoluteBeginPos 
				<< " , absoluteEndPos = " << this->absoluteEndPos 
				<< " , fileLength = " << this->fileLength ;

			return o.str();
		}
	private:
		void setParametersDefault()
		{
			this->ddsFormat = DDS_FORMAT_DEFAULT;
			this->fileLength = 0;
			this->absoluteBeginPos = 0;
			this->absoluteEndPos = 0;
		}
	};

	typedef SharedPtr<WriterInfo> WriterInfoPtr;

	typedef std::vector<WriterInfo> WriterInfoList;

	typedef SharedPtr<WriterInfoList> WriterInfoListPtr;





	// 连通CxFile的接口
	class CxStreamWriter : public CxFile
	{
	public:
		CxStreamWriter( StreamWriterPtr preaderstream )
		{
			assert( !preaderstream.isNull() );
			m_pStreamWriter = preaderstream;
		}
		~CxStreamWriter()
		{

		}

		virtual bool	Close()
		{
			assert( isValid() );
			m_pStreamWriter->close();
			return true;
		}

		virtual size_t	Read(void *buffer, size_t size, size_t count)
		{
			//assert( 0 && "CxStreamWriter不能执行Read!");
			VG_WARN(Warning::WARN_INVALID_STATE,
				Warning::BUTTON_NONE,
				"CxStreamWriter正在执行Read,读取内容将不确定.",
				"CxStreamWriter::Read");
			return 0;
		}

		virtual size_t	Write(const void *buffer, size_t size, size_t count)
		{
			this->m_pStreamWriter->write( 
				static_cast<const char*>(buffer) , size * count );
			return size * count;
		}

		virtual bool	Seek(long offset, int origin)
		{
			assert( isValid() );

			StreamWriterSeekDir dir;

			if (origin == SEEK_SET)		 
			{
				dir = ios_base::beg;
			}
			else if (origin == SEEK_CUR)
			{
				dir = ios_base::cur;
			}
			else if (origin == SEEK_END)
			{
				dir = ios_base::end;
			}
			else
			{
				return false;
			}

			this->m_pStreamWriter->seek( offset , dir );

			return true;
		}

		virtual long	Tell()
		{
			assert( isValid() );
			return this->m_pStreamWriter->tell();
		}

		virtual long	Size()
		{
			assert( 0 && "StreamReader不能执行Size!");
			return 0;
		}
		virtual bool	Flush()
		{
			this->m_pStreamWriter->flush();
			return true;
		}

		virtual bool	Eof()
		{
			assert( 0 && "CxStreamWriter不能执行Eof!");
			return false;
		}

		virtual long	Error()
		{
			//assert(0 && "正在执行Error()函数!");
			return 0;
		}

		virtual bool	PutC(unsigned char c)
		{
			assert( isValid() );
			this->m_pStreamWriter->write( 
				(char*)( &c ) , sizeof( unsigned char ) );
			return true;
		}
		virtual long	GetC() 
		{
			assert( 0 && "CxStreamWriter不能执行GetC!");
			return 0;
		}

		virtual char *	GetS(char *string, int n)
		{
			assert(0);
			return NULL;
		}
		virtual long	Scanf(const char *format, void* output)
		{
			assert(0);
			return 0;
		}

	private:

		bool isValid() const
		{
			return !m_pStreamWriter.isNull();
		}

	private:

		StreamWriterPtr m_pStreamWriter;

	};







	
}// end of namespace vgCore

#endif // end of __TVGSTREAMWRITER_H__