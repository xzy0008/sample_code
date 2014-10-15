


#ifndef __VGKOPENGLSUPPORT_H__
#define __VGKOPENGLSUPPORT_H__

#include <vgKernel/vgkForward.h>

	
namespace vgKernel {

	/**
		@date 	2007/02/25  14:12	
		@author  xy

		@brief 	OpenGL支持类,包含查询目的机器对Opengl的支持情况.

		此类都为静态函数.

		@see    
	*/
	class VGK_EXPORT  OpenGLSupport
	{
	private:
		OpenGLSupport()
		{

		}
	public:

		~OpenGLSupport()
		{

		}
	public:

		static bool initialiseOpenGLExtension();

		// 查看机器是否支持压缩纹理.
		static bool	checkTextureCompresstionSupport();

		static bool checkCubeMapSupport();

		// 查看机器是否支持各异向性过滤.
		static bool  checkTextureFilterAnisotropicSupport();

		// 开启各异向性过滤.
		static bool turnOnLargestTexFilterAnisotropic();

		static bool checkOpenGLErrorThrowException();

		static void checkOpenGLErrorThrowException( 
			const String& source , const String& file , const long& line );

		static bool checkOpenGLErrorWithoutThrow( String& errMsg );

		static void makeErrorStackEmpty();


		static String getOpenGLDetails();

	private:
		
		static const String getOpenGLErrorInfo( const GLenum& errorCode );
	};
	
	
}// end of namespace vgKernel


#if _DEBUG
	#define VGK_CHECK_OPENGL_ERROR() vgKernel::OpenGLSupport::checkOpenGLErrorThrowException( \
		"", __FILE__, __LINE__ );
#else
	#define VGK_CHECK_OPENGL_ERROR() 
#endif


	
	

	


#endif // end of __VGKOPENGLSUPPORT_H__