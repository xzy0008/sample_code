



#include <vgStableHeaders.h>
#include <vgImage/vgiImage.h>
#include <vgImage/vgiDdsFileStructure.h>
#include <vgKernel/vgkOpenGLSupport.h>


namespace vgImage {
	

	//----------------------------------------------------------------
	Image::Image( char* filebuf , long filesize )
	{
		setDefault();

		_fileBuffer = filebuf;
		_fileSize = filesize;

		_loadOK = loadFromMemory();
	}
	//----------------------------------------------------------------
	Image::~Image()
	{
		if ( _fileBuffer != NULL )
		{
			delete[] _fileBuffer;
			_fileBuffer = NULL;
		}

		setDefault();
	}
	//----------------------------------------------------------------


	//----------------------------------------------------------------
	bool Image::loadFromMemory()
	{
		assert( _fileBuffer != NULL );
		assert( _fileSize > 0 );

		char  mDdsFileCode[4];
		DDSURFACEDESC2 mDdsHeader;


		char* curFilePos = _fileBuffer;

		//------------------------------------------
		// 1.读取fourCC
		//------------------------------------------
		memcpy( mDdsFileCode ,  curFilePos , 4 );
		curFilePos += 4;

		if ( strncmp( mDdsFileCode , "DDS ", 4 ) != 0  )
		{
			assert(0);
			return false;
		}

		//------------------------------------------
		// 2.读取头文件信息
		//------------------------------------------
		memcpy( &mDdsHeader , curFilePos , sizeof( DDSURFACEDESC2 ) );
		curFilePos += sizeof( DDSURFACEDESC2 );

		switch( mDdsHeader.ddpfPixelFormat.dwFourCC )
		{
		case FOURCC_DXT1:
			{
				// DXT1's compression ratio is 8:1
				mOpenGLFormat = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
				//factor = 2;
				break;
			}
		case FOURCC_DXT3:
			{
				// DXT3's compression ratio is 4:1
				mOpenGLFormat = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
				//factor = 4;
				break;
			}
		case FOURCC_DXT5:
			{
				// DXT5's compression ratio is 4:1
				mOpenGLFormat = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
				//factor = 4;
				break;
			}
		default:
			{
				assert(0);

				return false;
			}
		}

		// 更新dwLinearSize为0的情况。
		if( mDdsHeader.dwLinearSize == 0 )
		{
			mDdsHeader.dwLinearSize =
				ImageUtility::getDdsImageStorageRequirements(
				mDdsHeader.dwWidth , mDdsHeader.dwHeight , 
				mOpenGLFormat , false );
		}

		//------------------------------------------
		// 3.计算数据区域长度,并检查
		//------------------------------------------
		long bufferSize = ImageUtility::getDdsImageStorageRequirements(
			mDdsHeader.dwWidth , mDdsHeader.dwHeight , 
			mOpenGLFormat , true );

		if ( bufferSize == 0 )
		{
			return false;
		}

		if ( (curFilePos + bufferSize) != (_fileBuffer + _fileSize ) )
		{
			assert(0);
			return false;
		}

		//------------------------------------------
		// 4.赋值各数据位
		//------------------------------------------
		mpPixelData = curFilePos;
		mPixelDataSize = bufferSize;

		mWidth      = mDdsHeader.dwWidth;
		mHeight     = mDdsHeader.dwHeight;
		mNumMipMaps = mDdsHeader.dwMipMapCount;

		//------------------------------------------
		// 最后,将标记位置位
		//------------------------------------------
		_loadOK = true;

		return true;
	}
	//----------------------------------------------------------------
	GLuint Image::createTextureIDImpletation()
	{
		GLuint ntexid;

		int nSize = 0;
		int nOffset = 0;

		long nNumMipMaps = mNumMipMaps;
		uint nWidth = mWidth;
		uint nHeight = mHeight;


		VGK_CHECK_OPENGL_ERROR();

		glGenTextures( 1, &ntexid );
		glBindTexture( GL_TEXTURE_2D, ntexid );

		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

		VGK_CHECK_OPENGL_ERROR();

		/// load All mipmaps situation.

		/////开启各异向性过滤.
		//if ( opt->mIfTurnOnFilterAnisotropic )
		//{

		//	if ( OpenGLSupport::checkTextureFilterAnisotropicSupport() )
		//	{
		//		OpenGLSupport::turnOnLargestTexFilterAnisotropic();
		//	}

		//	VGK_CHECK_OPENGL_ERROR();
		//}


		///// 处理border时的情况.
		//if ( opt->mIfHasBorder == true )
		//{
		//	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S ,GL_CLAMP_TO_EDGE);
		//	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T ,GL_CLAMP_TO_EDGE);

		//	VGK_CHECK_OPENGL_ERROR();
		//}

		for( int i = 0; i < nNumMipMaps; ++i )
		{
			if( nWidth  == 0 ) nWidth  = 1;
			if( nHeight == 0 ) nHeight = 1;

			nSize = ImageUtility::getDdsImageStorageRequirements( 
				nWidth , nHeight , mOpenGLFormat , false );

			glCompressedTexImage2DARB( GL_TEXTURE_2D,
				i,			// 使之成为0级.
				this->mOpenGLFormat,
				nWidth ,nHeight,
				/*opt->mIfHasBorder*/0, nSize,
				this->mpPixelData + nOffset );

			nOffset += nSize;

			nWidth  /= 2;
			nHeight /= 2;
		}// end of for


		VGK_CHECK_OPENGL_ERROR();

		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, 
			GL_LINEAR_MIPMAP_LINEAR);

		VGK_CHECK_OPENGL_ERROR();


		return ntexid;
	}
	//----------------------------------------------------------------
	GLuint Image::createTextureID()
	{
		if ( _loadOK == false )
		{
			return VG_NULL_TEXTURE_ID;
		}

		if( GL_ARB_texture_compression == false )
		{
			assert(0);
			return VG_NULL_TEXTURE_ID;
		}

		return createTextureIDImpletation();
	}
	//----------------------------------------------------------------
	void Image::setDefault()
	{
		mpPixelData = NULL;
		mPixelDataSize = 0;
		mWidth = 0;
		mHeight = 0;
 
		mOpenGLFormat = 0;
		mNumMipMaps = 0;

		_fileBuffer = NULL;
		_fileSize = 0;

		_loadOK = false;
	}
	//----------------------------------------------------------------
	long Image::getClearestLayerDataSize()
	{
		return ImageUtility::getDdsImageStorageRequirements( 
			mWidth , mHeight , mOpenGLFormat , false );
	}
	//----------------------------------------------------------------


}// end of namespace vgImage


