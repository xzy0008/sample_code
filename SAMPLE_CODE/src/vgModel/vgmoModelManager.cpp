


#include <vgStableHeaders.h>
#include <vgModel/vgmoModelManager.h>
#include <vgModel/vgmoFileHandleVmd.h>
#include <vgAsyn/vgaIoServer.h>
//#include <vgModel/vgmoIoRequestModelData.h>
#include <vgModel/vgmoFileWriterVmd.h>
#include <vgKernel/vgkLogManager.h>
//#include <vgImage/vgiFileWriterVgi.h>
#include <vgKernel/vgkRendererManager.h>

#include <vgKernel/vgkRenderCommandManager.h>
#include <vgModel/vgmoRenderCommand.h>

//#include <vgOcc/vgoOcclusion.h>
//#include <vgConf/vgcoProjectConfig.h>
//#include <vgConf/vgcoProjectConfigRegProxy.h>



namespace vgModel {

	///**
	//	在这里创建project config
	//*/
	//vgConf::ProjectConfigRegProxy vgmesh_project_reg1( 
	//	VMD_CONF_NAME , VMD_CONF_SMALLMESHREF_ENABLE , 
	//	VMD_CONF_SMALLMESHREF_ENABLE_DEFAULT_STR );

	//vgConf::ProjectConfigRegProxy vgmesh_project_reg2( 
	//	VMD_CONF_NAME , VMD_CONF_SMALLMESHREF_LOADTHRESHOLD , 
	//	VMD_CONF_SMALLMESHREF_LOADTHRESHOLD_DEFAULT_STR );


	//----------------------------------------------------------------
	bool ModelManager::addModelItem( ModelItem* item )
	{
		if ( item == NULL )
		{
			return false;
		}

		ModelItemInsertRes res = 
			_items.insert( std::make_pair( item->getUniqueID() , item ) );

		return res.second;
	}
	//----------------------------------------------------------------
	bool ModelManager::addItemsAndRegisterFileHandlerVmd( FileHandleVmd* handle )
	{
		assert( handle->isOpened() == true );
		//------------------------------------------
		// 1.首先检查FileHandleVmd中是否有相同的项,如果有,
		// 停止导入;检查filehandle是否已经存在,如果有,取消导入
		//------------------------------------------
		if ( exist( handle ) == true )
		{
			MessageBox( NULL , "vmd文件重复包含." , "error" , MB_OK );
			return false;
		}

		assert( handle->getLinkedFlag() == false );

		ModelItemMap* vgmitems = 
			handle->getModelItemsPtr();

		assert( vgmitems != NULL );

		ModelItemMap::iterator iter = vgmitems->begin();
		ModelItemMap::iterator iter_end = vgmitems->end();

		for ( ; iter != iter_end ; ++ iter )
		{
			if ( exist( iter->first ) == true )
			{
				MessageBox( NULL , "vmd中个体项重复包含." , "error" , MB_OK );
				return false;
			}
		}

		//------------------------------------------
		// 2.插入这些项到本地
		//------------------------------------------
		_items.insert( vgmitems->begin() , vgmitems->end() );

		//------------------------------------------
		// 3.设置handle的标志位
		//------------------------------------------
		handle->setLinkedFlag( true );

		//------------------------------------------
		// 4.加入filehandle管理队列
		//------------------------------------------
		registerAndAssociateFileHandleVmd( handle );

		//------------------------------------------
		// 5.最后拷贝到leaf, 并更新scenetree
		//------------------------------------------
		//copyModelItemsToLeafDeque();
		//_sceneTree->invalidate();

		//------------------------------------------
		// 进行小物体载入
		//------------------------------------------
		//{
		//	ModelItemMap::iterator iter = vgmitems->begin();
		//	ModelItemMap::iterator iter_end = vgmitems->end();

		//	for ( ; iter != iter_end ; ++ iter )
		//	{
		//		_smallModeles.filterSmallModeles( iter->second );
		//	}
		//}
		

		return true;
	}
	//----------------------------------------------------------------
	//FileHandleVmd* ModelManager::addItemsByFileHandle( const String& absolute_file_path )
	//{
	//	FileHandleVmd* vgmhandle 
	//		= new FileHandleVmd(	 absolute_file_path );

	//	bool opened = vgmhandle->open();

	//	if( opened == false )
	//	{
	//		delete vgmhandle;
	//		return false;
	//	}

	//	bool addres = addItemsAndRegisterFileHandlerVmd( vgmhandle );

	//	if ( addres == false)
	//	{
	//		delete vgmhandle;
	//		return NULL;
	//	}

	//	return vgmhandle;
	//}
	//----------------------------------------------------------------
	bool ModelManager::exist( const UniqueID& uuid ) 
	{
		ModelItemMap::iterator iter = _items.find( uuid );

		if ( iter == _items.end() )
		{
			return false;
		}

		return true;
	}
	//----------------------------------------------------------------
	bool ModelManager::exist( vgAsyn::FileHandle* handle ) 
	{
		FileHandleVmdMap::iterator iter = 
			_filehandlers.find( handle->getFilePath() );

		if ( iter == _filehandlers.end() )
		{
			return false;
		}

		return true;
	}
	//----------------------------------------------------------------
	bool ModelManager::shutdown()
	{

		return true;
	}
	//----------------------------------------------------------------
	bool ModelManager::registerAndAssociateFileHandleVmd( FileHandleVmd* handle )
	{
		assert( handle != NULL );

		FileHandleVmdMapInsertRes insert_res = 
			_filehandlers.insert( 
			std::make_pair( handle->getFilePath() , handle ) );

		assert( insert_res.second == true );

		// 向IoServer注册
		if ( insert_res.second == true )
		{
			bool associate_ret = 
				vgAsyn::IoServer::getSingleton().associateWithFileHandle( handle );

			assert( associate_ret == true );
		}

		return insert_res.second;
	}
	//----------------------------------------------------------------
	void ModelManager::renderAllModelItems()
	{
		static TraverseMapForRender func;

		for_each( _items.begin() , 
			_items.end() , 
			func );

		//ModelItemMap::iterator iter = _items.begin();
		//ModelItemMap::iterator iter_end = _items.end();

		//for ( ; iter != iter_end ; ++ iter )
		//{
		//	iter->second->render();
		//}

		return;
	}
	//----------------------------------------------------------------
	void ModelManager::dumpAllModelItemInfo()
	{
		vgKernel::LogManager& logmgr = 
			vgKernel::LogManager::getSingleton();

		ModelItemMap::iterator iter = _items.begin();
		ModelItemMap::iterator iter_end = _items.end();

		for ( ; iter != iter_end ; ++ iter )
		{
			logmgr.logMessage( iter->second->getDetails() );
		}
	}
	//----------------------------------------------------------------
	bool ModelManager::initialise()
	{
		return true;
	}

	//----------------------------------------------------------------
	void ModelManager::render()
	{
		assert( _culledModelRenderQueue != NULL );
		//assert( _prevCulledModelRenderQueue != NULL);

		//renderAllModelItems();
		//return;

		if ( _items.empty() == true )
		{
			return;
		}

		//------------------------------------------
		// 千万注意,要先执行setupRenderEnvironment
		//------------------------------------------
		static TraverseVecForRender renderfunc;

		//------------------------------------------
		// 最后渲染
		//------------------------------------------
		vgKernel::RendererQueue::iterator iter = _culledModelRenderQueue->begin();
		vgKernel::RendererQueue::iterator end  = _culledModelRenderQueue->end();

		while (iter != end)
		{
			((ModelItem*)(*iter))->render();
			iter ++;
		}

	}
	//----------------------------------------------------------------
	ModelItem* ModelManager::getModelItem( const UniqueID& uuid )
	{
		ModelItemMap::iterator find_res = _items.find( uuid );
		if ( find_res == _items.end() )
		{
			return NULL;
		}

		return find_res->second;
	}
	//----------------------------------------------------------------
	vgKernel::StringVectorPtr  ModelManager::saveItemsToVmd( const String& absolute_path )
	{
		return FileWriterVmd::writeToVmdFileFromModelItemMap(
			&_items, absolute_path );
	}
	//----------------------------------------------------------------
	void ModelManager::unloadAllModelItems()
	{
		//------------------------------------------
		// 0.开始删除小物体
		//------------------------------------------
		//_smallModeles.unRefAllSmallModeles();

		//------------------------------------------
		// 1.删除ModelItem
		//------------------------------------------
		ModelItemMap::iterator iter = _items.begin();
		ModelItemMap::iterator iter_end = _items.end();

		for ( ; iter != iter_end ; ++iter )
		{
			delete iter->second;
		}

		_items.clear();


		//------------------------------------------
		// 2.删除FileHandleVmd
		//------------------------------------------
		{
			FileHandleVmdMap::iterator iter = _filehandlers.begin();
			FileHandleVmdMap::iterator iter_end = _filehandlers.end();

			for ( ; iter != iter_end; ++iter )
			{
				delete iter->second;
			}

			_filehandlers.clear();
		}
	}
	//----------------------------------------------------------------
	//void ModelManager::copyModelItemsToLeafDeque()
	//{
	//	_renderers.clear();

	//	ModelItemMap::iterator iter = _items.begin();
	//	ModelItemMap::iterator iter_end = _items.end();

	//	for ( ; iter != iter_end ; ++iter )
	//	{
	//		_renderers.push_back( (vgKernel::Renderer*)iter->second );
	//	}
	//}
	//----------------------------------------------------------------
	//void ModelManager::setupRenderEnvironment()
	//{


	//}
	//----------------------------------------------------------------
	bool ModelManager::deleteModelItem( ModelItem* item )
	{
		//assert( item != NULL );

		if ( item == NULL )
		{
			return false;
		}

		ModelItemMap::iterator find_res = _items.find( item->getUniqueID() );
		if ( find_res == _items.end() )
		{
			// 不存在,没有删除
			//assert(0);
			return false;
		}
		

		_items.erase( find_res );

		delete item;

		return true;
	}
	//----------------------------------------------------------------
	bool ModelManager::onDeleteRenderer( Renderer *render)
	{
		if (render->getType() != RENDERER_TYPE_MODEL)
		{
			return false;
		}

		switch (render->getType())
		{
		case RENDERER_TYPE_MODEL:
			ModelItem* pModel;
			pModel = dynamic_cast<ModelItem*>(render);
			//_smallModeles.deleteSmallModel( pModel );
			deleteModelItem(pModel);
			break;

		default:
			break;
		}

		return true;
	}
	//----------------------------------------------------------------
	void ModelManager::readProject(const String& projpath , const String& projname)
	{
		//bool smallenabled = VG_PROJCONF_GET_BOOL( VMD_CONF_NAME , 
		//	VMD_CONF_SMALLMESHREF_ENABLE );

		//int threshold = VG_PROJCONF_GET_INT( VMD_CONF_NAME , 
		//	VMD_CONF_SMALLMESHREF_LOADTHRESHOLD );

		//_smallModeles.setFilterEnable( smallenabled );
		//_smallModeles.setLoadFileSizeThreshold( threshold );
	}
	//----------------------------------------------------------------
	void ModelManager::saveProject()
	{
		//VG_PROJCONF_SET( VMD_CONF_NAME , 
		//	VMD_CONF_SMALLMESHREF_ENABLE , 
		//	_smallModeles.getFilterEnable() );

		//VG_PROJCONF_SET( VMD_CONF_NAME , 
		//	VMD_CONF_SMALLMESHREF_LOADTHRESHOLD , 
		//	_smallModeles.getLoadFileSizeThreshold() );
	}

	ModelManager::ModelManager() : Singleton<ModelManager>( VGK_SINGLETON_LEFE_MODELMANAGER )
	{
		_culledModelRenderQueue = NULL;

		//this->registerOperatorHandle();

		assert( _culledModelRenderQueue == NULL );


		//------------------------------------------
		// 首先向RendererManager中添加RENDERER_TYPE_MESH
		// 然后获取CulledRenderQueue的指针.
		//------------------------------------------
		RendererQueue* allmeshrenders = 
			vgKernel::RendererManager::getSingleton().getRendererQueueByType(
			vgModel::RENDERER_TYPE_MODEL , true );
		assert( allmeshrenders != NULL );

		_culledModelRenderQueue = 
			vgKernel::RendererManager::getSingleton().getCulledRenderQueueByType(
			vgModel::RENDERER_TYPE_MODEL );

		assert( _culledModelRenderQueue != NULL );


		m_pModelRenderCmd = new ModelRenderCommand;
		vgKernel::RenderCommandFacade::AddCommand(m_pModelRenderCmd);

		VGK_TRACE(_T("ModelManager created."));
	}

	ModelManager::~ModelManager()
	{
		vgKernel::RenderCommandFacade::RemoveCommand(m_pModelRenderCmd);
		m_pModelRenderCmd = NULL;

		TRACE("Destory Model Render Command. \n");

		assert( _items.empty() == true && 
			"要在shutdown之前,opengl配置结束之前删除所有的mesh数据!" );

		assert( _filehandlers.empty() == true && 
			"要在shutdown之前,opengl配置结束之前删除所有的filehandle数据!" );


		VGK_TRACE(_T("ModelManager destroyed."));
	}
	//----------------------------------------------------------------
	void ModelManager::invalidateItemTextures()
	{
		ModelItemMap::iterator iter = _items.begin();
		ModelItemMap::iterator iter_end = _items.end();

		for ( ; iter != iter_end ; ++ iter )
		{
			iter->second->invalidateTextures();
		}
	}
	//----------------------------------------------------------------


	/*bool ModelManager::onDeleteRenderer( Renderer *render)*/
	/*{
		ModelItem* pModel;

		if (render->getType() == RENDERER_TYPE_MODEL)
		{
			pModel = dynamic_cast<ModelItem*>(render);
			
			deleteModelItem(pModel);

			return true;
		}
		else
		{
			return false;
		}
	}*/

}// end of namespace vgModel

