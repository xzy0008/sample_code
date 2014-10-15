#pragma once

#include <vgKernel/vgkForward.h>
#include <vgEntry/vgBaseEntryEx.h>
	
#include <vgGis3d/vggiDataSource.h>




class  VGG_EXPORT GisDataSourceEntry : 
	public vgBaseEntryEx
{
public:
	GisDataSourceEntry( vgGIS3D::DataSourcePtr pdatasource )
		: vgBaseEntryEx( NULL )
	{
		_datasource =  pdatasource;
		assert( _datasource.isNull() == NULL );
	}

	virtual ~GisDataSourceEntry();


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

	vgGIS3D::DataSourcePtr getShapeDataSource()
	{
		return _datasource;
	}

protected:

	virtual PropertiesParamVector& pushPropertiesParam( 
		PropertiesParamVector& params );

	virtual void updateUIFromInternal();

	virtual void updateInternalFromUI(const String& changed_param_name );



private:

	vgGIS3D::DataSourcePtr _datasource;

	String _filepath;

};

 