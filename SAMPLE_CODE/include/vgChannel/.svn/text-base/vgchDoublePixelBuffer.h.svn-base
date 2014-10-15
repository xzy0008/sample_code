#include <vgChannel/vgchPixelBuffer.h>

namespace vgChannel
{
	class DoublePixelBuffer
	{
	public:
		DoublePixelBuffer(int width, int height, PIXEL_BUFFER_TYPE type=PIXEL_PACK, GLenum format=GL_BGR);
		~DoublePixelBuffer();
		
		bool reSize(int width, int height);

		GLubyte *getBufferData();
		bool unmap();

	private:
		int m_currentBufferID;

		PixelBuffer m_buffer0;
		PixelBuffer m_buffer1;

	};
}