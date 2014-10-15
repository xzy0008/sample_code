


#include <vgStableHeaders.h>
#include <vgKernel/vgkWarning.h>
#include <vgTerritory/vgtFileReaderVtr.h>


namespace vgTerritory {
	
	using namespace vgKernel;
	
	
	//----------------------------------------------------------------
	VtrBriefPtrVec* FileReaderVtr::readFromFile( const String& abs_filename )
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
			o << "文件: " << abs_filename	<< " 校验失败, 文件可能损坏, 继续导入吗?";
			//MessageBox( NULL , o.str().c_str()  , "Error" , MB_OK );

			int ret = VGK_WARN( vgKernel::Warning::WARN_INVALID_STATE , 
				vgKernel::Warning::BUTTON_YES_NO , o.str() , 
				"FileReaderVtr::readFromFile" );

			if ( ret != vgKernel::Warning::RETURN_YES )
			{
				return NULL;
			}
		}
#endif

		StreamReaderPtr preader = 
			StreamReaderFactory::createFromFile( abs_filename );

		assert( preader.isNull() == false );

		//------------------------------------------
		// 首先读取header
		//------------------------------------------
		VtrHeader header;
		preader->read( &header , sizeof( header ) );

		assert( String(header._fourCC) == "VTR" );

		if ( String(header._fourCC) != "VTR" ||
			header._sizeOfWholeFile != preader->size())
		{
			std::ostringstream o;
			o << "文件头信息和文件不一致: " << abs_filename	<< ", 文件可能损坏, 继续导入吗?";
			//MessageBox( NULL , o.str().c_str()  , "Error" , MB_OK );

			int ret = VGK_WARN( vgKernel::Warning::WARN_INVALID_STATE , 
				vgKernel::Warning::BUTTON_YES_NO , o.str() , 
				"FileReaderVtr::readFromFile" );

			if ( ret != vgKernel::Warning::RETURN_YES )
			{
				return NULL;
			}
		}

		assert( header._lengthOfOneBrief == sizeof( VtrBrief ) );
		assert( header._sizeOfHeader == sizeof( VtrHeader ) );
		assert( header._numberOfBriefs > 0 );

		//------------------------------------------
		// 开始读取brief
		//------------------------------------------
		preader->seek( header._positionOfBriefs );
		VtrBriefPtrVec* ret = new VtrBriefPtrVec;

		for ( int i = 0 ; i < header._numberOfBriefs ; ++ i )
		{
			VtrBriefPtr brief(new VtrBrief);

			long readnum = preader->read( brief.getPointer() , header._lengthOfOneBrief );
			assert( readnum == header._lengthOfOneBrief );

			ret->push_back( brief );
		}

		assert( ret->size() == header._numberOfBriefs );

		return ret;
	}
	//----------------------------------------------------------------
	VtrHeaderPtr FileReaderVtr::readHeaderFromFile( const String& abs_filename )
	{
		StreamReaderPtr preader = 
			StreamReaderFactory::createFromFile( abs_filename );

		if ( preader.isNull() == true )
		{
			std::ostringstream o;
			o << "文件: " << abs_filename	<< " 不存在.";
			MessageBox( NULL , o.str().c_str()  , "Error" , MB_OK );
			return VtrHeaderPtr();
		}

		assert( preader.isNull() == false );

		//------------------------------------------
		// 首先读取header
		//------------------------------------------
		VtrHeaderPtr headerptr( new VtrHeader );

		preader->read( headerptr.getPointer() , sizeof( VtrHeader ) );

		assert( String(headerptr->_fourCC) == "VTR" );

#if 0
		if ( String(headerptr->_fourCC) != "VTR" ||
			headerptr->_sizeOfWholeFile != preader->size())
		{
			std::ostringstream o;
			o << "文件: " << abs_filename	<< " 可能损坏.";
			MessageBox( NULL , o.str().c_str()  , "Error" , MB_OK );
			return VtrHeaderPtr();
		}
#endif

		assert( headerptr->_lengthOfOneBrief == sizeof( VtrBrief ) );
		assert( headerptr->_sizeOfHeader == sizeof( VtrHeader ) );
		assert( headerptr->_numberOfBriefs > 0 );


		return headerptr;
	}
	//----------------------------------------------------------------

}// end of namespace vgTerritory
