


#ifndef __VGCOPROJECTCONFIGREGPROXY_H__
#define __VGCOPROJECTCONFIGREGPROXY_H__

#include <vgKernel/vgkForward.h>

	
namespace vgConf {


	/**
		@date 	2008/12/04  14:57	
		@author  xy
	
		@brief 	表项的注册代理类.
	
		@see    
	*/
	class VGK_EXPORT ProjectConfigRegProxy
	{
	public:
		ProjectConfigRegProxy( String section  , String key , String defaultvalue );
		virtual ~ProjectConfigRegProxy()
		{
			
		}

	public:
	
	};

	
	
}// end of namespace vgConf
	


#endif // end of __VGCOPROJECTCONFIGREGPROXY_H__