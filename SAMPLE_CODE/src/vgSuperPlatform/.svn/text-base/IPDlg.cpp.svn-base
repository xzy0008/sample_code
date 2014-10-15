// IPDlg.cpp : 实现文件
//

#include "vgStableHeaders.h"
#include "IPDlg.h"


// CIPDlg 对话框

IMPLEMENT_DYNAMIC(CIPDlg, CDialog)

CIPDlg::CIPDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CIPDlg::IDD, pParent)
	, IP1(211)
	, IP2(64)
	, IP3(136)
	, IP4(19)
{

}

CIPDlg::~CIPDlg()
{
}

void CIPDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_IP1, IP1);
	DDX_Text(pDX, IDC_IP2, IP2);
	DDX_Text(pDX, IDC_IP3, IP3);
	DDX_Text(pDX, IDC_IP4, IP4);
}


BEGIN_MESSAGE_MAP(CIPDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CIPDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CIPDlg 消息处理程序

void CIPDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	OnOK();
}
