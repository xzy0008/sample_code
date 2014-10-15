// DBOpenningDlg.cpp : implementation file
//

#include <vgStableHeaders.h>
//#include <framework.h>

#include <vgDatabase/vgDlgDBConnect.h>

#include <vgDatabase/vgdDefinition.h>

#ifdef VGD_DLL
#include <vgDatabaseDLL/vgDatabaseResource.h>
#else
#include <vgLibraryResource.h>
#endif

#include "vgDatabase/vgdDatabaseManager.h"
#include "vgDatabase/vgdOracleConnector.h"
#include "vgDatabase/vgdBasedConnector.h"

using namespace vgDatabase;
//数据库

// #include <vgDB/AdoX.h>
// #include <vgDB/ado.h>


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DlgDBOpenning dialog


DBConnectDlg::DBConnectDlg(CWnd* pParent /*=NULL*/)
	: CDialog(DBConnectDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(DlgDBOpenning)
	m_cstrFilePath = _T("");
//	pView = (CFrameWorkView *)pParent ;
	//}}AFX_DATA_INIT
}


void DBConnectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
//	{{AFX_DATA_MAP(DlgDBOpenning)
//  	DDX_Text(pDX, IDC_EDIT2, m_cstrFilePath);
	DDX_Text(pDX, IDC_DB_COMBO, m_databaseName);
	DDX_Text(pDX, IDC_DB_DS, m_databaseSource);
	DDX_Text(pDX, IDC_DB_USER, m_userName);
	DDX_Text(pDX, IDC_DB_PWD, m_pwd);
	DDX_Check(pDX, IDC_DB_REMPWD, m_remPwd);
//	}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DBConnectDlg, CDialog)
	//{{AFX_MSG_MAP(DlgDBOpenning)
	//ON_BN_CLICKED(IDC_BTN_FILEPATH, OnBtnFilepath)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BTN_DATABASEFILE, &DBConnectDlg::OnBnClickedBtnDatabasefile)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DlgDBOpenning message handlers

void DBConnectDlg::OnBtnFilepath() 
{
	// TODO: Add your control notification handler code here
	
	CString DefExt,filepath;
	DefExt.Format("%s","mdb文件(*.mdb)|*.mdb|");	
	///CFileDialog第一个参数若为true，为打开文件对话框,该段基于mfc
	CFileDialog fileDlg(FALSE,"mdb",NULL,OFN_HIDEREADONLY|
		OFN_CREATEPROMPT|OFN_NONETWORKBUTTON,DefExt);	

	if(fileDlg.DoModal()==IDOK)
	{
		m_cstrFilePath = fileDlg.GetPathName();
	}
	
	UpdateData(FALSE);
}

void DBConnectDlg::OnOK() 
{
	// TODO: Add extra validation here
	//AfxMessageBox("HERE");
	UpdateData(TRUE);

// 	AfxMessageBox(m_databaseSource);
// 	AfxMessageBox(m_userName);
// 	AfxMessageBox(m_pwd);

	if (m_databaseName == "Oracle")
	{
		DatabaseManager::getSingleton().CreateConnector(vgDatabase::VG_DATABASE_ORACLE);

		BasedConnector *pConnector = DatabaseManager::getSingleton().GetConnectorPtr();

		pConnector->SetDataSource(m_databaseSource.GetString());
		pConnector->SetUserID(m_userName.GetString());
		pConnector->SetPassword(m_pwd.GetString());

		if (DatabaseManager::getSingleton().OpenDatabase())
		{
			AfxMessageBox("连接成功");
			
			if (m_remPwd)
			{
				// AfxMessageBox("记住密码");
				saveToConfigFile();
			}
			else
			{
				deleteConfigFile();
			}

			CDialog::OnOK();
		}
		else
		{
			AfxMessageBox("连接失败");

			return;
		}
	}
	else if (m_databaseName == "Access")
	{
		DatabaseManager::getSingleton().CreateConnector(vgDatabase::VG_DATABASE_ACCESS);

		BasedConnector *pConnector = DatabaseManager::getSingleton().GetConnectorPtr();

		pConnector->SetDataSource(m_databaseSource.GetString());
		pConnector->SetUserID(m_userName.GetString());
		pConnector->SetPassword(m_pwd.GetString());

		if (DatabaseManager::getSingleton().OpenDatabase())
		{
			AfxMessageBox("连接成功");

			if (m_remPwd)
			{
				// AfxMessageBox("记住密码");
				saveToConfigFile();
			}
			else
			{
				deleteConfigFile();
			}

			CDialog::OnOK();
		}
		else
		{
			AfxMessageBox("连接失败");

			return;
		}

		//DatabaseManager::getSingleton().GetConnectorPtr()->GetTablesName();
	}
	else
	{
		AfxMessageBox("不支持的数据库类型");
	}

	// CDialog::OnOK();
}

void DBConnectDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

int DBConnectDlg::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
// 	m_strFileName = _T("");
// 	UpdateData(FALSE);
	return 0;
}

BOOL DBConnectDlg::OnInitDialog()
{
	CComboBox* pCombo = (CComboBox*)GetDlgItem(IDC_DB_COMBO);
	assert(pCombo != NULL);
	pCombo->AddString("Oracle");
	pCombo->AddString("Access");

	m_remPwd = 0;

	char exebuf[512];
	DWORD getret = GetModuleFileName( NULL , exebuf , 512 );

	assert( getret < 512 );
	assert( getret > 0 );

	String exestr( exebuf );
	String exepath = exestr.substr( 0 , 
		exestr.find_last_of("\\/")  + 1);

	m_profilePath = exepath + "db.ora";
	FILE *fp = fopen(m_profilePath.c_str(), "r");

	char buffer[256];

	if (fp != NULL)
	{
		fgets(buffer, 256, fp);
		buffer[strlen(buffer)-1] = '\0';
		m_databaseName = buffer;
		pCombo->SelectString(-1, m_databaseName);
		
		fgets(buffer, 256, fp);
		buffer[strlen(buffer)-1] = '\0';
		m_databaseSource = buffer;

		fgets(buffer, 256, fp);
		buffer[strlen(buffer)-1] = '\0';
		m_userName = buffer;

		fgets(buffer, 256, fp);
		buffer[strlen(buffer)-1] = '\0';
		m_pwd = buffer;
		
		m_remPwd = 1;

		fclose(fp);
	}
	UpdateData(FALSE);

	return TRUE;
}

bool DBConnectDlg::saveToConfigFile()
{
	FILE *fp = fopen(m_profilePath.c_str(), "w");
	
	if (fp == NULL)
		return false;

	fputs(m_databaseName + "\n", fp);
	fputs(m_databaseSource + "\n", fp);
	fputs(m_userName + "\n", fp);
	fputs(m_pwd + "\n", fp);
	
	fclose(fp);

	return true;
}

bool DBConnectDlg::deleteConfigFile()
{
	DeleteFile(m_profilePath.c_str());

	return true;
}
void DBConnectDlg::OnBnClickedBtnDatabasefile()
{
	// TODO: 在此添加控件通知处理程序代码
	CString DefExt,filepath;
	DefExt.Format("%s","mdb文件(*.mdb)|*.mdb|");	
	///CFileDialog第一个参数若为true，为打开文件对话框,该段基于mfc
	CFileDialog fileDlg(FALSE,"mdb",NULL,OFN_HIDEREADONLY|
		OFN_CREATEPROMPT|OFN_NONETWORKBUTTON,DefExt);	

	if(fileDlg.DoModal()==IDOK)
	{
		m_databaseSource = fileDlg.GetPathName();
	}

	UpdateData(FALSE);
}
