



#ifndef __TVGBillGpuProgram_H__
#define __TVGBillGpuProgram_H__




#include <vgCore/vgPrerequisites.h>
#include <vgCore/vgSharedPtr.h>
#include <vgTex/tvgGpuSupport.h>
#include <vgTex/tvgGpuProgram.h>
#include <vgTex/tvgGpuManager.h>

namespace vgCore {

	/**
	@date 	2007/05/14  21:22	
	@author  Leven

	@brief 	BILLµÄGPUµÄÀà¡£

	@see    
	*/

	class  VGDEP_EXPORT BillGpuProgram : public GpuProgram
	{
	public:
		static char *vertex_source;
		static char *pixel_source;

		static GLenum  FaceTarget[6];

	public:
		BillGpuProgram()
		{

			setDefault();
			GpuSupport::checkCgErrorStack();

			//			VG_TRACE("BillGpuProgram begin");	
		}
		~BillGpuProgram()
		{
			GpuSupport::checkCgErrorStack();
			this->destroy();


			//			VG_TRACE("BillGpuProgram end");	
		}

		bool init();



		void setParametersEveryFrame( const Vector3& eyePos )
		{
			this->mEyePosition = eyePos;
		}

		void useBindBegin( );

		virtual void useBindEnd()
		{
			//////////////////////////////////////////////////////////////////////////
			//cgGLDisableTextureParameter(
			//	cgGetNamedParameter(mCgPixelProgram, "normalMap2") );
			//////////////////////////////////////////////////////////////////////////

// 			cgGLDisableTextureParameter(
// 				cgGetNamedParameter(mCgPixelProgram, "environmentMap") );
			cgGLDisableTextureParameter(
				cgGetNamedParameter(mCgPixelProgram, "decalMap") );

			cgGLDisableProfile( mVertexProfile );
			cgGLDisableProfile( mPixelProfile );

// 			glDisable(GL_BLEND);
// 			glDisable(GL_TEXTURE_CUBE_MAP);

		}

		void destroy();

		void setDefault()
		{
			mCgPixelProgram = NULL;
			mCgVertexProgram = NULL;

		}


	public:


		Vector3 mEyePosition;

		CGprofile mVertexProfile;
		CGprofile mPixelProfile;

		CGprogram mCgPixelProgram;
		CGprogram mCgVertexProgram;

		GpuSupportPtr mSupportPtr;

		String mPixelPath;
		String mVertexPath;


		GLuint mCubeMapID;
		GLuint mNormalMapID;

		//GLuint mNormalMapID2;

		GLuint mDecalMapID;

		float  mBrightness;



	};

	typedef SharedPtr<BillGpuProgram> BillGpuProgramPtr;




}// end of namespace vgCore

#endif // end of __TVGBillGpuProgram_H__