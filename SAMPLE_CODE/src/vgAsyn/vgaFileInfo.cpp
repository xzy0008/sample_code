


#include <vgStableHeaders.h>
#include <vgAsyn/vgaFileInfo.h>


namespace vgAsyn {
	
	
	
	
	//----------------------------------------------------------------
	FileInfo* FileInfo::clone() const
	{
		return new FileInfo( _metaFileName , _fileHandle , _fileOffset , 
			_fileSize );
	}
	//----------------------------------------------------------------
}// end of namespace vgAsyn
