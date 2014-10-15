


#ifndef __VGLODEFINITION_H__
#define __VGLODEFINITION_H__

#include <vgKernel/vgkForward.h>




#define VGL_DESC  "vgLogoDLL"

#ifdef VGL_DLL
#	ifdef VGL_NONCLIENT_BUILD_DLL
#		define  VGL_EXPORT __declspec( dllexport )
#	else
#		define  VGL_EXPORT __declspec( dllimport )
#	endif
#else
#	define  VGL_EXPORT VGK_EXPORT
#endif




#	ifdef _DEBUG
#		define  VGL_DLL_NAME VGL_DESC##"_Debug.dll"
#		define  VGL_LIB_NAME VGL_DESC##"_Debug.lib"
#	else
#		define  VGL_DLL_NAME VGL_DESC##"_Release.dll"
#		define  VGL_LIB_NAME VGL_DESC##"_Release.lib"
#	endif


#include <vgLogo/vglo_api.h>


#endif // end of __VGLODEFINITION_H__