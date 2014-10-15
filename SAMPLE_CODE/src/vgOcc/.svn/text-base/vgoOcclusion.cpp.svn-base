
#include <vgStableHeaders.h>
#include <vgOcc/vgoOcclusion.h>
#include <vgKernel/vgkBox.h>
#include <vgKernel/vgkVec3.h>

namespace vgOcclusion {  

	vgOcclusionManager::vgOcclusionManager() : Singleton<vgOcclusionManager>(VGK_SINGLETON_LEFE_OCCMANAGER)
	{
		mVisibilityThreshold=10;
		mFrameID=1;
		mCurrentTestIdx = 0;
		mOcclusionQueries=NULL;

		mEnable = false; 
		mOccCnt = 0;
	}

	vgOcclusionManager::~vgOcclusionManager()
	{

	}
	void vgOcclusionManager::CommanRenderer(vgKernel::RendererQueue* _culledMeshRenderQueue)
	{
		vgKernel::RendererQueue::iterator iter = _culledMeshRenderQueue->begin();
		vgKernel::RendererQueue::iterator end  = _culledMeshRenderQueue->end();

		while (iter != end)
		{
			(*iter)->render();
			iter ++;
		}
		//vgUI::UIController::getSingleton().SetNewOccCnt(0,0,0);

	}

	void vgOcclusionManager::OccRenderer(vgKernel::RendererQueue* _culledMeshRenderQueue)
	{
#if 0
		static int timeCnt = 0;
		mOccCnt=0;
		mRenderCnt=0;
		mTotalCnt=_culledMeshRenderQueue->size();

		if (mFrameID % 5 == 0)
			OccQueryPreprocess(mTotalCnt);

		vgKernel::RendererQueue::iterator iter = _culledMeshRenderQueue->begin();
		vgKernel::RendererQueue::iterator end  = _culledMeshRenderQueue->end();

		//////////////////////////////////////////////////////////////////////////
		//将所有的物体加入查询队列之始 [9/22/2008 zhu]
		while (iter != end)
		{
			vgMesh::MeshItem*abs = (vgMesh::MeshItem*)*iter;

			int	mLastRendered = abs->getOcclusionState().GetLastRendered();

			if (mFrameID%5==0)
			{
				unsigned int occlusionQuery = mOcclusionQueries[mCurrentTestIdx++];
				abs->getOcclusionState().GetOcclusionQuery()	=	occlusionQuery;
				
				glBeginQueryARB(GL_SAMPLES_PASSED_ARB, occlusionQuery);
				
				abs->render();
				mRenderCnt++;
			
				glEndQueryARB(GL_SAMPLES_PASSED_ARB);

			}
			else
			{
				if (mLastRendered==mFrameID-1||mLastRendered==mFrameID-2||mLastRendered==mFrameID-3||mLastRendered==mFrameID-4)
				{
					abs->render();
				}
			}	

			iter++;
		}

		if (mFrameID%5==0)
		{
			iter = _culledMeshRenderQueue->begin();

			while (iter != end)
			{		
					vgMesh::MeshItem*abs = (vgMesh::MeshItem*)*iter;
					iter++;					
					unsigned int result ;
					glGetQueryObjectuivARB(abs->getOcclusionState().GetOcclusionQuery(), GL_QUERY_RESULT_ARB, &result);
					unsigned int visiblePixels= result;
					//根据上面得到的像素数目跟阈值的比较结果作出相应处理
					if(visiblePixels >  mVisibilityThreshold)
					{	
						mRenderCnt++;
						abs->getOcclusionState().GetLastRendered() = mFrameID;
					}
					else
						mOccCnt ++;
				
			}

		}	
		if (mFrameID % 5==0)
		{
			//vgUI::UIController::getSingleton().SetNewOccCnt(mTotalCnt,mRenderCnt,mOccCnt);
			timeCnt = 0;
		}
		mFrameID ++;

		if(mOcclusionQueries)
		{
			glDeleteQueriesARB(_culledMeshRenderQueue->size(), mOcclusionQueries);
			delete [] mOcclusionQueries;
			mOcclusionQueries = NULL;
		}
#endif
	}

	void vgOcclusionManager::OccQueryPreprocess(int NumofNode)
	{
		if( !mOcclusionQueries && (NumofNode>0) )
		{
			mOcclusionQueries = new unsigned int[NumofNode];//rootnode是SceneTreeNodeRefPtr引用指针类型	
		}
		glGenQueriesARB(NumofNode, mOcclusionQueries);
		mCurrentTestIdx = 0;

	}
}



