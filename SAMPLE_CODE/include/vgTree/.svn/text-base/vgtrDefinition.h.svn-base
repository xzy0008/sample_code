




#ifndef __VGTRDEFINITION_H__
#define __VGTRDEFINITION_H__


#include <vgKernel/vgkForward.h>


#define VGTR_DESC  "vgTreeDLL"

#ifdef VGTR_DLL
#	ifdef VGTR_NONCLIENT_BUILD_DLL
#		define  VGTR_EXPORT __declspec( dllexport )
#	else
#		define  VGTR_EXPORT __declspec( dllimport )
#	endif
#else
#	define  VGTR_EXPORT VGK_EXPORT
#endif



#	ifdef _DEBUG
#		define  VGTR_DLL_NAME VGTR_DESC##"_Debug.dll"
#		define  VGTR_LIB_NAME VGTR_DESC##"_Debug.lib"
#	else
#		define  VGTR_DLL_NAME VGTR_DESC##"_Release.dll"
#		define  VGTR_LIB_NAME VGTR_DESC##"_Release.lib"
#	endif


#endif // end of __VGTRDEFINITION_H__