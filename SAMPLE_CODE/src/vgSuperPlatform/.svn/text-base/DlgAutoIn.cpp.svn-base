// D:\___NewVersion\vrgis\src\vgSuperPlatform\DlgAutoIn.cpp : 实现文件
//

#include <vgstableheaders.h>
#include "DlgAutoIn.h"


// DlgAutoIn 对话框

IMPLEMENT_DYNAMIC(DlgAutoIn, CDialog)

DlgAutoIn::DlgAutoIn(CWnd* pParent /*=NULL*/)
	: CDialog(DlgAutoIn::IDD, pParent)
	, m_schem(_T(""))
	, m_years(0)
{

}

DlgAutoIn::~DlgAutoIn()
{
}

void DlgAutoIn::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_CBString(pDX, IDC_AUTO_SCHEM, m_schem);
	DDX_Text(pDX, IDC_AUTO_TIME, m_years);
	DDV_MinMaxInt(pDX, m_years, 2000, 2099);
}


BEGIN_MESSAGE_MAP(DlgAutoIn, CDialog)
END_MESSAGE_MAP()


// DlgAutoIn 消息处理程序
