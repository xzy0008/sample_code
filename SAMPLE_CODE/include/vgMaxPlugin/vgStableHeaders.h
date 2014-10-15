
#ifndef __VGSTABLEHEADER_H__
#define __VGSTABLEHEADER_H__

#define _exit exit
//
//
//#define _CRT_SECURE_NO_WARNINGS
//
////#pragma   warning(disable:4503)
////#pragma   warning(disable:4786)
//#pragma   warning(disable:4018)
//#pragma   warning(disable:4267)
//#pragma   warning(disable:4099)
//
////------------------------------------------
//// MFC headers
////------------------------------------------
//
//#ifndef _SECURE_ATL
//#define _SECURE_ATL 1
//#endif
//
//#ifndef VC_EXTRALEAN
//#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers
//#endif
//
//// Modify the following defines if you have to target a platform prior to the ones specified below.
//// Refer to MSDN for the latest info on corresponding values for different platforms.
//#ifndef WINVER				// Allow use of features specific to Windows XP or later.
//#define WINVER 0x0501		// Change this to the appropriate value to target other versions of Windows.
//#endif
//
//#ifndef _WIN32_WINNT		// Allow use of features specific to Windows XP or later.                   
//#define _WIN32_WINNT 0x0501	// Change this to the appropriate value to target other versions of Windows.
//#endif						
//
//#ifndef _WIN32_WINDOWS		// Allow use of features specific to Windows 98 or later.
//#define _WIN32_WINDOWS 0x0410 // Change this to the appropriate value to target Windows Me or later.
//#endif
//
//#ifndef _WIN32_IE			// Allow use of features specific to IE 6.0 or later.
//#define _WIN32_IE 0x0600	// Change this to the appropriate value to target other versions of IE.
//#endif
//
//#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS	// some CString constructors will be explicit
//
//// turns off MFC's hiding of some common and often safely ignored warning messages
//#define _AFX_ALL_WARNINGS
//
//#include <afxwin.h>         // MFC core and standard components
//#include <afxext.h>         // MFC extensions
//
//
//#include <afxdisp.h>        // MFC Automation classes
//
//
//
//#ifndef _AFX_NO_OLE_SUPPORT
//#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
//#endif
//#ifndef _AFX_NO_AFXCMN_SUPPORT
//#include <afxcmn.h>			// MFC support for Windows Common Controls
//#endif // _AFX_NO_AFXCMN_SUPPORT
//
//
//#if defined _M_IX86
//#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
//#elif defined _M_IA64
//#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='ia64' publicKeyToken='6595b64144ccf1df' language='*'\"")
//#elif defined _M_X64
//#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
//#else
//#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
//#endif



//------------------------------------------
// user headers
//------------------------------------------

//#include <vgKernel/vgkForward.h>
//#include <vgKernel/vgkOpenGLSupport.h>
//#include <vgKernel/vgkTrace.h>

//
////#define _BCGCBPRO_STATIC_
//#define max(a,b)            (((a) > (b)) ? (a) : (b))
//#define min(a,b)            (((a) < (b)) ? (a) : (b))
//#include <BCGCBProInc.h>			// BCGPro Control Bar
//
//
////------------------------------------------
//// Import libs
////------------------------------------------
//
/// 导入必要的openGL库.
//#pragma message("  now input OpenGL standard lib...")
//#pragma   comment(lib,"opengl32.lib")
//#pragma	  comment(lib,"glu32.lib")
//#pragma   comment(lib,"glaux.lib")

//#pragma   comment(lib ,"glew32.lib")
//
//
//
//////------------------------------------------
////// 测试使用！！
//////------------------------------------------
////#pragma message("  now input GLOD lib...")
////#pragma   comment(lib ,"glod.lib")
////#pragma   comment(lib ,"mt.lib")
////#pragma   comment(lib ,"vdslib.lib")
////#pragma   comment(lib ,"xbs.lib")
////#pragma   comment(lib ,"ply.lib")
//
//
//#pragma message("  now input BCGControlbar(vgUserInterface).lib...")
//#if _DEBUG
//#pragma comment( lib , "vgUserInterfaceD.lib")
//#else
//#pragma comment( lib , "vgUserInterface.lib")
//#endif
//
//
//
//
////------------------------------------------
//// 新的kernel库
////------------------------------------------
//#pragma message("  now input " VGK_LIB_NAME )
//#pragma  comment(lib,VGK_LIB_NAME)
//



//------------------------------------------
// Standard Headers
//------------------------------------------
#include <Windows.h>

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


//
/////初始化OpenGL环境
////#define GLEW_STATIC 
//#include <gl/glew.h>
//#include <glod.h>
//#include <gl/wglew.h>
//#include <gl/glu.h>
//#include <gl/glaux.h>
//
//#include <Cg/cg.h>
//#include <Cg/cgGL.h>
//
//





#include "Max.h"

#include <vgKernel/vgkForward.h>


#endif // end of __VGSTABLEHEADER_H__