#include <vgStableHeaders.h>
#include <vgChannel/vgchPixelBuffer.h>

namespace vgChannel
{

	PixelBuffer::PixelBuffer(int width, int height, vgChannel::PIXEL_BUFFER_TYPE type, GLenum format/* = GL_BGR*/)
		: m_width(width), m_height(height), m_pDrawBuffer(NULL), m_type(type), m_format(format)
	{
		glGenBuffers(1, &m_bufferId);	

		if ( format == GL_BGRA || format == GL_RGBA)
		{
			m_pixelLen = 4; 
		}
		else
		{
			m_pixelLen = 3;
		}

		if (type == PIXEL_PACK)
		{
			glBindBufferARB(GL_PIXEL_PACK_BUFFER_ARB, m_bufferId);
			glBufferDataARB(GL_PIXEL_PACK_BUFFER_ARB, m_pixelLen*m_width*m_height, 0, GL_STREAM_READ_ARB);
			glBindBufferARB(GL_PIXEL_PACK_BUFFER, 0);(GL_PIXEL_PACK_BUFFER_ARB, 0);
		}
		else if (type == PIXEL_UNPACK)
		{
			m_pDrawBuffer = new GLubyte[m_width * m_height * m_pixelLen];

			glBindBufferARB(GL_PIXEL_UNPACK_BUFFER_ARB, m_bufferId);
			glBufferDataARB(GL_PIXEL_UNPACK_BUFFER_ARB, m_pixelLen*m_width*m_height, m_pDrawBuffer, GL_STREAM_DRAW_ARB);
			glBindBufferARB(GL_PIXEL_PACK_BUFFER, 0);(GL_PIXEL_UNPACK_BUFFER_ARB, 0);	
		}

		if (glGetError() != GL_NO_ERROR)
		{
			AfxMessageBox("Construct pixel buffer error. \n");
		}
	}

	PixelBuffer::~PixelBuffer()
	{
		if (m_type == PIXEL_PACK)
		{
			glBindBufferARB(GL_PIXEL_PACK_BUFFER_ARB, 0);
		}
		else
		{
			glBindBufferARB(GL_PIXEL_UNPACK_BUFFER_ARB, 0);
		}

		if (m_pDrawBuffer != NULL)
		{
			delete [] m_pDrawBuffer;
		}

		glDeleteBuffers(1, &m_bufferId);
	}

	bool PixelBuffer::reSize(int width, int height)
	{
		m_width = width;
		m_height = height;
	
		if (m_type == PIXEL_PACK)
		{
			glBindBufferARB(GL_PIXEL_PACK_BUFFER_ARB, m_bufferId);
			glBufferDataARB(GL_PIXEL_PACK_BUFFER_ARB, m_pixelLen*m_width*m_height, 0, GL_STREAM_READ_ARB);
			glBindBufferARB(GL_PIXEL_PACK_BUFFER, 0);

		}
		else if (m_type == PIXEL_UNPACK)
		{
			if (m_pDrawBuffer != NULL)
			{
				delete [] m_pDrawBuffer;
			}

			m_pDrawBuffer = new GLubyte[m_width * m_height * m_pixelLen];

			glBindBufferARB(GL_PIXEL_UNPACK_BUFFER_ARB, m_bufferId);
			glBufferDataARB(GL_PIXEL_UNPACK_BUFFER_ARB, m_pixelLen*m_width*m_height, m_pDrawBuffer, GL_STREAM_DRAW_ARB);
			glBindBufferARB(GL_PIXEL_UNPACK_BUFFER_ARB, 0);

		}

		if (glGetError() != GL_NO_ERROR)
		{
			AfxMessageBox("Resize pixel buffer error. \n");

			return false;
		}

		return true;
	}

	GLubyte* PixelBuffer::getDrawBuffer()
	{
		return m_pDrawBuffer;
	}

	bool PixelBuffer::pack()
	{
		glBindBufferARB(GL_PIXEL_PACK_BUFFER_ARB, m_bufferId);
		glReadPixels(0, 0, m_width, m_height, m_format, GL_UNSIGNED_BYTE, 0);
		
		if (glGetError() != GL_NO_ERROR)
		{
			return false;
		}

		return true;
	}

	GLubyte* PixelBuffer::mapBuffer()
	{
		GLubyte* buf = (GLubyte*)glMapBufferARB(GL_PIXEL_PACK_BUFFER_ARB, GL_READ_ONLY_ARB);
		
		if (glGetError() == GL_NO_ERROR && buf != NULL)
		{
			return buf;
		}

		return NULL;
	}

	bool PixelBuffer::unmapBuffer()
	{
		glUnmapBufferARB(GL_PIXEL_PACK_BUFFER_ARB);
		glBindBufferARB(GL_PIXEL_PACK_BUFFER_ARB, 0);

		if (glGetError() != GL_NO_ERROR)
		{
			return false;
		}

		return true;
	}

	bool PixelBuffer::unpack()
	{
		glBindBufferARB(GL_PIXEL_UNPACK_BUFFER_ARB, m_bufferId);
		glDrawPixels(m_width, m_height, m_format, GL_UNSIGNED_BYTE, 0);
		glBindBufferARB(GL_PIXEL_UNPACK_BUFFER_ARB, 0);

		if (glGetError() != GL_NO_ERROR)
		{
			return false;
		}

		return true;
	}

}