


#include <vgStableHeaders.h>
#include <vgKernel/vgkException.h>
#include <vgImage/vgiFreeImageWrapper.h>
#include <vgImage/vgiImageUtility.h>
#include <vgImage/vgiCompress.h>
#include <vgKernel/vgkStreamReader.h>



namespace vgImage {
	

	
	
	//----------------------------------------------------------------
	bool FreeImageWrapper::createFromArray(  void* buf, long dwWidth, 
		long dwHeight , long dBpp/* = 24 */,bool axis_left_up /*= true*/ )
	{
		assert( dBpp == 24 || 
			dBpp == 32 );

		WORD w = (WORD)dwWidth;
		WORD h = (WORD)dwHeight;

		assert( w == dwWidth );
		assert( h == dwHeight );

		int bytepp = dBpp / 8;

		BOOL setok = setSize( FIT_BITMAP , w , h , (WORD)dBpp );

		if ( setok == FALSE )
		{
			return false;
		}

		char* buffer = (char*)buf;

		if ( axis_left_up )
		{
			for ( int y = 0 ; y < h ; ++ y )
			{
				char* databeg =  buffer + y * dwWidth * bytepp;

				memcpy( getScanLine( h - y - 1 ) , databeg , w * bytepp );
			}
		}
		else
		{
			for ( int y = 0 ; y < dwHeight ; ++ y )
			{
				char* databeg =  buffer + y * dwWidth * bytepp;

				memcpy( getScanLine( y  ) , databeg , dwWidth * bytepp );
			}
		}


		//BYTE* ddddf = FreeImage_GetScanLine( _dib , 0 );

		//int ddddd = FreeImage_GetPitch( _dib );

		//int ffas = FreeImage_GetLine( _dib );

		//BYTE* pixels = accessPixels();
		//assert( pixels != NULL );

		return true;
	}
	//----------------------------------------------------------------
	bool FreeImageWrapper::swapRedAndBlueChannel()
	{
		assert( isValid());
		if ( !isValid() )
		{
			return false;
		}
		// 目前只支持2种
		assert( getBitsPerPixel() == 32 ||
			getBitsPerPixel() == 24 );

		assert( getColorType() == FIC_RGB ||
			getColorType() == FIC_RGBALPHA );

		int height = getHeight();
		int width = getWidth();
		int bytespp = getLine() / width;

		for ( int y = 0 ; y < height ; ++ y )
		{
			BYTE* curdata = getScanLine( y );
			assert( curdata != NULL );

			for ( int x = 0 ; x < width ; ++ x )
			{
				BYTE tmp = *curdata;
				*curdata = *(curdata + 2);
				*(curdata + 2 ) = tmp;

				curdata += bytespp;
			}
		}

		return true;
	}
	//----------------------------------------------------------------
	bool FreeImageWrapper::saveToDdsFile( const String& file_abs_path ,
		const DdsFormat& dformat , const bool& auto_resize_to_two_power /*= false */ )
	{
		assert( isValid());
		if ( !isValid() )
		{
			return false;
		}
		GLenum ddsFormat;

		switch( dformat )
		{
		case DDS_FORMAT_DXT1 : //SAVE_DDS_DXT1:
			{
				ddsFormat = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
				break;
			}
		case DDS_FORMAT_DXT3 : //SAVE_DDS_DXT3:
			{
				ddsFormat = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
				break;
			}
		case DDS_FORMAT_DXT5 : //SAVE_DDS_DXT5:
			{
				ddsFormat = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
				break;
			}
		default:
			{
				VGK_EXCEPT(vgKernel::Exception::ERR_INVALIDPARAMS ,
					"创建纹理参数错误," ,
					"saveDDS");
				assert( 0 && " 不支持的格式!! ");
				return false;
			}
		}

		return saveToDdsFile( file_abs_path , ddsFormat , auto_resize_to_two_power );
	}
	//----------------------------------------------------------------
	bool FreeImageWrapper::saveToDdsFile( const String& file_abs_path ,
		const GLenum& dds_format , const bool& auto_resize_to_two_power /*= false */ )
	{
		if ( getBitsPerPixel() != 24 && getBitsPerPixel() != 32 )
		{
			//AfxMessageBox("只支持24位或32位图像.请转换后再生成.");
			//file_abs_path
			std::ostringstream ostr;
			ostr <<file_abs_path<<"转化失败，"<<"只支持24位或32位图像.请转换后再生成";
			AfxMessageBox(ostr.str().c_str());				

			return false;
		}

		assert( isValid());
		if ( !isValid() )
		{
			return false;
		}

		assert( dds_format == GL_COMPRESSED_RGBA_S3TC_DXT1_EXT ||
			dds_format == GL_COMPRESSED_RGBA_S3TC_DXT3_EXT || 
			dds_format == GL_COMPRESSED_RGBA_S3TC_DXT5_EXT );

		if ( ImageUtility::findImageFileExtension( file_abs_path ) != "dds" )
		{
			assert(0);
			return false;
		}

		// 确认已载入图像.
		assert( isValid() );

		vgKernel::StreamWriterPtr pstream = 
			vgKernel::StreamWriterFactory::createFromFile( file_abs_path );

		if ( pstream.isNull() == true )
		{
			return false;
		}

		if ( pstream->isValid() == false )
		{
			return false;
		}

		// 检查长宽是否是2的n次方.
		if ( !ImageUtility::checkImageSizeIsPowerOfTwo( this->getWidth() , 
			this->getHeight() ))
		{
			if ( auto_resize_to_two_power == false )
			{
				//assert( 0 && "长宽并不完全符合2的n次方条件!");
				AfxMessageBox("长宽并不完全符合2的n次方条件!");
				return false;
			}

			//------------------------------------------
			// 开始resize到2的n次方
			//------------------------------------------
			long adjust_width = ImageUtility::getSmallerPowerOfTwoNumber( getWidth() );
			long adjust_height = ImageUtility::getSmallerPowerOfTwoNumber( getHeight() );

			assert( (WORD)adjust_height == adjust_height );
			assert( (WORD)adjust_width == adjust_width );		

			BOOL resizeok = rescale(  (WORD)adjust_width , (WORD)adjust_height , FILTER_BOX );

			assert( resizeok == TRUE );

			if ( resizeok == FALSE )
			{
				return false;
			}
		}

		//------------------------------------------
		// 使用新的函数来处理
		//------------------------------------------
		BYTE* uncompressed_buf = NULL;
		long size = 0;

		if ( getBitsPerPixel() == 24 )
		{
			FreeImageWrapper* clonedimg = new FreeImageWrapper;
			*clonedimg = *this;
			clonedimg->convertTo32Bits();
			// 肯定对齐
			assert( clonedimg->accessAlignedPixels() != NULL );

			long filenum = Compress::processWholeFileToStream( clonedimg->accessAlignedPixels() , 
				clonedimg->getWidth(), clonedimg->getHeight() , pstream , dds_format );
			assert( filenum > 0 );

			delete clonedimg;
			return true;
		}
		else
		{
			assert( accessAlignedPixels() != NULL );

			long filenum = Compress::processWholeFileToStream( accessAlignedPixels() , 
				getWidth(), getHeight() , pstream , dds_format );
			assert( filenum > 0 );

			return true;
		}


	}
	//----------------------------------------------------------------
	BYTE* FreeImageWrapper::getAlignedPixelsCopy()
	{
		if ( !isValid() )
		{
			return NULL;
		}

		assert( isValid() );

		// 目前只支持2种
		assert( getBitsPerPixel() == 32 ||
			getBitsPerPixel() == 24 );

		assert( getColorType() == FIC_RGB ||
			getColorType() == FIC_RGBALPHA );

		int bytepp = getBitsPerPixel() / 8;
		int width  = getWidth();
		int height = getHeight();

		BYTE* intern = NULL;
		int bufsiz = width * height * bytepp;
		BYTE* ret = new BYTE[ bufsiz ];

		intern = accessAlignedPixels();
		if ( intern != NULL )
		{
			// 直接拷贝输出即可
			memcpy( ret , intern , bufsiz );
			return ret;
		}

		for ( int y = 0 ; y < height ; ++ y )
		{
			BYTE* data = getScanLine( y );
			memcpy( ret + width * bytepp, data, getLine() );
		}

		return ret;
	}
	//----------------------------------------------------------------
	BYTE* FreeImageWrapper::accessAlignedPixels()
	{
		if ( !isValid() )
		{
			return NULL;
		}

		if ( getBitsPerPixel() != 24 &&
			getBitsPerPixel() != 32 )
		{
			return NULL;
		}

		if ( getLine() != getScanWidth() )
		{
			return NULL;
		}

		return accessPixels();
	}
	//----------------------------------------------------------------
	bool FreeImageWrapper::loadFromFile( const String& filepath ,
		int flag /*= 0*/)
	{
		assert( isValid() == FALSE );

		BYTE* buf = NULL;
		int size_in_bytes = 0;

		vgKernel::StreamReaderPtr pstream = 
			vgKernel::StreamReaderFactory::createFromFile( filepath );

		if ( pstream.isNull() )
		{
			return false;
		}

		size_in_bytes = pstream->size();

		if ( size_in_bytes == 0 )
		{
			return false;
		}

		buf = new BYTE[ size_in_bytes ];
		memset( buf, 0 , size_in_bytes );

		size_t readnum = pstream->read( buf , size_in_bytes );
		assert( readnum == size_in_bytes );
		if ( readnum != size_in_bytes )
		{
			delete[] buf;
			return false;
		}

		// 释放文件指针
		pstream.setNull();


		fipMemoryIO mem( buf , size_in_bytes );

		int loadok = loadFromMemory( mem , flag );

		delete[] buf;

		if ( loadok == FALSE )
		{
			return false;
		}

		return true;
	}
	//----------------------------------------------------------------
	bool FreeImageWrapper::saveToFile( const String& save_path ,int flag /*= 0 */)
	{
#if 0
		BOOL saveok = save( save_path.c_str() , flag );
		return saveok == TRUE ;
#else

		FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
		fif = FreeImage_GetFIFFromFilename( save_path.c_str() );

		// 申请的内存区域
		fipMemoryIO alloc;

		BOOL saveok = saveToMemory( fif , alloc, flag );
		
		if( saveok == FALSE )
		{
			return false;
		}

		assert( alloc.isValid() );

		saveok = saveToFileImpl(save_path, alloc);

		if ( saveok == false )
		{
			int counter = 0;
			while ( counter < 100 && saveok == false )
			{
				saveok = saveToFileImpl(save_path, alloc);
				counter ++;
				Sleep(100);
			}

			if ( saveok == false )
			{
				assert( 0&& "loadok == false" );
				return false;
			}
			else
			{
				return true;
			}
		}

		return true;
#endif
	}
	//----------------------------------------------------------------
	bool FreeImageWrapper::crop( const vgKernel::ImageRect& rect , FreeImageWrapper* pDstImg , 
		bool axisLeftTop /*= true */ )
	{
		assert( isValid() == TRUE );

		if ( pDstImg == NULL )
		{
			if ( axisLeftTop == true )
			{
				BOOL cropok = fipImage::crop( rect.minPos.x, rect.minPos.y , 
					rect.maxPos.x ,rect.maxPos.y );
				return cropok == TRUE;
			}
			else
			{
				// 坐标轴在左下角
				BOOL cropok = fipImage::crop( rect.minPos.x , getHeight() - rect.maxPos.y , 
					rect.maxPos.x , getHeight() - rect.minPos.y );
				return cropok == TRUE;
			}
		}
		else
		{
			assert( pDstImg->isValid() == FALSE );

			if ( axisLeftTop == true )
			{
				BOOL cropok = copySubImage( *pDstImg , rect.minPos.x , rect.minPos.y ,
					rect.maxPos.x ,rect.maxPos.y );
				return cropok == TRUE;
			}
			else
			{

				BOOL cropok = copySubImage( *pDstImg , rect.minPos.x , getHeight() - rect.maxPos.y , 
					rect.maxPos.x , getHeight() - rect.minPos.y );
				return cropok == TRUE;
			}
		}
	}
	//----------------------------------------------------------------
	bool FreeImageWrapper::overlap( FreeImageWrapper &imgsrc2,
		const vgKernel::ImageRect& rect , bool axisLeftTop /*= true */ )
	{

		return true;
	}
	//----------------------------------------------------------------
	bool FreeImageWrapper::overlap2( FreeImageWrapper &overlapped, 
		long left , long top )
	{
		assert( overlapped.isValid() == TRUE );

		using namespace vgKernel;

		ImageRect selfrect( 0 , 0 , 
			getWidth(), getHeight() );

		ImageRect overrect( 0 , 0 , 
			overlapped.getWidth(), overlapped.getHeight() );

		selfrect.translate( ImagePos( -left , -top ) );

		//------------------------------------------
		// 倘若在本rect内,直接进行操作即可
		//------------------------------------------
		if ( selfrect.testInside( overrect ) )
		{
			BOOL pasteok = pasteSubImage( overlapped, left , top );
			return pasteok == TRUE;
		}

		ImageRect intr;
		bool findok = overrect.findIntersection2( selfrect , intr );

		if ( findok == false )
		{
			return false;
		}

		FreeImageWrapper tmp;
		BOOL copyok = overlapped.copySubImage( tmp , intr.minPos.x , intr.minPos.y , 
			intr.maxPos.x , intr.maxPos.y );

		if ( copyok == FALSE )
		{
			return false;
		}

		intr.translate( ImagePos( left , top ) );

		BOOL pasteok = pasteSubImage( tmp, intr.minPos.x , intr.minPos.y );

		return pasteok == TRUE;

		////------------------------------------------
		//// 首先检查越界的情况
		//// 这个时候复制需要的数据
		////------------------------------------------
		//FreeImageWrapper* tmp = &overlapped;

		//if((left + overlapped.getWidth() > getWidth()) || 
		//	(top + overlapped.getHeight() > getHeight() )) 
		//{
		//	tmp = new FreeImageWrapper;
		//	
		//	overlapped.copySubImage( *tmp , )

		//	return false;
		//}


		//BOOL pasteok = pasteSubImage( overlapped, left , top );
		//
		//return pasteok == TRUE;
	}
	//----------------------------------------------------------------
	void FreeImageWrapper::clearColor( const RGBQUAD& color )
	{
		assert( isValid() == TRUE );
		assert( getBitsPerPixel() == 32 );

		int h = getHeight();
		int w = getWidth();
		int bytepp = 4;

		BYTE* databeg = accessPixels();

		for ( int y = 0 ; y < h ; ++ y )
		{
			BYTE* bits =  getScanLine( y );

			if ( y == 0 )
			{
				for ( int x = 0 ; x < w ; ++ x )
				{
					bits[FI_RGBA_BLUE]	= color.rgbBlue;		// B
					bits[FI_RGBA_GREEN] = color.rgbGreen;		// G
					bits[FI_RGBA_RED]	= color.rgbRed;		// R
					bits[FI_RGBA_ALPHA] = color.rgbReserved;	// A
					bits += 4;
				}
			}
			else
			{
				memcpy( bits, databeg , w * bytepp );
			}
		}
	}
	//----------------------------------------------------------------
	void FreeImageWrapper::clearColor( 
		uchar color_r , uchar color_g , uchar color_b , uchar color_a )
	{
		RGBQUAD quad;
		quad.rgbRed = color_r;
		quad.rgbGreen = color_g;
		quad.rgbBlue = color_b;
		quad.rgbReserved = color_a;

		return clearColor( quad );
	}
	//----------------------------------------------------------------
	bool FreeImageWrapper::createFromSize( long dwWidth, long dwHeight , long dBpp /*= 32 */ )
	{
		assert( dBpp == 24 || 
			dBpp == 32 );

		WORD w = (WORD)dwWidth;
		WORD h = (WORD)dwHeight;

		assert( w == dwWidth );
		assert( h == dwHeight );

		BOOL setok = setSize( FIT_BITMAP , w , h , (WORD)dBpp );
		return setok == TRUE;
	}
	//----------------------------------------------------------------
	bool FreeImageWrapper::resize( const ImageSize& imgSize )
	{
		BOOL resok = 
			rescale( (WORD)imgSize.getWidth() , (WORD)imgSize.getHeight() , FILTER_BILINEAR );

		return resok == TRUE;
	}
	//----------------------------------------------------------------
	FreeImageWrapper* FreeImageWrapper::resizeCopy( const ImageSize& imgSize ) const
	{
		FreeImageWrapper* ret = new FreeImageWrapper;
		*ret = *this;

		BOOL resok = 
			ret->rescale( (WORD)imgSize.getWidth() , (WORD)imgSize.getHeight() , FILTER_BILINEAR );

		if( resok == FALSE )
		{
			delete ret;
			return NULL;
		}

		return ret;
	}
	//----------------------------------------------------------------
	bool FreeImageWrapper::saveToFileImpl( const String& save_path,
		fipMemoryIO &alloc )
	{
		vgKernel::StreamWriterPtr pstream = 
			vgKernel::StreamWriterFactory::createFromFile( save_path );

		if ( pstream.isNull() )
		{
			return false;
		}

		BYTE* buffer = NULL;
		DWORD buffer_size = 0;

		BOOL acquireok = alloc.acquire( &buffer , &buffer_size );
		assert( acquireok == TRUE );

		size_t writenum = pstream->write( buffer , buffer_size );
		if ( writenum != buffer_size )
		{
			return false;
		}

		assert( writenum == buffer_size );

		return true;
	}
	//----------------------------------------------------------------
}// end of namespace vgImage
