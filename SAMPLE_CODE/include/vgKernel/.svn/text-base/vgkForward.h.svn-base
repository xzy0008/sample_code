



#ifndef __VGKFORWARD_H__
#define __VGKFORWARD_H__


#ifdef VGLIBRARY_MFCDLL
#define VGK_DESC  "vgLibraryMFCDLL"
#else
#define VGK_DESC  "vgLibraryDLL"
#endif


#ifdef VGK_DLL
#	ifdef VGK_NONCLIENT_BUILD_DLL
#		define  VGK_EXPORT __declspec( dllexport )
#	else
#		define  VGK_EXPORT __declspec( dllimport )
#	endif
#else
#	define  VGK_EXPORT
#endif


#	ifdef _DEBUG
#		define  VGK_DLL_NAME VGK_DESC##"_Debug.dll"
#		define  VGK_LIB_NAME VGK_DESC##"_Debug.lib"
#	else
#		define  VGK_DLL_NAME VGK_DESC##"_Release.dll"
#		define  VGK_LIB_NAME VGK_DESC##"_Release.lib"
#	endif



#ifdef VGK_DLL
#include <vgKernel/vgkDynamicLibraryUtility.h>
#endif


#ifdef VGK_USE_ENGLISH
	#define VGK_LANG_ENG		1
	#define VGK_LANG_CHS		0
#else
	#define VGK_LANG_ENG		0
	#define VGK_LANG_CHS		1
#endif



//------------------------------------------
// 定义lod的级别,包括模型数据和纹理
// 2为最精细一级.
// 0为最粗糙一级.
//------------------------------------------
#define VGLOD_N	3
#define VGLOD_COARSE		0
#define VGLOD_CLEAR		(VGLOD_N - 1)

#define VGLOD_SQU_DIST_NEAR	(500.0f*500.0f)
#define VGLOD_SQU_DIST_FAR		(1000.0f*1000.0f)


#define VG_NULL_TEXTURE_ID		0

#include <cmath>
#include <cassert>
#include <vector>
#include <map>
#include <string>
#include <deque>
#include <algorithm>

#include <tchar.h>

#include <atltypes.h>

#ifndef VGK_NO_OPENGL
#include <gl/glew.h>
#include <gl/wglew.h>
#endif


typedef std::string			String;
typedef unsigned char		uchar;
typedef unsigned int		uint;

typedef unsigned __int64		uint64;


#include <vgKernel/vgkStringVector.h>
	


namespace vgKernel {
	class Box3;
	class Box;
	class ColorVal;
	class CoordSystem;
	class CrcUtility;
	class ImagePos;
	class ImageRect;
	class ImageSize;
	class InputHandler;
	class InputSystem;
	class Intersector;
	class LogManager;
	class Mat4;
	class Math;
	class OpenGLSupport;
	class Plane;
	class PointInPolygon;
	class Polygon2D;
	class Quat;
	class Ray;
	class RendererHolder;
	class RendererHolderManager;
	class RendererManager;
	class RgbaQuad;
	class Segment3;
	class SelectManager;
	class SingletonInstance;
	class SingletonManager;
	class StandardOutput;
	class StringUtility;
	class SystemUtility;
	class Triangle3;
	class UniqueID;
	class UniqueIDFactory;
	class Vec2;
	class Vec3;
	class Warning;
	class WriteUtility;

	class Plugin;
	class PluginManager;

	class Renderer;

}



#ifdef __cplusplus
extern "C" {
#endif


	typedef void* vgkVec3H;
	typedef void* vgkBox3H;


#ifdef __cplusplus
}
#endif


#endif // end of __VGKFORWARD_H__