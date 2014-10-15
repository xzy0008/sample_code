// CommandWnd.cpp : implementation file
/*
** Created by Lesky Zhou 
*/

#include <vgStableHeaders.h>
#if 0
#include "CommandWnd.h"

#include <vgPlan/DlgPlanShpIn2.h>
#include <vgPlan/DlgPlanOutput.h>
#include <vgShape/vgshShapeManager.h>
#include <vgPlan/vgPlanmanager.h>
#include <vgKernel/vgkRendererManager.h>
#include <vgPlan/DlgPlanBlock.h>

// 主菜单显示的TEXT
std::string s_menuName = "小区规划(&P)";
UINT s_menuPosition = -1;

// 每一个菜单的事件ID, 加载的时候动态生成事件ID
const static UINT ID_VGP_DLL_NEWPLAN		= ::RegisterWindowMessage( _T("ID_VGP_DLL_NEWPLAN") )  ;
const static UINT ID_VGP_DLL_NEWAREA		= ::RegisterWindowMessage( _T("ID_VGP_DLL_NEWAREA") )  ;
const static UINT ID_VGP_DLL_FROMPLAN		= ::RegisterWindowMessage( _T("ID_VGP_DLL_FROMPLAN") )  ;
const static UINT ID_VGP_DLL_SHOWPLAN		= ::RegisterWindowMessage( _T("ID_VGP_DLL_SHOWPLAN") )  ;
const static UINT ID_VGP_DLL_QUERYGREENRATIO     = ::RegisterWindowMessage( _T("ID_VGP_DLL_QUERYGREENRATIO") ) ;
const static UINT ID_VGP_DLL_QUERYPLOTRATIO      = ::RegisterWindowMessage( _T("ID_VGP_DLL_QUERYPLOTATIO") ) ;
const static UINT ID_VGP_DLL_EDITMODE		= ::RegisterWindowMessage( _T("ID_VGP_DLL_EDITMODE") )  ;

IMPLEMENT_DYNAMIC(CCommandWnd, CWnd)
CCommandWnd::CCommandWnd()
{
}

CCommandWnd::~CCommandWnd()
{
}

BEGIN_MESSAGE_MAP(CCommandWnd, CWnd)
	ON_REGISTERED_MESSAGE( ID_VGP_DLL_NEWPLAN, OnVgpNewPlan ) 
	ON_REGISTERED_MESSAGE( ID_VGP_DLL_NEWAREA, OnVgpNewArea ) 
	ON_REGISTERED_MESSAGE( ID_VGP_DLL_FROMPLAN, OnVgpFromPlan ) 
	ON_REGISTERED_MESSAGE( ID_VGP_DLL_SHOWPLAN, OnVgpShowPlan ) 
	ON_REGISTERED_MESSAGE( ID_VGP_DLL_QUERYGREENRATIO, OnVgpQueryGreenRatio )
	ON_REGISTERED_MESSAGE( ID_VGP_DLL_QUERYPLOTRATIO, OnVgpQueryPlotRatio )
	ON_REGISTERED_MESSAGE( ID_VGP_DLL_EDITMODE, OnVgpEditMode)
END_MESSAGE_MAP()

// CCommandWnd message handlers
LRESULT CCommandWnd::OnVgpNewPlan( WPARAM wParam, LPARAM lParam )
{

	vgPlan::DlgPlanShpIn2 dlg;

	// this->SetTimer(1, 150, NULL);

	if ( dlg.DoModal() != IDOK )
	{
		this->SetTimer(1, 15, NULL);

		return 0;
	}
	// this->SetTimer(1, 15, NULL);

	vgShape::Layer* pLayer = vgShape::ShapeManager::getSingleton().getLayerByShortName(dlg.getShpName());
	if (pLayer == NULL)
	{
		AfxMessageBox("未能创建Ground.");
		return 0;
	}

	vgPlan::vgPlanManager::getSingleton().addNewScene(dlg.getPlanName());


	if ( !vgPlan::vgPlanManager::getSingleton().getActiveScene()->addBuildingAreaFromLayer( dlg.getShpName()) )
	{
		AfxMessageBox("未能创建Region Area. ");

		return 0;
	}




	VGK_SHOW("导入区域成功. 继续生成栅格. \n");

	if (vgPlan::vgPlanManager::getSingleton().calculateGridForCurrentScene(1,1))
	{
		AfxMessageBox("方案创建成功.");
	}

	vgKernel::RendererManager::getSingleton().invalidate();
	return 0 ; 
}

 LRESULT CCommandWnd::OnVgpNewArea( WPARAM wParam, LPARAM lParam ) 
 {
	 vgPlan::vgPlanManager::getSingleton().setSelectorFlag(true);

 	return 0 ; 
 }

LRESULT CCommandWnd::OnVgpFromPlan( WPARAM wParam, LPARAM lParam ) 
{
	//add by zzy 209/10/27 14:18 for solve bug
	//如果m_sceneList中无场景则说明没有选定要规划的区域
	if( vgPlan::vgPlanManager::getSingleton().getNumOfScene() == 0 )
	{
		AfxMessageBox("请先选择规划区域！");
		return 0;
	}

	vgPlan::DlgPlanBlock dlg;

	vgPlan::vgSunAngle sunangle;

	/*this->SetTimer(1, 150, NULL);*/

	if (dlg.DoModal() == IDOK)
	{
		vgPlan::BlockParam blockParam = dlg.getBlockParam();

		// lss add 2009年5月13日10:44:50
		if (blockParam.blockX == 0	||
			blockParam.blockY == 0	||
			blockParam.floorAreaRatio == 0	
			)
		{
			AfxMessageBox("体块的长宽和容积率不允许为零，请重新输入!");
			this->SetTimer(1, 15, NULL);
			return 0;
		}

		if (blockParam.maxHeight < blockParam.minHeight)
		{
			AfxMessageBox("最高高度不应小于最低高度，请重新输入!");
			this->SetTimer(1, 15, NULL);
			return 0;
		}

		vgPlan::SunlightParam sunlightParam = dlg.getSunlightParam();

		vgPlan::vgPlanManager::getSingleton().getActiveScene()->generatePlan(blockParam, sunlightParam);
	}
	
	VGK_SHOW("生成规划完成 \n");
	vgPlan::vgPlanManager::getSingleton().setHaveGeneratedPlan( true );  //add by zzy 2009/10/27  15:36 标识已经有规划方案生成

	/*this->SetTimer(1, 15, NULL);*/

	return 0 ; 
}

LRESULT CCommandWnd::OnVgpShowPlan( WPARAM wParam, LPARAM lParam ) 
{
	 //add by zzy 2009/10/27  15:36 
	if ( !vgPlan::vgPlanManager::getSingleton().getHaveGeneratedPlan() )
	{
		AfxMessageBox("请先生成规划方案!");
		return 0;
	}

	vgPlan::DlgPlanOutput dlg;

	dlg.DoModal();

	return 0 ; 
}

LRESULT CCommandWnd::OnVgpQueryGreenRatio( WPARAM wParam, LPARAM lParam )
{
	//add by zzy 2009/10/27  15:36 
	/*if ( !vgPlan::vgPlanManager::getSingleton().getHaveGeneratedPlan() )
	{
		AfxMessageBox("请先生成规划方案!");
		return 0;
	}*/

	vgKernel::InputSystem::getSingleton().setCurrentStatus(
		VG_INPUT_VECTOR_ANALYSIS_GREEN);

	if( !vgShape::ShapeManager::getSingleton().setQueryRatioFlag(vgShape::GREEN_RATIO) )
	{
		vgKernel::InputSystem::getSingleton().setDefaultStatus();
	}

	return 0;
}

LRESULT CCommandWnd::OnVgpQueryPlotRatio( WPARAM wParam, LPARAM lParam )
{
	//add by zzy 2009/10/27  15:36 
	/*if ( !vgPlan::vgPlanManager::getSingleton().getHaveGeneratedPlan() )
	{
		AfxMessageBox("请先生成规划方案!");
		return 0;
	}*/

	vgKernel::InputSystem::getSingleton().setCurrentStatus(
		VG_INPUT_VECTOR_ANALYSIS_GREEN);

	if( !vgShape::ShapeManager::getSingleton().setQueryRatioFlag(vgShape::PLOT_RATIO) )
	{
		vgKernel::InputSystem::getSingleton().setDefaultStatus();
	}

	return 0;
}

LRESULT CCommandWnd::OnVgpEditMode( WPARAM wParam, LPARAM lParam ) 
{
	vgPlan::vgPlanManager::getSingleton().setEditMode(
		! vgPlan::vgPlanManager::getSingleton().getEditMode());

	return 0 ; 
}


// 仿照此函数实现用户自加载的菜单.
bool SetUserMenu(CMenu* SubMenu, UINT * NextMenuID)
{
	// 设置显示的菜单名
#if 0
	SubMenu->AppendMenu( MF_STRING, (UINT_PTR)(*NextMenuID), _T("新建方案(New Plan)") ) ;
	// 事件ID,对应点击的响应函数
	s_CommandToMessage[*NextMenuID] = ID_VGP_DLL_NEWPLAN;
	(*NextMenuID)++;
#endif
	SubMenu->AppendMenu( MF_STRING, (UINT_PTR)(*NextMenuID), _T("选择区域(Select &Area)") ) ;
	// 事件ID,对应点击的响应函数
	s_CommandToMessage[*NextMenuID] = ID_VGP_DLL_NEWAREA;
	(*NextMenuID)++;

	SubMenu->AppendMenu( MF_SEPARATOR, 0, _T("") ) ;

// 	SubMenu->AppendMenu( MF_STRING, (UINT_PTR)(*NextMenuID), _T("生成栅格(Generate Grid)") ) ;
// 	s_CommandToMessage[*NextMenuID] = ID_VGP_DLL_GENERATEGRID;
// 	(*NextMenuID)++;

	SubMenu->AppendMenu( MF_STRING, (UINT_PTR)(*NextMenuID), _T("生成规划(&From Plan)") ) ;
	s_CommandToMessage[*NextMenuID] = ID_VGP_DLL_FROMPLAN;
	(*NextMenuID)++;

	SubMenu->AppendMenu( MF_STRING, (UINT_PTR)(*NextMenuID), _T("方案显示(&Show Plan)") ) ;
	s_CommandToMessage[*NextMenuID] = ID_VGP_DLL_SHOWPLAN;
	(*NextMenuID)++;

	SubMenu->AppendMenu( MF_SEPARATOR, 0, _T("") ) ;

	CMenu querySubMenu;
	querySubMenu.CreateMenu();
	querySubMenu.AppendMenu( MF_STRING, (UINT_PTR)(*NextMenuID), _T("绿化率(Query &Green Ratio)") );
	s_CommandToMessage[*NextMenuID] = ID_VGP_DLL_QUERYGREENRATIO;
	(*NextMenuID)++;

	querySubMenu.AppendMenu( MF_STRING, (UINT_PTR)(*NextMenuID), _T("容积率(Query &Plot Ratio)") );
	s_CommandToMessage[*NextMenuID] = ID_VGP_DLL_QUERYPLOTRATIO;
	(*NextMenuID)++;

	SubMenu->AppendMenu( MF_POPUP, (UINT_PTR)querySubMenu.m_hMenu, _T("查询规划信息(&Query Plan Info)") );
	querySubMenu.Detach();

	SubMenu->AppendMenu( MF_SEPARATOR, 0, _T("") );

	SubMenu->AppendMenu( MF_STRING, (UINT_PTR)(*NextMenuID), _T("切换编辑模式(&Edit Mode)") ) ;
	s_CommandToMessage[*NextMenuID] = ID_VGP_DLL_EDITMODE;
	(*NextMenuID)++;

	return true;
}

bool GetUserMenuCheck(UINT ID)
{
	// 默认Check关闭

	if (ID == ID_VGP_DLL_EDITMODE)
	{
		return vgPlan::vgPlanManager::getSingleton().getEditMode();
	}

	return false;
}

bool GetUserMenuEnable(UINT ID)
{

	// 默认菜单开启
	return true;
}
#endif