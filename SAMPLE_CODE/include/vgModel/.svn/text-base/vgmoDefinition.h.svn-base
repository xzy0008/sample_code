




#ifndef __VMD_CONFDEFINITION_H__
#define __VMD_CONFDEFINITION_H__


#include <vgKernel/vgkForward.h>


#define VGMO_DESC  "vgModelDLL"

#ifdef VGMO_DLL
#	ifdef VGMO_NONCLIENT_BUILD_DLL
#		define  VGMO_EXPORT __declspec( dllexport )
#	else
#		define  VGMO_EXPORT __declspec( dllimport )
#	endif
#else
#	define  VGMO_EXPORT VGK_EXPORT
#endif



#	ifdef _DEBUG
#		define  VGMO_DLL_NAME VGMO_DESC##"_Debug.dll"
#		define  VGMO_LIB_NAME VGMO_DESC##"_Debug.lib"
#	else
#		define  VGMO_DLL_NAME VGMO_DESC##"_Release.dll"
#		define  VGMO_LIB_NAME VGMO_DESC##"_Release.lib"
#	endif


//------------------------------------------
// Model namespace
//------------------------------------------

#define VMD_RENDER_WAY  0  // 默认的VBO渲染
//#define VMD_RENDER_WAY  1  // 使用Vertex Array渲染

#define VMD_CONF_NAME		"Model"



#endif // end of __VMD_CONFDEFINITION_H__