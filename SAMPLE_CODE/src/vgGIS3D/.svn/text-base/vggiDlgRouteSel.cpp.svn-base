// D:\___visualVersion\trunkDLL\src\vgGIS3D\vggiDlgRouteSel.cpp : 实现文件
//

#include <vgStableHeaders.h>
#include <vgGIS3D\vggiDlgRouteSel.h>
#include <vgGIS3D\vggiGisDataManager.h>

// vgDlgRouteSel 对话框

namespace vgGIS3D
{
	IMPLEMENT_DYNAMIC(vgDlgRouteSel, CDialog)

	vgDlgRouteSel::vgDlgRouteSel(CWnd* pParent /*=NULL*/)
		: CDialog(vgDlgRouteSel::IDD, pParent)
	{

	}

	vgDlgRouteSel::~vgDlgRouteSel()
	{
	}

	void vgDlgRouteSel::DoDataExchange(CDataExchange* pDX)
	{
		CDialog::DoDataExchange(pDX);
	}


	BEGIN_MESSAGE_MAP(vgDlgRouteSel, CDialog)
	END_MESSAGE_MAP()


	// vgDlgRouteSel 消息处理程序

}

BOOL vgGIS3D::vgDlgRouteSel::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	vgGIS3D::DataSourcePtrMap *pDataSource  = vgGIS3D::GisDataManager::getSingleton().getDataSources();

	vgGIS3D::DataSourcePtrMap::iterator iter = pDataSource->begin();

	vgGIS3D::DataSourcePtrMap::iterator iter_end = pDataSource->end();

	CComboBox *pCombo = dynamic_cast<CComboBox*>(GetDlgItem(IDC_ROUTE_SEL_COMBO));

	if (pCombo == NULL)
	{
		AfxMessageBox("Get Item Failed.");
	
		return FALSE;
	}

	for ( ; iter != iter_end ;++iter )
	{
		vgGIS3D::DataSourcePtr pds = iter->second;

		pCombo->AddString(pds->getSourcePath().c_str());
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
