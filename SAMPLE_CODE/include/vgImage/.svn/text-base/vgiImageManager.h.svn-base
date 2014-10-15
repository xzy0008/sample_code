



#ifndef __VGIIMAGEMANAGER_H__
#define __VGIIMAGEMANAGER_H__
#include <vgImage/vgiDefinition.h>
#include <vgKernel/vgkForward.h>
#include <vgKernel/vgkSingleton.h>
#include <vgKernel/vgkTrace.h>
#include <vgImage/vgiFileHandleVgi.h>
#include <vgAsyn/vgaFileInfo.h>


	
namespace vgImage {

	/**
		@date 	2008/06/23  21:33	
		@author  leven
	
		@brief 	注意,目前只是对vgi的封装.
		vgm的filehandle管理是在meshManager中.

		以后可能需要统一管理.
	
		@see    
	*/
	class  VGI_EXPORT ImageManager : public vgKernel::Singleton<ImageManager>
	{
	public:
		typedef std::map<String, FileHandleVgi*> FileHandleVgiMap;
	private:
		typedef std::pair<FileHandleVgiMap::iterator, bool> FileHandleMapInsertResult;

		friend class vgKernel::Singleton<ImageManager>;
	private:
		ImageManager() 
			: Singleton<ImageManager>( VGK_SINGLETON_LEFE_IMAGEMGR ) 
		{
			VGK_TRACE(_T("ImageManager created."));
		}
		~ImageManager()
		{
			VGK_TRACE(_T("ImageManager destroyed."));
		}

	protected:

		virtual bool initialise()
		{
			return true;
		}

		virtual bool shutdown();

	public:

		void reset(){ clearAllFileHandles(); }

		void clearAllFileHandles();

		/**
			另外要注意,在vgAsyn:TextureManager中没有添加相应的纹理,需要手动添加!
		*/
		FileHandleVgi* addImageAndAssociateWithIoServer( const String& filepathname );

		// 要确认handle已经被打开了!!
		FileHandleVgi* addImageAndAssociateWithIoServer( FileHandleVgi* handle );


		bool exist( const String& metafilename );
		
		ImageMiniature* getImageMiniature( const String& metafilename );

		// utility
		void extractVgiToMultipleFiles();
		void extractVgiToMultipleFiles(const String& vgimg_path, 
			const String& save_multiple_files_path );


		//bool deleteFileHandleVgi( FileHandleVgi* filehandle )
		//{

		//}

		FileHandleVgi* getFileHandleVgi( const String& vgipath );

		FileHandleVgiMap* getFileHandleVgiMap()
		{
			return &_filehandles;
		}

	private:

		bool addFileHandle( FileHandleVgi* filehandle );
	
		FileHandleVgiMap _filehandles;
	};

	
	
}// end of namespace vgImage
	


#endif // end of __VGIIMAGEMANAGER_H__