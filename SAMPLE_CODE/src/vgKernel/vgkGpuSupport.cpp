

#include <vgStableHeaders.h>
#include <vgKernel/vgkGpuSupport.h>


namespace vgKernel {
	
	//----------------------------------------------------------------
	GpuSupport::GpuSupport()
	{
		//------------------------------------------
		// 设定默认的参数
		//------------------------------------------
		_cubeMapSupported = OpenGLSupport::checkCubeMapSupport();
		_vertexTextureFetchSupported = false;

		_pixelProfile = CG_PROFILE_UNKNOWN;
		_vertexProfile = CG_PROFILE_UNKNOWN;

		_gpuContext = new GpuContext;

#ifdef _DEBUG
		cgGLSetDebugMode( CG_TRUE );  // Enables debug mode
#else
		cgGLSetDebugMode( CG_FALSE ); // Disables debug mode
#endif

		//------------------------------------------
		// 设定回调函数.
		//------------------------------------------
		cgSetErrorCallback( checkCgErrorStack );


		//------------------------------------------
		// 查找最新的Profile
		//------------------------------------------
		setupValidCgProfile( _vertexProfile , _pixelProfile );


		//------------------------------------------
		// 设置vtf参数
		//------------------------------------------
		_vertexTextureFetchSupported = (_vertexProfile == CG_PROFILE_VP40);

	}
	//----------------------------------------------------------------
	GpuSupport::~GpuSupport()
	{
		if ( _gpuContext != NULL )
		{
			delete _gpuContext;
			_gpuContext = NULL;
		}
	}
	//----------------------------------------------------------------
	void GpuSupport::checkCgErrorStack()
	{
		CGerror error = cgGetError();

		if ( error == CG_NO_ERROR)
		{
			return;
		}

		// when error occured.
		const char* errStr = cgGetErrorString( error );

		String msg("Cg rendering API error occured.Message: ");
		msg += errStr;

		VGK_EXCEPT(Exception::ERR_RENDERINGAPI_ERROR,
			msg, "GpuSupport::checkCgErrorStack");

		return;
	}
	//----------------------------------------------------------------

	
	//----------------------------------------------------------------
	GpuContext::GpuContext()
	{
		_CgContext = NULL;

		_CgContext = cgCreateContext();

		assert( _CgContext != NULL );

		VGK_TRACE("GpuContext constructed");
	}
	//----------------------------------------------------------------
	GpuContext::~GpuContext()
	{
		if ( _CgContext != NULL )
		{
			cgDestroyContext( _CgContext );
			_CgContext = NULL;
		}

		VGK_TRACE("GpuContext destroyed");
	}
	//----------------------------------------------------------------
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
			VGK_EXCEPT(Exception::ERR_RENDERINGAPI_ERROR ,
				"显卡不支持Vertex Shader." ,
				"GpuSupport::setupValidCgProfile");
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
			VGK_EXCEPT(Exception::ERR_RENDERINGAPI_ERROR ,
				"显卡不支持pixel Shader." ,
				"GpuSupport::setupValidCgProfile");

			return false;
		}

		return true;
	}
	//----------------------------------------------------------------


}// end of namespace vgKernel
