


#ifndef __VGTSIMPLETREE_H__
#define __VGTSIMPLETREE_H__

#include <vgTree/vgtrDefinition.h>
#include <vgKernel/vgkForward.h>

#include <vgKernel/vgkRendererManager.h>

#include <vgTree/vgtAbstractTree.h>
#include <vgCam/vgcaCamManager.h>

namespace vgTree {

	using namespace vgKernel;
	/**
		@date 	2008/08/05  21:22	
		@author  leven
	
		@brief 	
	
		@see    
	*/
	class  VGTR_EXPORT SimpleTree : public AbstractTree
	{
	public:
		SimpleTree();
		virtual ~SimpleTree()
		{
			
		}
	
	
	public:


		virtual void setDistanceCull( float distance_cull ) 
		{
			if ( distance_cull <= 0.0f )
			{
				_distanceCullSquare = -1.0f;
			}
			else
			{
				_distanceCullSquare = distance_cull * distance_cull;
			}
		}

		virtual float getDistanceCull() 
		{
			return _distanceCullSquare <= 0.0f ? _distanceCullSquare :
				sqrt( _distanceCullSquare );
		}


		virtual void setRendererPackage( vgKernel::RendererPackage* package )
		{
			_allRenderers = package;
		}

		virtual void invalidate()
		{
			return;
		}    

		virtual void getVisibleSet( vgKernel::RendererPackage* visible_set );

		virtual void renderTreeStruct(bool bDrawStruct = false)
		{

			//vector<vgKernel::Box>::iterator iter	= m_vLeafBox.begin();
			//vector<vgKernel::Box>::iterator iterEnd	= m_vLeafBox.end();
			//for (; iter!= iterEnd; iter++)
			//{
			//	iter->render();
			//}

			//vgKernel::RendererManager::getSingleton().getBoundingBoxAll().render();
			return;
		}

		virtual void switchTreeStruct( )
		{
			return;
		}

		virtual bool isUseTree()
		{
			return	false;
		}

		TREE_TYPE	getType()	{	return TREE_LINEAR; }

	private:

		// 优先级高的在先的算法
		struct GreaterPriorRendererAlgorithm
		{
			inline bool operator()( Renderer*& rpStart, Renderer*& rpEnd )
			{
				return rpStart->getRenderingPriority() > rpEnd->getRenderingPriority();
			}
		};

	private:

		RendererPackage* _allRenderers;
		//RendererDeque* _leaves;
		vgCam::ViewFrustum* _frustum;

		//vector<vgKernel::Box>	m_vLeafBox;

		typedef RendererQueue BufferRenderers;

		GreaterPriorRendererAlgorithm _greatorPriorAlgo;

		BufferRenderers _bufPosPriorRenderers;
		BufferRenderers _bufNegPriorRenderers;

		vgCam::CamManager* _camMgr;

		float _distanceCullSquare;
	};
	
	
}// end of namespace vgTree
	


#endif // end of __VGTSIMPLETREE_H__