
#include <vgStableHeaders.h>
#include <vgStableHeaders.h>
#include <vgTex/tvgGpuSupport.h>


namespace vgCore {
	
	
	
	
	//----------------------------------------------------------------
	bool GpuSupport::setupValidCgProfile( CGprofile& vertex_profile , 
		CGprofile& pixel_profile )
	{
		// 先这样写，以后要分成单独的2个小程序。

		//
		// Search for a valid vertex shader profile in this order:
		//
		// CG_PROFILE_ARBVP1 - GL_ARB_vertex_program
		// CG_PROFILE_VP40   - GL_ARB_vertex_program + GL_NV_vertex_program3
		//

		if( cgGLIsProfileSupported(CG_PROFILE_VP40) )
		{
			vertex_profile = CG_PROFILE_VP40;
		}
		else if( cgGLIsProfileSupported(CG_PROFILE_ARBVP1) )
		{
			vertex_profile = CG_PROFILE_ARBVP1;
		}

		else
		{
			VG_EXCEPT(Exception::ERR_RENDERINGAPI_ERROR ,
				"显卡不支持Vertex Shader." ,
				"OpenGLSupport::setupValidCgProfile");
			return false;
		}

		//
		// Search for a valid pixel shader profile in this order:
		//
		// CG_PROFILE_ARBFP1 - GL_ARB_fragment_program
		// CG_PROFILE_FP30   - GL_NV_fragment_program
		// CG_PROFILE_FP20   - NV_texture_shader & NV_register_combiners
		//
		if( cgGLIsProfileSupported(CG_PROFILE_FP40) )
		{
			pixel_profile = CG_PROFILE_FP40;
		}
		else if( cgGLIsProfileSupported(CG_PROFILE_FP30) )
		{
			pixel_profile = CG_PROFILE_FP30;
		}
		else if( cgGLIsProfileSupported(CG_PROFILE_ARBFP1) )
		{
			pixel_profile = CG_PROFILE_ARBFP1;
		}
		 
		else if( cgGLIsProfileSupported(CG_PROFILE_FP20) )
		{
			pixel_profile = CG_PROFILE_FP20;
		}
		else
		{
			VG_EXCEPT(Exception::ERR_RENDERINGAPI_ERROR ,
				"显卡不支持pixel Shader." ,
				"OpenGLSupport::setupValidCgProfile");

			return false;
		}

		return true;
	}
	//----------------------------------------------------------------



}// end of namespace vgCore
