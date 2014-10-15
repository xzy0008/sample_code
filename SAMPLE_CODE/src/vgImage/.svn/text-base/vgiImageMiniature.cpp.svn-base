


#include <vgStableHeaders.h>
#include <vgKernel/vgkOpenGLSupport.h>
#include <vgImage/vgiImageMiniature.h>
#include <vgAsyn/vgaFileInfo.h>
#include <vgImage/vgiImageUtility.h>


namespace vgImage {

	//----------------------------------------------------------------
	ImageMiniature::ImageMiniature( VgiBrief* brief ,
		vgAsyn::FileHandle* pfilehandle   )
	{
		assert( brief != NULL );
		assert( pfilehandle != NULL );

		setDefault();

		//------------------------------------------
		// 赋值基本信息
		//------------------------------------------
		_pFilehandle = pfilehandle;
		_metaFileName = brief->_fileName;
		assert( _metaFileName.empty() == false );

		_metaFileOffset = brief->_metaFileOffset;
		assert( _metaFileOffset >= 0 );
		_metaFileSize = brief->_metaFileSize;
		assert( _metaFileSize > 0 );

		_height = brief->_height;
		_width = brief->_width;

		_openGLFormat = brief->_openGLFormat;

		for ( int i = 0; i < VGLOD_N ; ++ i )
		{
			//------------------------------------------
			// 注意!这里要转换相对的偏移为绝对的偏移
			//------------------------------------------
			_offsetLod[i] = brief->_offsetLod[i] + brief->_metaFileOffset;
			_sizeLod[i] = brief->_sizeLod[i];
			_mipMapLod[i] = brief->_mipMapLod[i];
		}

		_isValid = true;
	}
	//----------------------------------------------------------------
	void ImageMiniature::setDefault()
	{
		_height = 0;
		_width = 0;

		_openGLFormat = 0;

		for ( int i = 0 ; i < VGLOD_N ; ++i )
		{
			_offsetLod[i] = 0;
			_sizeLod[i] = 0;
			_mipMapLod[i] = 0;
		}

		_metaFileOffset = 0;
		_metaFileSize = 0;

		_isValid = false;
		_pFilehandle = NULL;
	}
	//----------------------------------------------------------------
	GLuint ImageMiniature::createTextureID( char* buf_input , const int& buf_size,
		const int& lod  )
	{
		if ( _isValid == false || buf_input == NULL || buf_size == 0 )
		{
			return VG_NULL_TEXTURE_ID;
		}

		//------------------------------------------
		// 开始创建Texture Id
		//------------------------------------------
		GLuint ntexid;

		int nSize = 0;
		int nOffset = 0;

		const long& nNumMipMaps = _mipMapLod[VGLOD_CLEAR];
		uint nWidth = _width;
		uint nHeight = _height;

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


		int divide = (int)pow( 2.0f , 
			_mipMapLod[VGLOD_CLEAR] - _mipMapLod[ lod ] );

		nWidth = _width / divide;
		nHeight = _height / divide;

		for( int i = 0; i < _mipMapLod[ lod ] ; ++i )
		{
			if( nWidth  == 0 ) nWidth  = 1;
			if( nHeight == 0 ) nHeight = 1;

			nSize = ImageUtility::getDdsImageStorageRequirements( 
				nWidth , nHeight , _openGLFormat , false );

			glCompressedTexImage2DARB( GL_TEXTURE_2D,
				i,			// 使之成为0级.
				_openGLFormat,
				nWidth ,nHeight,
				/*opt->mIfHasBorder*/0, nSize,
				buf_input + nOffset );

			nOffset += nSize;

			nWidth  /= 2;
			nHeight /= 2;
		}// end of for

		//------------------------------------------
		// 检查
		//------------------------------------------
		assert( nOffset == buf_size );


		VGK_CHECK_OPENGL_ERROR();

		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, 
			GL_LINEAR_MIPMAP_LINEAR);

		assert( ntexid != VG_NULL_TEXTURE_ID );

		return ntexid;
	}
	//----------------------------------------------------------------
	vgAsyn::FileInfo* ImageMiniature::getFileInfoByLod( const int& lod )
	{
		assert( lod < VGLOD_N );
		assert( lod >=0 );
		assert( VGLOD_N == 3 );

		if ( _isValid == false )
		{
			return NULL;
		}

		return new vgAsyn::FileInfo( _metaFileName , _pFilehandle , 
			_offsetLod[lod] , _sizeLod[lod] );
	}
	//----------------------------------------------------------------
	vgAsyn::FileInfo* ImageMiniature::getMetaFileInfo()
	{
		if ( _isValid == false )
		{
			return NULL;
		}

		return new vgAsyn::FileInfo( _metaFileName , _pFilehandle , 
			_metaFileOffset , _metaFileSize );
	}
	//----------------------------------------------------------------
}// end of namespace vgImage
