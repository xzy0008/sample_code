// D:\___visualVersion\from1297_trunkDLL-leshan\src_sdk\vgVisualPlatformDLL\vgLogonDialog.cpp : 实现文件
//

#include <vgStableHeaders.h>
#include <vgVisualPlatformDLL\vgLogonDialog.h>

#include <vgGlobal/vggSceneFileUtility.h>

// vgLogonDialog 对话框

IMPLEMENT_DYNAMIC(vgLogonDialog, CDialog)

vgLogonDialog::vgLogonDialog(CWnd* pParent /*=NULL*/)
	: CDialog(vgLogonDialog::IDD, pParent)
	, m_user(_T(""))
	, m_passWord(_T(""))
	, m_userName(_T(""))
	, m_status(_T(""))
{
	m_bLoading = false;
}

vgLogonDialog::~vgLogonDialog()
{
}

void vgLogonDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SCENE_COMBO, m_sceneCombo);
	DDX_Text(pDX, IDC_CONNECT_PASSWORD, m_passWord);
	DDX_Text(pDX, IDC_CONNECT_USER, m_userName);
	DDX_Control(pDX, IDC_CONNET_IP, m_ipControl);
	DDX_Text(pDX, IDC_CONNECT_STATUES, m_status);
}


BEGIN_MESSAGE_MAP(vgLogonDialog, CDialog)
	ON_BN_CLICKED(IDC_CONNECT_SERVER, &vgLogonDialog::OnBnClickedConnectServer)
	ON_BN_CLICKED(IDOK, &vgLogonDialog::OnBnClickedOk)
	ON_WM_TIMER()
END_MESSAGE_MAP()

void vgLogonDialog::OnTimer(UINT_PTR nIDEvent)
{
	static int numOfDot;
	static bool enableUpdate = false;
	
	UpdateData(TRUE);

	if (m_bLoading)
	{
		numOfDot ++;

		if (numOfDot > 6)
		{
			numOfDot = 0;
		}
		
		string outString = "状态 - 通信中";
		
		for (int i=0; i<numOfDot; i++)
		{
			outString += ".";
		}

		m_status = outString.c_str();

		enableUpdate = true;
	}
	else
	{
		m_status = "状态 - 客户端空闲";
	}

	//if (enableUpdate)
	{
		UpdateData(FALSE);
	}

	CDialog::OnTimer(nIDEvent);
}

 BOOL vgLogonDialog::OnInitDialog()
 {
	 __super::OnInitDialog();

 	// this->SetTimer(1, 300, NULL);

	 m_status = "状态 - 客户端空闲";

	 UpdateData(FALSE);

 	return TRUE;
 }

void vgLogonDialog::OnBnClickedConnectServer()
{
	// TODO: 在此添加控件通知处理程序代码
	CString ip;

	m_ipControl.GetWindowText(ip);

	// AfxMessageBox(ip);

	m_scenePath = "\\\\";
	m_scenePath += ip.GetString();

	m_scenePath += "\\vg\\";

	string indexPath = m_scenePath + "scene.txt";



	FILE *fp = fopen(indexPath.c_str(), "r");

	if (fp == NULL)
	{
		AfxMessageBox("连接远程服务器失败，请检查网络连接.");
		return ;
	}

	vgKernel::StringVector mod;

	char buffer[256];

	m_sceneCombo.Clear();

	while (fgets(buffer, 256, fp) != NULL)
	{
		if (buffer[strlen(buffer)-1] == '\n')
			buffer[strlen(buffer)-1] = '\0';
		
		m_sceneCombo.AddString(buffer);
	}

	fclose(fp);

	m_sceneCombo.SetCurSel(0);

	UpdateData(FALSE);
}


void vgLogonDialog::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	
	CString scene;
	m_sceneCombo.GetWindowText(scene);
	
	string name = scene.GetString();

	if (name.length() == 0)
	{
		AfxMessageBox("未连接场景.请选择服务器.");
	}

	m_sceneVgPath = "";

	m_sceneVgPath = m_scenePath + "VRGIS_";
	m_sceneVgPath = m_sceneVgPath + name;
	m_sceneVgPath = m_sceneVgPath + "\\";
	m_sceneVgPath = m_sceneVgPath + name;
	m_sceneVgPath = m_sceneVgPath + ".vg";

	// AfxMessageBox(m_sceneVgPath.c_str());
	
	if (m_userName != "admin" || m_passWord != "vrgis")
	{
		AfxMessageBox("错误的用户名密码，请联系管理员.");
		return ;
	}


	string vgPath = getVgSceneFullPath();

	FILE *fp = fopen(vgPath.c_str(), "r");

	if (fp == NULL)
	{
		AfxMessageBox("服务器内部错误.请联系管理员");

		return ;
	}

	fclose(fp);
	
	m_bLoading = true;

	m_status = "状态 - 通信中";

	UpdateData(FALSE);

	vgGlobal::SceneFileUtility::setUpdateTime( 1 );

	vgGlobal::SceneFileUtility::openScene(vgPath);

	m_bLoading = false;

	OnOK();
}
