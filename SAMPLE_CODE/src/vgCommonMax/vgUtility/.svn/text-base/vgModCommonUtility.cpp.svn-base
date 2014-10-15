
/**********************************************************************
*<
vgModelExp.cpp:	.MOD格式 场景导出插件接口及功能设计

主要内容是：
1、DLL入口DLLMain函数实现
2、插件的5个接口函数实现
3、插件功能类class vgModExportor 定义及其实现
4、插件描述类class vgModClassDesc 定义及其实现
*>	
**********************************************************************/
#include "vgStableHeaders.h"
#include "vgUtility/vgModCommonUtility.h"


HINSTANCE vgModUtility::hInstance = NULL; 


//----------------------------------------------------------------------------
TCHAR* vgModUtility::GetString( int id )
{
	static TCHAR stBuf[SCHAR_MAX];
	if (hInstance)
		return LoadString(hInstance, id, stBuf, SCHAR_MAX) ? stBuf : NULL;
	return NULL;
}

//----------------------------------------------------------------------------
//void vgModUtility::MessageBox( int s1, int s2 )
//{
//	TSTR str1(GetString(s1));
//	TSTR str2(GetString(s2));
//	::MessageBox(GetActiveWindow(), str1.data(), str2.data(), MB_OK);
//}

//----------------------------------------------------------------------------
int vgModUtility::MessageBox( int s1, int s2, int option /*= MB_OK*/ )
{
	string str1(GetString(s1));
	string str2(GetString(s2));
	return ::MessageBox(GetActiveWindow(), str1.c_str(), str2.c_str(), option);
}

//----------------------------------------------------------------------------
void vgModUtility::MessageBox( string msg )
{
	::MessageBox(GetActiveWindow(), msg.c_str(), "提示", MB_OK);
}
//----------------------------------------------------------------------------
//int vgModUtility::Alert( int s1, int s2 /*= IDS_TH_VGMODEXP*/, int option /*= MB_OK*/ )
//{
//	return MessageBox(s1, s2, option);
//
//}

//----------------------------------------------------------------------------
DWORD WINAPI vgModUtility::fn( LPVOID arg )
{
	return	0;
}

#if	IMPORT_MAX_LIB
//----------------------------------------------------------------------------
BOOL vgModUtility::UVVertEqual( UVVert tv0, UVVert tv1 )
{
	return (tv0.x == tv1.x &&
		tv0.y == tv1.y &&
		tv0.y == tv1.y);
}
#endif

//----------------------------------------------------------------------------
BOOL	vgModUtility::ApproxEqual(float a, float b)
{
	float eps = float(1.0e-5);
	float d = (float) fabs(a-b);
	return d < eps;
}



//----------------------------------------------------------------------------
