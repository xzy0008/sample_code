



#include <vgStableHeaders.h>
#include <vgShape/vgshGeometry.h>
#include <vgShape/vgshLayer.h>
#include <gdal/ogrsf_frmts.h>
#include <gdal/ogr_api.h>




namespace vgShape {
	


	//----------------------------------------------------------------
	Geometry::Geometry( OGRFeature* feature, Layer* father_layer )
		: _drawing( this )
	{
		assert( feature != NULL );
		_ogrFeatureFID = feature->GetFID();
		_fatherLayer = father_layer;
		assert( _fatherLayer != NULL );
	}
	//----------------------------------------------------------------
	OGRFeature* Geometry::getOGRFeature()
	{
		return _fatherLayer->getOGRFeatureByFID( _ogrFeatureFID );
	}
	//----------------------------------------------------------------
	void Geometry::setFeature( OGRFeature* feature )
	{
		return _fatherLayer->setOGRFeature( feature );
	}
	//----------------------------------------------------------------
	OGRFeaturePtr Geometry::getOGRFeaturePtr()
	{
		OGRFeature* ret = getOGRFeature();
		
		if ( ret != NULL )
		{
			return OGRFeaturePtr( ret );
		}

		return OGRFeaturePtr();
	}

	//----------------------------------------------------------------



}// end of namespace vgShape
