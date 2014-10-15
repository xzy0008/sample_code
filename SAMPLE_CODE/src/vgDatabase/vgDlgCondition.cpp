// DBOpenningDlg.cpp : implementation file
//

#include <vgStableHeaders.h>
#include <vgDatabase/vgDlgCondition.h>
#include "vgDatabase/vgdDatabaseManager.h"
#include "vgDatabase/vgdOracleConnector.h"
#include "vgDatabase/vgdBasedConnector.h"

using namespace vgDatabase;
//数据库

// #include <vgDB/AdoX.h>
// #include <vgDB/ado.h>


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define IDC_LST 123

/////////////////////////////////////////////////////////////////////////////
// DlgDBOpenning dialog

DBCondition::DBCondition(CWnd* pParent /*=NULL*/)
: CDialog(DBCondition::IDD, pParent)
{

}

DBCondition::~DBCondition()
{
	delete m_pConditionTab1;
	delete m_pConditionTab2;
	delete m_pConditionTab3;
}

void DBCondition::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//	{{AFX_DATA_MAP(DlgDBOpenning)
	//  	DDX_Text(pDX, IDC_EDIT2, m_cstrFilePath);
	// 	DDX_Text(pDX, IDC_DB_COMBO, m_databaseName);
	// 	DDX_Text(pDX, IDC_DB_DS, m_databaseSource);
	// 	DDX_Text(pDX, IDC_DB_USER, m_userName);
	// 	DDX_Text(pDX, IDC_DB_PWD, m_pwd);
	// 	DDX_Check(pDX, IDC_DB_REMPWD, m_remPwd);
	//	}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DBCondition, CDialog)
	//{{AFX_MSG_MAP(DlgDBOpenning)
	//ON_BN_CLICKED(IDC_BTN_FILEPATH, OnBtnFilepath)
	ON_WM_CREATE()
	ON_WM_SIZE()

	//}}AFX_MSG_MAP
	ON_WM_DESTROY()
END_MESSAGE_MAP()


void DBCondition::OnOK() 
{
	// TODO: Add extra validation here
	CDialog::OnOK();
	DestroyWindow();	

	// 	CDialog::OnOK();
}

void DBCondition::OnCancel() 
{
	// TODO: Add extra cleanup here
	CDialog::OnCancel();
	DestroyWindow();	

	// 	CDialog::OnCancel();
}

int DBCondition::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rectDummy;
	rectDummy.SetRectEmpty ();

	// Create combo:
	/*const DWORD dwViewStyle =	WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST
	| WS_BORDER | CBS_SORT | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;
	*/
	CRect rectTab;

	ScreenToClient (&rectTab);

	m_wndTab.Create (CBCGPTabWnd::STYLE_3D, rectTab, this, IDC_LST,
		CBCGPTabWnd::LOCATION_TOP);
	m_wndTab.EnableAutoColor (TRUE);
	m_wndTab.SetImageList (NIDB_TABICON, 16, RGB (255, 0, 255));
	m_wndTab.EnableTabSwap(false);

	AdjustLayout();

	return 0;
}

BOOL DBCondition::OnInitDialog()
{
	UpdateData(FALSE);

	m_pConditionTab1 = new DBConditionTab1(this);
	m_pConditionTab1->Create(IDD_DB_CDTAB1, &m_wndTab);

	m_pConditionTab2 = new DBConditionTab2(this);
	m_pConditionTab2->Create(IDD_DB_CDTAB2, &m_wndTab);

	m_pConditionTab3 = new DBConditionTab3(this);
	m_pConditionTab3->Create(IDD_DB_CDTAB3, &m_wndTab);

	m_wndTab.AddTab(m_pConditionTab1, "查询设置");
	m_wndTab.AddTab(m_pConditionTab2, "查询结果");
	m_wndTab.AddTab(m_pConditionTab3, "查询HTML");

	return TRUE;
}

void DBCondition::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);
	AdjustLayout ();
}

void DBCondition::AdjustLayout()
{
	if (GetSafeHwnd () == NULL)
	{
		return;
	}

	CRect rectClient;
	GetClientRect (rectClient);

	m_wndTab.SetWindowPos(NULL, rectClient.left, rectClient.top, rectClient.Width(), rectClient.Height(), SWP_NOACTIVATE | SWP_NOZORDER);
	m_wndTab.ModifyTabStyle ( CBCGPTabWnd::STYLE_3D_ROUNDED);
	m_wndTab.EnableAutoColor (FALSE);
}

void DBCondition::OnDestroy()
{
	CDialog::OnDestroy();

	// TODO: 在此处添加消息处理程序代码
	delete this;
}
