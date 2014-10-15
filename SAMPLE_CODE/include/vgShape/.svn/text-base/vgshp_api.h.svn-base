
#ifdef __cplusplus
extern "C" {
#endif


	typedef void* RendererH;

	typedef bool (*pfnShapeManager_setSelectMode)( 
		RendererH selected_layer , const bool& enable );
	extern VGSH_EXPORT  bool ShapeManager_setSelectMode( 
		RendererH selected_layer , const bool& enable );


	typedef void* DataSourceH;

	typedef DataSourceH (*pfnShapeManager_openShapeFile)( const String& filepath );
	extern VGSH_EXPORT  DataSourceH ShapeManager_openShapeFile( const String& filepath );

	typedef DataSourceH (*pfnShapeManager_openShapeFileSpecially)( const String& filepath );
	extern VGSH_EXPORT  DataSourceH ShapeManager_openShapeFileSpecially( const String& filepath );


	typedef void* LayerH;

	typedef LayerH (*pfnShapeManager_getLayerByShortName)( const String& filepath );
	extern VGSH_EXPORT  LayerH ShapeManager_getLayerByShortName( const String& filepath );

	
	typedef void* DataSourcePtrMapH;

	typedef DataSourcePtrMapH (*pfnShapeManager_getDataSources)( );
	extern VGSH_EXPORT  DataSourcePtrMapH ShapeManager_getDataSources( );

	typedef void (*pfnShapeManager_initAfterOpenGLSetup)( );
	extern VGSH_EXPORT  void ShapeManager_initAfterOpenGLSetup( );

	typedef void (*pfnShapeManager_uninitBeforeOpenGLDestroy)( );
	extern VGSH_EXPORT  void ShapeManager_uninitBeforeOpenGLDestroy( );

	typedef void (*pfnShapeManager_saveProject)(const String& filepath);
	extern VGSH_EXPORT  void ShapeManager_saveProject(const String& filepath);

	typedef void* (*pfnShapeManager_readProject)(const String& filepath);
	extern VGSH_EXPORT  void* ShapeManager_readProject(const String& filepath);

	typedef void (*pfnShapeManager_readProjectExtra)(const String& filepath);
	extern VGSH_EXPORT  void ShapeManager_readProjectExtra(const String& filepath);

	typedef bool (*pfnShapeManager_getSelectFlag)( );
	extern VGSH_EXPORT  bool ShapeManager_getSelectFlag( );


	typedef  void (*pfntranslateAllShape)(const double& offsetX, const double& offsetY,
		const double& offsetZ);
	extern VGSH_EXPORT void translateAllShape(const double& offsetX, const double& offsetY,
		const double& offsetZ);


	typedef void* GeometryPointerVecH;

	typedef GeometryPointerVecH (*pfnShapeManager_getSelectGeometriesFromLayer)(LayerH layer);
	extern VGSH_EXPORT  GeometryPointerVecH ShapeManager_getSelectGeometriesFromLayer(LayerH layer);


	typedef void* LayerPtrVectorH;

	typedef LayerPtrVectorH (*pfnShapeManager_getLayersFromDataSource)(DataSourceH src);
	extern VGSH_EXPORT  LayerPtrVectorH ShapeManager_getLayersFromDataSource(DataSourceH src);


	typedef void* ShapeDataSourceEntryH;

	typedef  ShapeDataSourceEntryH (*pfncreateEntryFromRenderer)();
	extern VGSH_EXPORT ShapeDataSourceEntryH createEntryFromRenderer();

#ifdef __cplusplus
}
#endif
