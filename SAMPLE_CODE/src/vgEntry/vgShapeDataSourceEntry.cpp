



#include <vgStableHeaders.h>
#include "vgentry/vgShapeDataSourceEntry.h"
#include <vgEntry/vgEntryUtility.h>
#include <vgUIController/vgUIController.h>
#include <vgShape/vgshShapeManager.h>

#include <vgKernel/vgkStringUtility.h>

//----------------------------------------------------------------
PropertiesParamVector& ShapeDataSourceEntry::pushPropertiesParam(
	PropertiesParamVector& params )
{
	VG_PUSH_PROP_GROUP( params , "Properties" );
	VG_PUSH_PROP_CONST_STR( params , "filepath" , &_filepath );

	return params;
}
//----------------------------------------------------------------
void ShapeDataSourceEntry::updateUIFromInternal()
{
	_filepath = _datasource->getFilePath();

}
//----------------------------------------------------------------
void ShapeDataSourceEntry::updateInternalFromUI(
	const String& changed_param_name )
{

}
//----------------------------------------------------------------
ShapeDataSourceEntry::~ShapeDataSourceEntry()
{
	//assert(0);


}
//----------------------------------------------------------------
//bool ShapeDataSourceEntry::onDelete()
//{
//
//	vgShape::ShapeManager::getSingleton().clearDataSource( _datasource );
//
//	vgUI::UIController::getSingleton().DeleteNode( this , true );
//	return true;
//}

bool ShapeDataSourceEntry::onUserDefinedDeletion()
{
	//------------------------------------------
	// 首先删除所有的layers
	// 这个时候会自动调用entry的delete
	// 于是所有的子节点应该都被删除掉了
	// 此时直接删除即可.
	//------------------------------------------
	_datasource->deleteAllLayers();

	vgShape::ShapeManager::getSingleton().clearDataSourcePtr( _datasource );

	return true;
}
//----------------------------------------------------------------
String ShapeDataSourceEntry::GetName()
{
	return vgKernel::StringUtility::getFilenameFromAbsolutePath( 
		_datasource->getFilePath() );
}
//----------------------------------------------------------------
