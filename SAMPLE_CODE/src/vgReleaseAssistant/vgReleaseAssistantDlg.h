// vgReleaseAssistantDlg.h : 头文件
//

#pragma once
#include "resource.h"

#include "vgGroup/vgGroupNodeManager.h"

using namespace vgGroup;
using namespace std;
// CvgReleaseAssistantDlg 对话框
class CvgReleaseAssistantDlg : public CDialog
{
// 构造
public:
	CvgReleaseAssistantDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_TEMPLATESETTING_DIALOG };

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
	//输入无需处理的文件夹名
	CString m_folderName;

	afx_msg void OnBnClickedButton1Executing();
	afx_msg void OnBnClickedButton2OpenPathIn();
	afx_msg void OnBnClickedButton3OpenPathOut();

	int		getDirectorySystemIn(GroupNodeItemPtr pGroupNode, String filePath,
		int* nCountFile = NULL, int* nCountDir = NULL );

	bool	distrubuteFiles();

	void	outputResultMsg();

protected:
	bool	filterVersion( GroupNodeItemPtr pGroupNode,
		vgKernel::StringVector filters);

	bool	copyReleaseFiles();
	bool	copyReleaseFiles( GroupNodeItemPtr pGroupNode, String dir);

	bool    AddVersionAndFilter( string versionName, vgKernel::StringVector filterString );
	bool    RemoveVersionAndFilter( string versionName );

	CString BrowseFolder( HWND hWnd, LPCTSTR lpTitle );
protected:
#if 1

	GroupNodeManager	_versionsManager;

	FolderNameMap       _folderNameMap;

	DWORD _oldTime;

#else
	GroupNodeManager directoryIn;
	GroupNodeManager directoryOutDebug, directoryOutRelease, directoryOutCommon;
#endif
public:
	afx_msg void OnBnClickedCheckCommon();
	afx_msg void OnBnClickedCheckDebug();
	afx_msg void OnBnClickedCheckRelease();

	afx_msg void OnBnClickedButtonAddflolder();
	afx_msg void OnEnChangeEditFoldername();
	afx_msg void OnBnClickedButtonRemoveflolder();
};
