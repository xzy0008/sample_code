


#include <vgStableHeaders.h>
#include <vgTerritory/vgtTerritoryPlugin.h>
#include <vgTerritory/vgtTerrainManager.h>

#include <vgTerritory/vgtTerrainCenterManager.h>
#include <vgTerritory/vgtElevationManager.h>



namespace vgTerritory {
	
	
	
	

	bool TerritoryPlugin::initInOpenGL()
	{
		vgTerritory::TerrainManager::getSingleton().initAfterOpenGLSetup();
		return true;
	}


	void TerritoryPlugin::render()
	{
		// vgTerritory::TerrainManager::getSingleton().render();
	}

	bool TerritoryPlugin::uninitInOpenGL()
	{

		vgTerritory::TerrainManager::getSingleton().uninitBeforeOpenGLDestroy();
		vgTerritory::ElevationManager::getSingleton().uninitBeforeOpenGLDestroy();
		vgTerritory::TerrainCenterManager::getSingleton().uninitBeforeOpenGLDestroy();


		return true;
	}

	void TerritoryPlugin::reset()
	{
		vgTerritory::TerrainManager::getSingleton().dropTerrianData();
	}

	void TerritoryPlugin::readProject( const String& projpath , const String& projname )
	{
		vgTerritory::TerrainManager::getSingleton().readProject( projpath, projname );
	}

	void TerritoryPlugin::saveProject( const String& projpath , const String& projname )
	{
		TerrainManager::getSingleton().saveProject( projpath, projname );
	}
}// end of namespace vgTerritory
