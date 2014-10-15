// CommandWnd.cpp : implementation file
/*
** Created by Lesky Zhou 
*/

#include <vgStableHeaders.h>

#if 0

#include "CommandWnd.h"

#include <vgKernel/vgkSystemUtility.h>

#include <vgSound/vgSoundManager.h>




// 主菜单显示的TEXT
std::string s_menuName = "音效(Sou&nd)";

// 每一个菜单的事件ID, 加载的时候动态生成事件ID
const static UINT ID_3DSOUND_ADD		= ::RegisterWindowMessage( _T("ID_3DSOUND_ADD") )  ;
const static UINT ID_BACKSOUND_SET	    = ::RegisterWindowMessage( _T("ID_BACKSOUND_SET") )  ;



IMPLEMENT_DYNAMIC(CCommandWnd, CWnd)
CCommandWnd::CCommandWnd()
{
}

CCommandWnd::~CCommandWnd()
{
}

BEGIN_MESSAGE_MAP(CCommandWnd, CWnd)
	ON_REGISTERED_MESSAGE( ID_3DSOUND_ADD, On3dsoundAdd ) 
	ON_REGISTERED_MESSAGE( ID_BACKSOUND_SET, OnBacksoundSet ) 
END_MESSAGE_MAP()

// CCommandWnd message handlers
LRESULT CCommandWnd::On3dsoundAdd( WPARAM wParam, LPARAM lParam )
{
	vgKernel::StringVector strExts;
	strExts.push_back("wav");
	vgKernel::StringVector strVec = vgKernel::SystemUtility::getFilesOpenByDialog(strExts);

	vgSound::SoundManager::getSingleton().importFiles( strVec );

	return 0;
}

LRESULT CCommandWnd::OnBacksoundSet( WPARAM wParam, LPARAM lParam )
{
	vgKernel::StringVector strExts;
	strExts.push_back("mp3");
	vgKernel::StringVector strVec = vgKernel::SystemUtility::getFilesOpenByDialog(strExts);

	vgSound::SoundManager::getSingleton().importFiles( strVec );

	return 0;
}


// 仿照此函数实现用户自加载的菜单.
bool SetUserMenu(CMenu* SubMenu, UINT * NextMenuID)
{
	// 设置显示的菜单名
	SubMenu->AppendMenu( MF_STRING, (UINT_PTR)(*NextMenuID), _T("添加立体音效(S&tereo Sound)") ) ;
	// 事件ID,对应点击的响应函数
	s_CommandToMessage[*NextMenuID] = ID_3DSOUND_ADD;
	(*NextMenuID)++;


	SubMenu->AppendMenu( MF_STRING, (UINT_PTR)(*NextMenuID), _T("添加背景音效(&Background Sound)") ) ;	
	s_CommandToMessage[*NextMenuID] = ID_BACKSOUND_SET;
	(*NextMenuID)++;	

	return true;
}

bool GetUserMenuCheck(UINT ID)
{
	// 默认Check关闭
	return false;
}

bool GetUserMenuEnable(UINT ID)
{

	// 默认菜单开启
	return true;
}

#endif
