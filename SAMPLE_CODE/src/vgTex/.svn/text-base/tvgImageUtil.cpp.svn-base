
#include <vgStableHeaders.h>

#include <vgTex/tvgImageUtil.h>

#include <nvtt/nvtt.h>


namespace vgCore {
	
	//----------------------------------------------------------------
	ImageFormat ImageUtility::findImageFormatFromExt( const String& ext )
	{
		//assert( ext != "" );
		if ( ext == "" )
		{
			return IMAGE_FORMAT_UNKNOWN;
		}
		ImageFormat type;

		if ( ext == "dds" )
		{
			type = IMAGE_FORMAT_DDS;
			return type;
		}

		if (ext == "bmp")					type = IMAGE_FORMAT_BMP;
#if CXIMAGE_SUPPORT_JPG
		else if (ext=="jpg"||ext=="jpeg")	type = IMAGE_FORMAT_JPG;
#endif
#if CXIMAGE_SUPPORT_GIF
		else if (ext == "gif")				type = IMAGE_FORMAT_GIF;
#endif
#if CXIMAGE_SUPPORT_PNG
		else if (ext == "png")				type = IMAGE_FORMAT_PNG;
#endif
#if CXIMAGE_SUPPORT_MNG
		else if (ext=="mng"||ext=="jng")	type = IMAGE_FORMAT_MNG;
#endif
#if CXIMAGE_SUPPORT_ICO
		else if (ext == "ico")				type = IMAGE_FORMAT_ICO;
#endif
#if CXIMAGE_SUPPORT_TIF
		else if (ext=="tiff"||ext=="tif")	type = IMAGE_FORMAT_TIF;
#endif
#if CXIMAGE_SUPPORT_TGA
		else if (ext=="tga")				type = IMAGE_FORMAT_TGA;
#endif
#if CXIMAGE_SUPPORT_PCX
		else if (ext=="pcx")				type = IMAGE_FORMAT_PCX;
#endif
#if CXIMAGE_SUPPORT_WBMP
		else if (ext=="wbmp")				type = IMAGE_FORMAT_WBMP;
#endif
#if CXIMAGE_SUPPORT_WMF
		else if (ext=="wmf"||ext=="emf")	type = IMAGE_FORMAT_WMF;
#endif
#if CXIMAGE_SUPPORT_J2K
		else if (ext=="j2k"||ext=="jp2")	type = IMAGE_FORMAT_J2K;
#endif
#if CXIMAGE_SUPPORT_JBG
		else if (ext=="jbg")				type = IMAGE_FORMAT_JBG;
#endif
#if CXIMAGE_SUPPORT_JP2
		else if (ext=="jp2"||ext=="j2k")	type = IMAGE_FORMAT_JP2;
#endif
#if CXIMAGE_SUPPORT_JPC
		else if (ext=="jpc"||ext=="j2c")	type = IMAGE_FORMAT_JPC;
#endif
#if CXIMAGE_SUPPORT_PGX
		else if (ext=="pgx")				type = IMAGE_FORMAT_PGX;
#endif
#if CXIMAGE_SUPPORT_RAS
		else if (ext=="ras")				type = IMAGE_FORMAT_RAS;
#endif
#if CXIMAGE_SUPPORT_PNM
		else if (ext=="pnm"||ext=="pgm"||ext=="ppm") type = IMAGE_FORMAT_PNM;
#endif
		else type = IMAGE_FORMAT_UNKNOWN;

		return type;
	}
	//----------------------------------------------------------------
	bool ImageUtility::getHeaderInfo( const string& filename , 
		Integer& width , Integer& height , 
		const ImageFormat& imgformat /*= IMAGE_FORMAT_UNKNOWN */ )
	{
		if ( imgformat == IMAGE_FORMAT_UNKNOWN )
		{
			const ImageFormat& iformat = findImageFormat( filename );
			//if ( iformat == IMAGE_FORMAT_GIF ||
			//	iformat == IMAGE_FORMAT_ICO )
			//{
			//	VG_WARN(Warning::WARN_IMPLEMENT_ILL,
			//		Warning::BUTTON_OK,
			//		"gif格式或者ico格式还没有实现读取头文件信息的功能." ,
			//		"ImageUtility::getHeaderInfo");
			//	return false;
			//}
			return  CxImage::GetHeaderInfo( filename.c_str() , iformat ,
				width , height );
		}
		else
		{
			//if ( imgformat == IMAGE_FORMAT_GIF ||
			//	imgformat == IMAGE_FORMAT_ICO )
			//{
			//	VG_WARN(Warning::WARN_IMPLEMENT_ILL,
			//		Warning::BUTTON_OK,
			//		"gif格式或者ico格式还没有实现读取头文件信息的功能." ,
			//		"ImageUtility::getHeaderInfo");
			//	return false;
			//}
			return  CxImage::GetHeaderInfo( filename.c_str() , imgformat ,
				width , height );
		}
		return false;
	}
	//----------------------------------------------------------------
	//----------------------------------------------------------------
	long ImageUtility::getDdsImageStorageRequirements( const long& width , 
		const long& height , const GLenum& dds_format ,
		const bool& calculate_mipmap )
	{
		if ( calculate_mipmap == false )
		{
			return getDdsImageStorage( width , height , dds_format );
		}

		assert( calculate_mipmap == true );

		size_t result_size = 0;

		int w = width;
		int h = height;

		int nNumMipMaps = getMaxMipmapNum( w , h );

		for( int i = 0 ; i < nNumMipMaps ; ++ i )
		{
			if( w == 0 ) 
			{
				w = 1;
			}
			if( h == 0 ) 
			{
				h = 1;
			}

			result_size += getDdsImageStorage( w , h , dds_format );

			w /= 2;
			h /= 2;
		}
		return result_size;
	}
	//----------------------------------------------------------------
	long ImageUtility::getDdsImageStorage( const long& width , const long& height , 
		const GLenum& dds_format )
	{
		int method;

		switch( dds_format )
		{
		case GL_COMPRESSED_RGBA_S3TC_DXT1_EXT:
			{	
				method = 1; // DXT1
				break;
			}
		case GL_COMPRESSED_RGBA_S3TC_DXT3_EXT:
			{	
				method = 3;// DXT3
				break;
			}
		case GL_COMPRESSED_RGBA_S3TC_DXT5_EXT:
			{	
				method = 5; // DXT5
				break;
			}
		default:
			{
				assert(0);
				return 0;
			}
		}

		// compute the storage requirements
		int blockcount = ( ( width + 3 )/4 ) * ( ( height + 3 )/4 );
		int blocksize = ( method == 1 ) ? 8 : 16;
		return blockcount*blocksize;
	}
	//----------------------------------------------------------------
	long ImageUtility::getDdsFileStorage( const long& width , 
		const long& height , const GLenum& dds_format )
	{
		long ret = 0;

		ret += 4; // fourCC
		ret += sizeof( DDSURFACEDESC2 );

		ret += getDdsImageStorageRequirements(
			width , height, dds_format , true );

		return ret;
	}
	//----------------------------------------------------------------










}// end of namespace vgCore
