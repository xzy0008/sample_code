

#ifndef _VGMODCOMMONUTILITY_H_INCLUDED_
#define _VGMODCOMMONUTILITY_H_INCLUDED_
/**********************************************************************
*<
vgModUtility.h:	 全局工具
主要内容是： 全局变量、全局函数、文件类的声明及定义
*>	
**********************************************************************/

#include "vgStableHeaders.h"

//////////////////////////////////////////////////////////////////////////
//		全局变量	//////////////////////////////////////////////////////
class vgModUtility
{
public:
	static HINSTANCE hInstance;

public:
	static	HINSTANCE	getInstance()	{	return	hInstance;}

	static	void		setInstance(HINSTANCE inst)	{	hInstance = inst;}

	//////////////////////////////////////////////////////////////////////////
	//   全局函数  ///////////////////////////////////////////////////////
	static TCHAR* GetString(int id);

	//static void MessageBox(int s1, int s2);
	static void MessageBox(string msg);

	static int MessageBox(int s1, int s2, int option = MB_OK);

	//static int Alert(int s1, int s2 = IDS_TH_VGMODEXP, int option = MB_OK);


	static DWORD WINAPI fn(LPVOID arg);

#if	IMPORT_MAX_LIB
	static BOOL	UVVertEqual(UVVert tv0, UVVert tv1) ;
#endif

	static BOOL		ApproxEqual(float a, float b);

};//class	vgModUtility

//////////////////////////////////////////////////////////////////////////
//  文件操作类  //////////////////////////////////////////////////////////
class WorkFile {
private:
	FILE *stream;

public:
	WorkFile(const TCHAR *filename,const TCHAR *mode = "rb") 
	{ 
		stream = NULL; 
		Open(filename, mode); 
	};
	~WorkFile() { Close(); };

	FILE *	Stream() { return stream; };

	int		Close() 
	{ 
		int result=0; 
		if(stream) 
			result=fclose(stream); 
		stream = NULL; 
		return result; 
	}
	void	Open(const TCHAR *filename,const TCHAR *mode) 
	{ 
		Close(); 
		_tfopen_s( &stream, filename, mode); 
	}

	bool checkFileExist( )
	{
		return NULL != Stream();
	}

};
//////////////////////////////////////////////////////////////	文件操作类
//////////////////////////////////////////////////////////////////////////

#endif	//_VGMODCOMMONUTILITY_H_INCLUDED_
