


#include <vgStableHeaders.h>
#include "vgentry/vgShapeLayerEntryEX.h"

#include "gdal/ogrsf_frmts.h"
#include "gdal/ogr_api.h"
#include <vgShape/vgshShapeManager.h>

//----------------------------------------------------------------
void ShapeLayerEntryEx::pushPropertiesEx( PropertiesParamVector& params )
{
	using namespace vgShape;

	GeometryPointerVec* geos = getLayerPtr()->getGeometries();
	Geometry* geo = (*geos)[0];
	OGRFeaturePtr pfeature = geo->getOGRFeaturePtr();
	OGRFeature* poFeature = pfeature.getPointer();

	OGRFeatureDefn *poFDefn = poFeature->GetDefnRef();

	assert( poFDefn != NULL );
	int fieldcount = poFDefn->GetFieldCount();

	/**
	@author  	lss
	@brief		πÿº¸◊÷∂Œ…Ë÷√
	*/
	VG_PUSH_PROP_GROUP( params , "Layer Attributes:" );

	VG_PUSH_OPTION_START( params, "Key Field", _keyFieldName);
	for ( int i = 0 ; i < fieldcount ; ++ i )
	{
		OGRFieldDefn* fielddefn = poFDefn->GetFieldDefn( i );
		assert( fielddefn != NULL );

		OGRFieldType fieldtype = fielddefn->GetType();

		String fielddesc = fielddefn->GetNameRef();

		VG_PUSH_OPTION_ITEM( params, fielddesc);
	}

	if (_keyFieldName != "")
	{
		VG_PUSH_OPTION_ITEM( params, "");
	}

	VG_PUSH_OPTION_END( params );
}

//----------------------------------------------------------------
void ShapeLayerEntryEx::updateInternalEx()
{
	using namespace vgShape;

	assert(0);
	//ShapeManager::getSingleton().setQueryRatioKeyField(_keyFieldName);
}
//----------------------------------------------------------------