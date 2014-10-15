



#include <vgStableHeaders.h>
#include "vgentry/vgGisDataSourceEntry.h"
#include <vgEntry/vgEntryUtility.h>
#include <vgUIController/vgUIController.h>
#include <vgGIS3d/vggiGisDataManager.h>

#include <vgKernel/vgkStringUtility.h>

//----------------------------------------------------------------
PropertiesParamVector& GisDataSourceEntry::pushPropertiesParam(
	PropertiesParamVector& params )
{
	VG_PUSH_PROP_GROUP( params , "Properties" );
	VG_PUSH_PROP_CONST_STR( params , "filepath" , &_filepath );

	return params;
}
//----------------------------------------------------------------
void GisDataSourceEntry::updateUIFromInternal()
{
	_filepath = _datasource->getSourcePath();

}
//----------------------------------------------------------------
void GisDataSourceEntry::updateInternalFromUI(
	const String& changed_param_name )
{

}
//----------------------------------------------------------------
GisDataSourceEntry::~GisDataSourceEntry()
{
	//assert(0);


}
//----------------------------------------------------------------
//bool GisDataSourceEntry::onDelete()
//{
//
//	vgShape::ShapeManager::getSingleton().clearDataSource( _datasource );
//
//	vgUI::UIController::getSingleton().DeleteNode( this , true );
//	return true;
//}

bool GisDataSourceEntry::onUserDefinedDeletion()
{
	//------------------------------------------
	// 首先删除所有的layers
	// 这个时候会自动调用entry的delete
	// 于是所有的子节点应该都被删除掉了
	// 此时直接删除即可.
	//------------------------------------------
	_datasource->deleteAllLayers();

	vgGIS3D::GisDataManager::getSingleton().clearDataSourcePtr( _datasource );

	return true;
}
//----------------------------------------------------------------
String GisDataSourceEntry::GetName()
{
	return vgKernel::StringUtility::getFilenameFromAbsolutePath( 
		_datasource->getSourcePath() );
}
//----------------------------------------------------------------
