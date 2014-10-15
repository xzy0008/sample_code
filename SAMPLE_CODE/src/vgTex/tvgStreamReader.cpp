
#include <vgStableHeaders.h>

#include <vgTex/tvgStreamReader.h>
#include <vgTex/tvgStringUtil.h>

namespace vgCore {
	

	//-----------------------------------------------------------------------
	//-----------------------------------------------------------------------
	/*
	/// 为了保险起见将此实现放在.h文件里面.
	template <typename T> StreamReader& StreamReader::operator >>(T& val)
	{
		read(static_cast<void*>(&val), sizeof(T));
		return *this;
	}
	*/
	//-----------------------------------------------------------------------
	//String StreamReader::getLine(bool trimAfter)
	//{
	//	char tmpBuf[VGES_STREAM_TEMP_SIZE];
	//	String retString;
	//	size_t readCount;
	//	// Keep looping while not hitting delimiter
	//	while ((readCount = read(tmpBuf, VGES_STREAM_TEMP_SIZE-1)) != 0)
	//	{
	//		// Terminate string
	//		tmpBuf[readCount] = '\0';

	//		char* p = strchr(tmpBuf, '\n');
	//		if (p != 0)
	//		{
	//			// Reposition backwards
	//			skip((long)(p + 1 - tmpBuf - readCount));
	//			*p = '\0';
	//		}

	//		retString += tmpBuf;

	//		if (p != 0)
	//		{
	//			// Trim off trailing CR if this was a CR/LF entry
	//			if (retString.length() && retString[retString.length()-1] == '\r')
	//			{
	//				retString.erase(retString.length()-1, 1);
	//			}

	//			// Found terminator, break out
	//			break;
	//		}
	//	}

	//	if (trimAfter)
	//	{
	//		StringUtil::trim(retString);
	//	}

	//	return retString;
	//}
	//-----------------------------------------------------------------------
	//size_t StreamReader::readLine(char* buf, size_t maxCount, const String& delim)
	//{
	//	// Deal with both Unix & Windows LFs
	//	bool trimCR = false;
	//	if (delim.find_first_of('\n') != String::npos)
	//	{
	//		trimCR = true;
	//	}

	//	char tmpBuf[VGES_STREAM_TEMP_SIZE];
	//	size_t chunkSize = Math::Min(maxCount, (size_t)VGES_STREAM_TEMP_SIZE-1);
	//	size_t totalCount = 0;
	//	size_t readCount; 
	//	while (chunkSize && (readCount = read(tmpBuf, chunkSize)))
	//	{
	//		// Terminate
	//		tmpBuf[readCount] = '\0';

	//		// Find first delimiter
	//		size_t pos = strcspn(tmpBuf, delim.c_str());

	//		if (pos < readCount)
	//		{
	//			// Found terminator, reposition backwards
	//			skip((long)(pos + 1 - readCount));
	//		}

	//		// Are we genuinely copying?
	//		if (buf)
	//		{
	//			memcpy(buf+totalCount, tmpBuf, pos);
	//		}
	//		totalCount += pos;

	//		if (pos < readCount)
	//		{
	//			// Trim off trailing CR if this was a CR/LF entry
	//			if (trimCR && totalCount && buf[totalCount-1] == '\r')
	//			{
	//				--totalCount;
	//			}

	//			// Found terminator, break out
	//			break;
	//		}

	//		// Adjust chunkSize for next time
	//		chunkSize = Math::Min(maxCount-totalCount, (size_t)VGES_STREAM_TEMP_SIZE-1);
	//	}

	//	// Terminate
	//	buf[totalCount] = '\0';

	//	return totalCount;
	//}
	//-----------------------------------------------------------------------
	//size_t StreamReader::skipLine(const String& delim)
	//{
	//	char tmpBuf[VGES_STREAM_TEMP_SIZE];
	//	size_t total = 0;
	//	size_t readCount;
	//	// Keep looping while not hitting delimiter
	//	while ((readCount = read(tmpBuf, VGES_STREAM_TEMP_SIZE-1)) != 0)
	//	{
	//		// Terminate string
	//		tmpBuf[readCount] = '\0';

	//		// Find first delimiter
	//		size_t pos = strcspn(tmpBuf, delim.c_str());

	//		if (pos < readCount)
	//		{
	//			// Found terminator, reposition backwards
	//			skip((long)(pos + 1 - readCount));

	//			total += pos + 1;

	//			// break out
	//			break;
	//		}

	//		total += readCount;
	//	}

	//	return total;
	//}
	//-----------------------------------------------------------------------
	//String StreamReader::getAsString(void)
	//{
	//	// Read the entire buffer
	//	char* pBuf = new char[mSize+1];
	//	// Ensure read from begin of stream
	//	seek(0);
	//	read(pBuf, mSize);
	//	pBuf[mSize] = '\0';
	//	String str;
	//	str.insert(0, pBuf, mSize);
	//	delete [] pBuf;
	//	return str;
	//}
	//-----------------------------------------------------------------------


#if 0
	//----------------------------------------------------------------
	//----------------------------------------------------------------
	//-----------------------------------------------------------------------
    MemoryStreamReader::MemoryStreamReader(void* pMem, size_t size, bool freeOnClose)
        : StreamReader()
    {
        mData = mPos = static_cast<uchar*>(pMem);
        mSize = size;
        mEnd = mData + mSize;
        mFreeOnClose = freeOnClose;
    }
    //-----------------------------------------------------------------------
    MemoryStreamReader::MemoryStreamReader(const String& name, void* pMem, size_t size, 
        bool freeOnClose)
        : StreamReader(name)
    {
        mData = mPos = static_cast<uchar*>(pMem);
        mSize = size;
        mEnd = mData + mSize;
        mFreeOnClose = freeOnClose;
    }
    //-----------------------------------------------------------------------
    MemoryStreamReader::MemoryStreamReader(StreamReader& sourceStream, 
        bool freeOnClose)
        : StreamReader()
    {
        // Copy data from incoming stream
        mSize = sourceStream.size();
        mData = new uchar[mSize];
        sourceStream.read(mData, mSize);
        mPos = mData;
        mEnd = mData + mSize;
        mFreeOnClose = freeOnClose;
    }
    //-----------------------------------------------------------------------
    MemoryStreamReader::MemoryStreamReader(StreamReaderPtr& sourceStream, 
        bool freeOnClose)
        : StreamReader()
    {
        // Copy data from incoming stream
        mSize = sourceStream->size();
        mData = new uchar[mSize];
        sourceStream->read(mData, mSize);
        mPos = mData;
        mEnd = mData + mSize;
        mFreeOnClose = freeOnClose;
    }
    //-----------------------------------------------------------------------
    MemoryStreamReader::MemoryStreamReader(const String& name, StreamReader& sourceStream, 
        bool freeOnClose)
        : StreamReader(name)
    {
        // Copy data from incoming stream
        mSize = sourceStream.size();
        mData = new uchar[mSize];
        sourceStream.read(mData, mSize);
        mPos = mData;
        mEnd = mData + mSize;
        mFreeOnClose = freeOnClose;
    }
    //-----------------------------------------------------------------------
    MemoryStreamReader::MemoryStreamReader(const String& name, const StreamReaderPtr& sourceStream, 
        bool freeOnClose)
        : StreamReader(name)
    {
        // Copy data from incoming stream
        mSize = sourceStream->size();
        mData = new uchar[mSize];
        sourceStream->read(mData, mSize);
        mPos = mData;
        mEnd = mData + mSize;
        mFreeOnClose = freeOnClose;
    }
    //-----------------------------------------------------------------------
    MemoryStreamReader::MemoryStreamReader(size_t size, bool freeOnClose)
        : StreamReader()
    {
        mSize = size;
        mFreeOnClose = freeOnClose;
        mData = new uchar[size];
        mPos = mData;
        mEnd = mData + mSize;
    }
    //-----------------------------------------------------------------------
    MemoryStreamReader::MemoryStreamReader(const String& name, size_t size, 
        bool freeOnClose)
        : StreamReader(name)
    {
        mSize = size;
        mFreeOnClose = freeOnClose;
        mData = new uchar[size];
        mPos = mData;
        mEnd = mData + mSize;
    }
    //-----------------------------------------------------------------------
    MemoryStreamReader::~MemoryStreamReader()
    {
        close();
    }
    //-----------------------------------------------------------------------
    size_t MemoryStreamReader::read(void* buf, size_t count)
    {
        size_t cnt = count;
        // Read over end of memory?
        if (mPos + cnt > mEnd)
            cnt = mEnd - mPos;
        if (cnt == 0)
            return 0;

        memcpy(buf, mPos, cnt);
        mPos += cnt;
        return cnt;
    }
    //-----------------------------------------------------------------------
  //  size_t MemoryStreamReader::readLine(char* buf, size_t maxCount, 
  //      const String& delim)
  //  {
  //      // Deal with both Unix & Windows LFs
		//bool trimCR = false;
		//if (delim.find_first_of('\n') != String::npos)
		//{
		//	trimCR = true;
		//}

  //      size_t pos = 0;

  //      // Make sure pos can never go past the end of the data 
  //      while (pos < maxCount && mPos < mEnd)
  //      {
  //          if (delim.find(*mPos) != String::npos)
  //          {
  //              // Trim off trailing CR if this was a CR/LF entry
  //              if (trimCR && pos && buf[pos-1] == '\r')
  //              {
  //                  // terminate 1 character early
  //                  --pos;
  //              }

  //              // Found terminator, skip and break out
  //              ++mPos;
  //              break;
  //          }

  //          buf[pos++] = *mPos++;
  //      }

  //      // terminate
  //      buf[pos] = '\0';

  //      return pos;
  //  }
    //-----------------------------------------------------------------------
    size_t MemoryStreamReader::skipLine(const String& delim)
    {
        size_t pos = 0;

        // Make sure pos can never go past the end of the data 
        while (mPos < mEnd)
        {
            ++pos;
            if (delim.find(*mPos++) != String::npos)
            {
                // Found terminator, break out
                break;
            }
        }

        return pos;

    }
    //-----------------------------------------------------------------------
    void MemoryStreamReader::skip(long count)
    {
        size_t newpos = (size_t)( ( mPos - mData ) + count );
        assert( mData + newpos <= mEnd );        

        mPos = mData + newpos;
    }
    //-----------------------------------------------------------------------
    void MemoryStreamReader::seek( size_t pos )
    {
        assert( mData + pos <= mEnd );
        mPos = mData + pos;
    }
    //-----------------------------------------------------------------------
    size_t MemoryStreamReader::tell(void) const
	{
		//mData is start, mPos is current location
		return mPos - mData;
	}
	//-----------------------------------------------------------------------
    bool MemoryStreamReader::eof(void) const
    {
        return mPos >= mEnd;
    }
    //-----------------------------------------------------------------------
    void MemoryStreamReader::close(void)    
    {
        if (mFreeOnClose && mData)
        {
            delete [] mData;
            mData = 0;
        }

    }
    //-----------------------------------------------------------------------

	
#endif
	
	
}// end of namespace 
