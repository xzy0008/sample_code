
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


#ifdef __cplusplus
}
#endif
