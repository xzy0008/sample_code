


#include <vgStableHeaders.h>
#include <vgMesh/vgmMeshManager.h>
#include <vgMesh/vgmFileHandleVgm.h>
#include <vgAsyn/vgaIoServer.h>
//#include <vgMesh/vgmIoRequestMeshData.h>
#include <vgMesh/vgmFileWriterVgm.h>
#include <vgKernel/vgkLogManager.h>
//#include <vgImage/vgiFileWriterVgi.h>
#include <vgKernel/vgkRendererManager.h>

//#include <vgOcc/vgoOcclusion.h>
#include <vgConf/vgcoProjectConfig.h>
#include <vgConf/vgcoProjectConfigRegProxy.h>
#include <vgMesh/vgmMeshRenderCommand.h>
#include <vgKernel/vgkRenderCommandManager.h>
#include <vgKernel/vgkSelectManager.h>
#include <vgKernel/vgkSystemUtility.h>

namespace vgMesh {

	/**
		在这里创建project config
	*/
	vgConf::ProjectConfigRegProxy vgmesh_project_reg1( 
		VGM_CONF_NAME , VGM_CONF_SMALLMESHREF_ENABLE , 
		VGM_CONF_SMALLMESHREF_ENABLE_DEFAULT_STR );

	vgConf::ProjectConfigRegProxy vgmesh_project_reg2( 
		VGM_CONF_NAME , VGM_CONF_SMALLMESHREF_LOADTHRESHOLD , 
		VGM_CONF_SMALLMESHREF_LOADTHRESHOLD_DEFAULT_STR );


	MeshManager::MeshManager() 
			: Singleton<MeshManager>( VGK_SINGLETON_LEFE_MESHMANAGER ) 
	{
		_culledMeshRenderQueue = NULL;
		_prevCulledMeshRenderQueue = NULL;

		//this->registerOperatorHandle();

		m_pRenderMeshCmd = new MeshRenderCommand;
		vgKernel::RenderCommandFacade::AddCommand(m_pRenderMeshCmd);

		VGK_TRACE(_T("MeshManager created."));
	}
	

	MeshManager::~MeshManager()
	{
		vgKernel::RenderCommandFacade::RemoveCommand(m_pRenderMeshCmd);

		m_pRenderMeshCmd = NULL;
		TRACE("Destory Mesh Render Command. \n");

		if ( _prevCulledMeshRenderQueue != NULL )
		{
			delete _prevCulledMeshRenderQueue;
			_prevCulledMeshRenderQueue = NULL;
		}

		assert( _items.empty() == true && 
			"要在shutdown之前,opengl配置结束之前删除所有的mesh数据!" );

		assert( _filehandlers.empty() == true && 
			"要在shutdown之前,opengl配置结束之前删除所有的filehandle数据!" );

		VGK_TRACE(_T("MeshManager destroyed."));
	}
	//----------------------------------------------------------------
	bool MeshManager::addMeshItem( MeshItem* item )
	{
		if ( item == NULL )
		{
			return false;
		}

		MeshItemInsertRes res = 
			_items.insert( std::make_pair( item->getUniqueID() , item ) );

		return res.second;
	}
	//----------------------------------------------------------------
	bool MeshManager::addItemsAndRegisterFileHandlerVgm( FileHandleVgm* handle )
	{
		assert( handle->isOpened() == true );
		//------------------------------------------
		// 1.首先检查FileHandleVgm中是否有相同的项,如果有,
		// 停止导入;检查filehandle是否已经存在,如果有,取消导入
		//------------------------------------------
		if ( exist( handle ) == true )
		{
			MessageBox( NULL , "vgm文件重复包含." , "error" , MB_OK );
			return false;
		}

		assert( handle->getLinkedFlag() == false );

		MeshItemMap* vgmitems = 
			handle->getMeshItemsPtr();

		assert( vgmitems != NULL );

		MeshItemMap::iterator iter = vgmitems->begin();
		MeshItemMap::iterator iter_end = vgmitems->end();

		for ( ; iter != iter_end ; ++ iter )
		{
			if ( exist( iter->first ) == true )
			{
				MessageBox( NULL , "vgm中个体项重复包含." , "error" , MB_OK );
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
		registerAndAssociateFileHandleVgm( handle );

		//------------------------------------------
		// 5.最后拷贝到leaf, 并更新scenetree
		//------------------------------------------
		//copyMeshItemsToLeafDeque();
		//_sceneTree->invalidate();

		//------------------------------------------
		// 进行小物体载入
		//------------------------------------------
		{
			MeshItemMap::iterator iter = vgmitems->begin();
			MeshItemMap::iterator iter_end = vgmitems->end();

			for ( ; iter != iter_end ; ++ iter )
			{
				_smallMeshes.filterSmallMeshes( iter->second );
			}
		}
		

		return true;
	}
	//----------------------------------------------------------------
	//FileHandleVgm* MeshManager::addItemsByFileHandle( const String& absolute_file_path )
	//{
	//	FileHandleVgm* vgmhandle 
	//		= new FileHandleVgm(	 absolute_file_path );

	//	bool opened = vgmhandle->open();

	//	if( opened == false )
	//	{
	//		delete vgmhandle;
	//		return false;
	//	}

	//	bool addres = addItemsAndRegisterFileHandlerVgm( vgmhandle );

	//	if ( addres == false)
	//	{
	//		delete vgmhandle;
	//		return NULL;
	//	}

	//	return vgmhandle;
	//}
	//----------------------------------------------------------------
	bool MeshManager::exist( const UniqueID& uuid ) 
	{
		MeshItemMap::iterator iter = _items.find( uuid );

		if ( iter == _items.end() )
		{
			return false;
		}

		return true;
	}
	//----------------------------------------------------------------
	bool MeshManager::exist( vgAsyn::FileHandle* handle ) 
	{
		FileHandleVgmMap::iterator iter = 
			_filehandlers.find( handle->getFilePath() );

		if ( iter == _filehandlers.end() )
		{
			return false;
		}

		return true;
	}
	//----------------------------------------------------------------
	bool MeshManager::shutdown()
	{
		return true;
	}
	//----------------------------------------------------------------
	bool MeshManager::registerAndAssociateFileHandleVgm( FileHandleVgm* handle )
	{
		assert( handle != NULL );

		FileHandleVgmMapInsertRes insert_res = 
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
	void MeshManager::renderAllMeshItems()
	{
		static TraverseMapForRender func;

		for_each( _items.begin() , 
			_items.end() , 
			func );

		//MeshItemMap::iterator iter = _items.begin();
		//MeshItemMap::iterator iter_end = _items.end();

		//for ( ; iter != iter_end ; ++ iter )
		//{
		//	iter->second->render();
		//}

		return;
	}
	//----------------------------------------------------------------
	void MeshManager::addRefToAllMeshItems()
	{
		static TraverseMapForAddRef func;

		for_each( 
			_items.begin() , 
			_items.end() , 
			func );


#if 0
		MeshItemMap::iterator iter = _items.begin();
		MeshItemMap::iterator iter_end = _items.end();

		for ( ; iter != iter_end ; ++ iter )
		{
			MeshItem* curitem = iter->second;

			curitem->addRef();

			//IoRequestMeshData* request = 
			//	new IoRequestMeshData( curitem , curitem->getDataFileInfo() );

			//request->sendRequestAndDoAsynHandlerFunc();
		}
#endif
	}
	//----------------------------------------------------------------
	void MeshManager::dumpAllMeshItemInfo()
	{
		vgKernel::LogManager& logmgr = 
			vgKernel::LogManager::getSingleton();

		MeshItemMap::iterator iter = _items.begin();
		MeshItemMap::iterator iter_end = _items.end();

		for ( ; iter != iter_end ; ++ iter )
		{
			logmgr.logMessage( iter->second->getDetails() );
		}
	}
	//----------------------------------------------------------------
	bool MeshManager::initialise()
	{
		
		//assert( _prevCulledMeshRenderQueue == NULL );
		//assert( _culledMeshRenderQueue == NULL );
		//_prevCulledMeshRenderQueue = new RendererQueue;

		////------------------------------------------
		//// 首先向RendererManager中添加RENDERER_TYPE_MESH
		//// 然后获取CulledRenderQueue的指针.
		////------------------------------------------
		//RendererQueue* allmeshrenders = 
		//	vgKernel::RendererManager::getSingleton().getRendererQueueByType(
		//	vgMesh::RENDERER_TYPE_MESH , true );
		//assert( allmeshrenders != NULL );

		//_culledMeshRenderQueue = 
		//	vgKernel::RendererManager::getSingleton().getCulledRenderQueueByType(
		//	vgMesh::RENDERER_TYPE_MESH );

		//assert( _culledMeshRenderQueue != NULL );

		return true;
	}
	//----------------------------------------------------------------
	void MeshManager::render()
	{
		assert( _culledMeshRenderQueue != NULL );
		assert( _prevCulledMeshRenderQueue != NULL);


		//renderAllMeshItems();
		//return;

		if ( _items.empty() == true )
		{
			return;
		}

		static TraverseVecForAddRef addreffunc;
		static TraverseVecForReleaseRef releasereffunc;



		//------------------------------------------
		// 1.得到渲染队列并更新distanceToViewer
		//------------------------------------------

		//------------------------------------------
		// 2.在这里对新的渲染队列做加1操作
		//------------------------------------------
		for_each( _culledMeshRenderQueue->begin() , 
			_culledMeshRenderQueue->end() , 
			addreffunc );
		//RendererQueue::iterator iter = _culledMeshRenderQueue->begin();
		//RendererQueue::iterator iter_end = _culledMeshRenderQueue->end();

		//for ( ; iter != iter_end ; ++iter )
		//{
		//	MeshItem* item = (MeshItem*)*iter;

		//	item->addViewRef();
		//}


		//------------------------------------------
		// 3.对旧的渲染队列viewReference计数减1
		//------------------------------------------
		for_each( _prevCulledMeshRenderQueue->begin() , 
			_prevCulledMeshRenderQueue->end() , 
			releasereffunc );


		//------------------------------------------
		// 千万注意,要先执行setupRenderEnvironment
		//------------------------------------------
		static TraverseVecForRender renderfunc;

		//------------------------------------------
		// 4.最后渲染
		//------------------------------------------
//		for_each( _culledMeshRenderQueue->begin() , 
//			_culledMeshRenderQueue->end() , 
//			renderfunc );
		
		//------------------------------------------
		// 4.遮挡剔除渲染
		//------------------------------------------
		vgKernel::RendererQueue::iterator iter = _culledMeshRenderQueue->begin();
		vgKernel::RendererQueue::iterator end  = _culledMeshRenderQueue->end();

		while (iter != end)
		{
			(*iter)->render();
			iter ++;
		}

		//vgOcclusion::vgOcclusionManager::getSingleton().Render(_culledMeshRenderQueue);

		//------------------------------------------
		// 5.其他操作
		//------------------------------------------
		_prevCulledMeshRenderQueue->clear();
		_prevCulledMeshRenderQueue->assign(
			_culledMeshRenderQueue->begin() , _culledMeshRenderQueue->end() );


		//_prevCulledMeshRenderQueue->swap( _meshRenderQueue );
		//_meshRenderQueue.clear();
	}
	//----------------------------------------------------------------
	MeshItem* MeshManager::getMeshItem( const UniqueID& uuid )
	{
		MeshItemMap::iterator find_res = _items.find( uuid );
		if ( find_res == _items.end() )
		{
			return NULL;
		}

		return find_res->second;
	}
	//----------------------------------------------------------------
	vgKernel::StringVectorPtr  MeshManager::saveItemsToVgm( const String& absolute_path )
	{
		if ( _bSaveSelectNode ) // 切块保存模式
		{
			bool bOk = collectSelectItem( vgKernel::SelectManager::getSingleton().getSelectedItems() );
			if ( !bOk )
			{
				string msg = "保存vgm失败！无法收集选定的vgm模型!";
				vgKernel::SystemUtility::showModelDialog( msg );
				return StringVectorPtr();
			}

			return FileWriterVgm::writeToVgmFileFromMeshItemMap(
				&_selectItems, absolute_path );
		}
		else  // 场景保存模式
		{
			return FileWriterVgm::writeToVgmFileFromMeshItemMap(
				&_items, absolute_path );
		}
	}
	//----------------------------------------------------------------
	void MeshManager::reset()
	{
// 		unloadAllMeshItems();
// 
// 		_prevCulledMeshRenderQueue->clear();
// 
// 		_culledMeshRenderQueue->clear();


	}
	//----------------------------------------------------------------
	void MeshManager::unloadAllMeshItems()
	{
		//------------------------------------------
		// 0.开始删除小物体
		//------------------------------------------
		_smallMeshes.unRefAllSmallMeshes();

		//------------------------------------------
		// 1.删除MeshItem
		//------------------------------------------
		MeshItemMap::iterator iter = _items.begin();
		MeshItemMap::iterator iter_end = _items.end();

		for ( ; iter != iter_end ; ++iter )
		{
			delete iter->second;
		}

		_items.clear();


		//------------------------------------------
		// 2.删除FileHandleVgm
		//------------------------------------------
		{
			FileHandleVgmMap::iterator iter = _filehandlers.begin();
			FileHandleVgmMap::iterator iter_end = _filehandlers.end();

			for ( ; iter != iter_end; ++iter )
			{
				delete iter->second;
			}

			_filehandlers.clear();
		}
	}
	//----------------------------------------------------------------
	void MeshManager::clearPrevRenderQueue()
	{
		//------------------------------------------
		// 对smallMeshes持有的进行unref和addref
		//------------------------------------------
		_smallMeshes.unRefBecauseOfImage();


		static TraverseVecForReleaseRef releasereffunc;

		//------------------------------------------
		// 分别对新旧渲染队列viewReference计数减1
		//------------------------------------------
		for_each( _prevCulledMeshRenderQueue->begin() , 
			_prevCulledMeshRenderQueue->end() , 
			releasereffunc );

		//for_each( _culledMeshRenderQueue->begin() , 
		//	_culledMeshRenderQueue->end() , 
		//	releasereffunc );

		//------------------------------------------
		// 清空
		//------------------------------------------
		//_culledMeshRenderQueue->clear();
		_prevCulledMeshRenderQueue->clear();

		//------------------------------------------
		// 进行addref
		//------------------------------------------
		_smallMeshes.addRefBecauseOfImage();
	}
	//----------------------------------------------------------------
	//void MeshManager::copyMeshItemsToLeafDeque()
	//{
	//	_renderers.clear();

	//	MeshItemMap::iterator iter = _items.begin();
	//	MeshItemMap::iterator iter_end = _items.end();

	//	for ( ; iter != iter_end ; ++iter )
	//	{
	//		_renderers.push_back( (vgKernel::Renderer*)iter->second );
	//	}
	//}
	//----------------------------------------------------------------
	//void MeshManager::setupRenderEnvironment()
	//{


	//}
	//----------------------------------------------------------------
	bool MeshManager::deleteMeshItem( MeshItem* item )
	{
		//assert( item != NULL );

		if ( item == NULL )
		{
			return false;
		}

		MeshItemMap::iterator find_res = _items.find( item->getUniqueID() );
		if ( find_res == _items.end() )
		{
			// 不存在,没有删除
			//assert(0);
			return false;
		}
		
		//clearPrevRenderQueue();

		static TraverseVecForReleaseRef releasereffunc;

		//------------------------------------------
		// 分别对新旧渲染队列viewReference计数减1
		//------------------------------------------
		for_each( _prevCulledMeshRenderQueue->begin() , 
			_prevCulledMeshRenderQueue->end() , 
			releasereffunc );

		//for_each( _culledMeshRenderQueue->begin() , 
		//	_culledMeshRenderQueue->end() , 
		//	releasereffunc );

		//------------------------------------------
		// 清空
		//------------------------------------------
		//_culledMeshRenderQueue->clear();
		_prevCulledMeshRenderQueue->clear();


		_items.erase( find_res );

		while ( item->getViewRef() != 0 )
		{
			item->releaseViewRef();
		}

		delete item;

		return true;
	}
	//----------------------------------------------------------------
	bool MeshManager::onDeleteRenderer( Renderer *render)
	{
		if (render->getType() != RENDERER_TYPE_MESH)
		{
			return false;
		}

		switch (render->getType())
		{
		case RENDERER_TYPE_MESH:
			MeshItem* pMesh;
			pMesh = dynamic_cast<MeshItem*>(render);
			_smallMeshes.deleteSmallMesh( pMesh );
			deleteMeshItem(pMesh);
			break;

		default:
			break;
		}

		return true;
	}
	//----------------------------------------------------------------
	void MeshManager::readProject(const String& projpath , const String& projname)
	{
		bool smallenabled = VG_PROJCONF_GET_BOOL( VGM_CONF_NAME , 
			VGM_CONF_SMALLMESHREF_ENABLE );

		int threshold = VG_PROJCONF_GET_INT( VGM_CONF_NAME , 
			VGM_CONF_SMALLMESHREF_LOADTHRESHOLD );

		_smallMeshes.setFilterEnable( smallenabled );
		_smallMeshes.setLoadFileSizeThreshold( threshold );
	}
	//----------------------------------------------------------------
	void MeshManager::saveProject()
	{
		VG_PROJCONF_SET( VGM_CONF_NAME , 
			VGM_CONF_SMALLMESHREF_ENABLE , 
			_smallMeshes.getFilterEnable() );

		VG_PROJCONF_SET( VGM_CONF_NAME , 
			VGM_CONF_SMALLMESHREF_LOADTHRESHOLD , 
			_smallMeshes.getLoadFileSizeThreshold() );
	}

	//----------------------------------------------------------------
	void MeshManager::initAfterOpenGLSetup()
	{
		assert( _prevCulledMeshRenderQueue == NULL );
		assert( _culledMeshRenderQueue == NULL );
		_prevCulledMeshRenderQueue = new RendererQueue;

		//------------------------------------------
		// 首先向RendererManager中添加RENDERER_TYPE_MESH
		// 然后获取CulledRenderQueue的指针.
		//------------------------------------------
		RendererQueue* allmeshrenders = 
			vgKernel::RendererManager::getSingleton().getRendererQueueByType(
			vgMesh::RENDERER_TYPE_MESH , true );
		assert( allmeshrenders != NULL );

		_culledMeshRenderQueue = 
			vgKernel::RendererManager::getSingleton().getCulledRenderQueueByType(
			vgMesh::RENDERER_TYPE_MESH );

		assert( _culledMeshRenderQueue != NULL );
	}

	//----------------------------------------------------------------
	bool MeshManager::collectSelectItem( const vgKernel::RendererQueue& renderQuene )
	{
		using namespace vgKernel;
		using namespace vgMesh;

		RendererQueue::const_iterator iter = renderQuene.begin();
		RendererQueue::const_iterator iter_end = renderQuene.end();

		for ( ; iter != iter_end; iter++ )
		{
			if ( (*iter)->getType() == RENDERER_TYPE_MESH )
			{
				MeshItem* pMeshItem = dynamic_cast<MeshItem*>(*iter);
				assert( pMeshItem != NULL );

				_selectItems.insert( std::make_pair( pMeshItem->getUniqueID(), pMeshItem ) );
			}
		}

		return true;
	}

	//----------------------------------------------------------------
	void MeshManager::clearSelectItemMap()
	{
		_selectItems.clear();
	}

	//----------------------------------------------------------------


	/*bool MeshManager::onDeleteRenderer( Renderer *render)*/
	/*{
		MeshItem* pMesh;

		if (render->getType() == RENDERER_TYPE_MESH)
		{
			pMesh = dynamic_cast<MeshItem*>(render);
			
			deleteMeshItem(pMesh);

			return true;
		}
		else
		{
			return false;
		}
	}*/


	

}// end of namespace vgMesh

