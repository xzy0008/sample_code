


#include <vgStableHeaders.h>
#include <vgMesh/vgmMeshData.h>
#include <vgMesh/vgmMeshRenderWayVbo.h>
#include <vgMesh/vgmMeshRenderWayDisplayList.h>



namespace vgMesh {
	
	
	
	//----------------------------------------------------------------
	MeshData::MeshData()
	{
		setDefault();
	}
	//----------------------------------------------------------------
	MeshData::~MeshData()
	{
		destroy();
	}
	//----------------------------------------------------------------
	void MeshData::destroy()
	{
		if ( _renderWay != NULL )
		{
			_renderWay->doReferenceDelete();
			_renderWay = NULL;
		}

		setDefault();
	}
	//----------------------------------------------------------------
	void MeshData::setDefault()
	{
		_renderWay = NULL;
	}
	//----------------------------------------------------------------
	void MeshData::render(int lod , int force_render_in_num_layers,
		bool transparent_mode ,
		RgbaQuad* colorval )
	{
		if ( _renderWay == NULL )
		{
			return;
		}

		_renderWay->setTransparent( transparent_mode );
		_renderWay->render(lod , force_render_in_num_layers , colorval);
	}
	//----------------------------------------------------------------
	void MeshData::convertToVboRenderWay()
	{
		assert( _renderWay != NULL );

		MeshRenderWayVertexArray* vertexarray = 
			dynamic_cast<MeshRenderWayVertexArray*>(_renderWay);

		if ( vertexarray == NULL )
		{
			return;
		}

		MeshRenderWay* tmp = 
			new MeshRenderWayVbo( vertexarray );

		bool init_res = tmp->initialiseInMainThread();
		assert( init_res == true );

		// 使用引用计数删除
		_renderWay->doReferenceDelete();

		// 注意要增加计数
		tmp->addRef();
		_renderWay = tmp;
	}
	//----------------------------------------------------------------

	//void MeshData::convertToDisplayListRenderWay()
	//{
	//	assert( _renderWay != NULL );

	//	MeshRenderWayVertexArray* vertexarray = 
	//		dynamic_cast<MeshRenderWayVertexArray*>(_renderWay);

	//	if ( vertexarray == NULL )
	//	{
	//		return;
	//	}

	//	if (vertexarray->GetLayerofTexture() == 1)
	//	{
	//		MeshRenderWay *tmp = 
	//			new MeshRenderWayDisplayList( vertexarray);

	//		bool init_res = tmp->initialiseInMainThread();
	//		assert( init_res == true );

	//		_renderWay = tmp;
	//	}

	//}

	//----------------------------------------------------------------
	bool MeshData::initInMainThread()
	{
		assert( _renderWay != NULL );

		return _renderWay->initialiseInMainThread();
	}
	//----------------------------------------------------------------
	bool MeshData::initialise( char* buf , long bufsize )
	{
		MeshRenderWayVertexArray* vertexrender = 
			new MeshRenderWayVertexArray( buf , bufsize );

		
		bool initok = vertexrender->initialise();

		if ( initok == false )
		{
			assert(0);
			delete vertexrender;
			return false;
		}

		vertexrender->addRef();

		_renderWay = vertexrender;
		return true;
	}
	//----------------------------------------------------------------
}// end of namespace vgMesh
