#ifndef __VODEFINITION_H__
#define __VODEFINITION_H__
//definition of vrOceanDLL export defines -- livenson 20091110

#define VO_DESC  "vgOceanDLL"

#ifdef VO_DLL
#	ifdef VO_NONCLIENT_BUILD_DLL
#		define  VO_EXPORT __declspec( dllexport )
#	else
#		define  VO_EXPORT __declspec( dllimport )
#	endif
#else
#   define VO_EXPORT VGK_EXPORT
#endif



#	ifdef _DEBUG
#		define  VO_DLL_NAME VO_DESC##"_Debug.dll"
#		define  VO_LIB_NAME VO_DESC##"_Debug.lib"
#	else
#		define  VO_DLL_NAME VO_DESC##"_Release.dll"
#		define  VO_LIB_NAME VO_DESC##"_Release.lib"
#	endif


#endif // end 