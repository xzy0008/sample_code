
#ifndef __VGSTABLEHEADER_H__
#define __VGSTABLEHEADER_H__



#include <vgGlobalDefinition.h>



#define _CRT_SECURE_NO_WARNINGS

//#pragma   warning(disable:4503)
//#pragma   warning(disable:4786)
#pragma   warning(disable:4018)
#pragma   warning(disable:4267)
#pragma   warning(disable:4099)

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



#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT


#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_IA64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='ia64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif



//------------------------------------------
// user headers
//------------------------------------------

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


#define BOOST_PYTHON_STATIC_LIB
#define BOOST_DEBUG_PYTHON
#include <boost/python.hpp>
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>
#include <boost/python/suite/indexing/map_indexing_suite.hpp>

#include <boost/python/suite/indexing_suite/container_suite.hpp>
#include <boost/python/suite/indexing_suite/vector.hpp>
#include <boost/python/suite/indexing_suite/map.hpp>
#include <boost/python/suite/indexing_suite/deque.hpp>
#include <boost/python/class.hpp>
#include <boost/python/module.hpp>


//#define _BCGCBPRO_STATIC_
#define max(a,b)            (((a) > (b)) ? (a) : (b))
#define min(a,b)            (((a) < (b)) ? (a) : (b))
#include <BCGCBProInc.h>			// BCGPro Control Bar


//#pragma warning (disable : 4146)
//
//#import "c:\Program Files\Common Files\system\ado\msadox.dll"
//
//#import "c:\Program Files\Common Files\System\ADO\msado15.dll" rename ("EOF", "ADOEOF")
//using namespace ADODB;
//
//#pragma warning (default : 4146)



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


//#include <vgCam/vgcaCamManager.h>
//#include <vgCam/vgcaCamFacade.h>

#include <vgAsyn/vgaIoServer.h>
#include <vgAsyn/vgaFileInfo.h>
#include <vgAsyn/vgaIoRequest.h>

#include <vgGlobal/vggGlobalConsole.h>
#include <vgGlobal/vggGlobalFacade.h>
#include <vgGlobal/vggSystemFacade.h>

#include <vgTerritory/vgtTerrainManager.h>
#include <vgTerritory/vgtElevationManager.h>

//------------------------------------------
// Import libs
//------------------------------------------
/// 导入必要的openGL库.
//#pragma message("  now input OpenGL standard lib...")
//#pragma   comment(lib,"opengl32.lib")
//#pragma	  comment(lib,"glu32.lib")
//#pragma   comment(lib,"glaux.lib")
//#pragma   comment(lib ,"glew32s.lib")
//
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
//#pragma message("  now input Lua lib...")
//#pragma comment(lib, "LuaPlus.lib" )

//
//
//#pragma message("  now input cximage.lib...")
//#pragma comment(lib,"cximage.lib")
//#pragma comment(lib,"jbig.lib")
//#pragma comment(lib,"LibJPEG.lib")
//#pragma comment(lib,"LibPNG.lib")
//#pragma comment(lib,"libTiff.lib")
//#pragma comment(lib,"zlib.lib")
//#pragma comment(lib,"libjasper.lib")
//#pragma comment(lib,"j2k.lib")



//#pragma message("  now input ImageLibrary.lib...")
//#pragma comment(lib,"ImageLibrary.lib")
//#pragma comment(lib,"squish.lib")
//
//
//#pragma message("  now input dinput8.lib...")
//	#pragma comment(lib,"dinput8.lib")
//
//#pragma message("  now input dxguid.lib...")
//	#pragma  comment(lib, "dxguid.lib")
//
//
//#pragma message("  now input cg.lib...")
//#pragma  comment(lib, "cg.lib")
//#pragma message("  now input cgGL.lib...")
//#pragma  comment(lib, "cgGL.lib")



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

///初始化OpenGL环境
//#define GLEW_STATIC 
#include <gl/glew.h>
#include <glod.h>
#include <gl/wglew.h>
#include <gl/glu.h>
#include <gl/glaux.h>

#include <Cg/cg.h>
#include <Cg/cgGL.h>





#define DIRECTINPUT_VERSION 0x0800
/// 初始化DirectX相关文件
#include <dinput.h>







//------------------------------------------
// vgCore headers
//------------------------------------------

#include <vgPrerequisites.h>
#include <vgSharedPtr.h>
#include <vgSingleton.h>
#include <vgTrace.h>
#include <vgWarning.h>
#include <vgStandardHeaders.h>
#include <vgException.h>
#include <vgLog.h>
#include <vgLogManager.h>
#include <vgMath/vgfStableHeaders.h>
//#include <vgRoot.h>

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