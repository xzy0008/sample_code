


#ifndef __VGSDKPLUGIN_H__
#define __VGSDKPLUGIN_H__

#include <vgSDK/vgsdkDefinition.h>
#include <vgKernel/vgkForward.h>

#include <vgKernel/vgkPlugin.h>

	
namespace vgSDK {

	/**
		@date 	2009/06/29  14:41	
		@author  lss
	
		@brief 	
	
		@see    
	*/
	class SDKUtilityPlugin : public vgKernel::Plugin
	{
	public:
		SDKUtilityPlugin():
		  vgKernel::Plugin()
		{
			
		}
		virtual ~SDKUtilityPlugin()
		{
			
		}

	public:

		virtual String getName()
		{
			return VGSDK_DLL_NAME;	
		}

	};

	

	
}// end of namespace vgSDK
	


#endif // end of __VGSHSHAPEPLUGIN_H__