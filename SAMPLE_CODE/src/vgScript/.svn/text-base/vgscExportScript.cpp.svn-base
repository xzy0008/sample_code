


#include <vgStableHeaders.h>
#include <vgScript/vgscExportScript.h>
#include <vgScript/vgscScriptManager.h>


namespace vgScript {
	
	
	
	
	//----------------------------------------------------------------
	void exportScript()
	{
		using namespace boost::python;

		class_<ScriptManager >( "ScriptManager" , no_init )
			.def( "runScriptFile", &ScriptManager::runScriptFile )
			.def( "runScriptString", &ScriptManager::runScriptString )
			.def( "createMultiSelectDailogAndRunScript", 
				&ScriptManager::createMultiSelectDailogAndRunScript )
			.def( "getDefaultScript", &ScriptManager::getDefaultScript )
			.def( "runScriptConsole", &ScriptManager::runScriptConsole )
			.def( "dumpToScriptConsole", &ScriptManager::dumpToScriptConsole )
			.def( "clearScriptConsoleContent", &ScriptManager::clearScriptConsoleContent )

			.def( "renderBegin", &ScriptManager::renderBegin )
			.def( "render", &ScriptManager::render )
			.def( "renderEnd", &ScriptManager::renderEnd )

			.def( "readProjectEnd", &ScriptManager::readProjectEnd )
			.def( "saveProject", &ScriptManager::saveProject )
			.def( "getUserDefinedScripts", &ScriptManager::getUserDefinedScripts )
			.def( "setUserDefinedScripts", &ScriptManager::setUserDefinedScripts )


			.def( "getSingleton", &ScriptManager::getSingleton ,
				return_value_policy<reference_existing_object>() )
			.staticmethod( "getSingleton" )
			;

	}
	//----------------------------------------------------------------


}// end of namespace vgScript
