

#ifndef __TVGIMAGE_H__
#define __TVGIMAGE_H__

#include <vgCore/vgPrerequisites.h>
#include <vgCore/vgSharedPtr.h>
#include <vgTex/tvgImageUtil.h>
#include <vgTex/tvgTexture.h>

#include <vgTex/tvgArchive.h>
#include <vgTex/tvgStreamWriter.h>

namespace vgCore {

	/**
		@date 	2007/04/28  15:23	
		@author  Leven
			
		@brief 	图像类的基类,负责读入图像数据.

		图像格式一般分为2种:Cximage格式的还有dds格式的,因为每种格式处理的方式
		不同,所以最好的方法就是创建一个基类,然后由ImageFactory的一系列create方法
		创建ImagePtr.
			
		@see DdsImage NormalImage ImageFactory
	*/
	class  VGDEP_EXPORT Image
	{
	public:

		/// 构造函数
		Image()
		{

		}

		/// 析构函数,声明为virtual,便于继承.
		virtual ~Image()
		{

		}
	

		/**
			虚函数。通过图像的文件名和文件格式载入文件。

			@note	直接创建DdsImage,NormalImage实例并loadFromFile的方法是不推荐的,
			推荐从ImageFactory创建。

			@param	filename 传入的文件名

			@param	imgformat 传入的文件格式,当为IMAGE_FORMAT_UNKNOWN时自动通过
			文件名获取格式。IMAGE_FORMAT_UNKNOWN为默认形参。

			@returns	bool 是否成功的载入了文件。
		*/
		virtual bool	loadFromArchiveFile( const String& filename , 
			const ImageFormat& imgformat = IMAGE_FORMAT_UNKNOWN ) = 0;



		//////////////////////////////////////////////////////////////////////////

		/// @copydoc Image::loadFromStream
		virtual bool	loadFromStream( const StreamReaderPtr& pstream , 
			const String& stream_filename ,
			const ImageFormat& imgformat = IMAGE_FORMAT_UNKNOWN ) = 0 ;


		virtual bool loadFromHeaderInfo( const StreamReaderPtr& pstream ,
			const String& filename , 
			const ImageFormat& imgformat = IMAGE_FORMAT_UNKNOWN ) = 0 ;



		virtual bool	saveToStream( const StreamWriterPtr& pstream ,
			const ImageFormat& imgformat = IMAGE_FORMAT_UNKNOWN ,
			const DdsFormat& ddsformat = DDS_FORMAT_DEFAULT ) = 0;

		virtual bool	loadFromFileInfo( const FileInfoPtr& pfileinfo , 
			const ImageFormat& imgformat = IMAGE_FORMAT_UNKNOWN ) = 0 ;

		// 注意！将会更改指向的WriterInfoPtr
		virtual bool    saveToWriter( WriterInfoPtr& pwriter ) = 0;

		//////////////////////////////////////////////////////////////////////////


		/**
			虚函数。通过图像的文件名和文件格式载入文件头信息。

			@note	这里可以用于图像文件的提前检查。查看一个文件是否存在，以及是否
			格式正确。注意，这里并不直接载入数据信息。

			@param	filename 传入的文件名

			@param	imgformat 传入的文件格式,当为IMAGE_FORMAT_UNKNOWN时自动通过
			文件名获取格式。IMAGE_FORMAT_UNKNOWN为默认形参。

			@returns	bool 是否成功的载入了文件头信息。
		*/
		virtual bool loadFromHeaderInfo( const String& filename ,
			const ImageFormat& imgformat = IMAGE_FORMAT_UNKNOWN ) = 0 ;


		/**
			虚函数。根据文件名存储到硬盘。
			@param	filename 文件名.
			@param	imgformat 文件的格式，参见ImageFormat
			@param	ddsformat 特别为dds格式所设。当为非dds格式时，此参数无效。
			@returns	bool 是否成功的存储。
		*/
		virtual bool	saveToFile( const String& filename ,
			const ImageFormat& imgformat = IMAGE_FORMAT_UNKNOWN ,
			const DdsFormat& ddsformat = DDS_FORMAT_DEFAULT ) = 0 ;


		/**
			载入数据之后,产生Unbinded状态的TexturePtr.
			@note	
			@param	option 
			@returns	vgCore::TexturePtr 
		*/
		virtual TexturePtr createUnbindedTexPtr(
			const TextureBuildOptionPtr& option = TextureBuildOptionPtr::DEFAULT_OPTION ) = 0 ;


		/**
			释放资源
			release the image data
			@note	
			@returns	void 
		*/
		virtual void release() = 0;

		/**
			是否已经初始化
		*/
		virtual bool isValid() const
		{
			return mInitialised;
		}

		/**
			得到文件的长度
		*/
		virtual Integer getWidth() const
		{
			return this->mWidth;
		}
	
		/**
			得到文件的宽度.
		*/
		virtual Integer getHeight() const
		{
			return this->mHeight;
		}

		/**
			得到图像文件的大小.
			@returns	ImageSize  图像的大小.
		*/
		virtual ImageSize getImageSize() const
		{
			return ImageSize( mWidth , mHeight );
		}

		/**
			得到Texture的像素格式信息
		*/
		const TexturePixelFormat		getTexPixelFormat() const 
		{ 
			return this->mTexPixelFormat; 
		}

		/**
			得到Texture的flag信息
		*/
		const TextureFlag		getTextureFlag() const 
		{ 
			return this->mTextureFlag; 
		}

		/**
			得到文件路径.
		*/
		const String		getFilePath() const;

		/**
			得到此Image的具体信息.
		*/
		virtual const String getDetails() const;

	protected:

		/// 通过声明friend TextureBuilder,限制创建Texture的权力分配.
		friend class TextureBuilder;

		/**
			设置默认参数的初始值.
			set all the parameters default.
		*/
		//virtual void setParametersDefault() = 0 ;

		/**
			创建Texture的id值
			for TextureBuilder use.
			@note	注意,此方法只能由特定的类使用.
			@param	option 纹理的选项.
			@returns	uint 产生的opengl的纹理id
		*/
		virtual uint createTextureID( 
			const TextureBuildOptionPtr& option = TextureBuildOptionPtr::DEFAULT_OPTION ) = 0 ;

	
	protected:
	public:

		/// 默认的图像大小,为常量.
		static const Integer DEFAULT_IMAGE_WIDTH;
		static const Integer DEFAULT_IMAGE_HEIGHT;

		/// 图像的文件路径.
		String		mFilePath;

		/// 图像的长宽.
		Integer		mWidth;
		Integer		mHeight;

		/// 是否已经初始化的标志.
		bool		mInitialised;

		/// texture的标志位.
		TextureFlag mTextureFlag;
		TexturePixelFormat mTexPixelFormat;
	
	};


	/**
		使用智能指针重定义图像类.
	*/
	typedef SharedPtr<Image>  ImagePtr;
	
	
}

#endif // end of __TVGIMAGE_H__