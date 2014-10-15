#include <vgStableHeaders.h>
#include <vgChannel/vgchDoublePixelBuffer.h>

namespace vgChannel
{
	DoublePixelBuffer::DoublePixelBuffer(int width, int height, PIXEL_BUFFER_TYPE type/* =PIXEL_PACK */, GLenum format/* =GL_BGR */)
		: m_buffer0(width, height, type, format)
		, m_buffer1(width, height, type, format)
		, m_currentBufferID(0)
	{

	}

	DoublePixelBuffer::~DoublePixelBuffer()
	{

	}

	bool DoublePixelBuffer::reSize(int width, int height)
	{
		m_buffer0.reSize(width, height);
		m_buffer1.reSize(width, height);

		return true;
	}

	GLubyte* DoublePixelBuffer::getBufferData()
	{
		if (m_currentBufferID ==0)
		{
			m_currentBufferID = 1;

			m_buffer1.pack();
			return m_buffer0.mapBuffer();
		}
		else
		{
			m_currentBufferID = 0;
			
			m_buffer0.pack();
			return m_buffer1.mapBuffer();
		}
	}

	bool DoublePixelBuffer::unmap()
	{
		if (m_currentBufferID == 0)
		{
			return m_buffer1.unmapBuffer();
		}
		else
		{
			return m_buffer0.unmapBuffer();
		}
	}
}