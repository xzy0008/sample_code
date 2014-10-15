

#ifndef __TVGSTREAMREADER_H__
#define __TVGSTREAMREADER_H__

#include <vgCore/vgPrerequisites.h>

#include <ximage.h>

namespace vgCore {

	/// virtual class for any file reading stream. 
	class StreamReader
	{

	protected:

		String mName;	

		size_t mSize;

#define VGES_STREAM_TEMP_SIZE 128

	public:

		StreamReader() : mSize(0) {}

		StreamReader(const String& name) : mName(name), mSize(0) {}

		const String& getName(void) { return mName; }

		virtual ~StreamReader() {}

		//virtual bool create( const String& filename ) = 0;



		//template<typename T> 
		//StreamReader& operator >> (T& val)
		//{
		//	/// 注意这里不能用String类型.虽然标准的std::fstream可以.
		//	read(static_cast<void*>(&val), sizeof(T));
		//	return *this;
		//}

		virtual size_t read(void* buf, size_t count) = 0;

		//virtual size_t readLine(char* buf, size_t maxCount, const String& delim = "\n");

		//virtual String getLine( bool trimAfter = true );

		//virtual String getAsString(void);

		//virtual size_t skipLine(const String& delim = "\n");

		virtual void skip(long count) = 0;

		virtual void seek( size_t pos ) = 0;

		virtual size_t tell(void) const = 0;

		virtual bool eof(void) const = 0;

		size_t size(void) const { return mSize; }

		virtual void close(void) = 0;

		virtual bool isValid() = 0;

	};


	typedef SharedPtr<StreamReader> StreamReaderPtr;

	


#if 0
	/** Common subclass of StreamReader for handling data from chunks of memory.
	*/
	class MemoryStreamReader : public StreamReader
	{
	protected:
        /// Pointer to the start of the data area
	    uchar* mData;
        /// Pointer to the current position in the memory
	    uchar* mPos;
        /// Pointer to the end of the memory
	    uchar* mEnd;
        /// Do we delete the memory on close
		bool mFreeOnClose;			
	public:
		
		/** Wrap an existing memory chunk in a stream.
		@param pMem Pointer to the exising memory
		@param size The size of the memory chunk in bytes
		@param freeOnClose If true, the memory associated will be destroyed
			when the stream is destroyed.
		*/
		MemoryStreamReader(void* pMem, size_t size, bool freeOnClose = false);
		
		/** Wrap an existing memory chunk in a named stream.
		@param name The name to give the stream
		@param pMem Pointer to the exising memory
		@param size The size of the memory chunk in bytes
		@param freeOnClose If true, the memory associated will be destroyed
			when the stream is destroyed.
		*/
		MemoryStreamReader(const String& name, void* pMem, size_t size, 
				bool freeOnClose = false);

		/** Create a stream which pre-buffers the contents of another stream.
		@remarks
			This constructor can be used to intentionally read in the entire
			contents of another stream, copying them to the internal buffer
			and thus making them available in memory as a single unit.
		@param sourceStream Another StreamReader which will provide the source
			of data
		@param freeOnClose If true, the memory associated will be destroyed
			when the stream is destroyed.
		*/
		MemoryStreamReader(StreamReader& sourceStream, 
				bool freeOnClose = true);
		
		/** Create a stream which pre-buffers the contents of another stream.
		@remarks
			This constructor can be used to intentionally read in the entire
			contents of another stream, copying them to the internal buffer
			and thus making them available in memory as a single unit.
		@param sourceStream Weak reference to another StreamReader which will provide the source
			of data
		@param freeOnClose If true, the memory associated will be destroyed
			when the stream is destroyed.
		*/
		MemoryStreamReader(StreamReaderPtr& sourceStream, 
				bool freeOnClose = true);

		/** Create a named stream which pre-buffers the contents of 
			another stream.
		@remarks
			This constructor can be used to intentionally read in the entire
			contents of another stream, copying them to the internal buffer
			and thus making them available in memory as a single unit.
		@param name The name to give the stream
		@param sourceStream Another StreamReader which will provide the source
			of data
		@param freeOnClose If true, the memory associated will be destroyed
			when the stream is destroyed.
		*/
		MemoryStreamReader(const String& name, StreamReader& sourceStream, 
				bool freeOnClose = true);

        /** Create a named stream which pre-buffers the contents of 
        another stream.
        @remarks
        This constructor can be used to intentionally read in the entire
        contents of another stream, copying them to the internal buffer
        and thus making them available in memory as a single unit.
        @param name The name to give the stream
        @param sourceStream Another StreamReader which will provide the source
        of data
        @param freeOnClose If true, the memory associated will be destroyed
        when the stream is destroyed.
        */
        MemoryStreamReader(const String& name, const StreamReaderPtr& sourceStream, 
            bool freeOnClose = true);

        /** Create a stream with a brand new empty memory chunk.
		@param size The size of the memory chunk to create in bytes
		@param freeOnClose If true, the memory associated will be destroyed
			when the stream is destroyed.
		*/
		MemoryStreamReader(size_t size, bool freeOnClose = true);
		/** Create a named stream with a brand new empty memory chunk.
		@param name The name to give the stream
		@param size The size of the memory chunk to create in bytes
		@param freeOnClose If true, the memory associated will be destroyed
			when the stream is destroyed.
		*/
		MemoryStreamReader(const String& name, size_t size, 
				bool freeOnClose = true);

		~MemoryStreamReader();

		/** Get a pointer to the start of the memory block this stream holds. */
		uchar* getPtr(void) { return mData; }
		
		/** Get a pointer to the current position in the memory block this stream holds. */
		uchar* getCurrentPtr(void) { return mPos; }
		
		/** @copydoc StreamReader::read
		*/
		size_t read(void* buf, size_t count);
		/** @copydoc StreamReader::readLine
		*/
		size_t readLine(char* buf, size_t maxCount, const String& delim = "\n");
		
		/** @copydoc StreamReader::skipLine
		*/
		size_t skipLine(const String& delim = "\n");

		/** @copydoc StreamReader::skip
		*/
		void skip(long count);
	
		/** @copydoc StreamReader::seek
		*/
	    void seek( size_t pos );
		
		/** @copydoc StreamReader::tell
		*/
	    size_t tell(void) const;

		/** @copydoc StreamReader::eof
		*/
	    bool eof(void) const;

        /** @copydoc StreamReader::close
        */
        void close(void);

		/** Sets whether or not to free the encapsulated memory on close. */
		void setFreeOnClose(bool free) { mFreeOnClose = free; }
	};

    /** Shared pointer to allow memory data streams to be passed around without
    worrying about deallocation
    */
    typedef SharedPtr<MemoryStreamReader> MemoryDataStreamPtr;


#endif


	// 连通CxFile的接口
	class CxStreamReader : public CxFile
	{
	public:
		CxStreamReader( StreamReaderPtr preaderstream )
		{
			assert( !preaderstream.isNull() );
			assert( preaderstream->isValid() );
			m_pStreamReader = preaderstream;
		}
		~CxStreamReader()
		{
			
		}
	
		virtual bool	Close()
		{
			assert( isValid() );
			m_pStreamReader->close();
			return true;
		}

		virtual size_t	Read(void *buffer, size_t size, size_t count)
		{
			assert( isValid() );
			return m_pStreamReader->read( buffer , size * count );
		}


		virtual size_t	Write(const void *buffer, size_t size, size_t count)
		{
			assert( 0 && "StreamReader不能执行Write!");
			return 0;
		}
		virtual bool	Seek(long offset, int origin)
		{
			assert( isValid() );
			size_t now_pos = this->m_pStreamReader->tell();

			if (origin == SEEK_SET)		 
			{
				this->m_pStreamReader->seek( offset );
			}
			else if (origin == SEEK_CUR)
			{
				this->m_pStreamReader->seek( now_pos + offset );
			}
			else if (origin == SEEK_END)
			{
				size_t end_pos = this->m_pStreamReader->size();
				this->m_pStreamReader->seek( end_pos + offset );
			}
			else
			{
				return false;
			}

			return true;
		}
		virtual long	Tell()
		{
			assert( isValid() );
			return this->m_pStreamReader->tell();
		}

		virtual long	Size()
		{
			assert( isValid() );
			return this->m_pStreamReader->size();
		}
		virtual bool	Flush()
		{
			return true;
		}

		virtual bool	Eof()
		{
			return this->m_pStreamReader->eof();
		}

		virtual long	Error()
		{
			assert(0 && "正在执行Error()函数!");
			return 0;
		}

		virtual bool	PutC(unsigned char c)
		{
			assert( 0 && "StreamReader不能执行PutC!");
			return false;
		}
		virtual long	GetC() 
		{
			if (Eof()) 
			{
				return EOF;
			}

			BYTE result = 0; 
			this->m_pStreamReader->read( &result , sizeof( BYTE ) );

			return result;
			//return *(BYTE*)((BYTE*)m_pBuffer + m_Position++);
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
			if( m_pStreamReader.isNull() == false )
			{
				if( m_pStreamReader->isValid() == true )
				{
					return true;
				}
			}

			return false;
		}

	private:
		
		StreamReaderPtr m_pStreamReader;

	
	
	};
	
	
	
}// end of namespace

#endif // end of __TVGSTREAMREADER_H__