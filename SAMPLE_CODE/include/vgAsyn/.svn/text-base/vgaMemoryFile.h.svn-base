



#ifndef __VGAMEMORYFILE_H__
#define __VGAMEMORYFILE_H__
#include <vgAsyn/vgaDefinition.h>
#include <vgKernel/vgkForward.h>

	
namespace vgAsyn {

	class FileInfo;
	class FileHandle;

	/**
		@date 	2009/04/29  10:25	
		@author  leven
	
		@brief 	
	
		@see    
	*/
	class  VGA_EXPORT MemoryFile
	{
	public:
		MemoryFile()
		{
			_filehandle = NULL;
			_wholeFileMem = NULL;
		}
		~MemoryFile()
		{
			if ( _wholeFileMem != NULL )
			{
				delete[] _wholeFileMem;
				_wholeFileMem = NULL;
			}
		}
	
	public:

		// 从内存中读取
		// 注意，有可能返回NULL
		char* readMemory( FileInfo* info );

		bool importFromFileHandle( FileHandle* handle );

		bool isValid() const
		{
			return _wholeFileMem != NULL && _filehandle != NULL;
		}

		FileHandle* getFilehandle() { return _filehandle; }

	private:
	
		FileHandle* _filehandle;

		long _wholeFileSize;

		char* _wholeFileMem;
	};
	
	
}// end of namespace vgAsyn
	


#endif // end of __VGAMEMORYFILE_H__