// VgimgReader.cpp : 定义应用程序的类行为。
//

#include <vgStableHeaders.h>
#include "VgimgReader.h"
#include "MainFrm.h"


#include "LeftView.h"

#include "SaveVgimgDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CVgimgReaderApp

BEGIN_MESSAGE_MAP(CVgimgReaderApp, CWinApp)
	ON_COMMAND(ID_APP_ABOUT, &CVgimgReaderApp::OnAppAbout)
	// 基于文件的标准文档命令
	ON_COMMAND(ID_FILE_NEW, &CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinApp::OnFileOpen)
END_MESSAGE_MAP()


// CVgimgReaderApp 构造

CVgimgReaderApp::CVgimgReaderApp()
{
}
CVgimgReaderApp::~CVgimgReaderApp()
{

}



CVgimgReaderApp theApp;


// CVgimgReaderApp 初始化

BOOL CVgimgReaderApp::InitInstance()
{

	CSaveVgimgDlg dlg;
	dlg.DoModal();

	return true;

}



// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()

// 用于运行对话框的应用程序命令
void CVgimgReaderApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}


// CVgimgReaderApp 消息处理程序

