// vgSDKDLL.h : vgSDKDLL DLL 的主头文件
//

#pragma once
#if 0
#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“vgStableHeaders.h”以生成 PCH 文件"
#endif

#include "resource.h"		// 主符号


// CvgSDKDLLApp
// 有关此类实现的信息，请参阅 vgSDKDLL.cpp
//

class CvgSDKDLLApp : public CWinApp
{
public:
	CvgSDKDLLApp();

// 重写
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
#endif