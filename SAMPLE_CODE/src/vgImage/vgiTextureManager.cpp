



#include <vgStableHeaders.h>
#include <vgImage/vgiTextureManager.h>
#include <vgImage/vgiTextureObserver.h>
#include <vgImage/vgiTextureItem.h>
#include <vgImage/vgiImageManager.h>
#include <vgImage/vgiImageUtility.h>
#include <vgKernel/vgkStringVector.h>
#include <vgImage/vgiTextureIoRequestDispatcher.h>
#include <vgConf/vgcoProjectConfig.h>
#include <vgConf/vgcoProjectConfigRegProxy.h>



namespace vgImage {
	

	/**
		在这里创建project config
	*/
	vgConf::ProjectConfigRegProxy vgImage_project_reg1( 
		VGI_CONF_NAME , VGI_CONF_SMALLIMGREF_ENABLE , 
		VGI_CONF_SMALLIMGREF_ENABLE_DEFAULT_STR );

	vgConf::ProjectConfigRegProxy vgImage_project_reg2( 
		VGI_CONF_NAME , VGI_CONF_SMALLIMGREF_LOADTHRESHOLD , 
		VGI_CONF_SMALLIMGREF_LOADTHRESHOLD_DEFAULT_STR );


	//----------------------------------------------------------------
	TextureObserver* TextureManager::getTextureObserver( const String& texname ,
		const int& lod )
	{
		if ( texname.empty() == true )
		{
			return NULL;
		}

		//------------------------------------------
		// 要检查输入的图像是否是dds文件!如果不是,返回NULL
		//------------------------------------------
		if( ImageUtility::findImageFileExtension( texname ) != "dds" )
		{
			assert(0 && "图像为非DDS格式!");
			return NULL;
		}

		//------------------------------------------
		// 从数据结构中查找Texture
		//------------------------------------------
		TextureMap::iterator find_result = _texMap.find( texname );

		// if nothing found
		if ( find_result == _texMap.end() )
		{
			return NULL;
		}

		// if found, return it.
		return find_result->second->getObserver( lod );
	}
	//----------------------------------------------------------------
	bool TextureManager::addTextureByName( const String& texname )
	{
		if ( validateTextureExtension( texname ) == false )
		{
			return false;
		}

		//------------------------------------------
		// 1.首先从数据结构中查找Texture
		//------------------------------------------
		TextureMap::iterator find_result = _texMap.find( texname );

		if ( find_result != _texMap.end() )
		{
			// 此时表示已经存在
			return false;
		}

		//------------------------------------------
		// 2.在FileHandleManager中找到ImageMiniature
		//------------------------------------------
		ImageMiniature* img =
			ImageManager::getSingleton().getImageMiniature( texname );

		if( img == NULL )
		{
			return false;
		}

		//------------------------------------------
		// 3.确认没有这一项之后,插入
		//------------------------------------------
		TextureItem* newitm = new TextureItem( texname , img );

		TextureInsertResult ret = _texMap.insert( std::make_pair( texname , 
			newitm ));

		_smallRefer.filterSmallTextures( newitm );

		return true;
	}
	//----------------------------------------------------------------
	bool TextureManager::addTexture( FileHandleVgi* vgimg )
	{
		assert( vgimg != NULL );
		vgKernel::StringVector* names = vgimg->listMetaFileNames();
		if ( names == NULL )
		{
			return false;
		}

		//------------------------------------------
		// 首先，设置同步模式
		//------------------------------------------
		vgImage::TextureIoRequestDispatcher::getSingleton().setAsynMode( false );

		//------------------------------------------
		// 然后添加纹理，这个时候经过SmallTextureReferencer
		// 进行小物体拣选
		//------------------------------------------
		vgKernel::StringVector::iterator iter = names->begin();
		vgKernel::StringVector::iterator iter_end = names->end();
		
		for ( ; iter != iter_end ;++iter )
		{
			addTextureByName( *iter );
		}

		delete names;

		//------------------------------------------
		// 返回异步模式
		//------------------------------------------
		// 提交修改,创建纹理
		vgImage::TextureIoRequestDispatcher::getSingleton().dealWithUpdateInfoEveryFrame();

		// 设置异步模式
		vgImage::TextureIoRequestDispatcher::getSingleton().setAsynMode( true );

		return true;
	}
	//----------------------------------------------------------------
	bool TextureManager::validateTextureExtension( const String& texname )
	{
		//------------------------------------------
		// 要检查输入的图像是否是dds文件!如果不是,返回NULL
		//------------------------------------------
		if ( ImageUtility::findImageFileExtension( texname) != "dds" )
		{
			assert(0 && "图像为非DDS格式!");
			return false;
		}

		return true;
	}
	//----------------------------------------------------------------
	void TextureManager::unloadAllTextureData()
	{
		// 卸载smallReferencer
		_smallRefer.unRefAllSmallTextures();

		// 删除掉整个的texture map
		TextureMap::iterator iter = _texMap.begin();
		TextureMap::iterator iter_end = _texMap.end();

		for ( ; iter != iter_end ; ++iter )
		{
			TextureItem* cur_tex_item = iter->second;
			delete cur_tex_item;
		}



		_texMap.clear();
	}
	//----------------------------------------------------------------
	vgKernel::StringVectorPtr TextureManager::getTextureNameList()
	{
		if ( _texMap.empty() == true )
		{
			return vgKernel::StringVectorPtr();
		}

		vgKernel::StringVectorPtr ret( new vgKernel::StringVector() );

		TextureMap::iterator iter = _texMap.begin();
		TextureMap::iterator iter_end = _texMap.end();

		for ( ; iter != iter_end ; ++iter )
		{
			ret->push_back( iter->first );
		}

		return ret;
	}
	//----------------------------------------------------------------
	bool TextureManager::addRefToEveryTextureBySpecificLod( const int& lod )
	{
		vgKernel::StringVectorPtr pnames = getTextureNameList();

		if ( pnames.isNull() == true )
		{
			return true;
		}

		TextureObserver* tmpobs = NULL; 

		vgKernel::StringVector::iterator iter = pnames->begin();
		vgKernel::StringVector::iterator iter_end = pnames->end();

		for ( ; iter != iter_end ; ++iter )
		{
			tmpobs = getTextureObserver( *iter , lod );
			if ( tmpobs != NULL )
			{
				tmpobs->addRef();
			}

			tmpobs = NULL;
		}

		return true;
	}
	//----------------------------------------------------------------
	bool TextureManager::shutdown()
	{
		assert( _texMap.empty() == true && "要在OpenGL结束之前清除所有的Texture!" );
		return true;
	}
	//----------------------------------------------------------------
	bool TextureManager::addRefToTexturesBySpecificLod( FileHandleVgi* vgihandle ,
		const int& lod )
	{
		vgKernel::StringVector* pnames = vgihandle->listMetaFileNames();
		assert( pnames != NULL );

		if ( pnames == NULL )
		{
			return false;
		}

		TextureObserver* tmpobs = NULL; 

		vgKernel::StringVector::iterator iter = pnames->begin();
		vgKernel::StringVector::iterator iter_end = pnames->end();

		for ( ; iter != iter_end ; ++iter )
		{
			tmpobs = getTextureObserver( *iter , lod );
			if ( tmpobs != NULL )
			{
				tmpobs->addRef();
			}

			tmpobs = NULL;
		}

		return true;
	}
	//----------------------------------------------------------------
	void TextureManager::readProject( const String& projpath , const String& projname )
	{
		bool smallenabled = VG_PROJCONF_GET_BOOL( VGI_CONF_NAME , 
			VGI_CONF_SMALLIMGREF_ENABLE );

		int threshold = VG_PROJCONF_GET_INT( VGI_CONF_NAME , 
			VGI_CONF_SMALLIMGREF_LOADTHRESHOLD );

		_smallRefer.setFilterEnable( smallenabled );
		_smallRefer.setLoadFileSizeThreshold( threshold );
	}
	//----------------------------------------------------------------
	void TextureManager::saveProject()
	{
		VG_PROJCONF_SET( VGI_CONF_NAME , 
			VGI_CONF_SMALLIMGREF_ENABLE , 
			_smallRefer.getFilterEnable() );

		VG_PROJCONF_SET( VGI_CONF_NAME , 
			VGI_CONF_SMALLIMGREF_LOADTHRESHOLD , 
			_smallRefer.getLoadFileSizeThreshold() );
	}
	//----------------------------------------------------------------



	//----------------------------------------------------------------

	
}// end of namespace vgImage
