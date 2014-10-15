


#include <vgStableHeaders.h>
#include <vgTerritory/vgtGdalHelper.h>


namespace vgTerritory {
	
	
#define VGT_GDAL_MEM_PRE String("/vsimem/")
	
	//----------------------------------------------------------------
	String GdalHelper::getMemName( const String& filename )
	{
		String shortname = 
			vgKernel::StringUtility::getFilenameFromAbsolutePath( filename );

		return VGT_GDAL_MEM_PRE + shortname;
	}
	//----------------------------------------------------------------
	bool GdalHelper::createMemFile( const String& abs_filepath )
	{
		vgKernel::StreamReaderPtr preader = 
			vgKernel::StreamReaderFactory::createFromFile( abs_filepath );

		int nInDataLength  = preader->size();

		char* pabyInData = new char[ nInDataLength ];
		memset( pabyInData , 0 , nInDataLength );

		int readnum = preader->read( pabyInData , nInDataLength );
		assert( readnum == nInDataLength );

		preader.setNull();

		return createMemFileFromBuffer( abs_filepath, pabyInData, nInDataLength , true );
	}
	//----------------------------------------------------------------
	bool GdalHelper::createMemFileFromBuffer( const String& filename , 
		void* buffer, int buffer_size_in_bytes,
		bool take_ownership )
	{
		FILE* ff = VSIFileFromMemBuffer( getMemName( filename ).c_str(), 
			(GByte*)buffer, 
			buffer_size_in_bytes, take_ownership? TRUE: FALSE );

		if ( ff == NULL )
		{
			return false;
		}

		VSIFCloseL( ff ); 

		return true;
	}
	//----------------------------------------------------------------
	bool GdalHelper::deleteMemFile( const String& filename )
	{
		int ret = VSIUnlink( getMemName( filename).c_str() ); 

		return true;
	}
	//----------------------------------------------------------------



}// end of namespace vgTerritory
