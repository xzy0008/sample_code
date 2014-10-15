

#ifndef __TVGWATERGPUPROGRAM_H__
#define __TVGWATERGPUPROGRAM_H__

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

	class WaterGpuProgram : public GpuProgram
	{
	public:
			
	static char *vertex_source;
	static char *vertex_source2;
	static char *pixel_source;


	static GLenum  FaceTarget[6] ;


	public:
		WaterGpuProgram()
		{

			setDefault();
			GpuSupport::checkCgErrorStack();

//			VG_TRACE("WaterGpuProgram begin");	
		}
		~WaterGpuProgram()
		{
			GpuSupport::checkCgErrorStack();
			this->destroy();


//			VG_TRACE("WaterGpuProgram end");	
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

			mDecalMapID = buildDecalMapID( waterDecalMap );
			assert(mDecalMapID != 0 );

			this->mBumpScale = bumpScale;

			mNormalMapID = buildNormalMapID( waterbumppath , mBumpScale );

			//mNormalMapID2 = buildNormalMapID( "40.bmp" , mBumpScale );

			assert(mNormalMapID != 0);
		}

		bool init();



		void setParametersEveryFrame( const Vector3& eyePos )
		{
			//this->mTimeLine[0] += 0.0005f;
			//this->mTimeLine[1] += 0.0005f;

			// Edit By FengYK @2010-03-23 通过改变 U、V 的大小改变水流方向
			if ( (_utimeline == 0 && _vtimeline == 0) )
			{
				_utimeline = 50.0;
				_vtimeline = 50.0;
			}

			this->mTimeLine[0] += _utimeline / 100000.0f;
			this->mTimeLine[1] += _vtimeline / 100000.0f;

			this->mEyePosition = eyePos;
		}

		virtual void useBindBegin( );

		virtual void useBindEnd();


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

	public:

		// Add By FengYK @2010-03-23 10:43
		float _utimeline;
		float _vtimeline;

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

		CGparameter g_CGparam_userClipPlaneParam;

		//CGparameter g_CGparam_modeViewMat;
	};

	typedef SharedPtr<WaterGpuProgram> WaterGpuProgramPtr;

	
	
	
}// end of namespace vgCore

#endif // end of __TVGWATERGPUPROGRAM_H__