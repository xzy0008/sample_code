



#ifndef __VGFRAMEBUFFER_H__
#define __VGFRAMEBUFFER_H__

#include <vgCore/vgPrerequisites.h>


namespace vgCore {

	/**
		@date 	2008/03/13  11:00	
		@author  leven
	
		@brief 	
	
		@see    
	*/
	class  VGDEP_EXPORT FrameBuffer
	{
	public:
		FrameBuffer( int width , int height );
		~FrameBuffer();


		bool create();

		void bind();

		void unbind();

		void destroy()
		{
			assert( isValid() );
			glDeleteTextures( 1, &g_dynamicTextureID );
			glDeleteTextures( 1, &g_dynamicDepthTextureID);
			glDeleteFramebuffersEXT( 1, &g_frameBuffer );
			glDeleteRenderbuffersEXT( 1, &g_depthRenderBuffer );
		}

	private:

		bool check_extension();

		bool isValid()
		{
			return m_IsValid ;
		}

		void check_buffer_status();

		//private:
	public:

		GLuint g_frameBuffer;
		GLuint g_depthRenderBuffer;

		GLuint g_dynamicTextureID;

		GLuint g_dynamicDepthTextureID;

		bool m_IsValid;

		int RENDERBUFFER_WIDTH ;
		int RENDERBUFFER_HEIGHT;
	};
	
	
	
	
}// end of namespace vgCore

#endif // end of __VGFRAMEBUFFER_H__