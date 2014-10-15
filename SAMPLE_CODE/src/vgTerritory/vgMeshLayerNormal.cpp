


#include <vgStableHeaders.h>
#include <vgTerritory/vgMeshLayerNormal.h>
#include <vgMesh/vgmMeshManager.h>
#include <vgCam/vgcaCamManager.h>
#include <vgTerritory/vgtTerrainCenterManager.h>


namespace vgTerritory {
	
	



	//----------------------------------------------------------------
	MeshLayerNormal::MeshLayerNormal(
		TerrainGpuProgram* pgpugram ,
		const float cellsize , 
		const int N , const int which_layer , 
		const MeshChunkLeftUpDataPtr meshnormleftup_data,
		const MeshChunkUpDataPtr meshupdata,
		const MeshChunkSlitDataPtr meshslitdata,
		const MeshChunkTopDataPtr meshtopdata )
	{
		//__meshNormUpPtr = meshupptr;

		_gpuProgramPtr = pgpugram;
		assert( _gpuProgramPtr != NULL );


		_cellSize = cellsize;
		_N = N;

		//------------------------------------------
		// 注意!!!这个_whichLayer是从0开始!!!!
		//------------------------------------------
		_whichLayer = which_layer;

		_stepSize = _cellSize * pow(2.0f , _whichLayer + 2);

		//------------------------------------------
		// 查找TerrainCenter
		// 这里要加1.因为是从0开始的
		//------------------------------------------
		_terrainCenter = 
			TerrainCenterManager::getSingleton().getSuitableCenter( _whichLayer + 1 );
		assert( _terrainCenter != NULL );

		_cellNumInWidth = pow( 2.0f , _N );

		_normalLayerScale = pow( 2.0f , which_layer );

		_normalLayerOffset = 
			_cellSize * _cellNumInWidth / 4 * pow( 2.0f , which_layer );

		_pMeshSlit = new MeshChunkSlit( meshslitdata , 
			_terrainCenter , _stepSize , 
			_normalLayerScale , 
			&_transX ,
			&vgCam::CamManager::getSingleton().getCurrentPositionPtr()->y,
			&_transZ );


		//_currentHeightMapID = height_map_id;
		//assert( _currentHeightMapID != 0);


		_viewFrustum = vgCam::CamManager::getSingleton().getCurrentFrustum();


		

		_transXInt = 0;
		_transZInt = 0;


		//------------------------------------------
		// 创建leftup
		//------------------------------------------
		const float& scale = _normalLayerScale;
		const float& offset = _normalLayerOffset;

		for ( int i = 0 ; i < 4 ; ++i )
		{
			_pMeshesLeftUp[i] = NULL;
		}

		static float s_lu_rot[4] = { 0, 90 , 270 , 180 };

		float t_lu_off[8] = {
			offset * (-3.0f) , offset * (-3.0f) ,
			offset * (-3.0f) , offset * (3.0f) ,
			offset * (3.0f) , offset * (-3.0f) ,
			offset * (3.0f) , offset * (3.0f) 
		};

		for ( int i = 0 ; i < 4 ; ++i )
		{
			_pMeshesLeftUp[i] = new MeshChunkLeftUp(
				meshnormleftup_data , _stepSize , 
				t_lu_off[ 2 * i ] , t_lu_off[ 2 * i + 1 ] ,
				offset , scale , s_lu_rot[i] , _terrainCenter ,
				&_transX ,
				&vgCam::CamManager::getSingleton().getCurrentPositionPtr()->y,
				&_transZ ); 
		}

		//------------------------------------------
		// 创建up
		//------------------------------------------

		static float s_u_rot[8] = { 
			0, 90 ,
			180 , 270 ,
			0, 90 ,
			180 , 270 
		};

		float t_u_off[16] = {
			offset * (-1.0f) , offset * (-3.0f) ,
			offset * (-3.0f) , offset * (1.0f) ,
			offset * (1.0f) , offset * (3.0f) ,
			offset * (3.0f) , offset * (-1.0f) ,

			offset * (1.0f) , offset * (-3.0f) ,
			offset * (3.0f) , offset * (1.0f) ,
			offset * (-1.0f) , offset * (3.0f) ,
			offset * (-3.0f) , offset * (-1.0f) ,
		};

		for ( int i = 0 ; i < 8 ; ++i )
		{
			_pMeshesUp[i] = NULL;
		}

		for ( int i = 0 ; i < 8 ; ++i )
		{
			bool rot_along_z = false;
			if ( i > 3 )
			{
				rot_along_z = true;
			}

			_pMeshesUp[i] = new MeshChunkUp(
				meshupdata , _stepSize ,
				t_u_off[ 2 * i ] , t_u_off[ 2 * i + 1 ] ,
				offset , scale , s_u_rot[i] , rot_along_z, _terrainCenter ,
				&_transX ,
				&vgCam::CamManager::getSingleton().getCurrentPositionPtr()->y,
				&_transZ ); 
		}

		//------------------------------------------
		// 创建Top
		//------------------------------------------
		{
			const float& offset = _normalLayerOffset * 2.0f;

			float t_offsets[8] = {
				offset * (-1.0f) , offset * (-1.0f) ,
				offset * (-1.0f) , offset * (1.0f) ,
				offset * (1.0f) , offset * (-1.0f) ,
				offset * (1.0f) , offset * (1.0f) 
			};

			int s_rotate[4] = { 0, 90 , 270 , 180 };

			for ( int i = 0 ; i < 4 ; ++i )
			{
				_pMeshesTop[i] = NULL;
			}

			for ( int i = 0 ; i < 4 ; ++i )
			{
				_pMeshesTop[i] = new MeshChunkTop(
					meshtopdata , _stepSize ,
					t_offsets[ 2 * i ] , t_offsets[ 2 * i + 1 ] ,
					offset , s_rotate[i] , _terrainCenter ,
					&_transX ,
					&vgCam::CamManager::getSingleton().getCurrentPositionPtr()->y,
					&_transZ ); 
			}
		}


	}
	//----------------------------------------------------------------
	MeshLayerNormal::~MeshLayerNormal()
	{
		for ( int i = 0 ; i < 4 ; ++i )
		{
			if ( _pMeshesLeftUp[i] != NULL )
			{
				delete _pMeshesLeftUp[i];
				_pMeshesLeftUp[i] = NULL;
			}
		}

		for ( int i = 0 ; i < 8 ; ++i )
		{
			if ( _pMeshesUp[i] != NULL )
			{
				delete _pMeshesUp[i];
				_pMeshesUp[i] = NULL;
			}
		}

		if ( _pMeshSlit != NULL )
		{
			delete _pMeshSlit;
			_pMeshSlit = NULL;
		}

		for ( int i = 0 ; i < 4 ; ++i )
		{
			if ( _pMeshesTop[i] != NULL )
			{
				delete _pMeshesTop[i];
				_pMeshesTop[i] = NULL;
			}
		}

	}
	//----------------------------------------------------------------
	void MeshLayerNormal::render(  const bool& render_normally )
	{
		_curPosX = vgCam::CamManager::getSingleton().getCurrentPositionPtr()->x;
		_curPosZ =  vgCam::CamManager::getSingleton().getCurrentPositionPtr()->z;

		_transXInt = floor(_curPosX / _stepSize);
		_transZInt = floor(_curPosZ / _stepSize);

		_transX = _transXInt * _stepSize;
		_transZ = _transZInt * _stepSize;

		if ( render_normally == true )
		{
			//------------------------------------------
			// 此时正常渲染
			//------------------------------------------
			_stepRenderFlagX = floor((_curPosX - _transX) * 2.0f / _stepSize);
			_stepRenderFlagZ = floor((_curPosZ - _transZ) * 2.0f / _stepSize);

			_pMeshesLeftUp[3]->setRenderGapsFlag(
				!( _stepRenderFlagX && _stepRenderFlagZ ) );

			/*
			|----------------|----------------|
			|       |        |       |        | 
			|       |    0   |   4   |        | 
			|---------------------------------|
			|       |                |        | 
			|   7   |                |   3    | 
			|-------|                |--------|----->x
			|       |                |        | 
			|  1    |                |   5    | 
			|---------------------------------|
			|       |        |       |        | 
			|       |   6    |   2   |        | 
			|----------------|----------------|
			|		         |
			|				 |
			|				 z
			*/
			_pMeshesUp[3]->setRenderGapsFlag( !_stepRenderFlagX	);
			_pMeshesUp[5]->setRenderGapsFlag( !_stepRenderFlagX	);

			_pMeshesUp[2]->setRenderGapsFlag( !_stepRenderFlagZ	);
			_pMeshesUp[6]->setRenderGapsFlag( !_stepRenderFlagZ	);

			//_pMeshesUp[3]->setRenderGapsFlag( false	);
			//_pMeshesUp[5]->setRenderGapsFlag( false	);

			//_pMeshesUp[2]->setRenderGapsFlag( false	);
			//_pMeshesUp[6]->setRenderGapsFlag( false	);


			_pMeshSlit->setRenderUpFlag( _stepRenderFlagZ ? true : false );
			_pMeshSlit->setRenderLeftFlag( _stepRenderFlagX ? true : false);

			glPushMatrix();
			glTranslatef( _transX , 0 , _transZ );

			for ( int i = 0 ; i < 4 ; ++i )
			{
				_pMeshesLeftUp[i]->render( _transXInt , _transZInt );
			}

			for ( int i = 0 ; i < 8 ; ++i )
			{
				_pMeshesUp[i]->render( _transXInt , _transZInt );
			}


			_pMeshSlit->render(  _transXInt , _transZInt  );

			glPopMatrix();

		}
		else
		{
			//------------------------------------------
			// 此时渲染top模式
			//------------------------------------------
			glPushMatrix();
			glTranslatef( _transX , 0 , _transZ );
			glScalef( _normalLayerScale * 2.0f , 1.0f , _normalLayerScale * 2.0f );


			/******************************
			0--------2
			|
			|
			1--------3
			******************************/
			for ( int i = 0 ; i < 4 ; ++i )
			{
				_pMeshesTop[i]->render( _transXInt , _transZInt );
			}

			glPopMatrix();
		}

		return;
	}
	//----------------------------------------------------------------




	
}// end of namespace vgTerritory
