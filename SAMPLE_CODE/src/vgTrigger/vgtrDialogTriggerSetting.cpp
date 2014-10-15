// DialogTriggerSetting.cpp : 实现文件
//

#include <vgStableHeaders.h>
#include <vgTriggerResource.h>
#include <vgTrigger/vgtrDialogTriggerSetting.h>

#include <vgTrigger/vgtrTriggerManager.h>
#include <vgTrigger/vgtrCommandFactory.h>


// CDialogTriggerSetting 对话框

IMPLEMENT_DYNAMIC(CDialogTriggerSetting, CDialog)

CDialogTriggerSetting::CDialogTriggerSetting(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogTriggerSetting::IDD, pParent)
	, m_attachName(_T(""))
	, m_triggerName(_T(""))
{
// 	vgTrigger::Trigger *pTrigger 
// 		= vgTrigger::TriggerManager::getSingleton().getCurrentSelectedTrigger();
// 
// 	m_attachName = pTrigger->getInnerNamePtr()->c_str();
}

CDialogTriggerSetting::~CDialogTriggerSetting()
{
}

void CDialogTriggerSetting::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_ATTACH_NAME, m_attachName);
	DDX_Control(pDX, IDC_COMBO_ATTACH_TYPE, m_attachType);
	DDX_Control(pDX, IDC_TAB_LOC, m_tabLoc);
	DDX_Control(pDX, IDC_CONFIG_COMBO, m_configComboBox);
	DDX_Control(pDX, IDC_COMBO_TIGGERNAME, m_triggerNameCombo);
}


BEGIN_MESSAGE_MAP(CDialogTriggerSetting, CDialog)
	ON_BN_CLICKED(IDOK, &CDialogTriggerSetting::OnBnClickedOk)
	ON_BN_CLICKED(IDC_UPDATE, &CDialogTriggerSetting::OnBnClickedUpdate)
	ON_CBN_SELCHANGE(IDC_CONFIG_COMBO, &CDialogTriggerSetting::OnCbnSelchangeConfigCombo)
	ON_CBN_SELCHANGE(IDC_COMBO_TIGGERNAME, &CDialogTriggerSetting::OnCbnSelchangeComboTiggername)
END_MESSAGE_MAP()


// CDialogTriggerSetting 消息处理程序

void CDialogTriggerSetting::OnBnClickedOk()
{
	return ;

	OnOK();
}

BOOL CDialogTriggerSetting::OnInitDialog()
{
	
	CDialog::OnInitDialog();

	//UpdateData(TRUE);
	// TODO:  在此添加额外的初始化

	vgTrigger::TriggerArray* pTriggerArray = vgTrigger::TriggerManager::getSingleton().getTriggerArrayPtr();
	
	m_triggerNameCombo.ResetContent();

	for (int i=0; i<pTriggerArray->size(); i++)
	{
		m_triggerNameCombo.AddString(pTriggerArray->at(i)->getName().c_str());
	}

 	vgTrigger::Trigger *pTrigger 
 		= vgTrigger::TriggerManager::getSingleton().getCurrentSelectedTrigger();
 
	m_configComboBox.ResetContent();
	m_configComboBox.AddString("<新建触发事件..>");

 	if (pTrigger != NULL)
 	{
		vgTrigger::CommandPtrArray* cmdPtr = 
			pTrigger->getCommandArrayPtr();

		for (int i=0; i<cmdPtr->size(); i++)
		{
			m_configComboBox.AddString(cmdPtr->at(i)->getName().c_str());
		}

 		m_triggerName = pTrigger->getName().c_str();

		m_triggerNameCombo.SelectString(0, pTrigger->getName().c_str());
 	}

	//UpdateData(FALSE);
	

	CRect rectTab;

	m_tabLoc.GetWindowRect (&rectTab);
	ScreenToClient (&rectTab);

	m_wndTab.Create (CBCGPTabWnd::STYLE_3D, rectTab, this, 1,
		CBCGPTabWnd::LOCATION_TOP);

	m_wndTab.SetImageList (IDB_ICON_VGSC_TABS, 16, RGB (255, 0, 255));

	m_wndEntrance.Create (ES_WANTRETURN|ES_AUTOVSCROLL | ES_MULTILINE  | WS_CHILD | WS_VISIBLE | WS_VSCROLL, CRect (0, 0, 10, 10), &m_wndTab, 1);
	m_wndEntrance.SetFont (&globalData.fontRegular);
	m_wndEntrance.SetWindowText (_T(""));

	m_wndExit.Create (ES_WANTRETURN|ES_AUTOVSCROLL | ES_MULTILINE  | WS_CHILD | WS_VISIBLE | WS_VSCROLL,  CRect (0, 0, 0, 0), &m_wndTab, 2);
	m_wndExit.SetFont (&globalData.fontRegular);
	m_wndExit.SetWindowText (_T(""));

	m_wndClick.Create (ES_WANTRETURN|ES_AUTOVSCROLL | ES_MULTILINE  | WS_CHILD | WS_VISIBLE | WS_VSCROLL,  CRect (0, 0, 0, 0), &m_wndTab, 3);
	m_wndClick.SetFont (&globalData.fontRegular);
	m_wndClick.SetWindowText (_T(""));


	m_wndTab.AddTab (&m_wndEntrance, "进入", 0, FALSE);
	m_wndTab.AddTab (&m_wndExit, "退出", 1, FALSE);
	m_wndTab.AddTab (&m_wndClick, "点击", 2, FALSE);
	
	UpdateData (FALSE);

	CBCGPTabWnd::Style style = CBCGPTabWnd::STYLE_3D;

	m_wndTab.ModifyTabStyle (style);
	m_wndTab.RecalcLayout ();
	m_wndTab.RedrawWindow ();

	m_wndTab.SetLocation (CBCGPTabWnd::LOCATION_TOP);
	// m_wndTab.EnableAutoColor (TRUE);

	m_wndTab.EnableTabSwap (FALSE);
	
	m_configComboBox.SetCurSel(0);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CDialogTriggerSetting::OnBnClickedUpdate()
{
	// TODO: 在此添加控件通知处理程序代码

	UpdateData(TRUE);
	
//	vgTrigger::Trigger *pTrigger 
//		= vgTrigger::TriggerManager::getSingleton().getCurrentSelectedTrigger();
		
	int nameLen = m_triggerNameCombo.GetLBTextLen(m_triggerNameCombo.GetCurSel());
	m_triggerNameCombo.GetLBText(m_triggerNameCombo.GetCurSel(),m_triggerName.GetBuffer(nameLen));
	
	vgTrigger::Trigger *pTrigger
		= vgTrigger::TriggerManager::getSingleton().getTriggerByName(m_triggerName.GetString());
	// 这里加个NULL判断

	if (pTrigger == NULL)
	{
		AfxMessageBox("请选择触发器");

		return ;
	}

	//string str(m_attachName);
	//string str = m_attachInfo.GetString();
	string name = m_attachName.GetString();
	
	if (name.length() == 0)
	{
		AfxMessageBox("事件名不能为空.");

		return ;
	}


	int nIndexSelected = m_attachType.GetCurSel();
	CString selectedCmd;
	int len = m_configComboBox.GetLBTextLen(m_configComboBox.GetCurSel());
	m_configComboBox.GetLBText(m_configComboBox.GetCurSel(), selectedCmd.GetBuffer(len));
	
	pTrigger->deleteCommandByName(selectedCmd.GetString());

	// 准备触发器事件
	vgTrigger::CommandID commandType = vgTrigger::CommandID(nIndexSelected);
	
	CString cmdParamCstr[3];
	m_wndEntrance.GetWindowText(cmdParamCstr[0]);
	m_wndExit.GetWindowText(cmdParamCstr[1]);
	m_wndClick.GetWindowText(cmdParamCstr[2]);
	
	String cmdParam[3];
	for (int i=0; i<3; i++)
	{
		cmdParam[i] = cmdParamCstr[i].GetString();
	}

	vgTrigger::CommandPtr pCmd;
	switch( commandType )
	{
	case vgTrigger::TRIGGER_COMMAND_MSG:
		// str = "进入范围;退出范围;点击";
		pCmd = vgTrigger::CommandFactory::generateCommand(
			vgTrigger::TRIGGER_COMMAND_MSG, 
			name, 
			cmdParam);
		break;

	case vgTrigger::TRIGGER_COMMAND_TEXT2D:
		pCmd = vgTrigger::CommandFactory::generateCommand(
			vgTrigger::TRIGGER_COMMAND_TEXT2D, 
			name,
			cmdParam/*pTrigger->getInnerNamePtr()*/);
		break;

	case vgTrigger::TRIGGER_COMMAND_SOUND3D:
		pCmd = vgTrigger::CommandFactory::generateCommand(
			vgTrigger::TRIGGER_COMMAND_SOUND3D, 
			name,
			cmdParam/*pTrigger->getInnerNamePtr()*/);
		break;

	case vgTrigger::TRIGGER_COMMAND_KEYFRAME:
		pCmd = vgTrigger::CommandFactory::generateCommand(
			vgTrigger::TRIGGER_COMMAND_KEYFRAME, 
			name,
			cmdParam/*pTrigger->getInnerNamePtr()*/);
		break;

	case vgTrigger::TRIGGER_COMMAND_AVI:
		pCmd = vgTrigger::CommandFactory::generateCommand(
			vgTrigger::TRIGGER_COMMAND_AVI, 
			name,
			cmdParam/*pTrigger->getInnerNamePtr()*/);
		break;

	case vgTrigger::TRIGGER_COMMAND_SCRIPT:

		pCmd = vgTrigger::CommandFactory::generateCommand(
			vgTrigger::TRIGGER_COMMAND_SCRIPT, 
			name,
			cmdParam
			/*pTrigger->getInnerNamePtr()*/);
		break;

	default:
		break;
	}

	if ( pCmd.isNull() )
	{
		AfxMessageBox("生成失败！");
		return;
	}

	pTrigger->regeditEvent(pCmd); 

	m_configComboBox.ResetContent();
	m_configComboBox.AddString("<新建触发事件..>");

	if (pTrigger != NULL)
	{
		vgTrigger::CommandPtrArray* cmdPtr = 
			pTrigger->getCommandArrayPtr();

		for (int i=0; i<cmdPtr->size(); i++)
		{
			m_configComboBox.AddString(cmdPtr->at(i)->getName().c_str());
		}
	}

	m_configComboBox.SelectString(0, pCmd->getName().c_str());

	::MessageBox(NULL, "添加/修改触发事件成功", "提示", MB_OK);
}

void CDialogTriggerSetting::OnCbnSelchangeConfigCombo()
{
	// TODO: 在此添加控件通知处理程序代码
	// int nIndexSelected = m_attachType.GetCurSel();

	int nameLen = m_triggerNameCombo.GetLBTextLen(m_triggerNameCombo.GetCurSel());

	m_triggerNameCombo.GetLBText(m_triggerNameCombo.GetCurSel(), m_triggerName.GetBuffer(nameLen));

	vgTrigger::Trigger *pTrigger 
		= vgTrigger::TriggerManager::getSingleton().getTriggerByName(m_triggerName.GetString());

// 	vgTrigger::Trigger *pTrigger 
// 		= vgTrigger::TriggerManager::getSingleton().getCurrentSelectedTrigger();
// 
	// 这里加个NULL判断
	if (pTrigger == NULL)
	{
		return ;
	}
	
	CString selectedCmd;
	m_configComboBox.GetLBText(m_configComboBox.GetCurSel(), selectedCmd);
	string name = selectedCmd.GetString();
	vgTrigger::CommandPtr cmd = pTrigger->getCommandByName(name.c_str());

	if (cmd.isNull())
	{
		m_attachType.SetCurSel(0);
		m_attachName = "";

		m_wndEntrance.SetWindowText("");
		m_wndExit.SetWindowText("");
		m_wndClick.SetWindowText("");

	}
	else
	{
		m_attachType.SetCurSel(cmd->getType());
		m_attachName = cmd->getName().c_str();

		m_wndEntrance.SetWindowText(cmd->getContectInfo(vgTrigger::TRIGGER_EVENT_ENTRENCE).c_str());
		m_wndExit.SetWindowText(cmd->getContectInfo(vgTrigger::TRIGGER_EVENT_EXIT).c_str());
		m_wndClick.SetWindowText(cmd->getContectInfo(vgTrigger::TRIGGER_EVENT_CLICK).c_str());

	}

	UpdateData(FALSE);
}

void CDialogTriggerSetting::updateControlData()
{
	// TODO: 在此添加控件通知处理程序代码
}
void CDialogTriggerSetting::OnCbnSelchangeComboTiggername()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);

	int nameLen = m_triggerNameCombo.GetLBTextLen(m_triggerNameCombo.GetCurSel());

	m_triggerNameCombo.GetLBText(m_triggerNameCombo.GetCurSel(), m_triggerName.GetBuffer(nameLen));
	
	// m_triggerName
	m_configComboBox.ResetContent();
	
	vgTrigger::Trigger *pTrigger 
		= vgTrigger::TriggerManager::getSingleton().getTriggerByName(m_triggerName.GetString());

	if (pTrigger != NULL)
	{
		m_configComboBox.AddString("<新建触发事件..>");
		
		vgTrigger::CommandPtrArray* cmdPtr = 
			pTrigger->getCommandArrayPtr();

		for (int i=0; i<cmdPtr->size(); i++)
		{
			m_configComboBox.AddString(cmdPtr->at(i)->getName().c_str());
		}

		m_triggerNameCombo.SelectString(0, pTrigger->getName().c_str());

	}

	m_attachName = "";
	m_configComboBox.SetCurSel(0);
	m_attachType.SetCurSel(0);

	m_wndClick.SetWindowText("");
	m_wndEntrance.SetWindowText("");
	m_wndExit.SetWindowText("");

	UpdateData(FALSE);

}
