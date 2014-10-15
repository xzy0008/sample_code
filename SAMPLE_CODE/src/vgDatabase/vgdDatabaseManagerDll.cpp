
#include <vgStableHeaders.h>

#include <vgKernel/vgkPluginManager.h>
#include <vgDatabase/vgdDatabaseManager.h>
#include <vgDatabase/vgdProfileManager.h>
#include <vgDatabase/vgdDatabasePlugin.h>

extern "C" void VGD_EXPORT  VGK_PLUGIN_DLL_START(void)
{
	vgKernel::PluginManager::getSingleton().registerPlugin( 
		new vgDatabase::DatabasePlugin );
}

extern "C" void VGD_EXPORT VGK_PLUGIN_DLL_END(void)
{
	vgKernel::SingletonManager::getSingleton().deleteSingletonInstance( 
		vgDatabase::DatabaseManager::getSingletonPtr() );

	vgKernel::SingletonManager::getSingleton().deleteSingletonInstance( 
		vgDatabase::ProfileManager::getSingletonPtr() );
}
