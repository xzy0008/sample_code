



#include <vgStableHeaders.h>
#include <vgTerritory/vgDemBlock.h>


namespace vgTerritory {
	
	
	//----------------------------------------------------------------
	DemBlock::DemBlock()
	{
		_xNum = 0;
		_zNum = 0;
		_zData = NULL;
	}
	//----------------------------------------------------------------
	DemBlock::~DemBlock()
	{
		destroy();
	}
	//----------------------------------------------------------------
	void DemBlock::destroy()
	{
		if ( _zData != NULL )
		{
			delete[] _zData;
			_zData = NULL;
		}
	}
	//----------------------------------------------------------------
	void DemBlock::setData(const String& filename , const uint& x_num , 
		const uint& y_num , const double& xllcorner , 
		const double& yllcorner, const double& origin_y,
		const double& top_y , const float& cell ,  float* data )
	{
		_demFilename = filename;

		assert( data != NULL );

		_zData = data;
		_xNum = x_num;
		_zNum = y_num;

		_originX = xllcorner;
		_originZ = yllcorner;
		_originY = origin_y;

		_topY = top_y;


		_cellSize = cell;
	}
	//----------------------------------------------------------------
	String DemBlock::getDetails()
	{
		std::ostringstream o;
		o << "-- DemBlock Details: ( "
			<< " Filename : " <<_demFilename
			<< " , _xNum : " << _xNum
			<< " , _zNum : " << _zNum
			<< " , _originX : " << _originX
			<< " , _originY : " << _originY
			<< " , _originZ : " << _originZ
			<< " , _topY : " << _topY
			<< " , _cellSize : " << _cellSize
			<< " , _imgRect : " << _imgRect.getDetails()
			<< " )";

		return o.str();
	}
	//----------------------------------------------------------------

}// end of namespace vgTerritory
