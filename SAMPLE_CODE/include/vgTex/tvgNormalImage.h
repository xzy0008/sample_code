

#ifndef __TVGNORMALIMAGE_H__
#define __TVGNORMALIMAGE_H__

#include <vgCore/vgPrerequisites.h>
#include <vgCore/vgSharedPtr.h>
#include <vgTex/tvgTexture.h>
#include <vgTex/tvgImage.h>
#include <vgTex/vgDdsDeclaration.h>
#include <vgTex/tvgArchiveManager.h>

#include <vgTex/tvgArchive.h>

#include <acimg.h>
#include <vgCore/vgException.h>



namespace vgCore {


	class NormalImage;

	/**
		@date 	2007/04/28  20:46	
		@author  Leven
			
		@brief 	使用智能指针将CxImage包装,防止资源泄露.
			
		@see    SharedPtr
	*/
	typedef SharedPtr<CxImage>  CximagePtr;
	
	/**
		@date 	2007/04/28  20:46	
		@author  Leven
			
		@brief 	使用智能指针将NormalImage包装,防止资源泄露.
			
		@see    SharedPtr
	*/
	typedef SharedPtr<NormalImage>  NormalImagePtr;

	/**
		@date 	2007/04/28  20:46	
		@author  Leven
			
		@brief 	CxImage的包装类.将除了dds文件以外的所有图像文件的读取做一个封装.
			支持的格式有下列几种:

			CXIMAGE_FORMAT_BMP
			CXIMAGE_FORMAT_UNKNOWN
			CXIMAGE_FORMAT_JPG
			CXIMAGE_FORMAT_GIF
			CXIMAGE_FORMAT_PNG
			CXIMAGE_FORMAT_ICO
			CXIMAGE_FORMAT_TIF
			CXIMAGE_FORMAT_TGA
			CXIMAGE_FORMAT_PCX
			CXIMAGE_FORMAT_WBMP
			CXIMAGE_FORMAT_WMF
			CXIMAGE_FORMAT_JP2
			CXIMAGE_FORMAT_JPC
			CXIMAGE_FORMAT_PGX
			CXIMAGE_FORMAT_RAS
			CXIMAGE_FORMAT_PNM
			
			其中支持dds压缩格式的存储,关于压缩的详细信息,参见DdsImage

		@see    Cximage DdsImage
	*/
	class NormalImage : public Image
	{
	public:

		/// 补充水所写begin
		bool buildTextureByGLEnum( GLenum target );

		/// 补充水所写end



		/**
			构造函数.
		*/
		NormalImage()
		{
			this->setParametersDefault();
		}

		/**
			析构函数.
		*/
		virtual ~NormalImage()
		{
			this->release();

			mCximagePtr.setNull();
		}

		//////////////////////////////////////////////////////////////////////////


		virtual bool loadFromHeaderInfo( const StreamReaderPtr& pstream ,
			const String& filename , 
			const ImageFormat& imgformat = IMAGE_FORMAT_UNKNOWN );


		/// @copydoc Image::loadFromStream
		virtual bool	loadFromStream( const StreamReaderPtr& pstream , 
			const String& stream_filename ,
			const ImageFormat& imgformat = IMAGE_FORMAT_UNKNOWN )
		{
			assert( !isValid() );	/// 先这样写,检查错误.

			ImageFormat resFormat = imgformat;

			if ( resFormat == IMAGE_FORMAT_DDS )
			{
				return false;
			}
			if ( resFormat == IMAGE_FORMAT_UNKNOWN )
			{
				resFormat = ImageUtility::findImageFormat( stream_filename );
			}

			if ( resFormat == IMAGE_FORMAT_UNKNOWN )
			{
				return false;
			}

			if ( pstream.isNull() )
			{
				return false;
			}

			//if ( pstream->isValid() == false )
			//{
			//	return false;
			//}

			/*
			size_t buf_size = pstream->size();

			// 申请缓冲区
			byte* buf = new byte[buf_size];

			pstream->read( buf , buf_size );

			bool result = this->mCximagePtr->Decode( 
				static_cast<BYTE*>( buf ) , buf_size , imgformat );

			if ( result )
			{
				this->updateSelfInfoFromCximage();
			}

			// 释放缓冲区
			delete[] buf;
			buf = NULL;
			*/

			//StreamReaderPtr preader( new FileStreamReader( stream_filename ) );

			CxStreamReader cxfile( pstream );

			bool result = this->mCximagePtr->Decode( &cxfile , resFormat );

			if ( result )
			{
				this->updateSelfInfoFromCximage();
				this->mFilePath = stream_filename;
				this->mInitialised = true;
			}

			return result;
		}


		virtual bool	saveToStream( const StreamWriterPtr& pstream ,
			const ImageFormat& imgformat = IMAGE_FORMAT_UNKNOWN ,
			const DdsFormat& ddsformat = DDS_FORMAT_DEFAULT )
		{
			assert( isValid() );

			if ( pstream.isNull() )
			{
				return false;
			}

			if ( imgformat == IMAGE_FORMAT_UNKNOWN )
			{
				//iformat = ImageUtility::findImageFormat( this->mFilePath );
				return false;
			}

			if ( imgformat == IMAGE_FORMAT_DDS )
			{
				return this->saveToDdsFromCximage( pstream , ddsformat );
			}

			CxStreamWriter cxfile( pstream );

			const bool result = mCximagePtr->Encode( &cxfile , imgformat );

			return result;
		}



		virtual bool	loadFromFileInfo( const FileInfoPtr& pfileinfo , 
			const ImageFormat& imgformat = IMAGE_FORMAT_UNKNOWN ) 
		{
			// check the file pointer
			if ( pfileinfo.isNull() )
			{
				return false;
			}

			// check the stream
			if ( pfileinfo->streamReaderPtr.isNull() )
			{
				return false;
			}

			return loadFromStream( pfileinfo->streamReaderPtr ,
				pfileinfo->basename , imgformat );

			/*

			uchar* buffer = new uchar[ buffersize ];
			pfileinfo->streamReaderPtr->read( buffer , buffersize );

			// copy from loadFromFile() begin

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

				if( this->mCximagePtr->Decode( buffer , buffersize , t ) )
				{
					this->mFilePath = filename;
					this->updateSelfInfoFromCximage();
					return true;
				}
				return false;
			}
			else
			{
				if( mCximagePtr->Decode( buffer , buffersize , imgformat ) )
				{
					this->mFilePath = filename;
					this->updateSelfInfoFromCximage();
					return true;
				}
				return false;
			}

			// copy from loadFromFile() end

			// 注意释放
			delete[] buffer;
			buffer = NULL;

			return true;
			*/
		}


		// 注意！将会更改指向的WriterInfoPtr
		virtual bool    saveToWriter( WriterInfoPtr& pwriter )
		{
			assert( isValid() );
			// 当未定义文件名的时候
			if ( pwriter->aimFilename.empty() )
			{
				return this->copyOriginalDataToWriter( pwriter );
			}

			const ImageFormat original_format = 
				ImageUtility::findImageFormat( this->mFilePath );

			const ImageFormat aim_format = 
				ImageUtility::findImageFormat( pwriter->aimFilename );

			if ( original_format == aim_format )
			{
				return this->copyOriginalDataToWriter( pwriter );
			}

			pwriter->streamWriterPtr->seek( pwriter->absoluteBeginPos );

			this->saveToStream( pwriter->streamWriterPtr , aim_format , pwriter->ddsFormat );

			pwriter->absoluteEndPos = pwriter->streamWriterPtr->tell();

			assert( pwriter->absoluteEndPos >= pwriter->absoluteBeginPos);

			pwriter->fileLength = 
				pwriter->absoluteEndPos - pwriter->absoluteBeginPos;

			pwriter->originalFilename = this->mFilePath;

			return  true;
		}
		//////////////////////////////////////////////////////////////////////////


		/// @copydoc Image::loadFromFile
		virtual bool	loadFromArchiveFile( const String& filename , 
			const ImageFormat& imgformat = IMAGE_FORMAT_UNKNOWN );

		/// @copydoc Image::loadFromHeaderInfo
		virtual bool loadFromHeaderInfo( const String& filename ,
			const ImageFormat& imgformat = IMAGE_FORMAT_UNKNOWN );

		/// @copydoc Image::saveToFile
		virtual bool	saveToFile( const String& filename ,
			const ImageFormat& imgformat = IMAGE_FORMAT_UNKNOWN ,
			const DdsFormat& ddsformat = DDS_FORMAT_DEFAULT );

		/// @copydoc Image::createUnbindedTexPtr
		virtual TexturePtr createUnbindedTexPtr(
			const TextureBuildOptionPtr& option = TextureBuildOptionPtr::DEFAULT_OPTION );

		/// @copydoc Image::release
		virtual void release()
		{
			this->setParametersDefault();
		}

	protected:

		/// @copydoc Image::createTextureID
		virtual uint createTextureID( 
			const TextureBuildOptionPtr& option = TextureBuildOptionPtr::DEFAULT_OPTION );

	public:

		/// 下面是非继承函数.
		/// not virtual functions

		/**
			载入alpha通道文件.若文件为非单通道,则自动转为单色(即单通道)
				
			@note	此时正常的状态是已经载入了文件.如果文件存在alpha通道,此时会覆盖.
				
			@param	alphafile 载入alpha的文件名
				
			@returns	bool 是否成功载入了.
		*/
		bool  loadAlphaFile( const String& alphafile );

		/**
			切割图像.
				
			@note	一般执行的图像的缩小操作.当Rect的大小超出图像的大小时并不能保证正确.
				另外注意图像的坐标轴问题.
				
			@param	rect 切割图像的长方形表示.即在原图中所占的位置.

			@param	pDstImg 将图像存入的目的地.注意为空时,会将数据存入本身.

			@param	axisLeftTop 坐标轴是否在左上角.
				
			@returns	bool 是否成功的做出了切割.
		*/
		bool  crop( const ImageRect& rect , NormalImagePtr pDstImg , 
			const bool& axisLeftTop = true );

		/**
			在图像上绘制文字信息.
				
			@note	注意,此时x偏移和y偏移都是对于坐标轴在左上角而言.
				
			@param	xoffset x偏移.
			@param	yoffset y偏移.
			@param	text 要写的文字.
			@param	color 文字的颜色.
			@param	font 文字的字体名称.
			@param	fontsize 文字的大小.
			@param	setAlpha 是否将其设置为透明.
				
			@returns	bool 是否成功的写入了文字.
		*/
		bool drawString( const Integer& xoffset ,
			const Integer& yoffset , const String& text ,
			const vgMath::ColorValue& color , const string& font = "" , 
			const Integer& fontsize = 30 , const bool& setAlpha = false );

		/**
			将imgsrc2的图像内容叠在本图像之上.
				
			@note	本方法也有坐标轴之分.另外注意,本函数暂不支持超过图像大小的Rect.
				
			@param	imgsrc2 重叠在上层的图像.
			@param	rect 相对于底层的正方形区块.
			@param	axisLeftTop 坐标是否是左上角.
				
			@returns	void 
		*/
		void overlap( NormalImage &imgsrc2, const ImageRect& rect ,
			const bool& axisLeftTop = true );

		/**
			从给定的图像大小创建空白的图像.
				
			@note	dBpp指的是bit per pixel, can be 1, 4, 8, 24 
				
			@param	dwWidth 图像长
			@param	dwHeight 图像高
			@param	dBpp can be 1, 4, 8, 24 
				
			@returns	bool 是否成功创建.
		*/
		bool createFromSize( const Integer& dwWidth, 
			const Integer& dwHeight , const Integer& dBpp = 24 );

		/**
			清除颜色.即将图像的全部像素值置为参数的颜色.
				
			@param	bval 目的颜色值.
		*/
		void clearColor( const uchar& bval = 0 )
		{
			assert( isValid() );
			mCximagePtr->Clear( bval );
		}

		/**
			得到alpha文件路径信息.
		*/
		const String getAlphaFilePath() const
		{
			return this->mAlphaFilePath;
		}

		CximagePtr getCximagePtr()
		{
			return this->mCximagePtr;
		}
		/**
			重新设置图像的大小.
		*/
		bool resize( const ImageSize& imgSize );

		/**
			返回重新设置图像大小后的拷贝.
		*/
		const NormalImagePtr  resizeCopy( const ImageSize& imgSize ) const;

		/**
			通过读取CxImage信息来更新自身的值.
		*/
		void updateSelfInfoFromCximage();

	private:

		/**
			set all the parameters default.
		*/
		void setParametersDefault();



		/**
			根据Cximage的信息存入dds数据.
				
			@note	cximage要保证已载入.
				
			@param	ddsfile dds文件的文件名.
			@param	dformat dds文件格式.具体参见DdsFormat
				
			@returns	bool 是否正确存储.
		*/
		bool	saveToDdsFromCximage( const String& ddsfile ,
			const DdsFormat& dformat = DDS_FORMAT_DEFAULT );


		bool	saveToDdsFromCximage( const StreamWriterPtr& pstream ,
			const DdsFormat& dformat = DDS_FORMAT_DEFAULT );





		/**
			使用A8R8G8B8的方式存储dds.
				
			@note	这个时候dds文件没有经过压缩存储,并不是推荐的方式.此函数会被
				saveToFile自动调用.
				
			@param	ddsfile dds的文件名.
				
			@returns	bool 是否正确存取.
		*/
		bool  saveDdsUsingA8R8G8B8(const String& ddsfile);

		bool  saveDdsUsingA8R8G8B8( const StreamWriterPtr& pstream );


	private:

		//////////////////////////////////////////////////////////////////////////


		bool copyOriginalDataToWriter( WriterInfoPtr& pwriter )
		{
			if ( pwriter.isNull() )
			{
				return false;
			}
			if ( pwriter->streamWriterPtr.isNull() )
			{
				return false;
			}

			if ( isValid() == false )
			{
				return false;
			}

			if ( this->mFilePath.empty() )
			{
				return false;
			}

			const String& originfile = this->mFilePath;

			FileInfoPtr pfileinfo = ArchiveManager::getSingleton().getFileInfo( originfile );

			if ( pfileinfo.isNull() )
			{
				VG_EXCEPT(Exception::ERR_FILE_NOT_FOUND,
					"The original Image file :" + originfile + " has been lost.",
					"DdsImage::saveToWriter");

				return false;
			}

			StreamReaderPtr& preader = pfileinfo->streamReaderPtr;

			if ( preader.isNull() )
			{
				VG_EXCEPT(Exception::ERR_FILE_NOT_FOUND,
					"The original Image file :" + originfile + " has been lost.",
					"DdsImage::saveToWriter");

				return false;
			}

			size_t filesize = pfileinfo->uncompressedSize;

			char *buffer = new char[ filesize ];

			assert( buffer != NULL );

			preader->read( buffer , filesize );
			// end to read all data

			pwriter->streamWriterPtr->seek( pwriter->absoluteBeginPos );
			pwriter->streamWriterPtr->write( buffer , filesize );
			pwriter->absoluteEndPos = pwriter->streamWriterPtr->tell();

			pwriter->fileLength = filesize;
			pwriter->originalFilename = originfile;

			delete[] buffer;
			buffer = NULL;

			return true;
		}

		//////////////////////////////////////////////////////////////////////////

	private:
	public:

		/// alpha文件的文件路径.
		String		mAlphaFilePath;

		/// 指向Cximage的指针.
		CximagePtr	mCximagePtr;
	};
	
	
	
	
}// end of namespace vgCore

#endif // end of __TVGNORMALIMAGE_H__