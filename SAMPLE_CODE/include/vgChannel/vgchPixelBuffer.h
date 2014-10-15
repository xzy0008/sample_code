#pragma once

namespace vgChannel
{
	enum PIXEL_BUFFER_TYPE
	{
		PIXEL_PACK,
		PIXEL_UNPACK
	};

	class PixelBuffer
	{
	public:
		PixelBuffer(int width, int height, PIXEL_BUFFER_TYPE type=PIXEL_PACK, GLenum format=GL_BGR);
		~PixelBuffer();

		bool reSize(int width, int height);
		int getWidth() { return m_width; }
		int getHeight() { return m_height; }

		/*
			Pack 从像素缓冲区读数据到内存
			1、先调用Pack开启DMA传送
			2、调用mapBuffer获取数据到内存
			3、对返回的内存进行操作，注意修改不会影响到颜色缓冲区
			4、调用unmapBuffer释放缓冲区内存
		*/

		// DMA传送，读屏
		bool pack();
		// 映射屏幕像素点数据到临时缓冲区 
		GLubyte* mapBuffer();
		// 释放临时缓冲区数据
		bool unmapBuffer();

		/*
		UnPack 从内存传送数据到像素缓冲区
		1、先调用getDrawBuffer得到内存缓冲区地址
		2、对内存缓冲区进行操作
		3、调用pack传送数据至颜色缓冲区
		*/

		// DMA传送，写屏
		bool unpack();
		// 得到写屏缓冲区数据可进行修改
		GLubyte* getDrawBuffer();
	
	private:

		GLuint					m_bufferId;
		GLubyte*				m_pDrawBuffer;

		int						m_width;
		int						m_height;
	
		int						m_pixelLen;
		GLenum					m_format;

		PIXEL_BUFFER_TYPE		m_type;
	};
}