

#ifndef __VGAIMAGE_H__
#define __VGAIMAGE_H__

#include <vgImage/vgiDefinition.h>
#include <vgKernel/vgkForward.h>
#include <vgImage/vgiImageUtility.h>


namespace vgImage {


	/**
		@date 	2008/06/18  19:25	
		@author  leven
	
		@brief 	

		在vgImage中texture的载入载出使用的是ImageMiniature
		本类是utility类,用来手动载入dds文件


		//------------------------------------------
		// 开始测试Image
		//------------------------------------------
		FileInfoPtr pinfo = ArchiveManager::getSingleton().getFileInfo( "02.dds" );
		assert( pinfo.isNull() == false );
		int filesize = pinfo->uncompressedSize;
		char *filebuf = new char[filesize];
		pinfo->streamReaderPtr->read( filebuf , filesize );

		vgAsyn::Image img( filebuf , filesize );

		GLuint id = img.createTextureID();
	
		@see    
	*/
	class  VGI_EXPORT Image
	{
	public:

		//------------------------------------------
		// 注意,一旦将指针传递进来
		// Image类将负责filebuf的释放
		//------------------------------------------
		Image( char* filebuf , long filesize );

		~Image();
	
		bool isValid() const
		{
			return _loadOK;
		}

		GLuint createTextureID();


		void* getPixelDataPointer()
		{
			assert( mpPixelData != NULL );
			return mpPixelData;
		}

		long getPixelDataSize()
		{
			return mPixelDataSize;
		}

		long getClearestLayerDataSize();

	private:

		void setDefault();
		bool loadFromMemory();
		GLuint createTextureIDImpletation();

	public:

		char* _fileBuffer;
		long _fileSize;

		bool _loadOK;


		//------------------------------------------
		// 注意,以下是临时的变量
		// 只是存放在这里
		//------------------------------------------
		char	 *mpPixelData;
		long	 mPixelDataSize;
		long		mWidth;
		long 		mHeight;

		GLenum   mOpenGLFormat;
		long  mNumMipMaps;
	};
	
	
}// end of namespace vgAsyn



#endif // end of __VGAIMAGE_H__
