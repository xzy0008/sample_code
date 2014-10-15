
#pragma once
#include "resource.h"

// BMPExportDialog 对话框

class BMPExportDialog : public CDialog
{
	DECLARE_DYNAMIC(BMPExportDialog)

public:
	BMPExportDialog(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~BMPExportDialog();

	// 对话框数据
	enum { IDD = IDD_BMPEXPORT_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeEditBmppath();
	afx_msg void OnEnChangeEditBmpwidth();
	CString m_bmpFilePath;
	int m_bmpWidth;
	int m_bmpHeight;
	afx_msg void OnBnClickedExpbmpPath();
};
