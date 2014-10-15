




#ifndef __VGM_CONFDEFINITION_H__
#define __VGM_CONFDEFINITION_H__




#include <vgKernel/vgkForward.h>


#define VGM_DESC  "vgMeshDLL"

#ifdef VGM_DLL
#	ifdef VGM_NONCLIENT_BUILD_DLL
#		define  VGM_EXPORT __declspec( dllexport )
#	else
#		define  VGM_EXPORT __declspec( dllimport )
#	endif
#else
#	define  VGM_EXPORT VGK_EXPORT
#endif



#	ifdef _DEBUG
#		define  VGM_DLL_NAME VGM_DESC##"_Debug.dll"
#		define  VGM_LIB_NAME VGM_DESC##"_Debug.lib"
#	else
#		define  VGM_DLL_NAME VGM_DESC##"_Release.dll"
#		define  VGM_LIB_NAME VGM_DESC##"_Release.lib"
#	endif

	

//------------------------------------------
// Mesh namespace
//------------------------------------------
#define VGM_CONF_NAME		"Mesh"


//------------------------------------------
// Mesh space
//------------------------------------------

#define VGM_CONF_SMALLMESHREF_ENABLE		"SmallMeshReferencerEnable"
#define VGM_CONF_SMALLMESHREF_ENABLE_DEFAULT		true
#define VGM_CONF_SMALLMESHREF_ENABLE_DEFAULT_STR		"1"

#define VGM_CONF_SMALLMESHREF_LOADTHRESHOLD		"SmallMeshFileSizeThreshold"
#define VGM_CONF_SMALLMESHREF_LOADTHRESHOLD_DEFAULT		4096
#define VGM_CONF_SMALLMESHREF_LOADTHRESHOLD_DEFAULT_STR		"4096"



#endif // end of __VGM_CONFDEFINITION_H__