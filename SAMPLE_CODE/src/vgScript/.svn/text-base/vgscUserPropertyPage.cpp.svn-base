

#include <vgStableHeaders.h>


#include "vgScript/vgscUserPropertyPage.h"


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(UserPropertyPage, CBCGPPropertyPage)



/////////////////////////////////////////////////////////////////////////////
// UserPropertyPage property page

UserPropertyPage::UserPropertyPage() 
: CBCGPPropertyPage(UserPropertyPage::IDD)
{
}


UserPropertyPage::UserPropertyPage( const std::vector<std::string>& initscript ) 
: CBCGPPropertyPage(UserPropertyPage::IDD)
{
	//{{AFX_DATA_INIT(UserPropertyPage)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	_initScripts = initscript;
	assert( initscript.size() == 5 );
}

UserPropertyPage::~UserPropertyPage()
{
}

void UserPropertyPage::DoDataExchange(CDataExchange* pDX)
{
	CBCGPPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(UserPropertyPage)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_TABS_LOC, m_wndTabLoc);
}


BEGIN_MESSAGE_MAP(UserPropertyPage, CBCGPPropertyPage)
	//{{AFX_MSG_MAP(UserPropertyPage)
	// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BTN_EDIT_INIT, &UserPropertyPage::OnBnClickedBtnEditInit)
	// Tab control notifications
	ON_REGISTERED_MESSAGE(BCGM_ON_MOVE_TAB, OnMoveTab)
	ON_REGISTERED_MESSAGE(BCGM_CHANGE_ACTIVE_TAB, OnChangeActiveTab)
	ON_REGISTERED_MESSAGE(BCGM_CHANGING_ACTIVE_TAB, OnChangingActiveTab)

	ON_BN_CLICKED(IDC_SAVE_AND_RUN, &UserPropertyPage::OnBnClickedSaveAndRun)
	ON_BN_CLICKED(IDC_CLEAR_USER_SCRIPT, &UserPropertyPage::OnBnClickedClearUserScript)
END_MESSAGE_MAP()

void UserPropertyPage::OnBnClickedBtnEditInit()
{
	//::MessageBox(NULL , "sdfafd" , "sdfafs" , MB_OK );

	//UserScriptEditDlg dlg;

	//dlg.DoModal();
}

BOOL UserPropertyPage::OnInitDialog()
{
	CBCGPPropertyPage::OnInitDialog();



	// TODO:  在此添加额外的初始化

	if (m_wndTab.GetSafeHwnd () != NULL)
	{
		return TRUE;
	}

	CRect rectTab;

	m_wndTabLoc.GetWindowRect (&rectTab);
	ScreenToClient (&rectTab);

	m_wndTab.Create (CBCGPTabWnd::STYLE_3D, rectTab, this, 1,
		CBCGPTabWnd::LOCATION_TOP);

	m_wndTab.SetImageList (IDB_ICON_VGSC_TABS, 16, RGB (255, 0, 255));


	_cedits.push_back( &m_wnd1 );
	_cedits.push_back( &m_wnd2 );
	_cedits.push_back( &m_wnd3 );
	_cedits.push_back( &m_wnd4 );
	_cedits.push_back( &m_wnd5 );

	assert( _initScripts.size() == _cedits.size() );

	for ( int i = 0 ;i < _cedits.size() ; ++ i )
	{
		CEdit* edi = _cedits[i];

		edi->Create(
			ES_WANTRETURN|ES_AUTOVSCROLL | ES_MULTILINE  | WS_CHILD | WS_VISIBLE | WS_VSCROLL, 
			CRect (0, 0, 0, 0),
			&m_wndTab, i );

		edi->SetFont (&globalData.fontRegular);
		edi->SetWindowText( _initScripts[i].c_str() );

		edi->SetMargins( 5, 5 );
	}

	m_wndTab.AddTab (&m_wnd1, "User Init", 0, FALSE);
	m_wndTab.AddTab (&m_wnd2, "User RenderBegin", 1, FALSE);
	m_wndTab.AddTab (&m_wnd3, "User Render", 2, FALSE);
	m_wndTab.AddTab (&m_wnd4, "User RenderEnd", 3, FALSE);
	m_wndTab.AddTab (&m_wnd5, "User Uninit", 5, FALSE);


	UpdateData (FALSE);

	CBCGPTabWnd::Style style = CBCGPTabWnd::STYLE_3D;

	m_wndTab.ModifyTabStyle (style);
	m_wndTab.RecalcLayout ();
	m_wndTab.RedrawWindow ();

	m_wndTab.SetLocation (CBCGPTabWnd::LOCATION_TOP);
	//m_wndTab.EnableAutoColor (TRUE);

	m_wndTab.EnableTabSwap (TRUE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

LRESULT UserPropertyPage::OnMoveTab( WPARAM wp, LPARAM lp )
{
	return NULL;
}

LRESULT UserPropertyPage::OnChangeActiveTab( WPARAM wp, LPARAM lp )
{
return NULL;
}

LRESULT UserPropertyPage::OnChangingActiveTab( WPARAM wp, LPARAM lp )
{
return NULL;
}
void UserPropertyPage::OnBnClickedSaveAndRun()
{
	// TODO: 在此添加控件通知处理程序代码

	getDataFromTabs();


}

void UserPropertyPage::getDataFromTabs()
{
	_scripts.clear();

	UpdateData( FALSE );
	for ( int i = 0 ; i < _cedits.size() ; ++ i )
	{
		CString str;
		_cedits[i]->GetWindowText( str );
		_scripts.push_back( str.GetBuffer(0) );
	}
}

bool UserPropertyPage::isStringChanged()
{
	getDataFromTabs();

	assert( _initScripts.size() == _scripts.size() );

	for ( int i = 0 ; i < _initScripts.size() ; ++ i )
	{
		std::string s1 = _initScripts[i];
		std::string s2 = _scripts[i];
		if( s1.compare( s2 ) != 0 )
		{
			return true;
		}
	}

	return false;
}
BOOL UserPropertyPage::OnCommand(WPARAM wParam, LPARAM lParam)
{
	// TODO: 在此添加专用代码和/或调用基类


	return CBCGPPropertyPage::OnCommand(wParam, lParam);
}

void UserPropertyPage::OnBnClickedClearUserScript()
{
	clearAll();
}

void UserPropertyPage::clearAll()
{
	for ( int i = 0 ;i < _cedits.size() ; ++ i )
	{
		CEdit* edi = _cedits[i];

		edi->SetWindowText( "" );
	}
}