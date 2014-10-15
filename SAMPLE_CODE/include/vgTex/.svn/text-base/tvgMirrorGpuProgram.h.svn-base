




#ifndef __TVGMIRRORGPUPROGRAM_H__
#define __TVGMIRRORGPUPROGRAM_H__







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

	class MirrorGpuProgram : public GpuProgram
	{
	public:
		static char *vertex_source;
		static char *pixel_source;

		static GLenum  FaceTarget[6];

	public:
		MirrorGpuProgram()
		{

			setDefault();
			GpuSupport::checkCgErrorStack();

//			VG_TRACE("MirrorGpuProgram begin");	
		}
		~MirrorGpuProgram()
		{
			GpuSupport::checkCgErrorStack();
			this->destroy();


//			VG_TRACE("MirrorGpuProgram end");	
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

		virtual void useBindEnd();


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

	typedef SharedPtr<MirrorGpuProgram> MirrorGpuProgramPtr;

	
	
	
}// end of namespace vgCore

#endif // end of __TVGMIRRORGPUPROGRAM_H__