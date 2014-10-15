


#ifndef __VGVIDEFINITION_H__
#define __VGVIDEFINITION_H__



#include <vgKernel/vgkForward.h>



#define VGVI_DESC  "vgVisualEffectsDLL"

#ifdef VGVI_DLL
#	ifdef VGVI_NONCLIENT_BUILD_DLL
#		define  VGVI_EXPORT __declspec( dllexport )
#	else
#		define  VGVI_EXPORT __declspec( dllimport )
#	endif
#else
#	define  VGVI_EXPORT VGK_EXPORT
#endif




#	ifdef _DEBUG
#		define  VGVI_DLL_NAME VGVI_DESC##"_Debug.dll"
#		define  VGVI_LIB_NAME VGVI_DESC##"_Debug.lib"
#	else
#		define  VGVI_DLL_NAME VGVI_DESC##"_Release.dll"
#		define  VGVI_LIB_NAME VGVI_DESC##"_Release.lib"
#	endif



//------------------------------------------
// visual Effects namespace
//------------------------------------------
#define VG_VISUALEFFECTS_STR		"VisualEffects"


//------------------------------------------
// fog space
//------------------------------------------
#define VG_FOG_NAME_ENABLE		"fogEnabled"
#define VG_FOG_DEFAULT_ENABLE		false
#define VG_FOG_DEFAULT_ENABLE_STR		"0"

#define VG_FOG_NAME_START			"fogStart"
#define VG_FOG_DEFAULT_START			0.1
#define VG_FOG_DEFAULT_START_STR	"0.1"

#define VG_FOG_NAME_END				"fogEnd"
#define VG_FOG_DEFAULT_END			5000.0
#define VG_FOG_DEFAULT_END_STR		"5000.0"

#define VG_FOG_NAME_DENSITY		"fogDensity"
#define VG_FOG_DEFAULT_DENSITY		0.35
#define VG_FOG_DEFAULT_DENSITY_STR	"0.35"

#define VG_FOG_NAME_MODE			"fogMode"
#define VG_FOG_DEFAULT_MODE		FOG_MOD_LINEAR
#define VG_FOG_DEFAULT_MODE_STR		"0"

#define VG_FOG_NAME_COLOR_R			"fogColorR"
#define VG_FOG_DEFAULT_COLOR_R		0.8
#define VG_FOG_DEFAULT_COLOR_R_STR		"0.8"
	
#define VG_FOG_NAME_COLOR_G			"fogColorG"
#define VG_FOG_DEFAULT_COLOR_G		0.8
#define VG_FOG_DEFAULT_COLOR_G_STR		"0.8"

#define VG_FOG_NAME_COLOR_B			"fogColorB"
#define VG_FOG_DEFAULT_COLOR_B		0.75
#define VG_FOG_DEFAULT_COLOR_B_STR		"0.75"

#define VG_FOG_NAME_COLOR_A			"fogColorA"
#define VG_FOG_DEFAULT_COLOR_A		0.9
#define VG_FOG_DEFAULT_COLOR_A_STR		"0.9"


#endif // end of __VGVIDEFINITION_H__