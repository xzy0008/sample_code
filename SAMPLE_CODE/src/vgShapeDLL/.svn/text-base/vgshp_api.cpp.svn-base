


#include <vgStableHeaders.h>

#include <vgShape/vgshShapeManager.h>
#include <vgShape/vgshExtendedUtility.h>
#include "vgEntry/vgShapeDataSourceEntry.h"

using namespace vgShape;

bool ShapeManager_setSelectMode(RendererH selected_layer , const bool& enable )
{
	return ShapeManager::getSingleton().setSelectMode(
		(vgKernel::Renderer*)selected_layer, enable );
}

DataSourceH ShapeManager_openShapeFile( const String& filepath )
{
	DataSourcePtr& psource = ShapeManager::getSingleton().getCurrentDataSource();
	psource = ShapeManager::getSingleton().openShapeFile(filepath);

	return (DataSourceH)psource.getPointer();
}

DataSourceH ShapeManager_openShapeFileSpecially( const String& filepath )
{
	DataSourcePtr& psource = ShapeManager::getSingleton().getCurrentDataSource();
	psource = ShapeManager::getSingleton().openShapeFileSpecially(filepath);

	return (DataSourceH)psource.getPointer();
}


LayerH ShapeManager_getLayerByShortName( const String& filepath )
{
	return (LayerH)ShapeManager::getSingleton().getLayerByShortName(filepath);
}

DataSourcePtrMapH ShapeManager_getDataSources( )
{
	return (DataSourcePtrMapH)ShapeManager::getSingleton().getDataSources( );
}

void ShapeManager_initAfterOpenGLSetup( )
{
	ShapeManager::getSingleton().initAfterOpenGLSetup( );
}

void ShapeManager_uninitBeforeOpenGLDestroy( )
{
	ShapeManager::getSingleton().uninitBeforeOpenGLDestroy( );
}

void ShapeManager_saveProject(const String& filepath)
{
	ShapeManager::getSingleton().saveProject(filepath);
}

void* ShapeManager_readProject(const String& filepath)
{
	String strShpNames = ShapeManager::getSingleton().readProject(filepath);

	char* pNames = new char[strShpNames.size()+1];
	strcpy_s( pNames, strShpNames.size()+1, strShpNames.c_str() );
	return (void*)pNames;
}

void ShapeManager_readProjectExtra(const String& filepath)
{
	ShapeManager::getSingleton().readProjectExtra(filepath);
}

bool ShapeManager_getSelectFlag(const String& filepath)
{
	return ShapeManager::getSingleton().getSelectFlag();
}

void translateAllShape(const double& offsetX, const double& offsetY,
					   const double& offsetZ)
{
	ExtendedUtility::translateAllShape( offsetX, offsetY, offsetZ);
}

GeometryPointerVecH ShapeManager_getSelectGeometriesFromLayer(LayerH layer)
{
	return (GeometryPointerVecH)ShapeManager::getSingleton().
		getSelectGeometriesFromLayer( (Layer*)layer);
}

LayerPtrVectorH ShapeManager_getLayersFromDataSource(DataSourceH src)
{
	return (DataSourceH)ShapeManager::getSingleton().
		getLayersFromDataSource( (DataSource*)src );
}

ShapeDataSourceEntryH createEntryFromRenderer()
{
	DataSourcePtr& psource = ShapeManager::getSingleton().getCurrentDataSource();
	
	ShapeDataSourceEntry* ds = 
		new ShapeDataSourceEntry( psource );

	psource.releaseRef();

	return ds;
}


