


#ifndef __VGSODEFINITION_H__
#define __VGSODEFINITION_H__


#include <vgKernel/vgkForward.h>
#include <vgKernel/vgkRenderer.h>
#include <vgKernel/vgkShadowCastObject.h>



#define VGSO_DESC  "vgSolarDLL"

#ifdef VGSO_DLL
#	ifdef VGSO_NONCLIENT_BUILD_DLL
#		define  VGSO_EXPORT __declspec( dllexport )
#	else
#		define  VGSO_EXPORT __declspec( dllimport )
#	endif
#else
#	define  VGSO_EXPORT VGK_EXPORT
#endif




#	ifdef _DEBUG
#		define  VGSO_DLL_NAME VGSO_DESC##"_Debug.dll"
#		define  VGSO_LIB_NAME VGSO_DESC##"_Debug.lib"
#	else
#		define  VGSO_DLL_NAME VGSO_DESC##"_Release.dll"
#		define  VGSO_LIB_NAME VGSO_DESC##"_Release.lib"
#	endif



//------------------------------------------
// Solar namespace
//------------------------------------------
#define VGSO_NAME		"Solar"



//------------------------------------------
// Solar space
//------------------------------------------

#define VGSO_SHADOW_ENABLE		"ShadowEnable"
#define VGSO_SHADOW_ENABLE_DEFAULT		false
#define VGSO_SHADOW_ENABLE_DEFAULT_STR		"0"

#define VGSO_USECOMPUTERDATE		"UseComputerDate"
#define VGSO_USECOMPUTERDATE_DEFAULT		true
#define VGSO_USECOMPUTERDATE_DEFAULT_STR		"1"
	
#define VGSO_CURRENTYEAR		"CurrentYear"
#define VGSO_CURRENTYEAR_DEFAULT		2009
#define VGSO_CURRENTYEAR_DEFAULT_STR		"2009"

#define VGSO_CURRENTMONTH		"CurrentMonth"
#define VGSO_CURRENTMONTH_DEFAULT		6
#define VGSO_CURRENTMONTH_DEFAULT_STR		"6"

#define VGSO_CURRENTDAY		"CurrentDay"
#define VGSO_CURRENTDAY_DEFAULT		1
#define VGSO_CURRENTDAY_DEFAULT_STR		"1"

#define VGSO_CURRENTHOUR		"CurrentHour"
#define VGSO_CURRENTHOUR_DEFAULT		12
#define VGSO_CURRENTHOUR_DEFAULT_STR		"12"

#define VGSO_CURRENTMINUTE		"CurrentMinute"
#define VGSO_CURRENTMINUTE_DEFAULT		0
#define VGSO_CURRENTMINUTE_DEFAULT_STR		"0"

#define VGSO_CURRENTLATITUDE		"CurrentLatitude"
#define VGSO_CURRENTLATITUDE_DEFAULT		36
#define VGSO_CURRENTLATITUDE_DEFAULT_STR		"36"


namespace vgSolar {
	class DateTimeAndLocation;
	class SolarManager;
}



#ifdef __cplusplus
extern "C" {
#endif


	typedef vgKernel::Vec3* (*pfnSolarManager_getLightDirection)();

	extern VGSO_EXPORT  vgKernel::Vec3* SolarManager_getLightDirection();



	typedef bool (*pfnSolarManager_getShadowEnabled)();
	extern VGSO_EXPORT  bool SolarManager_getShadowEnabled();

	typedef bool (*pfnSolarManager_turnOffShadowEffect)();
	extern VGSO_EXPORT  bool SolarManager_turnOffShadowEffect();




	typedef bool (*pfnSolarManager_turnOnShadowEffect)(vgKernel::RendererQueue* renderer_queue ,
		vgKernel::Vec3* new_light_dir ,
		bool force_to_load);
	extern VGSO_EXPORT  bool SolarManager_turnOnShadowEffect(vgKernel::RendererQueue* renderer_queue ,
		vgKernel::Vec3* new_light_dir ,
		bool force_to_load);



	typedef bool (*pfnSolarManager_changeLightDirection)( 
		const vgKernel::Vec3& new_light_dir );

	extern VGSO_EXPORT  bool SolarManager_changeLightDirection( 
		const vgKernel::Vec3& new_light_dir  );


	typedef bool (*pfnSolarManager_changeDateTimeAndLoc)( 
		vgSolar::DateTimeAndLocation* loc );

	extern VGSO_EXPORT  bool SolarManager_changeDateTimeAndLoc( 
		vgSolar::DateTimeAndLocation* loc );


	typedef vgKernel::ShadowCastObjectVec* (*pfnSolarManager_getShadowCastObjects)();

	extern VGSO_EXPORT  vgKernel::ShadowCastObjectVec* SolarManager_getShadowCastObjects();



	typedef bool (*pfnSolarManager_setSolarAnalysis)( 
		bool enable_it );

	extern VGSO_EXPORT  bool SolarManager_setSolarAnalysis( 
		bool enable_it  );



	typedef bool (*pfnSolarManager_getSolarAnalysisEnable)();
	extern VGSO_EXPORT  bool SolarManager_getSolarAnalysisEnable();


	typedef void (*pfndoDailogAndChangeSolarLightDirection)();
	extern VGSO_EXPORT  void doDailogAndChangeSolarLightDirection();


	typedef void (*pfndoDailogAndSolarAnalysis)();
	extern VGSO_EXPORT  void doDailogAndSolarAnalysis();

#ifdef __cplusplus
}


#endif






#endif // end of __VGSODEFINITION_H__
