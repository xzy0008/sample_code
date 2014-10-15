// vgtDlgCutArea.cpp : implementation file
//

#include <vgStableHeaders.h>
#include "vgTerritory/vgtDlgCutArea.h"
#include <vgKernel/vgkStringUtility.h>


// vgtDlgCutArea dialog

IMPLEMENT_DYNAMIC(vgtDlgCutArea, CDialog)

vgtDlgCutArea::vgtDlgCutArea(CWnd* pParent /*=NULL*/)
	: CDialog(vgtDlgCutArea::IDD, pParent)
{

}

vgtDlgCutArea::~vgtDlgCutArea()
{
}

void vgtDlgCutArea::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_FILE_EDIT, m_wndFileEdit);
	DDX_Text( pDX , IDC_FILE_EDIT , _abspath );
}


BEGIN_MESSAGE_MAP(vgtDlgCutArea, CDialog)
END_MESSAGE_MAP()


// vgtDlgCutArea message handlers

BOOL vgtDlgCutArea::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	CString DefExt;

	DefExt.Format("%s","(*.vtr)|*.vtr|(*.*)|*.*|");

	m_wndFileEdit.EnableFileBrowseButton ( "vtr", DefExt );

	UpdateData (FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void vgtDlgCutArea::OnOK()
{
	// TODO: Add your specialized code here and/or call the base class
	UpdateData( TRUE );

	CDialog::OnOK();
}

String vgtDlgCutArea::getPath()
{
	String longname = _abspath.GetBuffer(0);

	return vgKernel::StringUtility::getPathFromAbsoluteFilename( longname );
}

String vgtDlgCutArea::getMetaName()
{
	String longname = _abspath.GetBuffer(0);

	return vgKernel::StringUtility::getFilenameWithoutExtFromAbsPath( longname );
}

String vgtDlgCutArea::getAbsName()
{
	return _abspath.GetBuffer(0);
}