#ifndef __VGOCCLUSION_H__
#define __VGOCCLUSION_H__


#include <vgOcc/vgocDefinition.h>

#include <vgKernel/vgkRenderer.h>
#include <vgKernel/vgkSingleton.h>


namespace vgOcclusion {  

	class  VGOC_EXPORT vgOcclusionManager 
		: public vgKernel::Singleton<vgOcclusionManager>
	{
		friend class vgKernel::Singleton<vgOcclusionManager>;

	public:
		vgOcclusionManager();

		~vgOcclusionManager();

		bool initialise()
		{

			return true;
		}

		virtual bool shutdown()
		{
			return true;
		}

	public:

		virtual void reset(){};

		void Render(vgKernel::RendererQueue* _culledMeshRenderQueue);

		void EnableOcc() { mEnable = true; }

		void DisableOcc() { mEnable = false; }

		bool GetOccState(){return mEnable;}

		unsigned int GetOccCnt() { return mOccCnt; }

	private:
		void OccRenderer(vgKernel::RendererQueue* _culledMeshRenderQueue);
		void CommanRenderer(vgKernel::RendererQueue* _culledMeshRenderQueue);
		void OccQueryPreprocess(int NumofNode);

	private:

		unsigned int mFrameID;
		int mCurrentTestIdx;
		unsigned int mVisibilityThreshold;
		unsigned int *mOcclusionQueries;


		unsigned int  mTotalCnt;
		unsigned int  mRenderCnt;
		unsigned int  mOccCnt;
		bool mEnable;
	};

	inline void vgOcclusionManager::Render(vgKernel::RendererQueue* _culledMeshRenderQueue)
	{
		//if ( mEnable )
		//{
		//	OccRenderer(_culledMeshRenderQueue);
		//}
		//else
		//{
			CommanRenderer(_culledMeshRenderQueue);

		//}
	}

}

#endif