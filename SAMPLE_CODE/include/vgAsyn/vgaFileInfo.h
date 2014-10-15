



#ifndef __VGAFILEINFO_H__
#define __VGAFILEINFO_H__
#include <vgAsyn/vgaDefinition.h>
#include <vgKernel/vgkForward.h>
#include <vgAsyn/vgaFileHandle.h>


namespace vgAsyn {

	class IoRequest;
	/**
		@date 	2008/06/23  15:06	
		@author  leven
	
		@brief 	
	
		@see    
	*/
	class  VGA_EXPORT FileInfo
	{
	public:
		FileInfo( String metafilename , 
			FileHandle* filehandle , 
			long offset , long size )
		{
			_metaFileName = metafilename;
			_fileHandle = filehandle;

			_fileOffset = offset;
			_fileSize = size;
		}

		~FileInfo()
		{	
		}
	
		FileInfo* clone() const;

	public:
	
		String _metaFileName;
		FileHandle* _fileHandle;

		long _fileOffset;
		long _fileSize;

	};
	
	
	
}// end of namespace vgAsyn

#endif // end of __VGAFILEINFO_H__