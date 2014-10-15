

#include <vgStableHeaders.h>
#include "vgChannelDLL/CommandWindow.h"

#include "vgChannel/vgcChannelManager.h"


//const static UINT ID_DYNAMICADD_DLL = ::RegisterWindowMessage(_T("ID_DYNAMICADD_DLL"));

IMPLEMENT_DYNAMIC(CCommandWindow, CWnd)
CCommandWindow::CCommandWindow()
{
}

CCommandWindow::~CCommandWindow()
{
}

BEGIN_MESSAGE_MAP(CCommandWindow, CWnd)
	//ON_REGISTERED_MESSAGE(ID_DYNAMICADD_DLL, onOffFullscreen)
END_MESSAGE_MAP()

// LRESULT CCommandWindow::onOffFullscreen(WPARAM wParam, LPARAM lParam)
// {	
// 	MessageBox("是否全屏" , "我的菜单" , MB_YESNO);
// 	return 0;
// }
// 
// bool SetRightUserMenu(CMenu* SubMenu, UINT * NextMenuID)
// {
// 	SubMenu->AppendMenu( MF_STRING, (UINT_PTR)(*NextMenuID), _T("动态加载") ) ;
// 	s_CommandToTheMessage[*NextMenuID] = ID_DYNAMICADD_DLL;
// 	(*NextMenuID)++;
// 
// 	SubMenu->InsertMenu(3,MF_BYPOSITION|MF_POPUP|MF_STRING,
// 
// 		(UINT) SubMenu,"子菜单"); //添加子菜单
// 
// 
// 	return true;
// }

 bool GetRightUserMenuCheck(UINT ID)
 {
	 //if (ID == ID_DYNAMICADD_DLL)
	 //{

	 //}
	return false;
 }

 bool GetRightUserMenuEnable(UINT ID)
 {
	 //if (ID == ID_DYNAMICADD_DLL)
	 //{

	 //}
	 return true;
 }