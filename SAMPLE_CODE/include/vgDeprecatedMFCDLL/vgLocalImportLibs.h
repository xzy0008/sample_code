#ifndef	_VGLOCAL_IMPORT_LIBS_H_INCLUDED_
#define	_VGLOCAL_IMPORT_LIBS_H_INCLUDED_

//!  导入额外库. 
/*!
BCG等本工程用到的额外库的导入.
*/




#pragma warning (disable: 4996) 
#pragma warning (disable: 4005) 
#pragma warning (disable: 4995) 

//////////////////////////////////////////////////////////////////////////
//
//	导入额外库
//
#pragma message("\t now input Extra	Libs...")


//////////////////////////////////////////////////////////////////////////
//	BCG 库
#define max(a,b)            (((a) > (b)) ? (a) : (b))
#define min(a,b)            (((a) < (b)) ? (a) : (b))

#include <BCGCBProInc.h>			// BCGPro Control Bar

#pragma message("\t\t\t\t now input BCGControlbar(vgUserInterface).lib...")
#if _DEBUG
#pragma comment( lib , "vgUserInterfaceD.lib")
#else
#pragma comment( lib , "vgUserInterface.lib")
#endif


// GDAL库
#pragma message("\t\t\t\t now input gdal.lib" )
//#pragma  comment(lib, "gdal.lib")
#if _DEBUG
#pragma  comment(lib, "gdal_i.lib")
#else
#pragma  comment(lib, "gdal_i.lib")
#endif


/// 导入DirectSound库.
#pragma message("  now input DirectSound lib...")
#pragma comment(lib, "dsound.lib")
#pragma comment(lib, "dxguid.lib")

/// 导入OpenAL库
#pragma message("  now input OpenAL lib...")
#pragma comment(lib, "alut.lib" )
#pragma comment(lib, "OpenAL32.lib" )

// CxImage 库
#pragma message("  now input cximage(vgImageLib).lib...")
#if _DEBUG
#pragma comment( lib , "vgImageLibD.lib")
#else
#pragma comment( lib , "vgImageLib.lib")
#endif

// Direct Input 库
#include <dinput.h>
#pragma message("  now input dinput8.lib...")
#pragma comment(lib,"dinput8.lib")

#pragma message("  now input dxguid.lib...")
#pragma  comment(lib, "dxguid.lib")





//------------------------------------------
// 新的kernel库
//------------------------------------------
#include <vgKernel/vgkForward.h>
#pragma message("  now input " VGK_LIB_NAME )
#pragma  comment(lib,VGK_LIB_NAME)

// vgAsynDLL库
#include <vgAsyn/vgaDefinition.h>
#pragma message("  now input " VGA_LIB_NAME )
#pragma  comment(lib,VGA_LIB_NAME)

// vgCamDLL库
#include <vgCam/vgcaDefinition.h>
#pragma message("  now input " VGCA_LIB_NAME )
#pragma  comment(lib,VGCA_LIB_NAME)

// vgImageDLL库
#include <vgImage/vgiDefinition.h>
#pragma message("  now input " VGI_LIB_NAME )
#pragma  comment(lib,VGI_LIB_NAME)

// vgMeshDLL库
#include <vgMesh/vgmDefinition.h>
#pragma message("  now input " VGM_LIB_NAME )
#pragma  comment(lib,VGM_LIB_NAME)

// vgFontDLL库
#include <vgFont/vgfDefinition.h>
#pragma message("  now input " VGF_LIB_NAME )
#pragma  comment(lib,VGF_LIB_NAME)

// vgDatabaseDLL库
#include <vgDatabase/vgdDefinition.h>
#pragma message("  now input " VGD_LIB_NAME )
#pragma  comment(lib,VGD_LIB_NAME)

// vgUIControllerDLL库
#include <vgUIController/vgUIControlDefinition.h>
#pragma message("  now input " VGUI_LIB_NAME )
#pragma  comment(lib,VGUI_LIB_NAME)


#endif//_VGLOCAL_IMPORT_LIBS_H_INCLUDED_
