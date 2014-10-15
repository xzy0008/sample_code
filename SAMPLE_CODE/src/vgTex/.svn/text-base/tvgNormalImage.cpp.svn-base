

#include <vgStableHeaders.h>

#include <vgTex/tvgNormalImage.h>

#include <nvtt/nvtt.h>
#include <vgImage/vgiCompress.h>
#include <vgImage/vgiImageUtility.h>


namespace vgCore {
	
	
	//----------------------------------------------------------------
	bool NormalImage::loadFromArchiveFile( const String& filename , 
		const ImageFormat& imgformat /*= IMAGE_FORMAT_UNKNOWN */ )
	{
		StreamReaderPtr pFile = ArchiveManager::getSingleton().open( filename );

		ImageFormat resFormat = imgformat;

		if ( resFormat == IMAGE_FORMAT_UNKNOWN )
		{
			resFormat = ImageUtility::findImageFormat( filename );
		}

		return this->loadFromStream( pFile , filename , resFormat );

		/*

		assert( !isValid() );	/// 先这样写,检查错误.

		if ( imgformat == IMAGE_FORMAT_DDS )
		{
			return false;
		}

		if ( imgformat == IMAGE_FORMAT_UNKNOWN )
		{
			ImageFormat t = ImageUtility::findImageFormat( filename );

			if ( t == IMAGE_FORMAT_UNKNOWN 
				|| t == IMAGE_FORMAT_DDS )
			{
				return false;
			}

			if( this->mCximagePtr->Load( filename.c_str() , t ) )
			{
				this->mFilePath = filename;
				this->updateSelfInfoFromCximage();
				return true;
			}
			return false;
		}
		else
		{
			if( this->mCximagePtr->Load( filename.c_str() , imgformat ) )
			{
				this->mFilePath = filename;
				this->updateSelfInfoFromCximage();
				return true;
			}
			return false;
		}
		*/
	}
	//----------------------------------------------------------------
	bool NormalImage::loadFromHeaderInfo( const String& filename ,  
		const ImageFormat& imgformat /*= IMAGE_FORMAT_UNKNOWN */ )
	{
		return this->loadFromHeaderInfo( 
			ArchiveManager::getSingleton().open( filename ) , filename , imgformat );
	}
	//----------------------------------------------------------------
	bool NormalImage::loadFromHeaderInfo( const StreamReaderPtr& pstream , 
		const String& filename , const ImageFormat& imgformat /*= IMAGE_FORMAT_UNKNOWN */ )
	{
		assert( !isValid() );	/// 先这样写,检查错误.

		ImageFormat resFormat = imgformat;

		if ( pstream.isNull() )
		{
			return false;
		}

		if ( resFormat == IMAGE_FORMAT_DDS )
		{
			return false;
		}

		if ( resFormat == IMAGE_FORMAT_UNKNOWN )
		{
			resFormat = ImageUtility::findImageFormat( filename );

			if ( resFormat == IMAGE_FORMAT_UNKNOWN 
				|| resFormat == IMAGE_FORMAT_DDS )
			{
				return false;
			}
		}

		// 如果仍然为非支持格式
		if ( resFormat == IMAGE_FORMAT_UNKNOWN 
			|| resFormat == IMAGE_FORMAT_DDS )
		{
			return false;
		}

		// everything ok,let's do it

		Integer width,height;

		CxStreamReader cxfile( pstream );

		if( CxImage::GetHeaderInfo( &cxfile , resFormat , width , height ) )
		{
			this->mFilePath = filename;
			this->mWidth = width;
			this->mHeight = height;
			this->mInitialised = false;
			this->mTextureFlag = TEXTURE_FLAG_TEXTURE_2D;
			this->mTexPixelFormat = TEXTURE_PIXFORMAT_UNKOWN;
			return true;
		}
		return false;
	}
	//----------------------------------------------------------------
	bool NormalImage::saveToFile( const String& filename ,  
		const ImageFormat& imgformat /*= IMAGE_FORMAT_UNKNOWN */, 
		const DdsFormat& ddsformat /*= DDS_FORMAT_DEFAULT */ )
	{
		assert( isValid() );
		//StreamWriterPtr ppstream( new FileStreamWriter( filename ) );

		ImageFormat resFormat = imgformat;
		if ( imgformat == IMAGE_FORMAT_UNKNOWN )
		{
			resFormat = ImageUtility::findImageFormat( filename );
		}

		return this->saveToStream( 
			StreamFactory::createWriterFromFile( filename ) , resFormat , ddsformat );
	}
	//----------------------------------------------------------------
	bool NormalImage::saveToDdsFromCximage( const String& ddsfile ,  
		const DdsFormat& dformat /*= DDS_FORMAT_DEFAULT */ )
	{
		return this->saveToDdsFromCximage( 
			StreamFactory::createWriterFromFile( ddsfile ) , dformat );

		/*
		assert( dformat == DDS_FORMAT_DXT1 ||
			dformat == DDS_FORMAT_DXT3 || 
			dformat == DDS_FORMAT_DXT5 ||
			dformat  == DDS_FORMAT_A8R8G8B8 );

		if ( dformat == DDS_FORMAT_A8R8G8B8 )
		{
			return this->saveDdsUsingA8R8G8B8( ddsfile );
		}

		// 确认已载入m_Cximage图像.
		assert( isValid() );

		if ( !isValid() )
		{
			return false;
		}

		// 创建文件句柄.
		// Open the file
		FILE *f = fopen( ddsfile.c_str() , "wb");
		if( f == 0 ) 
		{
			assert( 0 && "文件写入失败!");
			return false;
		}

		// 检查长宽是否是2的n次方.
		if ( !ImageUtility::checkImageSizeIsPowerOfTwo( this->getWidth() , 
			this->getHeight() ))
		{
			assert( 0 && "长宽并不完全符合2的n次方条件!");
		}

		// 创建DDS头文件信息.
		// Save the image description
		DdsHeader dds;
		memset(&dds, 0, sizeof(dds));
		dds.dwMagic  = *(DWORD*)"DDS ";
		dds.dwSize   = 124;
		// 此处改.
		dds.dwFlags  = DDSD_CAPS|DDSD_PIXELFORMAT|DDSD_WIDTH|DDSD_HEIGHT|DDSD_LINEARSIZE ;
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

		int method;
		int blockSize;
		int flag;

		switch( dformat )
		{
		case DDS_FORMAT_DXT1 : //SAVE_DDS_DXT1:
			{
				dds.ddpfPixelFormat.dwFourCC = *(DWORD*)"DXT1";
				blockSize = 8;
				method = squish::kDxt1;
				flag = acImage::DDS_DXT1;
				break;
			}
		case DDS_FORMAT_DXT3 : //SAVE_DDS_DXT3:
			{
				dds.ddpfPixelFormat.dwFourCC = *(DWORD*)"DXT3";
				blockSize = 16;
				method = squish::kDxt3;
				flag = acImage::DDS_DXT3;
				break;
			}
		case DDS_FORMAT_DXT5 : //SAVE_DDS_DXT5:
			{
				dds.ddpfPixelFormat.dwFourCC = *(DWORD*)"DXT5";
				blockSize = 16;
				method = squish::kDxt5;
				flag = acImage::DDS_DXT5;
				break;
			}
		default:
			{
				VG_EXCEPT(Exception::ERR_INVALIDPARAMS ,
					"创建纹理参数错误," ,
					"saveDDS");
				assert( 0 && " 不支持的格式!! ");
				return false;
			}
		}

		// Determine linear size
		dds.dwPitchOrLinearSize = width/4 * height/4 * blockSize;

		/// 赋予DDS的mipmap值
		unsigned int maxmip = ImageUtility::getMaxMipmapNum( this->getWidth() , this->getHeight() );

		/// here , we should not use the texOption.miplevel,
		/// but use the calculated miplevel.
		unsigned int _miplevel ;

		_miplevel = maxmip;

		dds.dwMipMapCount = _miplevel;
		dds.ddsCaps.dwCaps1 |= (DDSCAPS_MIPMAP |DDSCAPS_COMPLEX);

		/// 写入DDS headers
		fwrite(&dds, sizeof(dds), 1, f);

		/// 临时的mip图像.
		CxImage mipCximage;

		for (unsigned int mipcount = 1 ; mipcount <= _miplevel ; ++ mipcount )
		{
			this->mCximagePtr->Resample2(width , height 
				, CxImage::IM_BICUBIC2 
				, CxImage::OM_REPEAT 
				, &mipCximage );

			//注意这个地方!!!!!!!!!要保证有alpha通道!!!!!!!!

			acImage::Image mipacImage;

			long size;
			if(mipCximage.EncodeToA8R8G8B8( mipacImage.data , size))
			{
				mipacImage.numColours = 0;
				mipacImage.width = width;
				mipacImage.height = height;
				mipacImage.format = acImage::PF_A8R8G8B8;
				mipacImage.pitch = mipacImage.width * 4;

				BYTE* mipmemblocks = NULL;
				unsigned int mipmemsize = 0;

				if ( !acImage::CodeToMemory( mipmemblocks ,mipmemsize ,mipacImage,flag))
				{
					assert( 0 && " CodeToMemory出错!!");
					return false;
				}

				/// 写入文件
				fwrite(mipmemblocks , mipmemsize , 1 , f);
				delete mipmemblocks;
			}
			else 
			{
				assert( 0 && "EncodeToA8R8G8B8失败!");
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

		/// 关闭文件
		fclose(f);
		return true;
		*/
	}
	//----------------------------------------------------------------
	bool NormalImage::saveToDdsFromCximage( const StreamWriterPtr& pstream , 
		const DdsFormat& dformat /*= DDS_FORMAT_DEFAULT */ )
	{
		assert( dformat == DDS_FORMAT_DXT1 ||
			dformat == DDS_FORMAT_DXT3 || 
			dformat == DDS_FORMAT_DXT5 ||
			dformat  == DDS_FORMAT_A8R8G8B8 );

		if ( dformat == DDS_FORMAT_A8R8G8B8 )
		{
			return this->saveDdsUsingA8R8G8B8( pstream );
		}

		// 确认已载入m_Cximage图像.
		assert( isValid() );

		if ( !isValid() )
		{
			return false;
		}

		// 检查长宽是否是2的n次方.
		if ( !ImageUtility::checkImageSizeIsPowerOfTwo( this->getWidth() , 
			this->getHeight() ))
		{
			assert( 0 && "长宽并不完全符合2的n次方条件!");
		}

		// 创建DDS头文件信息.
		// Save the image description
		DdsHeader dds;
		memset(&dds, 0, sizeof(dds));
		dds.dwMagic  = *(DWORD*)"DDS ";
		dds.dwSize   = 124;
		// 此处改.
		dds.dwFlags  = DDSD_CAPS|DDSD_PIXELFORMAT|DDSD_WIDTH|DDSD_HEIGHT|DDSD_LINEARSIZE ;
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

		GLenum method;
		int blockSize;

		switch( dformat )
		{
		case DDS_FORMAT_DXT1 : //SAVE_DDS_DXT1:
			{
				dds.ddpfPixelFormat.dwFourCC = *(DWORD*)"DXT1";
				blockSize = 8;
				method = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
				break;
			}
		case DDS_FORMAT_DXT3 : //SAVE_DDS_DXT3:
			{
				dds.ddpfPixelFormat.dwFourCC = *(DWORD*)"DXT3";
				blockSize = 16;
				method = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
				break;
			}
		case DDS_FORMAT_DXT5 : //SAVE_DDS_DXT5:
			{
				dds.ddpfPixelFormat.dwFourCC = *(DWORD*)"DXT5";
				blockSize = 16;
				method = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
				break;
			}
		default:
			{
				VG_EXCEPT(Exception::ERR_INVALIDPARAMS ,
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
		pstream->write( (const char*)&dds, sizeof(dds) );

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
					vgImage::ImageUtility::getDdsImageStorage( width , height , method );

				char* compress_buffer = new char[ compress_size ];
				assert( compress_buffer != 0 );
					
				vgImage::Compress::processToBuffer( uncompressed_buf , width , height , compress_buffer , method );

				/// 写入流
				pstream->write( (const char*)compress_buffer , compress_size );

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
	bool NormalImage::saveDdsUsingA8R8G8B8( const String& ddsfile )
	{
		return this->saveDdsUsingA8R8G8B8( 
			StreamFactory::createWriterFromFile( ddsfile ) );
	}
	//----------------------------------------------------------------
	bool NormalImage::saveDdsUsingA8R8G8B8( const StreamWriterPtr& pstream )
	{

		assert(0);
		return true;

#if 0
		assert( isValid() );

		if ( !isValid() )
		{
			return false;
		}

		acImage::Image mipacImage;

		long size;
		if( mCximagePtr->EncodeToA8R8G8B8( mipacImage.data , size))
		{
			mipacImage.numColours = 0;
			mipacImage.width = this->getWidth();
			mipacImage.height = this->getHeight();
			mipacImage.format = acImage::PF_A8R8G8B8;
			mipacImage.pitch = mipacImage.width * 4;

			assert(size == mipacImage.pitch * mipacImage.height );
		}
		else
		{
			assert( 0 && "EncodeToA8R8G8B8出错!");
			return false;
		}

		BYTE* buf = NULL;
		long buf_size = 0;
		int saveResult = acImage::SaveDdsToMemory( buf , buf_size , mipacImage , 0 );
		if(  saveResult == 0 )	//使之产生A8R8G8B8的文件.
		{
			pstream->write( (const char*)buf , buf_size );
			delete[] buf;
			buf = NULL;

			return true;
		}
		else if( saveResult == -3 )		//打开文件失败!
		{
			delete[] buf;
			buf = NULL;
			assert( 0 && "打开文件失败!");
			return false;
		}
		else
		{
			delete[] buf;
			buf = NULL;
			assert( 0 && "未生成成功");
			return false;
		}
#endif
	}
	//----------------------------------------------------------------
	vgCore::TexturePtr NormalImage::createUnbindedTexPtr( 
		const TextureBuildOptionPtr& option /*= TextureBuildOptionPtr::DEFAULT_OPTION */ )
	{
		assert( !option.isNull() );

		const uint& texid = this->createTextureID( option );

		if( texid == -1 )
		{
			return TexturePtr::EmptyTexturePtr;
		}

		TexturePtr ptex( new Texture );

		ptex->makeUnbindedFromUndefined( texid , mFilePath ,
			this->getWidth() , this->getHeight() ,option->mTexPixelFormat , 
			TEXTURE_FLAG_TEXTURE_2D , option );

		return ptex;
	}
	//----------------------------------------------------------------
	uint NormalImage::createTextureID( 
		const TextureBuildOptionPtr& option /*= TextureBuildOptionPtr::DEFAULT_OPTION */ )
	{
		assert( !option.isNull() );

		///主要要添加RGB_mode 的代码。
		if ( !isValid() )
		{
			assert( 0 && "纹理没有载入，图像内容为空，无法创建纹理" );
			VG_EXCEPT(Exception::ERR_FILE_NOT_FOUND 
				,"纹理没有载入，图像内容为空，无法创建纹理" 
				, "UniformImageFile::CreateTexture()");

			return -1;
		}

		///要检查是否是2的整数倍。
		int				biBitCount = (int)this->mCximagePtr->GetBpp();
		unsigned char	*buffer = NULL;
		long			size = 0;
		int				width = this->getWidth();
		int				height = this->getHeight();
		unsigned int	texid = 0;
		bool			alphasupport = this->mCximagePtr->AlphaIsValid();

		switch( biBitCount )
		{
		case 1:
		case 4:
		case 8:
			{
				this->mCximagePtr->IncreaseBpp(24);
			}
		case 24:		///还有别的要检查，以后添加。
			{


				TexturePixelFormat format = option->mTexPixelFormat;
				
				if ( format != TEXTURE_PIXFORMAT_RGB 
					&& format != TEXTURE_PIXFORMAT_RGBA)
				{
					VG_WARN( Warning::WARN_INVALIDPARAMS ,
						Warning::BUTTON_NONE,
						"TextureBuildOptionPtr参数不正确,已被纠正.",
						"NormalImage::createTextureID()");

					format = this->mTexPixelFormat;
				}

				switch( format )
				{
				case TEXTURE_PIXFORMAT_RGB:
					{
						if (!this->mCximagePtr->Encode2RGB(buffer,size))
						{
							VG_EXCEPT(Exception::ERR_INTERNAL_ERROR
								,"Encode2RGB()失败,内部错误." 
								, "UniformImageFile::CreateTexture()");
							return -1;
						}
						break;	//end of case RGB
					}	
				case TEXTURE_PIXFORMAT_RGBA:
					{
						if (!this->mCximagePtr->Encode2RGBA(buffer,size))
						{
							VG_EXCEPT(Exception::ERR_INTERNAL_ERROR
								,"Encode2RGBA()失败,内部错误." 
								, "UniformImageFile::CreateTexture()");
							return -1;
						}
						break;
					}
				default:
					{
						VG_EXCEPT(Exception::ERR_INTERNAL_ERROR
							,"Encode2RGBA()失败,内部错误." 
							, "UniformImageFile::CreateTexture()");

						return -1;
					}
				}
				break;	//end of case 24
			}
		default:
			{
				return -1;
			}
		}

		// make sure there is no error msg
		OpenGLSupport::makeErrorStackEmpty();
		String errMessage;

		if ( option->mTexPixelFormat == TEXTURE_PIXFORMAT_RGB )
		{
			glGenTextures(1, &texid);
			
			if( OpenGLSupport::checkOpenGLErrorWithoutThrow( errMessage ) )
			{
				/// free buf
				if ( buffer )
				{
					free( buffer );
				}

				VG_EXCEPT(Exception::ERR_RENDERINGAPI_ERROR ,
					"glGenTextures failed! Error Code: " + errMessage ,
					"NormalImage::createTextureID()");

				return -1;
			}


			glBindTexture(GL_TEXTURE_2D, texid );
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
			glTexImage2D(GL_TEXTURE_2D, 0, 3, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, buffer );

			if ( option->mIfGenMipmap )
			{
				glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR );  
				glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR_MIPMAP_LINEAR ); 
				gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB , width , height , GL_RGB , GL_UNSIGNED_BYTE, buffer );
			}

			VG_CHECK_OPENGL_ERROR();
		}
		else	// for the condition: TEXTURE_PIXFORMAT_RGBA
		{
			glGenTextures(1, &texid);

			if( OpenGLSupport::checkOpenGLErrorWithoutThrow( errMessage ) )
			{
				/// free buf
				if ( buffer )
				{
					free( buffer );
				}

				VG_EXCEPT(Exception::ERR_RENDERINGAPI_ERROR ,
					"glGenTextures failed! Error Code: " + errMessage ,
					"NormalImage::createTextureID()");

				return -1;
			}


			glBindTexture(GL_TEXTURE_2D, texid );
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
			glTexImage2D(GL_TEXTURE_2D, 0, 4, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, buffer );

			//glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S ,GL_CLAMP);
			//glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T ,GL_CLAMP);
			//////////////////////////////////////////////////////////////////////////

			if ( option->mIfGenMipmap )
			{
				glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR );  
				glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR_MIPMAP_LINEAR ); 
				gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA , width , height , GL_RGBA , GL_UNSIGNED_BYTE, buffer );
			}

			VG_CHECK_OPENGL_ERROR();
		}

		/// free buf
		if ( buffer )
		{
			free( buffer );
		}

		return texid;
	}
	//----------------------------------------------------------------
	bool NormalImage::loadAlphaFile( const String& alphafile )
	{
		assert( isValid() );

		CximagePtr pximg( new CxImage() );

		ImageFormat iformat = ImageUtility::findImageFormat( alphafile );

		assert( iformat != IMAGE_FORMAT_DDS );

		///若载入失败
		if ( !pximg->Load( alphafile.c_str() , iformat ) )
		{
			return false;
		}

		if ( pximg->IsGrayScale() )	///若为8位灰度模式，此时方便处理
		{
			if( this->mCximagePtr->AlphaSet( *pximg ) )
			{
				this->mAlphaFilePath = alphafile;
				return true;		///成功返回
			}

			return false;		
		}
		else	///不为灰度模式时，处理成灰度模式
		{
			if( !pximg->GrayScale() )		///处理成灰度未成功时
			{
				return false;
			}

			if( this->mCximagePtr->AlphaSet( *pximg ) )
			{
				this->mAlphaFilePath = alphafile;
				return true;		///成功返回
			}
				
			return false;
		}
	}
	//----------------------------------------------------------------
	void NormalImage::setParametersDefault()
	{
		this->mHeight = DEFAULT_IMAGE_WIDTH;
		this->mWidth = DEFAULT_IMAGE_HEIGHT;
		this->mFilePath = "";
		this->mAlphaFilePath = "";

		this->mInitialised = false;

		this->mTextureFlag = TEXTURE_FLAG_UNINITIALISED;
		this->mTexPixelFormat = TEXTURE_PIXFORMAT_UNKOWN;
		this->mCximagePtr.setNull();
		this->mCximagePtr.bind( new CxImage );
	}
	//----------------------------------------------------------------
	void NormalImage::updateSelfInfoFromCximage()
	{
		assert( !mCximagePtr.isNull() );
		assert( mCximagePtr->IsValid() );

		this->mWidth = mCximagePtr->GetWidth();
		this->mHeight = mCximagePtr->GetHeight();
		if ( mCximagePtr->IsValid() )
		{
			this->mInitialised = true;
		}

		this->mTextureFlag = TEXTURE_FLAG_TEXTURE_2D;

		if ( mCximagePtr->AlphaIsValid() )
		{
			this->mTexPixelFormat = TEXTURE_PIXFORMAT_RGBA;
		}
		else
		{
			this->mTexPixelFormat = TEXTURE_PIXFORMAT_RGB;
		}
		return;
	}
	//----------------------------------------------------------------
	bool NormalImage::crop( const ImageRect& rect , NormalImagePtr pDstImg , 
		const bool& axisLeftTop /*= true */ )
	{
		assert( isValid() );

		if ( pDstImg.isNull() )
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
			assert( !pDstImg->mCximagePtr.isNull() );

			if ( axisLeftTop == true )
			{
				if( mCximagePtr->Crop( rect.minPos.x , rect.minPos.y ,
					rect.maxPos.x ,rect.maxPos.y , pDstImg->mCximagePtr.getPointer() ) )
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
					pDstImg->mCximagePtr.getPointer() ) )
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
	bool NormalImage::drawString( const Integer& xoffset ,  const Integer& yoffset ,
		const String& text ,  const vgMath::ColorValue& color , const string& font /*= "" */, 
		const Integer& fontsize /*= 30 */, const bool& setAlpha /*= false */ )
	{
		assert( isValid() );

		if ( mCximagePtr->DrawString(0 , xoffset , yoffset , 
			text.c_str() , color.getAsRGBQUAD() , font.c_str() , fontsize , 400 , 0 , 0 , setAlpha ) == 1 )
		{
			return true;
		}
		return false;
	}
	//----------------------------------------------------------------
	void NormalImage::overlap( NormalImage &imgsrc2, const ImageRect& rect ,  const bool& axisLeftTop /*= true */ )
	{
		assert( isValid() );
		//this->m_Cximage.Mix(imgsrc2.getCximage() ,CxImage::OpDstCopy ,rect.minPos.x , imgsrc2.getHeight() - getHeight() - rect.minPos.y );
		if ( axisLeftTop == true )
		{
			this->mCximagePtr->MixFrom( *imgsrc2.mCximagePtr , 
				-rect.minPos.x , -imgsrc2.getHeight() + getHeight() + rect.minPos.y );
		}
		else
		{
			this->mCximagePtr->MixFrom( *imgsrc2.mCximagePtr , 
				-rect.minPos.x , -rect.minPos.y );
		}
	}
	//----------------------------------------------------------------
	bool NormalImage::createFromSize( const Integer& dwWidth, const Integer& dwHeight , const Integer& dBpp /*= 24 */ )
	{
		if( mCximagePtr->Create( dwWidth , dwHeight , dBpp ) == NULL )
		{
			return false;
		}

		this->updateSelfInfoFromCximage();

		this->mInitialised = true;
		return true;
	}
	//----------------------------------------------------------------
	bool NormalImage::resize( const ImageSize& imgSize )
	{
		assert( isValid() );

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
	const NormalImagePtr NormalImage::resizeCopy( const ImageSize& imgSize ) const
	{
		assert( isValid() );

		NormalImagePtr pNormalImg ( new NormalImage );

		if( this->mCximagePtr->Resample2(imgSize.getWidth() , imgSize.getHeight()
			, CxImage::IM_BICUBIC2 
			, CxImage::OM_REPEAT 
			, pNormalImg->mCximagePtr.getPointer() ) )
		{
			pNormalImg->mFilePath = this->getFilePath();
			pNormalImg->updateSelfInfoFromCximage();

			return pNormalImg;
		}

		// empty return .
		return NormalImagePtr();
	}
	//----------------------------------------------------------------
	bool NormalImage::buildTextureByGLEnum( GLenum target )
	{
		///主要要添加RGB_mode 的代码。
		if ( !isValid() )
		{
			assert( 0 && "纹理没有载入，图像内容为空，无法创建纹理" );
			VG_EXCEPT(Exception::ERR_FILE_NOT_FOUND 
				,"纹理没有载入，图像内容为空，无法创建纹理" 
				, "UniformImageFile::CreateTexture()");

			return -1;
		}

		unsigned char	*buffer = NULL;
		long			size = 0;

		int				lWidthPixels = this->getWidth();
		int				lHeightPixels = this->getHeight();


		if (!this->mCximagePtr->Encode2RGB(buffer,size))
		{
			VG_EXCEPT(Exception::ERR_INTERNAL_ERROR
				,"Encode2RGB()失败,内部错误." 
				, "NormalImage::buildTextureByGLEnum()");
			return false;
		}


		glTexImage2D(target, 0, GL_RGB, lWidthPixels, lHeightPixels, 0, GL_RGB,
			GL_UNSIGNED_BYTE, buffer);  // (Modify This If You Want Mipmaps)

		VG_CHECK_OPENGL_ERROR();

		gluBuild2DMipmaps(target, GL_RGB , lWidthPixels , 
			lHeightPixels , GL_RGB , GL_UNSIGNED_BYTE, buffer );

		VG_CHECK_OPENGL_ERROR();

		delete buffer;

		return true;
	}
	//----------------------------------------------------------------


}// end of namespace vgCore
