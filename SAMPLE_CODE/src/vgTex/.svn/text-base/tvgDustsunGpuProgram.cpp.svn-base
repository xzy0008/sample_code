
#include <vgStableHeaders.h>
#include <vgTex/tvgGpuProgram.h>

#include <vgTex/tvgDustsunGpuProgram.h>
#include <vgTex/tvgOpenGLSupport.h>

#include <vgKernel/vgkPluginManager.h>
#include <vgTerritory/vgtDefinition.h>
#include <olectl.h>

namespace vgCore {
	

 	char *DustsunGpuProgram::vertex_source = "\
 		uniform float4x4 modelViewProj : state.matrix.mvp;\
 		void main(\
 		float4 in_position	:   POSITION ,\
 		float2 texCoord : TEXCOORD0,\
 		out  float4 oPosition  : POSITION,\
 		out float2 TexCoordorigin  : TEXCOORD0,\
 		out float2 TexCoorddust    : TEXCOORD1,\
 		out float  clip0    : CLP0,\
 		uniform float4 userClipPlaneParam )\
 	{\
 		oPosition = mul( modelViewProj, in_position );\
 		TexCoordorigin  = texCoord;\
 		TexCoorddust    = texCoord;\
 		clip0 = dot( in_position, userClipPlaneParam );\
 	}";
 
 	char *DustsunGpuProgram::pixel_source = "\
 											void main(\
 											float2 TexCoordorigin  : TEXCOORD0,\
 											float2 TexCoorddust    : TEXCOORD1,\
 											out float4 color : COLOR,\
 											uniform sampler2D decalID,\
											uniform sampler2D dustsunID,\
											uniform sampler2D lastsunID,\
 											uniform float ratio)\
 	{\
 		float4 originColor  = tex2D(decalID, TexCoordorigin);\
		float4 dustColor = tex2D(dustsunID, TexCoorddust);\
		float4 lastColor = tex2D( lastsunID, TexCoorddust);\
		if( ratio >= 0 && ratio <= 0.5)\
		color = originColor * (1.0 -2.0 * ratio) + dustColor *(ratio*2.0); \
		else\
		color = dustColor * (2.0 - 2.0*ratio) + lastColor * (ratio *2.0 - 1.0 );\
 	}";


	bool DustsunGpuProgram::buildFaceTextureUsingGDI( const string& filename , GLenum target )
	{

		FileInfoPtr pfile = ArchiveManager::getSingleton().getFileInfo( filename );

		if ( pfile.isNull() )
		{
			assert(0 && "no file");
			return false;
		}

		NormalImagePtr pimg = ImageFactory::createNormalImagePtr();

		bool ret = pimg->loadFromFileInfo( pfile);

		if ( ret == false )
		{
			assert(0);
		}

		pimg->buildTextureByGLEnum( target );

		//没有用，但是这样可以用于保存纹理。
		TextureManager::getSingleton().addTexturePtr( filename );

		return true;
	}

		bool DustsunGpuProgram::init()
		{
			GpuManager& gpuMgr = GpuManager::getSingleton();
			mSupportPtr = gpuMgr.getGpuSupportPtr();

			this->mVertexProfile = mSupportPtr->getVertexProfile();
			this->mPixelProfile = mSupportPtr->getPixelProfile();


			mIsValid = true;

			try
			{
				/// 初始化CGprogram程序
				mCgVertexProgram = 	cgCreateProgram( 
					mSupportPtr->getGpuContextPtr()->getContext(),
					CG_SOURCE,
					vertex_source,
					mVertexProfile,
					NULL, NULL );
			}
			catch (...)
			{
				assert(0);
			}

			GpuSupport::checkCgErrorStack();

			mCgPixelProgram = 	cgCreateProgram( 
				mSupportPtr->getGpuContextPtr()->getContext(),
				CG_SOURCE,
				pixel_source,
				mPixelProfile,
				NULL, NULL );

			GpuSupport::checkCgErrorStack();

			cgGLLoadProgram( mCgVertexProgram );

			GpuSupport::checkCgErrorStack();

			cgGLLoadProgram( mCgPixelProgram );

			GpuSupport::checkCgErrorStack();


			g_CGparam_userClipPlaneParam = 
				cgGetNamedParameter( mCgVertexProgram , "userClipPlaneParam");

			return true;
		}
		//----------------------------------------------------------------
		GLuint DustsunGpuProgram::buildDecalMapID( const String& decalmap )
		{
			GLuint textureID = 0;

			OpenGLSupport::makeErrorStackEmpty();

			glGenTextures(1, &textureID);
			glBindTexture(GL_TEXTURE_2D, textureID);

			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

			VG_CHECK_OPENGL_ERROR();

			if ( !buildFaceTextureUsingGDI( decalmap , GL_TEXTURE_2D ) )
			{
				assert(0 && " DECALMAP图像载入失败! ");
			}

			return textureID;
		}

		void DustsunGpuProgram::destroy()
		{
			GpuSupport::checkCgErrorStack();
			if ( mCgPixelProgram != NULL )
			{
				cgDestroyProgram(mCgPixelProgram);
				GpuSupport::checkCgErrorStack();
				mCgPixelProgram = NULL;
			}

			if ( mCgVertexProgram != NULL )
			{
				cgDestroyProgram(mCgVertexProgram);
				GpuSupport::checkCgErrorStack();
				mCgVertexProgram = NULL;
			}

			//------------------------------------------
			// 删除纹理
			//------------------------------------------
			// make sure there is no error msg
			OpenGLSupport::makeErrorStackEmpty();
			String errMessage;

			if ( mDecalMapID != 0 )
			{
				glDeleteTextures( 1 , &mDecalMapID );
				mDecalMapID = 0;
			}

			if ( mLastsunMapID != 0 )
			{
				glDeleteTextures( 1 , &mLastsunMapID );
				mLastsunMapID = 0;
			}

			if ( mDustsunMapID != 0 )
			{
				glDeleteTextures( 1 , &mDustsunMapID );
				mDustsunMapID = 0;
			}


			if( OpenGLSupport::checkOpenGLErrorWithoutThrow( errMessage ) )
			{
				VG_EXCEPT(Exception::ERR_RENDERINGAPI_ERROR ,
					"glDeleteTextures failed! Error Code: " + errMessage ,
					"Texture::deleteTexture()");

				return;
			}

			setDefault();
		}

		void DustsunGpuProgram::useBindBegin()
		{
			cgGLSetTextureParameter(
				cgGetNamedParameter( mCgPixelProgram, "decalID"), 
				mDecalMapID );

 			cgGLSetTextureParameter(
 				cgGetNamedParameter( mCgPixelProgram, "dustsunID"), 
 				mDustsunMapID );

			cgGLSetTextureParameter(
				cgGetNamedParameter( mCgPixelProgram, "lastsunID"),
				mLastsunMapID);

 			
 			cgGLSetParameter1f(
 				cgGetNamedParameter( mCgPixelProgram, "ratio"), 
 				m_ratio );

			cgGLEnableProfile( mVertexProfile );
			cgGLEnableProfile( mPixelProfile );

			cgGLBindProgram( mCgPixelProgram );
			cgGLBindProgram( mCgVertexProgram );

			cgGLEnableTextureParameter(
				cgGetNamedParameter(mCgPixelProgram, "decalID") );

 			cgGLEnableTextureParameter(
 				cgGetNamedParameter(mCgPixelProgram, "dustsunID") );

			cgGLEnableTextureParameter(
				cgGetNamedParameter(mCgPixelProgram, "lastsunID") );

 			float* clip_param = NULL;
 
 
 			using namespace vgKernel;
 			Plugin* plg = PluginManager::getSingleton().getPluginRef( VGT_DLL_NAME );
 
 			pfnTerrainManager_getUserClipPlaneParam  func = NULL;
 
 			if ( plg != NULL )
 			{
 				func = ( pfnTerrainManager_getUserClipPlaneParam )plg->getProcAddr(
 					"TerrainManager_getUserClipPlaneParam" );
 			}
 
 			if ( func != NULL )
 			{
 				clip_param = (*func)();
 			}
 			//vgPlugin::TerritoryUtility::getUserClipPlanelParam();
 			//vgTerritory::TerrainManager::getSingleton().getUserClipPlaneParam();
 
 			if ( clip_param != NULL )
 			{
 				cgGLSetParameter4fv( g_CGparam_userClipPlaneParam , clip_param );
 			}
 			else
 			{
 				GLfloat param[4];
 				param[0] = 1.0f;
 				param[1] = 1.0f;
 				param[2] = 1.0f;
 				param[3] = 1.0f;
 
 				cgGLSetParameter4fv( g_CGparam_userClipPlaneParam , param );
 			}
		}

		void DustsunGpuProgram::useBindEnd()
		{
			cgGLDisableTextureParameter(
				cgGetNamedParameter(mCgPixelProgram, "decalID") );

 			cgGLDisableTextureParameter(
 				cgGetNamedParameter(mCgPixelProgram, "dustsunID") );

			cgGLDisableTextureParameter(
				cgGetNamedParameter(mCgPixelProgram, "lastsunID") );
// // 
// 			cgGLDisableTextureParameter(
// 				cgGetNamedParameter(mCgPixelProgram, "ratio") );

			cgGLDisableProfile( mVertexProfile );
			cgGLDisableProfile( mPixelProfile );
		}
		//----------------------------------------------------------------










}// end of namespace vgCore
