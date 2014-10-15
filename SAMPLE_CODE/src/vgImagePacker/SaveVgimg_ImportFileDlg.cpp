// SaveVgimg_ImportFileDlg.cpp : implementation file
//

#include <vgStableHeaders.h>
#include "VgimgReader.h"
#include "SaveVgimg_ImportFileDlg.h"


// CSaveVgimg_ImportFileDlg dialog

IMPLEMENT_DYNAMIC(CSaveVgimg_ImportFileDlg, CDialog)

CSaveVgimg_ImportFileDlg::CSaveVgimg_ImportFileDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSaveVgimg_ImportFileDlg::IDD, pParent)
{

}

CSaveVgimg_ImportFileDlg::~CSaveVgimg_ImportFileDlg()
{
}

void CSaveVgimg_ImportFileDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE1, m_FileTree);
}


BEGIN_MESSAGE_MAP(CSaveVgimg_ImportFileDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &CSaveVgimg_ImportFileDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDOK, &CSaveVgimg_ImportFileDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CSaveVgimg_ImportFileDlg message handlers

BOOL CSaveVgimg_ImportFileDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here

	m_FileTree.AddHidFolder(CSIDL_BITBUCKET);
	m_FileTree.AddHidFolder(CSIDL_CONTROLS);
	//	m_FileTree.AddHidFolder(CSIDL_WINDOWS);
	m_FileTree.DisplayTree();


	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CSaveVgimg_ImportFileDlg::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	UpdateData();

	//m_FileTree.GetSelectedFiles();
	CString *files_names = NULL ;
	int files_num = m_FileTree.GetSelectedFiles( files_names );

	//assert( files_num != 0 );
	if ( files_num == 0 )
	{
		return;
	}

	CString all;

	for ( int i = 0 ; i < files_num ; ++i )
	{
		all += *(files_names+i);
		all += '\n';
	}
	MessageBox( all );

	delete[] files_names;
}

void CSaveVgimg_ImportFileDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	UpdateData();

	OnOK();
}
