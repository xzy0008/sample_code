


#ifndef __VGSOUNDDEFINITION_H__
#define __VGSOUNDDEFINITION_H__

#include <vgKernel/vgkForward.h>


#define VGSOUND_DESC  "vgSoundDLL"

#ifdef VGSOU_DLL
#	ifdef VGSOU_NONCLIENT_BUILD_DLL
#		define  VGSOUND_EXPORT __declspec( dllexport )
#	else
#		define  VGSOUND_EXPORT __declspec( dllimport )
#	endif
#else
#	define  VGSOUND_EXPORT VGSOUND_EXPORT
#endif




#	ifdef _DEBUG
#		define  VGSOUND_DLL_NAME VGSOUND_DESC##"_Debug.dll"
#		define  VGSOUND_LIB_NAME VGSOUND_DESC##"_Debug.lib"
#	else
#		define  VGSOUND_DLL_NAME VGSOUND_DESC##"_Release.dll"
#		define  VGSOUND_LIB_NAME VGSOUND_DESC##"_Release.lib"
#	endif


#include <vgSound/vgsou_api.h>

	
#endif