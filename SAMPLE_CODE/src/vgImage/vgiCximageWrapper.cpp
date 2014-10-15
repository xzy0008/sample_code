


#include <vgStableHeaders.h>
#include <vgImage/vgiCximageWrapper.h>
#include <vgImage/vgiImageUtility.h>
#include <vgImage/vgiDdsFileStructure.h>
#include <vgImage/vgiCompress.h>
#include <ximage.h>
#include <vgKernel/vgkException.h>


namespace vgImage {
	



	// 连通CxFile的接口
	class CxStreamReader : public CxFile
	{
	public:
		CxStreamReader( StreamReaderPtr preaderstream )
		{
			assert( !preaderstream.isNull() );
			assert( preaderstream->isValid() );
			m_pStreamReader = preaderstream;
		}
		~CxStreamReader()
		{

		}

		virtual bool	Close()
		{
			assert( isValid() );
			m_pStreamReader->close();
			return true;
		}

		virtual size_t	Read(void *buffer, size_t size, size_t count)
		{
			assert( isValid() );
			return m_pStreamReader->read( buffer , size * count );
		}


		virtual size_t	Write(const void *buffer, size_t size, size_t count)
		{
			assert( 0 && "StreamReader不能执行Write!");
			return 0;
		}
		virtual bool	Seek(long offset, int origin)
		{
			assert( isValid() );
			size_t now_pos = this->m_pStreamReader->tell();

			if (origin == SEEK_SET)		 
			{
				this->m_pStreamReader->seek( offset );
			}
			else if (origin == SEEK_CUR)
			{
				this->m_pStreamReader->seek( now_pos + offset );
			}
			else if (origin == SEEK_END)
			{
				size_t end_pos = this->m_pStreamReader->size();
				this->m_pStreamReader->seek( end_pos + offset );
			}
			else
			{
				return false;
			}

			return true;
		}
		virtual long	Tell()
		{
			assert( isValid() );
			return this->m_pStreamReader->tell();
		}

		virtual long	Size()
		{
			assert( isValid() );
			return this->m_pStreamReader->size();
		}
		virtual bool	Flush()
		{
			return true;
		}

		virtual bool	Eof()
		{
			return this->m_pStreamReader->eof();
		}

		virtual long	Error()
		{
			assert(0 && "正在执行Error()函数!");
			return 0;
		}

		virtual bool	PutC(unsigned char c)
		{
			assert( 0 && "StreamReader不能执行PutC!");
			return false;
		}
		virtual long	GetC() 
		{
			if (Eof()) 
			{
				return EOF;
			}

			BYTE result = 0; 
			this->m_pStreamReader->read( &result , sizeof( BYTE ) );

			return result;
			//return *(BYTE*)((BYTE*)m_pBuffer + m_Position++);
		}

		virtual char *	GetS(char *string, int n)
		{
			assert(0);
			return NULL;
		}
		virtual long	Scanf(const char *format, void* output)
		{
			assert(0);
			return 0;
		}

	private:

		bool isValid() const
		{
			if( m_pStreamReader.isNull() == false )
			{
				if( m_pStreamReader->isValid() == true )
				{
					return true;
				}
			}

			return false;
		}

	private:

		StreamReaderPtr m_pStreamReader;
	};



	// 连通CxFile的接口
	class CxStreamWriter : public CxFile
	{
	public:
		CxStreamWriter( StreamWriterPtr preaderstream )
		{
			assert( !preaderstream.isNull() );
			m_pStreamWriter = preaderstream;
		}
		~CxStreamWriter()
		{

		}

		virtual bool	Close()
		{
			assert( isValid() );
			m_pStreamWriter->close();
			return true;
		}

		virtual size_t	Read(void *buffer, size_t size, size_t count)
		{
			assert( 0 && "CxStreamWriter不能执行Read!");

			return 0;
		}

		virtual size_t	Write(const void *buffer, size_t size, size_t count)
		{
			this->m_pStreamWriter->write( (void*)buffer , size * count );
			return size * count;
		}

		virtual bool	Seek(long offset, int origin)
		{
			assert( isValid() );

			StreamWriterSeekMethod dir;

			if (origin == SEEK_SET)		 
			{
				dir = STREAMWRITER_SEEK_BEGIN;
			}
			else if (origin == SEEK_CUR)
			{
				dir = STREAMWRITER_SEEK_CURRENT;
			}
			else if (origin == SEEK_END)
			{
				dir = STREAMWRITER_SEEK_END;
			}
			else
			{
				return false;
			}

			this->m_pStreamWriter->seek( offset , dir );

			return true;
		}

		virtual long	Tell()
		{
			assert( isValid() );
			return this->m_pStreamWriter->tell();
		}

		virtual long	Size()
		{
			assert( 0 && "CxStreamWriter不能执行Size!");
			return 0;
		}
		virtual bool	Flush()
		{
			this->m_pStreamWriter->flush();
			return true;
		}

		virtual bool	Eof()
		{
			assert( 0 && "CxStreamWriter不能执行Eof!");
			return false;
		}

		virtual long	Error()
		{
			//assert(0 && "正在执行Error()函数!");
			return 0;
		}

		virtual bool	PutC(unsigned char c)
		{
			assert( isValid() );
			this->m_pStreamWriter->write( 
				(char*)( &c ) , sizeof( unsigned char ) );
			return true;
		}
		virtual long	GetC() 
		{
			assert( 0 && "CxStreamWriter不能执行GetC!");
			return 0;
		}

		virtual char *	GetS(char *string, int n)
		{
			assert(0);
			return NULL;
		}
		virtual long	Scanf(const char *format, void* output)
		{
			assert(0);
			return 0;
		}

	private:

		bool isValid() const
		{
			return !m_pStreamWriter.isNull();
		}

	private:

		StreamWriterPtr m_pStreamWriter;

	};


	enum  ImageFormat 
	{
		IMAGE_FORMAT_UNKNOWN	= CXIMAGE_FORMAT_UNKNOWN ,
		IMAGE_FORMAT_BMP		= CXIMAGE_FORMAT_BMP ,
		IMAGE_FORMAT_JPG		= CXIMAGE_FORMAT_JPG ,
		//IMAGE_FORMAT_GIF		= CXIMAGE_FORMAT_GIF ,
		IMAGE_FORMAT_PNG		= CXIMAGE_FORMAT_PNG ,
		IMAGE_FORMAT_TIF		= CXIMAGE_FORMAT_TIF ,
		IMAGE_FORMAT_TGA		= CXIMAGE_FORMAT_TGA ,
		//IMAGE_FORMAT_PCX		= CXIMAGE_FORMAT_PCX ,
		//IMAGE_FORMAT_WBMP		= CXIMAGE_FORMAT_WBMP ,
		//IMAGE_FORMAT_WMF		= CXIMAGE_FORMAT_WMF ,
		IMAGE_FORMAT_JP2		= CXIMAGE_FORMAT_JP2 ,
		//IMAGE_FORMAT_JPC		= CXIMAGE_FORMAT_JPC ,
		//IMAGE_FORMAT_PGX		= CXIMAGE_FORMAT_PGX ,
		//IMAGE_FORMAT_RAS		= CXIMAGE_FORMAT_RAS ,
		//IMAGE_FORMAT_PNM		= CXIMAGE_FORMAT_PNM ,
	};
	
	
	ImageFormat findImageFormat( const String& filename )
	{

		std::string::size_type pos = filename.rfind('.');
		std::string ext = filename.substr(pos == std::string::npos ? filename.length() : pos + 1);
		transform(ext.begin(), ext.end(), ext.begin(), ::tolower);

		ext.erase(ext.find_last_not_of(' ') + 1);

		if ( ext == "" )
		{
			return IMAGE_FORMAT_UNKNOWN;
		}

		ImageFormat type;

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
	
	bool getImageFormatInfo( const String& filename , long& width, long& height)
	{
		ImageFormat format = 
			findImageFormat( filename );

		assert ( format != IMAGE_FORMAT_UNKNOWN );

		//------------------------------------------
		// 读取文件
		//------------------------------------------
		vgKernel::StreamReaderPtr pstream = 
			vgKernel::StreamReaderFactory::createFromFile( filename );

		if( pstream.isNull() == true )
		{
			return false;
		}

		CxStreamReader cxfile( pstream );

		/**
		仅仅读取头文件
		*/
		if( CxImage::GetHeaderInfo( &cxfile , (DWORD)format , width , height ) 
			== false )
		{
			return false;
		}

		return true;
	}

	
	//----------------------------------------------------------------
	CximageWrapper::CximageWrapper()
	{
		this->mHeight = 0;
		this->mWidth = 0;
		this->mFilePath = "";

		this->mInitialised = false;

		/*this->mCximagePtr = NULL;*/
		this->mCximagePtr =  new CxImage;
	}

	CximageWrapper::CximageWrapper( CximagePtr cximg )
	{
		assert( cximg != NULL );
		// assert( mCximagePtr == NULL );
		// mCximagePtr 可能还没初始化

		this->mHeight = 0;
		this->mWidth = 0;
		this->mFilePath = "";

		this->mInitialised = false;

		this->mCximagePtr = cximg;




		updateSelfInfoFromCximage();
	}
	//----------------------------------------------------------------
	CximageWrapper::~CximageWrapper()
	{
		if ( mCximagePtr != NULL )
		{
			delete mCximagePtr;
			mCximagePtr = NULL;
		}
	}
	//----------------------------------------------------------------
	bool CximageWrapper::loadHeaderFromFile( const String& file_abs_path )
	{
		assert( mInitialised == false );

		vgKernel::StreamReaderPtr pstream = 
			vgKernel::StreamReaderFactory::createFromFile( file_abs_path );

		if ( pstream.isNull() )
		{
			return false;
		}

		ImageFormat format = findImageFormat( file_abs_path );

		if ( format == IMAGE_FORMAT_UNKNOWN )
		{
			return false;
		}

		long width,height;

		CxStreamReader cxfile( pstream );

		if( CxImage::GetHeaderInfo( &cxfile , format , width , height ) )
		{
			this->mFilePath = file_abs_path;
			this->mWidth = width;
			this->mHeight = height;
			this->mInitialised = false;

			return true;
		}

		return false;
	}
	//----------------------------------------------------------------
	bool CximageWrapper::loadFromFile( const String& file_abs_path )
	{
		assert( mInitialised == false );	 

		ImageFormat resFormat = findImageFormat( file_abs_path );

		if ( resFormat == IMAGE_FORMAT_UNKNOWN )
		{
			return false;
		}

		vgKernel::StreamReaderPtr pstream = 
			vgKernel::StreamReaderFactory::createFromFile( file_abs_path );

		if ( pstream.isNull() )
		{
			return false;
		}

		long bufsize = pstream->size();

		if ( bufsize == 0 )
		{
			return false;
		}

		byte* buf = new byte[ bufsize ];
		memset( buf, 0 , bufsize );

		size_t readnum = pstream->read( buf , bufsize );
		assert( readnum == bufsize );

		bool result = this->mCximagePtr->Decode( buf , bufsize , resFormat );

		if ( result )
		{
			updateSelfInfoFromCximage();
			mFilePath = file_abs_path;
			mInitialised = true;
		}

		delete[] buf;

		return result;
	}
	//----------------------------------------------------------------
	void CximageWrapper::updateSelfInfoFromCximage()
	{
		assert( mCximagePtr!= NULL );

		if ( mCximagePtr->IsValid() )
		{
			this->mInitialised = true;
			this->mWidth = mCximagePtr->GetWidth();
			this->mHeight = mCximagePtr->GetHeight();
		}

		return;
	}
	//----------------------------------------------------------------
	bool CximageWrapper::saveToFile( const String& output_filepath )
	{
		assert( mInitialised == true );

		if ( mInitialised == false )
		{
			return false;
		}

		vgKernel::StreamWriterPtr pstream = 
			vgKernel::StreamWriterFactory::createFromFile( output_filepath );

		if ( pstream.isNull() )
		{
			return false;
		}

		ImageFormat imgformat = findImageFormat( output_filepath );

		if ( imgformat == IMAGE_FORMAT_UNKNOWN )
		{
			return false;
		}

		//------------------------------------------
		// 先写到内存,然后再写入文件,这样加快速度.
		//------------------------------------------
		BYTE * buffer = NULL;
		long size = 0;

		const bool result = mCximagePtr->Encode( buffer , size , imgformat );
		assert( result == true );

		if ( buffer == NULL )
		{
			return false;
		}

		if ( result == false )
		{
			if ( buffer != NULL )
			{
				delete[] buffer;
			}
			return false;
		}

		size_t writenum = pstream->write( buffer , size );
		assert( writenum == size );

		delete[] buffer;

		return result;
	}
	//----------------------------------------------------------------
	bool CximageWrapper::saveToDdsFile( const String& file_abs_path ,
		const DdsFormat& dformat ,
		const bool& auto_resize_to_two_power/* = false */)
	{
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
				VGK_EXCEPT(Exception::ERR_INVALIDPARAMS ,
					"创建纹理参数错误," ,
					"saveDDS");
				assert( 0 && " 不支持的格式!! ");
				return false;
			}
		}

		return saveToDdsFile( file_abs_path , ddsFormat , auto_resize_to_two_power );

#if 0

		// 创建DDS头文件信息.
		// Save the image description
		DdsHeader dds;
		GLenum ddsFormat;
		memset(&dds, 0, sizeof(dds));
		dds.dwMagic  = *(DWORD*)"DDS ";
		dds.dwSize   = 124;
		// 此处改.
		dds.dwFlags  = DDSD_CAPS|DDSD_PIXELFORMAT|DDSD_WIDTH|DDSD_HEIGHT|DDSD_LINEARSIZE |
			DDSD_MIPMAPCOUNT ;
		dds.dwHeight = this->getHeight();
		dds.dwWidth  = this->getWidth();
		dds.ddsCaps.dwCaps1 = DDSCAPS_TEXTURE;
		dds.ddpfPixelFormat.dwSize = 32;

		//dds.dwFlags |= DDSD_LINEARSIZE;
		dds.ddpfPixelFormat.dwFlags |= DDPF_FOURCC;

		

		// Determine dimension aligned to 4 pixels
		UINT width = this->getWidth();
		if( width % 4 ) width += 4 - (width % 4);

		UINT height = this->getHeight();
		if( height % 4 ) height += 4 - (height % 4);

		//int method;
		int blockSize;

		switch( dformat )
		{
		case DDS_FORMAT_DXT1 : //SAVE_DDS_DXT1:
			{
				dds.ddpfPixelFormat.dwFourCC = *(DWORD*)"DXT1";
				blockSize = 8;
				ddsFormat = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
				break;
			}
		case DDS_FORMAT_DXT3 : //SAVE_DDS_DXT3:
			{
				dds.ddpfPixelFormat.dwFourCC = *(DWORD*)"DXT3";
				blockSize = 16;
				ddsFormat = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
				break;
			}
		case DDS_FORMAT_DXT5 : //SAVE_DDS_DXT5:
			{
				dds.ddpfPixelFormat.dwFourCC = *(DWORD*)"DXT5";
				blockSize = 16;
				ddsFormat = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
				break;
			}
		default:
			{
				VGK_EXCEPT(Exception::ERR_INVALIDPARAMS ,
					"创建纹理参数错误," ,
					"saveDDS");
				assert( 0 && " 不支持的格式!! ");
				return false;
			}
		}

		// Determine linear size
		dds.dwPitchOrLinearSize = width/4 * height/4 * blockSize;

		/// 赋予DDS的mipmap值
		uint maxmip = ImageUtility::getMaxMipmapNum( this->getWidth() , this->getHeight() );

		const uint& _miplevel = maxmip;

		dds.dwMipMapCount = _miplevel;
		dds.ddsCaps.dwCaps1 |= (DDSCAPS_MIPMAP |DDSCAPS_COMPLEX);

		/// 写入DDS headers
		pstream->write( &dds, sizeof(dds) );

		/// 临时的mip图像.
		CxImage mipCximage;


		for (unsigned int mipcount = 1 ; mipcount <= _miplevel ; ++ mipcount )
		{
			this->mCximagePtr->Resample2(width , height 
				, CxImage::IM_BICUBIC2 
				, CxImage::OM_REPEAT 
				, &mipCximage );


			BYTE* uncompressed_buf = NULL;
			long size;

			if(mipCximage.Encode2RGBA( uncompressed_buf , size))
			{
				int compress_size = 
					ImageUtility::getDdsImageStorageRequirements(
					width , height , ddsFormat , false );

				char* compress_buffer = new char[ compress_size ];
				assert( compress_buffer != 0 );


				Compress::processToBuffer(uncompressed_buf , width , height , compress_buffer , 
						ddsFormat );

				/// 写入流
				pstream->write( compress_buffer , compress_size );

				delete[] compress_buffer;
				compress_buffer = NULL;


				delete[] uncompressed_buf;
				uncompressed_buf = NULL;

			}
			else 
			{
				assert( 0 && "Encode2RGBA失败!");
				return false;
			}

			/// 释放临时文件.
			mipCximage.Destroy();
			if ( height != 1 )
			{
				height /= 2;
			}
			if ( width != 1 )
			{
				width /= 2;
			}
		}	// end of mipmap count.

		return true;
#endif

	}
	//----------------------------------------------------------------
	bool CximageWrapper::saveToDdsFile( const String& file_abs_path , 
		const GLenum& dds_format , 
		const bool& auto_resize_to_two_power /*= false*/ )
	{
		assert( dds_format == GL_COMPRESSED_RGBA_S3TC_DXT1_EXT ||
			dds_format == GL_COMPRESSED_RGBA_S3TC_DXT3_EXT || 
			dds_format == GL_COMPRESSED_RGBA_S3TC_DXT5_EXT );

		if ( ImageUtility::findImageFileExtension( file_abs_path ) != "dds" )
		{
			assert(0);
			return false;
		}

		// 确认已载入m_Cximage图像.
		assert( mInitialised == true );

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
				assert( 0 && "长宽并不完全符合2的n次方条件!");
				return false;
			}
			
			//------------------------------------------
			// 开始resize到2的n次方
			//------------------------------------------
			long adjust_width = ImageUtility::getSmallerPowerOfTwoNumber( getWidth() );
			long adjust_height = ImageUtility::getSmallerPowerOfTwoNumber( getHeight() );

			bool resizeok = resize( ImageSize( adjust_width , adjust_height ) );

			assert( resizeok == true );
		}

		//------------------------------------------
		// 使用新的函数来处理
		//------------------------------------------
		BYTE* uncompressed_buf = NULL;
		long size = 0;

		bool encodeok = mCximagePtr->Encode2BGRA( uncompressed_buf , size);
		if ( encodeok == false )
		{
			return false;
		}

		//////////////////////////////////////////////////////////////////////////

		//------------------------------------------
		// 转换到
		//------------------------------------------
		//BYTE* buffer = uncompressed_buf;
		//long bufsize = size;


		//		assert( bufsize % 4 == 0 );

		//		for ( int i = 0 ; i < bufsize / 4 ; ++ i )
		//		{		
		//			byte tmp = buffer[ 4 * i + 2 ];
		//			buffer[ 4 * i + 2 ] = buffer[ 4 * i ];
		//			buffer[ 4 * i ] = tmp;
		//		}


		//////////////////////////////////////////////////////////////////////////

		long filenum = Compress::processWholeFileToStream( uncompressed_buf , 
			getWidth(), getHeight() , pstream , dds_format );
		assert( filenum > 0 );

		delete[] uncompressed_buf;
		size = 0;

		return true;
	}
	//----------------------------------------------------------------
	bool CximageWrapper::crop( const ImageRect& rect ,
		CximageWrapperPtr pDstImg , const bool& axisLeftTop /*= true */ )
	{
		assert( mInitialised == true );

		if ( pDstImg.isNull() == true )
		{
			if ( axisLeftTop == true )
			{
				return mCximagePtr->Crop( rect.minPos.x , rect.minPos.y , 
					rect.maxPos.x ,rect.maxPos.y , NULL );
			}
			else
			{
				/// 坐标轴在左下角
				return mCximagePtr->Crop( rect.minPos.x , getHeight() - rect.maxPos.y , 
					rect.maxPos.x , getHeight() - rect.minPos.y , NULL );
			}
		}
		else
		{
			assert( pDstImg->mCximagePtr != NULL );

			if ( axisLeftTop == true )
			{
				if( mCximagePtr->Crop( rect.minPos.x , rect.minPos.y ,
					rect.maxPos.x ,rect.maxPos.y , pDstImg->mCximagePtr ) )
				{
					pDstImg->updateSelfInfoFromCximage();
					pDstImg->mInitialised = true;
					return true;
				}
				return false;
			}
			else
			{
				if( mCximagePtr->Crop( rect.minPos.x , getHeight() - rect.maxPos.y , 
					rect.maxPos.x , getHeight() - rect.minPos.y ,
					pDstImg->mCximagePtr ) )
				{
					pDstImg->updateSelfInfoFromCximage();
					pDstImg->mInitialised = true;
					return true;
				}
				return false;
			}

		}
	}
	//----------------------------------------------------------------
	bool CximageWrapper::drawString( const long& xoffset , 
		const long& yoffset , const String& text , 
		const String& font /*= "" */, const long& fontsize /*= 30 */,
		const bool& setAlpha /*= false */ )
	{
		assert( mInitialised == true );

		RGBQUAD color;
		color.rgbBlue = 0;
		color.rgbGreen = 0;
		color.rgbRed = 0;
		color.rgbReserved = 0;

		if ( mCximagePtr->DrawString(0 , xoffset , yoffset , 
			text.c_str() ,  color , font.c_str() , fontsize , 400 , 0 , 0 , setAlpha ) == 1 )
		{
			return true;
		}
		return false;
	}
	//----------------------------------------------------------------
	void CximageWrapper::overlap( CximageWrapper &imgsrc2, 
		const ImageRect& rect , const bool& axisLeftTop /*= true */ )
	{
		assert( mInitialised == true );

		//this->m_Cximage.Mix(imgsrc2.getCximage() ,CxImage::OpDstCopy ,rect.minPos.x , imgsrc2.getHeight() - getHeight() - rect.minPos.y );
		if ( axisLeftTop == true )
		{
			this->mCximagePtr->MixFrom2( *imgsrc2.mCximagePtr , 
				-rect.minPos.x , -imgsrc2.getHeight() + getHeight() + rect.minPos.y );
		}
		else
		{
			this->mCximagePtr->MixFrom2( *imgsrc2.mCximagePtr , 
				-rect.minPos.x , -rect.minPos.y );
		}
	}
	//----------------------------------------------------------------
	void CximageWrapper::overlap2( CximageWrapper &imgsrc2, const long& xoffset , 
		const long& yoffset  )
	{
		assert( mInitialised == true );

		//------------------------------------------
		// 注意!!MixFrom3都是以左下角为原点!!
		//------------------------------------------

		this->mCximagePtr->MixFrom3( *imgsrc2.mCximagePtr , 
				xoffset , getHeight() - imgsrc2.getHeight() - yoffset );

	}
	//----------------------------------------------------------------
	const CximageWrapperPtr CximageWrapper::resizeCopy(
		const ImageSize& imgSize ) const
	{
		assert( mInitialised == true );

		CximageWrapperPtr pNormalImg ( new CximageWrapper );

		if( this->mCximagePtr->Resample2(imgSize.getWidth() , imgSize.getHeight()
			, CxImage::IM_BICUBIC2 
			, CxImage::OM_REPEAT 
			, pNormalImg->mCximagePtr ) )
		{
			pNormalImg->mFilePath = this->getFilePath();
			pNormalImg->updateSelfInfoFromCximage();

			return pNormalImg;
		}

		// empty return .
		return CximageWrapperPtr();
	}
	//----------------------------------------------------------------
	bool CximageWrapper::resize( const ImageSize& imgSize )
	{
		assert( mInitialised == true );

		if( this->mCximagePtr->Resample2(imgSize.getWidth() , imgSize.getHeight()
			, CxImage::IM_BICUBIC2 
			, CxImage::OM_REPEAT 
			, NULL ) )
		{
			this->mWidth = imgSize.getWidth();
			this->mHeight = imgSize.getHeight();
			return true;
		}
		return false;
	}
	//----------------------------------------------------------------
	bool CximageWrapper::createFromSize( const long& dwWidth, const long& dwHeight ,
		const long& dBpp /*= 32 */ )
	{
		assert( mInitialised == false );

#if 1
		if( mCximagePtr->Create( dwWidth , dwHeight , dBpp ) == NULL )
		{
			return false;
		}

		mCximagePtr->AlphaCreate();

		assert( mCximagePtr->AlphaIsValid() );

		mCximagePtr->Clear( 0 );
		mCximagePtr->AlphaClear();

		this->updateSelfInfoFromCximage();

		this->mInitialised = true;

		return true;
#else

		assert( dBpp == 32 );
		byte* buf = new byte[ 4 * dwWidth * dwHeight ];

		memset( buf , 0  , 4 * dwWidth * dwHeight );

		bool create_result = 
			mCximagePtr->CreateFromArray( (BYTE*)buf , dwWidth , dwHeight , dBpp , 
			dwWidth * dBpp / 8 , false );

		if ( create_result == false )
		{
			delete buf;
			return false;
		}

		this->updateSelfInfoFromCximage();

		this->mInitialised = true;

		delete buf;

		return true;
#endif
	}
	//----------------------------------------------------------------
	bool CximageWrapper::createFromArray(  void* buf, const long& dwWidth, 
		const long& dwHeight , const long& dBpp /*= 24 */,bool bFlipImage /*= false */ ,
		bool reverse_R_and_B /*= false */)
	{
		assert( dwWidth > 0 );
		assert( dwHeight > 0 );
		assert( dBpp == 24 || dBpp == 32 );
	
		byte* buffer = (byte*)buf;

		if ( reverse_R_and_B == true )
		{
			long bufsize = dwWidth * dwHeight * dBpp / 8;
			assert( bufsize > 0 );
			buffer = new byte[ bufsize ];
			memset( buffer , 0 , bufsize );

			memcpy( buffer , buf , bufsize );

			if ( dBpp == 24 )
			{
				assert( bufsize % 3 == 0 );

				for ( int i = 0 ; i < bufsize / 3 ; ++ i )
				{		
					byte tmp = buffer[ 3 * i + 2 ];
					buffer[ 3 * i + 2 ] = buffer[ 3 * i ];
					buffer[ 3 * i ] = tmp;
				}
			}
			else if ( dBpp == 32 )
			{
				assert( bufsize % 4 == 0 );

				for ( int i = 0 ; i < bufsize / 4 ; ++ i )
				{		
					byte tmp = buffer[ 4 * i + 2 ];
					buffer[ 4 * i + 2 ] = buffer[ 4 * i ];
					buffer[ 4 * i ] = tmp;
				}
			}
		}

		bool create_result = 
			mCximagePtr->CreateFromArray( (BYTE*)buffer , dwWidth , dwHeight , dBpp , 
			dwWidth * dBpp / 8 , bFlipImage );

		if ( reverse_R_and_B == true )
		{
			delete[] buffer;
			buffer = NULL;
		}

		if ( create_result == false )
		{
			return false;
		}

		updateSelfInfoFromCximage();

		mInitialised = true;

		return true;
	}
	//----------------------------------------------------------------
	bool CximageWrapper::cxCreateFromArray( BYTE* pArray,DWORD dwWidth,
		DWORD dwHeight, DWORD dwBitsperpixel, DWORD dwBytesperline, 
		bool bFlipImage )
	{
		assert( dwWidth > 0 );
		assert( dwHeight > 0 );


		bool create_result = 
			mCximagePtr->CreateFromArray( pArray , dwWidth , dwHeight , dwBitsperpixel , 
			dwBytesperline , bFlipImage );

		if ( create_result == false )
		{
			return false;
		}

		updateSelfInfoFromCximage();

		mInitialised = true;

		return true;
	}
	//----------------------------------------------------------------
	bool CximageWrapper::saveToDdsFileWithBorderCheck( 
		const String& file_abs_path , const DdsFormat& dformat ,
		const bool& border_left_black , 
		const bool& border_up_black )
	{
		assert(0);

		assert( dformat == DDS_FORMAT_DXT1 ||
			dformat == DDS_FORMAT_DXT3 || 
			dformat == DDS_FORMAT_DXT5 );

		if ( ImageUtility::findImageFileExtension( file_abs_path ) != "dds" )
		{
			assert(0);
			return false;
		}

		// 确认已载入m_Cximage图像.
		assert( mInitialised == true );

		vgKernel::StreamWriterPtr pstream = 
			vgKernel::StreamWriterFactory::createFromFile( file_abs_path );

		if ( pstream.isNull() == true )
		{
			return false;
		}

		// 检查长宽是否是2的n次方.
		if ( !ImageUtility::checkImageSizeIsPowerOfTwo( this->getWidth() , 
			this->getHeight() ))
		{
			assert( 0 && "长宽并不完全符合2的n次方条件!");
			return false;
		}

		// 创建DDS头文件信息.
		// Save the image description
		DdsHeader dds;
		GLenum ddsFormat;
		memset(&dds, 0, sizeof(dds));
		dds.dwMagic  = *(DWORD*)"DDS ";
		dds.dwSize   = 124;
		// 此处改.
		dds.dwFlags  = DDSD_CAPS|DDSD_PIXELFORMAT|DDSD_WIDTH|DDSD_HEIGHT|DDSD_LINEARSIZE |
			DDSD_MIPMAPCOUNT ;
		dds.dwHeight = this->getHeight();
		dds.dwWidth  = this->getWidth();
		dds.ddsCaps.dwCaps1 = DDSCAPS_TEXTURE;
		dds.ddpfPixelFormat.dwSize = 32;

		//dds.dwFlags |= DDSD_LINEARSIZE;
		dds.ddpfPixelFormat.dwFlags |= DDPF_FOURCC;


		// Determine dimension aligned to 4 pixels
		UINT width = this->getWidth();
		if( width % 4 ) width += 4 - (width % 4);

		UINT height = this->getHeight();
		if( height % 4 ) height += 4 - (height % 4);

		//int method;
		int blockSize;

		switch( dformat )
		{
		case DDS_FORMAT_DXT1 : //SAVE_DDS_DXT1:
			{
				dds.ddpfPixelFormat.dwFourCC = *(DWORD*)"DXT1";
				blockSize = 8;
				ddsFormat = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
				break;
			}
		case DDS_FORMAT_DXT3 : //SAVE_DDS_DXT3:
			{
				dds.ddpfPixelFormat.dwFourCC = *(DWORD*)"DXT3";
				blockSize = 16;
				ddsFormat = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
				break;
			}
		case DDS_FORMAT_DXT5 : //SAVE_DDS_DXT5:
			{
				dds.ddpfPixelFormat.dwFourCC = *(DWORD*)"DXT5";
				blockSize = 16;
				ddsFormat = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
				break;
			}
		default:
			{
				VGK_EXCEPT(Exception::ERR_INVALIDPARAMS ,
					"创建纹理参数错误," ,
					"saveDDS");
				assert( 0 && " 不支持的格式!! ");
				return false;
			}
		}

		// Determine linear size
		dds.dwPitchOrLinearSize = width/4 * height/4 * blockSize;

		/// 赋予DDS的mipmap值
		uint maxmip = ImageUtility::getMaxMipmapNum( this->getWidth() , this->getHeight() );

		const uint& _miplevel = maxmip;

		dds.dwMipMapCount = _miplevel;
		dds.ddsCaps.dwCaps1 |= (DDSCAPS_MIPMAP |DDSCAPS_COMPLEX);

		/// 写入DDS headers
		pstream->write( &dds, sizeof(dds) );

		/// 临时的mip图像.
		CxImage mipCximage;

		for (unsigned int mipcount = 1 ; mipcount <= _miplevel ; ++ mipcount )
		{
			this->mCximagePtr->Resample2(width , height 
				, CxImage::IM_BICUBIC2 
				, CxImage::OM_REPEAT 
				, &mipCximage );


			BYTE* uncompressed_buf = NULL;
			long size;

			if(mipCximage.Encode2BGRA( uncompressed_buf , size))
			{
				//------------------------------------------
				// 检查border
				//------------------------------------------
				if ( border_left_black == true )
				{
					int i = 0;
					for ( int j = 0 ; j < height ; ++ j )
					{
						uncompressed_buf[ i * 4 + 4 * width * j ] = 0;
						uncompressed_buf[ i * 4 + 4 * width * j + 1] = 0;
						uncompressed_buf[ i * 4 + 4 * width * j + 2] = 0;
						uncompressed_buf[ i * 4 + 4 * width * j + 3] = 0;
					}
				}

				if ( border_up_black == true )
				{
					for ( int i = 0 ; i < width ; ++ i )
					{
						// 反转的
						int j = height - 1;
						uncompressed_buf[ i * 4 + 4 * width * j ] = 0;
						uncompressed_buf[ i * 4 + 4 * width * j + 1] = 0;
						uncompressed_buf[ i * 4 + 4 * width * j + 2] = 0;
						uncompressed_buf[ i * 4 + 4 * width * j + 3] = 0;
					}
				}


				int compress_size = 
					ImageUtility::getDdsImageStorageRequirements(
					width , height , ddsFormat , false );

				char* compress_buffer = new char[ compress_size ];
				assert( compress_buffer != 0 );


				Compress::processToBuffer(uncompressed_buf , width , height , compress_buffer , 
					ddsFormat );

				/// 写入流
				pstream->write( compress_buffer , compress_size );

				delete[] compress_buffer;
				compress_buffer = NULL;


				delete[] uncompressed_buf;
				uncompressed_buf = NULL;

			}
			else 
			{
				assert( 0 && "Encode2RGBA失败!");
				return false;
			}

			/// 释放临时文件.
			mipCximage.Destroy();
			if ( height != 1 )
			{
				height /= 2;
			}
			if ( width != 1 )
			{
				width /= 2;
			}
		}	// end of mipmap count.

		return true;
	}
	//----------------------------------------------------------------
	void CximageWrapper::release()
	{
		this->mHeight = 0;
		this->mWidth = 0;
		this->mFilePath = "";

		this->mInitialised = false;

		if ( mCximagePtr != NULL )
		{
			delete mCximagePtr;
			mCximagePtr = NULL;
		}

		this->mCximagePtr = new CxImage;
	}
	//----------------------------------------------------------------
	void CximageWrapper::clearColor( const RGBQUAD& color )
	{
		if ( mCximagePtr == NULL )
		{
			return;
		}

		if ( !mCximagePtr->IsValid() )
		{
			return;
		}

		int width = mCximagePtr->GetWidth();
		int height = mCximagePtr->GetHeight();

		for ( int i = 0 ; i < width ; ++ i )
		{
			for ( int j = 0 ; j < height ; ++ j )
			{
				mCximagePtr->SetPixelColor( i , j  , color , true );
			}
		}

		return;
	}
	//----------------------------------------------------------------
	void CximageWrapper::clearColor( const uchar& color_r , 
		const uchar& color_g , const uchar& color_b , const uchar& color_a )
	{
		RGBQUAD quad;
		quad.rgbRed = color_r;
		quad.rgbGreen = color_g;
		quad.rgbBlue = color_b;
		quad.rgbReserved = color_a;

		return clearColor( quad );
	}
	//----------------------------------------------------------------


}// end of namespace vgImage
