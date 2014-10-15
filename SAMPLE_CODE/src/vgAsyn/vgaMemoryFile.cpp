


#include <vgStableHeaders.h>
#include <vgAsyn/vgaMemoryFile.h>
#include <vgAsyn/vgaFileHandle.h>
#include <vgAsyn/vgaFileInfo.h>


namespace vgAsyn {
	
	
	
	

	bool MemoryFile::importFromFileHandle( FileHandle* handle )
	{
		assert( handle != NULL );
		char* buf = NULL;
		long buf_size = 0;
		bool readok = handle->readWholeFileToMemory( buf , buf_size );

		if ( readok == false )
		{
			return false;
		}

		_filehandle = handle;
		_wholeFileMem = buf;
		_wholeFileSize = buf_size;

		return true;
	}
	//----------------------------------------------------------------
	char* MemoryFile::readMemory( FileInfo* info )
	{
		if ( info->_fileHandle != _filehandle )
		{
			return NULL;
		}

		if ( (info->_fileOffset + info->_fileSize) > _wholeFileSize )
		{
			assert(0);
			return NULL;
		}

		char* ret = new char[ info->_fileSize ];
		memcpy( ret, _wholeFileMem + info->_fileOffset, info->_fileSize );

		return ret;
	}
	//----------------------------------------------------------------


}// end of namespace vgAsyn
