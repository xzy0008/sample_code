
#include <vgStableHeaders.h>

#include <vgKernel/vgkPluginManager.h>

#include <vgUIController/vgUIController.h>
#include <vgUIControllerDLL/vgUIControllerPlugin.h>



extern "C" void VGUI_EXPORT  VGK_PLUGIN_DLL_START(void)
{
	vgKernel::PluginManager::getSingleton().registerPlugin( 
		new vgUI::UIControllerPlugin );
}

extern "C" void VGUI_EXPORT VGK_PLUGIN_DLL_END(void)
{
	vgKernel::SingletonManager::getSingleton().deleteSingletonInstance( 
		vgUI::UIController::getSingletonPtr() );
}
