
#include <vgStableHeaders.h>
#include "vgplan/DlgPlanOutput.h"
#include <vgPlan/vgPlanmanager.h>

#include <vgShape/vgshShapeManager.h>

namespace vgPlan
{
	// DlgPlanOutput 对话框

	IMPLEMENT_DYNAMIC(DlgPlanOutput, CDialog)

		DlgPlanOutput::DlgPlanOutput(CWnd* pParent /*=NULL*/)
		: CDialog(DlgPlanOutput::IDD, pParent)
		, m_blockX(0)
		, m_blockY(0)
		, m_blockCnt(0)
		, m_floorAreaRadio(0)
		, m_schemName(_T(""))
		, m_red(0)
		, m_green(0)
		, m_blue(0)
		, m_alpha(0)
	{
		vgPlan::vgPlanScene *pScene = vgPlan::vgPlanManager::getSingleton().getActiveScene();

		if (pScene != NULL)
		{
			m_maxFloor = pScene->getMaxFloor();
			m_minFloor = pScene->getMinFloor();

			// lss add 2009年5月13日11:09:43
			m_red = vgPlan::vgPlanManager::getSingleton().getActiveScene()->getBlockRed();
			m_blue = vgPlan::vgPlanManager::getSingleton().getActiveScene()->getBlockBlue();
			m_green = vgPlan::vgPlanManager::getSingleton().getActiveScene()->getBlockGreen();
			m_alpha = vgPlan::vgPlanManager::getSingleton().getActiveScene()->getBlockAlpha();
		}	
		else
		{
			m_maxFloor = 0;
			m_minFloor = 0;
		}

		//m_red = vgPlan::vgPlanManager::getSingleton().getActiveScene()->getBlockRed();
		//m_blue = vgPlan::vgPlanManager::getSingleton().getActiveScene()->getBlockBlue();
		//m_green = vgPlan::vgPlanManager::getSingleton().getActiveScene()->getBlockGreen();
		//m_alpha = vgPlan::vgPlanManager::getSingleton().getActiveScene()->getBlockAlpha();
	}

	DlgPlanOutput::~DlgPlanOutput()
	{

	}

	void DlgPlanOutput::DoDataExchange(CDataExchange* pDX)
	{
		CDialog::DoDataExchange(pDX);
		DDX_Control(pDX, IDC_FLOOR, m_floorComboBox);
		DDX_Text(pDX, IDC_OUT_BLOCKX, m_blockX);
		DDX_Text(pDX, IDC_OUT_BLOCKY, m_blockY);
		DDX_Text(pDX, IDC_OUT_BLOCKCNT, m_blockCnt);
		DDX_Text(pDX, IDC_OUT_FARADIO, m_floorAreaRadio);
		DDX_Text(pDX, IDC_OUT_SCHEMNAME, m_schemName);
		DDX_Text(pDX, IDC_PLAN_COLORR, m_red);
		DDX_Text(pDX, IDC_PLAN_COLORG, m_green);
		DDX_Text(pDX, IDC_PLAN_COLORB, m_blue);
		DDX_Text(pDX, IDC_PLAN_COLORALPHA, m_alpha);
	}


	BEGIN_MESSAGE_MAP(DlgPlanOutput, CDialog)
		ON_CBN_SELCHANGE(IDC_FLOOR, &DlgPlanOutput::OnCbnSelchangeFloor)
		//	ON_EN_CHANGE(IDC_EDIT7, &DlgPlanOutput::OnEnChangeEdit7)
		ON_BN_CLICKED(IDC_RADIO1, &DlgPlanOutput::OnBnClickedRadio1)
		ON_BN_CLICKED(IDC_RADIO3, &DlgPlanOutput::OnBnClickedRadio3)
		ON_BN_CLICKED(IDC_RADIO2, &DlgPlanOutput::OnBnClickedRadio2)
		ON_CBN_SELCHANGE(IDC_SCHEM_OUTCOMBO, &DlgPlanOutput::OnCbnSelchangeCombo1)
		ON_BN_CLICKED(IDC_EXP_SHP, &DlgPlanOutput::OnBnClickedExpShp)
		ON_EN_CHANGE(IDC_EDIT1, &DlgPlanOutput::OnEnChangeEdit1)
		ON_EN_CHANGE(IDC_PLAN_COLORR, &DlgPlanOutput::OnEnChangePlanColorr)
		ON_EN_CHANGE(IDC_PLAN_COLORG, &DlgPlanOutput::OnEnChangePlanColorg)
		ON_EN_CHANGE(IDC_PLAN_COLORB, &DlgPlanOutput::OnEnChangePlanColorb)
		ON_EN_CHANGE(IDC_PLAN_COLORALPHA, &DlgPlanOutput::OnEnChangePlanColoralpha)
	END_MESSAGE_MAP()

	BOOL DlgPlanOutput::OnInitDialog()
	{
		CComboBox* pCombo = (CComboBox*)GetDlgItem(IDC_FLOOR);

		pCombo->ResetContent();

		vgPlan::vgPlanScene *pScene = vgPlan::vgPlanManager::getSingleton().getActiveScene();

		//add by zzy 2009/10/27  13:29  solve bug.
		if ( pScene == NULL )
		{
			return false;
		}

		if (pScene != NULL)
		{
			stringstream outSting;

			for (int i=m_minFloor; i<=m_maxFloor; i++)
			{
				outSting.str("");
				outSting << i << "层" ;

				pCombo->AddString(outSting.str().c_str());
			}

			m_schemName = pScene->getName().c_str();
		}

		stringstream sString;

		if (pScene->getCurrentFloor() >= m_minFloor)   //这里出错
		{
			sString << pScene->getCurrentFloor() << "层";
			pCombo->SelectString(-1, sString.str().c_str());
		}

		CComboBox* pComboSchem = (CComboBox*)GetDlgItem(IDC_SCHEM_OUTCOMBO);

		if (pComboSchem == NULL)
		{
			return FALSE;
		}

		pComboSchem->Clear();

		stringstream outSting;
		int nameCnt = vgPlan::vgPlanManager::getSingleton().getNumOfScene();

		for (int i=0; i<nameCnt; i++)
		{
			outSting.str("");
			outSting << vgPlan::vgPlanManager::getSingleton().getSceneNameById(i);

			pComboSchem->AddString(outSting.str().c_str());
		}

		pComboSchem->SelectString(-1, m_schemName);

		UpdateData(FALSE);

		/*pCombo->SetCurSel(0);*/

		return TRUE;
	}
	// DlgPlanOutput 消息处理程序

	void DlgPlanOutput::OnCbnSelchangeFloor()
	{
		// TODO: 在此添加控件通知处理程序代码
		int currentFloor = m_minFloor + m_floorComboBox.GetCurSel();

		if (currentFloor < m_minFloor || currentFloor > m_maxFloor)
		{
			AfxMessageBox("Error Floor Number");

			return ;
		}
		// vgPlan::vgPlanManager::getSingleton().getLastScenePtr()->setCurrentSchemFloor(currentFloor);

		vgPlan::vgPlanScene *pScene = vgPlan::vgPlanManager::getSingleton().getActiveScene();

		if (pScene != NULL && currentFloor > 0)
		{
			pScene->setCurrentSchemFloor(currentFloor);

			m_blockCnt = pScene->getNumOfBuilding(currentFloor);

			m_blockX = pScene->getBlockParam().blockX;
			m_blockY = pScene->getBlockParam().blockY;

			m_floorAreaRadio = pScene->getFloorAreaRatio(currentFloor);	

			// vgShape::ShapeManager::getSingleton().quitQuery();
		}

		UpdateData(FALSE);
	}

	void DlgPlanOutput::OnCancel()
	{
		// TODO: 在此添加专用代码和/或调用基类

		CDialog::OnCancel();
		/*DestroyWindow();*/
	}

	void DlgPlanOutput::OnEnChangeEdit7()
	{
		// TODO:  如果该控件是 RICHEDIT 控件，则它将不会
		// 发送该通知，除非重写 CDialog::OnInitDialog()
		// 函数并调用 CRichEditCtrl().SetEventMask()，
		// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

		// TODO:  在此添加控件通知处理程序代码
	}

	void DlgPlanOutput::OnBnClickedRadio1()
	{
		// TODO: 在此添加控件通知处理程序代码

		vgPlan::vgPlanScene *pScene = vgPlan::vgPlanManager::getSingleton().getActiveScene();

		int currentFloor = m_minFloor + m_floorComboBox.GetCurSel();

		if (pScene != NULL && currentFloor > 0)
		{
			// pScene->matchFloorAreaRatio(0);
			OnCbnSelchangeFloor();

			m_floorAreaRadio = vgPlan::vgPlanManager::getSingleton().getActiveScene()->getFloorAreaRatio(currentFloor);
		}

		UpdateData(FALSE);
	}

	void DlgPlanOutput::OnBnClickedRadio3()
	{
		// TODO: 在此添加控件通知处理程序代码

		vgPlan::vgPlanScene *pScene = vgPlan::vgPlanManager::getSingleton().getActiveScene();

		int currentFloor = m_minFloor + m_floorComboBox.GetCurSel();

		if (pScene != NULL && currentFloor > 0)
		{
			pScene->matchFloorAreaRatio(1);

			m_floorAreaRadio = vgPlan::vgPlanManager::getSingleton().getActiveScene()->getFloorAreaRatio(currentFloor);
		}


		UpdateData(FALSE);
	}

	void DlgPlanOutput::OnBnClickedRadio2()
	{
		// TODO: 在此添加控件通知处理程序代码

		vgPlan::vgPlanScene *pScene = vgPlan::vgPlanManager::getSingleton().getActiveScene();

		int currentFloor = m_minFloor + m_floorComboBox.GetCurSel();

		if (pScene != NULL && currentFloor > 0)
		{
			pScene->matchFloorAreaRatio(2);

			m_floorAreaRadio = vgPlan::vgPlanManager::getSingleton().getActiveScene()->getFloorAreaRatio(currentFloor);
		}

		UpdateData(FALSE);
	}

	void DlgPlanOutput::OnCbnSelchangeCombo1()
	{
		// TODO: 在此添加控件通知处理程序代码
		CComboBox* pCombo = (CComboBox*)GetDlgItem(IDC_SCHEM_OUTCOMBO);

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

		// 更新楼层信息
		pCombo = (CComboBox*)GetDlgItem(IDC_FLOOR);

		if (pCombo == NULL)
		{
			return ;
		}

		pCombo->ResetContent();

		vgPlan::vgPlanScene *pScene = vgPlan::vgPlanManager::getSingleton().getActiveScene();

		if (pScene != NULL)
		{
			stringstream outSting;
			m_minFloor = pScene->getMinFloor();
			m_maxFloor = pScene->getMaxFloor();

			for (int i=m_minFloor; i<=m_maxFloor; i++)
			{
				outSting.str("");
				outSting << i << "层" ;

				pCombo->AddString(outSting.str().c_str());
			}

			m_schemName = pScene->getName().c_str();

		//	vgShape::ShapeManager::getSingleton().quitQuery();

		}


		m_red = vgPlan::vgPlanManager::getSingleton().getActiveScene()->getBlockRed();
		m_blue = vgPlan::vgPlanManager::getSingleton().getActiveScene()->getBlockBlue();
		m_green = vgPlan::vgPlanManager::getSingleton().getActiveScene()->getBlockGreen();
		m_alpha = vgPlan::vgPlanManager::getSingleton().getActiveScene()->getBlockAlpha();

		UpdateData(FALSE);
	}

	void DlgPlanOutput::OnBnClickedExpShp()
	{
		// TODO: 在此添加控件通知处理程序代码
		char szFilters[]=
			"(*.shp)|*.shp|All Files (*.*)|*.*||";

		CFileDialog dlg (FALSE, "shp", "*.shp",
			OFN_FILEMUSTEXIST| OFN_HIDEREADONLY, szFilters, this);

		if (dlg.DoModal() == IDOK)
		{
			string filePath = dlg.GetPathName();

			vgPlan::vgPlanScene *pScene = vgPlan::vgPlanManager::getSingleton().getActiveScene();

			if (pScene != NULL)
			{
				DeleteFile(filePath.c_str());

				if (pScene->saveCurrentSchemToShpFile(filePath))
				{
					AfxMessageBox("保存完成.");

					return ;
				}
			}

			AfxMessageBox("保存失败.");		
		}
	}

	void DlgPlanOutput::OnEnChangeEdit1()
	{
		// TODO:  如果该控件是 RICHEDIT 控件，则它将不会
		// 发送该通知，除非重写 CDialog::OnInitDialog()
		// 函数并调用 CRichEditCtrl().SetEventMask()，
		// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

		// TODO:  在此添加控件通知处理程序代码
	}

	void DlgPlanOutput::OnEnChangePlanColorr()
	{
		// TODO:  如果该控件是 RICHEDIT 控件，则它将不会
		// 发送该通知，除非重写 CDialog::OnInitDialog()
		// 函数并调用 CRichEditCtrl().SetEventMask()，
		// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

		// TODO:  在此添加控件通知处理程序代码
		UpdateData();

		vgPlan::vgPlanManager::getSingleton().getActiveScene()->setBlockColor(m_red, m_green, m_blue, m_alpha);
	}


	void DlgPlanOutput::OnEnChangePlanColorg()
	{
		// TODO:  如果该控件是 RICHEDIT 控件，则它将不会
		// 发送该通知，除非重写 CDialog::OnInitDialog()
		// 函数并调用 CRichEditCtrl().SetEventMask()，
		// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

		// TODO:  在此添加控件通知处理程序代码
		UpdateData();

		vgPlan::vgPlanManager::getSingleton().getActiveScene()->setBlockColor(m_red, m_green, m_blue, m_alpha);
	}

	void DlgPlanOutput::OnEnChangePlanColorb()
	{
		// TODO:  如果该控件是 RICHEDIT 控件，则它将不会
		// 发送该通知，除非重写 CDialog::OnInitDialog()
		// 函数并调用 CRichEditCtrl().SetEventMask()，
		// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

		// TODO:  在此添加控件通知处理程序代码
		UpdateData();

		vgPlan::vgPlanManager::getSingleton().getActiveScene()->setBlockColor(m_red, m_green, m_blue, m_alpha);
	}

	void DlgPlanOutput::OnEnChangePlanColoralpha()
	{
		// TODO:  如果该控件是 RICHEDIT 控件，则它将不会
		// 发送该通知，除非重写 CDialog::OnInitDialog()
		// 函数并调用 CRichEditCtrl().SetEventMask()，
		// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

		// TODO:  在此添加控件通知处理程序代码
		UpdateData();

		vgPlan::vgPlanManager::getSingleton().getActiveScene()->setBlockColor(m_red, m_green, m_blue, m_alpha);
	}

}
