
#include <vgStableHeaders.h>

#include <vgKernel/vgkPluginManager.h>
#include <vgKernel/vgkSystemUtility.h>
#include <vgSound/vgSoundManager.h>

#include <vgSoundDLL/vgSoundPlugin.h>



extern "C" void VGSOUND_EXPORT  VGK_PLUGIN_DLL_START(void)
{
	vgKernel::PluginManager::getSingleton().registerPlugin( 
		new vgSound::SoundPlugin);
}

extern "C" void VGSOUND_EXPORT VGK_PLUGIN_DLL_END(void)
{
#if 1
	vgKernel::SingletonManager::getSingleton().deleteSingletonInstance( 
		vgSound::SoundManager::getSingletonPtr());
#endif
}
