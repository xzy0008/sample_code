// Dialogs.cpp : implementation file
//
#include <vgStableHeaders.h>
#include "stdafx.h"
/*#include "RC_Demo.h"*/
#include "vgMeshDialogs.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDispColorDlg dialog


IMPLEMENT_DYNCREATE(CDispColorDlg, CDialog)

CDispColorDlg::CDispColorDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDispColorDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDispColorDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// TRACE("Construtor of disp dialog \n");
}

CDispColorDlg::~CDispColorDlg()
{
	// TRACE("Deconstructor of disp dialog \n");
}

void CDispColorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDispColorDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDispColorDlg, CDialog)
	//{{AFX_MSG_MAP(CDispColorDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON1, &CDispColorDlg::OnBnClickedButton1)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDispColorDlg message handlers

 
 /////////////////////////////////////////////////////////////////////////////
 // CDispPropDlg dialog
 
 IMPLEMENT_DYNCREATE(CDispPropDlg, CDialog)
 
 CDispPropDlg::CDispPropDlg(CWnd* pParent /*=NULL*/)
 	: CDialog(CDispPropDlg::IDD, pParent)
 {
 	//{{AFX_DATA_INIT(CDispPropDlg)
 		// NOTE: the ClassWizard will add member initialization here
 	//}}AFX_DATA_INIT
 }
 
 
 void CDispPropDlg::DoDataExchange(CDataExchange* pDX)
 {
 	CDialog::DoDataExchange(pDX);
 	//{{AFX_DATA_MAP(CDispPropDlg)
 		// NOTE: the ClassWizard will add DDX and DDV calls here
 	//}}AFX_DATA_MAP
 }
 
 
 BEGIN_MESSAGE_MAP(CDispPropDlg, CDialog)
 	//{{AFX_MSG_MAP(CDispPropDlg)
 		// NOTE: the ClassWizard will add message map macros here
 	//}}AFX_MSG_MAP
 END_MESSAGE_MAP()
 
// /////////////////////////////////////////////////////////////////////////////
// // CDispPropDlg message handlers
// 
// 
// /////////////////////////////////////////////////////////////////////////////
// // CHideDlg dialog
// 
// IMPLEMENT_DYNCREATE(CHideDlg, CDialog)
// 
// CHideDlg::CHideDlg(CWnd* pParent /*=NULL*/)
// 	: CDialog(CHideDlg::IDD, pParent)
// {
// 	//{{AFX_DATA_INIT(CHideDlg)
// 		// NOTE: the ClassWizard will add member initialization here
// 	//}}AFX_DATA_INIT
// }
// 
// 
// void CHideDlg::DoDataExchange(CDataExchange* pDX)
// {
// 	CDialog::DoDataExchange(pDX);
// 	//{{AFX_DATA_MAP(CHideDlg)
// 		// NOTE: the ClassWizard will add DDX and DDV calls here
// 	//}}AFX_DATA_MAP
// }
// 
// 
// BEGIN_MESSAGE_MAP(CHideDlg, CDialog)
// 	//{{AFX_MSG_MAP(CHideDlg)
// 		// NOTE: the ClassWizard will add message map macros here
// 	//}}AFX_MSG_MAP
// END_MESSAGE_MAP()
// 
// /////////////////////////////////////////////////////////////////////////////
// // CHideDlg message handlers
// 
// 
// /////////////////////////////////////////////////////////////////////////////
// // CLinkDlg dialog
// 
// IMPLEMENT_DYNCREATE(CLinkDlg, CDialog)
// 
// CLinkDlg::CLinkDlg(CWnd* pParent /*=NULL*/)
// 	: CDialog(CLinkDlg::IDD, pParent)
// {
// 	//{{AFX_DATA_INIT(CLinkDlg)
// 	m_bCheck1 = FALSE;
// 	//}}AFX_DATA_INIT
// }
// 
// 
// void CLinkDlg::DoDataExchange(CDataExchange* pDX)
// {
// 	CDialog::DoDataExchange(pDX);
// 	//{{AFX_DATA_MAP(CLinkDlg)
// 	DDX_Check(pDX, IDC_CHECK1, m_bCheck1);
// 	//}}AFX_DATA_MAP
// }
// 
// 
// BEGIN_MESSAGE_MAP(CLinkDlg, CDialog)
// 	//{{AFX_MSG_MAP(CLinkDlg)
// 	//}}AFX_MSG_MAP
// END_MESSAGE_MAP()
// 
// /////////////////////////////////////////////////////////////////////////////
// // CLinkDlg message handlers
// 
// BOOL CLinkDlg::OnInitDialog() 
// {
// 	CDialog::OnInitDialog();
// 	
// 	m_bCheck1 = TRUE;
// 	UpdateData(FALSE);	
// 
// 	return TRUE;  // return TRUE unless you set the focus to a control
// 	              // EXCEPTION: OCX Property Pages should return FALSE
// }

int CDispColorDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	// TRACE("DISP Dialog Create \n");

	return 0;
}

void CDispColorDlg::OnDestroy()
{
	CDialog::OnDestroy();
	// TRACE("Destory Dialog window \n");

	// TODO: 在此处添加消息处理程序代码
}

void CDispColorDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码

	vgMeshEntry *pNode = dynamic_cast<vgMeshEntry *>(vgUIController::GetInstance()->GetCurrentSelectedNode());
	if (NULL != pNode)
	{
		::MessageBox(NULL, pNode->GetName().c_str(), "MeshName", MB_OK);
	}
}
