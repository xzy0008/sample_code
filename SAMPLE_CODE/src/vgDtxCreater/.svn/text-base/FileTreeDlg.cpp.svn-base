// FileTreeDlg.cpp : implementation file
//

#include <vgStableHeaders.h>
#include "VgimgReader.h"
#include "FileTreeDlg.h"


// CFileTreeDlg dialog

IMPLEMENT_DYNAMIC(CFileTreeDlg, CDialog)

CFileTreeDlg::CFileTreeDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFileTreeDlg::IDD, pParent)
{

}

CFileTreeDlg::~CFileTreeDlg()
{
}

void CFileTreeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE1, m_FileTree);
}


BEGIN_MESSAGE_MAP(CFileTreeDlg, CDialog)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE1, &CFileTreeDlg::OnTvnSelchangedTree1)
END_MESSAGE_MAP()


// CFileTreeDlg message handlers

BOOL CFileTreeDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ½ûÖ¹checkboxÄ£Ê½¡£
	m_FileTree.setCheckState( false );

	// TODO:  Add extra initialization here
	m_FileTree.AddHidFolder(CSIDL_BITBUCKET);
	m_FileTree.AddHidFolder(CSIDL_CONTROLS);
	//	m_FileTree.AddHidFolder(CSIDL_WINDOWS);
	m_FileTree.DisplayTree();
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CFileTreeDlg::OnTvnSelchangedTree1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: Add your control notification handler code here

	CString str = m_FileTree.GetSelectedFile();

	if ( str != "" )
	{
		MessageBox( str );
	}
	

	*pResult = 0;
}
