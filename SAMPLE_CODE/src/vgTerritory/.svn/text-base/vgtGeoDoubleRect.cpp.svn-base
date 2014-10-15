


#include <vgStableHeaders.h>
#include <vgTerritory/vgtGeoDoubleRect.h>
#include <vgTerritory/vgtGeoDemManager.h>


namespace vgTerritory {
	
	
	
	
	//----------------------------------------------------------------
	void GeoDoubleRect::getAxisFlag()
	{
		//GeoGlobalData* globaldata = GeoDemManager::getSingleton().getGlobalDataPtr();

		if ( _globalData == NULL )
		{
			_CrtDbgBreak();
		}

		assert( _globalData != NULL );

		_axisLeftDown = &_globalData->_axisLeftDown;
	}
	//----------------------------------------------------------------
	void GeoDoubleRect::makeSafe()
	{
		//GeoDoubleRect tmp( *this );

		double _tmp_topLeftX = _topLeftX;
		double _tmp_topLeftY = _topLeftY;
		double _tmp_lowRightX = _lowRightX;
		double _tmp_lowRightY = _lowRightY;

		if ( _axisLeftDown == NULL )
		{
			getAxisFlag();
		}

		assert( _axisLeftDown != NULL );

		//if ( *_axisLeftDown == false )
		//{
			_topLeftX = VGT_MIN( _tmp_topLeftX , _tmp_lowRightX );
			_topLeftY = VGT_MIN( _tmp_topLeftY , _tmp_lowRightY );

			_lowRightX = VGT_MAX( _tmp_topLeftX , _tmp_lowRightX );
			_lowRightY = VGT_MAX( _tmp_topLeftY , _tmp_lowRightY );
		//}
		//else
		//{
		//	_topLeftX = VGT_MIN( _tmp_topLeftX , _tmp_lowRightX );
		//	_topLeftY = VGT_MAX( _tmp_topLeftY , _tmp_lowRightY );

		//	_lowRightX = VGT_MAX( _tmp_topLeftX , _tmp_lowRightX );
		//	_lowRightY = VGT_MIN( _tmp_topLeftY , _tmp_lowRightY );
		//}

		assert( isSafe() );
	}
	//----------------------------------------------------------------
	void GeoDoubleRect::setDefault()
	{
		_topLeftX = 0.0;
		_topLeftY = 0.0;
		_lowRightX = 0.0;
		_lowRightY = 0.0;

		_pixelWidth = 0;
		_pixelHeight = 0;

		_globalData = NULL;
		_axisLeftDown = NULL;

	}
	//----------------------------------------------------------------
	bool GeoDoubleRect::isSafe() const
	{
		assert( _globalData != NULL );
		assert( _axisLeftDown != NULL );

		bool ret = false;

		//if ( *_axisLeftDown == false )
		//{
			ret = (_topLeftX <= _lowRightX) && (_topLeftY <= _lowRightY);
		//}
		//else
		//{
		//	ret = (_topLeftX <= _lowRightX) && (_topLeftY >= _lowRightY);
		//}

		return ret;
	}
	//----------------------------------------------------------------
	ImageRect GeoDoubleRect::getImageRect( const double& pixelsizeX ,
		const double& pixelsizeY )
	{
		assert( isSafe() );
		ImageRect ret;

		ret.minPos.x = _topLeftX / abs( pixelsizeX ) + 0.5f ;
		ret.minPos.y = _topLeftY / abs( pixelsizeY ) + 0.5f ;

		ret.maxPos.x = _lowRightX / abs( pixelsizeX ) + 0.5f ;
		ret.maxPos.y = _lowRightY / abs( pixelsizeY ) + 0.5f ;

		ret.makeSafe();

		//assert( ret.isSafe() );

		return ret;
	}
	//----------------------------------------------------------------
	bool GeoDoubleRect::findIntersection( const GeoDoubleRect& rkBox, 
		GeoDoubleRect& rkIntr ) const
	{
		assert( isSafe() );
		assert( rkBox.isSafe() );

		if ( testIntersect( rkBox ) == false )
		{
			return false;
		}

		if ( _topLeftX <= rkBox._topLeftX )
		{
			rkIntr._topLeftX = rkBox._topLeftX;
		}
		else
		{
			rkIntr._topLeftX = _topLeftX;
		}

		if ( _topLeftY <= rkBox._topLeftY )
		{
			rkIntr._topLeftY = rkBox._topLeftY;
		}
		else
		{
			rkIntr._topLeftY = _topLeftY;
		}

		if ( _lowRightX <= rkBox._lowRightX )
		{
			rkIntr._lowRightX = _lowRightX;
		}
		else
		{
			rkIntr._lowRightX = rkBox._lowRightX;
		}

		if ( _lowRightY <= rkBox._lowRightY )
		{
			rkIntr._lowRightY = _lowRightY;
		}
		else
		{
			rkIntr._lowRightY = rkBox._lowRightY;
		}

		return true;
	}
	//----------------------------------------------------------------



}// end of namespace vgTerritory
