


#include <vgStableHeaders.h>
#include <vgTerritory/vgtIoRequestElevationRetrive.h>
#include <vgTerritory/vgtDefinition.h>



namespace vgTerritory {


	//----------------------------------------------------------------
	IoRequestElevationRetrive::IoRequestElevationRetrive( vgAsyn::FileInfo* fileinfo , 
		float scaleY  )
		: vgAsyn::IoRequest( fileinfo )
	{
		setAsynchronousMode( false );

		_scaleY = scaleY;

		for ( int i = 0 ; i < 4 ; ++ i )
		{
			_elevation[i] = 0.0f;
		}
	}
	//----------------------------------------------------------------
	bool IoRequestElevationRetrive::anotherThreadHandler()
	{
		//dispatchMainThreadFunc();

		assert( _fileInfo->_fileSize % sizeof( float ) == 0);

		float* floatBuf = (float*)_buffer;

		_elevation[ VGT_LEFT_UP ] = *floatBuf;
		_elevation[ VGT_RIGHT_UP ] = *( floatBuf + 1 );
		_elevation[ VGT_LEFT_DOWN ] = *( floatBuf + _fileInfo->_fileSize / 4 - 2 );
		_elevation[ VGT_RIGHT_DOWN ] = *( floatBuf + _fileInfo->_fileSize / 4 - 1 );

		for ( int i = 0 ; i < 4 ; ++ i )
		{
			_elevation[i] *= _scaleY;
		}

		return true;
	}
	//----------------------------------------------------------------
	bool IoRequestElevationRetrive::mainThreadHandler()
	{
		return true;
	}
	//----------------------------------------------------------------
}// end of namespace vgTerritory
