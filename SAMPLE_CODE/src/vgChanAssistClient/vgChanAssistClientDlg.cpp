// ClientAssistantDlg.cpp : 实现文件
//

#include "vgStableHeaders.h"
#include "vgChanAssistClient/vgChanAssistClient.h"
#include "vgChanAssistClient/vgChanAssistClientDlg.h"
#include <WinSock2.h>
#include <TlHelp32.h>


static int		chanRecvPort = 8695;	//接收端口号8695
static SOCKET	chanRecvSocket;
static SOCKET	chanSendSocket;
static SOCKADDR_IN addrSnd;

static DWORD	chanThreadID;
static HANDLE	chanReceiveHandle;

static std::string m_broadCastAddress;
static std::string m_ownAddeess;

static DWORD WINAPI chanReceiveThread(LPVOID lpParameter);//接收消息线程
static void reriveFromServerSocket(long dataLength);	  //		
static void reStartComputer(bool bclose);				  // 关闭或重启计算机

static void vgkillProgress(const char* szExeName);		  // 关闭进程

static std::string m_ProgerssName;	//	进程名称
static CClientAssistantDlg *pDlgthis;

#define PROP_HAS_BUTTON	0x0002		//  CFileItem 类中

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CFileItem Class

CFileItem::CFileItem(const CString& strFileName) :
CBCGPGridItem (_variant_t((LPCTSTR) strFileName))
{
	m_dwFlags = PROP_HAS_BUTTON;
}
//****************************************************************************************
void CFileItem::OnClickButton (CPoint /*point*/)
{
	CBCGPGridCtrl* pGridCtrl = GetOwnerList();

	m_bButtonIsDown = TRUE;
	Redraw ();

	CString strPath = (LPCTSTR)(_bstr_t)m_varValue;

	CFileDialog dlg (TRUE,  strPath);

	if (dlg.DoModal () == IDOK)
	{
		strPath = dlg.GetPathName ();
		m_varValue = (LPCTSTR) strPath;
	}
	else
	{
		return;
	}

	m_bButtonIsDown = FALSE;
	Redraw ();

	if (m_pWndInPlace != NULL)
	{
		m_pWndInPlace->SetWindowText (strPath);
		m_pWndInPlace->SetFocus ();
	}
	else
	{
		pGridCtrl->SetFocus ();
	}
}
//////////////////////////////////////////////////////////////////////////

// CClientAssistantDlg 对话框




CClientAssistantDlg::CClientAssistantDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CClientAssistantDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	is_visible = false;
	_FullScreen = NULL;
	_startChannel = NULL;
	_softBlend = NULL;
	pDlgthis = this;
}

void CClientAssistantDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STC_TXT, m_DlgGridLocation);
}

BEGIN_MESSAGE_MAP(CClientAssistantDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_WM_WINDOWPOSCHANGING()
	ON_BN_CLICKED(IDCANCEL, &CClientAssistantDlg::OnBnClickedCancel)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDOK, &CClientAssistantDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BTN_HIDE, &CClientAssistantDlg::OnBnClickedBtnHide)
	ON_BN_CLICKED(IDC_BTN_ADDROW, &CClientAssistantDlg::OnBnClickedBtnAddrow)
	ON_BN_CLICKED(IDC_BEN_DELETEROW, &CClientAssistantDlg::OnBnClickedBenDeleterow)
END_MESSAGE_MAP()


// CClientAssistantDlg 消息处理程序

BOOL CClientAssistantDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	// --------------------------------------------------------------
	CRect rectGrid;
	m_DlgGridLocation.GetClientRect (&rectGrid);

	m_DlgGridLocation.MapWindowPoints (this, &rectGrid);

	m_wndGrid.Create (WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER, rectGrid, this, (UINT)-1);
	m_wndGrid.EnableHeader (TRUE, BCGP_GRID_HEADER_MOVE_ITEMS);

	//m_wndGrid.SetReadOnly ();
	m_wndGrid.SetWholeRowSel(FALSE);
	m_wndGrid.EnableMarkSortedColumn(FALSE);
	m_wndGrid.EnableHeader(TRUE, 0);

	m_wndGrid.InsertColumn(0, _T("场景名称"), 65);
	m_wndGrid.InsertColumn(1, _T("VRGIS程序路径"), 130);
	m_wndGrid.InsertColumn(2, _T("VG文件路径"), 130);
	m_wndGrid.InsertColumn(3, _T("全屏"), 40);
	m_wndGrid.InsertColumn(4, _T("开启多通道"), 70);
	m_wndGrid.InsertColumn(5, _T("软融合"), 65);
	m_wndGrid.InsertColumn(6, _T("客户端/服务器"), 90);
		
	UpdateData(FALSE);
	// --------------------------------------------------------------

	write2Reg();	// 写入注册表启动项
	
	// 注册热键 Ctrl + Alt + 9 
	//::RegisterHotKey(this->m_hWnd, m_hotKeyID ,MOD_CONTROL|MOD_ALT,'9');
	BOOL isRegister = ::RegisterHotKey(this->m_hWnd, 0Xa006 ,MOD_CONTROL|MOD_ALT,'9');
	
	if ( !isRegister )
	{
		AfxMessageBox("注册热键失败!");
	}

	startConnect();			// 建立监听

	//readConfigFile_ini();	// 读取ini配置文件
	readConfigFile_XML();	// 读取XML配置文件
						
	// --------------------------------------------------------------
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CClientAssistantDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CClientAssistantDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标显示。
//
HCURSOR CClientAssistantDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//-------------------------------------------------------------------

void CClientAssistantDlg::OnWindowPosChanging(WINDOWPOS* lpwndpos)
{
	// 此函数用于隐藏窗口 -FengYK @2010-03-10 08:59
	if(!is_visible)   
		lpwndpos->flags &= ~SWP_SHOWWINDOW;   

	CDialog::OnWindowPosChanging(lpwndpos);

	// TODO: 在此处添加消息处理程序代码
}
//-------------------------------------------------------------------

void CClientAssistantDlg::readConfigFile_ini()
{
	char szModule[MAX_PATH] ;      
	::GetModuleFileName (NULL, szModule, MAX_PATH);

	string srcFolder(szModule);

	string::size_type found = srcFolder.find_last_of( "\\/" );
	string srcFilePath = srcFolder.substr( 0 , found );
	//srcFilePath += "\\ClientAssistant.ini";

	string strName1 = srcFolder.substr(found + 1, srcFolder.length() - found - 5);

	srcFilePath += "\\";
	srcFilePath += strName1;
	srcFilePath += ".ini";

	FILE *fp;

	fopen_s(&fp, srcFilePath.c_str(), "r");	// 读,文件必须存在。

	if (fp == NULL)
	{
		CString strWarning;
		strWarning.Format("%s.exe 打开配置文件失败!\n请确认应用程序目录下存在%s文件!", strName1.c_str(), srcFilePath.c_str());
		AfxMessageBox(strWarning);
		//return;
		OnCancel();	//退出程序
	}
	else
	{
		char str[256];
		int cnt = 0;

		if ( fgets(str, 256, fp) != NULL ) 
		{
			CString strInFile(str);

			if ( strInFile.Right(1) == "\n")
			{
				strInFile.TrimRight("\n");
			}

			if ( strInFile == "1")
			{
				is_visible = true;
			}
			else if ( strInFile == "0")
			{
				is_visible = false;
			}
		}


		while ( fgets(str, 256, fp) != NULL)
		{
			CString strInFile(str);

			//int m_length = strInFile.GetLength();

			if ( strInFile.Right(1) == "\n")
			{
				strInFile.TrimRight("\n");
			}

			vec_str_config.push_back(strInFile);

		}

		fclose(fp);
	}

	m_AddConfig();
}
//-------------------------------------------------------------------

void CClientAssistantDlg::writeConfigFile_ini()
{
	char szModule[MAX_PATH] ;      
	::GetModuleFileName (NULL, szModule, MAX_PATH);

	string srcFolder(szModule);

	string::size_type found = srcFolder.find_last_of( "\\/" );
	string srcFilePath = srcFolder.substr( 0 , found );
	//srcFilePath += "\\ClientAssistant.ini";
	string strName1 = srcFolder.substr(found + 1, srcFolder.length() - found - 5);

	srcFilePath += "\\";
	srcFilePath += strName1;
	srcFilePath += ".ini";

	FILE *fp;

	fopen_s(&fp, srcFilePath.c_str(), "w");	// 写。

	if (fp == NULL)
	{
		CString strWarning;
		strWarning.Format("%s.exe 写入配置文件%s失败!", strName1.c_str(), srcFilePath.c_str());
		AfxMessageBox(strWarning);
		return;
	}
	else
	{
		fputs("1\n", fp);	// 是否隐藏界面 1:不隐藏; 0:隐藏

		for (int i=0; i<m_wndGrid.GetRowCount(); i++)
		{
			CBCGPGridRow *pRow = m_wndGrid.GetRow(i);

			CString sceneName(pRow->GetItem(0)->GetValue().bstrVal);
			sceneName.Append("\n");
			fputs( sceneName, fp );
			
			CString vrgis_exePath(pRow->GetItem(1)->GetValue().bstrVal);
			vrgis_exePath.Append("\n");
			fputs( vrgis_exePath, fp );
			
			CString vg_path(pRow->GetItem(2)->GetValue().bstrVal);
			vg_path.Append(_T(" "));
			fputs(vg_path, fp);
			
			//int b_fullScreen = _FullScreen->GetValue();
			//int b_startChan = _startChannel->GetValue();

			int b_fullScreen = pRow->GetItem(3)->GetValue();
			int b_startChan = pRow->GetItem(4)->GetValue();
			int b_sofrBlend = pRow->GetItem(5)->GetValue();

			if ( b_fullScreen == 0 )		// 是否选择全屏
			{
				fputs(_T("-nfs "), fp);
			}
			else if ( b_fullScreen == -1 )
			{
				fputs(_T("-fs "), fp);
			}

			if ( b_startChan == 0 )			// 是否选择开启多通道
			{
				fputs(_T("-nsc "), fp);
			}
			else if ( b_startChan == -1 )
			{
				fputs(_T("-sc "), fp);
			}

			if ( b_sofrBlend == 0 )			// 是否选择开启软融合
			{
				fputs(_T("-nbaa "), fp);
			}
			else if ( b_sofrBlend == -1 )
			{
				fputs(_T("-baa "), fp);
			}

			CString server_Type(pRow->GetItem(6)->GetValue().bstrVal);
			if ( server_Type == "客户端" )	// 服务器或客户端
			{
				fputs(_T("-1\n"), fp);
			}
			else if ( server_Type == "服务器" )
			{
				fputs(_T("-0\n"), fp);
			}

		}
		
		fclose(fp);
	}		

}
//-------------------------------------------------------------------

void CClientAssistantDlg::write2Reg()
{
	HKEY hKey; 

	LPCTSTR data_Set="Software\\Microsoft\\Windows\\CurrentVersion\\Run";//设置注册表中相关的路径,两个斜杠 

	long ret0=(::RegOpenKeyEx(HKEY_LOCAL_MACHINE,data_Set,0,KEY_WRITE,&hKey));//打开注册表中的相应项 

	if(ret0!=ERROR_SUCCESS) 
	{ 
		MessageBox("打开注册表失败"); 
		return ;
	} 

	int i=0;
	char szModule[MAX_PATH] ;      

	::GetModuleFileName (NULL, szModule, MAX_PATH); //获得程序路径包含文件名

	CString title;
	title.Format("vgChannelAssist_Client");				//写入注册表的标题

	//int length=szModule.GetLength()+1;			//+1是因为lpb是分配了空间以后逐个字符写进来的，而不是定义一个CString类型的lpb用strcpy拷贝过来的，所以需将字符串结束字符也写进去。
	int length = sizeof(szModule) + 1;
	int len = length - 1;

	LPBYTE lpb=new BYTE[length]; 
	int j=0;

	for(i = 0;i<len;i++) 
	{
		lpb[j] = szModule[i];
		j++;

	}

	lpb[j] = 0; //写lpb中最后一个字符，也就是字符串结束字符，这也是上面长度+1的原因

	long ret1=(::RegSetValueEx(hKey,title,NULL,REG_SZ,lpb,length/*cbData*/));//将相关的信息写入注册表。

	if(ret1!=ERROR_SUCCESS) //判断系统的相关注册是否成功？
	{ 
		CString strWaring;
		strWaring.Format("写入注册表失败");
		MessageBox(strWaring); 
		delete lpb; 
		::RegCloseKey(hKey);//关闭注册表中的相应的项 
		return ;
	}
}
//-------------------------------------------------------------------

void CClientAssistantDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	OnCancel();
	// 因为遇到了无法完整退出自己的问题，现在手动结束自己 - FengYK
	char char_SelfName[MAX_PATH] ;      
	::GetModuleFileName (NULL, char_SelfName, MAX_PATH); //获得程序路径包含文件名
	string strName(char_SelfName);
	string strName1;
	string::size_type found = strName.find_last_of( "\\/" );
	strName1 = strName.substr(found + 1);

	vgkillProgress(strName1.c_str());

}
//-------------------------------------------------------------------

BOOL CClientAssistantDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	switch(pMsg->message)
	{
	case WM_KEYDOWN:
// 		if ( pMsg->wParam == 'Q')
// 		{
// 			AfxMessageBox("Q键被按下!");
// 		}
	case WM_SYSKEYDOWN:	// 响应快捷键
// 		iResult = TranslateAccelerator(m_hWnd,hAcc,pMsg);
// 		//翻译快捷键成功，返回TRUE
// 		if(iResult)
// 			return TRUE;
	case WM_HOTKEY:		// 响应热键
		if(pMsg->wParam == 0Xa006)  
			OnShowDlg();
	}

	return CDialog::PreTranslateMessage(pMsg);
}
//-------------------------------------------------------------------

void CClientAssistantDlg::OnShowDlg()
{
	if ( is_visible )
	{
		is_visible = false;
		this->ShowWindow(SW_HIDE);
	}
	else
	{
		is_visible = true;
		this->ShowWindow(SW_SHOW);
	}

}
//-------------------------------------------------------------------

void CClientAssistantDlg::OnDestroy()
{
	CDialog::OnDestroy();

	// TODO: 在此处添加消息处理程序代码
	UnregisterHotKey(this->m_hWnd, 0Xa006);

	WSACleanup();

	if(chanReceiveHandle != NULL)
	{
		WaitForSingleObject(chanReceiveHandle,INFINITE);
		chanReceiveHandle = NULL;
		chanThreadID = 0;
	}

	closesocket(chanRecvSocket);

	if ( pDlgthis != NULL )
	{
		delete pDlgthis;
		pDlgthis = NULL;
	}
	//delete this;
}
//-------------------------------------------------------------------

BOOL CClientAssistantDlg::startConnect()
{
	WSADATA wsd;

	int ret = WSAStartup(0x0202,&wsd);
	if(ret!=0)
	{
		WSACleanup();
	}

	//获得广播的IP----------------------------------------------------------
	char hostName[255];   
	PHOSTENT hostinfo;

	if(gethostname(hostName, sizeof(hostName))   ==   0)   
	{   
		if((hostinfo = gethostbyname(hostName)) != NULL)   
		{   
			m_broadCastAddress = inet_ntoa(*(struct in_addr *)*hostinfo->h_addr_list);   
			m_ownAddeess = m_broadCastAddress;
		}

		if (m_broadCastAddress[m_broadCastAddress.length()-2] == '.')//IP地址的最后段是1位
		{
			m_broadCastAddress.erase(m_broadCastAddress.length()-1);
			m_broadCastAddress.append("255",m_broadCastAddress.length()-1);;
		}
		else if (m_broadCastAddress[m_broadCastAddress.length()-3] == '.')//IP地址最后段是两位
		{
			m_broadCastAddress.erase(m_broadCastAddress.length()-2);
			m_broadCastAddress.append("255",m_broadCastAddress.length()-1);;
		}
		else
		{
			m_broadCastAddress[m_broadCastAddress.length()-1] = '5';
			m_broadCastAddress[m_broadCastAddress.length()-2] = '5';
			m_broadCastAddress[m_broadCastAddress.length()-3] = '2';
		}
	}
	//------------------------------------------------------------------------
	if(! createRecvSocket(chanRecvPort))
	{
		AfxMessageBox("端口创建错误.");
		return FALSE;
	}

	chanReceiveHandle = 
		CreateThread(NULL, 0, chanReceiveThread, this, 0, &chanThreadID);

	SetThreadPriority( chanReceiveHandle, THREAD_PRIORITY_ABOVE_NORMAL);

	if( chanReceiveHandle == NULL )
	{
		return FALSE;
	}

	return TRUE;
}
//-------------------------------------------------------------------

BOOL CClientAssistantDlg::createRecvSocket(int RecvPort)
{
	int ret;

	// 创建Server接收Socket
	chanRecvSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_IP); 

	if(chanRecvSocket == INVALID_SOCKET)
	{
		return FALSE;
	}

	SOCKADDR_IN addr;
	ZeroMemory(&addr, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = INADDR_ANY;
	addr.sin_port = htons(RecvPort);

	// 绑定接收使用的端口和地址
	ret = bind(chanRecvSocket, (struct sockaddr *)&addr, sizeof(addr));

	if(ret != 0)
	{
		return FALSE;
	}

	// 创建发送Socket
	chanSendSocket = socket(AF_INET,SOCK_DGRAM,IPPROTO_IP); 
	if(chanSendSocket == INVALID_SOCKET)
	{
		return 0;
	}

	//绑定发送
	ZeroMemory(&addrSnd,sizeof(addrSnd));
	addrSnd.sin_family = AF_INET;
	addrSnd.sin_addr.s_addr = INADDR_ANY;

	ret = bind(chanSendSocket, (struct sockaddr *)&addrSnd, sizeof(addrSnd));

	addrSnd.sin_addr.s_addr = inet_addr(m_broadCastAddress.c_str());

	if(ret != 0)
	{
		return 0;
	}

	return TRUE;

}
//-------------------------------------------------------------------

DWORD WINAPI chanReceiveThread(LPVOID lpParameter)
{
	int ret;
	unsigned long lLength;

	while( TRUE )
	{
		ret = ioctlsocket(chanRecvSocket, FIONREAD, &lLength);
		if(ret != 0)
		{
			break;
		}
		else
		{
			if(lLength>0)
			{
				reriveFromServerSocket(lLength);
			}
		}

		Sleep(10);
	}

	return 0;

}
//-------------------------------------------------------------------

void reriveFromServerSocket(long dataLength)
{
	char *pbuf;
	int addr_len, iRecLen;;
	struct sockaddr_in addr;

	pbuf = new char[dataLength + 1];
	memset(pbuf, 0, dataLength + 1);

	addr_len = sizeof(addr);

	iRecLen = recvfrom(chanRecvSocket, pbuf, dataLength, 0,(struct sockaddr *)&addr, &addr_len);

	CString recvStr(pbuf);	//接收到的消息

	if( iRecLen <= 0 )
	{
		return;
	}
	else if ( recvStr.Left(17) == "VRGISstartChannel" )
	{

		SHELLEXECUTEINFO  ShExecInfo = {0};
		string strExeFilePath;
		string strvgPath;
		CString tempStr;

		if ( recvStr.GetLength() > 17)
		{
			tempStr = recvStr.Mid(17);
		}

		//////////////////////////////////////////////////////////////////////////
		// 因为开始在static 的函数中不能调用CClientAssistantDlg::m_wndGrid 
		// 所以没有使用这种办法;使用的读取配置文件的方法
		// 现在使用指针的方法做;
		// 在开头定义了一个 static CClientAssistantDlg *pDlg;
		// 在CClientAssistantDlg 的构造函数中对pDlg 进行赋值，
		// 在CClientAssistantDlg 的Destory 函数中进行销毁

		for ( int i = 0; i < pDlgthis->m_wndGrid.GetRowCount(); i++ )
		{
			CBCGPGridRow *pRow = pDlgthis->m_wndGrid.GetRow(i);

			if ( pRow->GetItem(0)->GetValue().bstrVal == tempStr )
			{
				strExeFilePath = (_bstr_t)(pRow->GetItem(1)->GetValue().bstrVal);
				strvgPath = (_bstr_t)(pRow->GetItem(2)->GetValue().bstrVal);

				int b_fullScreen = pRow->GetItem(3)->GetValue();
				int b_startChan = pRow->GetItem(4)->GetValue();
				int b_softBlend = pRow->GetItem(5)->GetValue();

				CString strFullScreen;
				CString strStartChan;
				CString strSoftBlend;			// 用于软融合

				if ( b_fullScreen == 0 )		// 是否选择全屏
				{
					strFullScreen.Format("%s", _T(" -nfs"));
				}
				else if ( b_fullScreen == -1 )
				{
					strFullScreen.Format("%s", _T(" -fs"));
				}

				if ( b_startChan == 0 )			// 是否选择开启多通道
				{
					strStartChan.Format("%s", _T(" -nsc"));
				}
				else if ( b_startChan == -1 )
				{
					strStartChan.Format("%s", _T(" -sc"));
				}

				if ( b_softBlend == 0 )			// 是否选择开启软融合
				{
					strSoftBlend.Format("%s", _T(" -nbaa"));
				}
				else if ( b_softBlend == -1 )
				{
					strSoftBlend.Format("%s", _T(" -baa"));
				}

				strvgPath += strFullScreen.GetBuffer();
				strFullScreen.ReleaseBuffer();

				strvgPath += strStartChan.GetBuffer();
				strStartChan.ReleaseBuffer();

				strvgPath += strSoftBlend.GetBuffer();
				strSoftBlend.ReleaseBuffer();

				CString strServType(pRow->GetItem(6)->GetValue().bstrVal);

				if ( strServType == "客户端" )	// 服务器或客户端
				{
					strvgPath += " -1";
				}
				else if ( strServType == "服务器" )
				{
					strvgPath += " -0";;
				}
				
				m_ProgerssName = strExeFilePath;
			}
		}

		if ( strExeFilePath == "" || strvgPath == "" )
		{
			return;
		}
		//////////////////////////////////////////////////////////////////////////

#if 0
		// ---------------------------------------------------------------
		// 收到消息后读取 XML 配置文件方式
		char szModule[MAX_PATH] ;      
		::GetModuleFileName (NULL, szModule, MAX_PATH);

		string srcFolder(szModule);

		string::size_type found = srcFolder.find_last_of( "\\/" );
		string srcFilePath = srcFolder.substr( 0 , found );
		//srcFilePath += "\\ClientAssistant.ini";

		string strName1 = srcFolder.substr(found + 1, srcFolder.length() - found - 5);

		CString configFilePath;

		configFilePath.Format( "%s\\%s.xml", srcFilePath.c_str(), strName1.c_str() );

		XMLConfigManager *pXMLConfig = new XMLConfigManager();

		pXMLConfig->LoadXmlDocument( configFilePath );

		// 界面控制参数
		if ( pXMLConfig->FindSection( tempStr ) )
		{
			SectionData sceneInfo = pXMLConfig->GetCurrentValue( tempStr );

			CString vrgis_exePath = sceneInfo._Currentkeyvalue[0];
			CString vg_path = sceneInfo._Currentkeyvalue[1];
			CString strFullScreen = sceneInfo._Currentkeyvalue[2];
			CString strStartChan = sceneInfo._Currentkeyvalue[3];
			CString strSoftBlend = sceneInfo._Currentkeyvalue[4];
			CString strServType = sceneInfo._Currentkeyvalue[5];

			strExeFilePath = vrgis_exePath.GetBuffer();
			vrgis_exePath.ReleaseBuffer();
			m_ProgerssName = strExeFilePath;
			
			strvgPath = vg_path.GetBuffer();
			vg_path.ReleaseBuffer();

			strvgPath += _T(" ");
			strvgPath += strFullScreen.GetBuffer();
			strFullScreen.ReleaseBuffer();
			
			strvgPath += _T(" ");
			strvgPath += strStartChan.GetBuffer();
			strStartChan.ReleaseBuffer();

			strvgPath += _T(" ");
			strvgPath += strSoftBlend.GetBuffer();
			strSoftBlend.ReleaseBuffer();

			strvgPath += _T(" ");

			if ( strServType == "客户端" )
			{
				strvgPath += _T("-1");
			}
			else if ( strServType == "服务器" )
			{
				strvgPath += _T("-0");
			}

		}
		else
		{
			CString s_sceneName;
			s_sceneName.Format(_T("没有找到场景%s,请查看配置!"), tempStr );
			AfxMessageBox(s_sceneName);
		}

		// ---------------------------------------------------------------
#endif
	
#if 0
		// ---------------------------------------------------------------
		// 收到消息后读取 ini 配置文件方式

		char szModule[MAX_PATH] ;      
		::GetModuleFileName (NULL, szModule, MAX_PATH);

		string srcFolder(szModule);

		string::size_type found = srcFolder.find_last_of( "\\/" );
		string srcFilePath = srcFolder.substr( 0 , found );
		//srcFilePath += "\\ClientAssistant.ini";

		string strName1 = srcFolder.substr(found + 1, srcFolder.length() - found - 5);

		srcFilePath += "\\";
		srcFilePath += strName1;
		srcFilePath += ".ini";

		FILE *fp;

		fopen_s(&fp, srcFilePath.c_str(), "r");	// 读,文件必须存在。

		if (fp == NULL)
		{
			CString strWarning;
			strWarning.Format("%s.exe 读取配置文件失败!\n请确认应用程序目录下存在%s文件!", strName1.c_str(), srcFilePath.c_str());
			AfxMessageBox(strWarning);
			return;
		}
		else
		{
			char str[256];
			int cnt = 0;

			fgets(str, 256, fp);

				while ( fgets(str, 256, fp) != NULL )
				{
					CString strInFile(str);

					if ( strInFile.Right(1) == "\n")
					{
						strInFile.TrimRight("\n");
					}

					if ( strInFile == tempStr )
					{
						if ( fgets(str, 256, fp) != NULL )
						{
							CString exePath(str);

							if ( exePath.Right(1) == "\n")
							{
								exePath.TrimRight("\n");
							}

							strExeFilePath = exePath.GetBuffer();
							exePath.ReleaseBuffer();

							m_ProgerssName = strExeFilePath;
						}

						if ( fgets(str, 256, fp) != NULL )
						{
							CString vgPath(str);

							if ( vgPath.Right(1) == "\n")
							{
								vgPath.TrimRight("\n");
							}

							strvgPath = vgPath.GetBuffer();
							vgPath.ReleaseBuffer();
						}

						//return;
					}

				}

				fclose(fp);
		}
		// ---------------------------------------------------------------
#endif


#if 0
		// ---------------------------------------------------------------
		// 原来写的配置文件的方式
		char szModule[MAX_PATH] ;      
		::GetModuleFileName (NULL, szModule, MAX_PATH);

		string srcFolder(szModule);



		string::size_type found = srcFolder.find_last_of( "\\/" );
		string srcFilePath = srcFolder.substr( 0 , found );
		//srcFilePath += "\\vgChannelAssistClient.ini";
		if ( recvStr.GetLength() > 17)
		{
			CString tempStr = recvStr.Mid(17);
			srcFilePath += "\\vgChannelAssistClient";
			srcFilePath += tempStr.GetBuffer();
			tempStr.ReleaseBuffer();
			srcFilePath += ".ini";
		}
		else
		{
			srcFilePath += "\\vgChannelAssistClient.ini";
		}

		FILE *fp;

		//fp = fopen(srcFilePath.c_str(), "r");	//使用fopen编译时警告不安全
		fopen_s(&fp, srcFilePath.c_str(), "r");

		if (fp == NULL)
		{
			CString strWarning;
			strWarning.Format("ChannelAssistClient.exe 打开配置文件失败！\n请确认%s 文件存在", srcFilePath.c_str());
			AfxMessageBox(strWarning);
			return;
		}
		else
		{
			fseek(fp, 0, SEEK_END);
			int iEnd = ftell(fp);
			fseek(fp, 0, SEEK_SET);
			int iStart = ftell(fp);

			int m_uiFileLen = iEnd - iStart;

			char * ucpBuffer = NULL;
			ucpBuffer = new char[m_uiFileLen];

			size_t numofRead = fread(ucpBuffer, 1, m_uiFileLen, fp);

			string strInFile(ucpBuffer);

			size_t charcaterNum = strInFile.find_first_of("\n", 1);

			strExeFilePath = strInFile.substr(0,charcaterNum);

			m_ProgerssName = strExeFilePath;

			strvgPath = strInFile;

			strvgPath.erase( 0, charcaterNum+1 );

			if (strvgPath.length() > (numofRead - charcaterNum))
			{
				strvgPath.erase(numofRead - charcaterNum);
			}

			delete ucpBuffer;
			ucpBuffer = NULL;

			fclose(fp);
		}

		// ---------------------------------------------------------------------
#endif
		

		ShExecInfo.cbSize = sizeof(SHELLEXECUTEINFO);
		ShExecInfo.fMask     = NULL;
		ShExecInfo.hwnd      = NULL;
		ShExecInfo.lpVerb    = NULL;
		//ShExecInfo.lpVerb	 = _T("open");

		//从配置文件中读取执行文件的绝对路径,可以是 .exe也可以使 .vg 
		ShExecInfo.lpFile	 = strExeFilePath.c_str();		
		ShExecInfo.lpParameters =  strvgPath.c_str();	//向VRGIS传递的参数(vg的路径和是否打开三通道、全屏，来自读取的文件)

		ShExecInfo.lpDirectory  = NULL;

		ShExecInfo.nShow        = SW_SHOWMAXIMIZED;  // 最大化显示这个程序
		ShExecInfo.hInstApp = NULL;
		ShExecInfo.hProcess = NULL;

		//string::size_type found2 = strParamaInFile.find_last_of( "\\/" );
		//strvgConfigPath = strParamaInFile.substr( 0 , found2 );
		//strvgConfigPath += "\\data.ini";

		//fstream Write_to_File(strvgConfigPath.c_str(), ios_base::out);	//发现fstream 不能正确读取中文路径下的文件
		//Write_to_File << strvgPath;
		//Write_to_File.close();

		//如果程序已经打开就退出
		if( FindWindow(NULL,"VR-GIS企业版 Platform 2.0")) return;

		ShellExecuteEx(&ShExecInfo);

		DWORD waitStatus = WaitForSingleObject(ShExecInfo.hProcess,INFINITE);

		if (WAIT_ABANDONED)
		{
			CString strSend;
			strSend.Format("IP地址为:%s的客户端收到启动信息", m_ownAddeess.c_str());

			addrSnd.sin_port = htons(8694);

			sendto(chanRecvSocket,strSend,strSend.GetLength()+1,0,
				(SOCKADDR*)&addrSnd,sizeof(SOCKADDR));
		}
		//fstream Write_File_Null(strvgConfigPath.c_str(), ios_base::out);
		//Write_File_Null << endl;
		//Write_File_Null.close();

	}
	else if (recvStr == "VRGISendChannel")
	{
		//FindWindow的两个参数可以帮助你定位一个窗口.动态库版
		HWND hWnd = ::FindWindow(NULL, _T("VR-GIS企业版 Platform 2.0"));
		if (NULL != hWnd) 
		{
			::SendMessage(hWnd, WM_CLOSE, 0, 0);
		}

		hWnd = ::FindWindow(NULL, _T("VR-GIS Platform 2.0"));
		if ( NULL != hWnd)
		{
			::SendMessage(hWnd, WM_CLOSE, 0, 0);
		}

		if ( !m_ProgerssName.empty())
		{
			string::size_type found = m_ProgerssName.find_last_of( "\\/" );
			string srcFilePath = m_ProgerssName.substr(found + 1);

			vgkillProgress(srcFilePath.c_str());	//结束进程
		}

	}
	else if ( recvStr == "vrgisReStartComputer" )	
	{
		reStartComputer(false);
	}
	else if (recvStr == "vrgisEndComputer")
	{
		reStartComputer(true);
	}

	delete [] pbuf;
	pbuf = NULL;
}
//-------------------------------------------------------------------

void reStartComputer(bool bclose)	// 关闭或重启计算机
{
	OSVERSIONINFO OsVerInfo;		//保存系统版本信息的数据结构 
	OsVerInfo.dwOSVersionInfoSize=sizeof(OSVERSIONINFO); 
	GetVersionEx(&OsVerInfo);		//取得系统的版本信息 
	if(OsVerInfo.dwPlatformId == VER_PLATFORM_WIN32_NT) 
	{ 
		TOKEN_PRIVILEGES tkp; 
		HANDLE hToken; 

		if (!OpenProcessToken(GetCurrentProcess(),TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken))  
		{ 
			AfxMessageBox("打开进程标识失败！");
		} 

		LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME,&tkp.Privileges[0].Luid); //获得本地机唯一的标识 
		tkp.PrivilegeCount = 1;   
		tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;  
		AdjustTokenPrivileges(hToken, FALSE, &tkp, 0,(PTOKEN_PRIVILEGES) NULL, 0); //调整获得的权限 

		if (GetLastError() != ERROR_SUCCESS)  
		{ 
			AfxMessageBox("打开进程标识失败！");
		} 
		BOOL fResult = FALSE;
		if (bclose)									//关机
		{
			fResult =InitiateSystemShutdown(  
				NULL,								// 要关的计算机用户名,可在局域网网中关掉对方的机器，NULL表示关本机 
				"WINDOWS将在以上时间内关闭，请做好保存工作!",  // 显示的消息 
				60,									// 关机所需的时间 
				TRUE,                                  
				FALSE);								//设为TRUE为重起，设为FALSE为关机 

		}
		else										//重启
		{
			fResult =InitiateSystemShutdown(  
				NULL,
				"WINDOWS将在以上时间内重新启动，请做好保存工作!",
				60,
				TRUE,
				TRUE);								
		}

		if(!fResult)  
		{  
			AfxMessageBox("打开进程标识失败！");
		}  

		tkp.Privileges[0].Attributes = 0;  
		AdjustTokenPrivileges(hToken, FALSE, &tkp, 0,(PTOKEN_PRIVILEGES) NULL, 0);  

		if (GetLastError() != ERROR_SUCCESS)  
		{ 
			AfxMessageBox("关机权限获取失败!");
		} 

		if (bclose)
		{
			ExitWindowsEx(EWX_SHUTDOWN, 0);
		}
		else
		{
			ExitWindowsEx(EWX_REBOOT, 0); 
		}
		//开始重启。如果在本工程中运行，只有这一句代码就可以实现计算机重启，但是使用Debug或Release文件夹中的exe却不可以重启计算机。
		//用Debug或Release文件夹中的exe要重启计算机的话，要if中的所有代码。因为VC++这个开发工具的线程拥有关机权限，本工程作为VC开发工具的
		//子进程继承了关机权限，所以可以实现关机或重启计算机。如果用Debug或Release文件夹中的exe，他作为独立的线程，没有关机权限，所以需要此if语句的代码来获得关机权限。
	} 
}
//-------------------------------------------------------------------

void vgkillProgress(const char* szExeName)		// 结束进程
{
	if (szExeName == NULL) 
		return; 

	int lsr = lstrlen(szExeName); 

	if (lsr == 0) 
		return; 

	PROCESSENTRY32 m_Progress; 

	HANDLE m_handle = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0); 

	if (((int)m_handle) != -1) 
	{ 
		m_Progress.dwSize = sizeof(m_Progress); 

		if (Process32First(m_handle, &m_Progress)) 
		{ 
			do 
			{ 
				if (lstrcmpi(szExeName, m_Progress.szExeFile + lstrlen(m_Progress.szExeFile) - lsr) == 0) 
				{ 
					HANDLE hProcessHandle; 
					hProcessHandle = OpenProcess(0x1F0FFF, true, m_Progress.th32ProcessID); 

					if (hProcessHandle != NULL) 
					{ 
						if (TerminateProcess(hProcessHandle, 0) != NULL) 
						{ 
							CloseHandle(hProcessHandle); 
						} 
					} 
					//CloseHandle(m_handle); 
					break; 
				} 

			}while ( Process32Next(m_handle, &m_Progress) ); 
		} 

		CloseHandle(m_handle); 
	} 

}
//-------------------------------------------------------------------

void CClientAssistantDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	//writeConfigFile_ini();
	writeConfigFile_XML();
	//OnOK();
	// Edit By FengYK @2010-04-03 14:32 单击保存时不再隐藏窗口
	//is_visible = false;
	//this->ShowWindow(SW_HIDE);
}
//-------------------------------------------------------------------

void CClientAssistantDlg::OnBnClickedBtnHide()
{
	// TODO: 在此添加控件通知处理程序代码
	is_visible = false;
	this->ShowWindow(SW_HIDE);
}
//-------------------------------------------------------------------

void CClientAssistantDlg::m_AddRow()
{
	CBCGPGridRow* pRow = m_wndGrid.CreateRow(m_wndGrid.GetColumnCount ());

	for (int i = 0; i < m_wndGrid.GetColumnCount();i++)
	{
		pRow->GetItem (i)->AllowEdit (TRUE);
	}

	pRow->GetItem (0)->SetValue (_T("场景名称:"));

	pRow->ReplaceItem (1, new CFileItem (_T("VRGIS Platform路径:")));
	pRow->ReplaceItem (2, new CFileItem (_T("VG文件路径:")));

	_FullScreen = new CBCGPGridCheckItem (TRUE);
	_startChannel = new CBCGPGridCheckItem (TRUE);
	_softBlend = new CBCGPGridCheckItem (TRUE);		// 是否开启软融合 
	pRow->ReplaceItem (3, _FullScreen);
	pRow->ReplaceItem (4, _startChannel);
	pRow->ReplaceItem(5, _softBlend);

	CBCGPGridItem* pItem;
	pItem = new CBCGPGridItem (_T("客户端"));
	pItem->AddOption (_T("客户端"), TRUE);
	pItem->AddOption(_T("服务器"), TRUE);
	pRow->ReplaceItem (6, pItem);

	m_wndGrid.AddRow(pRow, TRUE);
	UpdateData(FALSE);

}
void CClientAssistantDlg::OnBnClickedBtnAddrow()
{
	// TODO: 在此添加控件通知处理程序代码
	m_AddRow();
}
//-------------------------------------------------------------------
// 原来写的读取ini 配置文件的时候要用到的，现在没有使用
void CClientAssistantDlg::m_AddConfig()
{
	if ( !vec_str_config.empty())
	{
		vector<CString>::iterator iterBegin = vec_str_config.begin();
		vector<CString>::iterator iterEnd = vec_str_config.end();

		for ( iterBegin; iterBegin != iterEnd; iterBegin++ )
		{
			if ( iterBegin == iterEnd - 2)
			{
				return;
			}

			CString sceneName = (*iterBegin);
			CString exePath = (*(iterBegin + 1));
			CString str_cmd = (*(iterBegin + 2 ));
			
			CBCGPGridRow* pRow = m_wndGrid.CreateRow(m_wndGrid.GetColumnCount ());

			for (int i = 0; i < m_wndGrid.GetColumnCount();i++)
			{
				pRow->GetItem (i)->AllowEdit (TRUE);
			}
			
			// 场景名称
			pRow->GetItem(0)->SetValue(sceneName.AllocSysString(), TRUE);
			
			//	VRGISPlatform 路径
			pRow->ReplaceItem (1, new CFileItem (exePath));

			//	VG路径
			int firstNull = str_cmd.Find( _T(" "), 0);
			CString vgPath = str_cmd.Left( firstNull );
			pRow->ReplaceItem (2, new CFileItem (vgPath));

			//	全屏
			int secdNull = str_cmd.Find( _T(" "), firstNull+1);
			CString str_fullscreen = str_cmd.Mid( firstNull+1, secdNull - firstNull - 1 );
			if ( str_fullscreen == "-fs" )
			{
				_FullScreen = new CBCGPGridCheckItem (TRUE);
				pRow->ReplaceItem (3, _FullScreen);
			}
			else if ( str_fullscreen == "-nfs" )
			{
				_FullScreen = new CBCGPGridCheckItem (FALSE);
				pRow->ReplaceItem (3, _FullScreen);
			}

			// 开启多通道
			int thirdNull = str_cmd.Find( _T(" "), secdNull+1);
			CString str_startchan = str_cmd.Mid( secdNull+1, thirdNull - secdNull - 1 );
			if ( str_startchan == "-sc" )
			{
				_startChannel = new CBCGPGridCheckItem (TRUE);
				pRow->ReplaceItem (4, _startChannel);
			}
			else if ( str_startchan == "-nsc" )
			{
				_startChannel = new CBCGPGridCheckItem (FALSE);
				pRow->ReplaceItem (4, _startChannel);
			}

			// 开启软融合(边缘融合和几何校正)blend and adjust
			int fourthNull = str_cmd.Find( _T(" "), thirdNull+1);
			CString str_softBlend = str_cmd.Mid( thirdNull+1, fourthNull - thirdNull - 1 );
			if ( str_softBlend == "-baa" )	// blend and adjust
			{
				_softBlend = new CBCGPGridCheckItem (TRUE);
				pRow->ReplaceItem (5, _softBlend);
			}
			else if ( str_startchan == "-nbaa" )
			{
				_softBlend = new CBCGPGridCheckItem (FALSE);
				pRow->ReplaceItem (5, _softBlend);
			}

			// 客户端或服务器
			CString str_servType = str_cmd.Mid( thirdNull+1, str_cmd.GetLength() - thirdNull );
			if ( str_servType == "-1")
			{
				CBCGPGridItem* pItem;
				pItem = new CBCGPGridItem (_T("客户端"));
				pItem->AddOption (_T("客户端"), TRUE);
				pItem->AddOption(_T("服务器"), TRUE);
				pRow->ReplaceItem (6, pItem);
			}
			else if ( str_servType == "-0")
			{
				CBCGPGridItem* pItem;
				pItem = new CBCGPGridItem (_T("服务器"));
				pItem->AddOption (_T("客户端"), TRUE);
				pItem->AddOption(_T("服务器"), TRUE);
				pRow->ReplaceItem (6, pItem);
			}
			
			m_wndGrid.AddRow(pRow, TRUE);

			UpdateData( FALSE );

			iterBegin++;
			iterBegin++;
		}

	}
}
//-------------------------------------------------------------------
void CClientAssistantDlg::readConfigFile_XML()
{
	char szModule[MAX_PATH] ;      
	::GetModuleFileName (NULL, szModule, MAX_PATH);

	string srcFolder(szModule);

	string::size_type found = srcFolder.find_last_of( "\\/" );
	string srcFilePath = srcFolder.substr( 0 , found );
	string strName1 = srcFolder.substr(found + 1, srcFolder.length() - found - 5);

	CString configFilePath;
	int sceneCount = 0;

	configFilePath.Format( "%s\\%s.xml", srcFilePath.c_str(), strName1.c_str() );

	bool isreadok = vgConfig::XMLConfigManager::getSingleton().LoadXmlDocument( configFilePath );
	
	if ( !isreadok )
	{
		CString warning;
		warning.Format("读取配置文件%s失败!\n请检查文件是否存在!", configFilePath);
		AfxMessageBox(warning);
		return;
	}

	// 界面控制参数
	if ( vgConfig::XMLConfigManager::getSingleton().FindSection( _T("Interface")) )
	{
		vgConfig::SectionData secInface = vgConfig::XMLConfigManager::getSingleton().GetCurrentValue(_T("Interface"));

		int show_hide = vgConfig::XMLConfigManager::getSingleton().GetIntValue( _T("Interface"), _T("Interface") );
		
		if ( show_hide == 1 )
		{
			is_visible = true;
		}
		else if ( show_hide == 0 )
		{
			is_visible = false;
		}
	}

	// 与场景有关的参数
	if ( vgConfig::XMLConfigManager::getSingleton().FindSection( _T("SceneInfo") ) )
	{
		vgConfig::SectionData scene = vgConfig::XMLConfigManager::getSingleton().GetCurrentValue(_T("SceneInfo"));

		sceneCount = vgConfig::XMLConfigManager::getSingleton().GetIntValue( _T("SceneInfo"), _T("SceneCount") );
		
		for ( int i = 0; i < sceneCount; i++ )
		{
			CString str_sceneName;

			vgConfig::SectionData tempSecData = vgConfig::XMLConfigManager::getSingleton().GetCurrentValue( _T("SceneInfo") );
			
			str_sceneName = tempSecData._Currentkeyvalue[i+1];

			if ( vgConfig::XMLConfigManager::getSingleton().FindSection( str_sceneName ) )
			{
				vgConfig::SectionData sceneInfo = vgConfig::XMLConfigManager::getSingleton().GetCurrentValue( str_sceneName );

				CString vrgis_exePath = sceneInfo._Currentkeyvalue[0];
				CString vg_path = sceneInfo._Currentkeyvalue[1];
				CString strFullScreen = sceneInfo._Currentkeyvalue[2];
				CString strStartChan = sceneInfo._Currentkeyvalue[3];
				CString strSoftBlend = sceneInfo._Currentkeyvalue[4];
				CString strServType = sceneInfo._Currentkeyvalue[5];

				CBCGPGridRow* pRow = m_wndGrid.CreateRow(m_wndGrid.GetColumnCount ());

				for (int i = 0; i < m_wndGrid.GetColumnCount();i++)
				{
					pRow->GetItem (i)->AllowEdit (TRUE);
				}
				
				// 场景名称
				pRow->GetItem(0)->SetValue(str_sceneName.AllocSysString(), TRUE);

				//	VRGISPlatform 路径
				pRow->ReplaceItem (1, new CFileItem (vrgis_exePath));

				//	VG路径			
				pRow->ReplaceItem (2, new CFileItem (vg_path));

				//	全屏
				if ( strFullScreen == "-fs" )
				{
					_FullScreen = new CBCGPGridCheckItem (TRUE);
					pRow->ReplaceItem (3, _FullScreen);
				}
				else if ( strFullScreen == "-nfs" )
				{
					_FullScreen = new CBCGPGridCheckItem (FALSE);
					pRow->ReplaceItem (3, _FullScreen);
				}

				// 开启多通道
				if ( strStartChan == "-sc" )
				{
					_startChannel = new CBCGPGridCheckItem (TRUE);
					pRow->ReplaceItem (4, _startChannel);
				}
				else if ( strStartChan == "-nsc" )
				{
					_startChannel = new CBCGPGridCheckItem (FALSE);
					pRow->ReplaceItem (4, _startChannel);
				}

				//	开启边缘融合和几何校正
				if ( strSoftBlend == "-baa" )
				{
					_softBlend = new CBCGPGridCheckItem (TRUE);
					pRow->ReplaceItem (5, _softBlend);
				}
				else if ( strSoftBlend == "-nbaa" )
				{
					_softBlend = new CBCGPGridCheckItem (FALSE);
					pRow->ReplaceItem (5, _softBlend);
				}

				// 客户端或服务器
				if ( strServType == _T("客户端") )
				{
					CBCGPGridItem* pItem;
					pItem = new CBCGPGridItem (_T("客户端"));
					pItem->AddOption (_T("客户端"), TRUE);
					pItem->AddOption(_T("服务器"), TRUE);
					pRow->ReplaceItem (6, pItem);
				}
				else if ( strServType == _T("服务器") )
				{
					CBCGPGridItem* pItem;
					pItem = new CBCGPGridItem (_T("服务器"));
					pItem->AddOption (_T("客户端"), TRUE);
					pItem->AddOption(_T("服务器"), TRUE);
					pRow->ReplaceItem (6, pItem);
				}

				m_wndGrid.AddRow(pRow, TRUE);

				UpdateData( FALSE );

			}
		}
	}
}
//-------------------------------------------------------------------
void CClientAssistantDlg::writeConfigFile_XML()
{
	char szModule[MAX_PATH] ;      
	::GetModuleFileName (NULL, szModule, MAX_PATH);

	string srcFolder(szModule);

	string::size_type found = srcFolder.find_last_of( "\\/" );
	string srcFilePath = srcFolder.substr( 0 , found );
	string strName1 = srcFolder.substr(found + 1, srcFolder.length() - found - 5);

	CString configFilePath;

	configFilePath.Format( "%s\\%s.xml", srcFilePath.c_str(), strName1.c_str() );

	vgConfig::XMLConfigManager::getSingleton().LoadXmlDocument(configFilePath);

	for ( int i = 0; i < m_wndGrid.GetRowCount(); i++ )
	{
		CBCGPGridRow *pRow = m_wndGrid.GetRow(i);
		CString str_sceneName(pRow->GetItem(0)->GetValue().bstrVal);
		bool isHave = true;

		if ( !vec_str_config.empty())
		{
			vector<CString>::iterator iterBegin = vec_str_config.begin();
			vector<CString>::iterator iterEnd = vec_str_config.end();

			for ( iterBegin; iterBegin != iterEnd; iterBegin++ )
			{
				if ( (*iterBegin) == str_sceneName )
				{
					isHave = false;
				}
			}

		}

		if ( isHave )
		{
			vec_str_config.push_back(str_sceneName);
		}

	}

	CString strRowCount;
	strRowCount.Format("%d", vec_str_config.size());
	// CString strRowCount;		// 不能使用RowCount, 因为XML 写文件时将
	// Section 和 Key 都相同的
	// strRowCount.Format("%d", m_wndGrid.GetRowCount());

	vgConfig::XMLConfigManager::getSingleton().AddKeys(_T("Interface"),		// 控制对话框的显示/隐藏
		_T("Interface"), _T("1"));

	vgConfig::XMLConfigManager::getSingleton().AddKeys(_T("SceneInfo"), 
		_T("SceneCount"), strRowCount);

	for ( int i = 0; i < m_wndGrid.GetRowCount(); i++ )
	{
		CBCGPGridRow *pRow = m_wndGrid.GetRow(i);
		CString str_sceneName(pRow->GetItem(0)->GetValue().bstrVal);

		vgConfig::XMLConfigManager::getSingleton().AddKeys(_T("SceneInfo"), 
			str_sceneName, str_sceneName);
	}

	for (int i=0; i<m_wndGrid.GetRowCount(); i++)
	{
		CBCGPGridRow *pRow = m_wndGrid.GetRow(i);

		CString sceneName(pRow->GetItem(0)->GetValue().bstrVal);
		CString vrgis_exePath(pRow->GetItem(1)->GetValue().bstrVal);
		CString vg_path(pRow->GetItem(2)->GetValue().bstrVal);

		int b_fullScreen = pRow->GetItem(3)->GetValue();
		int b_startChan = pRow->GetItem(4)->GetValue();
		int b_softBlend = pRow->GetItem(5)->GetValue();

		CString strFullScreen;
		CString strStartChan;
		CString strSoftBlend;

		if ( b_fullScreen == 0 )		// 是否选择全屏
		{
			strFullScreen.Format("%s", _T("-nfs"));
		}
		else if ( b_fullScreen == -1 )
		{
			strFullScreen.Format("%s", _T("-fs"));
		}

		if ( b_startChan == 0 )			// 是否选择开启多通道
		{
			strStartChan.Format("%s", _T("-nsc"));
		}
		else if ( b_startChan == -1 )
		{
			strStartChan.Format("%s", _T("-sc"));
		}

		if ( b_softBlend == 0 )			// 是否选择开启软融合
		{
			strSoftBlend.Format("%s", _T("-nbaa"));
		}
		else if ( b_softBlend == -1 )
		{
			strSoftBlend.Format("%s", _T("-baa"));
		}

		CString strServType(pRow->GetItem(6)->GetValue().bstrVal);

		vgConfig::XMLConfigManager::getSingleton().AddKeys(sceneName, 
			_T("vrgis_exePath"), vrgis_exePath);
		vgConfig::XMLConfigManager::getSingleton().AddKeys(sceneName, 
			_T("vg_path"), vg_path);
		vgConfig::XMLConfigManager::getSingleton().AddKeys(sceneName, 
			_T("FullScreen"), strFullScreen);
		vgConfig::XMLConfigManager::getSingleton().AddKeys(sceneName, 
			_T("StartChannel"), strStartChan);
		vgConfig::XMLConfigManager::getSingleton().AddKeys(sceneName, 
			_T("SoftBlend"), strSoftBlend);
		vgConfig::XMLConfigManager::getSingleton().AddKeys(sceneName, 
			_T("ServerType"), strServType);		
	}

	vgConfig::XMLConfigManager::getSingleton().SaveXML(configFilePath);

}
//-------------------------------------------------------------------
void CClientAssistantDlg::OnBnClickedBenDeleterow()
{
	// TODO: 在此添加控件通知处理程序代码
	CBCGPGridRow *pNowRow = m_wndGrid.GetCurSel();

	if ( pNowRow != NULL )
	{
		CString sceneName(pNowRow->GetItem(0)->GetValue().bstrVal);
		
		char szModule[MAX_PATH] ;      
		::GetModuleFileName (NULL, szModule, MAX_PATH);

		string srcFolder(szModule);

		string::size_type found = srcFolder.find_last_of( "\\/" );
		string srcFilePath = srcFolder.substr( 0 , found );
		string strName1 = srcFolder.substr(found + 1, srcFolder.length() - found - 5);

		CString configFilePath;
		int sceneCount = 0;

		configFilePath.Format( "%s\\%s.xml", srcFilePath.c_str(), strName1.c_str() );
		
		bool isreadok = vgConfig::XMLConfigManager::getSingleton().LoadXmlDocument( configFilePath );

		if ( !isreadok )
		{
			//CString warning;
			//warning.Format("读取配置文件%s失败!\n请检查文件是否存在!", configFilePath);
			//AfxMessageBox(warning);
			return;
		}

		// 删除配置文件中的相关信息
		if ( vgConfig::XMLConfigManager::getSingleton().FindSection( sceneName ) )
		{
			vgConfig::XMLConfigManager::getSingleton().RemoveKeys(_T("SceneInfo"), sceneName);
			vgConfig::XMLConfigManager::getSingleton().RemoveSection( sceneName );
			CString strRowCount;
			strRowCount.Format("%d", m_wndGrid.GetRowCount() - 1);

			vgConfig::XMLConfigManager::getSingleton().AddKeys(_T("SceneInfo"), 
				_T("SceneCount"), strRowCount);
			vgConfig::XMLConfigManager::getSingleton().SaveXML(configFilePath);
		}

		m_wndGrid.RemoveRow( pNowRow->GetRowId(), TRUE );

	}
}
//-------------------------------------------------------------------
