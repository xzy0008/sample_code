



#ifndef __VGTERRITORY_TERRAINRENDERER_H__
#define __VGTERRITORY_TERRAINRENDERER_H__


#include <vgTerritory/vgtDefinition.h>
#include <vgKernel/vgkForward.h>
#include <vgTerritory/vgVgtrFile.h>
#include <vgTerritory/vgTerrainGpuProgram.h>
#include <vgTerritory/vgMeshLayerTop.h>
#include <vgTerritory/vgMeshLayerNormal.h>
#include <vgTerritory/vgTerrainLevelling.h>

namespace vgTerritory {

	class TerrainManager;

	/**
		@date 	2008/04/03  19:06	
		@author  leven
	
		@brief 	
	
		@see    
	*/
	class  VGT_EXPORT TerrainRenderer
	{
		friend class TerrainManager;
	public:
		TerrainRenderer( TerrainGpuProgram* gpuprogram );
		~TerrainRenderer();
	
		bool init();

		void render();

		void destroy();
	

		
	
		MeshLayerTopPtr _meshTopLayer;
		MeshLayerNormPtrVector _meshNormLayers;

		
		//MeshTexCenterPtrVecPtr _meshCentersPtr;


		//GLuint getHeightMapid() const
		//{
		//	return _heightmapid_tmp;
		//}

		/**
			得到vtr文件的layer
		*/
		int getVtrLayerNum() const
		{
			return (int)( log( (float)_wholeN / _num )/ log(2.0f) );
		}

	private:
	
		TerrainGpuProgram* _terrainGpuProgram;


		//static GLuint generateHeightMap( const vgTerritory::VgtrFilePtr pvgtr );

		//GLuint _heightmapid_tmp;

		//float _scaleY;
		//float _heightMapWholeSize;

		//bool g_bWireFrameMode;

		float* _pCurrentPosY;
		float _heightStepStride;

		// Y轴的最大scale,换言之是最高的高度.
		float _maxScaleY;

		//----------------------------------------------------------------
		float _clipPlaneParamFloat0[4];		// x轴负方向裁剪
		float _clipPlaneParamFloat1[4];		// z轴负方向裁剪
		float _clipPlaneParamFloat2[4];		// x轴正方向裁剪
		float _clipPlaneParamFloat3[4];		// z轴正方向裁剪

		int _N;
		int _num;
		int _wholeN;
		double _worldx;
		double _worldy;
		double _worldz;
		float _cellsize;
		int _numOfLayers;

		bool _initialisedOK;
	};
	
	typedef vgKernel::SharePtr<TerrainRenderer> TerrainRendererPtr;
	
	
	
}// end of namespace vgTerritory

#endif // end of __VGTERRITORY_TERRAINRENDERER_H__