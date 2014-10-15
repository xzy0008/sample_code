


#ifndef __TVGMETALGPUPROGRAM_H__
#define __TVGMETALGPUPROGRAM_H__




#include <vgCore/vgPrerequisites.h>
#include <vgCore/vgSharedPtr.h>
#include <vgTex/tvgGpuSupport.h>
#include <vgTex/tvgGpuProgram.h>
#include <vgTex/tvgGpuManager.h>

namespace vgCore {

	/**
		@date 	2007/05/14  21:22	
		@author  Leven
	
		@brief 	水的GPU的类。
	
		@see    
	*/

	class MetalGpuProgram : public GpuProgram
	{
	public:
			
	static char *vertex_source;
	static char *pixel_source;


	static GLenum  FaceTarget[6] ;


	public:
		MetalGpuProgram()
		{

			setDefault();
			GpuSupport::checkCgErrorStack();

//			VG_TRACE("MetalGpuProgram begin");	
		}
		~MetalGpuProgram()
		{
			GpuSupport::checkCgErrorStack();
			this->destroy();


//			VG_TRACE("MetalGpuProgram end");	
		}

		void setParametersOnce(	const String& pixelpath ,
			const String& vertexpath , const StringVector& cubeMapPath ,
			const String& waterbumppath  ,
			const String& waterDecalMap , const float& bumpScale = 1.0f);

		bool init();



		void setParametersEveryFrame( const Vector3& eyePos )
		{
			this->mEyePosition = eyePos;
		}

		void useBindBegin( )
		{
			glDisable(GL_TEXTURE_2D);
			glEnable(GL_TEXTURE_CUBE_MAP);

			glTexGeni( GL_S , GL_TEXTURE_GEN_MODE , GL_REFLECTION_MAP );
			glTexGeni( GL_T , GL_TEXTURE_GEN_MODE , GL_REFLECTION_MAP );
			glTexGeni( GL_R , GL_TEXTURE_GEN_MODE , GL_REFLECTION_MAP );

			glEnable( GL_TEXTURE_GEN_S );
			glEnable( GL_TEXTURE_GEN_T );
			glEnable( GL_TEXTURE_GEN_R );


			cgGLSetParameter3fv(
				cgGetNamedParameter(mCgVertexProgram, "eyePosition"), 
				mEyePosition.v );

			cgGLSetTextureParameter(
				cgGetNamedParameter( mCgPixelProgram, "normalMap"), 
				mNormalMapID );



			//////////////////////////////////////////////////////////////////////////

			//cgGLSetTextureParameter(
			//	cgGetNamedParameter( mCgPixelProgram, "normalMap2"), 
			//	mNormalMapID2 );
			//////////////////////////////////////////////////////////////////////////

			cgGLSetTextureParameter(
				cgGetNamedParameter( mCgPixelProgram, "environmentMap"), 
				mCubeMapID );

			//cgGLSetTextureParameter(
			//	cgGetNamedParameter( mCgPixelProgram, "decalMap"), 
			//	mDecalMapID );


			cgGLEnableProfile( mVertexProfile );
			cgGLEnableProfile( mPixelProfile );

			cgGLBindProgram( mCgPixelProgram );
			cgGLBindProgram( mCgVertexProgram );

			cgGLEnableTextureParameter(
				cgGetNamedParameter(mCgPixelProgram, "normalMap") );
			//////////////////////////////////////////////////////////////////////////
			//cgGLEnableTextureParameter(
			//	cgGetNamedParameter(mCgPixelProgram, "normalMap2") );
			//////////////////////////////////////////////////////////////////////////

			cgGLEnableTextureParameter(
				cgGetNamedParameter(mCgPixelProgram, "environmentMap") );

			//cgGLEnableTextureParameter(
			//	cgGetNamedParameter(mCgPixelProgram, "decalMap") );



		}

		virtual void useBindEnd()
		{
			//////////////////////////////////////////////////////////////////////////
			//cgGLDisableTextureParameter(
			//	cgGetNamedParameter(mCgPixelProgram, "normalMap2") );
			//////////////////////////////////////////////////////////////////////////

			//cgGLDisableTextureParameter(
			//	cgGetNamedParameter(mCgPixelProgram, "decalMap") );

			cgGLDisableTextureParameter(
				cgGetNamedParameter(mCgPixelProgram, "normalMap") );

			cgGLDisableTextureParameter(
				cgGetNamedParameter(mCgPixelProgram, "environmentMap") );

			cgGLDisableProfile( mVertexProfile );
			cgGLDisableProfile( mPixelProfile );

			glDisable( GL_TEXTURE_GEN_S );
			glDisable( GL_TEXTURE_GEN_T );
			glDisable( GL_TEXTURE_GEN_R );


			glDisable(GL_TEXTURE_CUBE_MAP);

			glEnable(GL_TEXTURE_2D);
		}


		void destroy();

		void setDefault()
		{
			mCgPixelProgram = NULL;
			mCgVertexProgram = NULL;

			mNormalMapID = 0;
			mCubeMapID = 0;
			mDecalMapID = 0;

			mBumpScale = 1.0f;

			mTimeLine[0] = 0.01f;
			mTimeLine[1] = 0.01f;
		}

	private:


		static GLuint buildCubeMapID( const StringVector& strVec );

		static GLuint buildNormalMapID( const String& normalmap , const float& bump );

		static GLuint buildDecalMapID( const String& decalmap );

		inline static uint getHeight(uchar* buf, const int& sizex , const uint& x,const uint& y )
		{
			const int& _sizeX = sizex;
			unsigned int _imagepos = _sizeX  * x * 3 + y * 3;

			unsigned int theight = buf[ _imagepos ]
			+ buf[ _imagepos + 1 ]
			+ buf[ _imagepos + 2 ];

			unsigned int result = theight/3;
			assert(result < 256);
			return result;
		}

		static bool buildFaceTextureUsingGDI( const String& filename , GLenum target );
	private:


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

		float  mBumpScale;

		float  mTimeLine[2];

	};

	typedef SharedPtr<MetalGpuProgram> MetalGpuProgramPtr;

	
	
	
}// end of namespace vgCore

#endif // end of __TVGMETALGPUPROGRAM_H__