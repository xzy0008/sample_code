




#include <vgStableHeaders.h>
#include <vgTerritory/vgTerrainHugeImageUtil.h>



namespace vgTerritory {

	const long AimSmallBlocksOption::DEFAULT_WIDTH = 1024;
	const long AimSmallBlocksOption::DEFAULT_HEIGHT = 1024;

	
	AimSmallBlocksOption::AimSmallBlocksOption(
		const String& fileprefix,
		const long& width,
		const long& height,
		const String& tmpfilepostfix		/*= "bmp"*/,
		const String& fileposfix			/*= "dds"*/,
		const bool& reverseSequence			/*= false*/,
		const bool& axisLeftTop				/*= false*/,
		const bool& loginfo					/*= true*/,
		const bool& overrid					/*= false*/,
		const bool& outputcombinesblock		/*= false*/,
		const String& outcombinesblockname	/*= ""*/,
		const bool& outputcombinefblock		/*= false*/,
		const String& outcombinefblockname	/*= ""*/,
		const bool& drawinfo				/*= false*/,
		const ImagePos& offset				/*= ImagePos::ZERO*/,
		const long& pixceloverlap		/*= 1*/,
		const long& sblocknum			/*= -1 */,
		const long& width_and_height_add_one /*= 0*/)
	{
		this->setParameters(fileprefix,
			width,
			height,
			tmpfilepostfix,
			fileposfix,
			reverseSequence,
			axisLeftTop,
			loginfo,
			overrid	,
			outputcombinesblock,
			outcombinesblockname,
			outputcombinefblock,
			outcombinefblockname,
			drawinfo,
			offset,
			pixceloverlap,
			sblocknum ,width_and_height_add_one );
	}

	void AimSmallBlocksOption::setParameters(
		const String& fileprefix,
		const long& width,
		const long& height,
		const String& tmpfilepostfix		/*= "bmp"*/,
		const String& fileposfix			/*= "dds"*/,
		const bool& reverseSequence			/*= false*/,
		const bool& axisLeftTop				/*= false*/,
		const bool& loginfo					/*= true*/,
		const bool& overrid					/*= false*/,
		const bool& outputcombinesblock		/*= false*/,
		const String& outcombinesblockname	/*= ""*/,
		const bool& outputcombinefblock		/*= false*/,
		const String& outcombinefblockname	/*= ""*/,
		const bool& drawinfo				/*= false*/,
		const ImagePos& offset				/*= ImagePos::ZERO*/,
		const long& pixceloverlap		/*= 1*/,
		const long& sblocknum			/*= -1 */,
		const long& width_and_height_add_one/* = 0*/)
	{
		this->widthAndHeightAddOne = width_and_height_add_one;

		this->aimFilePostfix = fileposfix;
		this->aimFilePrefix = fileprefix;
		this->aimHeight = height;
		this->aimOffset = offset;
		this->aimPixcelOverlap = pixceloverlap;
		this->aimSmallBlocksNum = sblocknum;
		this->aimTempFilePostfix = tmpfilepostfix;
		this->aimWidth = width;
		this->ifLogInfo = loginfo;
		this->ifDrawInfo = drawinfo;
		this->ifOutputCombinedFileBlocks = outputcombinefblock;
		this->aimCombinedFBlockName = outcombinefblockname;
		this->ifOutputCombinedSmallBlocks = outputcombinesblock;
		this->aimCombinedSBlockName = outcombinesblockname;
		this->ifOverrideExist = overrid;

		this->ifAxisLeftTop = axisLeftTop;
		this->ifReverseSequence = reverseSequence;

		if ( aimCombinedFBlockName.empty() )
		{
			this->aimCombinedFBlockName = fileprefix + _T('.') + aimFilePostfix;
		}
		if ( aimCombinedSBlockName.empty() )
		{
			this->aimCombinedSBlockName = fileprefix + _T("2.") + aimFilePostfix;
		}

		this->checkParametersIsAllRight();
	}
	//----------------------------------------------------------------
	/// 设定默认值.
	void  AimSmallBlocksOption::setParametersDefault(const String& fileprefix /*= "cuttedimage"*/)
	{
		this->aimFilePostfix =  _T("bmp");
		this->aimFilePrefix = fileprefix;
		this->aimHeight = DEFAULT_HEIGHT;
		this->aimOffset = ImagePos::ZERO;
		this->aimPixcelOverlap = 1;
		this->aimSmallBlocksNum = -1;
		this->aimTempFilePostfix =  _T("bmp");
		this->aimWidth = DEFAULT_WIDTH;
		this->ifDrawInfo = false;
		this->ifOutputCombinedFileBlocks = false;
		this->aimCombinedFBlockName = fileprefix + _T('.') + aimFilePostfix;
		this->ifOutputCombinedSmallBlocks = false;
		this->aimCombinedSBlockName = fileprefix + _T('.') + aimFilePostfix;
		this->ifOverrideExist = false;
		this->ifLogInfo = false;

		this->ifReverseSequence = false;
		this->ifAxisLeftTop = false;

		widthAndHeightAddOne = 0;

		this->checkParametersIsAllRight();
	}
	//----------------------------------------------------------------
	String AimSmallBlocksOption::getDetails() const
	{
		String result;
		result += String( _T("AimSmallBlocksOption = ( ")) 
			+  _T("\n aimWidth : ") + StringUtility::textCast(aimWidth)
			+  _T("\n aimHeight : ") + StringUtility::textCast(aimHeight)
			+  _T("\n aimFilePostfix = ") + aimFilePostfix 
			+  _T("\n aimFilePrefix = ") + aimFilePrefix 
			+  _T("\n aimOffset = ") + aimOffset.getDetails() 
			+  _T("\n aimPixcelOverlap = ") + StringUtility::textCast(aimPixcelOverlap) 
			+  _T("\n aimSmallBlocksNum = ") + StringUtility::textCast(aimSmallBlocksNum) 
			+  _T("\n aimTempFilePostfix = ") + aimTempFilePostfix 
			+  _T("\n ifDrawInfo = ") + StringUtility::textCast(ifDrawInfo) 
			+  _T("\n ifLogInfo = ") + StringUtility::textCast(ifLogInfo)
			+  _T("\n ifOutputCombinedFileBlocks = ") + StringUtility::textCast(ifOutputCombinedFileBlocks) 
			+  _T("\n ifOutputCombinedSmallBlocks = ") + StringUtility::textCast(ifOutputCombinedSmallBlocks) 
			+  _T("\n ifOverrideExist = ") + StringUtility::textCast(ifOverrideExist)
			+  _T("\n ifReverseSequence = ") + StringUtility::textCast(ifReverseSequence)
			+  _T("\n ifAxisLeftTop = ") + StringUtility::textCast(ifAxisLeftTop);

		return result;
	}
	//----------------------------------------------------------------
	inline bool  AimSmallBlocksOption::checkParametersIsAllRight()
	{
		if ( aimWidth <= 1 || aimHeight <= 1 )
		{
			assert( 0 &&  _T("The input params : width and height size is < 1 ."));
			VGK_EXCEPT(Exception::ERR_INVALID_STATE,
				 _T("The input params : width and height size is < 1 .") ,
				 _T("AimSmallBlocksOption::checkParametersIsAllRight()"));
			return false;
		}
		if ( aimPixcelOverlap > (aimWidth/2) ||
			aimPixcelOverlap < (-aimWidth/2) ||
			aimPixcelOverlap > (aimHeight/2) ||
			aimPixcelOverlap < (-aimHeight/2) )
		{
			assert( 0 &&  _T("aimPixcelOverlap太大或者太小,并不保证结果正确!"));
			VGK_EXCEPT(Exception::ERR_INVALID_STATE,
				 _T("The input params : aimPixcelOverlap's size is not correct.") ,
				 _T("AimSmallBlocksOption::checkParametersIsAllRight()"));
			return false;
		}
		if ( aimFilePrefix.empty() && aimFilePostfix.empty() )
		{
			assert(0 &&  _T("The input params : aimFilePrefix and aimFilePostfix size is both empty ."));
			VGK_EXCEPT(Exception::ERR_INVALID_STATE,
				 _T("The input params : aimFilePrefix and aimFilePostfix size is both empty .") ,
				 _T("AimSmallBlocksOption::checkParametersIsAllRight()"));

			return false;
		}

		/*
		if ( !ImageUtility::checkImageSizeIsPowerOfTwo( aimWidth , aimHeight ) )
		{
			int ret = VG_WARN(Warning::WARN_INVALIDPARAMS ,
				Warning::BUTTON_YES_NO,
				"The input params : width and height size is not power of 2.This may cause some unkown errors.Would you like the default parameters of size ( both the width and height is 1024 ) override your input ones?" ,
				"AimSmallBlocksOption::checkParametersIsAllRight()");

			if ( ret == Warning::RETURN_YES )
			{
				aimWidth = DEFAULT_WIDTH;
				aimHeight = DEFAULT_HEIGHT;
			}
			if ( ret == Warning::RETURN_NO )
			{
				// no nothing here
			}
		}

		*/

		if ( aimCombinedFBlockName.empty() || aimCombinedSBlockName.empty() )
		{
			assert(0 && "The input params : aimCombinedFBlockName or aimCombinedFBlockName is empty .");
			VGK_EXCEPT(Exception::ERR_INVALID_STATE,
				 _T("The input params : aimCombinedFBlockName or aimCombinedFBlockName is empty .") ,
				 _T("AimSmallBlocksOption::checkParametersIsAllRight()"));

			return false;
		}

		if ( aimTempFilePostfix ==  _T("dds") )
		{
			int ret = VGK_WARN(Warning::WARN_INVALIDPARAMS ,
				Warning::BUTTON_YES_NO,
				_T( "The input params : aimTempFilePostfix may not be supported.\
				\n\"dds\"为不推荐的temp文件格式,更改为推荐的默认格式\"bmp\"吗?" ),
				 _T("AimSmallBlocksOption::checkParametersIsAllRight"));
			if ( ret == Warning::RETURN_YES )
			{
				aimTempFilePostfix =  _T("bmp");
			}
		}
		if ( aimFilePostfix ==  _T("dds") && ifOutputCombinedSmallBlocks == true )
		{
			assert(0 && "The input params : aimFilePostfix and ifOutputCombinedSmallBlocks are mutex!");
			VGK_EXCEPT(Exception::ERR_INVALID_STATE,
				 _T("The input params : aimFilePostfix and ifOutputCombinedSmallBlocks are mutex!") ,
				 _T("AimSmallBlocksOption::checkParametersIsAllRight()"));
			return false;
		}
		/// waiting to add ...
		/// 比如,估计文件大小,若超过内存大小,肯定不能完成时,则抛出异常.
		/// 再比如,文件格式不支持时 ; aimSmallBlocksNum不符合正常范围时等等.....

		return true;
	}
	//////////////////////////////////////////////////////////////////////////

	//----------------------------------------------------------------
	String FileNamesInfo::getDetails() const
	{
		int countCol = 0;
		String result( _T("FileNamesInfo = ( columnNum : "));
		result += StringUtility::textCast( columnNum ) +  _T(" , rowNum : ");
		result += StringUtility::textCast( rowNum ) ;

		result +=  _T("\nFiles info list:\n");

		for ( StringVector::const_iterator i = filenameVector.begin() ;
			i != filenameVector.end() ;
			++ i)
		{
			result +=  _T("\t\t") + (*i);

			countCol ++;
			if ( countCol % columnNum == 0 )
			{
				result +=  _T("\n");
				countCol = 0;
			}
		}
		result +=  _T(" )\n");
		return result;
	}
	//----------------------------------------------------------------
	ImageRect fileBlockVector::getWorldImageRect() const
	{
		ImagePos minpos = ImagePos::MAX;
		ImagePos maxpos = ImagePos::MIN;
		for ( vector<fileBlock>::const_iterator i = vector<fileBlock>::begin() ;
			i != vector<fileBlock>::end() ;
			++ i )
		{
			maxpos = ImageUtility::getMaximalPos( maxpos , i->fileAbsoluteRect.maxPos );
			minpos = ImageUtility::getMinimalPos( minpos , i->fileAbsoluteRect.minPos );
		}
		//assert( minpos == ImagePos::ZERO );



		return ImageRect( minpos , maxpos );
	}
	//----------------------------------------------------------------
	String  fileBlock::getDetails() const
	{
		String result( _T("-------------fileBlock info------------\n fileAbsoluteRect = "));
		result += fileAbsoluteRect.getDetails() +  _T(" \n fileSrcName = ");
		result += fileSrcName +  _T("\n");

		result +=  _T("   TaskList as follows :\n");
		for (smallBlockVector::const_iterator i = taskList.begin() ;
			i != taskList.end() ; ++ i )
		{
			result += i->getDetails() +  _T("\n");
		}

		result +=  _T("  TaskList end.");
		/// tasklist waiting to add...
		return result;
	}

	
	//----------------------------------------------------------------
	FileNamesInfoPtr HugeImageUtil::createFileNamesInfoFormArray(
		const StringVector& stringvec ,  const long& col , 
		const long& row , const bool& loginfo )
	{
		if ( (long)stringvec.size() < ( col * row ) )
		{
			assert(0 && "StringVector's size not match!");
			VGK_EXCEPT(Exception::ERR_INVALIDPARAMS,
				 _T("StringVector's size not match!"),
				 _T("HugeImagesProcessor::createFileNamesInfoFormArray()"));

			return FileNamesInfoPtr();
		}
		/// 注意要考虑什么情况下返回NULL的情况.

		FileNamesInfoPtr pfbinfo( new FileNamesInfo );
		pfbinfo->rowNum = row;
		pfbinfo->columnNum = col;

		/// 这里用直接复制传递,效率说实话不高,最好的方法是传递指针
		/// 但是stringvec算不上超大的内存占用量,所以这里还是简单起见.
		pfbinfo->filenameVector = stringvec;

		if ( loginfo )
		{
			LogManager &logmgr = LogManager::getSingleton();
			logmgr.logMessage( pfbinfo->getDetails() );
		}
		return pfbinfo;
	}
	//----------------------------------------------------------------
	FileNamesInfoPtr HugeImageUtil::createFileNamesInfoFormArray( 
		const TCHAR** const &chararray ,  const long& col ,
		const long& row , const bool& loginfo )
	{
		FileNamesInfoPtr pfbinfo( new FileNamesInfo );
		pfbinfo->rowNum = row;
		pfbinfo->columnNum = col;

		String str;
		for ( int y = 0 ; y < col ; ++ y )
		{
			for ( int x = 0 ; x < row ; ++ x )
			{
				str = *(chararray + x + y * row);
				pfbinfo->filenameVector.push_back( str );
			}// end of x
		}
		if ( loginfo )
		{
			LogManager &logmgr = LogManager::getSingleton();
			logmgr.logMessage( pfbinfo->getDetails() );
		}
		return pfbinfo;
	}
	//----------------------------------------------------------------


	String smallBlock::getPostfixNumFlag( const bool& reverseSeq ) const
	{
		assert( checkSafe() );

		std::ostringstream o;
		o << "_";
		if ( reverseSeq == false )
		{
			o <<  worldSequenceNumber.x << "_" << worldSequenceNumber.y << ".";
		}
		else
		{
			o <<  worldSequenceNumber.y << "_" << worldSequenceNumber.x << ".";
		}

		String post = o.str();

		if ( hasIntersect )
		{
			post += _T( "tmp." );
		}
		return post;
	}
}// end of namespace vgTerritory
