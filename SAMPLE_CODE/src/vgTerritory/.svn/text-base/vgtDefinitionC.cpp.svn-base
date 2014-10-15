


#include <vgStableHeaders.h>
#include <vgTerritory/vgtTerrainManager.h>
#include <vgTerritory/vgtElevationFilter.h>
#include <vgTerritory/vgtTerrainCenterManager.h>

using namespace vgTerritory;

bool TerrainManager_getElevationByPosition( 
	const Vec3& pos , float& out_elevation , 
	const bool& use_accurate )
{
	

	return TerrainManager::getSingleton().getElevationByPosition (pos , out_elevation , 
		use_accurate );
}


bool TerrainManager_saveData( 
							  const String& absolute_path )
{
	return TerrainManager::getSingleton().saveData( 
		absolute_path );
}


bool TerrainManager_hasTerrainData()
{
return TerrainManager::getSingleton().hasTerrainData();
}

bool TerrainManager_initAfterOpenGLSetup()
{
		return TerrainManager::getSingleton().initAfterOpenGLSetup();
}
//-----------------------------------------------


 bool TerrainManager_uninitBeforeOpenGLDestroy()
{
		return TerrainManager::getSingleton(). uninitBeforeOpenGLDestroy() ;
}
//-----------------------------------------------

 bool TerrainManager_dropTerrianData()
{
		return TerrainManager::getSingleton(). dropTerrianData() ;
}
//-----------------------------------------------

 void TerrainManager_render()
{
		return TerrainManager::getSingleton(). render() ;
}
//-----------------------------------------------

 bool TerrainManager_openVtrFile(const String& abs_vtr_filename)
{
		return TerrainManager::getSingleton(). openVtrFile( abs_vtr_filename) ;
}
//-----------------------------------------------

 void TerrainManager_setRenderFlag(const bool& enable)
{
		return TerrainManager::getSingleton(). setRenderFlag( enable) ;
}
//-----------------------------------------------

 bool TerrainManager_getRenderFlag()
{
		return TerrainManager::getSingleton(). getRenderFlag() ;
}
//-----------------------------------------------


 void TerrainManager_setCollisionDetectedFlag(const bool& enable)
{
		return TerrainManager::getSingleton(). setCollisionDetectedFlag( enable) ;
}
//-----------------------------------------------

 bool TerrainManager_getCollisionDetectedFlag()
{
		return TerrainManager::getSingleton().  getCollisionDetectedFlag();
}
//-----------------------------------------------

 void TerrainManager_setCutSurfaceAnalysisFlag(const bool& enable)
{
		return TerrainManager::getSingleton(). setCutSurfaceAnalysisFlag( enable) ;
}
//-----------------------------------------------

 bool TerrainManager_getCutSurfaceAnalysisFlag() 
{
		return TerrainManager::getSingleton(). getCutSurfaceAnalysisFlag()  ;
}
//-----------------------------------------------


 void TerrainManager_setCutSurfaceAnalysisFlag2(const bool& enable)
{
		return TerrainManager::getSingleton(). setCutSurfaceAnalysisFlag2( enable) ;
}
//-----------------------------------------------

 bool TerrainManager_getCutSurfaceAnalysisFlag2() 
{
		return TerrainManager::getSingleton(). getCutSurfaceAnalysisFlag2()  ;
}
//-----------------------------------------------


 void TerrainManager_setCutSurfaceVisibilityFlag(const bool& enable)
{
		return TerrainManager::getSingleton(). setCutSurfaceVisibilityFlag( enable) ;
}
//-----------------------------------------------

 bool TerrainManager_getCutSurfaceVisibilityFlag() 
{
		return TerrainManager::getSingleton(). getCutSurfaceVisibilityFlag()  ;
}
//-----------------------------------------------

 void TerrainManager_setCutSurfaceVisibilityFlag2(const bool& enable)
{
		return TerrainManager::getSingleton(). setCutSurfaceVisibilityFlag2( enable) ;
}
//-----------------------------------------------

 bool TerrainManager_getCutSurfaceVisibilityFlag2() 
{
		return TerrainManager::getSingleton(). getCutSurfaceVisibilityFlag2()  ;
}
//-----------------------------------------------

 void TerrainManager_setCutSurfaceLevellingFlag(const bool& enable)
{
		return TerrainManager::getSingleton(). setCutSurfaceLevellingFlag( enable) ;
}
//-----------------------------------------------

 bool TerrainManager_getCutSurfaceLevellingFlag() 
{
		return TerrainManager::getSingleton(). getCutSurfaceLevellingFlag()  ;
}
//-----------------------------------------------


 void TerrainManager_setCutAreaFlag(const bool& enable)
{
		return TerrainManager::getSingleton(). setCutAreaFlag( enable) ;
}
//-----------------------------------------------

 bool TerrainManager_getCutAreaFlag() 
{
		return TerrainManager::getSingleton().  getCutAreaFlag();
}
//-----------------------------------------------


 void TerrainManager_setBlendFlag(const bool& enable)
{
		return TerrainManager::getSingleton(). setBlendFlag( enable) ;
}
//-----------------------------------------------

 bool TerrainManager_getBlendFlag() 
{
		return TerrainManager::getSingleton(). getBlendFlag() ;
}
//-----------------------------------------------

 float* TerrainManager_getUserClipPlaneParam()
{
		return TerrainManager::getSingleton().  getUserClipPlaneParam();
}

//-----------------------------------------------
bool TerrainManager_saveSelectVtrAndVgi( const String& folderpath )
{
	return TerrainManager::getSingleton().saveSelectVtrAndVgi( folderpath );
}

//-----------------------------------------------
void TerrainManager_setSaveMode( bool bMode )
{
	TerrainManager::getSingleton().setSaveMode( bMode );
}

//-----------------------------------------------
vgKernel::Vec2* TerrainManager_getTerrainBoundCenter()
{
	ElevationBound bound = ElevationManager::getSingleton().getValidSceneBound();

	// 指针由客房端负责删除
	return new vgKernel::Vec2( bound.getCenter().x, bound.getCenter().y );
}

//-----------------------------------------------
float TerrainManager_getMaxLengthFromTerrainBoundingBox()
{
	ElevationBound bound = ElevationManager::getSingleton().getValidSceneBound();

	float width = bound.getWidth();
	float height = bound.getHeight();

	return width > height ? width : height;
}

//-----------------------------------------------
bool TerrainManager_hasCutArea()
{
	return TerrainManager::getSingleton().hasCutArea();
}

//-----------------------------------------------
// void TerrainManager_readProject()
//{
//		return TerrainManager::getSingleton(). readProject() ;
//}
////-----------------------------------------------
//
// void TerrainManager_saveProject()
//{
//		return TerrainManager::getSingleton().  saveProject();
//}
//-----------------------------------------------


 vgKernel::Vec3* getTerrainCoord()
{
	vgTerritory::VtrHeaderPtr header = 
		vgTerritory::ElevationManager::getSingleton().getMainFileHandleVtr()->getHeader();

	if ( header.isNull() == true )
	{
		return NULL;
	}

	return new vgKernel::Vec3( header->originX , header->originY , -header->originZ );
}




StructVtrHeader* getMainFileHandleVtrHeader()
{
	vgTerritory::FileHandleVtr* vtrhandle =
		vgTerritory::ElevationManager::getSingleton().getMainFileHandleVtr();

	if ( vtrhandle == NULL )
	{
		return NULL;
	}

	assert( vtrhandle != NULL );

	vgTerritory::VtrHeaderPtr pheader = vtrhandle->getHeader();

	return pheader.getPointer();
}




void restoreInEditMode()
{
	using namespace vgTerritory;

	ElevationFilter::getSingleton().clearPolygons();

	TerrainCenterManager::getSingleton().reloadAllCenters();
}

void saveInEditMode()
{
	vgTerritory::ElevationFilter::getSingleton().doFilterAndSave();
}



ElevationItemH ElevationManager_getElevationItem( const String& itemname ,
												 const bool& return_empty_item )
{


	return (ElevationItemH)ElevationManager::getSingleton().getElevationItem( itemname , return_empty_item );

}

void ElevationItem_getDisplaceParams(  ElevationItemH itm,
									 float* param )
{
	ElevationItem* im = (ElevationItem*)itm;

	im->getDisplaceParams(param);
}


long getCurrentHeightLayerNumber()
{
	return TerrainCenterManager::getSingleton().getCurrentHeightLayerNumber();
}

void TerrainManager_setVerSectionAnaFlag(const bool& enable)
{
	return TerrainManager::getSingleton(). setVerSectionAnaFlag( enable) ;
}
//-----------------------------------------------

bool TerrainManager_getVerSectionAnaFlag()
{
	return TerrainManager::getSingleton(). getVerSectionAnaFlag()  ;
}
//-----------------------------------------------

void TerrainManager_setHorSectionAnaFlag(const bool& enable)
{
	return TerrainManager::getSingleton(). setHorSectionAnaFlag( enable) ;
}
//-----------------------------------------------

bool TerrainManager_getHorSectionAnaFlag()
{
	return TerrainManager::getSingleton(). getHorSectionAnaFlag()  ;
}
//-----------------------------------------------
