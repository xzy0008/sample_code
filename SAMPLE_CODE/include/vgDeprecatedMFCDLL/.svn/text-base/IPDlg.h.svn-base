#pragma once

#include "resource.h"

// CIPDlg 对话框

class  VGDEP_EXPORT CIPDlg : public CDialog
{
	DECLARE_DYNAMIC(CIPDlg)

public:
	CIPDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CIPDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG_IP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	BYTE IP1;
	BYTE IP2;
	BYTE IP3;
	BYTE IP4;
	afx_msg void OnBnClickedOk();
};
