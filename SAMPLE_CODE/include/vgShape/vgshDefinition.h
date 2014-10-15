



#ifndef __VGSHDEFINITION_H__
#define __VGSHDEFINITION_H__

#include <vgKernel/vgkForward.h>





#define VGSH_DESC  "vgShapeDLL"

#ifdef VGSH_DLL
#	ifdef VGSH_NONCLIENT_BUILD_DLL
#		define  VGSH_EXPORT __declspec( dllexport )
#	else
#		define  VGSH_EXPORT __declspec( dllimport )
#	endif
#else
#	define  VGSH_EXPORT VGK_EXPORT
#endif



#	ifdef _DEBUG
#		define  VGSH_DLL_NAME VGSH_DESC##"_Debug.dll"
#		define  VGSH_LIB_NAME VGSH_DESC##"_Debug.lib"
#	else
#		define  VGSH_DLL_NAME VGSH_DESC##"_Release.dll"
#		define  VGSH_LIB_NAME VGSH_DESC##"_Release.lib"
#	endif



#define VG_SHAPE_STR		"Shape"

#define VG_SHAPE_SHPPATH_STR	"Path"

#define VG_SHAPE_SHPMAT_STR		"Matrix"

#define VG_SHAPE_STYLE_FIELD	"vg_style"




#include <vgShape/vgshp_api.h>



#endif // end of __VGSHDEFINITION_H__