


#include <vgStableHeaders.h>
#include <vgScript/vgscModuleCam.h>
#include <vgScript/vgscExportCam.h>
#include <vgScript/vgscBoostPythonInclude.h>

namespace vgScript {
	
	
	//----------------------------------------------------------------
	BOOST_PYTHON_MODULE(vgCam)
	{
		exportCam();
	}
	//----------------------------------------------------------------
	void registerScriptModule_vgCam()
	{
		initvgCam();
	}
	//----------------------------------------------------------------
	
}// end of namespace vgScript
