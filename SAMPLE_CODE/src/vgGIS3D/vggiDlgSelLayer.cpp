// D:\___visualVersion\trunkDLL\src\vgGIS3D\vggiDlgSelLayer.cpp : 实现文件
//

#include <vgStableHeaders.h>
#include <vgGIS3D\vggiDlgSelLayer.h>

#include <vgGIS3D/vggiGisDataManager.h>
#include <vgGIS3D/vggiDataSource.h>

#include <vgKernel/vgkSystemUtility.h>


// vgDlgSelLayer 对话框

namespace vgGIS3D
{
	IMPLEMENT_DYNAMIC(vgDlgSelLayer, CDialog)

		vgDlgSelLayer::vgDlgSelLayer(CWnd* pParent /*=NULL*/)
		: CDialog(vgDlgSelLayer::IDD, pParent)
	{

	}

	vgDlgSelLayer::~vgDlgSelLayer()
	{
	}

	void vgDlgSelLayer::DoDataExchange(CDataExchange* pDX)
	{
		CDialog::DoDataExchange(pDX);
		DDX_Control(pDX, IDC_SEL_LAYER_COMBO, m_layerNameCombo);
	}


	BEGIN_MESSAGE_MAP(vgDlgSelLayer, CDialog)
	END_MESSAGE_MAP()


	// vgDlgSelLayer 消息处理程序

	string vgDlgSelLayer::getSelectLayerName()
	{
		// UpdateData(TRUE);
		return m_layerNameStr;
	}

	BOOL vgDlgSelLayer::OnInitDialog()
	{
		CDialog::OnInitDialog();

		// TODO:  在此添加额外的初始化
		// TODO:  在此添加额外的初始化
		vgGIS3D::DataSourcePtrMap *pDataSource  = vgGIS3D::GisDataManager::getSingleton().getDataSources();

		vgGIS3D::DataSourcePtrMap::iterator iter = pDataSource->begin();

		vgGIS3D::DataSourcePtrMap::iterator iter_end = pDataSource->end();

		int nCount = 0;
		for ( ; iter != iter_end ;++iter )
		{
			vgGIS3D::DataSourcePtr pds = iter->second;

			LayerPtrVector *pVec = pds->getLayerPtrVector();
			
			for (int i=0; i<pVec->size(); i++)
			{
				m_layerNameCombo.AddString(pVec->at(i)->getName().c_str());
				nCount++;
			}
		}

		if(nCount!=0)
		{
			m_layerNameCombo.SetCurSel(0);
		}

		UpdateData(FALSE);

		return TRUE;  // return TRUE unless you set the focus to a control
		// 异常: OCX 属性页应返回 FALSE
	}

}



void vgGIS3D::vgDlgSelLayer::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类
	CString wndStr;

	int nSelIndex = 0;
	nSelIndex = m_layerNameCombo.GetCurSel();
	if ( -1 == nSelIndex )
	{
		int nStatus = vgKernel::SystemUtility::talkWithModelDialog(
			"没有选中图层，是否重新选择？");
		if ( IDYES != nStatus )
		{
			CDialog::OnOK();
		}
	
		return;
	}

	wndStr.GetBuffer(m_layerNameCombo.GetLBTextLen( nSelIndex ));
	m_layerNameCombo.GetLBText(m_layerNameCombo.GetCurSel(), wndStr);

	m_layerNameStr = wndStr.GetString(); 

	CDialog::OnOK();
}
