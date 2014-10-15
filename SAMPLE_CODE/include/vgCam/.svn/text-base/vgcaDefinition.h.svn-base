


#ifndef __VGCADEFINITION_H__
#define __VGCADEFINITION_H__



#include <vgKernel/vgkForward.h>


#define VGCA_DESC  "vgCamDLL"

#ifdef VGCA_DLL
#	ifdef VGCA_NONCLIENT_BUILD_DLL
#		define  VGCA_EXPORT __declspec( dllexport )
#	else
#		define  VGCA_EXPORT __declspec( dllimport )
#	endif
#else
#	define  VGCA_EXPORT VGK_EXPORT
#endif




#	ifdef _DEBUG
#		define  VGCA_DLL_NAME VGCA_DESC##"_Debug.dll"
#		define  VGCA_LIB_NAME VGCA_DESC##"_Debug.lib"
#	else
#		define  VGCA_DLL_NAME VGCA_DESC##"_Release.dll"
#		define  VGCA_LIB_NAME VGCA_DESC##"_Release.lib"
#	endif






#endif // end of __VGCADEFINITION_H__