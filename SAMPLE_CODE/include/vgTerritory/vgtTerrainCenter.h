


#ifndef __VGTERRITORY_TTERRAINCENTER_H__
#define __VGTERRITORY_TTERRAINCENTER_H__


#include <vgTerritory/vgtDefinition.h>
#include <vgKernel/vgkForward.h>
#include <vgTerritory/vgtElevationItem.h>
#include <vgTerritory/vgtFileHandleVtr.h>
#include <vgTerritory/vgtElevationManager.h>

	
namespace vgTerritory {


	#define VGT_USE16X16		0




	/**
		@date 	2008/09/08  10:53	
		@author  leven
	
		@brief 	来负责每一层的center,包括纹理和高度数据
	
		@see    
	*/
	class  VGT_EXPORT TerrainCenter
	{
	public:

		/**
			layer == 0时,表示这是最精细的一级.
		*/
		TerrainCenter( FileHandleVtr* vtrfile , const int& layer ,
			bool islastlayer );
		~TerrainCenter();

	public:

		float getLogicCenterX();

		float getLogicCenterZ();

		/**
			分别是四个block区块的当前指向 
			使用下面的定义:
			const int VGT_LEFT_UP	 = 0;
			const int VGT_LEFT_DOWN = 1;
			const int VGT_RIGHT_UP = 2;
			const int VGT_RIGHT_DOWN = 3;
		*/
		union
		{
			struct
			{ 
				ElevationItem* _pTexBlockLeftUp;
				ElevationItem* _pTexBlockLeftDown;
				ElevationItem* _pTexBlockRightUp;
				ElevationItem* _pTexBlockRightDown;
			};

			ElevationItem* _curElevItem[ 4 ];
		};

#if VGT_USE16X16
		ElevationItem* _cornerItem[ 4 ];
		ElevationItem* _prevCornerItem[ 4 ];
		ElevationItem* _upItem[ 8 ];
		ElevationItem* _prevUpItem[ 8 ];
#endif

		/**
			通过传入的当前的位置来更新区块.
		*/
		void update( const float& curpos_x,
			const float& curpos_z );

		bool isLoadedFully();
	

		/**
			重新载入.
		*/
		bool reload();

	private:

		void updateImpl( const int& xblockpos , const int& zblockpos );

	private:

		bool _isLastLayer;

		ElevationManager* _elevMgr;


		ElevationItem* _prevElevItem[4];

		/**
			每一层的对应宽度.计算出来的,为常量
			因为是正方形,所以长宽是一样的
			如第一层,N=8,cellsize= 2.0f,则为256*2.0f = 512.0f;
		*/
		float _blockWidth;

		/**
			 当前的位置,当为-1时是需要更新的状态.
			 正常条件下应该都是正值.
		*/
		int _curBlockPosX;
		int _curBlockPosZ;

		float _absCenterX;
		float _absCenterZ;

		String _prefix;

		FileHandleVtr* _vtrFilehandle;

		int		_curLayer;
	};
	

	typedef std::vector<TerrainCenter*> TerrainCenterPtrVec;
	
}// end of namespace vgTerritory
	


#endif // end of __VGTERRITORY_TTERRAINCENTER_H__