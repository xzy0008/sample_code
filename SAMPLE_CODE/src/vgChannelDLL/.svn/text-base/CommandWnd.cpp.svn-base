// CommandWnd.cpp : implementation file
/*
** Created by FengYK
*/

#include <vgStableHeaders.h>
#include "vgChannelDLL/CommandWnd.h"

#include "vgChannel/vgcChannelManager.h"

#include <vgChannel/DlgChannelParam.h>
#include <vgChannel/vgDlgEdgeBlend.h>
#include <vgChannel/vgNurbsParamDlg.h>


// 主菜单显示的TEXT
 std::string s_menuName = "多通道(&M)";
 UINT s_menuPosition = -1;

// 每一个菜单的事件ID, 加载的时候动态生成事件ID
/*const*/ /*static*/
const static UINT ID_CHANNEL_LEFT_DLL		= ::RegisterWindowMessage( _T("ID_CHANNEL_LEFT_DLL") );
const static UINT ID_CHANNEL_SERVER_DLL		= ::RegisterWindowMessage( _T("ID_CHANNEL_SERVER_DLL") );
const static UINT ID_CHANNEL_CANCEL_DLL		= ::RegisterWindowMessage( _T("ID_CHANNEL_CANCEL_DLL") );
const static UINT ID_CHANNEL_PARAM_DLL		= ::RegisterWindowMessage( _T("ID_CHANNEL_PARAM_DLL") );

const static UINT ID_BLENDONOFF_DLL			= ::RegisterWindowMessage( _T("ID_BLENDONOFF_DLL") );
const static UINT ID_EDGE_BLEND_DLL			= ::RegisterWindowMessage( _T("ID_EDGE_BLEND_DLL") );
const static UINT ID_NURBS_DLL				= ::RegisterWindowMessage( _T("ID_NURBS_DLL") );
const static UINT ID_LittleCorrect_DLL		= ::RegisterWindowMessage( _T("ID_LittleCorrect_DLL") );
const static UINT ID_BLEND_DLL				= ::RegisterWindowMessage( _T("ID_BLEND_DLL") );

//const static UINT ID_DYNAMICADD_DLL = ::RegisterWindowMessage(_T("ID_DYNAMICADD_DLL"));

IMPLEMENT_DYNAMIC(CCommandWnd, CWnd)
CCommandWnd::CCommandWnd()
{
}

CCommandWnd::~CCommandWnd()
{
}

BEGIN_MESSAGE_MAP(CCommandWnd, CWnd)
	ON_REGISTERED_MESSAGE( ID_CHANNEL_LEFT_DLL, OnChannelLeft ) 
 	ON_REGISTERED_MESSAGE( ID_CHANNEL_SERVER_DLL, OnChannelServer ) 
 	ON_REGISTERED_MESSAGE( ID_CHANNEL_CANCEL_DLL, OnChannelCancel ) 
 	ON_REGISTERED_MESSAGE( ID_CHANNEL_PARAM_DLL, OnChannelParam ) 
 
 	ON_REGISTERED_MESSAGE( ID_BLENDONOFF_DLL, OnBlendonoff ) 
 	ON_REGISTERED_MESSAGE( ID_EDGE_BLEND_DLL, OnEdgeBlend ) 
 
 	ON_REGISTERED_MESSAGE( ID_NURBS_DLL, OnNurbs )
 	ON_REGISTERED_MESSAGE( ID_BLEND_DLL, OnBlend ) 
 	ON_REGISTERED_MESSAGE( ID_LittleCorrect_DLL, OnLittlecorrect )

	//ON_REGISTERED_MESSAGE(ID_DYNAMICADD_DLL, onMessageBox)
END_MESSAGE_MAP()

// CCommandWnd message handlers
LRESULT CCommandWnd::OnChannelLeft( WPARAM wParam, LPARAM lParam )
{
	vgChannel::ChannelManager::getSingleton().SetChannelFromFile();
	vgChannel::ChannelManager::getSingleton().startChannel(-1);
	return 0;
}

LRESULT CCommandWnd::OnChannelServer( WPARAM wParam, LPARAM lParam )
{
	//获取本机IP地址
	char host_name[256];
	HOSTENT* pHost;
	if (gethostname(host_name, sizeof(host_name)) == SOCKET_ERROR)
	{
		return 0;
	}
	else
	{
		DWORD TempIP;
		int p[4];
		pHost=gethostbyname(host_name);
		TempIP = *((DWORD*)pHost->h_addr_list[0]);//获得本机IP地址
		union   Change   //以下为改正IP的过程
		{   
			DWORD   dwData;   
			byte     bData[8];   
		};   
		Change   test;   
		memset(test.bData, 0, 8);
		test.dwData = TempIP;
		p[0] = test.bData[0];
		p[1] = test.bData[1];
		p[2] = test.bData[2];
		p[3] = test.bData[3];
		test.bData[3]=p[0];   
		test.bData[2]=p[1];   
		test.bData[1]=p[2];   
		test.bData[0]=p[3];   
		TempIP = test.dwData;
		vgChannel::ChannelManager::getSingleton().setServerIP(TempIP);
	}
	vgChannel::ChannelManager::getSingleton().startChannel(0);
	return 0;
}


LRESULT CCommandWnd::OnChannelCancel( WPARAM wParam, LPARAM lParam )
{
	vgChannel::ChannelManager::getSingleton().cancelChannel();
	return 0;
}


LRESULT CCommandWnd::OnChannelParam( WPARAM wParam, LPARAM lParam )
{
	DlgChannelParam *dlg=new DlgChannelParam;
	dlg->Create(DlgChannelParam::IDD,NULL);
	dlg->ShowWindow(SW_SHOW);
	return 0;
}

LRESULT CCommandWnd::OnBlendonoff(WPARAM wParam, LPARAM lParam )
{
	vgChannel::ChannelManager::getSingleton().setBlendAndAdjustEnable(
		! vgChannel::ChannelManager::getSingleton().getBlendAndAdjustEnable());
	return 0;
}

LRESULT CCommandWnd::OnEdgeBlend(WPARAM wParam, LPARAM lParam )
{
	vgChannel::ChannelManager::getSingleton().setEdgeBlendEnable(
		! vgChannel::ChannelManager::getSingleton().getEdgeBlendEnable());
	return 0;
}

LRESULT CCommandWnd::OnNurbs(WPARAM wParam, LPARAM lParam )
{
	vgNurbsParamDlg *dlg=new vgNurbsParamDlg;
	dlg->Create(vgNurbsParamDlg::IDD, NULL);
	dlg->ShowWindow(SW_SHOW);
	return 0;
}

LRESULT CCommandWnd::OnBlend(WPARAM wParam, LPARAM lParam )
{
	vgDlgEdgeBlend *dlg = new vgDlgEdgeBlend;
	dlg->Create(vgDlgEdgeBlend::IDD, NULL);
	dlg->ShowWindow(SW_SHOW);
	return 0;
}

LRESULT CCommandWnd::OnLittlecorrect(WPARAM wParam, LPARAM lParam )
{
	vgChannel::ChannelManager::getSingleton().setNurbsLittleCorrectEnable(
		! vgChannel::ChannelManager::getSingleton().getNurbsLittleCorrectEnable());
	if ( vgChannel::ChannelManager::getSingleton().getNurbsLittleCorrectEnable())
	{
		vgKernel::InputSystem::getSingleton().setCurrentStatus(VG_INPUTMODE_NURBSCORRECT);	
	}
	else
	{
		if (IDYES == MessageBox("是否保存更改", "控制点微调", MB_YESNO))
		{			
			vgChannel::ChannelManager::getSingleton().savePramaToXml();
		}
		else
		{
			vgChannel::ChannelManager::getSingleton().ReturnToOriPrama();
		}
		vgKernel::InputSystem::getSingleton().setDefaultStatus();				
	}
	return 0;
}

//LRESULT CCommandWnd::onMessageBox(WPARAM wParam, LPARAM lParam)
//{	
//	MessageBox("加载成功" , "我的菜单" , MB_YESNO);
//	return 0;
//}

// 仿照此函数实现用户自加载的菜单.
bool SetUserMenu(CMenu* SubMenu, UINT * NextMenuID)
{
	// 设置显示的菜单名
	SubMenu->AppendMenu( MF_STRING, (UINT_PTR)(*NextMenuID), _T("建立客户端(Create &Client)") ) ;
	// 事件ID,对应点击的响应函数
	s_CommandToMessage[*NextMenuID] = ID_CHANNEL_LEFT_DLL;
	(*NextMenuID)++;

	SubMenu->AppendMenu( MF_STRING, (UINT_PTR)(*NextMenuID), _T("建立服务器(Create &Server)") ) ;
	s_CommandToMessage[*NextMenuID] = ID_CHANNEL_SERVER_DLL;
	(*NextMenuID)++;

	SubMenu->AppendMenu( MF_STRING, (UINT_PTR)(*NextMenuID), _T("断开连接(&Disconnect)") ) ;
	s_CommandToMessage[*NextMenuID] = ID_CHANNEL_CANCEL_DLL;
	(*NextMenuID)++;

	SubMenu->AppendMenu( MF_SEPARATOR, 0, _T("") ) ;//分割线

	SubMenu->AppendMenu( MF_STRING, (UINT_PTR)(*NextMenuID), _T("网络参数配置(Con&fig)") ) ;
	s_CommandToMessage[*NextMenuID] = ID_CHANNEL_PARAM_DLL;
	(*NextMenuID)++;

	SubMenu->AppendMenu( MF_SEPARATOR, 0, _T("") ) ;//菜单中的分割线

	CMenu * popupMenu = new CMenu();//二级菜单
	popupMenu->CreateMenu();

	popupMenu->AppendMenu( MF_STRING, (UINT_PTR)(*NextMenuID), _T("开启\\关闭几何校正(On\\Off Geometrical Correction)") ) ;
	s_CommandToMessage[*NextMenuID] = ID_BLENDONOFF_DLL;
	(*NextMenuID)++;

	popupMenu->AppendMenu( MF_STRING, (UINT_PTR)(*NextMenuID), _T("开启\\关闭边缘融合(On\\Off Edge Blending)") ) ;
	s_CommandToMessage[*NextMenuID] = ID_EDGE_BLEND_DLL;
	(*NextMenuID)++;

	popupMenu->AppendMenu( MF_STRING, (UINT_PTR)(*NextMenuID), _T("几何校正配置(Geometrical Correction Conf&ig)") ) ;
	s_CommandToMessage[*NextMenuID] = ID_NURBS_DLL;
	(*NextMenuID)++;

	popupMenu->AppendMenu( MF_STRING, (UINT_PTR)(*NextMenuID), _T("控制点微调(Contorl Point Config)") ) ;
	s_CommandToMessage[*NextMenuID] = ID_LittleCorrect_DLL;
	(*NextMenuID)++;

	popupMenu->AppendMenu( MF_STRING, (UINT_PTR)(*NextMenuID), _T("边缘融合配置(Ed&ge blending config)") ) ;
	s_CommandToMessage[*NextMenuID] = ID_BLEND_DLL;
	(*NextMenuID)++;

	SubMenu->AppendMenu(MF_POPUP, (UINT_PTR)popupMenu->operator HMENU(), "融合\\几何校正(Blending\\Correction)");//二级菜单
	popupMenu->Detach();
	delete popupMenu;

	SubMenu->AppendMenu( MF_SEPARATOR, 0, _T("") ) ;//分割线

	return true;
}
//add by kinghj 2009.12.3实现用户自加载的右键菜单项
bool SetRightUserMenu(CMenu* SubMenu, UINT * NextMenuID)
{
	//查看下面注掉的内容添加菜单项。也可以参见上面的SetUserMenu()函数
	//SubMenu->AppendMenu( MF_STRING, (UINT_PTR)(*NextMenuID), _T("动态加载") ) ;
	//s_CommandToMessage[*NextMenuID] = ID_DYNAMICADD_DLL;
	//(*NextMenuID)++;

	//SubMenu->InsertMenu(3,MF_BYPOSITION|MF_POPUP|MF_STRING,

	//	(UINT) SubMenu,"二级菜单"); //添加子菜单


	return true;
}

bool GetUserMenuCheck(UINT ID)
{
	if (ID == ID_CHANNEL_LEFT_DLL)
	{
	}

	if (ID == ID_CHANNEL_SERVER_DLL)
	{
	}

	if (ID == ID_CHANNEL_CANCEL_DLL)
	{
	}
	
	if (ID == ID_CHANNEL_PARAM_DLL)
	{
	}

	if (ID == ID_BLENDONOFF_DLL)
	{
		return(vgChannel::ChannelManager::getSingleton().getBlendAndAdjustEnable());
	}

	if (ID == ID_EDGE_BLEND_DLL)
	{
		return(vgChannel::ChannelManager::getSingleton().getEdgeBlendEnable());
	}

	if (ID == ID_NURBS_DLL)
	{
	}

	if (ID == ID_LittleCorrect_DLL)
	{
		return(vgChannel::ChannelManager::getSingleton().getNurbsLittleCorrectEnable());
	}

	if (ID == ID_BLEND_DLL)
	{
	}
	// 默认Check关闭
	return false;
}

bool GetUserMenuEnable(UINT ID)
{
	if (ID == ID_CHANNEL_LEFT_DLL)
	{
	}

	if (ID == ID_CHANNEL_SERVER_DLL)
	{
	}

	if (ID == ID_CHANNEL_CANCEL_DLL)
	{
	}

	if (ID == ID_CHANNEL_PARAM_DLL)
	{
	}

	if (ID == ID_BLENDONOFF_DLL)
	{
	}

	if (ID == ID_EDGE_BLEND_DLL)//默认在几何校正不开启的情况下，边缘融合菜单不可用
	{
		return(vgChannel::ChannelManager::getSingleton().getBlendAndAdjustEnable());
		//return false;
	}

	if (ID == ID_NURBS_DLL)
	{
	}

	if (ID == ID_LittleCorrect_DLL)
	{
	}

	if (ID == ID_BLEND_DLL)
	{
	}
	// 默认菜单开启
	return true;
}