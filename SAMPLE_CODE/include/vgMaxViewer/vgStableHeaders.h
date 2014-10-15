#ifndef		_VGSTABLEHEADER_H_INCLUDED_
#define		_VGSTABLEHEADER_H_INCLUDED_	


#define _exit exit

#include "Max.h"

#include "resource.h"
//#include "resourceOverride.h"
#include "utilapi.h"
#include "stdmat.h"
#include "bmmlib.h"
#include "iparamb2.h"
#include "iparamm2.h"
#include "IDxMaterial.h"

#include <stdarg.h>

#include <vector>
#include <algorithm>
#include <string>
#include <cmath>

using namespace std;

typedef unsigned int uint;

#include "vgMath/vgVec3.h"
#include "vgMath/vgBox3.h"

using namespace vgMath;

//#include "resource.h"

#if _DEBUG
#define CL_CLASSID					Class_ID(0x13283ea4, 0x30e70da5)
#else
#define CL_CLASSID					Class_ID(0x89f67b4, 0xb5a2766)
#endif

#define DXMATERIAL_DYNAMIC_UI		Class_ID(0xef12512, 0x11351ed1)
#define CLASS_ID_MOD_EXPORT_JPG_DEBUG Class_ID(0x6469051e, 0x43806589);//mod_d_jpg
#define CLASS_ID_MOD_MAXPLUGIN_JPG_DEBUG Class_ID(0x934305c, 0x5d4b0c7c);//vgMaxPlugin(Debug)
#define CLASS_ID_MOD_MAXPLUGIN_JPG_RELEASE	Class_ID(0x5967053d, 0x6bd52070);//vgMaxPlugin(Release)

//Class_ID(0x9ae2532, 0x75072e4)//Class_ID(0x57ab2b60, 0x590572f5)
// two handy macros to set cursors for busy or normal operation
#define UI_MAKEBUSY			SetCursor(LoadCursor(NULL, IDC_WAIT));
#define UI_MAKEFREE			SetCursor(LoadCursor(NULL, IDC_ARROW));

#define REGISTER_ROOT			HKEY_CURRENT_USER

// 导出选项
enum	E_Export_Option
{
	FILTER_SELECTED		= SCENE_EXPORT_SELECTED,
	PROMPT_SETTING		= SCENE_EXPORT_SELECTED << 1,
	PROMPT_RESULT		= SCENE_EXPORT_SELECTED << 2,
	PROMPT_WARNING		= SCENE_EXPORT_SELECTED << 3,
	EXPORT_OPTION_COUNT
};
#endif//	_VGSTABLEHEADER_H_INCLUDED_	