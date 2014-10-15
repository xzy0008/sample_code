// vgPipeAttriDlg.cpp : 实现文件
//

#include <vgStableHeaders.h>
#include <vgGIS3D\vgPipeLayerAttriDlg.h>

#include <vgGis/vgGisManager.h>
#include <vgGIS3D/vggiDataSource.h>
#include <vgGis3d/vggiGeometry.h>
#include <vgGIS3D/vggiPrerequisite.h>
#include <vgGis3d/vggiLine.h>
#include <vgGIS3D/vgAddAttriSectionDlg.h>

#include <vgKernel/vgkStringUtility.h>
#include <vgKernel/vgkSystemUtility.h>
#include <vgCam/vgcaCamFacade.h>


// vgPipeAttriDlg 对话框
namespace vgGIS3D
{
	IMPLEMENT_DYNAMIC(vgPipeLayerAttriDlg, CDialog)

		std::vector<CString> vgPipeLayerAttriDlg::m_fieldNameVec;


		vgPipeLayerAttriDlg::vgPipeLayerAttriDlg(CWnd* pParent /*=NULL*/)
		: CDialog(vgPipeLayerAttriDlg::IDD, pParent)
	{
		//m_ogrPipeLineMap = NULL;
		m_ogrPipeLineMap = vgGIS3D::GisManager::getSingleton().getPipeLineMap();
		m_pRecordsetLand = NULL;	
		m_menu.LoadMenu(IDR_PIPELAYER_ATTRI);
	}

	vgPipeLayerAttriDlg::~vgPipeLayerAttriDlg()
	{		
		if (m_pRecordsetLand !=  NULL)
		{
			delete m_pRecordsetLand;
			m_pRecordsetLand = NULL;
		}

		m_menu.DestroyMenu();
	}

	void vgPipeLayerAttriDlg::DoDataExchange(CDataExchange* pDX)
	{
		CDialog::DoDataExchange(pDX);
		DDX_Control(pDX, IDC_ATTRI_SECTIONS, m_wndGridLocation);
	}


	BEGIN_MESSAGE_MAP(vgPipeLayerAttriDlg, CDialog)
		ON_WM_CREATE()	
		ON_WM_TIMER()
		ON_WM_DESTROY()			
		ON_BN_CLICKED(IDC_ADD_SECTION, &vgPipeLayerAttriDlg::OnAppendOption)
		ON_COMMAND(ID_ADD_SECTION, &vgPipeLayerAttriDlg::OnAddAttriSection)
		ON_COMMAND(ID_PIPEATTRI_PRINT, &vgPipeLayerAttriDlg::OnPrintPipeAttri)
		ON_COMMAND(ID_PIPRATTRI_EXPORT, &vgPipeLayerAttriDlg::OnExportPipeAttri)
	END_MESSAGE_MAP()


	// vgPipeAttriDlg 消息处理程序

	int vgPipeLayerAttriDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
	{
		if (CDialog::OnCreate(lpCreateStruct) == -1)
		{
			AfxMessageBox("Error.");
			return -1;
		}

		return 0;
	}

	BOOL vgPipeLayerAttriDlg::OnInitDialog()
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

		getValueFromDatabase();

		UpdateData(FALSE);

		m_wndGrid.SetWholeRowSel(TRUE);

		sLastRow = NULL;
		SetTimer(1, 100, NULL);

		return TRUE;  // return TRUE unless you set the focus to a control
		// 异常: OCX 属性页应返回 FALSE
	}

	void vgPipeLayerAttriDlg::getValueFromDatabase()
	{
		CADODatabase* pAdoDatabase = vgDatabase::DatabaseManager::getSingleton().GetConnectorPtr()->GetCurDatabase();
		vgDatabase::BasedConnector* connectorptr = vgDatabase::DatabaseManager::getSingleton().GetConnectorPtr();
		std::vector<String>  tablelist = connectorptr->GetTablesName();

		Layer *shapLayer = m_ogrPipeLineMap->getShapeLayer();
		m_tableName = shapLayer->getName();

		for (int i = 0; i < tablelist.size(); i++)
		{
			if (m_tableName == tablelist[i])
			{
				String strSQLcommand = "SELECT * FROM ";
				strSQLcommand+=m_tableName;

				CADODatabase& pDb_Land = vgDatabase::DatabaseManager::getSingleton().GetConnectorPtr()->GetDatabase();

				if ( m_pRecordsetLand != NULL )
				{
					m_pRecordsetLand->Close();
					delete m_pRecordsetLand;
					m_pRecordsetLand = NULL;
				}
				m_pRecordsetLand = new CADORecordset(&pDb_Land);
				//m_pRecordsetLand = connectorptr->Execute(strSQLcommand);

				if (!m_pRecordsetLand->Open(strSQLcommand.c_str(), CADORecordset::openUnknown))
				{
					return;
				}
				
				CADOFieldInfo fInfo;
				for (int i = 0; i < m_pRecordsetLand->GetFieldCount(); i++)
				{
					m_pRecordsetLand->GetFieldInfo(i , &fInfo);
					CString fieldName(fInfo.m_strName);
					vgPipeLayerAttriDlg::m_fieldNameVec.push_back(fieldName);
					m_wndGrid.InsertColumn(i, fieldName, 80);
				}
				//m_wndGrid.InsertColumn(m_pRecordsetLand->GetFieldCount(), _T(""), 80);

				std::vector<CString> rowValueVec;

				if (m_pRecordsetLand->GetRecordCount() < 1)
				{
					return;
				}
				
				m_pRecordsetLand->MoveFirst();
				for ( int i = 0; i < m_pRecordsetLand->GetRecordCount(); i++ )
				{
					if (!rowValueVec.empty())
					{
						rowValueVec.clear();
					}

					CBCGPGridRow *pRow = m_wndGrid.CreateRow(m_pRecordsetLand->GetFieldCount());
					for (int j = 0; j < m_pRecordsetLand->GetFieldCount(); j++)
					{
						//CString fieldValue = _T("");
						m_pRecordsetLand->GetFieldInfo(j, &fInfo);
						if (fInfo.m_nType == 4 || fInfo.m_nType == 5)
						{
							double fieldValue = 0.0;
							m_pRecordsetLand->GetFieldValue(j, fieldValue);
							pRow->GetItem(j)->SetValue(fieldValue, TRUE);
						}
						else if (fInfo.m_nType == 11)
						{
							bool fieldValue = false;
							m_pRecordsetLand->GetFieldValue(j, fieldValue);
							pRow->GetItem(j)->SetValue(fieldValue, TRUE);
						}
						else if (fInfo.m_nType == 3)
						{
							int fieldValue = 0;
							m_pRecordsetLand->GetFieldValue(j, fieldValue);
							pRow->GetItem(j)->SetValue(fieldValue, TRUE);
						}
						else
						{
							CString fieldValue = _T("");
							m_pRecordsetLand->GetFieldValue(j, fieldValue);
							pRow->GetItem(j)->SetValue(fieldValue.AllocSysString(), TRUE);
						}
					}
					m_wndGrid.AddRow(pRow, TRUE);	
					m_pRecordsetLand->MoveNext();
				}
			}
			else 
			{
				continue;
			}
		}
	}		

	void vgPipeLayerAttriDlg::getValue()
	{
		Layer *shpLayer = m_ogrPipeLineMap->getShapeLayer();		
		GeometryPointerVec *geoVec = shpLayer->getGeometries();

		GeometryPointerVec ::iterator iter = geoVec->begin();
		GeometryPointerVec ::iterator iter_end = geoVec->end();

		for (; iter != iter_end; iter++)
		{
			vgGIS3D::OGRFeaturePtr pfeature = (*iter)->getOGRFeaturePtr();
			assert( pfeature.isNull() ==false );

			OGRFeature* poFeature = pfeature.getPointer();
			OGRFeatureDefn *poFDefn = poFeature->GetDefnRef();

			int fieldCount = poFDefn->GetFieldCount();

			CBCGPGridRow* pRow = m_wndGrid.CreateRow(fieldCount);
			for (int i = 0; i < fieldCount; i++)
			{
				OGRFieldDefn* fielddefn = poFDefn->GetFieldDefn( i );
				OGRFieldType fieldtype = fielddefn->GetType();

				if ( fieldtype == OFTInteger )
				{
					int* ptr = new int;
					*ptr = poFeature->GetFieldAsInteger( i );
					pRow->ReplaceItem (i, new CBCGPGridItem ((int)*ptr));	
				}
				else if ( fieldtype == OFTReal )
				{
					double* ptr = new double;
					*ptr = poFeature->GetFieldAsDouble( i );
					if (abs(*ptr - (int)*ptr) < 1e-10)
					{
						pRow->ReplaceItem (i, new CBCGPGridItem ((int)*ptr));
					}
					else
					{
						pRow->ReplaceItem (i, new CBCGPGridItem ((double)*ptr));
					}										
				}
				else /*if ( fieldtype == OFTString )*/
				{
					CString temstr(poFeature->GetFieldAsString( i ));
					pRow->GetItem(i)->SetValue(temstr.AllocSysString(), TRUE);					
				}// End if
			}
			m_wndGrid.AddRow(pRow, true);
		}
	}

	void vgPipeLayerAttriDlg::updateList(CString sectionName, CString type, CString initValue)
	{
		UpdateData(true);

		addSortToDatabase(sectionName, type);//添加到数据库

		int count = m_wndGrid.GetColumnCount();
		m_wndGrid.InsertColumn(count, sectionName, 100);		
		
		int index = m_pRecordsetLand->GetRecordCount();

		for (int i = 0; i < index; i++)
		{
			CBCGPGridRow *pRow = m_wndGrid.GetRow(i);
			CBCGPGridItem *item = m_wndGrid.CreateItem(i, 1);			
#if 0			
			if (type == _T("Integer"))
			{	
				int secValue = atoi(initValue);
				item->SetValue(secValue, TRUE);
				pRow->AddItem(item);				
			}
			else if (type == _T("Double"))
			{
				float secValue = atof(initValue);
				item->SetValue(secValue, TRUE);				
				pRow->AddItem(item);
			}
			else
			{
				CString temstr = initValue;
				item->SetValue(temstr.AllocSysString(), TRUE);
				pRow->AddItem(item);
			}
#else
			item->SetValue(initValue.AllocSysString(), TRUE);
			pRow->AddItem(item);
#endif
		}		
		m_wndGrid.AdjustLayout();
		m_wndGrid.Invalidate();		
		UpdateData(FALSE);
		this->Invalidate();				
	}

	//向数据库中添加列
	void vgPipeLayerAttriDlg::addSortToDatabase(CString sectionName, CString type)
	{
		CADODatabase* pAdoDatabase = vgDatabase::DatabaseManager::getSingleton().GetConnectorPtr()->GetCurDatabase();
				
		String recordString = _T("ALTER TABLE");
		recordString += " ";
		recordString += m_tableName;
		recordString += " ";
		recordString += _T("ADD");
		recordString += " ";
		recordString += sectionName;
		recordString += " ";
		
		String typetle = "";
		if (type == _T("Integer"))
		{
			typetle = "INT";
		}
		else if (type == _T("Double"))
		{
			typetle = "FLOAT";
		}
		else
		{
			typetle = "VARCHAR";
		}
		recordString += typetle; 

		CString commandrecord = recordString.c_str();		

		if ( pAdoDatabase->Execute(commandrecord))
		{
			//AfxMessageBox("insert record success!");
		}
		else
		{
			AfxMessageBox("insert record failed!");
			return;
		}
	}

	void vgPipeLayerAttriDlg::OnTimer(UINT_PTR nIDEvent)
	{
		CDialog::OnTimer(nIDEvent);
	}

	void vgPipeLayerAttriDlg::OnDestroy()
	{
		CDialog::OnDestroy();

		// TODO: 在此处添加消息处理程序代码
		//delete this;
	}

	void vgPipeLayerAttriDlg::OnOK()
	{
		m_wndGrid.AdjustLayout();
		m_wndGrid.Invalidate();		
		UpdateData(FALSE);

		CADODatabase* pAdoDatabase = vgDatabase::DatabaseManager::getSingleton().GetConnectorPtr()->GetCurDatabase();

		String commandStr = "DELETE FROM";
		commandStr += " ";
		commandStr += m_tableName;
		CString commandCstr = commandStr.c_str();

		if (!pAdoDatabase->Execute(commandCstr))
		{
			AfxMessageBox("删除原数据库文件失败");
			return;
		}		

		int colNum = m_wndGrid.GetColumnCount();
		int rowNum = m_wndGrid.GetRowCount();

		//////////////////////////////////////////////////////////////////////////
		/////记录入库
		//////////////////////////////////////////////////////////////////////////		
		commandStr.clear();
		commandStr += "INSERT INTO";
		commandStr += " ";
		commandStr += m_tableName;
		commandStr += "(";
		for (int i = 0; i < colNum; i++)
		{
			commandStr += m_wndGrid.GetColumnName(i);

			if (i != colNum-1)
			{
				commandStr += ",";
			}
		}

		commandStr += _T(")\nVALUES\n(");		

		std::ostringstream o;
		String recordStr;
		for (int i = 0; i < rowNum; i++)
		{
			recordStr.clear();
			o.str("");
			recordStr += commandStr;

			CBCGPGridRow *pRow = m_wndGrid.GetRow(i);
			for (int j = 0; j < colNum; j++)
			{
				CString tt(pRow->GetItem(j)->GetValue());	
				
				o << "'";
				o << tt;				
				o << "'";
				if (j != colNum-1)
				{
					o << ",";
				}				
			}
			o << ")";
			recordStr += o.str();
			CString recordCstr = recordStr.c_str();

			if (!pAdoDatabase->Execute(recordCstr))
			{
				AfxMessageBox("保存数据入库发生错误");
				return;
			}
		}

		CDialog::OnOK();
		DestroyWindow();
	}

	void vgPipeLayerAttriDlg::OnAppendOption()
	{
		CPoint   pos;   
		GetCursorPos(&pos); 		
		CMenu *pOptionMenu;
		pOptionMenu = m_menu.GetSubMenu(0); 			
		pOptionMenu->TrackPopupMenu(TPM_LEFTALIGN, pos.x, pos.y, this, NULL);
	}

	void vgPipeLayerAttriDlg::OnAddAttriSection()
	{		
		CWnd* pWnd = vgKernel::SystemUtility::getCurrentViewWnd();
		pWnd->SetTimer( 1, 150, NULL );
		vgAddSectionInfoDlg dlg;
		if (dlg.DoModal() == IDOK)
		{
			CString name = dlg.m_sectionName;
			CString type = dlg.m_wndStr;
			CString initValue = dlg.m_initValue;
			updateList(name, type, initValue);
			return;
		}
		pWnd->SetTimer( 1, 15, NULL );
	}

	void vgPipeLayerAttriDlg::OnPrintPipeAttri()
	{
		if (!m_wndGrid.GetColumnCount())
		{	
			if (AfxMessageBox("属性列表为空，您确定要打印吗", MB_YESNO) != IDYES)
			{
				return;
			}						
		}
		m_wndGrid.Print();
	}

	void vgPipeLayerAttriDlg::OnExportPipeAttri()
	{

	}
}//end namespace


