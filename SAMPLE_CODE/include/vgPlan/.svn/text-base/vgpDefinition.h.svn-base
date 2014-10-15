


#ifndef __VGPDEFINITION_H__
#define __VGPDEFINITION_H__


#include <vgKernel/vgkForward.h>
#include <vgKernel/vgkRenderer.h>

#define VGP_DESC  "vgPlanDLL"

#ifdef VGP_DLL
#	ifdef VGP_NONCLIENT_BUILD_DLL
#		define  VGP_EXPORT __declspec( dllexport )
#	else
#		define  VGP_EXPORT __declspec( dllimport )
#	endif
#else
#	define  VGP_EXPORT VGK_EXPORT
#endif




#	ifdef _DEBUG
#		define  VGP_DLL_NAME VGP_DESC##"_Debug.dll"
#		define  VGP_LIB_NAME VGP_DESC##"_Debug.lib"
#	else
#		define  VGP_DLL_NAME VGP_DESC##"_Release.dll"
#		define  VGP_LIB_NAME VGP_DESC##"_Release.lib"
#	endif



//------------------------------------------
// Solar namespace
//------------------------------------------
#define VGP_NAME		"PLAN"


namespace vgPlan {
	// class DateTimeAndLocation;
	// class SolarManager;
}



#ifdef __cplusplus
extern "C" {
#endif

// 
// 	typedef vgKernel::Vec3* (*pfnSolarManager_getLightDirection)();
// 
// 	extern VGSO_EXPORT  vgKernel::Vec3* SolarManager_getLightDirection();
// 
// 
// 
// 	typedef bool (*pfnSolarManager_getShadowEnabled)();
// 	extern VGSO_EXPORT  bool SolarManager_getShadowEnabled();
// 
// 	typedef bool (*pfnSolarManager_turnOffShadowEffect)();
// 	extern VGSO_EXPORT  bool SolarManager_turnOffShadowEffect();
// 
// 
// 
// 
// 	typedef bool (*pfnSolarManager_turnOnShadowEffect)(vgKernel::RendererQueue* renderer_queue ,
// 		vgKernel::Vec3* new_light_dir ,
// 		bool force_to_load);
// 	extern VGSO_EXPORT  bool SolarManager_turnOnShadowEffect(vgKernel::RendererQueue* renderer_queue ,
// 		vgKernel::Vec3* new_light_dir ,
// 		bool force_to_load);
// 
// 
// 
// 	typedef bool (*pfnSolarManager_changeLightDirection)( 
// 		const vgKernel::Vec3& new_light_dir );
// 
// 	extern VGSO_EXPORT  bool SolarManager_changeLightDirection( 
// 		const vgKernel::Vec3& new_light_dir  );
// 
// 
// 	typedef bool (*pfnSolarManager_changeDateTimeAndLoc)( 
// 		vgSolar::DateTimeAndLocation* loc );
// 
// 	extern VGSO_EXPORT  bool SolarManager_changeDateTimeAndLoc( 
// 		vgSolar::DateTimeAndLocation* loc );
// 
// 
// 	typedef vgKernel::ShadowCastObjectVec* (*pfnSolarManager_getShadowCastObjects)();
// 
// 	extern VGSO_EXPORT  vgKernel::ShadowCastObjectVec* SolarManager_getShadowCastObjects();
// 
// 
// 
// 	typedef bool (*pfnSolarManager_setSolarAnalysis)( 
// 		bool enable_it );
// 
// 	extern VGSO_EXPORT  bool SolarManager_setSolarAnalysis( 
// 		bool enable_it  );
// 
// 
// 
// 	typedef bool (*pfnSolarManager_getSolarAnalysisEnable)();
// 	extern VGSO_EXPORT  bool SolarManager_getSolarAnalysisEnable();




#ifdef __cplusplus
}


#endif






#endif // end of __VGSODEFINITION_H__