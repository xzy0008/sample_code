


#include <vgStableHeaders.h>
#include <vgKernel/vgkCrcUtility.h>


namespace vgKernel {
	
	
	
	//----------------------------------------------------------------
	bool CrcUtility::getFileCrc32Code( const String& absolute_file_path ,
		DWORD& crc_code )
	{
		DWORD result = 
			CCrc32Static::FileCrc32Assembly( absolute_file_path.c_str() , crc_code );

		if ( result != NO_ERROR )
		{
			return false;
		}

		return true;
	}
	//----------------------------------------------------------------

}// end of namespace vgKernel
