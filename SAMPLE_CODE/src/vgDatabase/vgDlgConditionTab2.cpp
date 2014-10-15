// DBOpenningDlg.cpp : implementation file
//

#include <vgStableHeaders.h>

#include <Shlwapi.h>
//#include <framework.h>

/*#include <vgDatabase/vgDlgDBConnect.h>*/
#include <vgDatabase/vgDlgConditionTab2.h>
#include "vgDatabase/vgdDatabaseManager.h"
#include "vgDatabase/vgdOracleConnector.h"
#include "vgDatabase/vgdBasedConnector.h"

#include <vgDatabase/vgDlgCondition.h>
#include "vgDatabase/vgdDatabaseManager.h"
#include "vgDatabase/vgdOracleConnector.h"
#include "vgDatabase/vgdBasedConnector.h"
#include <vgDatabase/vgdProfileManager.h>
#include <vgDatabase/CUnrarDLL.h>

#include <vgKernel/vgkRendererManager.h>
#include <vgKernel/vgkColorableObject.h>

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


DBConditionTab2::DBConditionTab2(CWnd* pParent /*=NULL*/)
	: CDialog(DBConditionTab2::IDD, pParent)
{
	//AfxMessageBox("构造 DBConditionTab2");
	m_pParent = pParent;
}

DBConditionTab2::~DBConditionTab2()
{
	//AfxMessageBox("销毁 DBConditionTab2");
}

void DBConditionTab2::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
//	{{AFX_DATA_MAP(DBConditionTab2)
	DDX_Control(pDX, IDC_COLOR_PICKER, m_ColorPicker);
	DDX_Control(pDX, IDC_SPIN_ALPHA, m_spinAlpha);
	DDX_Text(pDX, IDC_EDIT_ALPHA, m_editAlpha);
//	}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DBConditionTab2, CDialog)
	//{{AFX_MSG_MAP(DlgDBOpenning)
	//ON_BN_CLICKED(IDC_BTN_FILEPATH, OnBtnFilepath)
	ON_WM_CREATE()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON11, &DBConditionTab2::OnBnClickedButton11)
	ON_BN_CLICKED(IDC_DBTAB2_BACK, &DBConditionTab2::OnBnClickedDbtab2Back)
	ON_BN_CLICKED(IDC_PRINT, &DBConditionTab2::OnBnClickedPrint)
	ON_BN_CLICKED(IDC_BUTTON1, &DBConditionTab2::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_COLOR_PICKER, &DBConditionTab2::OnColorPicker)
	ON_BN_CLICKED(IDC_BUTTON_HILIGHT, &DBConditionTab2::OnHilightDisplay)
	ON_BN_CLICKED(IDC_SPIN_ALPHA, &DBConditionTab2::OnSpinAlpha)

END_MESSAGE_MAP()


void DBConditionTab2::OnOK() 
{
	// TODO: Add extra validation here
	//AfxMessageBox("HERE");
	//UpdateData(TRUE);

	return ;

	CDialog::OnOK();
}

void DBConditionTab2::OnCancel() 
{
	// TODO: Add extra cleanup here
	return ;

	CDialog::OnCancel();
}

int DBConditionTab2::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	CRect rectGrid;

	ScreenToClient (&rectGrid);

	m_resultGrid.Create (WS_CHILD | WS_VISIBLE | WS_BORDER, rectGrid, this, 1);

	AdjustLayout();

	return 0;
}

BOOL DBConditionTab2::OnInitDialog()
{

	UpdateData(FALSE);

	//-------------
	// Set color:
	//-------------
	BCGP_GRID_COLOR_DATA Initheme;

	Initheme = m_resultGrid.GetColorTheme();
	theme.m_HeaderColors = Initheme.m_HeaderColors;
	theme.m_HeaderSelColors = Initheme.m_HeaderSelColors;

	m_resultGrid.SetColorTheme (theme);
	
	//-------------
	// Global set:
	//-------------
	//m_resultGrid.SetWholeRowSel(TRUE);
	//m_resultGrid.EnableMarkSortedColumn (FALSE);
	m_resultGrid.EnableHeader (TRUE, BCGP_GRID_HEADER_SORT);
	m_resultGrid.SetDbSort();

	// Create color picker:
	m_ColorPicker.EnableAutomaticButton (_T("Automatic"), RGB (255, 255, 0));
	m_ColorPicker.EnableOtherButton (_T("Other"));
	m_ColorPicker.SetColor (m_ColorPicker.GetAutomaticColor());
	m_ColorPicker.SetColumnsNumber (10);

	m_curColor = m_ColorPicker.GetColor();

	m_spinAlpha.SetRange(0, 255);
	m_spinAlpha.SetPos(255);
	m_spinAlpha.SetBuddy(GetDlgItem(IDC_EDIT_ALPHA));
	m_editAlpha = m_spinAlpha.GetPos();

	UpdateData(FALSE);

	return TRUE;
}

void DBConditionTab2::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	AdjustLayout();
}

void DBConditionTab2::OnBnClickedButton11()
{
	// TODO: 在此添加控件通知处理程序代码
	DBCondition *pDialog = (DBCondition*)m_pParent;

	if (pDialog)
	{
		pDialog->Quit();
	}
}

void DBConditionTab2::OnBnClickedDbtab2Back()
{
	// TODO: 在此添加控件通知处理程序代码
	DBCondition *pParent = (DBCondition*)m_pParent;
	if (pParent != NULL)
	{
		pParent->SetActiveTab(0);
	}
}

void DBConditionTab2::AdjustLayout()
{
	if (GetSafeHwnd () == NULL)
	{
		return;
	}

	CRect rectClient;
	GetClientRect (rectClient);

	m_resultGrid.SetWindowPos(NULL, rectClient.left + 20, rectClient.top +30, rectClient.Width() - 42, rectClient.Height()- 80, SWP_NOACTIVATE | SWP_NOZORDER);

}

bool DBConditionTab2::InitResultGrid(String connectString, String id, String pwd, CString sqlString)
{	 
	if (!m_resultGrid.OpenDB (connectString.c_str(), id.c_str(), pwd.c_str()))
	{
		AfxMessageBox("opendb 失败");
	}
	
	if (!m_resultGrid.OpenSQL(sqlString))
	{
		m_resultGrid.Close();

		return false;
	}

	for (int i=0; i<m_resultGrid.GetColumnCount(); i++)
	{
 		String str = m_resultGrid.GetColumnName(i).GetString();
 		m_resultGrid.SetColumnWidth(i, str.length() * 8 + 40);
	}

	m_resultGrid.Invalidate(false);
	m_resultGrid.AdjustLayout();

	return true;
}
void DBConditionTab2::OnBnClickedPrint()
{
	// TODO: 在此添加控件通知处理程序代码
	m_resultGrid.Print();
}

void DBConditionTab2::OnColorPicker() 
{
	m_curColor = m_ColorPicker.GetColor();

	UpdateData (FALSE);
}

void DBConditionTab2::OnHilightDisplay()
{
	UpdateData(TRUE);

	CString primaryid;
	String  str;
	CString Cstr;

	vgDatabase::QueryProfile pQueryProfile = vgDatabase::ProfileManager::getSingleton().GetCurProfile();

	primaryid = pQueryProfile.GetShowNameFromQueryName(pQueryProfile.GetPrimaryId());

	for (int nIndex =0;nIndex < m_resultGrid.GetRowCount();nIndex++)
	{
		CBCGPGridRow* pRow = m_resultGrid.GetRow(nIndex);

		for (int i = 0; i < m_resultGrid.GetColumnCount();i++)
		{
			if (m_resultGrid.GetColumnName(i) == primaryid)
			{
				Cstr = pRow->GetItem(i)->GetValue();
				str = Cstr.GetString();
				break;
			}
		}	

		vgKernel::Renderer* pRenderer = vgKernel::RendererManager::getSingleton().getRendererbyName(str);

		vgKernel::ColorableObject* pColorObj = dynamic_cast<vgKernel::ColorableObject*>(pRenderer);

		if (pColorObj != NULL)
		{
			pColorObj->setColorableValue( vgKernel::RgbaQuad(
				GetRValue(m_curColor), 
				GetGValue(m_curColor),
				GetBValue(m_curColor), 
				m_editAlpha) );

			pRenderer->notifyOberversOnEvent(vgKernel::VG_OBS_PROPCHANGED, NULL);
		}



	}

	return;
}

void DBConditionTab2::OnSpinAlpha()
{
	m_editAlpha = m_spinAlpha.GetPos();
	UpdateData(FALSE);
}

void DBConditionTab2::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码

	//---------------------------------------------------------
	//1.判断当前文件夹是否有下载文件夹并删除
	//---------------------------------------------------------
	DBCondition *pParent = (DBCondition*)m_pParent;

	CString deleteDir = pParent->GetResultTab()->OutputDir;

	if(PathFileExists(deleteDir/*OutputDir.c_str()*/))     
	{	
		DeleteDirectory((LPSTR)(LPCTSTR)deleteDir);
	}

	//---------------------------------------------------------
	//2.得到当前执行文件路径
	//---------------------------------------------------------
	char exebuf[512];

	DWORD getret = GetModuleFileName( NULL , exebuf , 512 );

	assert( getret < 512 );

	assert( getret > 0 );

	String exestr( exebuf );

	String exepathtemp = exestr.substr( 0 , exestr.find_last_of("\\/")  + 1);

	CString exepath = exepathtemp.c_str();

	OutputDir = exepath + "HTML_TEMP";

	//---------------------------------------------------------
	//3.判断列表中所选中的行，为后面定位做准备
	//---------------------------------------------------------
	CString primaryid;

	String  str;

	int curIndex;

	CString Cstr;

	int nselectNumber = 0;

	BOOL tab = FALSE;

	vgDatabase::QueryProfile pQueryProfile = vgDatabase::ProfileManager::getSingleton().GetCurProfile();

	primaryid = pQueryProfile.GetShowNameFromQueryName(pQueryProfile.GetPrimaryId());

	str = "'";//  [12/16/2008 yuxin]

	for (int nIndex =0;nIndex < m_resultGrid.GetRowCount();nIndex++)
	{
		if (m_resultGrid.IsRowSelected(nIndex))
		{
			tab = TRUE;

			curIndex = nIndex;

			// 			CBCGPGridRow* pRow; 
			// 			
			// 			pRow = m_resultGrid.GetRow(nIndex);

			// 			for (int i = 0; i < m_resultGrid.GetColumnCount();i++)
			// 			{
			// 				if (m_resultGrid.GetColumnName(i) == primaryid)
			// 				{
			// 					Cstr = pRow->GetItem(i)->GetValue();
			// 					
			// 					str += Cstr.GetString();
			// 					
			// 					str += "'";
			// 				}
			// 			}			
			break;
		}
	}

	if (!tab)
	{
		AfxMessageBox("未选择查询对象!");

		return;
	}

	//--------------------------------------------------------------------
	//4.查询所有行和列
	//---------------------------------------------------------------------
	if (! vgDatabase::DatabaseManager::getSingleton().IsOpen())
	{
		AfxMessageBox("数据库未打开");

		return ;
	}

	vgDatabase::QueryProfile curProfile = vgDatabase::ProfileManager::getSingleton().GetCurProfile();

	String profilename = curProfile.GetName();

	String strSQL = vgDatabase::ProfileManager::getSingleton().CreateQueryWithWhere(profilename,false);

	if (curProfile.m_connectList.size() == 0)
	{
		int pos = strSQL.find("where");

		String tmpString = strSQL.substr(0, pos);

		strSQL = tmpString.c_str();
	}

	// 	strSQL += str;//  [12/16/2008 yuxin]

	CADODatabase& pDb = vgDatabase::DatabaseManager::getSingleton().GetConnectorPtr()->GetDatabase();

	CADORecordset* m_pRecordset = new CADORecordset(&pDb);

	if (!m_pRecordset->Open(strSQL.c_str(), CADORecordset::openUnknown))
	{
		return;
	}

	//--------------------------------------------------------------------	
	//5.定位所选行
	//--------------------------------------------------------------------
	//m_pRecordset->Find(str.c_str());

	for (int i = 0; i < curIndex; i++)
	{
		m_pRecordset->MoveNext();
	}
	//--------------------------------------------------------------------
	//6.判断所选列是否包含二进制文件，并下载到内存
	//--------------------------------------------------------------------
	BOOL tab2 = FALSE;

	CADOFieldInfo fieldinfo ;

	String fieldName;

	String fieldValue;

	int feildcount = m_pRecordset->GetFieldCount();

	for (int i = 0; i < feildcount; i++)
	{
		m_pRecordset->GetFieldInfo(i,&fieldinfo);

		if ((fieldinfo.m_nType == CADORecordset::typeBinary) |( fieldinfo.m_nType == CADORecordset::typeVarBinary) |(fieldinfo.m_nType == CADORecordset::typeLongVarBinary) )
		{
			tab2 = TRUE;

			fieldName = fieldinfo.m_strName;

			break;
		}
	}

	long lDataSize = fieldinfo.m_lSize;

	char* data = new char[lDataSize];

	if (!tab2)
	{
		AfxMessageBox("没有可以显示的HTML页面！");

		return;
	}

	if (!m_pRecordset->GetChunk(fieldName.c_str(),(LPVOID)data))
	{
		AfxMessageBox("无法下载目标文件");

		return;
	}

	//----------------------------------------------------------------------
	//7.查找当前执行文件夹是否有下载文件夹，没有则创建
	//----------------------------------------------------------------------
	CFileFind ff;

	if (!ff.FindFile(OutputDir + "\\*.*"))
	{
		CreateDirectory(OutputDir + "\\",NULL);
	}

	ff.Close();
	//----------------------------------------------------------------------
	//8.下载二进制文件到本地文件夹
	//----------------------------------------------------------------------
	CFile targetFile;

	CFileException eTargetFile;

	CString targetFileName = OutputDir + "\\html.rar";

	if (!targetFile.Open(targetFileName, CFile::modeCreate | CFile::modeWrite, &eTargetFile))
	{
		AfxMessageBox("file open failed");

		return;
	}
	else
	{
		// 打开文件成功，准备写入
		targetFile.Write((BYTE *)data, lDataSize);

		targetFile.Close();
	}

	//----------------------------------------------------------------------------
	//9.解压文件
	//---------------------------------------------------------------------------
	CUnrarDLL unrarObj;

	unrarObj.LoadDLL();

	if (!unrarObj.OpenRARFile(targetFileName))
	{
		AfxMessageBox("open failed");
	}
	else
	{
		unrarObj.SetOutputDirectory(OutputDir);

		unrarObj.UnRARArchive();
	}

	//---------------------------------------------------------------------
	//10.遍历下载文件夹，查找.htm或.html文件
	//---------------------------------------------------------------------
	CFileFind ffind;   

	CString url;

	CString  szDir = OutputDir;   

	CString strFileName,   strSuffix,   strFilePath;   

	int index;

	szDir += "\\*.*";         

	BOOL res = ffind.FindFile(szDir); 

	while( res )   
	{   
		res =  (BOOL)ffind.FindNextFile();   

		if(!ffind.IsDirectory() && !ffind.IsDots())   
		{     
			strFileName   =   ffind.GetFileName();

			index   =   strFileName.ReverseFind('.');           

			strSuffix   =   strFileName.Mid(index+1);  

			if   ( strSuffix == "html" ||strSuffix == "htm")     
			{   
				url = ffind.GetFilePath();           
			}   
		}   
	}

	ffind.Close();//关闭 

	//--------------------------------------------------------------------
	//11.显示查询结果，跳转到显示页面
	//--------------------------------------------------------------------
	pParent->GetHtmlTab()->m_htmlControl.Navigate(url, NULL, NULL, NULL, NULL);

	if (pParent != NULL)
	{
		pParent->SetActiveTab(2);
	}	

	//---------------------------------------------------------------------
	//12.关闭记录集
	//---------------------------------------------------------------------
	m_pRecordset->Close();

	delete data;

	delete m_pRecordset;
}

bool DBConditionTab2::DeleteDirectory(const char* DirName )
{
	CFileFind   tempFind;   
	char   tempFileFind[MAX_PATH];   
	sprintf(tempFileFind,"%s\\*.*",DirName);   
	BOOL   IsFinded=(BOOL)tempFind.FindFile(tempFileFind);   

	while(IsFinded)   
	{   
		IsFinded=(BOOL)tempFind.FindNextFile();   
		if(!tempFind.IsDots())   
		{   
			char   foundFileName[MAX_PATH];   
			strcpy(foundFileName,tempFind.GetFileName().GetBuffer(MAX_PATH));   
			if(tempFind.IsDirectory())   
			{   
				char   tempDir[MAX_PATH];   
				sprintf(tempDir,"%s\\%s",DirName,foundFileName);   
				DeleteDirectory(tempDir);   
			}   
			else   
			{   
				char   tempFileName[MAX_PATH];   
				sprintf(tempFileName,"%s\\%s",DirName,foundFileName);   
				DeleteFile(tempFileName);   
			}   
		}   
	}   

	tempFind.Close(); 

	if(!RemoveDirectory(DirName))   
	{   
		//AfxMessageBox("删除目录失败！");//比如没有找到文件夹,删除失败，可把此句删除   
		return   FALSE;   
	}   
	return   TRUE;   

}