


#include <vgStableHeaders.h>
#include <vgImage/vgiImageRGBA.h>


namespace vgImage {
	
	
	
	//----------------------------------------------------------------
	ImageRGBA::ImageRGBA( char* buffer , long width, long height ,
		bool take_ownership  , bool flip_Y )
	{
		_width = width;
		_height = height;

		if ( take_ownership )
		{
			_pixelData = buffer;
		}
		else
		{
			_pixelData = new char[ _width * _height * 4 ];
			memcpy( _pixelData , buffer , _width * height * 4 );
		}

		assert( isValid() );

		_flipY = flip_Y;
		_ownership = true;
	}
	//----------------------------------------------------------------
	ImageRGBA::~ImageRGBA()
	{
		if (_ownership )
		{
			if ( _pixelData )
			{
				delete[] _pixelData;
				_pixelData = NULL;
			}
		}

	}
	//----------------------------------------------------------------
	bool ImageRGBA::writeToBmpStream( vgKernel::StreamWriterPtr pwriter )
	{
		if ( pwriter.isNull() )
		{
			return false;
		}

#if 0
		int size = _width * _height * 4; // 每个像素点4个字节

		// 位图第一部分，文件信息
		BITMAPFILEHEADER bfh;
		bfh.bfType = 0x4d42; //bm
		bfh.bfSize = size // data size
			+ sizeof( BITMAPFILEHEADER ) // first section size
			+ sizeof( BITMAPINFOHEADER ) // second section size
			;

		bfh.bfReserved1 = 0; // reserved 
		bfh.bfReserved2 = 0; // reserved

		bfh.bfOffBits = bfh.bfSize - size;

		// 位图第二部分，数据信息
		BITMAPINFOHEADER bih;
		bih.biSize = sizeof(BITMAPINFOHEADER);
		bih.biWidth = _width;
		bih.biHeight = _height;
		bih.biPlanes = 1;
		bih.biBitCount = 32;
		bih.biCompression = 0;
		bih.biSizeImage = size;
		bih.biXPelsPerMeter = 0;
		bih.biYPelsPerMeter = 0;
		bih.biClrUsed = 0;
		bih.biClrImportant = 0;      

		pwriter->write( &bfh , sizeof (BITMAPFILEHEADER) );
		pwriter->write( &bih , sizeof( BITMAPINFOHEADER) );

		if ( _flipY )
		{
			for ( int y = 0 ; y < _height ; ++ y )
			{
				pwriter->write( _pixelData + size - _width * 4 * ( y + 1) ,  _width * 4 );
			}
		}
		else
		{
			pwriter->write( _pixelData , size );
		}
#else

		char* buff = NULL;
		long buff_size = 0;
		if ( encodeToBmpMemory( buff , buff_size ) )
		{
			pwriter->write( buff , buff_size );
			delete[] buff;
			return true;
		}

		delete[] buff;
		return false;

#endif

		return true;
	}
	//----------------------------------------------------------------
	bool ImageRGBA::encodeToBmpMemory( char*& buf , long& buf_length )
	{
		assert( buf == NULL );

		int size = _width * _height * 4; // 每个像素点4个字节

		buf_length = size + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) ;

		buf = new char[ buf_length ];
		int pos = 0;

		// 位图第一部分，文件信息
		BITMAPFILEHEADER bfh;
		bfh.bfType = 0x4d42; //bm
		bfh.bfSize = size // data size
			+ sizeof( BITMAPFILEHEADER ) // first section size
			+ sizeof( BITMAPINFOHEADER ) // second section size
			;

		bfh.bfReserved1 = 0; // reserved 
		bfh.bfReserved2 = 0; // reserved

		bfh.bfOffBits = bfh.bfSize - size;

		// 位图第二部分，数据信息
		BITMAPINFOHEADER bih;
		bih.biSize = sizeof(BITMAPINFOHEADER);
		bih.biWidth = _width;
		bih.biHeight = _height;
		bih.biPlanes = 1;
		bih.biBitCount = 32;
		bih.biCompression = 0;
		bih.biSizeImage = size;
		bih.biXPelsPerMeter = 0;
		bih.biYPelsPerMeter = 0;
		bih.biClrUsed = 0;
		bih.biClrImportant = 0;      

		memcpy( buf , &bfh , sizeof (BITMAPFILEHEADER) );
		pos += sizeof(BITMAPFILEHEADER);

		memcpy( buf + pos, &bih , sizeof (BITMAPINFOHEADER) );
		pos += sizeof(BITMAPINFOHEADER);

		if ( _flipY )
		{
			for ( int y = 0 ; y < _height ; ++ y )
			{
				memcpy( buf + pos, _pixelData + size - _width * 4 * ( y + 1) ,  _width * 4 );
				pos +=  _width * 4;
			}
		}
		else
		{
			memcpy( buf + pos, _pixelData, size );
			pos +=  size;
		}

		assert( pos == buf_length );
		return true;
	}
	//----------------------------------------------------------------
	bool ImageRGBA::isValid()
	{
		return (_pixelData != NULL)&&( _width > 0)&&(_height>0);
	}
	//----------------------------------------------------------------





}// end of namespace vgImage
