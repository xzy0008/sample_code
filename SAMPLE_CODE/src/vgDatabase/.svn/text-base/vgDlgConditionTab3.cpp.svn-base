// DBConditionTab3.cpp : 实现文件
//

#include <vgStableHeaders.h>
//#include <framework.h>

/*#include <vgDatabase/vgDlgDBConnect.h>*/
#include <vgDatabase/vgDlgConditionTab3.h>
#include "vgDatabase/vgdDatabaseManager.h"
#include "vgDatabase/vgdOracleConnector.h"
#include "vgDatabase/vgdBasedConnector.h"

#include <vgDatabase/vgDlgCondition.h>
#include <vgDatabase/CUnrarDLL.h>



// DBConditionTab3 对话框

IMPLEMENT_DYNAMIC(DBConditionTab3, CDialog)

DBConditionTab3::DBConditionTab3(CWnd* pParent /*=NULL*/)
	: CDialog(DBConditionTab3::IDD, pParent)
{
	m_pParent = pParent;
}

DBConditionTab3::~DBConditionTab3()
{

}

void DBConditionTab3::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EXPLORER1, m_htmlControl);
}


BEGIN_MESSAGE_MAP(DBConditionTab3, CDialog)
	ON_WM_CREATE()
	ON_BN_CLICKED(IDOK, &DBConditionTab3::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &DBConditionTab3::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON1, &DBConditionTab3::OnBnClickedButton1)
END_MESSAGE_MAP()


// DBConditionTab3 消息处理程序

void DBConditionTab3::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	//OnOK();
}

void DBConditionTab3::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	DBCondition *pDialog = (DBCondition*)m_pParent;

	if (pDialog)
	{
		pDialog->Quit();
	}
}


int DBConditionTab3::OnCreate( LPCREATESTRUCT lpCreateStruct )
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
		
	return 0;
}

BOOL DBConditionTab3::OnInitDialog()
{
	CDialog::OnInitDialog();

	return TRUE;  // return TRUE unless you set the focus to a control
}


void DBConditionTab3::OnBnClickedButton1()//  [12/4/2008 yuxin]
{
	// TODO: 在此添加控件通知处理程序代码

	DBCondition *pParent = (DBCondition*)m_pParent;
	if (pParent != NULL)
	{
		pParent->SetActiveTab(1);
	}
	
}

