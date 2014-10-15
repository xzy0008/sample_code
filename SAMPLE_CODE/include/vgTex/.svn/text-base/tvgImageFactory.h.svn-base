

#ifndef __TVGIMAGEFACTORY_H__
#define __TVGIMAGEFACTORY_H__

#include <vgCore/vgPrerequisites.h>
#include <vgTex/tvgDdsImage.h>
#include <vgTex/tvgNormalImage.h>
#include <vgTex/tvgArchiveManager.h>


namespace vgCore {

	/**
		@date 	2007/04/06  13:10	
		@author  Leven
	
		@brief 	Image的工厂类.此类负责Image的产生.

		@note 构造函数都是private,不允许创建.
	
		@see    Image NormalImage DdsImage
	*/
	class ImageFactory
	{
	private:

		/**
			构造函数,不允许创建.
		*/
		ImageFactory()
		{

		}
		/**
			析构函数.
		*/
		~ImageFactory()
		{

		}

	public:


		//////////////////////////////////////////////////////////////////////////
		
		static ImagePtr createFromArchiveFile( const String& filename ,
			const ImageFormat& imgformat = IMAGE_FORMAT_UNKNOWN )
		{
			FileInfoPtr pfileinfo = ArchiveManager::getSingleton().getFileInfo( filename );

			if ( pfileinfo.isNull() )
			{
				return emptyImagePtrReturn( filename );
			}

			ImagePtr  pimg = createFromFileFormat( filename , imgformat );

			if ( pimg.isNull() )
			{
				return emptyImagePtrReturn( filename );
			}

			if( pimg->loadFromFileInfo( pfileinfo , imgformat ) )
			{
				return pimg;
			}

			return emptyImagePtrReturn( filename );
		};

		static ImagePtr createFromLoadingStream( const StreamReaderPtr& pstream ,
			const String& filename , const ImageFormat& imgformat = IMAGE_FORMAT_UNKNOWN )
		{
			ImagePtr  pimg = createFromFileFormat( filename , imgformat );

			if ( pimg.isNull() )
			{
				return emptyImagePtrReturn( filename );
			}

			if( pimg->loadFromStream( pstream , filename , imgformat ) )
			{
				return pimg;
			}

			return emptyImagePtrReturn( filename );
		}


		//////////////////////////////////////////////////////////////////////////
		/**
			通过文件格式创建需要的Image.
				
			@note	由于Cximage处理除了dds以外的图像,DdsImage处理dds图像,为了
				避免每次使用时判断图像格式,故提供此接口.
				
			@param	filename 输入的文件名.
			@param	imgformat 文件格式,默认为IMAGE_FORMAT_UNKNOWN,此时根据filename
				来自动生成format
				
			@returns	ImagePtr 
		*/
		static ImagePtr createFromFileFormat( const String& filename ,
			const ImageFormat& imgformat = IMAGE_FORMAT_UNKNOWN );

	
		/**
			通过读取头文件信息而不载入数据的方式产生Image.
				
			@note	由于Cximage处理除了dds以外的图像,DdsImage处理dds图像,为了
				避免每次使用时判断图像格式,故提供此接口.
				
			@param	filename 输入的文件名.
			@param	imgformat 文件格式,默认为IMAGE_FORMAT_UNKNOWN,此时根据filename
				来自动生成format
				
			@returns	ImagePtr 
		*/
		static ImagePtr createFromLoadingHeader( const String& filename , 
			const ImageFormat& imgformat = IMAGE_FORMAT_UNKNOWN );

		/**
			通过载入文件所有的信息来创建需要的Image.
				
			@note	这个函数执行2步:1.根据文件格式选择必要的Image
				2.将这个filename执行Image的loadFromFile将文件载入.
				
			@param	filename 输入的文件名.
			@param	imgformat 文件格式,默认为IMAGE_FORMAT_UNKNOWN,此时根据filename
				来自动生成format
				
			@returns	ImagePtr 
		*/
		static ImagePtr createFromLoadingFile( const String& filename , 
			const ImageFormat& imgformat = IMAGE_FORMAT_UNKNOWN );


		/**
			通过一个TexturePtr来创建Image.
				
			@param	ptex 传入的TexturePtr
			@param	checkLoaded 是否检查TexturePtr的状态已载入.
				
			@returns	ImagePtr 
		*/
		static  ImagePtr createFromTexturePtr( const TexturePtr& ptex ,
			const bool& checkLoaded = true );

		/**
			创建NormalImage
				
			@note	此方法用来处理除dds文件以外的图像文件.由于dds已被压缩,
				故没有处理的功能.
				
			@returns	NormalImagePtr 
		*/
		static NormalImagePtr createNormalImagePtr();
	
	private:

		/**
			私有.当文件找不到时返回空的ImagePtr指针.
		*/
		inline static ImagePtr emptyImagePtrReturn( const String& filename )
		{
			return ImagePtr();
		}
	};
	
	
	
	
}// end of namespace vgCore

#endif // end of __TVGIMAGEFACTORY_H__