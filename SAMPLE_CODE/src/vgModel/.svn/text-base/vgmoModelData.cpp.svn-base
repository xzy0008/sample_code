


#include <vgStableHeaders.h>
#include <vgModel/vgmoModelData.h>
#include <vgModel/vgmoModelRenderWayVbo.h>
#include <vgModel/vgmoModelRenderWayDisplayList.h>



namespace vgModel {
	
	
	
	//----------------------------------------------------------------
	ModelData::ModelData()
	{
		setDefault();
	}
	//----------------------------------------------------------------
	ModelData::~ModelData()
	{
		destroy();
	}
	//----------------------------------------------------------------
	void ModelData::destroy()
	{
		if ( _renderWay != NULL )
		{
			_renderWay->doReferenceDelete();
			_renderWay = NULL;
		}

		setDefault();
	}
	//----------------------------------------------------------------
	void ModelData::setDefault()
	{
		_renderWay = NULL;
	}
	//----------------------------------------------------------------
	void ModelData::render(int lod , int force_render_in_num_layers,
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
	void ModelData::convertToVboRenderWay()
	{
		assert( _renderWay != NULL );

		ModelRenderWayVertexArray* vertexarray = 
			dynamic_cast<ModelRenderWayVertexArray*>(_renderWay);

		if ( vertexarray == NULL )
		{
			return;
		}

		ModelRenderWay* tmp = 
			new ModelRenderWayVbo( vertexarray );

		bool init_res = tmp->initialiseInMainThread();
		assert( init_res == true );

		// 使用引用计数删除
		_renderWay->doReferenceDelete();

		// 注意要增加计数
		tmp->addRef();
		_renderWay = tmp;
	}
	//----------------------------------------------------------------

	//void ModelData::convertToDisplayListRenderWay()
	//{
	//	assert( _renderWay != NULL );

	//	ModelRenderWayVertexArray* vertexarray = 
	//		dynamic_cast<ModelRenderWayVertexArray*>(_renderWay);

	//	if ( vertexarray == NULL )
	//	{
	//		return;
	//	}

	//	if (vertexarray->GetLayerofTexture() == 1)
	//	{
	//		ModelRenderWay *tmp = 
	//			new ModelRenderWayDisplayList( vertexarray);

	//		bool init_res = tmp->initialiseInMainThread();
	//		assert( init_res == true );

	//		_renderWay = tmp;
	//	}

	//}

	//----------------------------------------------------------------
	bool ModelData::initInMainThread()
	{
		assert( _renderWay != NULL );

		return _renderWay->initialiseInMainThread();
	}
	//----------------------------------------------------------------
	bool ModelData::initialise( char* buf , long bufsize )
	{
		ModelRenderWayVertexArray* vertexrender = 
			new ModelRenderWayVertexArray( buf , bufsize );

		
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
}// end of namespace vgModel
