#ifndef	_VGLOCAL_IMPORT_LIBS_H_INCLUDED_
#define	_VGLOCAL_IMPORT_LIBS_H_INCLUDED_

#include <vgKernel/vgkForward.h>
#include <vgLocalDefines.h>
//!  导入额外库. 
/*!
BCG等本工程用到的额外库的导入.
*/

//////////////////////////////////////////////////////////////////////////
//
//	导入额外库
#pragma message("\t now input Extra	Libs...")


//------------------------------------------
// 新的kernel&core库
//------------------------------------------
#include <vgMod/vgdepDefinition.h>
#pragma message("\t\t\t\t now input " VGDEP_LIB_NAME )
#pragma  comment(lib,VGDEP_LIB_NAME)

#include <vgKernel/vgkForward.h>
#pragma message("  now input " VGK_LIB_NAME )
#pragma  comment(lib,VGK_LIB_NAME)

#include <vgAsyn/vgaDefinition.h>
#pragma message("  now input " VGA_LIB_NAME )
#pragma  comment(lib,VGA_LIB_NAME)

#include <vgCam/vgcaDefinition.h>
#pragma message("  now input " VGCA_LIB_NAME )
#pragma  comment(lib,VGCA_LIB_NAME)

#include <vgImage/vgiDefinition.h>
#pragma message("  now input " VGI_LIB_NAME )
#pragma  comment(lib,VGI_LIB_NAME)

#include <vgModel/vgmoDefinition.h>
#pragma message("  now input " VGMO_LIB_NAME )
#pragma  comment(lib,VGMO_LIB_NAME)

#include <vgMesh/vgmDefinition.h>
#pragma message("  now input " VGM_LIB_NAME )
#pragma  comment(lib,VGM_LIB_NAME)

//#include <vgTerritory/vgtDefinition.h>
//#pragma message("  now input " VGT_LIB_NAME )
//#pragma  comment(lib,VGT_LIB_NAME)

#include <vgTree/vgtrDefinition.h>
#pragma message("  now input " VGTR_LIB_NAME )
#pragma  comment(lib,VGTR_LIB_NAME)

//#include <vgSolar/vgsoDefinition.h>
//#pragma message("  now input " VGSO_LIB_NAME )
//#pragma  comment(lib,VGSO_LIB_NAME)

#include <vgVisualEffects/vgviDefinition.h>
#pragma message("  now input " VGVI_LIB_NAME )
#pragma  comment(lib,VGVI_LIB_NAME)
#if 0
#include <vgShape/vgshDefinition.h>
#pragma message("  now input " VGSH_LIB_NAME )
#pragma  comment(lib,VGSH_LIB_NAME)
#endif
#include <vgOcc/vgocDefinition.h>
#pragma message("  now input " VGOC_LIB_NAME )
#pragma  comment(lib,VGOC_LIB_NAME)

#include <vgFont/vgfDefinition.h>
#pragma message("  now input " VGF_LIB_NAME )
#pragma  comment(lib,VGF_LIB_NAME)

#include <vgLogo/vgloDefinition.h>
#pragma message("  now input " VGL_LIB_NAME )
#pragma  comment(lib,VGL_LIB_NAME)

#include <vgDatabase/vgdDefinition.h>
#pragma message("  now input " VGD_LIB_NAME )
#pragma  comment(lib,VGD_LIB_NAME)

//#include <vgSound/vgSoundDefinition.h>
//#pragma message("  now input " VGSOU_LIB_NAME )
//#pragma  comment(lib,VGSOU_LIB_NAME)


//#include <vgGis/vggisDefinition.h>
//#pragma message("\t\t\t\t now input " VGG_LIB_NAME )
//#pragma  comment(lib,VGG_LIB_NAME) 


#include <vgScript/vgscDefinition.h>
#pragma message("\t\t\t\t now input " VGSC_LIB_NAME )
#pragma  comment(lib,VGSC_LIB_NAME)


//#include <vgPlugin/vgplDefinition.h>
//#pragma message("\t\t\t\t now input " VGPL_LIB_NAME )
//#pragma  comment(lib,VGPL_LIB_NAME)

#include <vgUIController/vgUIControlDefinition.h>
#pragma message("  now input " VGUI_LIB_NAME )
#pragma  comment(lib,VGUI_LIB_NAME)



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
//#pragma  comment(lib, "gdal.lib")
#pragma message("\t\t\t\t now input gdals(vgGeo)...")
#if _DEBUG
#pragma  comment(lib, "gdal_i.lib")
#else
#pragma  comment(lib, "gdal_i.lib")
#endif


#endif//_VGLOCAL_IMPORT_LIBS_H_INCLUDED_
