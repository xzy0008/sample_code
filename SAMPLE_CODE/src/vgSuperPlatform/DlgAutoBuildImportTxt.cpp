
#include "vgStableHeaders.h"
#include "DlgAutoBuildImportTxt.h"


// DlgAutobuildImportTxt 对话框

IMPLEMENT_DYNAMIC(DlgAutobuildImportTxt, CDialog)

DlgAutobuildImportTxt::DlgAutobuildImportTxt(CWnd* pParent /*=NULL*/)
	: CDialog(DlgAutobuildImportTxt::IDD, pParent)
	, m_schemName(_T(""))
{

}

DlgAutobuildImportTxt::~DlgAutobuildImportTxt()
{
}

void DlgAutobuildImportTxt::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_CBString(pDX, IDC_COMBO1, m_schemName);
}


BEGIN_MESSAGE_MAP(DlgAutobuildImportTxt, CDialog)
END_MESSAGE_MAP()


// DlgAutobuildImportTxt 消息处理程序
