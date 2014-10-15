


#ifndef __VGCACAMFACADE_H__
#define __VGCACAMFACADE_H__
#include <vgCam/vgcaDefinition.h>
#include <vgKernel/vgkForward.h>
#include <vgKernel/vgkRenderer.h>
#include <vgCam/vgcaViewCam.h>

	
namespace vgCam {



	/**
		@date 	2008/12/11  21:53	
		@author  leven
	
		@brief 	
	
		@see    
	*/
	class VGCA_EXPORT  CamFacade
	{
	public:
		CamFacade()
		{
			
		}
		~CamFacade()
		{
			
		}

	public:

		// 转到物体,当为camera的时候自动执行处理.
		static bool gotoObject( const String& obj_name );

		// 只有类型是camera的时候才跳转
		static bool gotoCameraByName( const String& cam_name );
		static bool gotoCamera( vgCam::ViewCam* cam );

		static bool gotoRenderer( vgKernel::Renderer* renderer );

		static bool gotoBox( const vgKernel::Box& box );
	
		static bool gotoSelectedObject();

		static bool gotoSelectedCamera();

		static bool playVCR( const String& name );

		static bool stopVCR( const String& vcrname );

		static bool continueVCR( const String& vcrname );

		static bool stopVCRSeries( );

		static bool continueVCRSeries( );

		static bool accelerateVCR( const String& vcrname );

		static bool decelerateVCR( const String& vcrname );
	};
	
	
}// end of namespace vgCam
	


#endif // end of __VGCACAMFACADE_H__