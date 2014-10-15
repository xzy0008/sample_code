

#ifndef __VGTERRITORY_TERRAINHUGEIMAGERENDER_H__
#define __VGTERRITORY_TERRAINHUGEIMAGERENDER_H__


#if 0


#include <vgKernel/vgkForward.h>
#include <vgKernel/vgkSharePtr.h>
#include <vgTerritory/vgTerrainHugeImageUtil.h>


namespace vgTerritory {

	/**
		@date 	2007/04/07  15:37	
		@author  Leven
	
		@brief 	
	
		@see    
	*/
	class HugeImageRender
	{
	public:
		HugeImageRender()
		{
			this->initDefaultParameters();
		}
		~HugeImageRender()
		{
			this->clear();
		}


		bool inputParameters( const HugeImageBlockInfoVectorPtr &pimagevec )
		{
			this->m_pHugeImageInfoVec = pimagevec;
			this->mInitialised = true;
			return true;
		}

		inline const bool isValid() const
		{
			return this->mInitialised;
		}

		inline void clear()
		{
			/// 显式的清理
			this->m_pHugeImageInfoVec.setNull();
		}

		bool initScene();

		//void renderScene();

	private:
	public:

		void renderPointsInFrustum();

		inline void initDefaultParameters()
		{
			m_pHugeImageInfoVec.setNull();
			this->mInitialised = false;
		}

		//inline void drawQuad( const )


		HugeImageBlockInfoVectorPtr m_pHugeImageInfoVec;

		bool mInitialised;


		//////////////////////////////////////////////////////////////////////////

		vgKernel::Vec3  mCameraPos;
		vgKernel::Vec3  mCameraLook;
		vgKernel::Vec3  mCameraUp;

		//Frustum  mFrustum;

		void updateFrustum();

	};

	typedef vgKernel::SharePtr<HugeImageRender>  HugeImageRenderPtr;

	
	
}// end of namespace vgTerritory


#endif


#endif // end of __VGTERRITORY_TERRAINHUGEIMAGERENDER_H__