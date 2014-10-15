


#ifndef __VGGISDEFINTION_H__
#define __VGGISDEFINTION_H__

#include <vgKernel/vgkForward.h>


#define VGG_DESC  "vgGisDLL"

#ifdef VGG_DLL
#	ifdef VGG_NONCLIENT_BUILD_DLL
#		define  VGG_EXPORT __declspec( dllexport )
#	else
#		define  VGG_EXPORT __declspec( dllimport )
#	endif
#else
#	define  VGG_EXPORT VGK_EXPORT
#endif




#	ifdef _DEBUG
#		define  VGG_DLL_NAME VGG_DESC##"_Debug.dll"
#		define  VGG_LIB_NAME VGG_DESC##"_Debug.lib"
#	else
#		define  VGG_DLL_NAME VGG_DESC##"_Release.dll"
#		define  VGG_LIB_NAME VGG_DESC##"_Release.lib"
#	endif

namespace	vgGIS3D
{
	enum EGisState
	{	
		GisNone,

		GisCoordinate,
		GisDistance,
		GisArea,

		GisVolume,GisWaterArea,

		GisWaterVolume,GisSoilVolume,GisP2PVisibility,GisSection,
		GisAddVertexString,GisEditVertexString,GisTerLeveling,

		GisHideVec,
		GisSelectRoutePoint,
		GisEidtRoute,

		GisContourVtr,

		GisBuffer,
		GisBufferShape,
		GisBufferModel,

		GisVer_Hor_Slope,
		GisControlHeight,
		GisFaecher
	};
}

#include <vgGis/vggis_api.h> 

#endif // end of __VGGISDEFINTION_H__
