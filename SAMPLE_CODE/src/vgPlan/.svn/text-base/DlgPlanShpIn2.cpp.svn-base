// D:\___NewVersion\vrgis\src\vgSuperPlatform\DlgPlanShpIn2.cpp : 实现文件
//

#include <vgStableHeaders.h>
#include "vgplan/DlgPlanShpIn2.h"
//#include <vgShape/vgshShapeManager.h>
#include <vgKernel/vgkPluginManager.h>
#include <vgShape/vgshDefinition.h>

#include <vgShape/vgshDataSource.h>

#include <vgKernel/vgkStringUtility.h>

// DlgPlanShpIn2 对话框

namespace vgPlan
{
	IMPLEMENT_DYNAMIC(DlgPlanShpIn2, CDialog)

		DlgPlanShpIn2::DlgPlanShpIn2(CWnd* pParent /*=NULL*/)
		: CDialog(DlgPlanShpIn2::IDD, pParent)
		, m_planName(_T(""))
		, m_planShpName(_T(""))
	{

	}

	DlgPlanShpIn2::~DlgPlanShpIn2()
	{
	}

	void DlgPlanShpIn2::DoDataExchange(CDataExchange* pDX)
	{
		CDialog::DoDataExchange(pDX);
		DDX_Text(pDX, IDC_PLANNAME, m_planName);
		DDX_CBString(pDX, IDC_PLANCOMBO, m_planShpName);
	}


	BEGIN_MESSAGE_MAP(DlgPlanShpIn2, CDialog)
		ON_BN_CLICKED(IDOK, &DlgPlanShpIn2::OnBnClickedOk)
	END_MESSAGE_MAP()


	// DlgPlanShpIn2 消息处理程序

	BOOL DlgPlanShpIn2::OnInitDialog()
	{
		CDialog::OnInitDialog();

		// TODO:  在此添加额外的初始化

		CComboBox *pCombo = (CComboBox*)GetDlgItem(IDC_PLANCOMBO);

		if (pCombo == NULL)
		{
			return FALSE;
		}

		//vgShape::DataSourcePtrMap *pDataSource = vgShape::ShapeManager::getSingleton().getDataSources();
		using namespace vgKernel;
		vgKernel::Plugin* plug = PluginManager::getSingleton().getPluginRef( VGSH_DLL_NAME );

		if ( plug == NULL )
		{
			return FALSE;
		}

		VGK_DLL_DECLARE_CLASSFUNC( plug, ShapeManager, getDataSources, pfn1 );

		assert( pfn1 != NULL);

		vgShape::DataSourcePtrMap *pDataSource  = (vgShape::DataSourcePtrMap*)pfn1( );

		vgShape::DataSourcePtrMap::iterator iter = pDataSource->begin();

		vgShape::DataSourcePtrMap::iterator iter_end = pDataSource->end();

		for ( ; iter != iter_end ;++iter )
		{
			vgShape::DataSourcePtr pds = iter->second;
			string name = vgKernel::StringUtility::getFilenameFromAbsolutePath(
				pds->getFilePath() );

			pCombo->AddString(name.c_str());
		}

		UpdateData(FALSE);

		return TRUE;  // return TRUE unless you set the focus to a control
	}

	void DlgPlanShpIn2::OnBnClickedOk()
	{
		// TODO: 在此添加控件通知处理程序代码
		UpdateData(TRUE);

		OnOK();
	}

	string DlgPlanShpIn2::getPlanName()
	{
		return m_planName.GetString();
	}

	string DlgPlanShpIn2::getShpName()
	{
		string fullName = m_planShpName.GetString();

		return fullName.substr(0, fullName.length() - 4);
	}

}