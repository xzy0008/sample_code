// ScriptConsoleDlg.cpp : implementation file
//

#include <vgStableHeaders.h>
#include "vgScript/ScriptConsoleDlg.h"

#include <vgScript/vgscScriptManager.h>
#include <vgKernel/vgkStringUtility.h>




#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CScriptConsoleDlg dialog

CScriptConsoleDlg::CScriptConsoleDlg(CWnd* pParent /*=NULL*/)
: CResizableDialog(CScriptConsoleDlg::IDD, pParent)
, _scriptContent(_T(""))
, _scriptOutput(_T(""))
, _scriptTips(_T(""))
{
	//{{AFX_DATA_INIT(CScriptConsoleDlg)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_pMenuFrame = NULL;
}

void CScriptConsoleDlg::DoDataExchange(CDataExchange* pDX)
{
	CResizableDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CScriptConsoleDlg)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_MENU_LOCATION, m_wndMenuBarLocation);
	DDX_Control(pDX, IDC_EDIT1, _outputCtrl);
	DDX_Control(pDX, IDC_SCRIPT_SPLITTER, _splitterStatic);
	DDX_Control(pDX, IDC_SCRIPT_EDIT, _scriptEditCtrl);
	DDX_Control(pDX, IDC_SCRIPT_TIP, _scriptTipsCtrl);
	DDX_Text( pDX , IDC_SCRIPT_EDIT , _scriptContent );
	DDX_Text( pDX , IDC_EDIT1 , _scriptOutput );
	DDX_Text( pDX , IDC_SCRIPT_TIP , _scriptTips );
}

BEGIN_MESSAGE_MAP(CScriptConsoleDlg, CResizableDialog)
	//{{AFX_MSG_MAP(CScriptConsoleDlg)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
	ON_EN_CHANGE(IDC_SCRIPT_EDIT, &CScriptConsoleDlg::OnEnChangeScriptEdit)
	ON_BN_CLICKED(IDC_SCRIPT_EXECUATE, &CScriptConsoleDlg::OnBnClickedScriptExecuate)
	ON_WM_SIZE()
	ON_COMMAND(ID_SCRIPT_EXIT, &CScriptConsoleDlg::OnScriptExit)
	ON_COMMAND(ID_SCRIPT_SAVE, &CScriptConsoleDlg::OnScriptSave)
	ON_COMMAND(ID_IMPORT_PY, &CScriptConsoleDlg::OnImportPy)
	ON_COMMAND(ID_SCRIPT_ABOUT, &CScriptConsoleDlg::OnScriptAbout)
	ON_COMMAND(ID_SCRIPT_CLEAR, &CScriptConsoleDlg::OnClear)
	ON_WM_DESTROY()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CScriptConsoleDlg message handlers

BOOL CScriptConsoleDlg::OnInitDialog()
{
	CResizableDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	addAnchorToItems();



	// Create menu bar:
	m_wndMenuBar.Create (this);

	CMenu menu;
	menu.LoadMenu (IDR_SCRIPT_MENU);
	m_wndMenuBar.CreateFromMenu (menu.GetSafeHmenu (), TRUE, TRUE);

	m_wndMenuBar.SetBarStyle (
		m_wndMenuBar.GetBarStyle () & 
		~(CBRS_GRIPPER | CBRS_BORDER_TOP | CBRS_BORDER_BOTTOM | CBRS_BORDER_LEFT | CBRS_BORDER_RIGHT));

	// Set menu bar position and size:
	CRect rectMenuBar;
	m_wndMenuBarLocation.GetWindowRect (&rectMenuBar);
	ScreenToClient (&rectMenuBar);

	m_wndMenuBar.SetWindowPos (&wndTop, rectMenuBar.left, rectMenuBar.top, 
		rectMenuBar.Width (), 
		rectMenuBar.Height (),
		SWP_NOACTIVATE);


	m_pMenuFrame = new CCmdFrame (this);
	m_pMenuFrame->Create (NULL, _T(""));
	m_pMenuFrame->ShowWindow (SW_HIDE);
	m_pMenuFrame->SetMenuBar (&m_wndMenuBar);

	m_wndMenuBar.SetOwner (m_pMenuFrame);
	BCGCBProSetTopLevelFrame (m_pMenuFrame);

	// other initializations

	// grip is visible by default
	//CheckRadioButton(IDC_RADIO1, IDC_RADIO2, IDC_RADIO2);
	//GetDlgItem(IDC_RADIO2)->SetFocus();


	dumpToOutput( "\r\n   Script Console v1.0\r\n\r\n" );

	// min/max size settings

	// get desktop size
	CRect rc;
	GetDesktopWindow()->GetClientRect(&rc);

	// set max tracking size to half a screen
	// SetMaxTrackSize(CSize(rc.Width(), rc.Height()/2));

	// maximized position and size on top of the screen
	// rc.bottom = 100;
	// SetMaximizedRect(rc);

	//  save/restore
	// (for dialog based app, default is a .INI file with
	// the application's name in the Windows directory)





	//////////////////////////////////////////////////////////////////////////

	createSplitter();


	EnableSaveRestore(_T("Script Console"));

#if VGK_LANG_CHS
	setScriptTips("提示: 按住Ctrl+Enter键执行脚本");
#endif

	_scriptEditCtrl.SetFocus();


	//////////////////////////////////////////////////////////////////////////

	return FALSE;  // return TRUE  unless you set the focus to a control
}




#define WS_EX_LAYOUT_RTL	0x00400000

int CScriptConsoleDlg::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	//	ModifyStyleEx(0, WS_EX_LAYOUT_RTL);

	if (CResizableDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	return 0;
}

void CScriptConsoleDlg::OnEnChangeScriptEdit()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CResizableDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}



void CScriptConsoleDlg::OnBnClickedScriptExecuate()
{
	UpdateData( TRUE );

	//MessageBox( _scriptContent );

	String content = _scriptContent.GetBuffer(0);

	dumpToOutput( content , true , true );

	vgKernel::StringUtility::replace( content , "\r" , "" );

	vgScript::ScriptManager::getSingleton().runScriptString( content );



	_scriptContent = "";

	UpdateData( FALSE );

	_outputCtrl.LineScroll( _outputCtrl.GetLineCount() );

	return;
}

LRESULT CScriptConsoleDlg::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	if (message == WM_NOTIFY)
	{
		if (wParam == IDC_SCRIPT_SPLITTER )
		{	
			SPC_NMHDR* pHdr = (SPC_NMHDR*) lParam;
			DoResize2(pHdr->delta);
		}
	}

	return CResizableDialog::DefWindowProc(message, wParam, lParam);
}

void CScriptConsoleDlg::DoResize2( int delta )
{

	RemoveAllAnchors();


	CSplitterControl::ChangeHeight(&_outputCtrl, delta);
	CSplitterControl::ChangeHeight( &_scriptEditCtrl , -delta , CW_BOTTOMALIGN );
	//CSplitterControl::ChangeHeight(&_splitterStatic, delta);

	CWnd* pWnd;
	pWnd = GetDlgItem( IDC_GROUP1 );
	CSplitterControl::ChangeHeight( pWnd , -delta , CW_BOTTOMALIGN );


	CRect rc;
	_splitterStatic.GetWindowRect( &rc );
	//ScreenToClient(rc);

	CSplitterControl::ChangePos( &_splitterStatic , 0 , delta );

	//CSplitterControl::ChangeHeight(&m_txtContent, -delta, CW_BOTTOMALIGN);


	addAnchorToItems();

	ArrangeLayout();
	//SetSplitterRange();
	setSplitterRange();


	Invalidate();
	UpdateWindow();
}

void CScriptConsoleDlg::createSplitter()
{
	CRect rc;
	CWnd* pWnd;

	pWnd = GetDlgItem( IDC_SCRIPT_SPLITTER );


	if ( pWnd == NULL )
	{
		return;
	}

	pWnd->GetWindowRect(rc);
	ScreenToClient(rc);
	m_wndSplitter1.Create(WS_CHILD | WS_VISIBLE, rc, this, IDC_SCRIPT_SPLITTER);
	m_wndSplitter1.SetRange(50, 50, -1);

	setSplitterRange();
	return;
}
void CScriptConsoleDlg::OnSize(UINT nType, int cx, int cy)
{
	CResizableDialog::OnSize(nType, cx, cy);

	//setSplitterRange();


	CRect rcTop;
	CWnd* pWnd;

	pWnd = GetDlgItem( IDC_SCRIPT_SPLITTER );

	if ( pWnd == NULL )
	{
		return;
	}

	pWnd->GetWindowRect(rcTop);
	ScreenToClient(rcTop);

	m_wndSplitter1.MoveWindow( &rcTop );



	setSplitterRange();

	Invalidate();
	UpdateWindow();
}

void CScriptConsoleDlg::setSplitterRange()
{

	CRect rcTop;
	CWnd* pWnd;

	pWnd = GetDlgItem( IDC_SCRIPT_SPLITTER );

	if ( pWnd == NULL )
	{
		return;
	}

	pWnd->GetWindowRect(rcTop);
	ScreenToClient(rcTop);

	{
		CRect rcTop;
		_outputCtrl.GetWindowRect(rcTop);
		ScreenToClient(rcTop);
		CRect rcMiddle;
		GetDlgItem(IDC_SCRIPT_EXECUATE)->GetWindowRect(rcMiddle);
		ScreenToClient(rcMiddle);
		m_wndSplitter1.SetRange(rcTop.top+30, rcMiddle.top-20);
	}

	//CRect rcTop;
	//_outputCtrl.GetWindowRect(rcTop);
	//ScreenToClient(rcTop);

	//CRect rcMiddle;
	//GetDlgItem(IDC_MSGVIEW)->GetWindowRect(rcMiddle);
	//ScreenToClient(rcMiddle);

	//m_wndSplitter1.SetRange( 0 , rcTop.top+50 );
	//m_wndSplitter1.SetRange(rcTop.top+50, rcTop.bottom);
	//m_wndSplitter1.SetRange(50, 50, -1);

	//CRect rcBottom;
	//m_ChangedFileListCtrl.GetWindowRect(rcBottom);
	//ScreenToClient(rcBottom);
	//m_wndSplitter2.SetRange(rcMiddle.top+30, rcBottom.bottom-20);

}

void CScriptConsoleDlg::addAnchorToItems()
{
	// preset layout
	AddAnchor(IDC_SCRIPT_EXECUATE, BOTTOM_RIGHT);
	AddAnchor(IDCANCEL, BOTTOM_RIGHT);
	AddAnchor(IDC_SPIN1, TOP_RIGHT);
	AddAnchor(IDC_LABEL1, TOP_LEFT);
	AddAnchor(IDC_EDIT1, TOP_LEFT, BOTTOM_RIGHT);
	AddAnchor( IDC_SCRIPT_SPLITTER , BOTTOM_LEFT, BOTTOM_RIGHT );
	AddAnchor( IDC_SCRIPT_EDIT , BOTTOM_LEFT, BOTTOM_RIGHT );
	AddAnchor(IDC_GROUP1, BOTTOM_LEFT, BOTTOM_RIGHT);
	AddAnchor(IDC_SCRIPT_TIP ,BOTTOM_LEFT, BOTTOM_RIGHT );
}
BOOL CScriptConsoleDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class

	switch (pMsg->message)
	{
	case WM_SYSKEYDOWN:
	case WM_SYSKEYUP:
	case WM_KEYDOWN:
		if (m_pMenuFrame->PreTranslateMessage (pMsg))
		{
			return TRUE;
		}
		break;
	}


	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam == VK_RETURN)
		{
			if (GetKeyState(VK_CONTROL) < 0)
			{
				OnBnClickedScriptExecuate();

				//dumpToOutput( " sadfasdfa " );

				//clearOutput();

				return TRUE;
			}
			else
			{

			}
		}
	}

	return CResizableDialog::PreTranslateMessage(pMsg);
}

void CScriptConsoleDlg::dumpToOutput( const std::string& msg, 
									 const bool& addlinesep/* = true  */, 
									 const bool& add_decoration/* = false*/ )
{

	String trimedstr = msg;

	size_t foundPos = 0;

	//while ( (foundPos = trimedstr.find("\r",foundPos)) != string::npos)
	//{
	//	trimedstr.replace(foundPos, 1, "");
	//}

	foundPos = 0;

	while ( (foundPos = trimedstr.find("\n",foundPos)) != String::npos)
	{
		trimedstr.replace(foundPos, 1, "\r\n");
		foundPos   =   foundPos   +   2; 
	}

	if ( add_decoration )
	{
		_scriptOutput += ">>> ";
	}

	_scriptOutput += trimedstr.c_str();

	if ( addlinesep )
	{
		_scriptOutput += "\r\n";
	}


	//int iLineNum = _outputCtrl.GetLineCount();
	//if (iLineNum <= 1000)
	//{
		
		//
	//}
	//else
	//{
		//_outputCtrl.SetSel(0, -1);
		//_outputCtrl.Clear();
	//}

	UpdateData( FALSE );

	//_outputCtrl.SetSel(-1, -1);
	//_outputCtrl.ReplaceSel( CString msg.c_str() + "\r\n"); 
}

void CScriptConsoleDlg::clearOutput()
{
	_scriptOutput="";
	UpdateData( FALSE );
}

void CScriptConsoleDlg::setScriptTips( const std::string& tips )
{
	_scriptTips = tips.c_str();
	UpdateData( FALSE );
}
void CScriptConsoleDlg::OnScriptExit()
{
	OnOK();
}

void CScriptConsoleDlg::OnScriptSave()
{
	// TODO: Add your command handler code here

	UpdateData( TRUE );

	//MessageBox( _scriptContent );

	String content = _scriptContent.GetBuffer(0);


	CString DefExt;

	DefExt.Format("%s","py文件(*.py)|*.py|");

	CFileDialog dlgmodelFile(false,"py",NULL,OFN_HIDEREADONLY|OFN_CREATEPROMPT|OFN_NONETWORKBUTTON,DefExt);

	dlgmodelFile.m_ofn.lpstrTitle="保存py文件";

	if(dlgmodelFile.DoModal()==IDOK)
	{
		String FilePathName = dlgmodelFile.GetPathName();


		vgKernel::StreamWriterPtr pwriter = 
			vgKernel::StreamWriterFactory::createFromFile( FilePathName );

		if ( pwriter.isNull() == true )
		{
			return;
		}

		pwriter->write( (void*)content.c_str() , content.size() );
	}

}

void CScriptConsoleDlg::OnImportPy()
{
	CString DefExt;

	DefExt.Format("%s","py文件(*.py)|*.py|");

	CFileDialog dlgmodelFile(true,"py",NULL,OFN_HIDEREADONLY|OFN_CREATEPROMPT|OFN_NONETWORKBUTTON,DefExt);

	dlgmodelFile.m_ofn.lpstrTitle="导入py文件";

	if(dlgmodelFile.DoModal()==IDOK)
	{
		String FilePathName = dlgmodelFile.GetPathName();


		vgKernel::StreamReaderPtr preader = 
			vgKernel::StreamReaderFactory::createFromFile( FilePathName );

		if ( preader.isNull() )
		{
			return;
		}

		int siz = preader->size();
		char* buf = new char[siz + 1 ];
		memset( buf , 0 , siz + 1);

		preader->read( buf , siz );


		_scriptContent= buf;
		delete buf;

		UpdateData( FALSE );

		//String ddde=_scriptContent;
	}
}

void CScriptConsoleDlg::OnScriptAbout()
{
	// TODO: Add your command handler code here
	::MessageBox( NULL , "Script Console 1.0 - VR-GIS platform", "关于" , MB_OK );
}

void CScriptConsoleDlg::OnDestroy()
{
	//m_pMenuFrame->DestroyWindow ();

	CResizableDialog::OnDestroy();



	// TODO: Add your message handler code here
}

void CScriptConsoleDlg::OnClear()
{
	clearOutput();
}