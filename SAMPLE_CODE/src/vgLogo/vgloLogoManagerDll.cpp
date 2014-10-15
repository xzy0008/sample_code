
#include <vgStableHeaders.h>
#include <vgKernel/vgkPluginManager.h>
#include <vgLogo/vgloLogoManager.h>
#include <vgLogo/vgloLogoPlugin.h>


extern "C" void VGL_EXPORT  VGK_PLUGIN_DLL_START(void)
{
	vgKernel::PluginManager::getSingleton().registerPlugin( 
		new vgLogo::LogoPlugin );
}

extern "C" void VGL_EXPORT VGK_PLUGIN_DLL_END(void)
{

	vgKernel::SingletonManager::getSingleton().deleteSingletonInstance(
		vgLogo::LogoManager::getSingletonPtr() );

}
