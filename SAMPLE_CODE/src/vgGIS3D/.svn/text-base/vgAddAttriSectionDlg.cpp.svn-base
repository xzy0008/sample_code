// vgPipeAttriDlg.cpp : 实现文件
//

#include <vgStableHeaders.h>
#include <vgGIS3D/vgAddAttriSectionDlg.h>
#include <vgKernel/vgkStringUtility.h>

#include <vgKernel/vgkSystemUtility.h>
#include <vgGIS/vgGisManager.h>
#include <vgGIS3D/vgPipeLayerAttriDlg.h>
#include <gdal/ogr_api.h>
#include <vgGIS3D/vggiDataSource.h>



// vgPipeAttriDlg 对话框
namespace vgGIS3D
{
	IMPLEMENT_DYNAMIC(vgAddSectionInfoDlg, CDialog)

	vgAddSectionInfoDlg::vgAddSectionInfoDlg(CWnd* pParent /*= NULL*/)
		: CDialog(vgAddSectionInfoDlg::IDD, pParent)
	{
		m_ogrPipeLineMap = vgGIS3D::GisManager::getSingleton().getPipeLineMap();
		m_sectionName = _T("");
		m_wndStr = _T("");
		m_initValue = _T("");
	}

	vgAddSectionInfoDlg::~vgAddSectionInfoDlg()
	{
	}

	void vgAddSectionInfoDlg::DoDataExchange(CDataExchange* pDX)
	{
		CDialog::DoDataExchange(pDX);
		DDX_Text(pDX, IDC_SECTION_NAME, m_sectionName);
		DDX_Text(pDX, IDC_DEFAULT_VALUE, m_initValue);
		DDX_Control(pDX, IDC_SECTION_TYPE, m_valueType);
	}


	BEGIN_MESSAGE_MAP(vgAddSectionInfoDlg, CDialog)
		ON_WM_CREATE()	
		ON_WM_TIMER()
		ON_WM_DESTROY()
	END_MESSAGE_MAP()


	// vgPipeAttriDlg 消息处理程序

	int vgAddSectionInfoDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
	{
		if (CDialog::OnCreate(lpCreateStruct) == -1)
		{
			AfxMessageBox("Error.");
			return -1;
		}

		return 0;
	}

	BOOL vgAddSectionInfoDlg::OnInitDialog()
	{
		CDialog::OnInitDialog();

		// TODO:  在此添加额外的初始化
		// TODO:  在此添加您专用的创建代码

		UpdateData ();

		m_valueType.AddString(_T("Integer"));
		m_valueType.AddString(_T("Double"));
		m_valueType.AddString(_T("String"));

		m_valueType.SetCurSel(0);

		// TODO: Add extra initialization here
		SetTimer(1, 100, NULL);

		return TRUE;  // return TRUE unless you set the focus to a control
		// 异常: OCX 属性页应返回 FALSE
	}

	void vgAddSectionInfoDlg::OnTimer(UINT_PTR nIDEvent)
	{
		CDialog::OnTimer(nIDEvent);
	}

	void vgAddSectionInfoDlg::OnDestroy()
	{
		CDialog::OnDestroy();

		// TODO: 在此处添加消息处理程序代码
		//delete this;
	}

	void vgAddSectionInfoDlg::OnOK()
	{
		UpdateData(true);
		if (m_sectionName == _T(""))
		{
			AfxMessageBox("字段的名字不能为空");
			return;
		}
		else
		{	
			for (int i = 0; i < vgPipeLayerAttriDlg::m_fieldNameVec.size(); i++)
			{
				if (vgPipeLayerAttriDlg::m_fieldNameVec[i] == m_sectionName)
				{
					AfxMessageBox("该字段值已经存在，请重新命名");
					return;
				}
			}

			int selID = m_valueType.GetCurSel();
			m_wndStr.GetBuffer(m_valueType.GetLBTextLen( selID ));
			m_valueType.GetLBText(m_valueType.GetCurSel(), m_wndStr);

			//if (m_initValue == _T(""))
			//{
			//	AfxMessageBox("请为该字段设置初值");
			//	return;
			//}
			if (m_initValue == _T(""))
			{
				if (m_wndStr == _T("Integer"))
				{
					m_initValue = _T("0");
				}
				else if (m_wndStr == _T("Double"))
				{
					m_initValue = _T("0.0");
				}
				else if (m_wndStr == _T("String"))
				{
					m_initValue = _T("NULL");
				}
			}

			vgPipeLayerAttriDlg::m_fieldNameVec.push_back(m_sectionName);			
		}
		UpdateData(FALSE);
		CDialog::OnOK();
		DestroyWindow();
	}


}//end namespace


