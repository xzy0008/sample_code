// vgTemplateSettingDlgDlg.h : 头文件
//

#pragma once
#include "resource.h"

// CvgTemplateSettingDlgDlg 对话框
class CvgEXEPackerDlg : public CDialog
{
// 构造
public:
	CvgEXEPackerDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_EXEPacker_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	// 输入端文件目录
	CString m_strDirIn;
	// 输出端文件目录
	CString m_strDirOut;
	// 执行文件目录
	CString m_strDirExecute;

	afx_msg void OnBnClickedButton1Executing();
	afx_msg void OnBnClickedButton2OpenPathIn();
	afx_msg void OnBnClickedButton3OpenPathOut();
	afx_msg void OnBnClickedButtonEXE();
};
