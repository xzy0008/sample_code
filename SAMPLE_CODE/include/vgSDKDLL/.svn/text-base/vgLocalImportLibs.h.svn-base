#ifndef	_VGLOCAL_IMPORT_LIBS_H_INCLUDED_
#define	_VGLOCAL_IMPORT_LIBS_H_INCLUDED_


//!  导入额外库. 
/*!
BCG等本工程用到的额外库的导入.
*/

//////////////////////////////////////////////////////////////////////////
//
//	导入额外库
#pragma message("\t now input Extra	Libs...")



// vgLibraryDLL
#include <vgKernel/vgkForward.h>
#pragma message("  now input " VGK_LIB_NAME )
#pragma  comment(lib,VGK_LIB_NAME)

// vgCamDLL
#include <vgCam/vgcaDefinition.h>
#pragma message("  now input " VGCA_LIB_NAME )
#pragma  comment(lib,VGCA_LIB_NAME)

// vgUIControllerDLL
#include <vgUIController/vgUIControlDefinition.h>
#pragma message("\t\t\t\t now input " VGUI_LIB_NAME )
#pragma  comment(lib,VGUI_LIB_NAME)

// vgGlobalDLL
#include <vgGlobal/vgglDefinition.h>
#pragma message("\t\t\t\t now input " VGGL_LIB_NAME )
#pragma  comment(lib,VGGL_LIB_NAME)

//vgSoundDLL
#include <vgSound/vgsoundDefinition.h>
#pragma message("\t\t\t\tnow input " VGSOUND_LIB_NAME )
#pragma  comment(lib,VGSOUND_LIB_NAME)

// vgShapeDLL
#include <vgShape/vgshDefinition.h>
#pragma message("  now input " VGSH_LIB_NAME )
#pragma  comment(lib,VGSH_LIB_NAME)


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


#endif//_VGLOCAL_IMPORT_LIBS_H_INCLUDED_
