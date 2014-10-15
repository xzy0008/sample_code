// SaveVgimg_ConfigSelectedDlg.cpp : implementation file
//

#include <vgStableHeaders.h>
#include "VgimgReader.h"
#include "SaveVgimg_ConfigSelectedDlg.h"
#include "SaveVgimg_Config_DDS.h"
#include "SaveVgimg_Config_JPG.h"



// CSaveVgimg_ConfigSelectedDlg dialog

IMPLEMENT_DYNAMIC(CSaveVgimg_ConfigSelectedDlg, CDialog)

CSaveVgimg_ConfigSelectedDlg::CSaveVgimg_ConfigSelectedDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSaveVgimg_ConfigSelectedDlg::IDD, pParent)
	, m_AimFileFormat(_T(""))
{
	NUM = 2;
}

CSaveVgimg_ConfigSelectedDlg::~CSaveVgimg_ConfigSelectedDlg()
{
	for ( int i = 0; i < NUM ; ++i )
	{
		delete m_ConfigDlg[i];
	}

}

void CSaveVgimg_ConfigSelectedDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_AIMFILE_FORMAT, m_AimFileComboBox);
	DDX_CBString(pDX, IDC_COMBO_AIMFILE_FORMAT, m_AimFileFormat);
	DDX_Control(pDX, IDC_SAVEVGIMG_CONFIG_POS, m_ConfigPos);
}


BEGIN_MESSAGE_MAP(CSaveVgimg_ConfigSelectedDlg, CDialog)
	ON_BN_CLICKED(IDC_SAVEVGIMG_SELCON_CLIPSEL, &CSaveVgimg_ConfigSelectedDlg::OnBnClickedSavevgimgSelconClipsel)
	ON_WM_SIZE()
	ON_CBN_SELCHANGE(IDC_COMBO_AIMFILE_FORMAT, &CSaveVgimg_ConfigSelectedDlg::OnCbnSelchangeComboAimfileFormat)
END_MESSAGE_MAP()


// CSaveVgimg_ConfigSelectedDlg message handlers

BOOL CSaveVgimg_ConfigSelectedDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here

	m_AimFileComboBox.SetCurSel(0);

	UpdateData();



	//获得每页显示的范围
	CRect Rect1;
	CRect rectPage;
	GetWindowRect(&Rect1); //获得主窗口的位置
	int nCaption = ::GetSystemMetrics(SM_CYCAPTION);
	int nXEdge = ::GetSystemMetrics(SM_CXEDGE);
	int nYEdge = ::GetSystemMetrics(SM_CYEDGE);


	CRect Rect2;
	CStatic* pos = (CStatic*)GetDlgItem(IDC_SAVEVGIMG_CONFIG_POS);
	pos->GetWindowRect(&Rect2); //获得框架的位置

	Rect1.top = Rect1.top + nCaption + nYEdge; //相对坐标
	Rect1.left = Rect1.left + 2 * nXEdge;
	//计算机位置
	rectPage.top=Rect2.top-Rect1.top;
	rectPage.left=Rect2.left-Rect1.left;
	rectPage.bottom=Rect2.bottom-Rect1.top;
	rectPage.right=Rect2.right-Rect1.left;


	CDialog *pjpg_dlg = new CSaveVgimg_Config_JPG();
	CDialog *pdds_dlg = new CSaveVgimg_Config_DDS();

	this->m_ConfigDlg[0] = pdds_dlg;
	this->m_ConfigDlg[1] = pjpg_dlg;



	bool result = pdds_dlg->Create(IDD_SAVEVGIMG_CONFIG_DDS ,this);
	bool result2 = pjpg_dlg->Create( IDD_SAVEVGIMG_CONFIG_JPG , this );

	assert( result2 == true );
	assert( result == true );

	// Is window created
	ASSERT(::IsWindow(pdds_dlg->m_hWnd));
	ASSERT(::IsWindow(pjpg_dlg->m_hWnd));

	// 检查每页的样式
	DWORD dwStyle = pdds_dlg->GetStyle();
	ASSERT((dwStyle & WS_CHILD) != 0); //子窗体
	ASSERT((dwStyle & WS_BORDER) == 0); //无边界


	m_ConfigDlg[0]->ShowWindow( SW_SHOW );
	m_ConfigDlg[0]->MoveWindow( rectPage );

	for ( int i = 1 ; i < NUM ; ++i )
	{
		m_ConfigDlg[i]->ShowWindow( SW_HIDE );
		m_ConfigDlg[i]->MoveWindow( rectPage );
	}

	//pdds_dlg->ShowWindow( SW_SHOW );




	CRect rectSeparator;
	GetWindowRect(&m_DlgLargeRect);

	GetDlgItem(IDC_SAVEVGIMG_SEL_CLIP)->GetWindowRect(&rectSeparator);

	m_DlgSmallRect.left = m_DlgLargeRect.left;
	m_DlgSmallRect.top = m_DlgLargeRect.top;
	m_DlgSmallRect.right = rectSeparator.left;
	m_DlgSmallRect.bottom = m_DlgLargeRect.bottom;


	setToSmallRect();


	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CSaveVgimg_ConfigSelectedDlg::OnBnClickedSavevgimgSelconClipsel()
{
	// TODO: Add your control notification handler code here
	CString str;
	
	GetDlgItemText( IDC_SAVEVGIMG_SELCON_CLIPSEL , str );
	if ( str == "高级格式设置<<" )
	{
		SetDlgItemText( IDC_SAVEVGIMG_SELCON_CLIPSEL , "高级格式设置>>" );
	}
	else
	{
		SetDlgItemText( IDC_SAVEVGIMG_SELCON_CLIPSEL , "高级格式设置<<" );
	}


	//static CRect rectLarge;
	//static CRect rectSmall;

	//if ( rectLarge.IsRectNull() )
	//{
	//	CRect rectSeparator;
	//	GetWindowRect(&rectLarge);

	//	GetDlgItem(IDC_SAVEVGIMG_SEL_CLIP)->GetWindowRect(&rectSeparator);

	//	rectSmall.left = rectLarge.left;
	//	rectSmall.top = rectLarge.top;
	//	rectSmall.right = rectSeparator.left;
	//	rectSmall.bottom = rectLarge.bottom;
	//}

	if ( str == "高级格式设置<<" )
	{
		setToSmallRect();

	}
	else
	{
		setToLargeRect();
	}

}

void CSaveVgimg_ConfigSelectedDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);
	// TODO: Add your message handler code here


}

void CSaveVgimg_ConfigSelectedDlg::OnCbnSelchangeComboAimfileFormat()
{
	// TODO: Add your control notification handler code here
	CString str;

	m_AimFileComboBox.GetLBText(
		m_AimFileComboBox.GetCurSel(), str );


	if ( str == "jpg")
	{
		for ( int i = 0; i < NUM ; ++i )
		{
			m_ConfigDlg[i]->ShowWindow( SW_HIDE );
		}

		m_ConfigDlg[1]->ShowWindow( SW_SHOW );
	}
	else if ( str == "DDS_DXT1" || 
		str == "DDS_DXT3" ||
		str == "DDS_DXT5" )
	{
		for ( int i = 0; i < NUM ; ++i )
		{
			m_ConfigDlg[i]->ShowWindow( SW_HIDE );
		}

		m_ConfigDlg[0]->ShowWindow( SW_SHOW );
	}



}
