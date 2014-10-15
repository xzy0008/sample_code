


#ifndef __VGNOISEDEFINITION_H__
#define __VGNOISEDEFINITION_H__

#include <vgKernel/vgkForward.h>




#define VGCHAN_DESC  "vgNoiseDLL"

#ifdef VGNOISE_DLL
#	ifdef VGNOISE_NONCLIENT_BUILD_DLL
#		define  VGNOISE_EXPORT __declspec( dllexport )
#	else
#		define  VGNOISE_EXPORT __declspec( dllimport )
#	endif
#else
#	define  VGNOISE_EXPORT VGK_EXPORT
#endif




#	ifdef _DEBUG
#		define  VGNOISE_DLL_NAME VGCHAN_DESC##"_Debug.dll"
#		define  VGNOISE_LIB_NAME VGCHAN_DESC##"_Debug.lib"
#	else
#		define  VGNOISE_DLL_NAME VGCHAN_DESC##"_Release.dll"
#		define  VGNOISE_LIB_NAME VGCHAN_DESC##"_Release.lib"
#	endif


#endif // end of __VGNOISEDEFINITION_H__