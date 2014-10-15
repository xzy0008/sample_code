
#include <vgStableHeaders.h>

#include <vgKernel/vgkPluginManager.h>

#include <vgTrigger/vgtrTriggerManager.h>
#include <vgTrigger/vgtrTriggerPlugin.h>


extern "C" void VGTRI_EXPORT  VGK_PLUGIN_DLL_START(void)
{
	vgKernel::PluginManager::getSingleton().registerPlugin( 
		new vgTrigger::TriggerPlugin );
}

extern "C" void VGTRI_EXPORT VGK_PLUGIN_DLL_END(void)
{
	vgKernel::SingletonManager::getSingleton().deleteSingletonInstance( 
		vgTrigger::TriggerManager::getSingletonPtr() );
}

