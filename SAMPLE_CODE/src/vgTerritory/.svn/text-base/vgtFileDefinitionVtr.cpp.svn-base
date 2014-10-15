


#include <vgStableHeaders.h>
#include <vgTerritory/vgtFileDefinitionVtr.h>
#include <vgKernel/vgkStringUtility.h>


namespace vgTerritory {
	
	
	
	
	//----------------------------------------------------------------
	void VtrHeader::setDefault()
	{
		_fourCC[0] = 'V';
		_fourCC[1] = 'T';
		_fourCC[2] = 'R';
		_fourCC[3] = 0;

		_version = 1;
		_sizeOfWholeFile = 0;

		_sizeOfHeader = sizeof( VtrHeader );

		_numberOfBriefs		= 0;
		_lengthOfOneBrief		= sizeof( VtrBrief );
		_positionOfBriefs		= 0;
		//_reserved1		= 0;
		//_reserved2		= 0;

		memset( _filledColor , 0 , 4 );

		_reserved3		= 0;
		_reserved4		= 0;

		memset( name , 0 , VTR_NAME_LENGTH );
		memset( imageFilename , 0 , VTR_NAME_LENGTH );

		N = 0;	
		cellTexSize = 0;
		xTotalNum = 0;			
		zTotalNum = 0;

		originX = 0.0;		
		originY = 0.0;
		originZ = 0.0;

		cellsize = 0.0f;

		numOfCenterLayers = 0;

		_nextVtrFileID = 0;
	}
	//----------------------------------------------------------------


	//----------------------------------------------------------------
	void VtrBrief::setDefault()
	{
		memset( _fileName , 0 , VTR_NAME_LENGTH );

		_metaFileOffset = 0;
		_metaFileSize = 0;
	}
	//----------------------------------------------------------------
	bool VtrBrief::getInfoFromBuffer( const String& filemetaname , 
		const char* const buffer, const long& buffer_size )
	{
		assert( buffer != NULL );
		assert( buffer_size > 0 );

		if ( buffer == NULL || buffer_size <= 0 )
		{
			return false;
		}

		if ( filemetaname.size() >= VTR_NAME_LENGTH )
		{
			return false;
		}

		String upperName = filemetaname;
		vgKernel::StringUtility::toLowerCase( upperName );
		strcpy( _fileName , upperName.c_str() );
		assert( _fileName[ VTR_NAME_LENGTH - 1 ] == 0 );

		memcpy( &_vgtrHeader , buffer , sizeof( _vgtrHeader ) );

		_metaFileSize = buffer_size;

		assert( _vgtrHeader.dataLen[0] != 0 );
		assert( _vgtrHeader.dataLen != 0 );

		if ( _vgtrHeader.fourCC[0] != 'v' || 
			_vgtrHeader.fourCC[1] != 'g'  || 
			_vgtrHeader.fourCC[2] != 't' || 
			_vgtrHeader.fourCC[3] != 'r'  )
		{
			return false;
		}

		return true;
	}
	//----------------------------------------------------------------

}// end of namespace vgTerritory
