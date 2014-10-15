


#ifndef __VGSCSCRIPTFACADE_H__
#define __VGSCSCRIPTFACADE_H__


#include <vgScript/vgscDefinition.h>
#include <vgKernel/vgkForward.h>

	
namespace vgScript {

	/**
		@date 	2008/12/11  20:46	
		@author  leven
	
		@brief 	
	
		@see    
	*/
	class VGSC_EXPORT ScriptFacade
	{
	private:
		ScriptFacade()
		{
			
		}
		~ScriptFacade()
		{
			
		}
	
	public:

		//static void facade1();
		static bool RunScriptSimpleString( const String& script_str );
		static bool RunScriptFile( const String& script_file_path ,
			bool alert = true);

	};
	
	
}// end of namespace vgScript
	


#endif // end of __VGSCSCRIPTFACADE_H__