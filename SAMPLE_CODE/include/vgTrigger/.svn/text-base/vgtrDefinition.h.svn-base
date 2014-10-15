


#ifndef __VGTRIGGERDEFINITION_H__
#define __VGTRIGGERDEFINITION_H__

#include <vgKernel/vgkForward.h>




#define VGTRI_DESC  "vgTriggerDLL"

#ifdef VGTRI_DLL
#	ifdef VGTRI_NONCLIENT_BUILD_DLL
#		define  VGTRI_EXPORT __declspec( dllexport )
#	else
#		define  VGTRI_EXPORT __declspec( dllimport )
#	endif
#else
#	define  VGTRI_EXPORT VGK_EXPORT
#endif




#	ifdef _DEBUG
#		define  VGTRI_DLL_NAME VGTRI_DESC##"_Debug.dll"
#		define  VGTRI_LIB_NAME VGTRI_DESC##"_Debug.lib"
#	else
#		define  VGTRI_DLL_NAME VGTRI_DESC##"_Release.dll"
#		define  VGTRI_LIB_NAME VGTRI_DESC##"_Release.lib"
#	endif


#ifdef __cplusplus
extern "C" {
#endif

	typedef bool (*pfnTriggerManager_readFromVgFile)(string savePath);
	extern VGTRI_EXPORT bool TriggerManager_readFromVgFile(string savePath);

	typedef bool (*pfnTriggerManager_writeToVgFile)(string savePath);
	extern VGTRI_EXPORT bool TriggerManager_writeToVgFile(string savePath);

#ifdef __cplusplus
}
#endif  

#endif // end of __VGTRIGGERDEFINITION_H__