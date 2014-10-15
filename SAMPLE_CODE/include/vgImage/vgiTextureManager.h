



#ifndef __VGITEXTUREMANAGER_H__
#define __VGITEXTUREMANAGER_H__

#include <vgImage/vgiDefinition.h>
#include <vgKernel/vgkForward.h>
#include <vgKernel/vgkSingleton.h>
#include <vgImage/vgiTexture.h>
#include <vgImage/vgiFileHandleVgi.h>
#include <vgImage/vgiTextureItem.h>
#include <vgKernel/vgkTrace.h>

#include <vgImage/vgiSmallTextureReferencer.h>



namespace vgImage {


	class TextureObserver;


	class  VGI_EXPORT TextureManager : public vgKernel::Singleton<TextureManager>
	{
		typedef std::map<String, TextureItem*> TextureMap;
		typedef		std::pair< TextureMap::iterator , bool>	TextureInsertResult;

		friend class vgKernel::Singleton<TextureManager>;
	private:
		TextureManager() 
			: Singleton<TextureManager>( VGK_SINGLETON_LEFE_TEXMGR ) 
		{
			VGK_TRACE(_T("TextureManager created."));
		}
		~TextureManager()
		{
			VGK_TRACE(_T("TextureManager destroyed."));
		}
	
	protected:

		virtual bool initialise()
		{
			return true;
		}

		virtual bool shutdown();
		
	public:

		void reset(){ unloadAllTextureData(); }

		/**
			关键函数,要在OpenGL配置环境结束之前执行.
		*/
		void unloadAllTextureData();

		// 注意，添加的时候都需要先变为同步模式，加载必要的纹理
		bool addTexture( FileHandleVgi* vgimg );
		

		//------------------------------------------
		// 注意,这里不负责增加引用计数
		// 另外,注意:
		// 客户端不能通过TextureObserver对其进行删除操作!
		//------------------------------------------
		TextureObserver* getTextureObserver( const String& texname ,
			const int& lod );
	
		/**
			Utility - in order to load all specific lod layers.
		*/
		bool addRefToEveryTextureBySpecificLod( const int& lod );
		bool addRefToTexturesBySpecificLod( 
			FileHandleVgi* vgihandle , const int& lod );

		SmallTextureReferencer* getSmallTextureReferencer() 
		{
			return &_smallRefer;
		}

		void readProject(const String& projpath , const String& projname);

		void saveProject();

	private:

		bool addTextureByName( const String& texname );

		bool validateTextureExtension( const String& texname );

		vgKernel::StringVectorPtr getTextureNameList();

	private:

		//------------------------------------------
		// 注意,暂定永远留在内存中的结构
		//------------------------------------------
		TextureMap _texMap;
	
	
		SmallTextureReferencer _smallRefer;
	};
	
	
	
}// end of namespace vgImage

#endif // end of __VGITEXTUREMANAGER_H__