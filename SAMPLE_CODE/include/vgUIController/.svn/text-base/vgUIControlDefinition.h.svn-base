


#ifndef __VGUIDEFINTION_H__
#define __VGUIDEFINTION_H__

#include <vgKernel/vgkForward.h>


#define VGUI_DESC  "vgUIControllerDLL"

#ifdef VGUI_DLL
#	ifdef VGUI_NONCLIENT_BUILD_DLL
#		define  VGUI_EXPORT __declspec( dllexport )
#	else
#		define  VGUI_EXPORT __declspec( dllimport )
#	endif
#else
#	define  VGUI_EXPORT VGK_EXPORT
#endif




#	ifdef _DEBUG
#		define  VGUI_DLL_NAME VGUI_DESC##"_Debug.dll"
#		define  VGUI_LIB_NAME VGUI_DESC##"_Debug.lib"
#	else
#		define  VGUI_DLL_NAME VGUI_DESC##"_Release.dll"
#		define  VGUI_LIB_NAME VGUI_DESC##"_Release.lib"
#	endif

#include <vgUIController/vgUIControl_api.h> 

#endif // end of __VGUIDEFINTION_H__