

#ifndef __VGMODLOCALDEFINITION_H__
#define __VGMODLOCALDEFINITION_H__


#define VGDEP_DESC "vgDeprecatedMFCDLL"

#ifdef VGDEP_DLL
#	ifdef VGDEP_NONCLIENT_BUILD_DLL
#		define  VGDEP_EXPORT __declspec( dllexport )
#	else
#		define  VGDEP_EXPORT __declspec( dllimport )
#	endif
#else
#	define  VGDEP_EXPORT
#endif


#	ifdef _DEBUG
#		define  VGDEP_DLL_NAME VGDEP_DESC##"_Debug.dll"
#		define  VGDEP_LIB_NAME VGDEP_DESC##"_Debug.lib"
#	else
#		define  VGDEP_DLL_NAME VGDEP_DESC##"_Release.dll"
#		define  VGDEP_LIB_NAME VGDEP_DESC##"_Release.lib"
#	endif





#endif // end of __VGMODLOCALDEFINITION_H__
