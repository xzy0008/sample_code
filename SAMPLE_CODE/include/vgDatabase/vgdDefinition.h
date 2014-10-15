


#ifndef __VGDDEFINITION_H__
#define __VGDDEFINITION_H__


#include <vgKernel/vgkForward.h>

#define VGD_DESC  "vgDatabaseDLL"

#ifdef VGD_DLL
#	ifdef VGD_NONCLIENT_BUILD_DLL
#		define  VGD_EXPORT __declspec( dllexport )
#	else
#		define  VGD_EXPORT __declspec( dllimport )
#	endif
#else
#	define  VGD_EXPORT VGK_EXPORT
#endif



#	ifdef _DEBUG
#		define  VGD_DLL_NAME VGD_DESC##"_Debug.dll"
#		define  VGD_LIB_NAME VGD_DESC##"_Debug.lib"
#	else
#		define  VGD_DLL_NAME VGD_DESC##"_Release.dll"
#		define  VGD_LIB_NAME VGD_DESC##"_Release.lib"
#	endif


#pragma   warning(disable:4190)

	
#include <vgDatabase/vgd_api.h>

#endif // end of __VGDDEFINITION_H__