#pragma once
#include "Resource.h"
#include "vgBasedTabPage.h"
#include "vgBaseEntry.h"

// TabOne 对话框

class TabOne : public CDialog, public vgBasedTabPage
{
	DECLARE_DYNAMIC(TabOne)

public:
	TabOne(CWnd* pParent = NULL);   // 标准构造函数
	TabOne(int *data);
	virtual ~TabOne();

	string GetTitle();
	CWnd* GetWnd();
	void ConnectNode(vgBaseEntry* node){}
	//virtual BOOL DestroyWindow();

// 对话框数据
	enum { IDD = NIDD_TAB1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnTvnSelchangedTree1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDestroy();
	afx_msg void OnTvnBegindragTree1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMRclickTree1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};
