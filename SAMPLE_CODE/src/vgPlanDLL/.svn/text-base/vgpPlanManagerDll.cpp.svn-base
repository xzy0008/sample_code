
#include <vgStableHeaders.h>


#include <vgKernel/vgkPluginManager.h>
#include <vgPlan/vgPlanmanager.h>
#include <vgplandll/vgpPlanPlugin.h>


extern "C" void VGP_EXPORT  VGK_PLUGIN_DLL_START(void)
{
	vgKernel::PluginManager::getSingleton().registerPlugin( 
		new vgPlan::PlanPlugin );
}

extern "C" void VGP_EXPORT VGK_PLUGIN_DLL_END(void)
{
	vgKernel::SingletonManager::getSingleton().deleteSingletonInstance( 
		vgPlan::vgPlanManager::getSingletonPtr() );
}
