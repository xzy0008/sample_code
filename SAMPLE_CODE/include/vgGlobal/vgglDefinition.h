


#ifndef __VGGLDEFINITION_H__
#define __VGGLDEFINITION_H__


#include <vgKernel/vgkForward.h>

#define VGGL_DESC  "vgGlobalDLL"

#ifdef VGGL_DLL
#	ifdef VGGL_NONCLIENT_BUILD_DLL
#		define  VGGL_EXPORT __declspec( dllexport )
#	else
#		define  VGGL_EXPORT __declspec( dllimport )
#	endif
#else
#	define  VGGL_EXPORT 
#endif



#	ifdef _DEBUG
#		define  VGGL_DLL_NAME VGGL_DESC##"_Debug.dll"
#		define  VGGL_LIB_NAME VGGL_DESC##"_Debug.lib"
#	else
#		define  VGGL_DLL_NAME VGGL_DESC##"_Release.dll"
#		define  VGGL_LIB_NAME VGGL_DESC##"_Release.lib"
#	endif




#endif // end of __VGGLDEFINITION_H__
