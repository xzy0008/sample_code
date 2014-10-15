


#ifndef __VGOCDEFINITION_H__
#define __VGOCDEFINITION_H__

#include <vgKernel/vgkForward.h>




#define VGOC_DESC  "vgOccDLL"

#ifdef VGOC_DLL
#	ifdef VGOC_NONCLIENT_BUILD_DLL
#		define  VGOC_EXPORT __declspec( dllexport )
#	else
#		define  VGOC_EXPORT __declspec( dllimport )
#	endif
#else
#	define  VGOC_EXPORT VGK_EXPORT
#endif




#	ifdef _DEBUG
#		define  VGOC_DLL_NAME VGOC_DESC##"_Debug.dll"
#		define  VGOC_LIB_NAME VGOC_DESC##"_Debug.lib"
#	else
#		define  VGOC_DLL_NAME VGOC_DESC##"_Release.dll"
#		define  VGOC_LIB_NAME VGOC_DESC##"_Release.lib"
#	endif


#endif // end of __VGOCDEFINITION_H__