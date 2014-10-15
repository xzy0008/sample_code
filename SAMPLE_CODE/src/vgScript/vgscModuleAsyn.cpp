



#include <vgStableHeaders.h>
#include <vgScript/vgscModuleAsyn.h>
#include <vgScript/vgscExportAsyn.h>
#include <vgScript/vgscBoostPythonInclude.h>

namespace vgScript {
	
	
	
	//----------------------------------------------------------------
	BOOST_PYTHON_MODULE(vgAsyn)
	{
		exportAsyn();
	}
	//----------------------------------------------------------------
	void registerScriptModule_vgAsyn()
	{
		initvgAsyn();
	}

}// end of namespace vgScript
