// D:\___NewVersion\vrgis\src\vgSuperPlatform\DlgPlanShpIn.cpp : 实现文件
//

#include "vgStableHeaders.h"
#include "DlgPlanShpIn.h"


// DlgPlanShpIn 对话框

IMPLEMENT_DYNAMIC(DlgPlanShpIn, CDialog)

DlgPlanShpIn::DlgPlanShpIn(CWnd* pParent /*=NULL*/)
	: CDialog(DlgPlanShpIn::IDD, pParent)
	, m_planName(_T(""))
	, m_areaFileName(_T(""))
	, m_roadFileName(_T(""))
	, m_exlcFileName(_T(""))
	, m_regionFileName(_T(""))
	, m_roadWidth(0)
{

}

DlgPlanShpIn::~DlgPlanShpIn()
{
}

void DlgPlanShpIn::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_PLANNAME, m_cplanName);
	DDX_Text(pDX, IDC_EDIT_AREA, m_careaFileName);
	DDX_Text(pDX, IDC_EDIT_ROAD, m_croadFileName);
	DDX_Text(pDX, IDC_EDIT_EXCL, m_cexlcFileName);
	DDX_Text(pDX, IDC_EDIT_REGION, m_cregionFileName);
	DDX_Text(pDX, IDC_ROAD_WIDTH, m_roadWidth);
}


BEGIN_MESSAGE_MAP(DlgPlanShpIn, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &DlgPlanShpIn::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON12, &DlgPlanShpIn::OnBnClickedButton12)
	ON_BN_CLICKED(IDC_BUTTON2, &DlgPlanShpIn::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON13, &DlgPlanShpIn::OnBnClickedButton13)
END_MESSAGE_MAP()


// DlgPlanShpIn 消息处理程序

void DlgPlanShpIn::OnBnClickedButton1()
{
	UpdateData(TRUE);
	
	// TODO: 在此添加控件通知处理程序代码
	char szFilters[]=
		"(*.shp)|*.shp|All Files (*.*)|*.*||";

	CFileDialog dlg (TRUE, "shp", "*.shp",
		OFN_FILEMUSTEXIST| OFN_HIDEREADONLY, szFilters, this);

	if( dlg.DoModal ()==IDOK )
	{
		m_areaFileName = dlg.GetPathName();
		m_careaFileName = dlg.GetPathName();

		UpdateData(false);
	}
}

void DlgPlanShpIn::OnBnClickedButton12()
{
	UpdateData(TRUE);
	
	// TODO: 在此添加控件通知处理程序代码
	char szFilters[]=
		"(*.shp)|*.shp|All Files (*.*)|*.*||";

	CFileDialog dlg (TRUE, "shp", "*.shp",
		OFN_FILEMUSTEXIST| OFN_HIDEREADONLY, szFilters, this);

	if( dlg.DoModal ()==IDOK )
	{
		m_roadFileName = dlg.GetPathName();
		m_croadFileName = dlg.GetPathName();

		UpdateData(false);
	}
}

void DlgPlanShpIn::OnBnClickedButton2()
{
	UpdateData(TRUE);

	// TODO: 在此添加控件通知处理程序代码
	char szFilters[]=
		"(*.shp)|*.shp|All Files (*.*)|*.*||";

	CFileDialog dlg (TRUE, "shp", "*.shp",
		OFN_FILEMUSTEXIST| OFN_HIDEREADONLY, szFilters, this);

	if( dlg.DoModal ()==IDOK )
	{
		m_exlcFileName = dlg.GetPathName();
		m_cexlcFileName = dlg.GetPathName();

		UpdateData(false);
	}
}

void DlgPlanShpIn::OnBnClickedButton13()
{
	UpdateData(TRUE);

	// TODO: 在此添加控件通知处理程序代码
	char szFilters[]=
		"(*.shp)|*.shp|All Files (*.*)|*.*||";

	CFileDialog dlg (TRUE, "shp", "*.shp",
		OFN_FILEMUSTEXIST| OFN_HIDEREADONLY, szFilters, this);

	if( dlg.DoModal ()==IDOK )
	{
		m_regionFileName = dlg.GetPathName();
		m_cregionFileName = dlg.GetPathName();

		UpdateData(false);
	}
}

void DlgPlanShpIn::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类
	UpdateData(TRUE);

	m_areaFileName = m_careaFileName.GetString();
	m_regionFileName = m_cregionFileName.GetString();
	m_roadFileName = m_croadFileName.GetString();
	m_exlcFileName = m_cexlcFileName.GetString();

	if (m_cplanName.GetLength() == 0)
	{
		AfxMessageBox("方案名不能为空.");

		return ;
	}

	CDialog::OnOK();
}
