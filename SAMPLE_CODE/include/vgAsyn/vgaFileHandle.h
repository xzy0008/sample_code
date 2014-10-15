






#ifndef __VGAFILEHANDLE_H__
#define __VGAFILEHANDLE_H__
#include <vgAsyn/vgaDefinition.h>
#include <vgKernel/vgkForward.h>
#include <vgAsyn/vgaAsynUtility.h>
#include <vgKernel/vgkStringVector.h>


namespace vgAsyn {

	class FileInfo;
	class IoRequest;
	class IoRequestStruct;

	/**
		@date 	2008/06/18  21:54	
		@author  leven
	
		@brief 	任何继承此类的函数需要客户端来管理生命周期.
	
		@see    
	*/
	class  VGA_EXPORT FileHandle
	{
	public:
		enum FileHandleType 
		{
			FILEHANDLE_TYPE_VGI,
			FILEHANDLE_TYPE_VGM,
			FILEHANDLE_TYPE_VTR
		};

		/**
			文件打开方式,默认都为FILEHANDLE_OPENACESS_READ
			注意!这一项的设置都要在Open执行之前!
		*/
		enum FileHandleOpenAccess
		{
			FILEHANDLE_OPENACESS_READ = GENERIC_READ,
			FILEHANDLE_OPENACESS_WRITE = GENERIC_WRITE
		};

	public:
		FileHandle( String filepath );
		virtual ~FileHandle();
	
	public:

		/**
			注意!要在open()之前!
		*/
		void setOpenAccess( FileHandleOpenAccess access )
		{
			_openAccess = access;
		}

		FileHandleOpenAccess getOpenAccess() const
		{
			return _openAccess;
		}

		DWORD getFileSize();

		HANDLE getHandle();

		String getFilePath()
		{
			return _filePath;
		}

		FileHandleType getType()
		{
			return _type;
		}

		bool doRead( char* buf , IoRequestStruct *prequest  );

		/**
			从文件中读取.
			注意, 暂时实现了同步的版本,异步版本暂时不做考虑.
		*/
		bool doWrite( char* buf, IoRequestStruct* prequest );

		virtual bool exist( const String& metafilename ) = 0;

		virtual vgKernel::StringVector* listMetaFileNames() = 0;

		virtual bool open();
	
		virtual void close();

		virtual bool extractToMultipleFiles( const String& save_multiple_file_path) = 0;

		inline bool isOpened() const
		{
			return _isOpened;
		}

		// 将整个的文件读入内存，用于内存文件，同步模式
		bool readWholeFileToMemory( char*& out_buf, long& out_filesize );


		// 将整个的文件读入内存，用于内存文件，同步模式
		bool copyWholeFile( const String& out_filename );



		//// 注意，客户端负责删除
		//// 这个函数主要是提供给CacheManager使用
		//virtual IoRequestVector* listIoRequests() = 0;

	protected:

		FileHandleOpenAccess _openAccess;
	
		FileHandleType _type;

		String _filePath; 

		bool _isOpened;

		HANDLE _fileHandle;
	};
	
	


	
}// end of namespace vgAsyn

#endif // end of __VGAFILEHANDLE_H__