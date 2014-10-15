


#include <vgStableHeaders.h>
#include <vgTerritory/vgMeshLayerTop.h>
#include <vgMesh/vgmMeshManager.h>
#include <vgCam/vgcaCamManager.h>
#include <vgTerritory/vgtTerrainCenterManager.h>
#include <vgTerritory/vgtTerrainManager.h>


namespace vgTerritory {
	
	



	//----------------------------------------------------------------
	MeshLayerTop::MeshLayerTop(  
		const float cellsize , 
		const int N , const MeshChunkTopDataPtr meshtopdata)
	{
		//得到最精细的一级
		_terrainCenter =
			TerrainCenterManager::getSingleton().getSuitableCenter( 0 );

		assert( _terrainCenter != NULL );

		_cellSize = cellsize;
		_N = N;



		_topLayerOffset = _cellSize * pow( 2.0f , _N )/ 4;


		//_currentHeightMapID = height_map_id;
		//assert( _currentHeightMapID != 0);





		_stepSize = _cellSize * 2.0f;

		_transXInt = 0;
		_transZInt = 0;



		const float& offset = _topLayerOffset;

		float t_offsets[8] = {
			offset * (-1.0f) , offset * (-1.0f) ,
			offset * (-1.0f) , offset * (1.0f) ,
			offset * (1.0f) , offset * (-1.0f) ,
			offset * (1.0f) , offset * (1.0f) 
		};

		int s_rotate[4] = { 0, 90 , 270 , 180 };

		for ( int i = 0 ; i < 4 ; ++i )
		{
			_pMeshChunks[i] = NULL;
		}

		for ( int i = 0 ; i < 4 ; ++i )
		{
			_pMeshChunks[i] = new MeshChunkTop(
				meshtopdata , _stepSize ,
				t_offsets[ 2 * i ] , t_offsets[ 2 * i + 1 ] ,
				offset , s_rotate[i] , _terrainCenter ,
				&_transX ,
				&vgCam::CamManager::getSingleton().getCurrentPositionPtr()->y,
				&_transZ ); 
		}
	}
	//----------------------------------------------------------------
	MeshLayerTop::~MeshLayerTop()
	{
		for ( int i = 0 ; i < 4 ; ++i )
		{
			if ( _pMeshChunks[i] != NULL )
			{
				delete _pMeshChunks[i];
				_pMeshChunks[i] = NULL;
			}
		}
	}
	//----------------------------------------------------------------
	void MeshLayerTop::render()
	{

		vgKernel::Vec3 cupos = vgCam::CamManager::getSingleton().getCurrentPosition();

		_curPosX =  cupos.x;
		_curPosZ =  cupos.z;

		_transXInt = floor(_curPosX / _stepSize);
		_transZInt = floor(_curPosZ / _stepSize);

		_transX = _transXInt * _stepSize;
		_transZ = _transZInt * _stepSize;


		glPushMatrix();
		glTranslatef( _transX , 0 , _transZ );

		for ( int i = 0 ; i < 4 ; ++i )
		{
			_pMeshChunks[i]->render( _transXInt , _transZInt );
		}

		glPopMatrix();

		return;
	}
	//----------------------------------------------------------------

	
}// end of namespace vgTerritory
