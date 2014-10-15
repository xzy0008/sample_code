
#include <vgStableHeaders.h>

//#include <vgTerritory/vgTerrainManagerPlugin.h>

//#include <vgPlugin/vgplManagerRoot.h>

#include <vgKernel/vgkPluginManager.h>
#include <vgTerritory/vgtTerrainManager.h>
#include <vgTerritory/vgtTerrainCenterManager.h>
#include <vgTerritory/vgtElevationManager.h>
#include <vgTerritory/vgtTerritoryPlugin.h>

#include <vgTerritory/vgtElevationFilter.h>

//vgTerritory::vgTerrainManagerPlugin* TerrainPlugin;
//
//extern "C" void VGT_EXPORT  dllStartPlugin(void)
//{
//    // Create new scene manager
//    TerrainPlugin = new vgTerritory::vgTerrainManagerPlugin();
//
//    // Register
//    vgPlugin::ManagerRoot::getSingleton().installPlugin(TerrainPlugin);
//}
//
//extern "C" void VGT_EXPORT dllStopPlugin(void)
//{
//	vgPlugin::ManagerRoot::getSingleton().uninstallPlugin(TerrainPlugin);
//    
//	delete TerrainPlugin;
//}




extern "C" void VGT_EXPORT  VGK_PLUGIN_DLL_START(void)
{
	vgKernel::PluginManager::getSingleton().registerPlugin( 
		new vgTerritory::TerritoryPlugin );
}

extern "C" void VGT_EXPORT VGK_PLUGIN_DLL_END(void)
{
	vgKernel::SingletonManager::getSingleton().deleteSingletonInstance( 
		vgTerritory::TerrainCenterManager::getSingletonPtr() );

	vgKernel::SingletonManager::getSingleton().deleteSingletonInstance( 
		vgTerritory::ElevationManager::getSingletonPtr() );

	vgKernel::SingletonManager::getSingleton().deleteSingletonInstance( 
		vgTerritory::TerrainManager::getSingletonPtr() );

	vgKernel::SingletonManager::getSingleton().deleteSingletonInstance(
		vgTerritory::ElevationFilter::getSingletonPtr() );
}
