
#include <vgStableHeaders.h>
#include <vgKernel/vgkPluginManager.h>
#include <vgFont/vgfFontManager.h>
#include <vgFont/vgfFontPlugin.h>

extern "C" void VGF_EXPORT  VGK_PLUGIN_DLL_START(void)
{
	vgKernel::PluginManager::getSingleton().registerPlugin( 
		new vgFont::FontPlugin );
}

extern "C" void VGF_EXPORT VGK_PLUGIN_DLL_END(void)
{

	vgKernel::SingletonManager::getSingleton().deleteSingletonInstance(
		vgFont::FontManager::getSingletonPtr() );

}
