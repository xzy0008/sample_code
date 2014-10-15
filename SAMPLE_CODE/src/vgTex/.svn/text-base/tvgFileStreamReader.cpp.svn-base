
#include <vgStableHeaders.h>

#include <vgTex/tvgFileStreamReader.h>
#include <vgTex/tvgStreamReader.h>

namespace vgCore {
	
	//----------------------------------------------------------------
	size_t FileStreamReader::read( void* buf, size_t count )
	{
		assert( _isValid == true );
		assert( buf != NULL );
		assert( count > 0 );

		DWORD dwBytesRead = 0;
		BOOL bSuccess = ReadFile( _filehandle, 
			buf, 
			count, 
			&dwBytesRead, 
			NULL);

		assert( bSuccess == TRUE );
		if ( bSuccess == FALSE )
		{
			return 0;
		}

		//if( count != dwBytesRead )
		//{
		//	assert(0);
		//}

		return dwBytesRead;
	}
	//----------------------------------------------------------------



#if 0 
	vgThreads::CriticalSection FileStreamReader::mCriticalSect;

	//-----------------------------------------------------------------------
	FileStreamReader::FileStreamReader(std::ifstream* s, bool freeOnClose)
		: StreamReader(), mpStream(s), mFreeOnClose(freeOnClose)
	{
		vgThreads::ScopedLock locker(mCriticalSect);
		// calculate the size
		mpStream->seekg(0, std::ios_base::end);
		mSize = mpStream->tellg();
		mpStream->seekg(0, std::ios_base::beg);


	}
	//-----------------------------------------------------------------------
	FileStreamReader::FileStreamReader(const String& name, 
		std::ifstream* s, bool freeOnClose)
		: StreamReader(name), mpStream(s), mFreeOnClose(freeOnClose)
	{
		vgThreads::ScopedLock locker(mCriticalSect);
		// calculate the size
		mpStream->seekg(0, std::ios_base::end);
		mSize = mpStream->tellg();
		mpStream->seekg(0, std::ios_base::beg);

	}
	//-----------------------------------------------------------------------
	FileStreamReader::FileStreamReader(const String& name, 
		std::ifstream* s, size_t size, bool freeOnClose)
		: StreamReader(name), mpStream(s), mFreeOnClose(freeOnClose)
	{
		// Size is passed in
		mSize = size;
	}
	//----------------------------------------------------------------
	FileStreamReader::FileStreamReader( const String& filename )
		: StreamReader()
	{
		vgThreads::ScopedLock locker(mCriticalSect);
		std::ifstream *filestream = 
			new std::ifstream( filename.c_str() , std::ifstream::binary | std::ifstream::in );

		if ( filestream->fail() )
		{
			VG_EXCEPT(Exception::ERR_FILE_NOT_FOUND ,
				"create FileStreamReader failed : ",
				"FileStreamReader::FileStreamReader");
			return;
		}
		this->create( filestream );


	}	
	//----------------------------------------------------------------
	FileStreamReader::FileStreamReader()
		: StreamReader() , mpStream( NULL )
	{

	}
	//-----------------------------------------------------------------------
	FileStreamReader::~FileStreamReader()
	{
		close();
	}
	//-----------------------------------------------------------------------
	size_t FileStreamReader::read(void* buf, size_t count)
	{
		vgThreads::ScopedLock locker(mCriticalSect);
		mpStream->read(static_cast<char*>(buf), static_cast<std::streamsize>(count));
		size_t tmp = mpStream->gcount();

		return tmp;
	}
	//-----------------------------------------------------------------------
	//size_t FileStreamReader::readLine(char* buf, size_t maxCount, 
	//	const String& delim)
	//{
	//	vgThreads::ScopedLock locker(mCriticalSect);

	//	if (delim.empty())
	//	{
	//		VG_EXCEPT(Exception::ERR_INVALIDPARAMS, "No delimiter provided",
	//			"FileStreamReader::readLine");
	//	}
	//	if (delim.size() > 1)
	//	{
	//		LogManager::getSingleton().logMessage(
	//			"WARNING: FileStreamReader::readLine - using only first delimeter");
	//	}
	//	// Deal with both Unix & Windows LFs
	//	bool trimCR = false;
	//	if (delim.at(0) == '\n') 
	//	{
	//		trimCR = true;
	//	}
	//	// maxCount + 1 since count excludes terminator in getline
	//	mpStream->getline(buf, static_cast<std::streamsize>(maxCount+1), delim.at(0));
	//	size_t ret = mpStream->gcount();
	//	// three options
	//	// 1) we had an eof before we read a whole line
	//	// 2) we ran out of buffer space
	//	// 3) we read a whole line - in this case the delim character is taken from the stream but not written in the buffer so the read data is of length ret-1 and thus ends at index ret-2
	//	// in all cases the buffer will be null terminated for us

	//	if (mpStream->eof()) 
	//	{
	//		// no problem
	//	}
	//	else if (mpStream->fail())
	//	{
	//		// Did we fail because of maxCount hit? No - no terminating character
	//		// in included in the count in this case
	//		if (ret == maxCount)
	//		{
	//			// clear failbit for next time 
	//			mpStream->clear();
	//		}
	//		else
	//		{
	//			VG_EXCEPT(Exception::ERR_INTERNAL_ERROR, 
	//				"Streaming error occurred", 
	//				"FileStreamReader::readLine");
	//		}
	//	}
	//	else 
	//	{
	//		// we need to adjust ret because we want to use it as a
	//		// pointer to the terminating null character and it is
	//		// currently the length of the data read from the stream
	//		// i.e. 1 more than the length of the data in the buffer and
	//		// hence 1 more than the _index_ of the NULL character
	//		--ret;
	//	}

	//	// trim off CR if we found CR/LF
	//	if (trimCR && buf[ret-1] == '\r')
	//	{
	//		--ret;
	//		buf[ret] = '\0';
	//	}



	//	return ret;
	//}
	//-----------------------------------------------------------------------
	void FileStreamReader::skip(long count)
	{
		vgThreads::ScopedLock locker(mCriticalSect);
		mpStream->clear(); //Clear fail status in case eof was set
		mpStream->seekg(static_cast<std::ifstream::pos_type>(count), std::ios::cur);

	}
	//-----------------------------------------------------------------------
	void FileStreamReader::seek( size_t pos )
	{
		vgThreads::ScopedLock locker(mCriticalSect);
		mpStream->clear(); //Clear fail status in case eof was set
		mpStream->seekg(static_cast<std::streamoff>(pos), std::ios::beg);

	}
	//-----------------------------------------------------------------------
	size_t FileStreamReader::tell(void) const
	{
		vgThreads::ScopedLock locker(mCriticalSect);
		mpStream->clear(); //Clear fail status in case eof was set
		size_t tt = mpStream->tellg();

		return tt;
	}
	//-----------------------------------------------------------------------
	bool FileStreamReader::eof(void) const
	{
		vgThreads::ScopedLock locker(mCriticalSect);
		bool tmp = mpStream->eof();

		return tmp;
	}
	//-----------------------------------------------------------------------
	void FileStreamReader::close(void)
	{
		vgThreads::ScopedLock locker(mCriticalSect);

		if (mpStream)
		{
			mpStream->close();
			if (mFreeOnClose)
			{
				// delete the stream too
				delete mpStream;
				mpStream = 0;
			}
		}


	}
	//----------------------------------------------------------------

#endif
	
}// end of namespace vgCore
