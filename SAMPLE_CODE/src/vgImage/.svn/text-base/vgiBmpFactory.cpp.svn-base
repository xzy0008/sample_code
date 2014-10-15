


#include <vgStableHeaders.h>
#include <vgImage/vgiBmpFactory.h>
#include <vgImage/vgiImageRGBA.h>


namespace vgImage {
	

	//----------------------------------------------------------------
	ImageRGBA* BmpFactory::decodeBmpToRGBAInMemory( 
		char* file_buffer , long buf_size ,bool filp_y )
	{
		assert( file_buffer != NULL );
		assert( buf_size > 0 );

		long pos = 0;

		BITMAPFILEHEADER* bfileheader = ( BITMAPFILEHEADER* ) file_buffer;
		pos += sizeof( BITMAPFILEHEADER );
		BITMAPINFOHEADER* infoheader = ( BITMAPINFOHEADER* )(file_buffer + pos );
		pos += sizeof( BITMAPINFOHEADER );

		if ( bfileheader->bfType != 0x4d42 ||
			bfileheader->bfReserved1 != 0 || 
			bfileheader->bfReserved2 != 0 ||
			infoheader->biSize != sizeof(BITMAPINFOHEADER) || 
			infoheader->biBitCount != 32 ||
			infoheader->biWidth <= 0 ||
			infoheader->biHeight <= 0 )
		{
			return NULL;
		}

		//if ( infoheader->biSizeImage != (
		//	infoheader->biWidth * infoheader->biHeight * 4 ) )
		//{
		//	return NULL;
		//}

		ImageRGBA* ret = new ImageRGBA( file_buffer + pos , infoheader->biWidth , 
			infoheader->biHeight , false , filp_y );

		pos += infoheader->biSizeImage;

		assert( buf_size == pos );

		return ret;

		//BITMAPFILEHEADER bfh;
		//bfh.bfType = 0x4d42; //bm
		//bfh.bfSize = size // data size
		//	+ sizeof( BITMAPFILEHEADER ) // first section size
		//	+ sizeof( BITMAPINFOHEADER ) // second section size
		//	;

		//bfh.bfReserved1 = 0; // reserved 
		//bfh.bfReserved2 = 0; // reserved


		//// 位图第二部分，数据信息
		//BITMAPINFOHEADER bih;
		//bih.biSize = sizeof(BITMAPINFOHEADER);
		//bih.biWidth = _width;
		//bih.biHeight = _height;
		//bih.biPlanes = 1;
		//bih.biBitCount = 32;
		//bih.biCompression = 0;
		//bih.biSizeImage = size;
		//bih.biXPelsPerMeter = 0;
		//bih.biYPelsPerMeter = 0;
		//bih.biClrUsed = 0;
		//bih.biClrImportant = 0;     


		//bfileheader->bfSize
		//	buf_length = size + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) ;


	}
	//----------------------------------------------------------------
	ImageRGBA* BmpFactory::decodeBmpFileToRGBA( const String& file_path )
	{
		vgKernel::StreamReaderPtr preader = 
			vgKernel::StreamReaderFactory::createFromFile( file_path );

		if ( preader.isNull() )
		{
			return NULL;
		}

		int siz = preader->size();
		preader->seek(0);
		char* bbbuf = new char[siz ];
		preader->read( bbbuf , siz );

		ImageRGBA* iii = decodeBmpToRGBAInMemory( bbbuf , siz , false );

		delete[] bbbuf;

		return iii;
	}
	//----------------------------------------------------------------
	
	
}// end of namespace vgImage
