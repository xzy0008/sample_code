


#ifndef __VGIIMAGERGBA_H__
#define __VGIIMAGERGBA_H__

#include <vgKernel/vgkForward.h>
#include <vgKernel/vgkSharePtr.h>
#include <vgKernel/vgkStreamReader.h>
#include <vgKernel/vgkStreamWriter.h>


namespace vgImage {

	class BmpFactory;

	/**
	@date 	2009/04/18  19:23	
	@author  leven

	@brief 	只用于处理RGBA的buffer，主要是为了提高效率。

	注意：

	1.左上角为坐标

	@see    
	*/
	class VGI_EXPORT ImageRGBA
	{
		friend class BmpFactory;
	public:
		// take_ownership是否获得所有权，如果为false，本类
		// 将复制一份数据
		ImageRGBA( char* buffer , long width, long height ,
			bool take_ownership , bool flip_Y );
		~ImageRGBA();

	public:

		// 写入内存。
		// 传入的buf需要是NULL
		bool encodeToBmpMemory( char*& buf , long& buf_length );

		bool writeToBmpStream( vgKernel::StreamWriterPtr pwriter );

		bool writeToFile( const String& outout_filename )
		{
			vgKernel::StreamWriterPtr pw = 
				vgKernel::StreamWriterFactory::createFromFile( 
				outout_filename );

			return writeToBmpStream( pw );
		}

		void setFilpY( bool flipy )
		{
			_flipY = flipy;
		}

		void flipYNow()
		{
			long size = _width * _height * 4;
			char* buf = new char[ size ];
			long pos = 0;

			for ( int y = 0 ; y < _height ; ++ y )
			{
				memcpy( buf + pos, _pixelData + size - _width * 4 * ( y + 1) ,  _width * 4 );
				pos +=  _width * 4;
			}

			delete[] _pixelData;
			_pixelData = buf;
		}

		char* getRawPixelData()
		{
			return _pixelData;
		}

		void setOwnership( bool to_others )
		{
			_ownership = !to_others;
		}

		long getWidth() const
		{
			return _width;
		}

		long getHeight() const
		{
			return _height;
		}

	private:

		bool isValid();

	private:

		// RGBA格式
		char	 *_pixelData;
		long		_width;
		long 		_height;

		bool _flipY;
		bool _ownership;
	};


	typedef vgKernel::SharePtr<ImageRGBA> ImageRGBAPtr;


}// end of namespace vgImage



#endif // end of __VGIIMAGERGBA_H__