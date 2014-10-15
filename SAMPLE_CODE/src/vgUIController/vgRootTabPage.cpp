// vgRootTabPage.cpp : 实现文件
//

#include <vgStableHeaders.h>


#include <vgUIController/vgRootTabPage.h>


// vgRootTabPage 对话框

IMPLEMENT_DYNAMIC(vgRootTabPage, CDialog)

vgRootTabPage::vgRootTabPage(CWnd* pParent /*=NULL*/)
	: CDialog(vgRootTabPage::IDD, pParent)
{

}

vgRootTabPage::~vgRootTabPage()
{
}

void vgRootTabPage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

string vgRootTabPage::GetTitle()
{
	return "VRGIS";
}

CWnd* vgRootTabPage::GetWnd()
{
	return this;
}

BEGIN_MESSAGE_MAP(vgRootTabPage, CDialog)
END_MESSAGE_MAP()


// vgRootTabPage 消息处理程序
