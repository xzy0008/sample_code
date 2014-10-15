



#include <vgStableHeaders.h>
#ifdef	SCRIPT_VGT

#include <vgScript/vgscExportTerritory.h>
#include <vgTerritory/vgtTerrainManager.h>
#include <vgTerritory/vgtElevationManager.h>


namespace vgScript {
	
	

	//----------------------------------------------------------------
	void exportTerritory()
	{
		using namespace boost::python;
		using namespace vgTerritory;

		class_<TerrainManager >( "TerrainManager" , no_init )
			.def("hasTerrainData", &TerrainManager::hasTerrainData )
			.def("openVtrFile", &TerrainManager::openVtrFile )
			.def("dropTerrianData", &TerrainManager::dropTerrianData )
			.def("saveData", &TerrainManager::saveData )

			.def("setRenderFlag", &TerrainManager::setRenderFlag )
			.def("getRenderFlag", &TerrainManager::getRenderFlag )

			.def("setCollisionDetectedFlag", &TerrainManager::setCollisionDetectedFlag )
			.def("getCollisionDetectedFlag", &TerrainManager::getCollisionDetectedFlag )

			.def("setCutSurfaceAnalysisFlag", &TerrainManager::setCutSurfaceAnalysisFlag )
			.def("getCutSurfaceAnalysisFlag", &TerrainManager::getCutSurfaceAnalysisFlag )
			.def("setCutSurfaceAnalysisFlag2", &TerrainManager::setCutSurfaceAnalysisFlag2 )
			.def("getCutSurfaceAnalysisFlag2", &TerrainManager::getCutSurfaceAnalysisFlag2 )

			.def("setCutSurfaceLevellingFlag", &TerrainManager::setCutSurfaceLevellingFlag )
			.def("getCutSurfaceLevellingFlag", &TerrainManager::getCutSurfaceLevellingFlag )

			.def("setCutSurfaceVisibilityFlag", &TerrainManager::setCutSurfaceVisibilityFlag )
			.def("getCutSurfaceVisibilityFlag", &TerrainManager::getCutSurfaceVisibilityFlag )
			.def("setCutSurfaceVisibilityFlag2", &TerrainManager::setCutSurfaceVisibilityFlag2 )
			.def("getCutSurfaceVisibilityFlag2", &TerrainManager::getCutSurfaceVisibilityFlag2 )

			.def("setCutAreaFlag", &TerrainManager::setCutAreaFlag )
			.def("getCutAreaFlag", &TerrainManager::getCutAreaFlag )

			.def("setBlendFlag", &TerrainManager::setBlendFlag )
			.def("getBlendFlag", &TerrainManager::getBlendFlag )

			.def( "getSingleton", &TerrainManager::getSingleton ,
			return_value_policy<reference_existing_object>() )
			.staticmethod( "getSingleton" )
		;

		class_<ElevationManager >( "ElevationManager" , no_init )
			.def("addRefToAllElevationItems", &ElevationManager::addRefToAllElevationItems )


			//.def("getWholeSceneBound", &ElevationManager::getWholeSceneBound )
			//.def("getValidSceneBound", &ElevationManager::getValidSceneBound )

			.def( "getSingleton", &ElevationManager::getSingleton ,
			return_value_policy<reference_existing_object>() )
			.staticmethod( "getSingleton" )
			;

	}
	//----------------------------------------------------------------


}// end of namespace vgScript
#endif
