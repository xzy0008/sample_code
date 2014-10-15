


#ifndef __VGEDITCOPYDEFINITION_H__
#define __VGEDITCOPYDEFINITION_H__

#include <vgKernel/vgkForward.h>


#define VGEDITCOPY_DESC  "vgEditCopyDLL"

#ifdef VGEDITCOPY_DLL
#	ifdef VGEDITCOPY_NONCLIENT_BUILD_DLL
#		define  VGEDITCOPY_EXPORT __declspec( dllexport )
#	else
#		define  VGEDITCOPY_EXPORT __declspec( dllimport )
#	endif
#else
#	define  VGEDITCOPY_EXPORT VGEDITCOPY_EXPORT
#endif




#	ifdef _DEBUG
#		define  VGEDITCOPY_DLL_NAME VGEDITCOPY_DESC##"_Debug.dll"
#		define  VGEDITCOPY_LIB_NAME VGEDITCOPY_DESC##"_Debug.lib"
#	else
#		define  VGEDITCOPY_DLL_NAME VGEDITCOPY_DESC##"_Release.dll"
#		define  VGEDITCOPY_LIB_NAME VGEDITCOPY_DESC##"_Release.lib"
#	endif


#include <vgEditCopyDLL/vgedit_api.h>

	
#endif