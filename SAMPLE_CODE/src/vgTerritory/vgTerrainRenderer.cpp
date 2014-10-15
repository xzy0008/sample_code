




#include <vgStableHeaders.h>
#include <vgTerritory/vgTerrainRenderer.h>
#include <vgMesh/vgmMeshManager.h>
#include <vgCam/vgcaCamManager.h>
#include <vgTerritory/vgtTerrainCenterManager.h>

#include <vgKernel/vgkOpenGLSupport.h>
#include <vgVisualEffects/vgviFogManager.h>



namespace vgTerritory {
	
	
	//----------------------------------------------------------------
	TerrainRenderer::TerrainRenderer( TerrainGpuProgram* gpuprogram )
	{
		//_heightmapid_tmp = 0;
		//g_bWireFrameMode = false;

		_pCurrentPosY = 
			&vgCam::CamManager::getSingleton().getCurrentPositionPtr()->y;

		_N = 0;
		_numOfLayers = 0;

		_initialisedOK  = false;

		_terrainGpuProgram = gpuprogram;

		_maxScaleY = 0.0f;

		assert( _terrainGpuProgram != NULL );

		
		float eqr_x1[] = {1.0f, 0.0f, 0.0f, 0.0f}; // 取x轴正方向
		float eqr_x2[] = {-1.0f, 0.0f, 0.0f, 0.0f}; // 取x轴正方向
		float eqr_z1[] = {0.0f, 0.0f, 1.0f, 0.0f}; // 取z轴正方向
		float eqr_z2[] = {0.0f, 0.0f, -1.0f, 0.0f}; // 取z轴正方向

		memcpy( _clipPlaneParamFloat0 , eqr_x1 , sizeof( float ) * 4 );
		memcpy( _clipPlaneParamFloat1 , eqr_z1 , sizeof( float ) * 4 );
		memcpy( _clipPlaneParamFloat2 , eqr_x2 , sizeof( float ) * 4 );
		memcpy( _clipPlaneParamFloat3 , eqr_z2 , sizeof( float ) * 4 );

		// x或者z轴正方向设定一个默认值.
		_clipPlaneParamFloat2[3] = 1000.0f;
		_clipPlaneParamFloat3[3] = 1000.0f;
	}
	//----------------------------------------------------------------
	TerrainRenderer::~TerrainRenderer()
	{

	}
	//----------------------------------------------------------------
	bool TerrainRenderer::init()
	{

		FileHandleVtr* vtrhandle = 
			ElevationManager::getSingleton().getMainFileHandleVtr();

		assert( _terrainGpuProgram != NULL );
		if ( _terrainGpuProgram == NULL )
		{
			return false;
		}

		assert( vtrhandle != NULL );
		if ( vtrhandle == NULL )
		{
			return false;
		}

		VtrHeaderPtr _headerPtr = vtrhandle->getHeader();

		//------------------------------------------
		// 设置ClipPlane
		//------------------------------------------
		ElevationBound bound = 
			ElevationManager::getSingleton().getValidSceneBound();

		// 注意前两个是负的
		_clipPlaneParamFloat0[3] = -bound.minPos.x;
		_clipPlaneParamFloat1[3] = -bound.minPos.y;
		_clipPlaneParamFloat2[3] = bound.maxPos.x;
		_clipPlaneParamFloat3[3] = bound.maxPos.y;

		//------------------------------------------
		// 设置选项
		//------------------------------------------
		_N = _headerPtr->N; 
		_num = pow( 2.0f , _N );
		_wholeN = _headerPtr->xTotalNum;
		_worldx =  _headerPtr->originX;
		_worldy = _headerPtr->originY;
		_worldz = _headerPtr->originZ;

		_maxScaleY = vtrhandle->getMaxScaleY();

		_cellsize = _headerPtr->cellsize;

		//_heightMapWholeSize = _wholeN * _cellsize;

		_numOfLayers =
			log( (float)_wholeN / _num )/ log(2.0f) + 1;

		_heightStepStride = _cellsize * 
			pow( 2.0f , _N ) / 2.0f;

		float meshlength = _cellsize *  _num / 2;
		float halfmeshlen = meshlength / 2.0f;

		//------------------------------------------
		// MeshTextureCenter
		//-----------------------------------------
		//_meshCentersPtr = meshcenters;
		//if( _meshCentersPtr.isNull() == true )
		//{
		//	MessageBox( NULL , "地形纹理初始化失败!" , "ERROR" , MB_OK );
		//	return false;
		//}
		//// 目前暂时支持2个层!!注意
		//assert( _meshCentersPtr->size() == 2 );

		//------------------------------------------
		// 创建MeshChunks
		//------------------------------------------
		vgTerritory::MeshChunkTopDataPtr meshtopptr( new vgTerritory::MeshChunkTopData );
		meshtopptr->createFromParameters(
			_num / 2 + 1 , _num / 2 + 1 , 
			meshlength ,meshlength,
			halfmeshlen * (-1.0f) , _worldy , halfmeshlen * (-1.0f));


		vgTerritory::MeshChunkLeftUpDataPtr meshleftupdataptr( new vgTerritory::MeshChunkLeftUpData );
		meshleftupdataptr->createFromParameters(
			_num / 4 + 1 , _num / 4 + 1 , 
			meshlength ,meshlength,
			halfmeshlen * (-3.0f) , _worldy , halfmeshlen * (-3.0f) );


		vgTerritory::MeshChunkUpDataPtr meshupdataptr( new vgTerritory::MeshChunkUpData );
		meshupdataptr->createFromParameters(
			_num / 4 + 1 , _num / 4 + 1 , 
			meshlength ,meshlength,
			halfmeshlen * (-1.0f) , _worldy , halfmeshlen * (-3.0f) );

		vgTerritory::MeshChunkSlitDataPtr meshslitptr( 
			new vgTerritory::MeshChunkSlitData( _N , _cellsize ) );

		//------------------------------------------
		// 创建layers
		//------------------------------------------
		_meshTopLayer.bind(
			new vgTerritory::MeshLayerTop(
				_cellsize , _N , meshtopptr
			));

		for ( int i = 0 ; i < _numOfLayers; ++ i )
		{
			vgTerritory::MeshLayerNormPtr pnormallayer;
			pnormallayer.bind(
				new vgTerritory::MeshLayerNormal( 
				_terrainGpuProgram , 
				_cellsize , _N , i  , 
				meshleftupdataptr , meshupdataptr ,
				meshslitptr, meshtopptr ) );

			_meshNormLayers.push_back( pnormallayer );
		}


		_initialisedOK = true;

		return true;
	}
	//----------------------------------------------------------------
	void TerrainRenderer::render()
	{
		if ( _initialisedOK == false )
		{
			return;
		}

		//------------------------------------------
		// 开启裁剪平面
		//------------------------------------------
		glEnable(GL_CLIP_PLANE1);
		glEnable(GL_CLIP_PLANE2);
		glEnable(GL_CLIP_PLANE3);
		glEnable(GL_CLIP_PLANE4);

		_terrainGpuProgram->setClipPlaneParam( 
			_clipPlaneParamFloat0,
			_clipPlaneParamFloat1,
			_clipPlaneParamFloat2,
			_clipPlaneParamFloat3 	);

		//------------------------------------------
		// 其他gpu的参数设置.
		//------------------------------------------
		static float uvparam[4] = { 0.0 , 0.5 , 0.0 , 0.00 };

		glMatrixMode( GL_MODELVIEW );
		glPushMatrix();
		GLfloat modelviewmat[16];
		glGetFloatv( GL_MODELVIEW_MATRIX, modelviewmat );
		glEnable(GL_DEPTH_TEST);
		glLoadIdentity();
		_terrainGpuProgram->setViewMatrix( modelviewmat );

		//_terrainGpuProgram->setDisplacementScaler( _scaleY );
		//_terrainGpuProgram->setHeightMapSize( _heightMapWholeSize );
		//_terrainGpuProgram->setHeightMapIdEveryFrame( _heightmapid_tmp );
		//_terrainGpuProgram->setDecalUVParamsEveryFrame( _heightmapid_tmp , uvparam );


		// 只设定一个临时的变量
		_terrainGpuProgram->setDisplacementScaler( 100.0f/*_scaleY*/ );
		_terrainGpuProgram->setHeightMapSize( 2048/*_heightMapWholeSize*/ );
		_terrainGpuProgram->setHeightMapIdEveryFrame( 0/*_heightmapid_tmp*/ );
		
		//将在ElevationItem::useBindInGpuProgram()中修改
		_terrainGpuProgram->setDecalUVParamsEveryFrame( 0/*_heightmapid_tmp*/ , uvparam );

		vgVisualEffects::FogManager& fogmgr = 
			vgVisualEffects::FogManager::getSingleton();

		if ( fogmgr.getEnabledFlag() )
		{
			_terrainGpuProgram->setFogEnableFlag( true );
			_terrainGpuProgram->setFogColor( 
				fogmgr.getFogColorValue() );

			_terrainGpuProgram->setFogStartAndEnd( fogmgr.getFogStart(),
				fogmgr.getFogEnd() );
		}
		else
		{
			_terrainGpuProgram->setFogEnableFlag( false );

			_terrainGpuProgram->setFogColor( 
				fogmgr.getFogColorValue() );

			_terrainGpuProgram->setFogStartAndEnd( 0, 1 );
		}

		_terrainGpuProgram->useBindBegin();



		//------------------------------------------
		// 计算高度优化值
		//------------------------------------------
		int norm_layer_size = _meshNormLayers.size();

		static int heightRenderFlag = 0;
		static int prev_heightFlag = 0;

		heightRenderFlag = 0;

		assert( _maxScaleY > 0.0f );

		if ( *_pCurrentPosY > _maxScaleY )
		{
			heightRenderFlag =
				log( (*_pCurrentPosY - _maxScaleY ) / _heightStepStride + 1.0f) /
				log( 2.0f );

			if ( heightRenderFlag < 0 )
			{
				heightRenderFlag = 0;
			}
			else if ( heightRenderFlag > norm_layer_size )
			{
				heightRenderFlag = norm_layer_size ;
			}
		}

		TerrainCenterManager::getSingleton().updateCentersInEveryFrame(
			heightRenderFlag );

		if ( prev_heightFlag != heightRenderFlag )
		{
			if ( heightRenderFlag != 0 && heightRenderFlag < norm_layer_size )
			{
				if ( _meshNormLayers[ heightRenderFlag - 1 ]->getTerrainCenter()->isLoadedFully() == false )
				{
					++heightRenderFlag;
				}
			}
			else
			{
				if ( _meshTopLayer->getTerrainCenter()->isLoadedFully() == false  )
				{
					++heightRenderFlag;
				}
			}
		}

		prev_heightFlag = heightRenderFlag;

		//------------------------------------------
		// 注意是由远及近绘制
		//------------------------------------------
		if ( heightRenderFlag == 0 )
		{
			for ( int i = norm_layer_size - 1 ; i != -1 ; -- i )
			{
				_meshNormLayers[i]->render( true );
			}

			_meshTopLayer->render();
		}
		else
		{
			for ( int i = norm_layer_size - 1 ; i > heightRenderFlag - 1 ; -- i )
			{	
				_meshNormLayers[i]->render( true );
			}

			_meshNormLayers[ heightRenderFlag - 1 ]->render( false );
		}
		

		_terrainGpuProgram->useBindEnd();

		glPopMatrix();

		//------------------------------------------
		// 最后关闭裁剪平面
		//------------------------------------------
		glDisable( GL_CLIP_PLANE1 );
		glDisable( GL_CLIP_PLANE2 );
		glDisable( GL_CLIP_PLANE3 );
		glDisable( GL_CLIP_PLANE4 );

		glDisable( GL_BLEND );
		return;
	}
	//----------------------------------------------------------------
	void TerrainRenderer::destroy()
	{

		VGK_CHECK_OPENGL_ERROR();

		return;
	}
	//----------------------------------------------------------------

}// end of namespace vgTerritory
