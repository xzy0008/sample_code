
#ifndef _UILoadThread_H
#define _UILoadThread_H

#include <vgDeprecatedMFCDLL/AutoLoadDialog.h>

// UILoadThread

class CUILoadThread : public CWinThread
{
	DECLARE_DYNCREATE(CUILoadThread)

protected:
	CUILoadThread();           // 动态创建所使用的受保护的构造函数
	virtual ~CUILoadThread();

public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

	afx_msg void OnDestroy(WPARAM wParam, LPARAM lParam);
protected:
	DECLARE_MESSAGE_MAP()

	CAutoLoadDialog dlg; 

};

#endif
