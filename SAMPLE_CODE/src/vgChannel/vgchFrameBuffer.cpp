
#include <vgStableHeaders.h>
#include <vgChannel/vgchFrameBuffer.h>
#include <vgVisualEffects/vgviBackgroundManager.h>
#include <vgKernel/vgkTrace.h>
#include <sstream>

namespace vgChannel {

	//----------------------------------------------------------------
	FrameBuffer::FrameBuffer( int width , int height )
	{
		m_bufferWidth = width;
		m_bufferHeight = height;

		g_dynamicDepthTextureID = 0;
		g_dynamicTextureID = 0;
		m_IsValid = false;
	}

	void FrameBuffer::setSize(int width, int height)
	{
		m_bufferWidth = width;
		m_bufferHeight = height;
	}

	//----------------------------------------------------------------
	bool FrameBuffer::create()
	{
		// Setup our FBO
		glGenFramebuffersEXT(1, &g_frameBuffer);
		glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, g_frameBuffer);

		// Create the render buffer for depth	
		glGenRenderbuffersEXT(1, &g_depthRenderBuffer);
		glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, g_depthRenderBuffer);
		glRenderbufferStorageEXT(GL_RENDERBUFFER_EXT, GL_DEPTH_COMPONENT, m_bufferWidth, m_bufferHeight);

		// Now setup a texture to render to
		glGenTextures(1, &g_dynamicTextureID);
		glBindTexture(GL_TEXTURE_2D, g_dynamicTextureID);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,  m_bufferWidth, m_bufferHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
		
		glTexEnvi( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL ); 
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		//  The following 3 lines enable mipmap filtering and generate the mipmap data so rendering works
		//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		//	glGenerateMipmapEXT(GL_TEXTURE_2D);

		// And attach it to the FBO so we can render to it
		glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, g_dynamicTextureID, 0);

		// Attach the depth render buffer to the FBO as it's depth attachment
		glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_RENDERBUFFER_EXT, g_depthRenderBuffer);


		GLenum status = glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT);
		if(status != GL_FRAMEBUFFER_COMPLETE_EXT)
			AfxMessageBox("FBO init Faild");

		m_IsValid = true;
		check_buffer_status();

		return true;
	}
	//----------------------------------------------------------------
	void FrameBuffer::bind()
	{
		glBindFramebufferEXT( GL_FRAMEBUFFER_EXT, g_frameBuffer );

		glShadeModel(GL_SMOOTH);	
		glEnable(GL_DEPTH_TEST);			
		glDepthFunc(GL_LEQUAL);				

		glViewport( 0, 0, m_bufferWidth, m_bufferHeight );

		// glClearColor(0.5f,0.6f,0.8f,1.0f);
		vgVisualEffects::BackgroundManager::getSingleton().renderBegin();

		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

		glMatrixMode( GL_MODELVIEW );
		glLoadIdentity();
	}
	//----------------------------------------------------------------
	void FrameBuffer::unbind()
	{
		assert( isValid() );
		check_buffer_status(3);

		glBindFramebufferEXT( GL_FRAMEBUFFER_EXT, 0 );
	}
	//----------------------------------------------------------------
	bool FrameBuffer::check_extension()
	{
		if( !glIsRenderbufferEXT || !glBindRenderbufferEXT || !glDeleteRenderbuffersEXT || 
			!glGenRenderbuffersEXT || !glRenderbufferStorageEXT || !glGetRenderbufferParameterivEXT || 
			!glIsFramebufferEXT || !glBindFramebufferEXT || !glDeleteFramebuffersEXT || 
			!glGenFramebuffersEXT || !glCheckFramebufferStatusEXT || !glFramebufferTexture1DEXT || 
			!glFramebufferTexture2DEXT || !glFramebufferTexture3DEXT || !glFramebufferRenderbufferEXT||  
			!glGetFramebufferAttachmentParameterivEXT || !glGenerateMipmapEXT )
		{
			::MessageBox(NULL,"One or more EXT_framebuffer_object functions were not found",
				"ERROR",MB_OK|MB_ICONEXCLAMATION);
			return false;
		}
		return true;
	}
	//----------------------------------------------------------------
	void FrameBuffer::check_buffer_status(int no)
	{

		GLenum status;
		status = glCheckFramebufferStatusEXT( GL_FRAMEBUFFER_EXT );
		std::stringstream outString; 

		switch( status )
		{
		case GL_FRAMEBUFFER_COMPLETE_EXT:
			break;

		case GL_FRAMEBUFFER_UNSUPPORTED_EXT:
			outString << no;
			AfxMessageBox(outString.str().c_str());
			::MessageBox(NULL,"GL_FRAMEBUFFER_UNSUPPORTED_EXT!","ERROR",MB_OK|MB_ICONEXCLAMATION);
			break;
			
		case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT_EXT:  
			outString << no;
			AfxMessageBox(outString.str().c_str());

			AfxMessageBox("GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT_EXT");
			break;

		case GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS_EXT:  
			outString << no;
			AfxMessageBox(outString.str().c_str());

			AfxMessageBox("GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS_EXT");
			break;

		case GL_FRAMEBUFFER_INCOMPLETE_FORMATS_EXT:     
			outString << no;
			AfxMessageBox(outString.str().c_str());

			AfxMessageBox("GL_FRAMEBUFFER_INCOMPLETE_FORMATS_EXT");
			break;

		case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER_EXT:  
			outString << no;
			AfxMessageBox(outString.str().c_str());

			AfxMessageBox("GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER_EXT");
			break;
		}

		return;
	}

	FrameBuffer::~FrameBuffer()
	{
		if ( isValid() )
		{
			this->destroy();
		}
		VGK_TRACE( "FrameBuffer destructed!");
	}
	//----------------------------------------------------------------



}// end of namespace vgCore