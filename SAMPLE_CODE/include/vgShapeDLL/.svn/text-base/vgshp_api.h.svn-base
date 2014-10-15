
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


#ifdef __cplusplus
}
#endif
