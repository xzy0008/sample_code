

#ifndef __VGDEPDEFINITION_H__
#define __VGDEPDEFINITION_H__


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


#ifdef VGDEP_DLL
#	ifdef _DEBUG
#		define  VGDEP_DLL_NAME VGDEP_DESC##"_Debug.dll"
#		define  VGDEP_LIB_NAME VGDEP_DESC##"_Debug.lib"
#	else
#		define  VGDEP_DLL_NAME VGDEP_DESC##"_Release.dll"
#		define  VGDEP_LIB_NAME VGDEP_DESC##"_Release.lib"
#	endif
#else
#	define  VGDEP_DLL_NAME
#	define VGDEP_LIB_NAME
#endif


#define VGMSGBOX(A) {\
	pwnd->SetTimer(1, 150, NULL);\
	A; \
	pwnd->SetTimer(1, 15, NULL);}

//#define VG_NEW	1
#define VG_NEW	0

#endif // end of __VGDEPDEFINITION_H__
