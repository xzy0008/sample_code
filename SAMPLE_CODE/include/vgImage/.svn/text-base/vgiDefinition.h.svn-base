




#ifndef __VGIDEFINITION_H__
#define __VGIDEFINITION_H__




#include <vgKernel/vgkForward.h>


#define VGI_DESC  "vgImageDLL"

#ifdef VGI_DLL
#	ifdef VGI_NONCLIENT_BUILD_DLL
#		define  VGI_EXPORT __declspec( dllexport )
#	else
#		define  VGI_EXPORT __declspec( dllimport )
#	endif
#else
#	define  VGI_EXPORT VGK_EXPORT
#endif




#	ifdef _DEBUG
#		define  VGI_DLL_NAME VGI_DESC##"_Debug.dll"
#		define  VGI_LIB_NAME VGI_DESC##"_Debug.lib"
#	else
#		define  VGI_DLL_NAME VGI_DESC##"_Release.dll"
#		define  VGI_LIB_NAME VGI_DESC##"_Release.lib"
#	endif



#define VGI_MULTITHREAD_UI_REFRESH_WAIT	50


//------------------------------------------
// Image namespace
//------------------------------------------
#define VGI_CONF_NAME		"Image"


//------------------------------------------
// Image space
//------------------------------------------

#define VGI_CONF_SMALLIMGREF_ENABLE		"SmallImageReferencerEnable"
#define VGI_CONF_SMALLIMGREF_ENABLE_DEFAULT		true
#define VGI_CONF_SMALLIMGREF_ENABLE_DEFAULT_STR		"1"

#define VGI_CONF_SMALLIMGREF_LOADTHRESHOLD		"SmallImageFileSizeThreshold"
#define VGI_CONF_SMALLIMGREF_LOADTHRESHOLD_DEFAULT		1749040
#define VGI_CONF_SMALLIMGREF_LOADTHRESHOLD_DEFAULT_STR		"1749040"

	


#endif // end of __VGIDEFINITION_H__