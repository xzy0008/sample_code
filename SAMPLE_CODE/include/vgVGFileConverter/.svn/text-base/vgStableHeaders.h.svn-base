
#ifndef __VGSTABLEHEADER_H__
#define __VGSTABLEHEADER_H__


#define _CRT_SECURE_NO_WARNINGS

//#pragma   warning(disable:4503)
//#pragma   warning(disable:4786)
#pragma   warning(disable:4018)
#pragma   warning(disable:4267)

//------------------------------------------
// MFC headers
//------------------------------------------

#ifndef _SECURE_ATL
#define _SECURE_ATL 1
#endif

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers
#endif

// Modify the following defines if you have to target a platform prior to the ones specified below.
// Refer to MSDN for the latest info on corresponding values for different platforms.
#ifndef WINVER				// Allow use of features specific to Windows XP or later.
#define WINVER 0x0501		// Change this to the appropriate value to target other versions of Windows.
#endif

#ifndef _WIN32_WINNT		// Allow use of features specific to Windows XP or later.                   
#define _WIN32_WINNT 0x0501	// Change this to the appropriate value to target other versions of Windows.
#endif						

#ifndef _WIN32_WINDOWS		// Allow use of features specific to Windows 98 or later.
#define _WIN32_WINDOWS 0x0410 // Change this to the appropriate value to target Windows Me or later.
#endif

#ifndef _WIN32_IE			// Allow use of features specific to IE 6.0 or later.
#define _WIN32_IE 0x0600	// Change this to the appropriate value to target other versions of IE.
#endif

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS	// some CString constructors will be explicit

// turns off MFC's hiding of some common and often safely ignored warning messages
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions





#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT
#include <afxdlgs.h>


#include <vgCommon/vgCommonImportLibs.h>


#include <vgKernel/vgkForward.h>
#pragma message("  now input " VGK_LIB_NAME )
#pragma  comment(lib,VGK_LIB_NAME)


#include <vgMod/vgdepDefinition.h>
#pragma message("\t\t\t\t now input " VGDEP_LIB_NAME )
#pragma  comment(lib,VGDEP_LIB_NAME)


#include <vgGlobal/vgglDefinition.h>
#pragma message("\t\t\t\t now input " VGGL_LIB_NAME )
#pragma  comment(lib,VGGL_LIB_NAME)

#include <vgSolar/vgsoDefinition.h>
#pragma message("  now input " VGSO_LIB_NAME )
#pragma  comment(lib,VGSO_LIB_NAME)

#include <vgPlan/vgpDefinition.h>
#pragma message("  now input " VGP_LIB_NAME)
#pragma comment(lib, VGP_LIB_NAME)

#include <vgCam/vgcaDefinition.h>
#pragma message("  now input " VGCA_LIB_NAME )
#pragma  comment(lib,VGCA_LIB_NAME)

#include <vgShape/vgshDefinition.h>
#pragma message("  now input " VGSH_LIB_NAME )
#pragma  comment(lib,VGSH_LIB_NAME)

#include <vgFont/vgfDefinition.h>
#pragma message("  now input " VGF_LIB_NAME )
#pragma  comment(lib,VGF_LIB_NAME)

#include <vgLogo/vgloDefinition.h>
#pragma message("  now input " VGL_LIB_NAME )
#pragma  comment(lib,VGL_LIB_NAME)

#include <vgDatabase/vgdDefinition.h>
#pragma message("  now input " VGD_LIB_NAME )
#pragma  comment(lib,VGD_LIB_NAME)


#include <vgScript/vgscDefinition.h>
#pragma message("\t\t\t\t now input " VGSC_LIB_NAME )
#pragma  comment(lib,VGSC_LIB_NAME)

#include <vgUIController/vgUIControlDefinition.h>
#pragma message("  now input " VGUI_LIB_NAME )
#pragma  comment(lib,VGUI_LIB_NAME)


#include <vgSound/vgsouDefinition.h>
#pragma message("  now input " VGSOU_LIB_NAME )
#pragma  comment(lib,VGSOU_LIB_NAME)

#include <BCGCBProInc.h>			// BCGPro Control Bar
#pragma message("  now input BCGControlbar(vgUserInterface).lib...")
#if _DEBUG
#pragma comment( lib , "vgUserInterfaceD.lib")
#else
#pragma comment( lib , "vgUserInterface.lib")
#endif

//------------------------------------------
// Standard Headers
//------------------------------------------
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <cstdarg>
#include <cmath>

// STL containers
#include <vector>
#include <map>
#include <string>
#include <set>
#include <list>
#include <deque>
#include <queue>
#include <hash_map>

// STL algorithms & functions
#include <algorithm>
#include <functional>
#include <limits>

// C++ Stream stuff
#include <fstream>
#include <iostream>
#include <iomanip>
#include <sstream>


#include <string>

using namespace std;



#include <vgKernel/vgkForward.h>

#include <vgKernel/vgkBox.h>
#include <vgKernel/vgkBox3.h>
#include <vgKernel/vgkColorVal.h>
#include <vgKernel/vgkException.h>
#include <vgKernel/vgkCrcUtility.h>
#include <vgKernel/vgkLogManager.h>
#include <vgKernel/vgkMat4.h>
#include <vgKernel/vgkOpenGLSupport.h>
#include <vgKernel/vgkQuat.h>
#include <vgKernel/vgkSharePtr.h>
#include <vgKernel/vgkSingleton.h>
#include <vgKernel/vgkStreamReader.h>
#include <vgKernel/vgkStreamWriter.h>
#include <vgKernel/vgkStringUtility.h>
#include <vgKernel/vgkStringVector.h>
#include <vgKernel/vgkSystemUtility.h>
#include <vgKernel/vgkTrace.h>
#include <vgKernel/vgkUniqueID.h>
#include <vgKernel/vgkVec2.h>
#include <vgKernel/vgkVec3.h>
#include <vgKernel/vgkWarning.h>
#include <vgKernel/vgkRenderer.h>
#include <vgKernel/vgkPlane.h>
#include <vgKernel/vgkRendererObserver.h>
#include <vgKernel/vgkSharePtr.h>


// vgMod¿â
#include <vgCore/vgPrerequisites.h>
#include <vgCore/vgSharedPtr.h>
#include <vgCore/vgSingleton.h>
//#include <vgTrace.h>
#include <vgCore/vgWarning.h>
#include <vgCore/vgException.h>
#include <vgCore/vgLog.h>
#include <vgCore/vgLogManager.h>
#include <vgMath/vgfStableHeaders.h>
#include <vgTex/tvgArchive.h>
#include <vgTex/tvgArchiveFactory.h>
#include <vgTex/tvgArchiveManager.h>
#include <vgTex/tvgArchiveSaver.h>
#include <vgTex/tvgBillboard.h>
#include <vgTex/tvgBillboardSet.h>
#include <vgTex/tvgDdsImage.h>
#include <vgTex/tvgFileStreamReader.h>
#include <vgTex/tvgGpuManager.h>
#include <vgTex/tvgGpuProgram.h>
#include <vgTex/tvgGpuSupport.h>
#include <vgTex/tvgImage.h>
#include <vgTex/tvgImageFactory.h>
#include <vgTex/tvgImagePos.h>
#include <vgTex/tvgImageRect.h>
#include <vgTex/tvgImageUtil.h>
#include <vgTex/tvgImageUtil.h>
#include <vgTex/tvgOpenGLSupport.h>
#include <vgTex/tvgStreamFactory.h>
#include <vgTex/tvgStreamReader.h>
#include <vgTex/tvgStreamWriter.h>
#include <vgTex/tvgString.h>
#include <vgTex/tvgTexture.h>
#include <vgTex/tvgTextureBuilder.h>
#include <vgTex/tvgTextureManager.h>
#include <vgTex/tvgWaterGpuProgram.h>
#include <vgTex/tvgZipArchive.h>
#include <vgTex/vgConvertUtil.h>

#endif // end of __VGSTABLEHEADER_H__