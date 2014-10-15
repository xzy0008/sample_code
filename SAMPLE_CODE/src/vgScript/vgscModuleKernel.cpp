


#include <vgStableHeaders.h>
#include <vgScript/vgscModuleKernel.h>
#include <vgScript/vgscExportKernel.h>
#include <vgScript/vgscExportKernelObjects.h>
#include <vgScript/vgscBoostPythonInclude.h>

namespace vgScript {
	
	
	//----------------------------------------------------------------
	BOOST_PYTHON_MODULE(vgKernel)
	{
		exportKernel();
		exportKernelObjects();
	}
	//----------------------------------------------------------------
	void registerScriptModule_vgKernel()
	{
		initvgKernel();
	}
	//----------------------------------------------------------------


}// end of namespace vgScript
