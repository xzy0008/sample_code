




#include <vgStableHeaders.h>
#include <vgImage/vgiImageManager.h>
#include <vgImage/vgiImageManager.h>
#include <vgImage/XBrowseForFolder.h>
#include <vgAsyn/vgaIoServer.h>

namespace vgImage {
	
	
	//------------------------------------------------------
	bool ImageManager::addFileHandle( FileHandleVgi* filehandle )
	{
		FileHandleMapInsertResult result = 
			_filehandles.insert( std::make_pair( filehandle->getFilePath() , 
			filehandle ) );

		return result.second;
	}
	//----------------------------------------------------------------
	FileHandleVgi* ImageManager::addImageAndAssociateWithIoServer(
		const String& filepathname )
	{
		//------------------------------------------
		// 首先查找
		//------------------------------------------
		FileHandleVgiMap::iterator find_res = _filehandles.find( filepathname );

		if ( find_res != _filehandles.end() )
		{
			assert( find_res->second != NULL );
			return find_res->second;
		}

		//------------------------------------------
		// 如果没有,插入
		//------------------------------------------
		FileHandleVgi *handle = new FileHandleVgi( filepathname );

		bool open_ret = handle->open();

		if ( open_ret == false )
		{
			delete handle;
			return NULL;
		}

		return addImageAndAssociateWithIoServer( handle );
	}
	//----------------------------------------------------------------
	FileHandleVgi* ImageManager::addImageAndAssociateWithIoServer( FileHandleVgi* handle )
	{
		//------------------------------------------
		// 首先查找
		//------------------------------------------
		FileHandleVgiMap::iterator find_res = _filehandles.find( handle->getFilePath() );

		if ( find_res != _filehandles.end() )
		{
			assert( find_res->second != NULL );
			return NULL;
		}

		bool add_ret = addFileHandle( handle );

		bool associate_ret = 
			vgAsyn::IoServer::getSingleton().associateWithFileHandle( handle );

		assert( associate_ret == true );

		return handle;
	}
	//----------------------------------------------------------------
	//FileInfo* ImageManager::getFileInfo( const String& shortname )
	//{
	//	FileInfo* ret = NULL;

	//	FileHandleVgiMap::iterator iter = _filehandles.begin();
	//	FileHandleVgiMap::iterator iter_end = _filehandles.end();

	//	for ( ; iter != iter_end ; ++iter )
	//	{
	//		ret = iter->second->getMetaFileInfo( shortname );
	//		if ( ret != NULL )
	//		{
	//			break;
	//		}
	//	}

	//	return ret;
	//}
	//----------------------------------------------------------------
	//FileHandle* ImageManager::getFileHandleWrapper( const String& filehandle_shortname )
	//{
	//	String tmp;
	//	String substr;
	//	FileHandle* ret = NULL;

	//	FileHandleVgiMap::iterator iter = _filehandles.begin();
	//	FileHandleVgiMap::iterator iter_end = _filehandles.end();

	//	for ( ; iter != iter_end ; ++iter )
	//	{
	//		tmp = iter->first;

	//		substr = tmp.substr( tmp.find_last_of("\\/") + 1 , String::npos );

	//		if ( substr == filehandle_shortname )
	//		{
	//			ret = iter->second;
	//			break;
	//		}
	//	}

	//	return ret;
	//}
	//----------------------------------------------------------------
	void ImageManager::extractVgiToMultipleFiles()
	{
		//------------------------------------------
		// 1.首先选择vgimg文件
		//------------------------------------------
		String vgimgfilepath;
		{
			CString DefExt;

			DefExt.Format("%s","vgi文件(*.vgi)|*.vgi|");

			CFileDialog dlgvgimg(true,"vgi",
				NULL,OFN_HIDEREADONLY|OFN_CREATEPROMPT|OFN_NONETWORKBUTTON,DefExt);

			dlgvgimg.m_ofn.lpstrTitle = "选择vgi文件";

			if( dlgvgimg.DoModal() == IDOK )
			{
				vgimgfilepath = dlgvgimg.GetPathName();
			}

			if ( vgimgfilepath.empty() == true )
			{
				return;
			}
		}

		//------------------------------------------
		// 2.选择保存文件对话框
		//------------------------------------------
		char buf[1024];
		BOOL ret = XBrowseForFolder( NULL , NULL , -1 , "选择解压文件路径" , 
			buf , 1024 , true );

		if ( ret == FALSE )
		{
			return;
		}

		String save_multiple_files_path( buf );

		return extractVgiToMultipleFiles( vgimgfilepath , save_multiple_files_path );
	}
	//----------------------------------------------------------------
	void ImageManager::extractVgiToMultipleFiles( const String& vgimg_path,
		const String& save_multiple_files_path )
	{
		FileHandleVgi* filehandle = addImageAndAssociateWithIoServer( vgimg_path );
		if( filehandle == NULL )
		{
			std::ostringstream o;
			o << "打开" << vgimg_path << "时出错";
			MessageBox( NULL , o.str().c_str() , "Error" , MB_OK );
			return;
		}

		bool save_ret = filehandle->extractToMultipleFiles( save_multiple_files_path );
		if( save_ret == false)
		{
			std::ostringstream o;
			o << "保存到" << save_multiple_files_path << "时出错";
			MessageBox( NULL , o.str().c_str() , "Error" , MB_OK );
			return;
		}

		return;
	}
	//----------------------------------------------------------------
	ImageMiniature* ImageManager::getImageMiniature( 
		const String& metafilename )
	{
		FileHandleVgi* ret = NULL;

		FileHandleVgiMap::iterator iter = _filehandles.begin();
		FileHandleVgiMap::iterator iter_end = _filehandles.end();

		for ( ; iter != iter_end ; ++iter )
		{
			ImageMiniature* getmini = 
				iter->second->getImageMiniature( metafilename );

			if ( getmini != NULL )
			{
				return getmini;
			}
		}

		return NULL;
	}
	//----------------------------------------------------------------
	bool ImageManager::shutdown()
	{

		clearAllFileHandles();

		return true;
	}
	//----------------------------------------------------------------
	bool ImageManager::exist( const String& metafilename )
	{
		FileHandleVgiMap::iterator iter = _filehandles.begin();
		FileHandleVgiMap::iterator iter_end = _filehandles.end();

		for ( ; iter != iter_end ; ++iter )
		{
			if ( iter->second->exist( metafilename ) )
			{
				return true;
			}
		}

		return false;
	}
	//----------------------------------------------------------------
	FileHandleVgi* ImageManager::getFileHandleVgi( const String& vgipath )
	{
		FileHandleVgiMap::iterator findres = 
			_filehandles.find( vgipath );

		if ( findres == _filehandles.end() )
		{
			return NULL;
		}

		return findres->second;
	}
	//----------------------------------------------------------------
	void ImageManager::clearAllFileHandles()
	{
		FileHandleVgiMap::iterator iter = _filehandles.begin();
		FileHandleVgiMap::iterator iter_end = _filehandles.end();

		for ( ; iter != iter_end ; ++iter )
		{
			FileHandleVgi* curhandle = iter->second;
			delete curhandle;
		}
		_filehandles.clear();
	}
	//----------------------------------------------------------------

	
}// end of namespace vgImage
