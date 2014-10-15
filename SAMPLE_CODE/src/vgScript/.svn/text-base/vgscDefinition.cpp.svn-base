




#include <vgStableHeaders.h>
#include <vgScript/vgscDefinition.h>

#include <vgScript/vgscScriptPlugin.h>
#include <vgKernel/vgkPluginManager.h>


#include <vgScript/vgscScriptManager.h>



extern "C" void VGSC_EXPORT  VGK_PLUGIN_DLL_START(void)
{
	vgKernel::PluginManager::getSingleton().registerPlugin( 
		new vgScript::ScriptPlugin );
}

extern "C" void VGSC_EXPORT VGK_PLUGIN_DLL_END(void)
{
	vgKernel::SingletonManager::getSingleton().deleteSingletonInstance(
		vgScript::ScriptManager::getSingletonPtr() );
}





bool ScriptManager_runScriptString( const String& script_str )
{
	using namespace vgScript;
	return ScriptManager::getSingleton().runScriptString( script_str );
}

void ScriptManager_createMultiSelectDailogAndRunScript()
{
	using namespace vgScript;
	ScriptManager::getSingleton().createMultiSelectDailogAndRunScript( );
}


bool ScriptManager_addUserScriptFunc( ScriptInitializeFunc user_func )
{
	using namespace vgScript;
	return ScriptManager::getSingleton().addUserScriptFunc( user_func );

}





