

#ifndef __TVGGPUSUPPORT_H__
#define __TVGGPUSUPPORT_H__

#include <vgCore/vgPrerequisites.h>
#include <vgCore/vgSharedPtr.h>
#include <vgTex/tvgOpenGLSupport.h>

#include <vgKernel/vgkTrace.h>
#include <Cg/cgGL.h>

namespace vgCore {


	class GpuContext
	{
	public:
		GpuContext()
		{
			setParametersDefault();

			initialise();

			VGK_TRACE("GpuContext constructed");
		}
		~GpuContext()
		{
			uninitialise();
			VGK_TRACE("GpuContext destroyed");
		}

		CGcontext getContext()
		{
			return mCgContext;
		}

	private:

		bool initialise()
		{
			mCgContext = cgCreateContext();

			assert( mCgContext != NULL );

			mInitialised = true;

			return true;
		}

		bool uninitialise()
		{
			assert( mInitialised == true );

			cgDestroyContext( mCgContext );
			mInitialised = false;

			return true;
		}

		void setParametersDefault()
		{
			mInitialised = false;
			mCgContext = NULL;
		}
		



	private:

		bool mInitialised;
		CGcontext   mCgContext;

	};

	typedef SharedPtr<GpuContext> GpuContextPtr;

	/**
		@date 	2007/05/10  10:18	
		@author  Leven
	
		@brief 	
	
		@see    
	*/
	class GpuSupport
	{
	public:
		GpuSupport()
		{
			if( OpenGLSupport::checkCubeMapSupport() == false )
			{
				//VG_EXCEPT(Exception::ERR_RENDERINGAPI_ERROR ,
				//	"机器不支持CubeMap!" ,
				//	"GpuSupport::GpuSupport()");
			}

			setParametersDefault();
			
			setupCgErrorCallback();

			setupValidCgProfile( mVertexProfile , mPixelProfile );

			mGpuContextPtr.bind( new GpuContext );

			mInitialised = true;
		}
		~GpuSupport()
		{

		}

		inline CGprofile getVertexProfile() 
		{
			assert( isValid() );
			return mVertexProfile;
		}

		inline CGprofile getPixelProfile() 
		{
			assert( isValid() );
			return mPixelProfile;
		}

		inline GpuContextPtr getGpuContextPtr()
		{
			assert(isValid());
			return this->mGpuContextPtr;
		}

	//private:

		static bool setupValidCgProfile( CGprofile& vertex_profile ,
			CGprofile& pixel_profile );


		//----------------------------------------------------------------
		static bool setupCgErrorCallback()
		{
			cgSetErrorCallback( checkCgErrorStack );
			return true;
		}
		//----------------------------------------------------------------
		static void checkCgErrorStack()
		{
			CGerror error = cgGetError();

			if ( error == CG_NO_ERROR)
			{
				return;
			}

			// when error occured.
			const char* errStr = cgGetErrorString( error );

			string msg("Cg rendering API error occured.Message: ");
			msg += errStr;

			VG_EXCEPT(Exception::ERR_RENDERINGAPI_ERROR,
				msg, "OpenGLSupport::checkCgErrorStack");

			return;
		}

	private:
	
		void setParametersDefault()
		{
			mInitialised = false;

			mPixelProfile = CG_PROFILE_UNKNOWN;
			mVertexProfile = CG_PROFILE_UNKNOWN;

#ifdef _DEBUG
			cgGLSetDebugMode( CG_TRUE );  // Enables debug mode
#else
			cgGLSetDebugMode( CG_FALSE ); // Disables debug mode
#endif
		}

		bool isValid() 
		{
			return mInitialised;
		}

	private:

		bool	mInitialised;

		CGprofile   mVertexProfile;
		CGprofile   mPixelProfile;

		GpuContextPtr mGpuContextPtr;
	};
	
	
	typedef SharedPtr<GpuSupport> GpuSupportPtr;
	
}// end of namespace vgCore

#endif // end of __TVGGPUSUPPORT_H__