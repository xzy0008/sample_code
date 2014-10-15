#ifndef __VGSDKDLL_H__
#define __VGSDKDLL_H__

#pragma   once 


#include <vgKernel/vgkStringUtility.h>
#include <vgKernel/vgkStringVector.h>



//using namespace std;

#define VGSDK_DESC  "vgSDKDLL"


/*#ifdef VGSDK_DLL*/
#ifdef VGSDK_DLL
#define VGSDK_EXPORT  __declspec(dllexport)
#else
#define VGSDK_EXPORT  __declspec(dllimport)
#endif

//  #else
//  #	define  VGSDK_DLL VGSDK_DLL
//  #endif


#	ifdef _DEBUG
#		define  VGSDK_DLL_NAME VGSDK_DESC##"_Debug.dll"
#		define  VGSDK_LIB_NAME VGSDK_DESC##"_Debug.lib"
#	else
#		define  VGSDK_DLL_NAME VGSDK_DESC##"_Release.dll"
#		define  VGSDK_LIB_NAME VGSDK_DESC##"_Release.lib"
#	endif

typedef std::map<UINT, UINT>		VGSDK_EXPORT 		CommandToMessage;


#	endif// __VGSDKDLL_H__