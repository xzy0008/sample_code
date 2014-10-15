
#ifdef __cplusplus
extern "C" {
#endif


	typedef void	(*pfnGisManager_reset)();
	extern VGG_EXPORT  void GisManager_reset();

	typedef void	(*pfnGisManager_uninitBeforeOpenGLDestroy)();
	extern VGG_EXPORT  void GisManager_uninitBeforeOpenGLDestroy();

	typedef void	(*pfnGisManager_renderGisElements)();
	extern VGG_EXPORT  void GisManager_renderGisElements();

	typedef void	(*pfnGisManager_setGisAnalysis)( 
		vgGIS3D::EGisState eType);
	extern VGG_EXPORT  void GisManager_setGisAnalysis( 
		vgGIS3D::EGisState eType);

	typedef vgGIS3D::EGisState	(*pfnGisManager_getAnalysisType)();
	extern VGG_EXPORT  vgGIS3D::EGisState GisManager_getAnalysisType();

	typedef void* GisAnalysisH;

	typedef GisAnalysisH (*pfnGisManager_getGisAnalysis)();
	extern VGG_EXPORT  GisAnalysisH GisManager_getGisAnalysis();


	typedef void* RendererH;

	typedef bool (*pfnGisDataManager_setSelectMode)( 
		RendererH selected_layer , const bool& enable );
	extern VGG_EXPORT  bool GisDataManager_setSelectMode( 
		RendererH selected_layer , const bool& enable );


	typedef void* DataSourceH;

	typedef DataSourceH (*pfnGisDataManager_openShapeFile)( const String& filepath );
	extern VGG_EXPORT  DataSourceH GisDataManager_openShapeFile( const String& filepath );

	typedef DataSourceH (*pfnGisDataManager_openShapeFileSpecially)( const String& filepath );
	extern VGG_EXPORT  DataSourceH GisDataManager_openShapeFileSpecially( const String& filepath );


	typedef void* LayerH;

	typedef LayerH (*pfnGisDataManager_getLayerByShortName)( const String& filepath );
	extern VGG_EXPORT  LayerH GisDataManager_getLayerByShortName( const String& filepath );


	typedef void* DataSourcePtrMapH;

	typedef DataSourcePtrMapH (*pfnGisDataManager_getDataSources)( );
	extern VGG_EXPORT  DataSourcePtrMapH GisDataManager_getDataSources( );

	typedef void (*pfnGisDataManager_initAfterOpenGLSetup)( );
	extern VGG_EXPORT  void GisDataManager_initAfterOpenGLSetup( );

	typedef void (*pfnGisDataManager_uninitBeforeOpenGLDestroy)( );
	extern VGG_EXPORT  void GisDataManager_uninitBeforeOpenGLDestroy( );

	typedef void (*pfnGisDataManager_saveProject)(const String& filepath);
	extern VGG_EXPORT  void GisDataManager_saveProject(const String& filepath);

	typedef void* (*pfnGisDataManager_readProject)(const String& filepath);
	extern VGG_EXPORT  void* GisDataManager_readProject(const String& filepath);

	typedef void (*pfnGisDataManager_readProjectExtra)(const String& filepath);
	extern VGG_EXPORT  void GisDataManager_readProjectExtra(const String& filepath);

	typedef bool (*pfnGisDataManager_getSelectFlag)( );
	extern VGG_EXPORT  bool GisDataManager_getSelectFlag( );


	typedef  void (*pfntranslateAllShape)(const double& offsetX, const double& offsetY,
		const double& offsetZ);
	extern VGG_EXPORT void translateAllShape(const double& offsetX, const double& offsetY,
		const double& offsetZ);


	typedef void* GeometryPointerVecH;

	typedef GeometryPointerVecH (*pfnGisDataManager_getSelectGeometriesFromLayer)(LayerH layer);
	extern VGG_EXPORT  GeometryPointerVecH GisDataManager_getSelectGeometriesFromLayer(LayerH layer);


	typedef void* LayerPtrVectorH;

	typedef LayerPtrVectorH (*pfnGisDataManager_getLayersFromDataSource)(DataSourceH src);
	extern VGG_EXPORT  LayerPtrVectorH GisDataManager_getLayersFromDataSource(DataSourceH src);


	typedef void* ShapeDataSourceEntryH;

	typedef  ShapeDataSourceEntryH (*pfncreateEntryFromRenderer)();
	extern VGG_EXPORT ShapeDataSourceEntryH createEntryFromRenderer();

#ifdef __cplusplus
}
#endif
