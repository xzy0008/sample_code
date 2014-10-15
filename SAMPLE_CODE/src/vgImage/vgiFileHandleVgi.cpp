


#include <vgStableHeaders.h>
#include <vgImage/vgiIoRequestExtractVgi.h>
#include <vgImage/vgiImageMiniature.h>
#include <vgImage/vgiFileHandleVgi.h>
#include <vgImage/vgiFileReaderVgi.h>
#include <vgImage/vgiImageUtility.h>
#include <vgAsyn/vgaMemoryFileManager.h>
#include <vgKernel/vgkSystemUtility.h>
#include <vgKernel/vgkStringUtility.h>

namespace vgImage {
	

	//----------------------------------------------------------------
	bool FileHandleVgi::extractToMultipleFiles( const String& save_multiple_file_path )
	{
		assert( _isOpened );

		ImageMiniMap::iterator iter = _imgMiniMap.begin();
		ImageMiniMap::iterator iter_end = _imgMiniMap.end();

		for ( ; iter != iter_end ; ++iter )
		{
			ImageMiniature* curimg = iter->second;
			assert( curimg != NULL );

			vgAsyn::FileInfo* asynfileinfo = curimg->getMetaFileInfo();

			if ( asynfileinfo == NULL || 
				curimg->isValid() == false )
			{
				std::ostringstream o;
				o << "解压" << getFilePath() << "文件时:" << iter->first << "文件出错";
				MessageBox( NULL , o.str().c_str() , "Error" , MB_OK );
				continue;
			}

			vgAsyn::IoRequest* requst =
				new IoRequestExtractVgi( save_multiple_file_path, asynfileinfo );

			requst->sendRequestAndDoAsynHandlerFunc();
		}

		return true;
	}
	//----------------------------------------------------------------
	bool FileHandleVgi::open()
	{
		// 首先检查扩展名
		if ( ImageUtility::findImageFileExtension( _filePath ) != "vgi" )
		{
			MessageBox( NULL , "非vgi文件" , "Error" , MB_OK );
			return false;
		}

		// 创建FileHandle
		bool openres = FileHandle::open();

		if ( openres == false )
		{
			return false;
		}

		//------------------------------------------
		// 开始读取Vgi索引数据
		//------------------------------------------
		VgiBriefPtrVec* briefs = 
			FileReaderVgi::readFromFile( _filePath , _header );

		if ( briefs == NULL )
		{
			MessageBox( NULL , "读取vgi文件失败" , "Error" , MB_OK );
			return false;
		}

		if ( briefs->empty() == true )
		{
			MessageBox( NULL , "读取vgi文件失败" , "Error" , MB_OK );
			return false;
		}

		assert( _imgMiniMap.empty() == true );

		VgiBriefPtrVec::iterator iter = briefs->begin();
		VgiBriefPtrVec::iterator iter_end  =briefs->end();

		for ( ; iter != iter_end ; ++iter )
		{
			VgiBrief* curbrief = (*iter).getPointer();

			ImageMiniature* mini_img = 
				new ImageMiniature( curbrief, this );

			assert( mini_img->isValid() == true );

			String filename = mini_img->getMetaFileName();

			//vgKernel::StringUtility::toLowerCase( filename );

			_imgMiniMap.insert( std::make_pair( 
				filename , mini_img ) );
		}


		//------------------------------------------
		// 清理
		//------------------------------------------
		delete briefs;


		//------------------------------------------
		// 加入进memoryfile
		//------------------------------------------
		//vgAsyn::MemoryFileManager::getSingleton().addMemoryFile( this );


		return true;
	}
	//----------------------------------------------------------------
	void FileHandleVgi::close()
	{
		ImageMiniMap::iterator iter = _imgMiniMap.begin();
		ImageMiniMap::iterator iter_end = _imgMiniMap.end();

		for ( ; iter != iter_end ; ++iter )
		{
			delete iter->second;
		}

		_imgMiniMap.clear();

		FileHandle::close();
	}
	//----------------------------------------------------------------
	bool FileHandleVgi::exist( const String& metafilename )
	{
		ImageMiniature* imgmini = getImageMiniature( metafilename );

		return imgmini != NULL;
	}
	//----------------------------------------------------------------
	vgKernel::StringVector* FileHandleVgi::listMetaFileNames()
	{
		assert( _isOpened == true );

		vgKernel::StringVector* ret = new vgKernel::StringVector;

		ImageMiniMap::iterator iter = _imgMiniMap.begin();
		ImageMiniMap::iterator iter_end = _imgMiniMap.end();

		for ( ; iter != iter_end ; ++iter )
		{
			ret->push_back( iter->first );
		}

		return ret;
	}
	//----------------------------------------------------------------
	ImageMiniature* FileHandleVgi::getImageMiniature( const String& metafilename )
	{
		assert( _isOpened == true );

		ImageMiniMap::iterator result = _imgMiniMap.find( metafilename );
		if ( result == _imgMiniMap.end() )
		{
			return NULL;
		}

		return result->second;
	}
	//----------------------------------------------------------------
	FileHandleVgi* FileHandleVgi::openNextFile()
	{
		assert( _imgMiniMap.empty() == false );
		long nextfileid = _header._nextFileID;

		if ( nextfileid == 0 )
		{
			return NULL;
		}

		String nextfilename = getNextFilePath();

		if ( nextfilename == "" )
		{
			return NULL;
		}

		if ( SystemUtility::checkFileExist( nextfilename ) == false )
		{
			std::ostringstream o;
			o << "打开文件: " << nextfilename << "时失败, 文件不存在.";
			MessageBox( NULL , o.str().c_str() , "提示" , MB_OK );
			return NULL;
		}

		FileHandleVgi* ret = new FileHandleVgi( nextfilename );

		bool openok = ret->open();

		if ( openok == false )
		{
			std::ostringstream o;
			o << "打开文件: " << nextfilename << "时失败.";
			MessageBox( NULL , o.str().c_str() , "提示" , MB_OK );

			delete ret;
			return NULL;
		}

		_nextHandle = ret;

		return ret;
	}
	//----------------------------------------------------------------
	String FileHandleVgi::getNextFilePath()
	{
		long nextfileid = _header._nextFileID;

		if ( nextfileid == 0 )
		{
			return "";
		}

		String path = StringUtility::getPathFromAbsoluteFilename( getFilePath() );
		String file = StringUtility::getFilenameWithoutExtFromAbsPath( getFilePath() );

		// 再取一次
		String fileshort = StringUtility::getFilenameWithoutExtension( file );

		std::ostringstream o;
		o << path  << fileshort << ".part" << nextfileid << ".vgi";
		String nextfilename = o.str();

		return nextfilename;
	}
	//----------------------------------------------------------------
	
}// end of namespace vgImage
