// dlgSetCellSize.cpp : 实现文件
//

//#include "stdafx.h"
#include "vgStableHeaders.h"
#include "vgTerritory/dlgSetCellSize.h"


// CdlgSetCellSize 对话框

IMPLEMENT_DYNAMIC(CdlgSetCellSize, CDialog)

CdlgSetCellSize::CdlgSetCellSize(CWnd* pParent /*=NULL*/)
	: CDialog(CdlgSetCellSize::IDD, pParent)
	, cellSize(10.0)
{

}

CdlgSetCellSize::~CdlgSetCellSize()
{
}

void CdlgSetCellSize::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_cellsize, cellSize);
}


BEGIN_MESSAGE_MAP(CdlgSetCellSize, CDialog)
	ON_EN_CHANGE(IDC_EDIT_cellsize, &CdlgSetCellSize::OnEnChangeEditcellsize)
END_MESSAGE_MAP()


// CdlgSetCellSize 消息处理程序

void CdlgSetCellSize::OnEnChangeEditcellsize()
{
	// TODO:  如果该控件是 RICHEDIT 控件，则它将不会
	// 发送该通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	UpdateData(true);
}
