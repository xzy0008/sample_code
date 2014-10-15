#pragma once

#include <vgTerritoryResource.h>
#include "afxwin.h"
// CDlg_VisibleAnalyst 对话框




class CDlg_VisibleAnalyst : public CDialog
{
	DECLARE_DYNAMIC(CDlg_VisibleAnalyst)

public:
	CDlg_VisibleAnalyst(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlg_VisibleAnalyst();

// 对话框数据
	enum { IDD = IDD_DLG_VISIBLE_ANA };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

protected:
	CBCGPGridCtrl m_wndGrid;

public:
	CString strVisiAnaRes;
	CStatic cstcGridPos;
	bool bClosed;
	std::vector<CString> vecStrModName;

public:
	void setClosed( bool bClosed ) { bClosed = bClosed; }
	bool getClosed() { return bClosed; }
	void setList();

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();

};
