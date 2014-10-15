// WizardSheetDlg.cpp : implementation file
//

#include <vgStableHeaders.h>
#include <vgConf/XMLProfile.h>
#include "WizardSheet.h"
#include "WizardSheetDlg.h"
#include "vgLibDependence.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CWizardSheetDlg dialog

CWizardSheetDlg::CWizardSheetDlg(CWnd* pParent /*=NULL*/)
	: CBCGPDialog(CWizardSheetDlg::IDD, pParent)
	, m_filePath(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CWizardSheetDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GRIDPOS, m_wndGridLocation);
	DDX_Control(pDX, IDC_COMBO1, m_versionCombo);
	DDX_Control(pDX, IDC_EDIT2, m_versionInfoEdit);
	DDX_Text(pDX, IDC_FILEPATH, m_filePath);
}

BEGIN_MESSAGE_MAP(CWizardSheetDlg, CBCGPDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_WM_DESTROY()
	ON_CBN_SELCHANGE(IDC_COMBO1, &CWizardSheetDlg::OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDC_SELFILE, &CWizardSheetDlg::OnBnClickedSelfile)
	ON_BN_CLICKED(IDC_GENERATE, &CWizardSheetDlg::OnBnClickedGenerate)
	ON_BN_CLICKED(IDC_EDIT, &CWizardSheetDlg::OnBnClickedEdit)
END_MESSAGE_MAP()


// CWizardSheetDlg message handlers

BOOL CWizardSheetDlg::OnInitDialog()
{
	vgInitDependenceVec();

	CDialog::OnInitDialog();
	
	CWaitCursor wait;

	UpdateData ();
	theApp.WriteInt (_T("Image"), true);

	theApp.WriteInt (_T("PushButtonsDefaultLook"), false);

	CBCGPButton::m_bDontSkin = false;
	RedrawWindow (NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW | RDW_ERASE | RDW_ALLCHILDREN);

	SetBackgroundImage (true ? IDB_BITMAP4 : 0);

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	CRect rectGrid;
	m_wndGridLocation.GetClientRect (&rectGrid);
	m_wndGridLocation.MapWindowPoints (this, &rectGrid);

 	m_wndGrid.Create (WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER, rectGrid, this, (UINT)-1);
 	m_wndGrid.EnableHeader (TRUE, BCGP_GRID_HEADER_MOVE_ITEMS);
 
 	//m_wndGrid.SetReadOnly ();
 
  	m_wndGrid.InsertColumn (0, _T("选择"), 70);
  	m_wndGrid.InsertColumn (1, _T("库名称"), 365);

	vgInitDependenceGrid(m_wndGrid);

	for (int i=0; i<gs_versionVec.size(); i++)
	{
		m_versionCombo.AddString(gs_versionVec[i].versionTitleName.c_str());
	}

	m_versionCombo.AddString("自定义版本");

	m_versionCombo.SetCurSel(m_versionCombo.GetCount()-1);
	m_versionInfoEdit.SetWindowText("VR-GIS 用户定制版本");

	UpdateData(FALSE);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CWizardSheetDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CWizardSheetDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CWizardSheetDlg::OnDestroy()
{
	CBCGPDialog::OnDestroy();

	vgCleanUpDependenceVec();
	// TODO: 在此处添加消息处理程序代码
}

void CWizardSheetDlg::OnCbnSelchangeCombo1()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);

	int sel = m_versionCombo.GetCurSel();
	
	if (sel == m_versionCombo.GetCount()-1)
	{
		m_versionInfoEdit.SetReadOnly(false);
		m_versionInfoEdit.SetWindowText("VR-GIS 用户定制版本");

		m_wndGrid.SetReadOnly(FALSE);
	}
	else
	{
		m_versionInfoEdit.SetWindowText(gs_versionVec[sel].versionTitleName.c_str());
		m_versionInfoEdit.SetReadOnly(TRUE);

		m_wndGrid.SetReadOnly(TRUE);
	}

	vgCheckVersionGrid(sel, m_wndGrid);

	UpdateData(FALSE);

}

void CWizardSheetDlg::OnBnClickedSelfile()
{
	// TODO: 在此添加控件通知处理程序代码
	char szFilters[]=
		"(*.xml)|*.xml|All Files (*.*)|*.*||";

	CFileDialog dlg (FALSE, "xml", "*.xml",
		OFN_FILEMUSTEXIST| OFN_HIDEREADONLY, szFilters, this);

	if (dlg.DoModal())
	{
		string fileName = dlg.GetPathName();
		
		m_filePath = fileName.c_str();

		UpdateData(FALSE);
	}
}

void CWizardSheetDlg::OnBnClickedGenerate()
{
	// TODO: 在此添加控件通知处理程序代码
 	if (m_filePath.GetLength() <= 5)
 	{
 		AfxMessageBox("请选择一个XML文件.");
 	}

	CXmlProfile profile;

	if (! profile.Load(m_filePath))
	{
		AfxMessageBox("打开文件失败.");
	}
	
	//CString ret = profile.SetProfileString("ExeDllConfig", "ExeDllTitle", NULL );

	//profile.SetKey("ExeDllConfig","ExeDllTitle", _T("中文测试"));

	char buffer[256];
	m_versionInfoEdit.GetWindowText(buffer, 256);

	string dllNames;

	for (int i=0; i<m_wndGrid.GetRowCount(); i++)
	{
		_variant_t bVal = m_wndGrid.GetRow(i)->GetItem(0)->GetValue();

		if (bVal.boolVal)
		{
			if (dllNames.length() != 0)
			{
				dllNames += ";";
			}

			_variant_t Val = m_wndGrid.GetRow(i)->GetItem(1)->GetValue();

			dllNames += _com_util::ConvertBSTRToString(Val.bstrVal);
		}
	}
	profile.WriteProfileString("ExeDllConfig","ExeDllTitle", buffer);
	profile.WriteProfileString("ExeDllConfig","ExeDllNames", dllNames.c_str());

	AfxMessageBox("生成成功.");

	profile.Close(true);
}

void CWizardSheetDlg::OnBnClickedEdit()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_filePath.GetLength() <= 5)
	{
		AfxMessageBox("请选择一个XML文件.");

		return ;
	}

	string execStr = "notepad ";
	execStr += m_filePath.GetString();

	WinExec(execStr.c_str(), SW_SHOWNORMAL);
}
