// DlgAutoBuildInput.cpp : 实现文件
//

#include <vgStableheaders.h>
#include "DlgAutoBuildInput.h"


// DlgAutoBuildInput 对话框

IMPLEMENT_DYNAMIC(DlgAutoBuildInput, CDialog)

DlgAutoBuildInput::DlgAutoBuildInput(CWnd* pParent /*=NULL*/)
	: CDialog(DlgAutoBuildInput::IDD, pParent)
	, m_schem(_T(""))
	, m_years(0)
{

}

DlgAutoBuildInput::~DlgAutoBuildInput()
{
}

void DlgAutoBuildInput::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_CBString(pDX, IDC_AUTO_SCHEM, m_schem);
	DDX_Text(pDX, IDC_AUTO_TIME, m_years);
	DDV_MinMaxInt(pDX, m_years, 2000, 2099);
}


BEGIN_MESSAGE_MAP(DlgAutoBuildInput, CDialog)
END_MESSAGE_MAP()


// DlgAutoBuildInput 消息处理程序
