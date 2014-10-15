


#include <vgStableHeaders.h>
#include <vgTerritory/vgtFileHandleVtr.h>
#include <vgKernel/vgkStringUtility.h>
#include <vgTerritory/vgtFileReaderVtr.h>
#include <vgTerritory/vgtDefinition.h>
#include <vgKernel/vgkSystemUtility.h>


namespace vgTerritory {
	

	//----------------------------------------------------------------
	bool FileHandleVtr::exist( const String& metafilename )
	{
		ElevationItem* item = getElevationItem( metafilename );

		return item != NULL;
	}
	//----------------------------------------------------------------
	vgKernel::StringVector* FileHandleVtr::listMetaFileNames()
	{
		assert( _isOpened == true );

		vgKernel::StringVector* ret = new vgKernel::StringVector;

		ElevationItemMap::iterator iter = _elevItems.begin();
		ElevationItemMap::iterator iter_end = _elevItems.end();

		for ( ; iter != iter_end ; ++iter )
		{
			ret->push_back( iter->first );
		}

		return ret;
	}
	//----------------------------------------------------------------
	bool FileHandleVtr::open()
	{

		// 首先检查扩展名
		String ext = vgKernel::StringUtility::getFileExtension( _filePath );

		vgKernel::StringUtility::trim( ext );
		if ( ext != "vtr" )
		{
			MessageBox( NULL , "非vtr文件" , "Error" , MB_OK );
			return false;
		}

		//------------------------------------------
		// 开始读取Vgi索引数据
		//------------------------------------------
		VtrBriefPtrVec* briefs = 
			vgTerritory::FileReaderVtr::readFromFile( _filePath );

		if ( briefs == NULL )
		{
			MessageBox( NULL , "读取vtr文件失败" , "Error" , MB_OK );
			return false;
		}

		if ( briefs->empty() == true )
		{
			MessageBox( NULL , "读取vtr文件失败" , "Error" , MB_OK );
			return false;
		}

		//------------------------------------------
		// 读取header
		//------------------------------------------
		_vtrFileHeader = vgTerritory::FileReaderVtr::readHeaderFromFile( _filePath );

		assert( _vtrFileHeader.isNull() == false );

		assert( _elevItems.empty() == true );

		VtrBriefPtrVec::iterator iter = briefs->begin();
		VtrBriefPtrVec::iterator iter_end  =briefs->end();

		for ( ; iter != iter_end ; ++iter )
		{
			VtrBrief* curbrief = (*iter).getPointer();

			ElevationItem* item = 
				new ElevationItem( curbrief, this );


			String filename = item->getName();

			_elevItems.insert( std::make_pair( 
				filename , item ) );
		}


		//------------------------------------------
		// 清理
		//------------------------------------------
		delete briefs;

		//------------------------------------------
		// 注意!设定可读可写方式!
		//------------------------------------------
		int access = 
			FILEHANDLE_OPENACESS_READ | FILEHANDLE_OPENACESS_WRITE;

		setOpenAccess( (FileHandleOpenAccess) access );

		// 创建FileHandle
		bool openres = FileHandle::open();

		if ( openres == false )
		{
			dropItemsData();
			return false;
		}


		return true;
	}
	//----------------------------------------------------------------
	void FileHandleVtr::close()
	{
		dropItemsData();


		FileHandle::close();
	}
	//----------------------------------------------------------------
	bool FileHandleVtr::extractToMultipleFiles( const String& save_multiple_file_path )
	{
		assert(0);
		return true;
	}
	//----------------------------------------------------------------
	ElevationItem* FileHandleVtr::getElevationItem( const String& metafilename )
	{
		assert( _isOpened == true );

		ElevationItemMap::iterator result = _elevItems.find( metafilename );
		if ( result == _elevItems.end() )
		{
			return NULL;
		}

		return result->second;
	}
	//----------------------------------------------------------------
	float FileHandleVtr::getMaxScaleY()
	{
		assert( _elevItems.empty() == false );
		float ret = _elevItems.begin()->second->getDisplaceScaleY();

		ElevationItemMap::iterator iter = _elevItems.begin();
		ElevationItemMap::iterator iter_end = _elevItems.end();

		for ( ; iter != iter_end ; ++ iter )
		{
			ret = VGT_MAX( iter->second->getDisplaceScaleY() , ret );
		}

		assert( ret > 0.0f );
		return ret;
	}
	//----------------------------------------------------------------
	FileHandleVtr* FileHandleVtr::openNextVtrFile()
	{
		assert( _vtrFileHeader.isNull() == false );
		long nextfileid = _vtrFileHeader->_nextVtrFileID;

		if ( nextfileid == 0 )
		{
			return NULL;
		}

		String path = StringUtility::getPathFromAbsoluteFilename( getFilePath() );
		String terrainname = _vtrFileHeader->name;
		std::ostringstream o;
		o << path  << "\\"  << terrainname << ".part" << nextfileid << ".vtr";
		String nextfilename = o.str();

		if ( SystemUtility::checkFileExist( nextfilename ) == false )
		{
			std::ostringstream o;
			o << "打开文件: " << nextfilename << "时失败, 文件不存在.";
			MessageBox( NULL , o.str().c_str() , "提示" , MB_OK );
			return NULL;
		}

		FileHandleVtr* ret = new FileHandleVtr( nextfilename );

		bool openok = ret->open();

		if ( openok == false )
		{
			std::ostringstream o;
			o << "打开文件: " << nextfilename << "时失败.";
			MessageBox( NULL , o.str().c_str() , "提示" , MB_OK );

			delete ret;
			return NULL;
		}

		_nextHandle= ret;
		return ret;
	}
	//----------------------------------------------------------------
	String FileHandleVtr::getNextFilePath()
	{
		assert( _vtrFileHeader.isNull() == false );
		long nextfileid = _vtrFileHeader->_nextVtrFileID;

		if ( nextfileid == 0 )
		{
			return "";
		}

		String path = StringUtility::getPathFromAbsoluteFilename( getFilePath() );
		String terrainname = _vtrFileHeader->name;
		std::ostringstream o;
		o << path  << "\\"  << terrainname << ".part" << nextfileid << ".vtr";
		String nextfilename = o.str();

		return nextfilename;
	}
	//----------------------------------------------------------------
	void FileHandleVtr::dropItemsData()
	{
		ElevationItemMap::iterator iter = _elevItems.begin();
		ElevationItemMap::iterator iter_end = _elevItems.end();

		for ( ; iter != iter_end ; ++iter )
		{
			delete iter->second;
		}

		_elevItems.clear();
	}
	//----------------------------------------------------------------
}// end of namespace vgTerritory
