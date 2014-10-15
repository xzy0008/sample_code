// D:\___NewVersion\vrgis\src\vgSuperPlatform\DlgChannelParam.cpp : 实现文件
//

#include "vgStableHeaders.h"
#include "vgChannel/DlgChannelParam.h"
#include "vgChannel/vgcChannelManager.h"

// DlgChannelParam 对话框

IMPLEMENT_DYNAMIC(DlgChannelParam, CDialog)

DlgChannelParam::DlgChannelParam(CWnd* pParent /*=NULL*/)
	: CDialog(DlgChannelParam::IDD, pParent)
	, m_ipAddress(0)
	, m_serverPort(0)
	, m_clientPort(0)
	, m_leftEdge(0)
	, m_rightEdge(0)
	, m_hOffset(0)
	, m_vOffset(0)
	, m_cameraOffset(0)
	, dwIPServerAddres(0)
	, m_eyePosOffset(0)
{

}

DlgChannelParam::~DlgChannelParam()
{
}

void DlgChannelParam::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT2, m_leftEdge);
	DDX_Text(pDX, IDC_EDIT11, m_rightEdge);
	DDX_Text(pDX, IDC_EDIT3, m_hOffset);
	DDX_Text(pDX, IDC_EDIT4, m_vOffset);
	DDX_Control(pDX, IDC_LIST_BOARD, m_wndGridLocation);
	DDX_Text(pDX, IDC_CAMERA_POS, m_cameraOffset);
	DDV_MinMaxInt(pDX, m_cameraOffset, 0, 10000);
	DDX_IPAddress(pDX, IDC_IPSERV, dwIPServerAddres);
	//DDX_Control(pDX, IDC_IPSERV, m_IPControl);
	DDX_Text(pDX, IDC_EYEPOS, m_eyePosOffset);
}


BEGIN_MESSAGE_MAP(DlgChannelParam, CDialog)
	ON_WM_CREATE()
	ON_WM_LBUTTONUP()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_UPDATE_PARAM, &DlgChannelParam::OnBnClickedUpdateParam)
	ON_WM_DESTROY()
	ON_NOTIFY(IPN_FIELDCHANGED, IDC_IPSERV, &DlgChannelParam::OnIpnFieldchangedIpserv)
	ON_BN_CLICKED(IDC_BTN_SAVECHANNEL, &DlgChannelParam::OnBnClickedBtnSavechannel)
END_MESSAGE_MAP()


// DlgChannelParam 消息处理程序

int DlgChannelParam::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
	{
		AfxMessageBox("Error.");
		return -1;
	}

	return 0;
}

BOOL DlgChannelParam::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	// TODO:  在此添加您专用的创建代码
	UpdateData ();

	// TODO: Add extra initialization here
	CRect rectGrid;
	m_wndGridLocation.GetClientRect (&rectGrid);

	m_wndGridLocation.MapWindowPoints (this, &rectGrid);

	m_wndGrid.Create (WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER, rectGrid, this, (UINT)-1);
	m_wndGrid.EnableHeader (TRUE, BCGP_GRID_HEADER_MOVE_ITEMS);

	//m_wndGrid.SetReadOnly ();

	m_wndGrid.InsertColumn (0, _T("IP地址"), 120);
	m_wndGrid.InsertColumn (1, _T("位置"), 50);

	UpdateData(FALSE);

	for (int i=0; i<vgChannel::ChannelManager::getSingleton().getInComeClientNum(); i++)
	{
		vgChannel::ClientInfo_t info = vgChannel::ChannelManager::getSingleton().getClientInfo(i);
		
		SOCKADDR_IN addr = info.clientSocketAddr;
		char*p  =  inet_ntoa(addr.sin_addr);   

		CBCGPGridRow* pRow = m_wndGrid.CreateRow(m_wndGrid.GetColumnCount ());

		for (int i = 0; i < m_wndGrid.GetColumnCount ();i++)
		{
			pRow->GetItem (i)->AllowEdit (FALSE);
		}
		//----------
		// Combobox:
		//----------
		pRow->GetItem(0)->SetValue (p);
		CString str;
		if (info.controlParam.channelNum > 0)
		{
			str.Format("+%d", info.controlParam.channelNum);
		}
		else
		{
			str.Format("%d", info.controlParam.channelNum);
		}

		CBCGPGridItem* pItem;
		
		if (str != "-2")
		{
			pItem = new CBCGPGridItem (str.GetString());
		}
		else
		{
			pItem = new CBCGPGridItem ("");
		}

		pItem->AddOption ("-1", TRUE);
		pItem->AddOption("0", TRUE);
		pItem->AddOption ("+1", TRUE);
		int clientNum = vgChannel::ChannelManager::getSingleton().getInComeClientNum();
		if (clientNum > 2)
		{
			pItem->AddOption("-11", TRUE);
			pItem->AddOption("10", TRUE);
			pItem->AddOption("+11", TRUE);
		}

		pRow->ReplaceItem (1, pItem);

		m_wndGrid.AddRow(pRow, TRUE);
	}
// 	CBCGPGridRow* pRow = m_wndGrid.CreateRow(m_wndGrid.GetColumnCount ());
// 
// 	for (int i = 0; i < m_wndGrid.GetColumnCount ();i++)
// 	{
// 		pRow->GetItem (i)->AllowEdit (FALSE);
// 	}
	//设置IP地址控件显示的的IP地址
	dwIPServerAddres = vgChannel::ChannelManager::getSingleton().GetServerIP();
	UpdateData(FALSE);

	m_wndGrid.SetWholeRowSel(TRUE);

	sLastRow = NULL;
	SetTimer(1, 100, NULL);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void DlgChannelParam::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	// AfxMessageBox("Lbutton up");
	CDialog::OnLButtonUp(nFlags, point);
}

void DlgChannelParam::OnTimer(UINT_PTR nIDEvent)
{
	CDialog::OnTimer(nIDEvent);
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	static int numofClient = vgChannel::ChannelManager::getSingleton().getInComeClientNum();

	int num = vgChannel::ChannelManager::getSingleton().getInComeClientNum();

	// 判断是否有新的客户端进入更新界面.
	if (numofClient != num)
	{
		numofClient = num;
		SOCKADDR_IN addr = vgChannel::ChannelManager::getSingleton().getClientSockAddr(numofClient-1);
		char*p  =  inet_ntoa(addr.sin_addr);   

		CBCGPGridRow* pRow = m_wndGrid.CreateRow(m_wndGrid.GetColumnCount ());

		for (int i = 0; i < m_wndGrid.GetColumnCount ();i++)
		{
			pRow->GetItem (i)->AllowEdit (FALSE);
		}
		//----------
		// Combobox:
		//----------
		pRow->GetItem(0)->SetValue (p);

		CBCGPGridItem* pItem = new CBCGPGridItem ("");

		pItem->AddOption ("-1", TRUE);
		pItem->AddOption ("0", TRUE);
		pItem->AddOption ("+1", TRUE);
		if (num > 2)
		{
			pItem->AddOption("-11", TRUE);
			pItem->AddOption("10", TRUE);
			pItem->AddOption("+11", TRUE);
		}

		pRow->ReplaceItem (1, pItem);

		m_wndGrid.AddRow(pRow, TRUE);
	}

	m_wndGrid.Invalidate(true);

	// 更新数据
	CBCGPGridRow *pNowRow = m_wndGrid.GetCurSel();

	// 是不是选择变更，如果变更就更新界面数据
	if (pNowRow != NULL && pNowRow != sLastRow)
	{
		CString ipCStr(pNowRow->GetItem(0)->GetValue().bstrVal);
		vgChannel::ControlPackage* cp = vgChannel::ChannelManager::getSingleton().getControlInfoByIp(ipCStr.GetString());
		
		m_cameraOffset = cp->cameraOffset;
		m_hOffset = cp->hOffset;
		m_vOffset = cp->vOffset;
		m_leftEdge = cp->leftEdge;
		m_rightEdge = cp->rightEdge;
		m_eyePosOffset = cp->eyePosOffset;

		sLastRow = pNowRow;
		
		// VGK_SHOW("SELECT CHANGE.");
		UpdateData(FALSE);	
	}
	else if(sLastRow == NULL)
	{
		// VGK_SHOW("LAST IS NULL");
	}
	else if (pNowRow == NULL)
	{
		// VGK_SHOW("NOW IS NULL");
	}

	for (int i=0; i<m_wndGrid.GetRowCount(); i++)
	{
		// 检查通道号是否变更了，如果变更就发送消息给客户端
		CBCGPGridRow *pRow = m_wndGrid.GetRow(i);

		CString ipCStr(pRow->GetItem(0)->GetValue().bstrVal);
		CString strChannel( pRow->GetItem(1)->GetValue().bstrVal);
		int channel;
		if (strChannel == "-1")
		{
			channel = -1;
		}
		else if (strChannel == "+1")
		{
			channel = 1;
		}
		else if (strChannel == "-11")
		{
			channel = -11;
		}
		else if (strChannel == "+11")
		{
			channel = 11;
		}
		else if (strChannel == "10")
		{
			channel = 10;
		}
		else
		{
			return ;
		}

		vgChannel::ControlPackage* cp = vgChannel::ChannelManager::getSingleton().getControlInfoByIp(ipCStr.GetString());
		
		if (cp != NULL && channel != cp->channelNum)
		{
			cp->channelNum = channel;
			vgChannel::ChannelManager::getSingleton().setControlInfoByIp(ipCStr.GetString(), *cp);
		}
		else if (cp == NULL)
		{
			AfxMessageBox("Not found. ");
		}
	}
	
	// VGK_SHOW("Timer");

}

void DlgChannelParam::updateClientInfo()
{
	UpdateData(TRUE);

	CBCGPGridRow *pNowRow = m_wndGrid.GetCurSel();
	
	if (pNowRow == NULL)
	{
		AfxMessageBox("没有选择客户端.");
		return;
	}
	CString strIp(pNowRow->GetItem(0)->GetValue().bstrVal);
	CString strChannel( pNowRow->GetItem(1)->GetValue().bstrVal);

	vgChannel::ControlPackage *cp = vgChannel::ChannelManager::getSingleton().getControlInfoByIp(strIp.GetString());
	
	if (cp != NULL)
	{
		cp->cameraOffset = m_cameraOffset;
		cp->hOffset = m_hOffset;
		cp->vOffset = m_vOffset;
		cp->leftEdge = m_leftEdge;
		cp->rightEdge = m_rightEdge;
		cp->eyePosOffset = m_eyePosOffset;

		vgChannel::ChannelManager::getSingleton().setControlInfoByIp(strIp.GetString(), *cp);

		CString strChanFilePath = vgChannel::ChannelManager::getSingleton().getClientInfoPath();
		if (strChanFilePath.GetLength() == 0)
		{
			if (IDYES == MessageBox("配置文件不存在，是否创建？", "保存配置", MB_YESNO))
			{
				CString DefSav;
				DefSav.Format("%s","xml(*.xml)|*.xml|All Files (*.*)|*.*||");

				CFileDialog savDlg (FALSE, "xml", "ClientInfo.xml",
					OFN_FILEMUSTEXIST| OFN_HIDEREADONLY, DefSav, this);
				if (savDlg.DoModal() == IDOK)
				{
					strChanFilePath = savDlg.GetPathName();
					vgChannel::ChannelManager::getSingleton().setClientInfoPath(strChanFilePath);
				}
				else
				{
					return;
				}
			}
		}
		vgChannel::ChannelManager::getSingleton().saveClientInfotoXML(strIp, strChannel, 
			m_cameraOffset, m_hOffset, m_vOffset, m_eyePosOffset);
	}
	else
	{
		// VGK_SHOW("CP IS NULL");
	}
}

void DlgChannelParam::OnBnClickedUpdateParam()
{
	// TODO: 在此添加控件通知处理程序代码
	updateClientInfo();
}

void DlgChannelParam::OnDestroy()
{
	CDialog::OnDestroy();

	// TODO: 在此处添加消息处理程序代码
	delete this;
}

void DlgChannelParam::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类
	//保存参数到文件中
	int m_chanNum = vgChannel::ChannelManager::getSingleton().getChannelNum();
	if (m_chanNum != 0)//如果不是服务器端，就保存服务器的IP
	{
		vgChannel::ChannelManager::getSingleton().SaveChannelSetToFile();
	}
	CDialog::OnOK();
	DestroyWindow();
}

void DlgChannelParam::OnCancel()
{
	// TODO: 在此添加专用代码和/或调用基类

	CDialog::OnCancel();
	DestroyWindow();
}

void DlgChannelParam::OnIpnFieldchangedIpserv(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMIPADDRESS pIPAddr = reinterpret_cast<LPNMIPADDRESS>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	TRACE("ID ADDRESS %d \n", dwIPServerAddres);
	//当IP地址控件的IP改变时，重新设置服务器的IP
	vgChannel::ChannelManager::getSingleton().setServerIP(dwIPServerAddres);
	*pResult = 0;
}

void DlgChannelParam::OnBnClickedBtnSavechannel()//打开客户端配置文件
{
	// TODO: 在此添加控件通知处理程序代码
	/*if (strChanFilePath.Empty() == true)
	{*/
	CString strChanFilePath;
	CString DefOpen;
	DefOpen.Format("%s","xml(*.xml)|*.xml|");
	CFileDialog dlgvgch(true,"xml",
		NULL,OFN_HIDEREADONLY|OFN_CREATEPROMPT|OFN_NONETWORKBUTTON,DefOpen);

#if VGK_LANG_CHS
	dlgvgch.m_ofn.lpstrTitle = "打开多通道配置文件"; 
#else
	dlgvgch.m_ofn.lpstrTitle = "OpenMultiChannelConfigFile"
#endif
		if( dlgvgch.DoModal() == IDOK )
		{
			strChanFilePath = dlgvgch.GetPathName();
		}
		/*}*/

		if (strChanFilePath.GetLength() != 0)
		{
			vgChannel::ChannelManager::getSingleton().setClientInfoPath(strChanFilePath);
			vgChannel::ChannelManager::getSingleton().readClientInfofromXML();

			m_wndGrid.Invalidate(true);
			for (int i=0; i<m_wndGrid.GetRowCount(); i++)
			{
				CBCGPGridRow *pRow = m_wndGrid.GetRow(i);
				CString ipCStr(pRow->GetItem(0)->GetValue().bstrVal);
				vgChannel::ControlPackage* cp = vgChannel::ChannelManager::getSingleton().getControlInfoByIp(ipCStr.GetString());
				int chanNum = cp->channelNum;
				CString str;
				if (chanNum > 0)
				{
					str.Format("+%d", chanNum);
				}
				else
				{
					str.Format("%d", chanNum);
				}
				for (int i = 0; i < m_wndGrid.GetColumnCount ();i++)
				{
					pRow->GetItem (i)->AllowEdit (FALSE);
				}
				variant_t newVal;

				newVal.SetString(str.GetBuffer());
				pRow->GetItem(1)->SetValue(newVal);
			}
		}		
		
}
