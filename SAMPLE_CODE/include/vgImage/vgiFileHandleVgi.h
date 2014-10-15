


#ifndef __VGIFILEHANDLEVGI_H__
#define __VGIFILEHANDLEVGI_H__
#include <vgImage/vgiDefinition.h>
#include <vgKernel/vgkForward.h>
#include <vgAsyn/vgaFileHandle.h>
#include <vgImage/vgiImageMiniature.h>

namespace vgImage {

	/**
		@date 	2008/08/04  10:05	
		@author  leven
	
		@brief 	
	
		@see    
	*/

	class  VGI_EXPORT FileHandleVgi : public vgAsyn::FileHandle
	{
	public:
		typedef std::map<String, ImageMiniature*> ImageMiniMap;
	public:
		FileHandleVgi( String filepath )
			: FileHandle( filepath )
		{
			_nextHandle = NULL;
			_type = FILEHANDLE_TYPE_VGI;
		}

		virtual ~FileHandleVgi()
		{
			close();
		}

		virtual bool exist( const String& metafilename );

		virtual vgKernel::StringVector* listMetaFileNames();

		virtual bool open();

		virtual void close();

		virtual bool extractToMultipleFiles( const String& save_multiple_file_path );

		ImageMiniature* getImageMiniature( const String& metafilename );


		/**
			如果有下一个vtr文件, 则尝试打开
		*/
		FileHandleVgi* openNextFile();

		String getNextFilePath();


		FileHandleVgi* getNextFileHandle()
		{
			return _nextHandle;
		}


	private:

		ImageMiniMap _imgMiniMap;

		FileHandleVgi* _nextHandle;

		VgiHeader _header;
	};
	
	
}// end of namespace vgImage
	


#endif // end of __VGIFILEHANDLEVGI_H__