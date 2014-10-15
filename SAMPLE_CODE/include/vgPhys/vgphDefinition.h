


#ifndef __VGPHDEFINITION_H__
#define __VGPHDEFINITION_H__



#include <vgKernel/vgkForward.h>

#include <vgCam/vgcaDefinition.h>

//#define VGPH_DESC  "vgPhysDLL"

//#ifdef VGPH_DLL
//#	ifdef VGPH_NONCLIENT_BUILD_DLL
//#		define  VGPH_EXPORT __declspec( dllexport )
//#	else
//#		define  VGPH_EXPORT __declspec( dllimport )
//#	endif
//#else
#	define  VGPH_EXPORT VGCA_EXPORT
//#endif


//
//#ifdef VGPH_DLL
//#	ifdef _DEBUG
//#		define  VGPH_DLL_NAME VGPH_DESC##"_Debug.dll"
//#		define  VGPH_LIB_NAME VGPH_DESC##"_Debug.lib"
//#	else
//#		define  VGPH_DLL_NAME VGPH_DESC##"_Release.dll"
//#		define  VGPH_LIB_NAME VGPH_DESC##"_Release.lib"
//#	endif
//#else
//#	define  VGPH_DLL_NAME
//#	define  VGPH_LIB_NAME
//#endif




#endif // end of __VGPHDEFINITION_H__