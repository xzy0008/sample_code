


#ifndef __VGKCAMMGRIMPL_H__
#define __VGKCAMMGRIMPL_H__

#include <vgKernel/vgkForward.h>
#include <vgKernel/vgkRendererObserver.h>

	
namespace vgKernel {

	/**
		@date 	2009/06/03  10:29	
		@author  xy
	
		@brief 	
	
		@see    
	*/
	class VGK_EXPORT CamMgrImpl : public ObserverContainer
	{
	public:
		CamMgrImpl( bool autoreg = true );
		virtual ~CamMgrImpl()
		{
			
		}
	

	public:

		virtual bool isControlling() = 0;

		virtual Vec3 getCurrentPosition() = 0;

		virtual Vec3* getCurrentPositionPtr() = 0;

		virtual void setCurrentPosition( const Vec3& newpos ) = 0;

		virtual Vec3 getCurrentDirection() = 0;

		virtual void setMovingEnable( bool enable_it ) = 0;

	};
	
	
}// end of namespace vgKernel
	


#endif // end of __VGKCAMMGRIMPL_H__