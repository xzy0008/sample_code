// vgTemplateSettingDlgDlg.h : 头文件
//

#pragma once

#include "resource.h"
#include "vgGroupNodeManager.h"
#include "afxcmn.h"

using namespace vgGroup;

// CvgInstallPatchWizardDlg 对话框
class CvgInstallPatchWizardDlg : public CDialog
{
// 构造
public:
	CvgInstallPatchWizardDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_INSTALLMAXPLUGIN_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;
	CProgressCtrl m_progressCtrl;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:

	afx_msg void OnBnClickedInstall();

private:
	bool getDesPathFormRegedit();

	int		getDirectorySystemIn(GroupNodeItemPtr pGroupNode, String filePath,
		int* nCountFile = NULL, int* nCountDir = NULL );

	bool    copyPatchFiles( GroupNodeItemPtr pGroupNode, String dir );

	GroupNodeManager _nodeManger;


	vector<String>   _desDirs;             //存储目标目录的数组
	int              _numOfFiles;          //需要更新的文件总个数
	int              _progressPos;         //进度条位置
	int              _numOfDirs;           //目标目录的个数，以防注册表9.0文件夹下有多个Installdir键值 

};
