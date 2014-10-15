#ifndef	_VGCOMMON_IMPORT_LIBS_H_INCLUDED_
#define	_VGCOMMON_IMPORT_LIBS_H_INCLUDED_

//!  导入常用库. 
/*!
OpenGL和CxImage等常用库的导入.
*/



//////////////////////////////////////////////////////////////////////////
//
//	导入基本库
//
#pragma message("\t now input Basic	Libs...")

//	OpenGL库.
#	pragma message("\t\t\t\t now input OpenGL standard lib...")
//#define GLEW_STATIC 
#include <gl/glew.h>
#include <gl/wglew.h>
#include <gl/glu.h>
#include <gl/glaux.h>

#		pragma   comment(lib,"opengl32.lib")
#		pragma	  comment(lib,"glu32.lib")
#		pragma   comment(lib,"glaux.lib")
#		pragma   comment(lib ,"glew32.lib")


////	Lua库
//#pragma message("\t\t\t\t now input Lua(LuaPlus).lib...")
//#pragma comment(lib, "LuaPlus.lib" )


//	cximage 库
#	pragma message("\t\t\t\t now input cximage(vgImageLib).lib...")
#	if _DEBUG
#		pragma comment( lib , "vgImageLibD.lib")
#	else
#		pragma comment( lib , "vgImageLib.lib")
#	endif


////	DirectInput库
//#define DIRECTINPUT_VERSION 0x0800
//#include <dinput.h>
//#	pragma message("\t\t\t\t now input DirectInput libs...")
//#		pragma comment(lib,"dinput8.lib")
//#		pragma  comment(lib, "dxguid.lib")


//	CG 库
#include <Cg/cg.h>
#include <Cg/cgGL.h>

#	pragma message("\t\t\t\t now input CG libs...")
#		pragma  comment(lib, "cg.lib")
#		pragma  comment(lib, "cgGL.lib")


////	nvidia texture 库
//#	pragma message("\t\t\t\t now input nvidia texture tools(vgImageTools).lib...")
//#	if _DEBUG
//#		pragma comment( lib, "vgImageToolsD.lib" )
//#	else
//#		pragma comment( lib, "vgImageTools.lib" )
//#	endif




#endif//_VGCOMMON_IMPORT_LIBS_H_INCLUDED_
