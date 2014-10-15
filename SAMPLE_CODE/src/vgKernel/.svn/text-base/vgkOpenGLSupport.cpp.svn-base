



#include <vgStableHeaders.h>
#include <vgKernel/vgkWarning.h>
#include <vgKernel/vgkException.h>
#include <vgKernel/vgkOpenGLSupport.h>
#include <vgKernel/vgkStringUtility.h>



namespace vgKernel {
	
	
	//----------------------------------------------------------------
	const String OpenGLSupport::getOpenGLErrorInfo( const GLenum& errorCode )
	{
		switch( errorCode )
		{
		case GL_NO_ERROR:
			return "没有错误出现.\nNo error has been recorded. The value of this symbolic constant is guaranteed to be zero. ";

		case GL_INVALID_ENUM:
			return "枚举参数超出范围.\nAn unacceptable value is specified for an enumerated argument. The offending function is ignored, having no side effect other than to set the error flag. ";

		case GL_INVALID_VALUE:
			return "数值参数超出范围.\nA numeric argument is out of range. The offending function is ignored, having no side effect other than to set the error flag. ";

		case GL_INVALID_OPERATION :
			return "在当前的状态中操作非法.\nThe specified operation is not allowed in the current state.The offending function is ignored, having no side effect other than to set the error flag. ";

		case GL_STACK_OVERFLOW:
			return "这条命令将导致堆栈上溢.\nThis function would cause a stack overflow. The offending function is ignored, having no side effect other than to set the error flag. ";

		case GL_STACK_UNDERFLOW:
			return "这条命令将导致堆栈下溢.\nThis function would cause a stack underflow.The offending function is ignored, having no side effect other than to set the error flag. ";

		case GL_OUT_OF_MEMORY:
			return "没有足够的内存来执行这条命令.\nThere is not enough memory left to execute the function.The state of OpenGL is undefined, except for the state of the error flags, after this error is recorded.";

		case GL_TABLE_TOO_LARGE:
			return "制定的表太大.\nThe specified table exceeds the implementation's maximum supported table size.GL_TABLE_TOO_LARGE was introduced in GL version 1.2. ";

		default:
			return "未知的OpenGL API错误形式!\nUnkown OpenGL Error Type!";
		}
	}

	bool OpenGLSupport::checkOpenGLErrorThrowException()
	{
		const GLenum& errorCode = glGetError();

		if ( GL_NO_ERROR == errorCode )
		{
			return false;
		}
		else
		{
			// means there is error.

			const uchar* str = gluErrorString( errorCode );

			char buffer[2048];

			sprintf(buffer, "Error Message : %s\n", str);

			VGK_EXCEPT(Exception::ERR_RENDERINGAPI_ERROR,
				"OpenGL API 调用错误:" + String(buffer) +
				"Error Description: " + getOpenGLErrorInfo( errorCode ),
				"OpenGLSupport::checkOpenGLError()");


			return true;
		}
	}

	void OpenGLSupport::checkOpenGLErrorThrowException( const String& source , const String& file , const long& line )
	{
		const GLenum& errorCode = glGetError();

		if ( GL_NO_ERROR == errorCode )
		{
			return;
		}
		else
		{
			// means there is error.

			const uchar* str = gluErrorString( errorCode );
			char buffer[200];
			sprintf(buffer, "Error Message : %s\n", str);

			String buf(buffer);
			StringUtility::trim(buf ,false, true);

			std::ostringstream desc;

			desc <<  "- OpenGL Error: " <<  buf
				<< "\n in " << source;

			if( line > 0 )
			{
				desc << " at " << file << " (line " << line << ")\n\n\n";
			}

			desc << "Error Description: " 
				<< getOpenGLErrorInfo( errorCode );

#if _DEBUG
			//::MessageBox( NULL ,  desc.str().c_str() , "OpenGL运行时错误!" , MB_OK );
#endif

			VGK_EXCEPT(Exception::ERR_RENDERINGAPI_ERROR,
				desc.str(),
				"OpenGLSupport::checkOpenGLError()");
		}
	}

	bool OpenGLSupport::checkOpenGLErrorWithoutThrow( String& errMsg )
	{
		const GLenum& errorCode = glGetError();

		if ( GL_NO_ERROR == errorCode )
		{
			return false;
		}
		else
		{
			// means there is error.

			const uchar* str = gluErrorString( errorCode );

			char buffer[200];

			sprintf(buffer, "Error Message : %s\n", str);

			errMsg = buffer ;
			errMsg += "Error Description: " + getOpenGLErrorInfo( errorCode );
			return true;
		}
	}

	void OpenGLSupport::makeErrorStackEmpty()
	{
		GLenum errorCode;

		do 
		{
			errorCode = glGetError();
		} 
		while( GL_NO_ERROR != errorCode );

		return ;
	}
	//----------------------------------------------------------------
	bool OpenGLSupport::checkTextureCompresstionSupport()
	{
		/// 检查显卡是否支持.
		if (!GLEW_ARB_texture_compression)
		{
			VGK_WARN(Warning::WARN_INVALID_STATE ,
				Warning::BUTTON_OK ,
				"显卡不支持GLEW_ARB_texture_compression" ,
				"OpenGLSupport::checkTextureCompresstionSupport()");
			return false;
		}
		return true;
	}
	//----------------------------------------------------------------
	bool OpenGLSupport::checkCubeMapSupport()
	{
		if (GLEW_EXT_texture_cube_map)
		{
			return true;
		}
		else
		{
			VGK_WARN(Warning::WARN_INVALID_STATE ,
				Warning::BUTTON_OK ,
				"显卡不支持CUBE_MAP扩展" ,
				"OpenGLSupport::checkCubeMapSupport()");

			return false;
		}
	}
	//----------------------------------------------------------------
	bool OpenGLSupport::checkTextureFilterAnisotropicSupport()
	{
		if ( !GLEW_EXT_texture_filter_anisotropic )
		{
			return false;
		}
		return true;
	}
	//----------------------------------------------------------------
	bool OpenGLSupport::turnOnLargestTexFilterAnisotropic()
	{
		if ( !checkTextureFilterAnisotropicSupport() )
		{
			VGK_EXCEPT(Exception::ERR_RENDERINGAPI_ERROR,
				"显卡不支持各异向性过滤.GLEW_EXT_texture_filter_anisotropic is not support." ,
				"OpenGLSupport::checkTextureFilterAnisotropic()");
			return false;
		}
		float fLargest;
		glGetFloatv( GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT , &fLargest );
		glTexParameteri(GL_TEXTURE_2D , GL_TEXTURE_MAX_ANISOTROPY_EXT , (GLint)fLargest );
		return true;
	}
	//----------------------------------------------------------------
	bool OpenGLSupport::initialiseOpenGLExtension()
	{
		VGK_TRACE( "OpenGLSupport::initialiseOpenGLExtension()" );
		GLenum err = glewInit();
		if (GLEW_OK != err)
		{
			/* Problem: glewInit failed, something is seriously wrong. */
			//::MessageBox(NULL,"glewInit failed, something is seriously wrong.",
			//	"glew error occured.",MB_OK );
			vgKernel::SystemUtility::showModelDialog(
				"glewInit failed, something is seriously wrong.");

			return false;
		}


		VGK_TRACE( "glewInit init ok" );

		double verison = 2.1;

		if ( GLEW_VERSION_2_1 )
		{
			verison = 2.1;
		}
		else if ( GLEW_VERSION_2_0 )
		{
			verison = 2.0;
		}
		else if ( GLEW_VERSION_1_5 )
		{
			verison = 1.5;
		}
		else if ( GLEW_VERSION_1_4 )
		{
			verison = 1.4;
		}
		else if ( GLEW_VERSION_1_3 )
		{
			verison = 1.3;
		}
		else if ( GLEW_VERSION_1_2 )
		{
			verison = 1.2;
		}
		else if ( GLEW_VERSION_1_1 )
		{
			verison = 1.1;
		}
		else
		{
			verison = 0.0;
		}

		if ( verison < 2.0 )
		{
#if VGK_LANG_CHS
			std::ostringstream o;
			o <<"显卡只支持OpenGL版本:" << verison << "\n";
			o << getOpenGLDetails();
			
			VGK_TRACE( o.str() );
			MessageBox( NULL , o.str().c_str() , "提示" , MB_OK );
#else
			std::ostringstream o;
			o <<"VR-GIS platform do not support the Graphic card, OpenGL version:" << verison << "\n";
			o << getOpenGLDetails();

			VGK_TRACE( o.str() );
			MessageBox( NULL , o.str().c_str() , "Tips" , MB_OK );
#endif
		}
		else
		{
			std::ostringstream o;
			o <<"显卡支持OpenGL版本:" << verison << "\n";
			o << getOpenGLDetails();

			VGK_TRACE( o.str() );
		}



		return true;
	}
	//----------------------------------------------------------------
	String OpenGLSupport::getOpenGLDetails()
	{
		std::ostringstream o;

		o << "OpenGL vendor:" << glGetString(GL_VENDOR)
		 << "\nOpenGL renderer:"<< glGetString(GL_RENDERER)
		 << "\nOpenGL version:"<<  glGetString(GL_VERSION)
		 << "\nOpenGL extensions:"
		<< (char*)glGetString(GL_EXTENSIONS);

		return o.str();
	}
	//----------------------------------------------------------------

	
}// end of namespace vgKernel
