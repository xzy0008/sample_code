/****************************************************************************
SelectImageDialog.cpp : Implementation file for the CSelectImageDialog class
written by PJ Arends
pja@telus.net

For updates check http://www.codeproject.com/tools/imageviewer.asp

-----------------------------------------------------------------------------
This code is provided as is, with no warranty as to it's suitability or usefulness
in any application in which it may be used.

This code may be used in any way you desire. This file may be redistributed by any
means as long as it is not sold for profit, and providing that this notice and the
author's name are included. Any modifications not made by the original author should
be clearly marked as such to remove any confusion between the original version and
any other versions.

If any bugs are found and fixed, a note to the author explaining the problem and
fix would be nice.
-----------------------------------------------------------------------------
****************************************************************************/

#include <vgStableHeaders.h>
#include "SelectImageDialog.h"


// CSelectImageDialog dialog

IMPLEMENT_DYNAMIC(CSelectImageDialog, CIVDialog)

CSelectImageDialog::CSelectImageDialog(CWnd* pParent /*=NULL*/)
    : CIVDialog(CSelectImageDialog::IDD, pParent)
    , m_Image(0)
    , m_MaxImage(1)
{

}

CSelectImageDialog::~CSelectImageDialog()
{
}

void CSelectImageDialog::DoDataExchange(CDataExchange* pDX)
{
    CIVDialog::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_EDITSELECT, m_Image);
    DDX_Control(pDX, IDC_SPINNUMBER, m_Spinner);
}


BEGIN_MESSAGE_MAP(CSelectImageDialog, CIVDialog)
    ON_EN_CHANGE(IDC_EDITSELECT, &CSelectImageDialog::OnEnChangeEditSelect)
END_MESSAGE_MAP()


// CSelectImageDialog message handlers

void CSelectImageDialog::OnEnChangeEditSelect()
{
    if (IsWindow(*GetDlgItem(IDOK)))
    {
        BOOL lpTrans = FALSE;
        UINT Image = GetDlgItemInt(IDC_EDITSELECT, &lpTrans, FALSE);
        GetDlgItem(IDOK)->EnableWindow(Image > 0 && Image != m_Image && Image <= m_MaxImage && lpTrans != FALSE);
    }
}

BOOL CSelectImageDialog::OnInitDialog()
{
    CIVDialog::OnInitDialog();

    m_Spinner.SetRange32(1, m_MaxImage);
    m_Spinner.SetPos32(m_Image);

    return TRUE;  // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX Property Pages should return FALSE
}
