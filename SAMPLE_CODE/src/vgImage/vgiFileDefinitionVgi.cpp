


#include <vgStableHeaders.h>
#include <vgImage/vgiFileDefinitionVgi.h>
#include <vgImage/vgiDdsFileStructure.h>
#include <vgImage/vgiImageUtility.h>
#include <vgKernel/vgkStringUtility.h>


namespace vgImage {
	
#define  VG_IMAGEMINI_LOD_COARSEST_SPECIFIC(maxMips)	((int)(maxMips/2))
#define  VG_IMAGEMINI_LOD_MEDIUM_SPECIFIC(maxMips)		((int)(maxMips/1.5))


	//----------------------------------------------------------------
	void VgiHeader::setDefault()
	{
		_fourCC[0] = 'V';
		_fourCC[1] = 'G';
		_fourCC[2] = 'I';
		_fourCC[3] = 0;

		_version = 1;
		_sizeOfWholeFile = 0;

		_sizeOfHeader = sizeof( VgiHeader );

		_numberOfBriefs		= 0;
		_lengthOfOneBrief		= sizeof( VgiBrief );
		_positionOfBriefs		= 0;
		//_reserved1		= 0;

		_nextFileID = 0;

		_reserved2		= 0;
		_reserved3		= 0;
		_reserved4		= 0;
	}
	//----------------------------------------------------------------


	//----------------------------------------------------------------
	void VgiBrief::setDefault()
	{
		memset( _fileName , 0 , VGI_NAME_LENGTH );

		_metaFileOffset = 0;
		_metaFileSize = 0;

		for ( int i = 0 ; i < VGLOD_N ; ++i )
		{
			_offsetLod[i] = 0;
			_sizeLod[i] = 0;
			_mipMapLod[i] = 0;
		}

		_width = 0;
		_height = 0;
		_openGLFormat = 0;

		_type = VGI_BRIEF_TYPE_DDS;
	}
	//----------------------------------------------------------------
	void VgiBrief::caluateLodOffsetAndSize()
	{
		assert( _metaFileOffset == 0 );
		assert( _metaFileSize != 0 );

		//------------------------------------------
		// 开始计算lod的偏移
		//------------------------------------------
		// lod == 2
		long head_size = sizeof( DDSURFACEDESC2 ) + 4;

		_offsetLod[2] = _metaFileOffset + head_size;
		_sizeLod[2] = _metaFileSize - head_size;

		// lod == 1 
		if ( _mipMapLod[VGLOD_CLEAR] < 4 )
		{
			assert(0);
		}

		{
			int halfMips = _mipMapLod[VGLOD_CLEAR] - _mipMapLod[VGLOD_CLEAR-1];
			int nWidth = _width;
			int nHeight = _height;
			int nSize = 0;
			int nOffset = 0;

			for( int i = 0; i < halfMips; ++i )
			{
				if( nWidth  == 0 ) nWidth  = 1;
				if( nHeight == 0 ) nHeight = 1;

				nSize = ImageUtility::getDdsImageStorageRequirements( 
					nWidth , nHeight , _openGLFormat , false );

				nOffset += nSize;

				nWidth  /= 2;
				nHeight /= 2;
			}// end of for

			_offsetLod[1] = _metaFileOffset + head_size + nOffset;
			_sizeLod[1] = _metaFileSize - head_size - nOffset;
		}

		// lod == 0
		{
			int mips = _mipMapLod[VGLOD_CLEAR] - _mipMapLod[VGLOD_CLEAR-2];
			int nWidth = _width;
			int nHeight = _height;
			int nSize = 0;
			int nOffset = 0;

			for( int i = 0; i < mips; ++i )
			{
				if( nWidth  == 0 ) nWidth  = 1;
				if( nHeight == 0 ) nHeight = 1;

				nSize = ImageUtility::getDdsImageStorageRequirements( 
					nWidth , nHeight , _openGLFormat , false );

				nOffset += nSize;

				nWidth  /= 2;
				nHeight /= 2;
			}// end of for

			_offsetLod[0] = _metaFileOffset + head_size + nOffset;
			_sizeLod[0] = _metaFileSize - head_size - nOffset;
		}

	}
	//----------------------------------------------------------------
	bool VgiBrief::getInfoFromBuffer( const String& filemetaname , 
		const char* const buffer, 
		const long& buffer_size )
	{
		assert( buffer != NULL );
		assert( buffer_size > 0 );

		if ( buffer == NULL || buffer_size <= 0 )
		{
			return false;
		}

		if ( filemetaname.size() >= VGI_NAME_LENGTH )
		{
			return false;
		}

		_type = VGI_BRIEF_TYPE_DDS;

		String upperName = filemetaname;
		StringUtility::toLowerCase( upperName );
		strcpy( _fileName , upperName.c_str() );
		assert( _fileName[ VGI_NAME_LENGTH - 1 ] == 0 );

		//------------------------------------------
		// 开始读取文件
		//------------------------------------------

		const char* const buf = buffer;
		long pos = 0;

		long mWidth = 0;
		long mHeight = 0;
		long mNumMipMaps = 0;
		char  mDdsFileCode[4];
		DDSURFACEDESC2 mDdsHeader;
		GLenum mOpenGLFormat = 0;


		memset( mDdsFileCode , 0 , 4 );
		memset( &mDdsHeader , 0 , sizeof( DDSURFACEDESC2 ) );


		memcpy( mDdsFileCode , buf + pos , 4 );
		pos += 4;

		if ( strncmp( mDdsFileCode , "DDS ", 4 ) != 0  )
		{
			MessageBox(NULL , "非DDS格式", "Error" , MB_OK );
			return false;
		}

		memcpy( &mDdsHeader , buf + pos , sizeof( DDSURFACEDESC2 ) );
		pos += sizeof( DDSURFACEDESC2 );


		switch( mDdsHeader.ddpfPixelFormat.dwFourCC )
		{
		case FOURCC_DXT1:
				mOpenGLFormat = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
				break;
		case FOURCC_DXT3:
				mOpenGLFormat = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
				break;
		case FOURCC_DXT5:
				mOpenGLFormat = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
				break;
		default:
			assert(0);
			MessageBox(NULL , "非支持的DDS格式", "Error" , MB_OK );
			return false;
		}

		mWidth = mDdsHeader.dwWidth;
		mHeight = mDdsHeader.dwHeight;
		mNumMipMaps = mDdsHeader.dwMipMapCount;

		if ( mNumMipMaps == 0 )
		{
			mNumMipMaps = getMaxMipmapNum( mWidth , mHeight );
			assert( mNumMipMaps != 0 );
		}

		//------------------------------------------
		// 开始校验
		//------------------------------------------
		long datalength =
			ImageUtility::getDdsImageStorageRequirements( mWidth , mHeight ,
			mOpenGLFormat , true );

		if ( (pos + datalength) != buffer_size )
		{
			return false;
		}

		//------------------------------------------
		// 开始赋值
		//------------------------------------------
		_width = mWidth;
		_height = mHeight;
		_openGLFormat = mOpenGLFormat;
		assert( mNumMipMaps > 0 );
		_mipMapLod[ VGLOD_CLEAR ] = mNumMipMaps;

		_mipMapLod[ VGLOD_COARSE ] = 
			VG_IMAGEMINI_LOD_COARSEST_SPECIFIC( mNumMipMaps );

		_mipMapLod[ VGLOD_COARSE + 1 ] =
			VG_IMAGEMINI_LOD_MEDIUM_SPECIFIC( mNumMipMaps );


		assert( pos < buffer_size );
		
		//------------------------------------------
		// 开始计算lod
		//------------------------------------------
		// _metaFileOffset在外部赋值,这里先不管它
		assert( _metaFileOffset == 0 );
		_metaFileSize = buffer_size;

		caluateLodOffsetAndSize();
	
		return true;
	}
	//----------------------------------------------------------------(
	long VgiBrief::getMaxMipmapNum( const long& width,const long& height )
	{
		assert( width != -1 && height != -1 );

		long w = width;
		long h = height;
		long result = 0;
		while ( w!=0 || h!=0 )
		{
			result++;
			w /=2;
			h /=2;
		}
		return result;
	}
	//----------------------------------------------------------------
	
	


}// end of namespace vgImage
