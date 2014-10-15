

#include <vgStableHeaders.h>

#include <vgShape/vgshExtendedUtility.h>
#include <vgShape/vgshShapeManager.h>

namespace vgShape{

	
	//----------------------------------------------------------------
	ExtendedUtility::ExtendedUtility()
	{
		
	}
	
	//----------------------------------------------------------------
	ExtendedUtility::~ExtendedUtility()
	{

	}

	//----------------------------------------------------------------
	void ExtendedUtility::translateAllShape( const double& offsetX, const double& offsetY,
		const double& offsetZ )
	{
		DataSourcePtrMap*	pDatasources = ShapeManager::getSingleton().getDataSources();
		DataSourcePtrMap::iterator iterOut = pDatasources->begin();
		DataSourcePtrMap::iterator iter_endOut = pDatasources->end();

		for ( ;iterOut != iter_endOut ; ++iterOut )
		{
			LayerPtrVector* pLayers = iterOut->second->getLayerPtrVector();
			
			LayerPtrVector::iterator iterIn = pLayers->begin();
			LayerPtrVector::iterator iter_endIn = pLayers->end();

			for ( ; iterIn != iter_endIn ; ++ iterIn )
			{
				(*iterIn)->translate( offsetX, offsetY, offsetZ );
			}
		}
	}
	//----------------------------------------------------------------
	
}//namespace vgShape