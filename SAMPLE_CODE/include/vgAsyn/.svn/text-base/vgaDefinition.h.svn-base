



#ifndef __VGADEFINITION_H__
#define __VGADEFINITION_H__


#include <vgKernel/vgkForward.h>


#define VGA_DESC  "vgAsynDLL"

#ifdef VGA_DLL
#	ifdef VGA_NONCLIENT_BUILD_DLL
#		define  VGA_EXPORT __declspec( dllexport )
#	else
#		define  VGA_EXPORT __declspec( dllimport )
#	endif
#else
#	define  VGA_EXPORT VGK_EXPORT
#endif




#	ifdef _DEBUG
#		define  VGA_DLL_NAME VGA_DESC##"_Debug.dll"
#		define  VGA_LIB_NAME VGA_DESC##"_Debug.lib"
#	else
#		define  VGA_DLL_NAME VGA_DESC##"_Release.dll"
#		define  VGA_LIB_NAME VGA_DESC##"_Release.lib"
#	endif




#endif // end of __VGADEFINITION_H__