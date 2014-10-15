
#include <vgStableHeaders.h>
#include <vgGIS3D\vggiDlgOracleConfig.h>

namespace vgGIS3D
{
	// vgDlgOracleConfig 对话框

	IMPLEMENT_DYNAMIC(vgDlgOracleConfig, CDialog)

		vgDlgOracleConfig::vgDlgOracleConfig(CWnd* pParent /*=NULL*/)
		: CDialog(vgDlgOracleConfig::IDD, pParent)
	{

	}

	vgDlgOracleConfig::~vgDlgOracleConfig()
	{
	}

	void vgDlgOracleConfig::DoDataExchange(CDataExchange* pDX)
	{
		CDialog::DoDataExchange(pDX);
		DDX_Check(pDX, IDC_CHECK_AUTOLOG, m_remeberInfo);
 		DDX_Text(pDX, IDC_ORA_USER, m_oraUser);
 		DDX_Text(pDX, IDC_ORA_PWD, m_oraPwd);
		DDX_Text(pDX, IDC_ORA_SERVICE, m_oraServ);
 		DDX_Text(pDX, IDC_ORA_SQL, m_sql);
	} 


	BEGIN_MESSAGE_MAP(vgDlgOracleConfig, CDialog)
	END_MESSAGE_MAP()

	
	// vgDlgOracleConfig 消息处理程序
}

void vgGIS3D::vgDlgOracleConfig::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	UpdateData(TRUE);

	CDialog::OnOK();
}

BOOL vgGIS3D::vgDlgOracleConfig::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	

	if (! m_remeberInfo)
	{
		m_oraUser.SetString("");
		m_oraServ.SetString("");
		m_oraPwd.SetString("");
	
		m_sql.SetString("");
	}

	m_oraUser.SetString("vgdb");
	m_oraServ.SetString("vrgis");
	m_oraPwd.SetString("vrgis");
	m_sql.SetString("select * from guanxian");
	
	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
