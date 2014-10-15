


#include <vgStableHeaders.h>

#include <vgGis/vgGisManager.h>
#include <vgGis3d/vggiGisDataManager.h>
#include <vgGIS3D/vggiExtendedUtility.h>
#include <vgEntry/vgGisDataSourceEntry.h>

using namespace vgGIS3D;

void	GisManager_reset()
{
	GisManager::getSingleton().reset();
}

void	GisManager_uninitBeforeOpenGLDestroy()
{
	GisManager::getSingleton().uninitBeforeOpenGLDestroy();
}

void	GisManager_renderGisElements()
{
	GisManager::getSingleton().renderGisElements();
}

void	GisManager_setGisAnalysis(EGisState eType)
{
	GisManager::getSingleton().setGisAnalysis(eType);
}


EGisState	GisManager_getAnalysisType()
{
	return GisManager::getSingleton().getAnalysisType();
}

GisAnalysisH	GisManager_getGisAnalysis()
{
	return (GisAnalysisH)GisManager::getSingleton().getGisAnalysis();
}


bool GisDataManager_setSelectMode(RendererH selected_layer , const bool& enable )
{
	return GisDataManager::getSingleton().setSelectMode(
		(vgKernel::Renderer*)selected_layer, enable );
}

DataSourceH GisDataManager_openShapeFile( const String& filepath )
{
	DataSourcePtr& psource = GisDataManager::getSingleton().getCurrentDataSource();
	psource = GisDataManager::getSingleton().openShapeFile(filepath);

	return (DataSourceH)psource.getPointer();
}

DataSourceH GisDataManager_openShapeFileSpecially( const String& filepath )
{
	DataSourcePtr& psource = GisDataManager::getSingleton().getCurrentDataSource();
	psource = GisDataManager::getSingleton().openShapeFileSpecially(filepath);

	return (DataSourceH)psource.getPointer();
}


LayerH GisDataManager_getLayerByShortName( const String& filepath )
{
	return (LayerH)GisDataManager::getSingleton().getLayerByShortName(filepath);
}

DataSourcePtrMapH GisDataManager_getDataSources( )
{
	return (DataSourcePtrMapH)GisDataManager::getSingleton().getDataSources( );
}

void GisDataManager_initAfterOpenGLSetup( )
{
	GisDataManager::getSingleton().initAfterOpenGLSetup( );
}

void GisDataManager_uninitBeforeOpenGLDestroy( )
{
	GisDataManager::getSingleton().uninitBeforeOpenGLDestroy( );
}

void GisDataManager_saveProject(const String& filepath)
{
	GisDataManager::getSingleton().saveProject(filepath);
}

void* GisDataManager_readProject(const String& filepath)
{
	String strShpNames = GisDataManager::getSingleton().readProject(filepath);

	char* pNames = new char[strShpNames.size()+1];
	strcpy_s( pNames, strShpNames.size()+1, strShpNames.c_str() );
	return (void*)pNames;
}

void GisDataManager_readProjectExtra(const String& filepath)
{
	GisDataManager::getSingleton().readProjectExtra(filepath);
}

bool GisDataManager_getSelectFlag(const String& filepath)
{
	return GisDataManager::getSingleton().getSelectFlag();
}

void translateAllShape(const double& offsetX, const double& offsetY,
					   const double& offsetZ)
{
	vgGIS3D::ExtendedUtility::translateAllShape( offsetX, offsetY, offsetZ);
}

GeometryPointerVecH GisDataManager_getSelectGeometriesFromLayer(LayerH layer)
{
	return (GeometryPointerVecH)GisDataManager::getSingleton().
		getSelectGeometriesFromLayer( (Layer*)layer);
}

LayerPtrVectorH GisDataManager_getLayersFromDataSource(DataSourceH src)
{
	return (DataSourceH)GisDataManager::getSingleton().
		getLayersFromDataSource( (DataSource*)src );
}

ShapeDataSourceEntryH createEntryFromRenderer()
{
	DataSourcePtr& psource = GisDataManager::getSingleton().getCurrentDataSource();

	GisDataSourceEntry* ds = 
		new GisDataSourceEntry( psource );

	psource.releaseRef();

	return ds;
}


