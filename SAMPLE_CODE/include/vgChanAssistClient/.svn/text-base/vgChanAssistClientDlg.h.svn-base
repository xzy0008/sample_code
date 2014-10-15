// ClientAssistantDlg.h : 头文件
//

#pragma once
#include "afxcmn.h"
#include "BCGPGridCtrl.h"
#include <string>
#include <vector>
#include "afxwin.h"
using namespace std;
#include <vgConfig/vgcXMLConfigManager.h>
#include <vgKernel/vgkTrace.h>
#include "vgChanAssistClient/vgChanresource.h"

//#include "XMLConfigManager.h"

// CClientAssistantDlg 对话框
class CClientAssistantDlg : public CDialog
{
// 构造
public:
	CClientAssistantDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_CLIENTASSISTANT_DIALOG };

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
	bool is_visible;
	string m_broadCastAddress;
	UINT m_hotKeyID;
	CBCGPGridCheckItem* _FullScreen;
	CBCGPGridCheckItem* _startChannel;
	CBCGPGridCheckItem* _softBlend;		// 软融合
	std::vector<CString> vec_str_config;

	CBCGPGridCtrl m_wndGrid;
	//vgConfig::XMLConfigManager *pxmlManager;

private:
	

public:
	afx_msg void readConfigFile_ini();	// 目前使用的是读取XML 配置文件的方式,
	afx_msg void writeConfigFile_ini();	// 读取ini 配置文件的方式是之前写的,但可能会有用,没有删除

	afx_msg void readConfigFile_XML();
	afx_msg void writeConfigFile_XML();

	afx_msg void write2Reg();

	BOOL startConnect();
	BOOL createRecvSocket(int RecvPort);

	afx_msg void OnShowDlg();
	afx_msg void m_AddRow();
	afx_msg void m_AddConfig();			// 原来写的读取ini 配置文件的时候要用到的，现在没有使用


	afx_msg void OnWindowPosChanging(WINDOWPOS* lpwndpos);
	afx_msg void OnBnClickedCancel();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedOk();
	CStatic m_DlgGridLocation;
	afx_msg void OnBnClickedBtnHide();
	afx_msg void OnBnClickedBtnAddrow();
	afx_msg void OnBnClickedBenDeleterow();
};

//////////////////////////////////////////////////////////////////////
// CFileItem Class

class  CFileItem : public CBCGPGridItem
{
	// Construction
public:
	CFileItem(const CString& strFileName);

	// Overrides
	virtual void OnClickButton (CPoint point);
};

//////////////////////////////////////////////////////////////////////////