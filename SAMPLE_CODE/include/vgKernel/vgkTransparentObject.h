



#ifndef __VGKTRANSPARENTOBJECT_H__
#define __VGKTRANSPARENTOBJECT_H__

#include <vgKernel/vgkForward.h>

	
namespace vgKernel {

	/**
		@date 	2009/02/25  8:37	
		@author  xy
	
		@brief 	
	
		@see    
	*/
	class TransparentObject
	{
	public:
		TransparentObject()
		{
			
		}
		virtual ~TransparentObject()
		{
			
		}
	
	
	public:


		virtual bool isTransparent() = 0;

		virtual void setTransparent( bool set_to_transp = true ) = 0;
	
	
	};
	
	
}// end of namespace vgKernel
	


#endif // end of __VGKTRANSPARENTOBJECT_H__