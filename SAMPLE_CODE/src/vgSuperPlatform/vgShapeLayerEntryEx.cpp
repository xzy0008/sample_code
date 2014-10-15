


#include <vgStableHeaders.h>
#include "vgShapeLayerEntryEX.h"

#include <vgShape/vgshShapeManager.h>

//----------------------------------------------------------------
void ShapeLayerEntryEx::pushPropertiesEx( PropertiesParamVector& params )
{
	using namespace vgShape;

/*	GeometryPointerVec* geos = getLayerPtr()->getGeometries();
	Geometry* geo = (*geos)[0];
	OGRFeaturePtr pfeature = geo->getOGRFeaturePtr();
	OGRFeature* poFeature = pfeature.getPointer();

	OGRFeatureDefn *poFDefn = poFeature->GetDefnRef();

	assert( poFDefn != NULL );
	int fieldcount = poFDefn->GetFieldCount();

	
	
	PropertiesParam param;
	param.label = "Layer Attributes:";
	param.typeId = PROP_ITEM_GROUP;
	param.dataType = PROP_DATA_NONE;
	param.connectedPtr = NULL;
	param.comment = string();
	params.push_back(param);

	param.label = "Key Field";
	param.typeId = PROP_ITEM_DATA;
	param.dataType = PROP_DATA_OPTION_START;
	param.connectedPtr = &_keyFieldName;
	params.push_back(param);

	for ( int i = 0 ; i < fieldcount ; ++ i )
	{
		OGRFieldDefn* fielddefn = poFDefn->GetFieldDefn( i );
		assert( fielddefn != NULL );

		OGRFieldType fieldtype = fielddefn->GetType();

		param.label = fielddefn->GetNameRef();
		param.typeId = PROP_ITEM_DATA;
		param.dataType = PROP_DATA_OPTION_ITEM;
		params.push_back( param ); 
	}


	if (_keyFieldName != "")
	{
		param.label = "";
		param.typeId = PROP_ITEM_DATA;
		param.dataType = PROP_DATA_OPTION_ITEM;
		params.push_back(param);
	}

	param.typeId = PROP_ITEM_DATA;
	param.dataType = PROP_DATA_OPTION_END;
	params.push_back(param);*/
}

//----------------------------------------------------------------
void ShapeLayerEntryEx::updateInternalEx()
{
	using namespace vgShape;

	ShapeManager::getSingleton().setQueryRatioKeyField(_keyFieldName);
}
//----------------------------------------------------------------