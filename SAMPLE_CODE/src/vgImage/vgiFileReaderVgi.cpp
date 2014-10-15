


#include <vgStableHeaders.h>
#include <vgImage/vgiFileReaderVgi.h>
#include <vgKernel/vgkStreamReader.h>
#include <vgKernel/vgkCrcUtility.h>


namespace vgImage {
	
	
	using namespace vgKernel;
	
	
	//----------------------------------------------------------------
	VgiBriefPtrVec* FileReaderVgi::readFromFile( const String& abs_filename,
		VgiHeader& outHeader)
	{
		StreamReaderPtr prereader = 
			StreamReaderFactory::createFromFile( abs_filename );

		if ( prereader.isNull() == true )
		{
			std::ostringstream o;
			o << "文件: " << abs_filename	<< " 不存在.";
			MessageBox( NULL , o.str().c_str()  , "Error" , MB_OK );
			return NULL;
		}

		prereader.setNull();

#if 0
		// 校验
		DWORD precrc;
		bool getcrc = CrcUtility::getFileCrc32Code( abs_filename , precrc );
		assert( getcrc == true );

		if ( precrc != 0xFFFFFFFF )
		{
			std::ostringstream o;
			o << "文件: " << abs_filename	<< " 校验失败, 文件可能损坏";
			MessageBox( NULL , o.str().c_str()  , "Error" , MB_OK );
			return NULL;
		}
#endif

		StreamReaderPtr preader = 
			StreamReaderFactory::createFromFile( abs_filename );

		assert( preader.isNull() == false );

		//------------------------------------------
		// 首先读取header
		//------------------------------------------
		VgiHeader &header = outHeader;
		preader->read( &header , sizeof( header ) );

		assert( String(header._fourCC) == "VGI" );

		if ( String(header._fourCC) != "VGI" ||
			header._sizeOfWholeFile != preader->size())
		{
			std::ostringstream o;
			o << "文件: " << abs_filename	<< " 可能损坏.";
			MessageBox( NULL , o.str().c_str()  , "Error" , MB_OK );
			return NULL;
		}

		assert( header._lengthOfOneBrief == sizeof( VgiBrief ) );
		assert( header._sizeOfHeader == sizeof( VgiHeader ) );
		assert( header._numberOfBriefs > 0 );

		//------------------------------------------
		// 开始读取brief
		//------------------------------------------
		preader->seek( header._positionOfBriefs );
		VgiBriefPtrVec* ret = new VgiBriefPtrVec;

		for ( int i = 0 ; i < header._numberOfBriefs ; ++ i )
		{
			VgiBriefPtr brief(new VgiBrief);

			long readnum = preader->read( brief.getPointer() , header._lengthOfOneBrief );
			assert( readnum == header._lengthOfOneBrief );

			ret->push_back( brief );
		}

		assert( ret->size() == header._numberOfBriefs );

		return ret;
	}
	//----------------------------------------------------------------
}// end of namespace vgImage
