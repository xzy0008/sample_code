


#include <vgStableHeaders.h>
#include <vgTerritory/vgtGeoGlobalData.h>
#include <vgTerritory/vgtGeoDemManager.h>


namespace vgTerritory {
	
	
	
	
	//----------------------------------------------------------------
	GeoGlobalData::GeoGlobalData()
	{
		_globalUpperLeftX = 0.0;
		_globalUpperLeftY = 0.0;
		_globalPixelSizeX = 0.0;
		_globalPixelSizeY = 0.0;
		_globalMinElevation = 0.0;
		_globalMaxElevation = 0.0;

		_globalLowerRightX = 0.0;
		_globalLowerRightY = 0.0;

		_isUpdated = false;

		_axisLeftDown = false;

		_globalChunkSize= 0;
		_globalAdjustCellsize = 0.0f;

		_globalElevationScale = 0.0f;

		_globalN =0;
		_globalCellTexSize = 0;

		_clearTempData = true;

		_genElevationOverview = true ;
		_genImageOverview = true ;
		_genDebugImages = false;

		_maxLayerNum = 0;
		memset( _filledColor , 0 , 4 );

		memset( _filledBlackColor , 0 ,  4 ); 
	}
	//----------------------------------------------------------------
	bool GeoGlobalData::isValid() const
	{
		return _isUpdated;
	}
	//----------------------------------------------------------------
	String GeoGlobalData::getDetails()
	{
		assert( isValid() );

		std::ostringstream o;

		o << "GeoGlobalData Details: ("
			<< " _axisLeftDown: " << _axisLeftDown
			<< ", _globalUpperLeftX: " << _globalUpperLeftX
			<< ", _globalUpperLeftY: " << _globalUpperLeftY
			<< ", _globalLowerRightX: " << _globalLowerRightX
			<< ", _globalLowerRightY: " << _globalLowerRightY
			<< ", _globalPixelSizeX: " << _globalPixelSizeX
			<< ", _globalPixelSizeY: " << _globalPixelSizeY
			<< ", _globalMinElevation: " << _globalMinElevation
			<< ", _globalMaxElevation: " << _globalMaxElevation
			<< ", _globalRect: " << _globalRect.getDetails()
			<< ", _globalAdjustRect: " << _globalAdjustRect.getDetails()
			<< " )";

		return o.str();
	}
	//----------------------------------------------------------------
	void GeoGlobalData::cleanTempFiles()
	{
		ScopedLock locker( _sect );

		if ( _clearTempData == false )
		{
			return;
		}

		vgKernel::StringVector::iterator iter = _needToCleanFiles.begin();
		vgKernel::StringVector::iterator iter_end = _needToCleanFiles.end();

		for ( ; iter != iter_end ; ++ iter )
		{
			vgKernel::SystemUtility::removeFile( *iter , false );
		}
		_needToCleanFiles.clear();
	}
	//----------------------------------------------------------------
	VgtrHeaderPtr GeoGlobalData::getVgtrHeaderPtr()
	{
		VgtrHeader* ret = new VgtrHeader;

		ret->cellsize = _globalAdjustCellsize;

		ret->cellTexSize = _globalCellTexSize;

		ret->xNum = _globalAdjustRect.getWidth() + 1;
		ret->zNum = ret->xNum;

		ret->displaceScaleY = _globalElevationScale;
		ret->displaceChunkScale  = 1.0f;
		ret->displaceChunkBiasX  = 0.0f;
		ret->displaceChunkBiasZ = 0.0f;
		
		assert( _terrainName.size() < VG_VGTR_NAME_LENGTH - 1 ); 
		strcpy( ret->name , _terrainName.c_str() );

		ret->N = _globalN;

		ret->originX = _globalUpperLeftX;
		ret->originY = _globalMinElevation;
		ret->originZ = _globalUpperLeftY;

		return VgtrHeaderPtr( ret );
	}
	//----------------------------------------------------------------
	void GeoGlobalData::pushNeedToCleanFile( const vgKernel::StringVectorPtr namelist )
	{
		ScopedLock locker( _sect );

		if ( _clearTempData == false )
		{
			return;
		}
		if ( namelist.isNull() == true )
		{
			return;
		}

		vgKernel::StringVector::iterator iter = namelist->begin();
		vgKernel::StringVector::iterator iter_end = namelist->end();

		for ( ; iter != iter_end ; ++ iter )
		{
			if ( *iter == "" )
			{
				continue;
			}
			_needToCleanFiles.push_back( *iter );
		}

		return;
	}
	//----------------------------------------------------------------
	void GeoGlobalData::pushNeedToCleanFile( const String& filename )
	{
		ScopedLock locker( _sect );

		if ( _clearTempData == false )
		{
			return;
		}

		if ( filename == "" )
		{
			return;
		}

		_needToCleanFiles.push_back( filename );
	}
	//----------------------------------------------------------------


}// end of namespace vgTerritory
