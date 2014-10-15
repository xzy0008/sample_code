
#ifndef __TVGTEXTUREBUILDER_H__
#define __TVGTEXTUREBUILDER_H__

#include <vgCore/vgPrerequisites.h>
#include <vgTex/tvgImageUtil.h>
#include <vgTex/tvgImageFactory.h>
#include <vgTex/tvgTexture.h>


namespace vgCore {


	/**
		@date 	2007/04/29  9:45	
		@author  Leven
			
		@brief 	创建Texture的类.纹理的创建和纹理的管理理应分开,这是创建本类的原因.
			

		@note 必要时可以添加为Singleton,用于统计之用,比如统计create的次数,统计内存情况等等.
			另外,本类提供的接口暂时只在TextureManager中使用.
			
		@see    TextureManager
	*/
	class TextureBuilder
	{
	private:

		/// 目前此类的接口只在TextureManager中使用.
		friend class TextureManager;

		TextureBuilder()
		{

		}
		~TextureBuilder()
		{

		}

	public:

		/**
			取得空纹理指针.此时本操作相当于将自身看成Factory模式.
		*/
		static inline  TexturePtr getEmptyTexturePtr()
		{
			return TexturePtr::EmptyTexturePtr;
		}

	private:

		/**
			创建Unbinded状态的Texture.
				
			@param	filename 纹理的文件名.
			@param	format 图像文件格式.
			@param	option 创建纹理的选项.
				
			@returns	TexturePtr 纹理指针.创建纹理失败时,会返回指向空纹理的指针,注意不是
				空指针.
		*/
		static  TexturePtr createUnbindedTexturePtr( 
			const String& filename , const ImageFormat& format ,
			const TextureBuildOptionPtr& option = TextureBuildOptionPtr::DEFAULT_OPTION );

		/**
			创建Unbinded状态的Texture.
				
			@note	为了操作上的方便.省去纹理的格式.
				
			@param	filename 纹理的文件名.
			@param	option 创建纹理的选项.
				
			@returns	TexturePtr 纹理指针.创建纹理失败时,会返回指向空纹理的指针,注意不是
				空指针.
		*/
		static  TexturePtr createUnbindedTexturePtr( const String& filename , 
			const TextureBuildOptionPtr& option  = TextureBuildOptionPtr::DEFAULT_OPTION );

		/**
			创建Unbinded状态的Texture.
				
			@note	use for huge cutted images.
				
			@param	filename 纹理的文件名.
			@param	option 纹理选项.默认为DEFAULT_HUGE_MAP_DXT_OPTION
				
			@returns	vgCore::TexturePtr 
		*/
		static  TexturePtr createFromHugeCuttedDdsImage( const String& filename ,
			const TextureBuildOptionPtr& option = TextureBuildOptionPtr::DEFAULT_HUGE_MAP_DXT_OPTION );

		/**
			设置Texture的状态为loaded.
				
			@note	此时会通过TexturePtr指向的文件名,提供的参数等来载入纹理文件.
				
			@param	ptex 纹理指针.
			@param	format 纹理的格式.
			@param	option 纹理的选项.
				
			@returns	bool 是否成功载入了数据.文件查找不到或者在读入的过程中出现了错误
				就会返回false.
		*/
		static bool setTexturePtrLoaded( TexturePtr& ptex ,
			const bool& useSelfOption = true,
			const ImageFormat& format = IMAGE_FORMAT_UNKNOWN ,
			const TextureBuildOptionPtr& option = TextureBuildOptionPtr::DEFAULT_OPTION );
		

		/**
			创建Unloaded状态的texture.
				
			@note	此时需要提供唯一的id名称.按照Texture的状态定义,unloaded状态必需一个唯一id.
				
			@param	uniname 唯一的id.
			@param	filename 文件名.
			@param	format 文件的格式.
			@param	option 纹理的选项.
				
			@returns	TexturePtr 纹理指针.创建纹理失败时,会返回指向空纹理的指针,注意不是
				空指针.
		*/
		static  TexturePtr createUnloadedTexturePtr( const String& uniname , 
			const String& filename , const ImageFormat& format = IMAGE_FORMAT_UNKNOWN,
			const TextureBuildOptionPtr& option = TextureBuildOptionPtr::DEFAULT_OPTION );


		/**
			使用已经载入的imgPtr将ptex载入
				
			@param	ptex 纹理的指针.
			@param	imgPtr 图像数据的指针.
				
			@returns	bool 是否成功将texture载入.
		*/
		static  bool  setTexturePtrLoadedFromImagePtr( TexturePtr& ptex , 
			ImagePtr& imgPtr , const bool& ifSetImgNull );

	private:


		/**
			@note	used for empty texture pointer return , when error occurs.
				
			@param	file 
				
			@returns	vgCore::TexturePtr 
		*/
		static inline  TexturePtr emptyTextureReturn( const String& file = "" )
		{
			createFileNotFoundWarning( file );
			return getEmptyTexturePtr();
		}

		/**
			@note	used for emptyTextureReturn()
				
			@param	file 
				
			@returns	void 
		*/
		static inline  void createFileNotFoundWarning( const String& file )
		{
			VG_WARN(Warning::WARN_FILE_NOT_FOUND ,
				Warning::BUTTON_NONE,
				"Image file : " + file + " is not found. ",
				"TextureBuilder::createFileNotFoundWarning()");
		}

	};
	
	
	
}// end of vgCore

#endif // end of __TVGTEXTUREBUILDER_H__