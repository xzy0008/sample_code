// D:\___visualVersion\trunkDLL\src\vgGIS3D\vggiDlgOutRoute.cpp : 实现文件
//

#include <vgStableHeaders.h>
#include <vgGis3d/vggiDlgOutRoute.h>


// vgDlgOutRoute 对话框

IMPLEMENT_DYNAMIC(vgDlgOutRoute, CDialog)

vgDlgOutRoute::vgDlgOutRoute(CWnd* pParent /*=NULL*/)
	: CDialog(vgDlgOutRoute::IDD, pParent)
{

}

vgDlgOutRoute::~vgDlgOutRoute()
{
}

void vgDlgOutRoute::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_LAYER_NAME, m_layerName);
	DDX_Text(pDX, IDC_FILEPATH,	 m_savePath);
}


BEGIN_MESSAGE_MAP(vgDlgOutRoute, CDialog)
	ON_BN_CLICKED(IDC_SEL_FILE, &vgDlgOutRoute::OnBnClickedSelFile)
	ON_BN_CLICKED(IDOK, &vgDlgOutRoute::OnBnClickedOk)
END_MESSAGE_MAP()


// vgDlgOutRoute 消息处理程序

void vgDlgOutRoute::OnBnClickedSelFile()
{
	// TODO: 在此添加控件通知处理程序代码
	char szFilters[]=
		"shp files(*.shp)|*.shp|";

	CFileDialog fileDialog (TRUE, "shp", NULL,
		OFN_HIDEREADONLY, szFilters, this);


	if( fileDialog.DoModal ()==IDOK )
	{
		m_savePath = fileDialog.GetPathName();
	}

	UpdateData(FALSE);

}

void vgDlgOutRoute::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);

	if (m_savePath.GetLength() == 0 || m_layerName.GetLength() == 0)
	{
		AfxMessageBox("输入不能为空,请重新输入.");
	
		return ;
	}
	OnOK();
}
