


#include <vgStableHeaders.h>
#include <vgKernel/vgkSystemUtility.h>
#include <vgScript/vgscScriptManager.h>
#include <vgScript/vgscScriptFacade.h>


namespace vgScript {

	bool   ScriptFacade::RunScriptSimpleString( const String& script_str )
	{
		return vgScript::ScriptManager::getSingleton().runScriptString(script_str);
	}

	bool   ScriptFacade::RunScriptFile( const String& script_file_path ,
		bool alert)
	{
		return vgScript::ScriptManager::getSingleton().runScriptFile(script_file_path, alert);
	}	
	


}// end of namespace vgScript
