


#include <vgStableHeaders.h>
#include <vgScript/vgscModuleScript.h>
#include <vgScript/vgscExportScript.h>


namespace vgScript {
	
	
	
	//----------------------------------------------------------------
	BOOST_PYTHON_MODULE(vgScript)
	{
		exportScript();
	}
	//----------------------------------------------------------------
	void registerScriptModule_vgScript()
	{
		initvgScript();
	}
	//----------------------------------------------------------------


}// end of namespace vgScript
