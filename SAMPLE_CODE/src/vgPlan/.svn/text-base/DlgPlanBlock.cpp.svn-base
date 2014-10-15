// D:\___NewVersion\vrgis\src\vgSuperPlatform\DlgPlanBlock.cpp : 实现文件
//

#include <vgStableHeaders.h>
#include "vgplan/DlgPlanBlock.h"
#include <vgPlan/vgPlanmanager.h>

// DlgPlanBlock 对话框

namespace vgPlan
{
	IMPLEMENT_DYNAMIC(DlgPlanBlock, CDialog)

		DlgPlanBlock::DlgPlanBlock(CWnd* pParent /*=NULL*/)
		: CDialog(DlgPlanBlock::IDD, pParent)
		, m_blockX(0)
		, m_blockY(0)
		, m_aliasX(20)
		, m_aliasY(20)
		, m_maxHeight(0)
		, m_minHeight(0)
		, m_heightPerFloor(3)
		, m_rotateDgree(0)
		, m_areaLat(40)
		, m_planYear(2010)
		, m_planMonth(1)
		, m_planDay(21)
		, m_sumTime(2)
		, m_aliasR(15)
		, m_floorArea(0)
		, m_schemName(_T(""))
	{

	}

	DlgPlanBlock::~DlgPlanBlock()
	{
	}

	void DlgPlanBlock::DoDataExchange(CDataExchange* pDX)
	{
		CDialog::DoDataExchange(pDX);
		DDX_Text(pDX, IDC_BLOCKX, m_blockX);
		DDX_Text(pDX, IDC_BLOCKY, m_blockY);
		DDX_Text(pDX, IDC_ALIASX, m_aliasX);
		DDX_Text(pDX, IDC_ALIASY, m_aliasY);
		DDX_Text(pDX, IDC_MAXHEIGHT, m_maxHeight);
		DDX_Text(pDX, IDC_MINHEIGHT, m_minHeight);
		DDX_Text(pDX, IDC_FLOORHEIGHT, m_heightPerFloor);
		DDX_Text(pDX, IDC_ROTATE, m_rotateDgree);
		DDX_Text(pDX, IDC_AREALAT, m_areaLat);
		DDX_Text(pDX, IDC_PALN_YEAR, m_planYear);
		DDX_Text(pDX, IDC_PALN_MONTH, m_planMonth);
		DDX_Text(pDX, IDC_PLAN_DAY, m_planDay);
		DDX_Text(pDX, IDC_SUNTIME, m_sumTime);
		DDX_Text(pDX, IDC_ALIASR, m_aliasR);
		DDX_Text(pDX, IDC_FLOORAREA, m_floorArea);
		DDX_Text(pDX, IDC_SHCEMNAME, m_schemName);
	}


	BEGIN_MESSAGE_MAP(DlgPlanBlock, CDialog)
		ON_CBN_SELCHANGE(IDC_COMBO2, &DlgPlanBlock::OnCbnSelchangeCombo2)
	END_MESSAGE_MAP()


	// DlgPlanBlock 消息处理程序

	BOOL DlgPlanBlock::OnInitDialog()
	{
		CDialog::OnInitDialog();


		// TODO:  在此添加额外的初始化
		vgPlan::vgPlanScene *pScene = vgPlan::vgPlanManager::getSingleton().getActiveScene();

		if (pScene != NULL)
		{
			vgPlan::BlockParam blockParam = pScene->getBlockParam();

			if (blockParam.blockX != 0)
			{
				m_blockX = blockParam.blockX;
			}

			if (blockParam.blockY != 0)
			{
				m_blockY = blockParam.blockY;
			}

			if (blockParam.aliasX != 0)
			{
				m_aliasX = blockParam.aliasX;
			}

			if (blockParam.aliasY != 0)
			{
				m_aliasY = blockParam.aliasY;
			}

			if (blockParam.aliasR != 0)
			{
				m_aliasR = blockParam.aliasR;
			}

			if (abs(blockParam.floorAreaRatio - 0) > 1e-3 )
			{
				m_floorArea = blockParam.floorAreaRatio;
			}

			if (blockParam.heightPerFloor != 0)
			{
				m_heightPerFloor = blockParam.heightPerFloor;
			}

			if (blockParam.maxHeight != 0)
			{
				m_maxHeight = blockParam.maxHeight;
			}

			if (blockParam.minHeight != 0)
			{
				m_minHeight = blockParam.minHeight;
			}


			m_schemName = pScene->getName().c_str();
		}

		CComboBox* pCombo = (CComboBox*)GetDlgItem(IDC_SCHEM_SELCOMBO);

		if (pCombo == NULL)
		{
			return FALSE;
		}

		pCombo->Clear();

		stringstream outSting;
		int nameCnt = vgPlan::vgPlanManager::getSingleton().getNumOfScene();

		for (int i=0; i<nameCnt; i++)
		{
			outSting.str("");
			outSting << vgPlan::vgPlanManager::getSingleton().getSceneNameById(i);

			pCombo->AddString(outSting.str().c_str());
		}

		pCombo->SelectString(-1, m_schemName);

		UpdateData(FALSE);

		return TRUE;  // return TRUE unless you set the focus to a control
		// 异常: OCX 属性页应返回 FALSE
	}

	void DlgPlanBlock::OnCbnSelchangeCombo2()
	{
		// TODO: 在此添加控件通知处理程序代码

		CComboBox* pCombo = (CComboBox*)GetDlgItem(IDC_SCHEM_SELCOMBO);

		if (pCombo == NULL)
		{
			AfxMessageBox("Error on sel changing.");
			return ;
		}

		int index = pCombo->GetCurSel();
		CString comboString;
		pCombo->GetLBText(index, comboString);

		// vgPlan::vgPlanManager::getSingleton().setActiveSceneById(index);

		vgPlan::vgPlanManager::getSingleton().setActiveSceneByName(comboString.GetString());

		UpdateData(TRUE);
	}
}
