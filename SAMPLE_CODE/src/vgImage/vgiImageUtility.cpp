


#include <vgStableHeaders.h>
#include <vgImage/vgiImageUtility.h>
#include <vgKernel/vgkStringUtility.h>
#include <vgImage/vgiImage.h>
#include <vgImage/vgiDdsFileStructure.h>
#include <vgKernel/vgkStreamReader.h>



namespace vgImage {
	
	int ImageUtility::getNearestPowerOfTwoNumber( const int& inputNum )
	{
		if ( inputNum == 0 || inputNum < 0 )
		{
			assert(0);
			return 0 ;
		}

		int left = inputNum;

		int aim = 1;

		do 
		{
			left /= 2;

			aim *= 2;

		} while( left != 0);


		int s = aim/2;

		int b = aim;

		return ( (b - inputNum) >= ( inputNum - s) ) ? s : b;
	}
	
	int ImageUtility::getBiggerPowerOfTwoNumber( const int& inputNum )
	{
		if ( inputNum == 0 || inputNum < 0 )
		{
			assert(0);
			return 0 ;
		}

		int left = inputNum;

		int aim = 1;

		do 
		{
			left /= 2;

			aim *= 2;

		} while( left != 0);

		return aim;
	}


	int ImageUtility::getSmallerPowerOfTwoNumber( const int& inputNum )
	{
		if ( inputNum == 0 || inputNum < 0 )
		{
			assert(0);
			return 0 ;
		}

		int left = inputNum;

		int aim = 1;

		do 
		{
			left /= 2;

			aim *= 2;

		} while( left != 0);

		assert( aim / 2 != 0 );

		return aim / 2;
	}

	bool ImageUtility::checkImageSizeIsPowerOfTwo( const long& width,const long& height )
	{
		long w = width;
		long h = height;
		while ( (w & 0x0001) == 0 && w != 0 )
		{
			w = w >> 1;
		}
		while ( (h & 0x0001) == 0 && h != 0 )
		{
			h = h >> 1;
		}
		if ( w == 1 && h == 1)
		{
			return true;
		}
		return false;
	}

	String ImageUtility::findImageFileExtension( const String& filename )
	{
		std::string::size_type pos = filename.rfind('.');
		std::string ext = filename.substr(pos == std::string::npos ? filename.length() : pos + 1);
		transform(ext.begin(), ext.end(), ext.begin(), ::tolower);

		ext.erase(ext.find_last_not_of(' ') + 1);
		return ext;
	}


	String ImageUtility::findFilenameFromAbsolutePath( const String& abs_path )
	{
		return vgKernel::StringUtility::getFilenameFromAbsolutePath( abs_path );
	}
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
	uint ImageUtility::getMaxMipmapNum( const uint& width,const uint& height )
	{
		assert( width != -1 && height != -1 );

		unsigned int w = width;
		unsigned int h = height;
		unsigned int result = 0;
		while ( w!=0 || h!=0 )
		{
			result++;
			w /=2;
			h /=2;
		}
		return result;
	}
	//----------------------------------------------------------------
	bool ImageUtility::checkDdsImageIsEmpty( 
		const String& dds_abs_filepath, bool& out_isEmpty )
	{
		vgKernel::StreamReaderPtr preader = 
			vgKernel::StreamReaderFactory::createFromFile( dds_abs_filepath );

		if ( preader.isNull() == true )
		{
			return false;
		}

		long filesize = preader->size();
		assert( filesize != 0 );

		if ( filesize <= 0 )
		{
			return false;
		}

		char* buf = new char[ filesize ];
		memset( buf , 0 , filesize );

		long readnum = preader->read( buf , filesize );

		if ( readnum != filesize )
		{
			delete[] buf;
			return false;
		}

		// image接管buf的生命周期.不需要手动删除buf了.
		vgImage::Image ddsimg( buf , filesize );

		if ( ddsimg.isValid() == false )
		{
			return false;
		}

		char* pixeldata = (char*)ddsimg.getPixelDataPointer();
		long datasize  = ddsimg.getClearestLayerDataSize();

		out_isEmpty = true;

		for ( int i = 0 ; i < datasize ; ++ i )
		{
			if ( pixeldata[i] != 0 && pixeldata[i] != -1)
			{
				out_isEmpty = false;
				break;
			}
		}

		return true;
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

}// end of namespace vgImage


