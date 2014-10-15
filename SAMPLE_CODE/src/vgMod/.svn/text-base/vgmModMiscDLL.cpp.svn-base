#include <vgStableHeaders.h>

#include <vgStableHeaders.h>

#include <vgKernel/vgkPluginManager.h>

#include <vgMod/vgcChannelManager.h>
#include <vgChannel/vgcChannelPlugin.h>


extern "C" void VGCHAN_EXPORT  VGK_PLUGIN_DLL_START(void)
{
	vgKernel::PluginManager::getSingleton().registerPlugin( 
		new vgChannel::ChannelPlugin );
}

extern "C" void VGCHAN_EXPORT VGK_PLUGIN_DLL_END(void)
{
	vgKernel::SingletonManager::getSingleton().deleteSingletonInstance( 
		vgChannel::ChannelManager::getSingletonPtr() );
}

