


#ifndef __VGTERRITORY_MESHLAYERTOP_H__
#define __VGTERRITORY_MESHLAYERTOP_H__


#include <vgTerritory/vgtDefinition.h>
#include <vgKernel/vgkForward.h>
#include <vgTerritory/vgTerrainGpuProgram.h>
#include <vgTerritory/vgMeshChunkTop.h>
#include <vgTerritory/vgtTerrainCenter.h>


namespace vgTerritory {

	/**
		@date 	2008/04/23  10:04	
		@author  leven
	
		@brief 	
	
		@see    
	*/
	class MeshLayerTop
	{
	public:
		MeshLayerTop(  
			const float cellsize , 
			const int N , const MeshChunkTopDataPtr meshtopdata );

		~MeshLayerTop();

		void render();

		TerrainCenter* getTerrainCenter()
		{
			return _terrainCenter;
		}

	private:

		//MeshTextureCenterPtr _texCenter;
		TerrainCenter* _terrainCenter;

		float _cellSize;
		int _N;





		// 计算出来数据
		float _stepSize;
		float _topLayerOffset;

		//GLuint	_currentHeightMapID;
		//float	_heightMapScale;

		float _curPosX;

		float _curPosZ;
		int _transXInt;
		int _transZInt;
		float _transX;
		float _transZ;

		//------------------------------------------
		// _meshChunks[0] : leftup
		// _meshChunks[1] : leftdown
		// _meshChunks[2] : rightup
		// _meshChunks[3] : rightdown
		//------------------------------------------
		MeshChunkTop* _pMeshChunks[4];

	};

	typedef vgKernel::SharePtr<MeshLayerTop> MeshLayerTopPtr;


	
	
	
}// end of namespace vgTerritory

#endif // end of __VGTERRITORY_MESHLAYERTOP_H__