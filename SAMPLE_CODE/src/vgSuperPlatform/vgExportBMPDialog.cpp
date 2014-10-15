
#include "vgStableHeaders.h"
#include "vgExportBmpDialog.h"

// BMPExportDialog 对话框

IMPLEMENT_DYNAMIC(BMPExportDialog, CDialog)

BMPExportDialog::BMPExportDialog(CWnd* pParent /*=NULL*/)
: CDialog(BMPExportDialog::IDD, pParent)
, m_bmpWidth(0)
, m_bmpHeight(0)
{

}

BMPExportDialog::~BMPExportDialog()
{
}

void BMPExportDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_BMPPATH, m_bmpFilePath);
	DDX_Text(pDX, IDC_EDIT_BMPWIDTH, m_bmpWidth);
	DDX_Text(pDX, IDC_EDIT_BMPHEIGHT, m_bmpHeight);
	DDV_MinMaxInt(pDX, m_bmpWidth, 4, INT_MAX);
	DDV_MinMaxInt(pDX, m_bmpHeight, 4, INT_MAX);
}


BEGIN_MESSAGE_MAP(BMPExportDialog, CDialog)
	ON_EN_CHANGE(IDC_EDIT_BMPPATH, &BMPExportDialog::OnEnChangeEditBmppath)
	ON_EN_CHANGE(IDC_EDIT_BMPWIDTH, &BMPExportDialog::OnEnChangeEditBmpwidth)
	ON_BN_CLICKED(IDC_EXPBMP_PATH, &BMPExportDialog::OnBnClickedExpbmpPath)
END_MESSAGE_MAP()


// BMPExportDialog 消息处理程序

void BMPExportDialog::OnEnChangeEditBmppath()
{
	// TODO:  如果该控件是 RICHEDIT 控件，则它将不会
	// 发送该通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}

void BMPExportDialog::OnEnChangeEditBmpwidth()
{
	// TODO:  如果该控件是 RICHEDIT 控件，则它将不会
	// 发送该通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}

void BMPExportDialog::OnBnClickedExpbmpPath()
{
	// TODO: 在此添加控件通知处理程序代码
	char szFilters[]=
		"(*.bmp)|*.bmp|All Files (*.*)|*.*||";

	CFileDialog dlg (FALSE, "bmp", "*.bmp",
		OFN_FILEMUSTEXIST| OFN_HIDEREADONLY, szFilters, this);

	if( dlg.DoModal ()==IDOK )
	{
		m_bmpFilePath = dlg.GetPathName();
		
		UpdateData(false);
	}
}
