// MyThread.cpp : 实现文件
//

#include <vgStableHeaders.h>
#include "vgAutoLoadThread.h"
// UILoadThread


IMPLEMENT_DYNCREATE(CUILoadThread, CWinThread)

CUILoadThread::CUILoadThread()
{
}

CUILoadThread::~CUILoadThread()
{
}

BOOL CUILoadThread::InitInstance()
{
	// TODO: 在此执行任意逐线程初始化
	dlg.DoModal();

	return TRUE;
}

int CUILoadThread::ExitInstance()
{
	// TODO: 在此执行任意逐线程清理

	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CUILoadThread, CWinThread)
	ON_THREAD_MESSAGE( WM_DESTROY, OnDestroy)
END_MESSAGE_MAP()


// MyThread 消息处理程序
void CUILoadThread::OnDestroy(WPARAM wParam, LPARAM lParam)
{
	HWND hWnd = dlg.GetSafeHwnd();
	SendMessage(hWnd,WM_CLOSE,0,0);
}