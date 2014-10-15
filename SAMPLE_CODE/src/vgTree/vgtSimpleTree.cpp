


#include <vgStableHeaders.h>
#include <vgTree/vgtSimpleTree.h>


namespace vgTree { 
	
	
	using namespace vgKernel;

	//----------------------------------------------------------------
	SimpleTree::SimpleTree()
	{
		_distanceCullSquare = -1.0f;

		_allRenderers = NULL;

		_frustum = vgCam::CamManager::getSingleton().getCurrentFrustum();

		_camMgr = vgCam::CamManager::getSingletonPtr();
		assert( _camMgr != NULL );

	}
	//----------------------------------------------------------------
	void SimpleTree::getVisibleSet( vgKernel::RendererPackage* visible_set )
	{
		assert( visible_set != NULL );
		assert( _allRenderers != NULL );
		assert( _frustum != NULL );

		assert( _allRenderers->size() == visible_set->size() );
		//m_vLeafBox.clear();

		vgKernel::RendererPackage::iterator ipac = _allRenderers->begin();
		vgKernel::RendererPackage::iterator ipac_end = _allRenderers->end();

		vgKernel::RendererPackage::iterator outipac = visible_set->begin();

		static Renderer* curleaf = NULL;
		static int priority = 0;



		for ( ; ipac != ipac_end ; ++ipac , ++ outipac )
		{
			assert( outipac != visible_set->end() );

			RendererQueue* queue = &ipac->second;
			RendererQueue* visible_queue = &outipac->second;

			assert( visible_queue->empty() == true );

			_bufPosPriorRenderers.clear();
			_bufNegPriorRenderers.clear();

			RendererQueue::iterator iter = queue->begin();
			RendererQueue::iterator iter_end = queue->end();

			for ( ; iter != iter_end ; ++iter )
			{
				curleaf = *iter;

				if( _frustum->testBoxInFrustum( curleaf->getBoundingBox() ) == false )
				{
					continue;
				}

				float distance_square = 
					curleaf->setDistanceToViewer( _camMgr->getCurrentPosition() );

				if ( _distanceCullSquare > 0.0f )
				{
					if ( distance_square > _distanceCullSquare )
					{
						continue;
					}
				}


				// 渲染优先级版本
				priority = curleaf->getRenderingPriority();

				if ( priority == 0 )
				{
					visible_queue->push_back( curleaf );
				}
				else if ( priority > 0 )
				{
					_bufPosPriorRenderers.push_back( curleaf );
				}
				else
				{
					_bufNegPriorRenderers.push_back( curleaf );
				}
			} //  end of queue

			//------------------------------------------
			// 插入有优先级的物体
			//------------------------------------------
			if ( _bufPosPriorRenderers.empty() == false )
			{
				std::sort( _bufPosPriorRenderers.begin() , _bufPosPriorRenderers.end() ,
					_greatorPriorAlgo );

				visible_queue->insert( visible_queue->begin() , 
					_bufPosPriorRenderers.begin() , _bufPosPriorRenderers.end() );
			}

			if ( _bufNegPriorRenderers.empty() == false )
			{
				std::sort( _bufNegPriorRenderers.begin() , _bufNegPriorRenderers.end() ,
					_greatorPriorAlgo );

				visible_queue->insert( visible_queue->end() , 
					_bufNegPriorRenderers.begin() , _bufNegPriorRenderers.end() );
			}
		}
	}
	//----------------------------------------------------------------


}// end of namespace vgTree
