



#ifndef __VGTERRITORY_MESHTEXTURECENTER_H__
#define __VGTERRITORY_MESHTEXTURECENTER_H__

#include <vgKernel/vgkForward.h>
#include <vgTerritory/vgTerrainGpuProgram.h>
#include <vgImage/vgiTextureObserver.h>

namespace vgTerritory {

#if 0

	class ElevationItem
	{
	public:
		ElevationItem( 
			float texUScale, float texUBias, float texVScale, float texVBias ,
			String texname , const bool& isempty = false );

		~ElevationItem();

	public:

		void useBindInTerrainGpuProgram();


	public:

		/*
		各标记如下
		float[0] _texUScale;
		float[1] _texUBias;
		float[2] _texVScale;
		float[3] _texVBias;
		公式:
		y = x * scale + bias;
		(y = x * 伸缩因子 - 左边距离 * 伸缩因子)
		*/
		float _texParams[4];

		TerrainGpuProgram* _pgpuprogram;

		vgImage::TexObsPointer _texObserver;


		bool _isEmptyBlock;
	};

	/**
		@date 	2008/04/19  16:07	
		@author  leven
	
		@brief 	
	
		@see    
	*/
	class MeshTextureCenter
	{
	public:
		MeshTextureCenter( bool needupdate );

		~MeshTextureCenter();
	

	public:

		// 注意,只能为块状;另外,默认从中心点原点开始
		bool init( const String& prefix , const float& blockwidth ,
			const int& num_in_width , const float& displace_in_x , 
			const float& displace_in_z , const int& whichlayer );

		void destroy();
	
		int getLogicCenterX()
		{
			return _absoluteCenterX;
		}

		int getLogicCenterZ()
		{
			return _absoluteCenterZ;
		}

		inline void setLogicCenterX( const int& centerx )
		{
			this->_absoluteCenterX = centerx;
		}
		inline void setLogicCenterZ( const int& centerz )
		{
			this->_absoluteCenterZ = centerz;
		}

		void update();


	public:



		ElevationItem* _pTexBlockLeftUp;
		ElevationItem* _pTexBlockLeftDown;
		ElevationItem* _pTexBlockRightUp;
		ElevationItem* _pTexBlockRightDown;

	private:

		inline ElevationItem* getTexBlock( const int& x , const int& z )
		{
			if ( x < 0 || z < 0 || 
				x >= _numInWidth || z >= _numInWidth )
			{
				return _emptyTexBlock;
			}

			return _texBlocks[ x + _numInWidth * z ];
		}

		bool _isNeedUpdate;


		float* _pCurrentPosX;
		float* _pCurrentPosZ;


		int _transX;
		int _transZ;


		int _halfNum;
		String _prefix;
		float _blockWidth;
		int _numInWidth;
		float _displaceInX;
		float _displaceInZ;
		int _whichLayer;

		ElevationItem** _texBlocks;

		static ElevationItem* _emptyTexBlock;


		float _absoluteCenterX;
		float _absoluteCenterZ;
	};
	

	typedef vgKernel::SharePtr<MeshTextureCenter> MeshTextureCenterPtr;

	typedef std::vector< MeshTextureCenterPtr> MeshTexCenterPtrVec;

	typedef vgKernel::SharePtr< MeshTexCenterPtrVec> MeshTexCenterPtrVecPtr;
	
	
#endif
	
	
}// end of namespace vgTerritory

#endif // end of __VGTERRITORY_MESHTEXTURECENTER_H__