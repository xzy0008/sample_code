#pragma once
#include "vgBasedTabPage.h"
#include "Resource.h"
#include "vgBaseEntry.h"

// vgRootTabPage 对话框

class vgRootTabPage : public CDialog, public vgBasedTabPage
{
	DECLARE_DYNAMIC(vgRootTabPage)

public:
	vgRootTabPage(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~vgRootTabPage();

	// extends from vgBasedTabPage
	string GetTitle();
	CWnd* GetWnd();
	
	void ConnectNode(vgBaseEntry* node) {}
// 对话框数据
	enum { IDD = NIDD_ROOTVIEW };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
