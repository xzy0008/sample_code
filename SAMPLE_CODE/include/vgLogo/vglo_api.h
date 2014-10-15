/*! \file vglo_api.h
\brief 图标 模块接口函数
*/

#ifdef __cplusplus
extern "C" {
#endif

/** \fn void LogoManager_getRenderstate()
\brief 得到渲染状态：TRUE为显示logo，FALSE为隐藏logo
*/
typedef bool (*pfnLogoManager_getRenderstate)();
extern VGL_EXPORT bool LogoManager_getRenderstate();

/** \fn void LogoManager_setRenderstate( bool _render )
\brief 设置渲染状态
\param _render TRUE为显示logo，FALSE为隐藏logo
*/
typedef void (*pfnLogoManager_setRenderstate)( bool _render );
extern VGL_EXPORT void LogoManager_setRenderstate( bool _render );

typedef void (*pfnLogoManager_OutPutHawkeyeMapInSky)( String _filename  );

extern VGL_EXPORT  void LogoManager_OutPutHawkeyeMapInSky(String _filename  );

typedef bool (*pfnLogoManager_getcompassrendersign)( );

extern VGL_EXPORT  bool LogoManager_getcompassrendersign( );

typedef void (*pfnLogoManager_setcompassrendersign)( bool _render );

extern VGL_EXPORT  void LogoManager_setcompassrendersign( bool _render );

typedef bool (*pfnLogoManager_getsmallmaprendersign)( );

extern VGL_EXPORT  bool LogoManager_getsmallmaprendersign( );

typedef void (*pfnLogoManager_setsmallmaprendersign)( bool _render );

extern VGL_EXPORT  void LogoManager_setsmallmaprendersign( bool _render );

typedef bool (*pfnLogoManager_getsmallmapdatasign)( );

extern VGL_EXPORT  bool LogoManager_getsmallmapdatasign( );
 
#ifdef __cplusplus
}
#endif
