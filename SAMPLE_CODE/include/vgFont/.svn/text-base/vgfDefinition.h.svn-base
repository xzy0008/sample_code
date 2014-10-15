


#ifndef __VGFDEFINTION_H__
#define __VGFDEFINTION_H__

#include <vgKernel/vgkForward.h>


#define VGF_DESC  "vgFontDLL"

#ifdef VGF_DLL
#	ifdef VGF_NONCLIENT_BUILD_DLL
#		define  VGF_EXPORT __declspec( dllexport )
#	else
#		define  VGF_EXPORT __declspec( dllimport )
#	endif
#else
#	define  VGF_EXPORT VGK_EXPORT
#endif




#	ifdef _DEBUG
#		define  VGF_DLL_NAME VGF_DESC##"_Debug.dll"
#		define  VGF_LIB_NAME VGF_DESC##"_Debug.lib"
#	else
#		define  VGF_DLL_NAME VGF_DESC##"_Release.dll"
#		define  VGF_LIB_NAME VGF_DESC##"_Release.lib"
#	endif


#include <vgFont/vgf_api.h>

#endif // end of __VGFDEFINTION_H__