
#include <vgStableHeaders.h>
#include <vgStableHeaders.h>
#include <vgTex/tvgOpenGLSupport.h>


namespace vgCore {
	
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

			VG_EXCEPT(Exception::ERR_RENDERINGAPI_ERROR,
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
			StringUtil::trim(buf ,false, true);

			std::ostringstream desc;

			desc <<  "- OpenGL Error: " <<  buf
				<< "\n in " << source;

			if( line > 0 )
			{
				desc << " at " << file << " (line " << line << ")\n\n\n";
			}

			desc << "Error Description: " 
				<< getOpenGLErrorInfo( errorCode );


			VG_EXCEPT(Exception::ERR_RENDERINGAPI_ERROR,
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




}// end of namespace vgCore
