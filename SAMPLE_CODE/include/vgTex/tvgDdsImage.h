

#ifndef __TVGDDSIMAGE_H__
#define __TVGDDSIMAGE_H__

#include <vgCore/vgPrerequisites.h>
#include <vgTex/vgDdsDeclaration.h>
#include <vgCore/vgSharedPtr.h>
#include <vgTex/tvgImage.h>
#include <vgTex/tvgStreamFactory.h>
#include <vgCore/vgException.h>

namespace vgCore {


	/**
		@date 	2007/04/28  16:38	
		@author  Leven
			
		@brief 	Dds图像载入类.一般用与dds的载入.
			DXT1,DXT3,DXT5格式存储的都为RGBA压缩数据.A8R8G8B8为未压缩数据.

		@remarks 

			DXTC减少了纹理内存消耗的50%甚至更多，有3种DXTC的格式可供使用，分别是DXT1，DXT3和DXT5。

		　　DXT1 压缩比例：1:8 
				压缩比最高，它只有1Bit  1555 Alpha，Alpha通道信息几乎完全丧失。
				一般将不带Alpha通道的图片压缩成这种格式。如WW用的卫星图片。

		  　DXT3 压缩比例：1:4
				使用了4Bit Alpha，可以有16个Alpha值，可很好地用于alpha通道锐利、对比强烈的半透和
				镂空材质。

			DXT5 压缩比例：1:4 
				使用了线形插值的4Bit Alpha，特别适合Alpha通道柔和的材质，比如高光掩码材质。
			
			许多3D软件包括大部分游戏都用dds格式，又称“贴图”，许多fans通过修改dds文件可以生成特殊显示效果。

			nVidia提供了PhotoShop使用dds的插件，通过该插件也可以生成dds文件。


		@see    
	*/
	class  VGDEP_EXPORT DdsImage : public Image
	{
	public:

		/**
			构造函数,其中包含参数的初始化.
		*/
		DdsImage()
		{
			this->setDdsParamsDefault();
		}
		/**
			析构函数.在这里释放数据.
		*/
		~DdsImage()
		{
			this->release();
		}

	public:


		//////////////////////////////////////////////////////////////////////////

		/// @copydoc Image::loadFromStream
		virtual bool	loadFromStream( const StreamReaderPtr& pstream , 
			const String& stream_filename ,
			const ImageFormat& imgformat = IMAGE_FORMAT_UNKNOWN );

		virtual bool loadFromHeaderInfo( const StreamReaderPtr& pstream ,
			const String& filename , 
			const ImageFormat& imgformat = IMAGE_FORMAT_UNKNOWN );

		/// @copydoc Image::saveToFile
		virtual bool	saveToStream( const StreamWriterPtr& pstream ,
			const ImageFormat& imgformat = IMAGE_FORMAT_UNKNOWN ,
			const DdsFormat& ddsformat = DDS_FORMAT_DEFAULT )
		{
			if ( pstream.isNull() )
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

			// 不允许用户使用其他输入。
			assert( ddsformat == DDS_FORMAT_DEFAULT );
			assert( imgformat == IMAGE_FORMAT_UNKNOWN );
			assert( mpPixelData != NULL );

			pstream->write( mDdsFileCode , 4 );
			pstream->write( (const char*)( &mDdsHeader ) , sizeof( mDdsHeader ) );
			pstream->write( (const char*)mpPixelData , mPixelDataSize );

			return true;
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

			return this->loadFromStream( pfileinfo->streamReaderPtr , 
				pfileinfo->basename, imgformat );
		}


		// 注意！将会更改指向的WriterInfoPtr
		virtual bool    saveToWriter( WriterInfoPtr& pwriter )
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

			if ( pwriter->aimFilename.empty() == false )
			{
				if( ImageUtility::findImageFileExtension( pwriter->aimFilename )
					!= "dds" )
				{
					VG_EXCEPT(Exception::ERR_NOT_IMPLEMENTED,
						"Convert from the original DDS Image to " + pwriter->aimFilename + " is not supported.",
						"DdsImage::saveToWriter");

					return false;
				}
			}

			const String& originfile = this->mFilePath;

			pwriter->streamWriterPtr->seek( pwriter->absoluteBeginPos );

			if ( this->saveToStream(pwriter->streamWriterPtr) == false )
			{
				return false;
			}

			pwriter->absoluteEndPos = pwriter->streamWriterPtr->tell();

			assert( (pwriter->absoluteEndPos - pwriter->absoluteBeginPos) >= 0 );

			pwriter->fileLength = 
				 pwriter->absoluteEndPos - pwriter->absoluteBeginPos;

			pwriter->originalFilename = originfile;
			return true;

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
			const DdsFormat& ddsformat = DDS_FORMAT_DEFAULT )
		{
			return this->saveToStream( StreamFactory::createWriterFromFile( filename ) );
		}

		/// @copydoc Image::createUnbindedTexPtr
		virtual TexturePtr createUnbindedTexPtr(
			const TextureBuildOptionPtr& option = TextureBuildOptionPtr::DEFAULT_OPTION );

		/// @copydoc Image::release
		virtual void release()
		{
			if ( mpPixelData != NULL )
			{
				delete mpPixelData;
				mpPixelData = NULL;
			}
			this->setDdsParamsDefault();
		}

	private:

		/**
			设置Dds图像文件的初始化数据.
		*/
		void setDdsParamsDefault();

		/// @copydoc Image::createTextureID
		virtual uint createTextureID( 
			const TextureBuildOptionPtr& option = TextureBuildOptionPtr::DEFAULT_OPTION );


	private:

		//////////////////////////////////////////////////////////////////////////
		//bool loadFromStreamReader( const StreamReaderPtr& pStream ,
		//	const String& ddsfilename );


		//////////////////////////////////////////////////////////////////////////
	public:

		/// 生成的opengl的像素格式.
		GLenum   mOpenGLFormat;

		/// mipmap的个数.
		Integer  mNumMipMaps;

		/// 存储的DDS的数据.
		uchar	 *mpPixelData;

		long	 mPixelDataSize;

		char  mDdsFileCode[4];
		DDSURFACEDESC2 mDdsHeader;

		DdsFormat mDdsFormat;
	};
	
	
	
}// end of namespace vgCore

#endif // end of __TVGDDSIMAGE_H__