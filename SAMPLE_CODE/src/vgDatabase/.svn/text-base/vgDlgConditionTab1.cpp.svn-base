// DBOpenningDlg.cpp : implementation file
//

#include <vgStableHeaders.h>
//#include <framework.h>

/*#include <vgDatabase/vgDlgDBConnect.h>*/
#include <vgDatabase/vgDlgConditionTab1.h>
#include <vgDatabase/vgDlgCondition.h>
#include <vgDatabase/vgDlgConditionTab2.h>

#include "vgDatabase/vgdDatabaseManager.h"
#include "vgDatabase/vgdOracleConnector.h"
#include "vgDatabase/vgdBasedConnector.h"

#include <vgDatabase/vgdProfileManager.h>

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
static BCGP_GRID_COLOR_DATA theme = 
{
	-1,	// Grid background color
	//RGB (246, 250, 253),
	-1,	// Grid foreground color
	-1,	// Header foreground color

	{	// Even rows colors:
		RGB (246, 250, 253), -1, -1, 0, -1
	},

	{	// Odd rows colors:
		-1, -1, -1, 0, -1
	},

	{	// Group colors:
		RGB (210, 230, 249), RGB (16, 37, 127), RGB (228, 241, 251), 90, -1
	},

	{	// Selected group colors:
		RGB (250, 199, 97), RGB (0, 0, 0), -1, 0, RGB (192, 192, 192)
	},

	{	// Selected rows colors:
		RGB (255, 229, 153), -1, -1, 0, RGB (192, 192, 192)
	},

 	{	// Header item colors:
 		RGB (154, 194, 237), RGB (16, 37, 127), RGB (189, 214, 242), 90, RGB (136, 176, 228)
 	},
 
 	{	// Selected header item colors:
 		-1, -1, -1, 0, -1
 	},

	{	// Left offset colors:
		RGB (207, 221, 240), -1, RGB (227, 234, 244), 90, RGB (136, 176, 228)
	},

	-1,	// Grid horizontal line text
	-1,	// Grid vertical line text
	-1,	// Description text color
};

DBConditionTab1::DBConditionTab1(CWnd* pParent /*=NULL*/)
	: CDialog(DBConditionTab1::IDD, pParent)
{
	m_pParent = pParent;

	QueryConditionView.SetWholeRowSel(true);
}

DBConditionTab1::~DBConditionTab1()
{
	//AfxMessageBox("销毁 DBConditionTab 1");
//	delete m_propertySheet;
}

void DBConditionTab1::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
//	{{AFX_DATA_MAP(DlgDBOpenning)
	DDX_Control(pDX, IDC_COMBO2, Profile_Name);
	DDX_Control(pDX, IDC_COMBO1, Feild_Name);
	DDX_Control(pDX, IDC_COMBO4, LogicalSymbol);
	DDX_Control(pDX, IDC_COMBO3, QueryCondition);
	DDX_Control(pDX, IDC_EDIT1, QueryConditionEdit);
//	}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DBConditionTab1, CDialog)
	//{{AFX_MSG_MAP(DlgDBOpenning)
	//ON_BN_CLICKED(IDC_BTN_FILEPATH, OnBtnFilepath)
	ON_BN_CLICKED(IDC_DC_COMMIT, OnCommitButtonClick)
	ON_WM_CREATE()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_DBC_ADDCON, &DBConditionTab1::OnBnClickedDbcAddcon)
	ON_CBN_SELCHANGE(IDC_COMBO2, &DBConditionTab1::OnCbnSelchangeCombo2)
END_MESSAGE_MAP()


void DBConditionTab1::OnOK() 
{
	// TODO: Add extra validation here
	//AfxMessageBox("HERE");
	UpdateData(TRUE);
	
	return ;

	CDialog::OnOK();
}

void DBConditionTab1::OnCancel() 
{
	// TODO: Add extra cleanup here
	return ;

	CDialog::OnCancel();
}

int DBConditionTab1::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	CRect rectGrid;

	ScreenToClient (&rectGrid);

	QueryConditionView.Create (WS_CHILD | WS_VISIBLE | WS_BORDER, rectGrid, this, 1);

	AdjustLayout();

	return 0;
}

BOOL DBConditionTab1::OnInitDialog()
{

	UpdateData(FALSE);

	//---------------------
	// Set profile combobox:
	//---------------------
	std::vector<vgDatabase::QueryProfile>::iterator iter = vgDatabase::ProfileManager::getSingleton().GetProfiles().begin();	

	ProfileManager::getSingleton().SetCurProfile(iter->GetName().c_str());

	for (;iter != vgDatabase::ProfileManager::getSingleton().GetProfiles().end();iter++)
	{
		CString name = iter->GetName().c_str();
		Profile_Name.AddString(name);
	}
	Profile_Name.SetCurSel(0);

	//---------------------
	// Set query_condition combobox:
	//---------------------
	QueryCondition.AddString(_T(">"));
	QueryCondition.AddString(_T(">="));
	QueryCondition.AddString(_T("<"));
	QueryCondition.AddString(_T("<="));
	QueryCondition.AddString(_T("="));
	QueryCondition.AddString(_T("<>"));
	QueryCondition.AddString(_T("> DATE"));
	QueryCondition.AddString(_T("< DATE"));
	QueryCondition.AddString(_T("= DATE"));
	QueryCondition.AddString(_T("like"));
	QueryCondition.SetCurSel(0);

	//---------------------
	// Set feild_name combobox:
	//---------------------
	std::vector<String> stringvec 
		= ProfileManager::getSingleton().GetProfiles().front().m_shownNameList;	
	for (int i =0;i<stringvec.size();i++)
	{
		CString feildlist = stringvec.at(i).c_str();
		Feild_Name.AddString(feildlist);
	}
	Feild_Name.SetCurSel(0);

	//---------------------
	// Set logic_symbol combobox:
	//---------------------
	LogicalSymbol.AddString(_T("And"));
	LogicalSymbol.AddString(_T("Or"));

	LogicalSymbol.SetCurSel(0);


	//-------------
	// Global set:
	//-------------
	QueryConditionView.EnableMarkSortedColumn (FALSE);
	QueryConditionView.EnableHeader (TRUE, BCGP_GRID_HEADER_MOVE_ITEMS);
	QueryConditionView.SetWholeRowSel(TRUE);

	//-------------
	// Add columns:
	//-------------
	QueryConditionView.InsertColumn (0, _T("逻辑关系"), 60);
	QueryConditionView.InsertColumn (1, _T("字段名"), 80);
	QueryConditionView.InsertColumn (2, _T("查询约束"), 80);
	QueryConditionView.InsertColumn (3, _T("查询条件"), 100);

	QueryConditionView.SetWholeRowSel(TRUE);

	//-------------
	// Set color:
	//-------------
	BCGP_GRID_COLOR_DATA Initheme;

	Initheme = QueryConditionView.GetColorTheme();
	theme.m_HeaderColors = Initheme.m_HeaderColors;
	theme.m_HeaderSelColors = Initheme.m_HeaderSelColors;

	QueryConditionView.SetColorTheme (theme);
	QueryConditionView.EnableColumnAutoSize(true);

	return TRUE;
}

void DBConditionTab1::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);
	AdjustLayout();
}

void DBConditionTab1::OnCommitButtonClick()
{
	DBCondition *pParent = (DBCondition*)m_pParent;
 	if (pParent != NULL)
 	{
		pParent->SetActiveTab(1);
	}

	CString profileName;

	Profile_Name.GetLBText(Profile_Name.GetCurSel(), profileName);
	String sqlString = vgDatabase::ProfileManager::getSingleton().CreateQuery(profileName.GetString(), false);
	
	QueryProfile *pProfile = vgDatabase::ProfileManager::getSingleton().GetProfile(profileName.GetString());

	CString SQLString;// = sqlString.c_str();
	
	// 空条件列表 需要处理where
	if (QueryConditionView.GetRowCount() == 0)
	{
		if (pProfile->m_connectList.size() == 0)
		{
			int pos = sqlString.find("where");
			String tmpString = sqlString.substr(0, pos);

			SQLString = tmpString.c_str();
		}
		else
		{
			SQLString = sqlString.c_str();
		}
		//AfxMessageBox(SQLString);

	}
	else
	{
		// 非空条件列表 正常处理
		SQLString = sqlString.c_str();
		// AfxMessageBox(SQLString);

		// 处理第0行

		if (pProfile->m_connectList.size() > 0)
		{
			SQLString += " AND ";
		}

		CBCGPGridRow* pRow = QueryConditionView.GetRow(0);

		for (int i = 1; i < QueryConditionView.GetColumnCount();i++)
		{
			// AfxMessageBox(pRow->GetItem(i)->GetLabel() );
			if (QueryConditionView.GetColumnName(i) == "查询条件")
			{

// 				SQLString += "'";
				SQLString += pRow->GetItem(i)->GetValue();
// 				SQLString += "'";
			}
			else if (QueryConditionView.GetColumnName(i) == "字段名")
			{
				SQLString += pProfile->GetQueryNameFromShowName(pRow->GetItem(i)->GetValue());//YX
			}
			else
			{
				SQLString += pRow->GetItem(i)->GetValue();
			}
			//SQLString += pProfile->GetRecordName(pRow->GetItem(i)->GetValue());
			SQLString += _T(" ");
		}	

		// 从第一行继续往下处理
		for (int nIndex =1; nIndex < QueryConditionView.GetRowCount();nIndex++)
		{
			// if (QueryConditionView.IsRowSelected(nIndex))
			{
				CBCGPGridRow* pRow; 
				pRow = QueryConditionView.GetRow(nIndex);
				for (int i = 0;i < QueryConditionView.GetColumnCount();i++)
				{
					if (QueryConditionView.GetColumnName(i) == "查询条件")
					{
// 						SQLString += "'";
						SQLString += pRow->GetItem(i)->GetValue();
// 						SQLString += "'";
					}
					else if (QueryConditionView.GetColumnName(i) == "字段名")
					{
						SQLString += pProfile->GetQueryNameFromShowName(pRow->GetItem(i)->GetValue());//YX
					}
					else
					{
						SQLString += pRow->GetItem(i)->GetValue();
					}
					SQLString += _T(" ");
				}					
			}
		}
	}

	   
	// AfxMessageBox(SQLString);
	//VGK_SHOW(SQLString.GetString());
	String connectStr = vgDatabase::DatabaseManager::getSingleton().GetConnectorPtr()->GetGridConnectString();
	String userID = vgDatabase::DatabaseManager::getSingleton().GetConnectorPtr()->GetUserID();
	String pwd = vgDatabase::DatabaseManager::getSingleton().GetConnectorPtr()->GetPassword();

	if (! pParent->GetResultTab()->InitResultGrid(connectStr, userID, pwd, SQLString))
	{
		AfxMessageBox("初始化Grid失败");
	}
}

void DBConditionTab1::AdjustLayout()
{
	if (GetSafeHwnd () == NULL)
	{
		return;
	}

	CRect rectClient;
	GetClientRect (rectClient);

	QueryConditionView.SetWindowPos(NULL, rectClient.left + 20, rectClient.top +30, rectClient.Width() - 42, rectClient.Height()- 140, SWP_NOACTIVATE | SWP_NOZORDER);

}

void DBConditionTab1::OnBnClickedDbcAddcon()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	
	CString str;
	QueryConditionEdit.GetWindowText(str);   

	if (str == "")
	{
		AfxMessageBox("输入中存在空值");

		return ;
	}

	CBCGPGridRow* pRow = QueryConditionView.CreateRow (QueryConditionView.GetColumnCount ());
	
	int nIndex;

	if (QueryConditionView.GetRowCount() != 0)
	{
		nIndex = LogicalSymbol.GetCurSel();
		LogicalSymbol.GetLBText(nIndex,str);
		pRow->GetItem (0)->SetValue ((_variant_t)str);
		pRow->GetItem (0)->AllowEdit (FALSE);
	}
	else
	{
		pRow->GetItem (0)->SetValue ((_variant_t)("#"));
		pRow->GetItem (0)->AllowEdit (FALSE);
	}

	nIndex = Feild_Name.GetCurSel();
	Feild_Name.GetLBText(nIndex,str);
	pRow->GetItem(1)->SetValue((_variant_t)str);
	pRow->GetItem (1)->AllowEdit (FALSE);

	nIndex = QueryCondition.GetCurSel();
	QueryCondition.GetLBText(nIndex,str);
	pRow->GetItem (2)->SetValue ((_variant_t)str);
	pRow->GetItem (2)->AllowEdit (FALSE);

	QueryConditionEdit.GetWindowText(str);
	pRow->GetItem (3)->SetValue ((_variant_t)str);

	QueryConditionView.AddRow (pRow, true);

	QueryConditionEdit.SetWindowText("");
}

void DBConditionTab1::OnCbnSelchangeCombo2()
{
	// TODO: 在此添加控件通知处理程序代码
	int nIndex = Profile_Name.GetCurSel();
	//================================================================YXDBNAME
	CString curprofilename;//ProfileManager::getSingleton.GetProfile(nIndex).GetName().c_str();
	Profile_Name.GetLBText(nIndex,curprofilename);

	ProfileManager::getSingleton().SetCurProfile(curprofilename);
	//==============================================================================

	std::vector<String> stringvec ;
	stringvec.clear();
	stringvec = ProfileManager::getSingleton().GetProfiles().at(nIndex).m_shownNameList;

	Feild_Name.ResetContent();
	for (int i =0;i<stringvec.size();i++)
	{
		CString feildlist = stringvec.at(i).c_str();
		Feild_Name.AddString(feildlist);
	}
	Feild_Name.SetCurSel(0);

	QueryConditionView.RemoveAll();
	QueryConditionView.Invalidate(true);
}
