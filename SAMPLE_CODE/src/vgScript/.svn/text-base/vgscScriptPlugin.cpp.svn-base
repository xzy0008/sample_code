


#include <vgStableHeaders.h>
#include <vgScript/vgscScriptPlugin.h>
#include <vgScript/vgscScriptManager.h>


namespace vgScript {
	
	
	
	

	bool ScriptPlugin::initInOpenGL()
	{
		vgScript::ScriptManager::getSingleton().initAfterOpenGLSetup();
		return true;
	}

	void ScriptPlugin::render()
	{
		vgScript::ScriptManager::getSingleton().render();
	}

	bool ScriptPlugin::uninitInOpenGL()
	{
		vgScript::ScriptManager::getSingleton().uninitBeforeOpenGLDestroy();
		return true;
	}

	void ScriptPlugin::reset()
	{
		vgScript::ScriptManager::getSingleton().uninitBeforeOpenGLDestroy();
	}

	void ScriptPlugin::saveProject( const String& projpath , const String& projname )
	{
		vgScript::ScriptManager::getSingleton().saveProject( projpath , projname );
	}

	void ScriptPlugin::renderFirst()
	{
		vgScript::ScriptManager::getSingleton().renderBegin();
	}

	void ScriptPlugin::renderLast()
	{
		//vgScript::ScriptManager::getSingleton()
		vgScript::ScriptManager::getSingleton().renderEnd();
	}

	void ScriptPlugin::readProjectEnd( const String& projpath , const String& projname )
	{
		vgScript::ScriptManager::getSingleton().readProjectEnd(projpath , projname);
	}
}// end of namespace vgScript
