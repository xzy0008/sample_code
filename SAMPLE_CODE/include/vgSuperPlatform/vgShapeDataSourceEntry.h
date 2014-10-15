



#ifndef __VGSHAPEDATASOURCEENTRY_H__
#define __VGSHAPEDATASOURCEENTRY_H__

#include <vgKernel/vgkForward.h>
#include "vgBaseEntryEx.h"
	
#include <vgShape/vgshDataSource.h>




class ShapeDataSourceEntry : 
	public vgBaseEntryEx
{
public:
	ShapeDataSourceEntry( vgShape::DataSourcePtr pdatasource )
		: vgBaseEntryEx( VG_ENTRY_SHAPE_DATASOURCE , NULL )
	{
		_datasource =  pdatasource;
		assert( _datasource.isNull() == NULL );
	}

	virtual ~ShapeDataSourceEntry();


public:

	// 删除时调用的函数
	//virtual bool onDelete();

	// 能够直接删除
	virtual bool canBeDeletedDirectly()
	{
		return true;
	}

	virtual bool onUserDefinedDeletion();

	virtual String GetName();

	vgShape::DataSourcePtr getShapeDataSource()
	{
		return _datasource;
	}

protected:

	virtual PropertiesParamVector& pushPropertiesParam( 
		PropertiesParamVector& params );

	virtual void updateUIFromInternal();

	virtual void updateInternalFromUI(const String& changed_param_name );



private:

	vgShape::DataSourcePtr _datasource;

	String _filepath;

};





#endif // end of __VGSHAPEDATASOURCEENTRY_H__