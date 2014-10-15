



#ifndef __TVGGLASSGPUPROGRAM_H__
#define __TVGGLASSGPUPROGRAM_H__




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

	class  VGDEP_EXPORT GlassGpuProgram : public GpuProgram
	{
	public:
		static char *vertex_source;
		static char *pixel_source;

		static GLenum  FaceTarget[6];

	public:
		GlassGpuProgram()
		{

			setDefault();
			GpuSupport::checkCgErrorStack();

//			VG_TRACE("GlassGpuProgram begin");	
		}
		~GlassGpuProgram()
		{
			GpuSupport::checkCgErrorStack();
			this->destroy();


//			VG_TRACE("GlassGpuProgram end");	
		}

		void setParametersOnce(	const String& pixelpath ,
			const String& vertexpath , const StringVector& cubeMapPath ,
			const String& waterbumppath  ,
			const String& waterDecalMap , const float& bumpScale = 1.0f)
		{
			assert( !isValid() );
			
			this->mPixelPath = pixelpath;
			this->mVertexPath = vertexpath;

			mCubeMapID = buildCubeMapID(cubeMapPath);
			assert(mCubeMapID != 0);

			//mDecalMapID = buildDecalMapID( waterDecalMap );
			//assert(mDecalMapID != 0 );

			this->mBrightness = bumpScale;

			//mNormalMapID = buildNormalMapID( waterbumppath , mBrightness );

			//assert(mNormalMapID != 0);
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

			//cgGLDisableTextureParameter(
			//	cgGetNamedParameter(mCgPixelProgram, "decalMap") );

			//cgGLDisableTextureParameter(
			//	cgGetNamedParameter(mCgPixelProgram, "normalMap") );

			cgGLDisableTextureParameter(
				cgGetNamedParameter(mCgPixelProgram, "environmentMap") );

			cgGLDisableProfile( mVertexProfile );
			cgGLDisableProfile( mPixelProfile );

			glDisable(GL_BLEND);
			glDisable(GL_TEXTURE_CUBE_MAP);

		}

		void destroy();

		void setDefault()
		{
			mCgPixelProgram = NULL;
			mCgVertexProgram = NULL;

			mNormalMapID = 0;
			mCubeMapID = 0;
			mDecalMapID = 0;

			mBrightness = 1.0f;

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

		float  mBrightness;



	};

	typedef SharedPtr<GlassGpuProgram> GlassGpuProgramPtr;

	
	
	
}// end of namespace vgCore

#endif // end of __TVGGLASSGPUPROGRAM_H__