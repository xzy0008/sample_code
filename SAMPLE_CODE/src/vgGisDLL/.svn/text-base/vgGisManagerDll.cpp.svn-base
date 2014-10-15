
#include <vgStableHeaders.h>

#include <vgKernel/vgkPluginManager.h>

#include <vgGis/vgGisManager.h>
#include <vgGisDLL/vgGisPlugin.h>
#include <vgGis3D/vggiGisDataManager.h>
#include <vgGIS3D/vggiContourManager.h>

extern "C" void VGG_EXPORT  VGK_PLUGIN_DLL_START(void)
{
	vgKernel::PluginManager::getSingleton().registerPlugin( 
		new vgGIS3D::GisPlugin );
}

extern "C" void VGG_EXPORT VGK_PLUGIN_DLL_END(void)
{
	vgKernel::SingletonManager::getSingleton().deleteSingletonInstance( 
		vgGIS3D::GisManager::getSingletonPtr() );

	vgKernel::SingletonManager::getSingleton().deleteSingletonInstance(
		vgGIS3D::GisDataManager::getSingletonPtr());

	vgKernel::SingletonManager::getSingleton().deleteSingletonInstance(
		vgGIS3D::ContourManager::getSingletonPtr());
}
