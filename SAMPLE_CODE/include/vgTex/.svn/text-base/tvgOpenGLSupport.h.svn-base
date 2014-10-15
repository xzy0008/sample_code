/*
-----------------------------------------------------------------------------
  VRES(Virtual Reality GIS Engine System)    
  -------------------------------------------------------------
  License details ... waiting to add...
  -------------------------------------------------------------
  Copyright  (C) 2007 , leven - All Rights Reserved
-----------------------------------------------------------------------------
*/

#ifndef __TVGOPENGLSUPPORT_H__
#define __TVGOPENGLSUPPORT_H__

#include <vgCore/vgPrerequisites.h>
#include <vgCore/vgWarning.h>
#include <Cg/cg.h>
#include <vgCore/vgException.h>

namespace vgCore {


	/**
		@date 	2007/02/25  14:12	
		@author  leven

		@brief 	OpenGL支持类,包含查询目的机器对Opengl的支持情况.

		此类都为静态函数.

		@see    
	*/
	class OpenGLSupport
	{
	private:
		///声明为private不允许创建.
		OpenGLSupport()
		{

		}
		~OpenGLSupport()
		{

		}
	public:

		//----------------------------------------------------------------
		// 查看机器是否支持压缩纹理.
		inline static bool	checkTextureCompresstionSupport()
		{
			/// 检查显卡是否支持.
			if (!GLEW_ARB_texture_compression)
			{
				VG_WARN(Warning::WARN_INVALID_STATE ,
					Warning::BUTTON_OK ,
					"显卡不支持GLEW_ARB_texture_compression" ,
					"OpenGLSupport::checkTextureCompresstionSupport()");
				return false;
			}
			return true;
		}
		//----------------------------------------------------------------
		inline static bool checkCubeMapSupport()
		{
			if (GLEW_EXT_texture_cube_map)
			{
				return true;
			}
			else
			{
				/*VG_WARN(Warning::WARN_INVALID_STATE ,
					Warning::BUTTON_OK ,
					"显卡不支持GLEW_ARB_CUBE_MAP" ,
					"OpenGLSupport::checkCubeMapSupport()");*/
				std::ostringstream o;
				o << "显卡不支持GLEW_ARB_CUBE_MAP! \n\n";
				VGK_SHOW(o.str());

				return false;
			}
		}
		//----------------------------------------------------------------
		// 查看机器是否支持各异向性过滤.
		inline static bool  checkTextureFilterAnisotropicSupport()
		{
			if ( !GLEW_EXT_texture_filter_anisotropic )
			{
				return false;
			}
			return true;
		}
		//----------------------------------------------------------------
		inline static bool turnOnLargestTexFilterAnisotropic()
		{
			if ( !checkTextureFilterAnisotropicSupport() )
			{
				VG_EXCEPT(Exception::ERR_RENDERINGAPI_ERROR,
					"显卡不支持各异向性过滤.GLEW_EXT_texture_filter_anisotropic is not support." ,
					"OpenGLSupport::checkTextureFilterAnisotropic()");
				return false;
			}
			float fLargest;
			glGetFloatv( GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT , &fLargest );
			glTexParameteri(GL_TEXTURE_2D , GL_TEXTURE_MAX_ANISOTROPY_EXT , fLargest );
			return true;
		}

		//----------------------------------------------------------------
		static bool checkOpenGLErrorThrowException();
		//----------------------------------------------------------------
		static void checkOpenGLErrorThrowException( 
			const String& source , const String& file , const long& line );
		//----------------------------------------------------------------
		static bool checkOpenGLErrorWithoutThrow( String& errMsg );
		//----------------------------------------------------------------
		static void makeErrorStackEmpty();
		//----------------------------------------------------------------


	private:
		
		static const String getOpenGLErrorInfo( const GLenum& errorCode );
	};
	
	
}

#define VG_CHECK_OPENGL_ERROR() vgCore::OpenGLSupport::checkOpenGLErrorThrowException( \
	"", __FILE__, __LINE__ );



#endif // end of __TVGOPENGLSUPPORT_H__