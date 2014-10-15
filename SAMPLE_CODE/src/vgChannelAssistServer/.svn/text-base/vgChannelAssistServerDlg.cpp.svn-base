// channelAssistantDlg.cpp : 实现文件
//

#include "vgStableHeaders.h"
#include "vgChannelAssistServer/vgChannelAssistServer.h"
#include "vgChannelAssistServer/vgChannelAssistServerDlg.h"

#include <WinSock2.h>
#include <string>
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


static SOCKET	assitSendSocket;
static SOCKET	assitRecvSocket;
static SOCKADDR_IN addrSnd;

static DWORD	chanThreadID;
static HANDLE	assitReceiveHandle;

static DWORD WINAPI assitReceiveThread(LPVOID lpParameter);
static void assitReceive(long dataLength);
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


// CchannelAssistantDlg 对话框




CchannelAssistantDlg::CchannelAssistantDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CchannelAssistantDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CchannelAssistantDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_VGNAME, m_vgNameCombo);
}

BEGIN_MESSAGE_MAP(CchannelAssistantDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BTN_START_CHANNEL, &CchannelAssistantDlg::OnBnClickedBtnStartChannel)
	ON_BN_CLICKED(IDC_BTN_END_CHANNEL, &CchannelAssistantDlg::OnBnClickedBtnEndChannel)
	ON_BN_CLICKED(IDC_BTN_REBOOT, &CchannelAssistantDlg::OnBnClickedBtnReboot)
	ON_BN_CLICKED(IDC_BTN_SHUTDOWN, &CchannelAssistantDlg::OnBnClickedBtnShutdown)
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CchannelAssistantDlg 消息处理程序

BOOL CchannelAssistantDlg::OnInitDialog()
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
	//////////////////////////////////////////////////////////////////////////
	WSADATA wsd;

	int ret = WSAStartup(0x0202,&wsd);
	if(ret!=0)
	{
		WSACleanup();
	}
	//创建接收Socket
	assitRecvSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_IP); 

	if(assitRecvSocket == INVALID_SOCKET)
	{
		return false;
	}

	SOCKADDR_IN addr;
	ZeroMemory(&addr, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = INADDR_ANY;
	addr.sin_port = htons(8694);
	// 绑定接收使用的端口和地址
	ret = bind(assitRecvSocket, (struct sockaddr *)&addr, sizeof(addr));


	// 创建Server发送Socket
	assitSendSocket = socket(AF_INET,SOCK_DGRAM,IPPROTO_IP); 
	if(assitSendSocket == INVALID_SOCKET)
	{
		//return 0;
		AfxMessageBox("channelAssistant创建发送Socket失败");
	}

	
	//绑定发送
	ZeroMemory(&addrSnd,sizeof(addrSnd));
	addrSnd.sin_family = AF_INET;
	addrSnd.sin_addr.S_un.S_addr=htonl(INADDR_ANY);
	//获得广播的IP
	char hostName[255];   
	PHOSTENT hostinfo;
	std::string m_broadCastAddress;

	if(gethostname(hostName, sizeof(hostName))   ==   0)   
	{   
		if((hostinfo = gethostbyname(hostName)) != NULL)   
		{   
			m_broadCastAddress = inet_ntoa(*(struct in_addr *)*hostinfo->h_addr_list);   
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
		else		//IP地址最后是3位
		{
			m_broadCastAddress[m_broadCastAddress.length()-1] = '5';
			m_broadCastAddress[m_broadCastAddress.length()-2] = '5';
			m_broadCastAddress[m_broadCastAddress.length()-3] = '2';
		}

	} 

	addrSnd.sin_addr.s_addr = INADDR_ANY;
	ret = bind(assitSendSocket, (struct sockaddr *)&addrSnd, sizeof(addrSnd));
	addrSnd.sin_addr.s_addr = inet_addr(m_broadCastAddress.c_str());
	//addrSnd.sin_addr.s_addr = inet_addr("222.195.148.255");
	
	if(ret != 0)
	{
		//return 0;
		AfxMessageBox("channelAssistant绑定发送Socket失败");
	}

	assitReceiveHandle = 
		CreateThread(NULL, 0, assitReceiveThread, this, 0, &chanThreadID);

	SetThreadPriority( assitReceiveHandle, THREAD_PRIORITY_ABOVE_NORMAL);

	if( assitReceiveHandle == NULL )
	{
		return false;
	}
	//////////////////////////////////////////////////////////////////////////
	readvgName();
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CchannelAssistantDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CchannelAssistantDlg::OnPaint()
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
HCURSOR CchannelAssistantDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CchannelAssistantDlg::OnBnClickedBtnStartChannel()
{
	// TODO: 在此添加控件通知处理程序代码

	CString wndStr;

	int nSelIndex = 0;
	nSelIndex = m_vgNameCombo.GetCurSel();

	if ( -1 == nSelIndex )
	{
		AfxMessageBox("没有选中vg文件名，请重新选择！");
		return;
	}

	wndStr.GetBuffer(m_vgNameCombo.GetLBTextLen( nSelIndex ));
	m_vgNameCombo.GetLBText(m_vgNameCombo.GetCurSel(), wndStr);

	CString strSend;
	
	strSend.Format("VRGISstartChannel%s", wndStr.GetString());
	
	addrSnd.sin_port=htons(8695);
	sendto(assitSendSocket,strSend,strSend.GetLength()+1,0,
		(SOCKADDR*)&addrSnd,sizeof(SOCKADDR));

}

void CchannelAssistantDlg::OnBnClickedBtnEndChannel()
{
	// TODO: 在此添加控件通知处理程序代码

	CString strSend = "VRGISendChannel";
	addrSnd.sin_port=htons(8695);
	sendto(assitSendSocket,strSend,strSend.GetLength()+1,0,
		(SOCKADDR*)&addrSnd,sizeof(SOCKADDR));
}

void CchannelAssistantDlg::OnBnClickedBtnReboot()
{
	// TODO: 在此添加控件通知处理程序代码

	CString strSend = "vrgisReStartComputer";
	addrSnd.sin_port=htons(8695);
	sendto(assitSendSocket,strSend,strSend.GetLength()+1,0,
		(SOCKADDR*)&addrSnd,sizeof(SOCKADDR));

}

void CchannelAssistantDlg::OnBnClickedBtnShutdown()
{
	// TODO: 在此添加控件通知处理程序代码

	CString strSend = "vrgisEndComputer";
	addrSnd.sin_port=htons(8695);
	sendto(assitSendSocket,strSend,strSend.GetLength()+1,0,
		(SOCKADDR*)&addrSnd,sizeof(SOCKADDR));

}

void CchannelAssistantDlg::OnDestroy()
{
	CDialog::OnDestroy();

	// TODO: 在此处添加消息处理程序代码
	WSACleanup();
	closesocket(assitSendSocket);

}

DWORD WINAPI assitReceiveThread(LPVOID lpParameter)
{
	int ret;
	unsigned long lLength;

	while( TRUE )
	{
		ret = ioctlsocket(assitRecvSocket, FIONREAD, &lLength);
		if(ret != 0)
		{
			break;
		}
		else
		{
			if(lLength>0)
			{
				assitReceive(lLength);
			}
		}

		Sleep(10);
	}

	return 0;
}

void assitReceive(long dataLength)
{
	char *pbuf;
	int addr_len, iRecLen;;
	struct sockaddr_in addr;

	pbuf = new char[dataLength + 1];
	memset(pbuf, 0, dataLength + 1);

	addr_len = sizeof(addr);

	iRecLen = recvfrom(assitRecvSocket, pbuf, dataLength, 0,(struct sockaddr *)&addr, &addr_len);

	CString recvStr(pbuf);	//接收到的消息

	if( iRecLen <= 0 )
	{
		return;
	}
	else
	{
		AfxMessageBox(recvStr);
	}

}

void CchannelAssistantDlg::readvgName()
{
	char szModule[MAX_PATH] ;      
	::GetModuleFileName (NULL, szModule, MAX_PATH);

	string srcFolder(szModule);

	string::size_type found = srcFolder.find_last_of( "\\/" );
	string srcFilePath = srcFolder.substr( 0 , found );
	srcFilePath += "\\vgChannelAssistServer.ini";
	
	FILE *fp;

	fopen_s(&fp, srcFilePath.c_str(), "r");

	if (fp == NULL)
	{
		CString strWarning;
		strWarning.Format("ChannelAssistServer.exe 打开配置文件失败！\n请确认应用程序目录下存在%s文件", srcFilePath.c_str());
		AfxMessageBox(strWarning);
		return;
	}
	else
	{
		char str[256];
		int cnt = 0;

		while ( fgets(str, 256, fp) != NULL)
		{
			CString strInFile(str);

			int m_length = strInFile.GetLength();

			if ( strInFile.Right(1) == "\n")
			{
				strInFile.TrimRight("\n");
			}

			m_vgNameCombo.AddString(strInFile);
		}

		if ( m_vgNameCombo.GetCount() > 0)
		{
			m_vgNameCombo.SetCurSel(0);
		}

 		UpdateData(FALSE);

		fclose(fp);
	}
}