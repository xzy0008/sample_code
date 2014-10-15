// dlgCutSuface.cpp : 实现文件
//

#include "vgStableHeaders.h"
#include "vgTerritory/dlgCutSuface.h"
#include "vgTerritory/CutSurfDoc.h"


#include <afxpriv.h> //Definition of WM_INITIALUPDATE

// CdlgCutSuface 对话框

IMPLEMENT_DYNAMIC(CdlgCutSuface, CDialog)

CdlgCutSuface::CdlgCutSuface(CWnd* pParent /*=NULL*/)
	: CDialog(CdlgCutSuface::IDD, pParent)
	, sHeightValue(_T(""))
{
	pView = NULL;

	m_bClosed = false;
}

CdlgCutSuface::~CdlgCutSuface()
{
// 	if (pView != NULL)
// 	{
// 		delete pView;
// 		pView = NULL;
// 	}
	
}

void CdlgCutSuface::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_STA_OUT_TXT, sHeightValue);
}


BEGIN_MESSAGE_MAP(CdlgCutSuface, CDialog)
	ON_WM_DESTROY()
	ON_WM_SETFOCUS()
	ON_BN_CLICKED(IDOK, &CdlgCutSuface::OnBnClickedOk)
END_MESSAGE_MAP()


// CdlgCutSuface 消息处理程序

BOOL CdlgCutSuface::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CCreateContext pContext;

	CWnd* pFrameWnd = this;

	pContext.m_pCurrentDoc = new CutSurfDoc;
	pContext.m_pNewViewClass = RUNTIME_CLASS(CutSurfView);

	/*CutSurfView **/pView =
		(CutSurfView *) ((CFrameWnd*)pFrameWnd)->CreateView(&pContext);
	ASSERT(pView);
	pView->ShowWindow(SW_NORMAL);

	CRect rectWindow;
	GetDlgItem(IDC_CUTVIEW_RECT)->GetWindowRect(rectWindow);
	ScreenToClient( rectWindow );
	// 设置View大小和位置
	pView->MoveWindow( rectWindow , TRUE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CdlgCutSuface::OnDestroy()
{
	CDialog::OnDestroy();
	//delete this;
	// TODO: 在此处添加消息处理程序代码

}

void CdlgCutSuface::OnSetFocus(CWnd* pOldWnd)
{
	CDialog::OnSetFocus(pOldWnd);

	// TODO: 在此处添加消息处理程序代码
}

void CdlgCutSuface::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	m_bClosed = true;

	OnOK();
}
