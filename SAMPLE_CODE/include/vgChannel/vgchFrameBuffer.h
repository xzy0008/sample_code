#pragma once

namespace vgChannel {

	class FrameBuffer
	{
	public:
		FrameBuffer( int width , int height );
		~FrameBuffer();

		void setSize(int width, int height);

		bool create();
		
		void bind();

		void unbind();

		GLuint getTextureId() { return g_dynamicTextureID; }

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

		void check_buffer_status(int no = 0);

		//private:
	public:

		GLuint g_frameBuffer;
		GLuint g_depthRenderBuffer;

		GLuint g_dynamicTextureID;

		GLuint g_dynamicDepthTextureID;

		bool m_IsValid;

		int m_bufferWidth ;
		int m_bufferHeight;
	};




}// end of namespace vgChannel
