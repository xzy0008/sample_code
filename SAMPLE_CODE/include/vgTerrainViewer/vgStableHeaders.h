
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
#include <afxdisp.h>        // MFC Automation classes

#include <afxpriv.h>

#include <afxmt.h>


#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT
#include <afxdlgs.h>


//-----------------------------------------
// 新的kernel库
//------------------------------------------
#include <vgKernel/vgkForward.h>
#pragma message("  now input " VGK_LIB_NAME )
#pragma  comment(lib,VGK_LIB_NAME)

#include <vgImage/vgiDefinition.h>
#pragma message("  now input " VGI_LIB_NAME )
#pragma  comment(lib,VGI_LIB_NAME)

#include <vgTerritory/vgtDefinition.h>
#pragma message("  now input " VGT_LIB_NAME )
#pragma  comment(lib,VGT_LIB_NAME)


//------------------------------------------
// user headers
//------------------------------------------


#include <vector>
#include <map>
#include <algorithm>



//#define _BCGCBPRO_STATIC_
//#include <BCGCBProInc.h>			// BCGPro Control Bar



#include <vgKernel/vgkForward.h>

#include <vgKernel/vgkBox.h>
#include <vgKernel/vgkException.h>
#include <vgKernel/vgkCrcUtility.h>
#include <vgKernel/vgkLogManager.h>
#include <vgKernel/vgkSharePtr.h>
#include <vgKernel/vgkSingleton.h>
#include <vgKernel/vgkStreamReader.h>
#include <vgKernel/vgkStreamWriter.h>
#include <vgKernel/vgkStringUtility.h>
#include <vgKernel/vgkStringVector.h>
#include <vgKernel/vgkTrace.h>
#include <vgKernel/vgkUniqueID.h>
#include <vgKernel/vgkVec3.h>
#include <vgKernel/vgkWarning.h>


//------------------------------------------
// Import libs
//------------------------------------------
/// 导入必要的openGL库.
#pragma message("  now input OpenGL standard lib...")
#pragma   comment(lib,"opengl32.lib")
#pragma	  comment(lib,"glu32.lib")
#pragma   comment(lib,"glaux.lib")
#pragma   comment(lib ,"glew32s.lib")
#pragma   comment(lib ,"glew32.lib")

//#pragma message("  now input GLOD lib...")
//#pragma   comment(lib ,"glod.lib")
//#pragma   comment(lib ,"mt.lib")
//#pragma   comment(lib ,"vdslib.lib")
//#pragma   comment(lib ,"xbs.lib")
//#pragma   comment(lib ,"ply.lib")

///// 导入DirectSound库.
//#pragma message("  now input DirectSound lib...")
//#pragma comment(lib, "dsound.lib")
//#pragma comment(lib, "dxguid.lib")

///// 导入OpenAL库
//#pragma message("  now input OpenAL lib...")
//#pragma comment(lib, "alut.lib" )
//#pragma comment(lib, "OpenAL32.lib" )


/// 导入Lua库
#pragma message("  now input Lua lib...")
#pragma comment(lib, "LuaPlus.lib" )


#pragma message("  now input cximage(vgImageLib).lib...")
#if _DEBUG
#pragma comment( lib , "vgImageLibD.lib")
#else
#pragma comment( lib , "vgImageLib.lib")
#endif



#pragma message("  now input nvidia texture tools(vgImageTools)...")
#if _DEBUG
#pragma comment( lib, "vgImageToolsD.lib" )
#else
#pragma comment( lib, "vgImageTools.lib" )
#endif

#pragma   warning(disable:4819)
#include <FreeImage.h>
#include <FreeImagePlus.h>

#if _DEBUG
#pragma comment( lib , "FreeImaged.lib")
#pragma comment( lib , "FreeImagePlusd.lib")
#else
#pragma comment( lib , "FreeImage.lib")
#pragma comment( lib , "FreeImagePlus.lib")
#endif

// #pragma message("  now input cximage.lib...")
// #pragma comment(lib,"cximage.lib")
// #pragma comment(lib,"jbig.lib")
// #pragma comment(lib,"LibJPEG.lib")
// #pragma comment(lib,"LibPNG.lib")
//#pragma comment(lib,"libTiff.lib")
// #pragma comment(lib,"zlib.lib")
// #pragma comment(lib,"libjasper.lib")
// #pragma comment(lib,"j2k.lib")



// #pragma message("  now input nvidia texture tools...")
// #pragma comment( lib, "nvtt.lib" )
// #pragma comment( lib, "squishlib.lib" )
// #pragma comment( lib, "nvmath.lib" )
// #pragma comment( lib, "nvcore.lib" )
// #pragma comment( lib, "nvimage.lib" )

#include <gdal/gdal.h>
#include <gdal/gdal_priv.h>

//#pragma message("  now input gdal.lib...")
//#pragma  comment(lib, "gdal.lib")

#if _DEBUG
#pragma message("  now input vgGeoD.lib...")
#pragma  comment(lib, "vgGeoD.lib")
#else
#pragma message("  now input vgGeo.lib...")
#pragma  comment(lib, "vgGeo.lib")
#endif



//#if DIRECTINPUT_SUPPORT
//#pragma message("  now input dinput8.lib...")
//	#pragma comment(lib,"dinput8.lib")
//
//#pragma message("  now input dxguid.lib...")
//	#pragma  comment(lib, "dxguid.lib")
//#endif // end of DIRECTINPUT_SUPPORT


//#if CG_PROGRAM_SUPPORT
//#pragma message("  now input cg.lib...")
//#pragma  comment(lib, "cg.lib")
//#pragma message("  now input cgGL.lib...")
//#pragma  comment(lib, "cgGL.lib")
//#endif // end of CG_PROGRAM_SUPPORT



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







#endif // end of __VGSTABLEHEADER_H__