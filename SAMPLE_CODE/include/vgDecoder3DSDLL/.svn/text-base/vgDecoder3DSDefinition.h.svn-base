


#ifndef __VGDECODER3DSDEFINITION_H__
#define __VGDECODER3DSDEFINITION_H__

#include <vgKernel/vgkForward.h>


#define VGDECODER3DS_DESC  "vgDecoder3DSDLL"

#ifdef VGDECODER3DS_DLL
#	ifdef VGDECODER3DS_NONCLIENT_BUILD_DLL
#		define  VGDECODER3DS_EXPORT __declspec( dllexport )
#	else
#		define  VGDECODER3DS_EXPORT __declspec( dllimport )
#	endif
#else
#	define  VGDECODER3DS_EXPORT VGDECODER3DS_EXPORT
#endif




#	ifdef _DEBUG
#		define  VGDECODER3DS_DLL_NAME VGDECODER3DS_DESC##"_Debug.dll"
#		define  VGDECODER3DS_LIB_NAME VGDECODER3DS_DESC##"_Debug.lib"
#	else
#		define  VGDECODER3DS_DLL_NAME VGDECODER3DS_DESC##"_Release.dll"
#		define  VGDECODER3DS_LIB_NAME VGDECODER3DS_DESC##"_Release.lib"
#	endif


#include <vgDECODER3DSDLL/vgDecoder3DS_api.h>

	
#endif