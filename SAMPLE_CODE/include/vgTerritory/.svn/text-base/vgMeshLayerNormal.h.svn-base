


#ifndef __VGTERRITORY_MESHLAYERNORMAL_H__
#define __VGTERRITORY_MESHLAYERNORMAL_H__


#include <vgTerritory/vgtDefinition.h>
#include <vgKernel/vgkForward.h>
#include <vgTerritory/vgTerrainGpuProgram.h>
#include <vgTerritory/vgMeshChunkTop.h>
#include <vgTerritory/vgtTerrainCenter.h>
#include <vgTerritory/vgMeshChunkLeftUp.h>
#include <vgTerritory/vgMeshChunkUp.h>
#include <vgTerritory/vgMeshChunkSlit.h>


namespace vgTerritory {

	/**
		@date 	2008/04/23  10:34	
		@author  leven
	
		@brief 	
	
		@see    
	*/
	class MeshLayerNormal
	{
	public:
		//------------------------------------------
		// which_layer 从0开始
		//------------------------------------------
		MeshLayerNormal( 
			TerrainGpuProgram* pgpugram ,
			const float cellsize , 
			const int N , const int which_layer , 
			const MeshChunkLeftUpDataPtr meshnormleftup_data,
			const MeshChunkUpDataPtr meshupdata,
			const MeshChunkSlitDataPtr meshslitdata,
			const MeshChunkTopDataPtr meshtopdata );

		~MeshLayerNormal();




		// render_normally == true -- > 正常渲染
		// render_normally == false --> 渲染top模式
		void render( const bool& render_normally );


		TerrainCenter* getTerrainCenter()
		{
			return _terrainCenter;
		}

	private:


		TerrainCenter* _terrainCenter;



		float _cellSize;

		int _whichLayer;
		int _N;



		vgCam::ViewFrustum* _viewFrustum;



		// 计算出来数据
		float _stepSize;
		int _cellNumInWidth;		// 宽度上cell的个数

		float _normalLayerOffset;
		float _normalLayerScale;


		//GLuint	_currentHeightMapID;
		//float	_heightMapScale;

		float _curPosX;
		float _curPosZ;
		int _transXInt;
		int _transZInt;
		float _transX;
		float _transZ;

		int _stepRenderFlagX;
		int _stepRenderFlagZ;


		TerrainGpuProgram* _gpuProgramPtr;

		//MeshChunkLeftUpPtr __meshNormLeftUpPtr;

		//------------------------------------------
		// _meshsLeftUp[0] : leftup
		// _meshsLeftUp[1] : leftdown
		// _meshsLeftUp[2] : rightup
		// _meshsLeftUp[3] : rightdown
		//------------------------------------------

		MeshChunkTop *_pMeshesTop[4];

		MeshChunkLeftUp *_pMeshesLeftUp[4];

		MeshChunkUp	*_pMeshesUp[8];

		MeshChunkSlit* _pMeshSlit;

	};

	typedef vgKernel::SharePtr<MeshLayerNormal> MeshLayerNormPtr;

	typedef std::vector< MeshLayerNormPtr > MeshLayerNormPtrVector;
	
	
	
}// end of namespace vgTerritory

#endif // end of __VGTERRITORY_MESHLAYERNORMAL_H__