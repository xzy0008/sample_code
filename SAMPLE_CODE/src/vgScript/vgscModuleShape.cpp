


#include <vgStableHeaders.h>
#ifdef	SCRIPT_VGSH

#include <vgScript/vgscModuleShape.h>
#include <vgScript/vgscExportShape.h>

#include <vgScript/vgscBoostPythonInclude.h>


namespace vgScript {
	
	//----------------------------------------------------------------
	BOOST_PYTHON_MODULE(vgShape)
	{
		exportShape();
	}
	//----------------------------------------------------------------
	void registerScriptModule_vgShape()
	{
		initvgShape();
	}
	
	
}// end of namespace vgScript

#endif
