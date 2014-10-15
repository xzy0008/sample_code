



#ifndef __VGTERRITORY_TTERRAINCENTERMANAGER_H__
#define __VGTERRITORY_TTERRAINCENTERMANAGER_H__


#include <vgTerritory/vgtDefinition.h>
#include <vgKernel/vgkForward.h>
#include <vgKernel/vgkSingleton.h>

#include <vgTerritory/vgtFileHandleVtr.h>
#include <vgImage/vgiFileHandleVgi.h>
#include <vgCam/vgcaCamManager.h>
#include <vgTerritory/vgtTerrainCenter.h>


	
namespace vgTerritory {

	/**
		@date 	2008/09/08  10:40	
		@author  leven
	
		@brief 	注意,销毁一定要在opengl销毁之前.
		其生命周期要比TerrainManager长
	

		@see    
	*/
	class  VGT_EXPORT TerrainCenterManager : 
		public vgKernel::Singleton<TerrainCenterManager>
	{
		friend class vgKernel::Singleton<TerrainCenterManager>;
	private:
		TerrainCenterManager();

		~TerrainCenterManager()
		{
			VGK_TRACE(_T("TerrainCenterManager destroyed."));
		}

	protected:
		virtual bool initialise();
		virtual bool shutdown()
		{
			assert( _centerLayers.empty() == true && 
				"uninitBeforeOpenGLDestroy没有执行" );
			return true;
		}

	public:

		virtual void reset(){};

		/**
			重新载入各个层级.
			用于刷新修改.
		*/
		bool reloadAllCenters();

		bool clearData();

		bool generateCenters( FileHandleVtr* vtrfilehandle );


		bool uninitBeforeOpenGLDestroy();
	
		/**
			在每帧中更新centers.
			需要放在TerrainManager的render中
			height_render_flag 是根据高度来更新centers.
			为0时,全部更新.
			为1时,center=0不更新,其他更新,依次类推
		*/
		void updateCentersInEveryFrame( const int& height_render_flag );

		/**
			通过当前的layer层数得到TerrainCenter
			注意,0是最清晰的一级.
			另外注意,当请求的layer大于layer的size时,返回的
			是最大级的center.
		*/
		TerrainCenter* getSuitableCenter( const int& layer );

		long getCurrentHeightLayerNumber() const
		{
			return _currentHeightLayer;
		}

		/**
			获取当前所有层所持有的items. 用于filter
		*/
		ElevationItemVector getContainedElevationItems();

		/**
			将Elevation的buffer dump到opengl显存中
		*/
		void dumpElevationBufferToHeightMap();


	private:
	
		vgCam::CamManager* _camMgr;

		TerrainCenterPtrVec _centerLayers;

		// 当前需要渲染的layer高度.
		// 当为0时,表示渲染最精细一层.
		long _currentHeightLayer;
	};
	
	
}// end of namespace vgTerritory
	


#endif // end of __VGTERRITORY_TTERRAINCENTERMANAGER_H__