// CommandWnd.cpp : implementation file
/*
** Created by Lesky Zhou 
*/

#include <vgStableHeaders.h>
#include "CommandWnd.h"

#include <vgGis/vgGisManager.h>


// 主菜单显示的TEXT
std::string s_menuName = "GIS分析";

// 每一个菜单的事件ID, 加载的时候动态生成事件ID
const static UINT ID_GIS_MEASURE_POINT		= ::RegisterWindowMessage( _T("ID_GIS_MEASURE_POINT") )  ;
const static UINT ID_GIS_MEASURE_DISTANCE	= ::RegisterWindowMessage( _T("ID_GIS_MEASURE_DISTANCE") )  ;
const static UINT ID_GIS_MEASURE_AREA		= ::RegisterWindowMessage( _T("ID_GIS_MEASURE_AREA") )  ;
const static UINT ID_GIS_MEASURE_VOLUME		= ::RegisterWindowMessage( _T("ID_GIS_MEASURE_VOLUME") )  ;


IMPLEMENT_DYNAMIC(CCommandWnd, CWnd)
CCommandWnd::CCommandWnd()
{
}

CCommandWnd::~CCommandWnd()
{
}

BEGIN_MESSAGE_MAP(CCommandWnd, CWnd)
	ON_REGISTERED_MESSAGE( ID_GIS_MEASURE_POINT, OnGisMeasurePoint ) 
	ON_REGISTERED_MESSAGE( ID_GIS_MEASURE_DISTANCE, OnGisMeasureDistance ) 
	ON_REGISTERED_MESSAGE( ID_GIS_MEASURE_AREA, OnGisMeasureArea ) 
	ON_REGISTERED_MESSAGE( ID_GIS_MEASURE_VOLUME, OnGisMeasureVolume ) 
END_MESSAGE_MAP()

// CCommandWnd message handlers
LRESULT CCommandWnd::OnGisMeasurePoint( WPARAM wParam, LPARAM lParam )
{
	vgGIS3D::GisManager::getSingleton().setGisAnalysis(vgGIS3D::GisCoordinate);
	return 0;
}

LRESULT CCommandWnd::OnGisMeasureDistance( WPARAM wParam, LPARAM lParam )
{
	vgGIS3D::GisManager::getSingleton().setGisAnalysis(vgGIS3D::GisDistance);
	return 0;
}


LRESULT CCommandWnd::OnGisMeasureArea( WPARAM wParam, LPARAM lParam )
{
	vgGIS3D::GisManager::getSingleton().setGisAnalysis(vgGIS3D::GisArea);
	return 0;
}


LRESULT CCommandWnd::OnGisMeasureVolume( WPARAM wParam, LPARAM lParam )
{
	vgGIS3D::GisManager::getSingleton().setGisAnalysis(vgGIS3D::GisVolume);
	return 0;
}


// 仿照此函数实现用户自加载的菜单.
bool SetUserMenu(CMenu* SubMenu, UINT * NextMenuID)
{
	// 设置显示的菜单名
	SubMenu->AppendMenu( MF_STRING, (UINT_PTR)(*NextMenuID), _T("坐标查询(Measure &Positions)") ) ;
	// 事件ID,对应点击的响应函数
	s_CommandToMessage[*NextMenuID] = ID_GIS_MEASURE_POINT;
	(*NextMenuID)++;


	SubMenu->AppendMenu( MF_STRING, (UINT_PTR)(*NextMenuID), _T("距离测量(Measure &Distances)") ) ;
	s_CommandToMessage[*NextMenuID] = ID_GIS_MEASURE_DISTANCE;
	(*NextMenuID)++;

	SubMenu->AppendMenu( MF_STRING, (UINT_PTR)(*NextMenuID), _T("面积测量(Measure &Aeras)") ) ;
	s_CommandToMessage[*NextMenuID] = ID_GIS_MEASURE_AREA;
	(*NextMenuID)++;

	SubMenu->AppendMenu( MF_STRING, (UINT_PTR)(*NextMenuID), _T("体积测量(Measure &Volume)") ) ;
	s_CommandToMessage[*NextMenuID] = ID_GIS_MEASURE_VOLUME;
	(*NextMenuID)++;

	return true;
}

bool GetUserMenuCheck(UINT ID)
{
	if (ID == ID_GIS_MEASURE_POINT)
	{
		return (vgGIS3D::GisCoordinate == vgGIS3D::GisManager::getSingleton().getAnalysisType());
	}

	if (ID == ID_GIS_MEASURE_DISTANCE)
	{
		return (vgGIS3D::GisDistance == vgGIS3D::GisManager::getSingleton().getAnalysisType());
	}

	if (ID == ID_GIS_MEASURE_AREA)
	{
		return (vgGIS3D::GisArea == vgGIS3D::GisManager::getSingleton().getAnalysisType());
	}
	
	if (ID == ID_GIS_MEASURE_VOLUME)
	{
		return (vgGIS3D::GisVolume == vgGIS3D::GisManager::getSingleton().getAnalysisType());
	}

	// 默认Check关闭
	return false;
}

bool GetUserMenuEnable(UINT ID)
{

	// 默认菜单开启
	return true;
}