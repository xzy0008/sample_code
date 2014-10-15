// CommandWnd.cpp : implementation file
/*
** Created by Lesky Zhou 
*/

#include <vgStableHeaders.h>
#if 0
#include "vgsolar/CommandWnd.h"

#include <vgSolar/vgsoSolarManager.h>
#include <vgKernel/vgkSelectManager.h>
#include <vgSolar/SolarConfig.h>



// 主菜单显示的TEXT
std::string s_menuName = "阴影分析(&A)";

// 每一个菜单的事件ID, 加载的时候动态生成事件ID
const static UINT ID_SOLAR_TURNON		= ::RegisterWindowMessage( _T("ID_SOLAR_TURNON") )  ;
const static UINT ID_SOLAR_TURNOFF	= ::RegisterWindowMessage( _T("ID_SOLAR_TURNOFF") )  ;
const static UINT ID_SOLAR_SET_DIR		= ::RegisterWindowMessage( _T("ID_SOLAR_SET_DIR") )  ;
const static UINT ID_SOLAR_ANALYSIS		= ::RegisterWindowMessage( _T("ID_SOLAR_ANALYSIS") )  ;


IMPLEMENT_DYNAMIC(CCommandWnd, CWnd)
CCommandWnd::CCommandWnd()
{
}

CCommandWnd::~CCommandWnd()
{
}

BEGIN_MESSAGE_MAP(CCommandWnd, CWnd)
	ON_REGISTERED_MESSAGE( ID_SOLAR_TURNON, OnSolarTurnOn ) 
	ON_REGISTERED_MESSAGE( ID_SOLAR_TURNOFF, OnSolarTurnOff ) 
	ON_REGISTERED_MESSAGE( ID_SOLAR_SET_DIR, OnSolarSetDirection ) 
	ON_REGISTERED_MESSAGE( ID_SOLAR_ANALYSIS, OnSolarAnalysis ) 
END_MESSAGE_MAP()

LRESULT CCommandWnd::OnSolarTurnOn( WPARAM wParam, LPARAM lParam )
{

	using namespace vgSolar;
	// TODO: Add your command handler code here
	// 当已经开启的时候，这个时候先卸载。
	if ( SolarManager::getSingleton().getShadowEnabled() )
	{
		SolarManager::getSingleton().turnOffShadowEffect();
	}

	vgKernel::RendererQueue* qu = 
		&vgKernel::SelectManager::getSingleton().getSelectedItems();

	//vgKernel::Vec3 dir( -1 , -1 , 2 );
	//dir.normalise();


	SolarManager::getSingleton().turnOnShadowEffect( qu , 
		NULL , true );


	return 0;
}

LRESULT CCommandWnd::OnSolarTurnOff( WPARAM wParam, LPARAM lParam )
{
	using namespace vgSolar;
	SolarManager::getSingleton().turnOffShadowEffect();
	return 0;
}

LRESULT CCommandWnd::OnSolarSetDirection( WPARAM wParam, LPARAM lParam )
{
	using namespace vgSolar;

	CSolarConfig dlg(
		&SolarManager::getSingleton().getCurrentDateAndTime() );

	if ( dlg.DoModal() == IDOK )
	{
		bool changeok = 
			SolarManager::getSingleton().changeDateTimeAndLoc(&dlg.getTimeAndLoc());

		if ( changeok == false )
		{
			::MessageBox( NULL , "太阳还没有出现" , "提示" ,  MB_OK );
		}
	}

	return 0;
}

LRESULT CCommandWnd::OnSolarAnalysis( WPARAM wParam, LPARAM lParam )
{
	using namespace vgKernel;
	using namespace vgSolar;


	if ( SelectManager::getSingleton().getSelectedItems().empty() )
	{
		vgKernel::ShadowCastObjectVec* vec = 
			SolarManager::getSingleton().getShadowCastObjects();

		if ( vec == NULL )
		{
			MessageBox( "没有投影的物体" );
			return 0;
		}

		vgKernel::SelectManager::getSingleton().clearSelection();

		vgKernel::ShadowCastObjectVec::iterator iter = vec->begin();
		vgKernel::ShadowCastObjectVec::iterator iter_end = vec->end();

		for( ; iter != iter_end ; ++ iter )
		{
			vgKernel::Renderer* ren = 
				dynamic_cast<vgKernel::Renderer*>( *iter );

			if ( ren != NULL )
			{
				vgKernel::SelectManager::getSingleton().addSelection( ren , false );
			}	
		}

		vgKernel::SelectManager::getSingleton().updateBox();
	}

	if ( SelectManager::getSingleton().getSelectedItems().empty() )
	{
		MessageBox( "请选中物体" );
		return 0;
	}

	// TODO: Add your command handler code here
	vgSolar::SolarManager::getSingleton().setSolarAnalysis(
		!SolarManager::getSingleton().getSolarAnalysisEnable() );


	return 0;
}
// 仿照此函数实现用户自加载的菜单.
bool SetUserMenu(CMenu* SubMenu, UINT * NextMenuID)
{
	// 设置显示的菜单名
	SubMenu->AppendMenu( MF_STRING, (UINT_PTR)(*NextMenuID), _T("开启阴影(Turn on Sh&adow)") ) ;
	// 事件ID,对应点击的响应函数
	s_CommandToMessage[*NextMenuID] = ID_SOLAR_TURNON;
	(*NextMenuID)++;


	SubMenu->AppendMenu( MF_STRING, (UINT_PTR)(*NextMenuID), _T("关闭阴影(Turn off Shado&w)") ) ;
	s_CommandToMessage[*NextMenuID] = ID_SOLAR_TURNOFF;
	(*NextMenuID)++;

	SubMenu->AppendMenu( MF_STRING, (UINT_PTR)(*NextMenuID), _T("设置光线方向(Set Light Direc&tion)") ) ;
	s_CommandToMessage[*NextMenuID] = ID_SOLAR_SET_DIR;
	(*NextMenuID)++;

	SubMenu->AppendMenu( MF_STRING, (UINT_PTR)(*NextMenuID), _T("日照分析(Solar Analysi&s)") ) ;
	s_CommandToMessage[*NextMenuID] = ID_SOLAR_ANALYSIS;
	(*NextMenuID)++;

	return true;
}

bool GetUserMenuCheck(UINT ID)
{
	if (ID == ID_SOLAR_TURNON)
	{
		//return (vgSolar::SolarManager::);
	}

	if (ID == ID_SOLAR_TURNOFF)
	{
		//return (vgGIS3nalysisType());
	}

	if (ID == ID_SOLAR_SET_DIR)
	{
		//return (vgGIS3D::GisArea == vgGIS3D::GisManager::getSingleton().getAnalysisType());
	}
	
	if (ID == ID_SOLAR_ANALYSIS)
	{
		return (vgSolar::SolarManager::getSingleton().getSolarAnalysisEnable());
	}

	// 默认Check关闭
	return false;
}

bool GetUserMenuEnable(UINT ID)
{
	if (ID == ID_SOLAR_TURNON)
	{
		return !vgSolar::SolarManager::getSingleton().getShadowEnabled();
	}

	if (ID == ID_SOLAR_TURNOFF)
	{
		return vgSolar::SolarManager::getSingleton().getShadowEnabled();
	}

	if (ID == ID_SOLAR_SET_DIR)
	{
		return vgSolar::SolarManager::getSingleton().getShadowEnabled();
	}

	if (ID == ID_SOLAR_ANALYSIS)
	{
		return vgSolar::SolarManager::getSingleton().getShadowEnabled();
	}


	// 默认菜单开启
	return true;
}
#endif