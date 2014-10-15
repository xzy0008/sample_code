


#include <vgStableHeaders.h>
#include <vgMesh/vgmMeshManager.h>
#include <vgMesh/vgmIoRequestMeshData.h>
#include <vgMesh/vgmMeshData.h>
//#include <vgConfig/vgcConfigManager.h>
#include <vgKernel/vgkOpenGLSupport.h>

#include <vgMesh/vgmMeshDataPlus.h>



namespace vgMesh {
	
	
	
	
	//----------------------------------------------------------------
	bool IoRequestMeshData::anotherThreadHandler()
	{
		//Sleep(50);

		//assert( _meshData == NULL );
		//assert( _buffer != NULL );


		assert( _buffer != NULL );

		assert( _meshData == NULL );

		_meshData = 
			new MeshData();

		bool initok = _meshData->initialise(  _buffer , _fileInfo->_fileSize  );

		assert( initok == true );

		assert( _meshData != NULL );

		if ( _loadShadowData )
		{
			assert( _meshDataPlus == NULL );
			_meshDataPlus = new MeshDataPlus;
			bool loadok = _meshDataPlus->importFromMeshData( _meshData );

			assert( loadok == true );
		}
		

		dispatchMainThreadFunc();

		return true;
	}
	//----------------------------------------------------------------
	bool IoRequestMeshData::mainThreadHandler()
	{


		MeshItem* item = MeshManager::getSingleton().getMeshItem( _meshID );

		if ( item == NULL )
		{
			// 此时item已经不存在,即已经删除掉了
			// 那么扔掉本数据即可.
			//assert(0);
			delete this;
			return true;
		}

		Mesh* mesh = item->getMeshByLod( _lod );

		assert( mesh != NULL );

		const int& refcount = mesh->getReferenceCount();

		assert( refcount > -1 );

		//------------------------------------------
		// 只有计数值大于0的时候才需要重置
		// 主要考虑的情况如下:
		//  1.计数从0到1,载入了;但是马上又载出,此时
		//		计数为0,不需要重置
		//------------------------------------------
		if ( refcount != 0 && mesh->getMeshData() == NULL )
		{
			_meshData->initInMainThread();


 		//	vgConfig::ConfigObject* renderwaymode = //chunyongma
			//	vgConfig::ConfigManager::getSingleton().getObject( "renderwaymode" );

			//int m_renderwaymode;

			//if ( renderwaymode != NULL )
			//{
			//	m_renderwaymode = renderwaymode->getInt();

			//	if (m_renderwaymode == 0)
			//	{
					VGK_CHECK_OPENGL_ERROR();
					_meshData->convertToVboRenderWay();
					VGK_CHECK_OPENGL_ERROR();
			//	}
			//	else if (m_renderwaymode == 1)
			//	{
			//		_meshData->convertToDisplayListRenderWay();
			//	}
			//	else
			//		goto MESHDATASET;
			//}

//MESHDATASET:

			if ( _loadShadowData && mesh->hasMeshPlusData() == false )
			{
				assert( _meshDataPlus != NULL );
				// 注意这一步
				_meshDataPlus->setFatherMesh( mesh );
				mesh->setMeshDataAndPlus( _meshData, _meshDataPlus );
			}
			else
			{
				assert( _meshDataPlus == NULL );
				mesh->setMeshData( _meshData );
			}
			

			//------------------------------------------
			// 在这里创建vbo
			//------------------------------------------

			setDeleteBufferFlag( false );
		}

		delete this;
		return true;
	}
	//----------------------------------------------------------------
	bool IoRequestMeshData::isReallyNeedToSend()
	{
		MeshItem* item = MeshManager::getSingleton().getMeshItem( _meshID );

		if ( item == NULL )
		{
			return false;
		}

		Mesh* mesh = item->getMeshByLod( _lod );
		assert( mesh != NULL );


		const int count = mesh->getReferenceCount();

		/**
			当引用计数为0或者已经有数据时,就不需要载入了
		*/
		if ( count == 0 || mesh->getMeshData() != NULL)
		{
			return false;
		}

		return true;
	}

	IoRequestMeshData::IoRequestMeshData( UniqueID unique_id , int lod , 
		vgAsyn::FileInfo* fileinfo,bool load_shadow_data  ) : vgAsyn::IoRequest( fileinfo ) ,
		_lod( lod ),
		_meshID( unique_id ),
		_loadShadowData( load_shadow_data ),
		_meshDataPlus( NULL )
	{
		_meshData = NULL;

	}
	//----------------------------------------------------------------



}// end of namespace vgMesh
