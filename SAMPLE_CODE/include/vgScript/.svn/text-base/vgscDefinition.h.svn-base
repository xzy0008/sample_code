


#ifndef __VGSCDEFINITION_H__
#define __VGSCDEFINITION_H__


#define VGSC_DESC  "vgScriptMFCDLL"

#ifdef VGSC_DLL
#	ifdef VGSC_NONCLIENT_BUILD_DLL
#		define  VGSC_EXPORT __declspec( dllexport )
#	else
#		define  VGSC_EXPORT __declspec( dllimport )
#	endif
#else
#	define  VGSC_EXPORT
#endif



#	ifdef _DEBUG
#		define  VGSC_DLL_NAME VGSC_DESC##"_Debug.dll"
#		define  VGSC_LIB_NAME VGSC_DESC##"_Debug.lib"
#	else
#		define  VGSC_DLL_NAME VGSC_DESC##"_Release.dll"
#		define  VGSC_LIB_NAME VGSC_DESC##"_Release.lib"
#	endif


#define VGSC_SECTION	"Script"

#define VGSC_USER_INIT 	"userInit"
	
#define VGSC_USER_UNINIT  "userUninit"

#define VGSC_USER_RENDER_BEGIN	"userRenderBegin"

#define VGSC_USER_RENDER	"userRender"

#define VGSC_USER_RENDER_END 	"userRenderEnd"


#define VGSC_USER_SAVE_PROJ 	"userSaveProj"
#define VGSC_USER_READ_PROJ 	"userReadProj"

#define VGSC_COMPILE_NAME	"vgScriptCompile"


#define VGSC_STATIC_FUNC_DECLARE(classname,staticname)  \
	classname _f_##classname##_get_static_func_##staticname() {\
	return classname::staticname; }


#define VGSC_STATIC_FUNC_PTR(classname,staticname)  \
	_f_##classname##_get_static_func_##staticname

	
#define VGARG boost::python::arg



typedef void (*ScriptInitializeFunc)(void); 


#ifdef __cplusplus
extern "C" {
#endif


	typedef bool	(*pfnScriptManager_runScriptString)(const String& script_str );
	extern VGSC_EXPORT  bool ScriptManager_runScriptString(const String& script_str );


	typedef void	(*pfnScriptManager_createMultiSelectDailogAndRunScript)();
	extern VGSC_EXPORT  void ScriptManager_createMultiSelectDailogAndRunScript();



	typedef bool	(*pfnScriptManager_addUserScriptFunc)(ScriptInitializeFunc user_func );
	extern VGSC_EXPORT  bool ScriptManager_addUserScriptFunc(ScriptInitializeFunc user_func );



#ifdef __cplusplus
}
#endif




#endif // end of __VGSCDEFINITION_H__