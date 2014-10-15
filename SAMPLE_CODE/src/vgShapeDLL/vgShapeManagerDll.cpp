
#include <vgStableHeaders.h>

#include <vgKernel/vgkPluginManager.h>

#include <vgShape/vgshShapeManager.h>
#include <vgShapeDLL/vgShpPlugin.h>



extern "C" void VGSH_EXPORT  VGK_PLUGIN_DLL_START(void)
{
	vgKernel::PluginManager::getSingleton().registerPlugin( 
		new vgShape::ShapePlugin );
}

extern "C" void VGSH_EXPORT VGK_PLUGIN_DLL_END(void)
{
	vgKernel::SingletonManager::getSingleton().deleteSingletonInstance( 
		vgShape::ShapeManager::getSingletonPtr() );
}
