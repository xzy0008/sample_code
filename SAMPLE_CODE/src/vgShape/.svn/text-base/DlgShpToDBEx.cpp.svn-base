// DlgShpToDB.cpp : implementation file
//

#include <vgStableHeaders.h>
#include "vgShape/DlgShpToDBEx.h"

#include <vgShape/vgshShapeManager.h>
#include <vgShape/vgshExtendedUtility.h>
#include <vgKernel/vgkStringUtility.h>
#include <vgKernel/vgkSystemUtility.h>


#include "gdal/ogrsf_frmts.h"
#include "gdal/ogr_api.h"


// CDlgShpToDBEx dialog

IMPLEMENT_DYNAMIC(CDlgShpToDBEx, CDialog)

CDlgShpToDBEx::CDlgShpToDBEx(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgShpToDBEx::IDD, pParent)
	, m_nCurrentKeyField(-1)
	, m_nCurrentLayer(-1)
	, m_nCurrentLayerType(-1)
{

}

CDlgShpToDBEx::~CDlgShpToDBEx()
{
}

void	CDlgShpToDBEx::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_BOOL_IN_DB, m_layerTypeList);
	DDX_Control(pDX, IDC_LIST_LAYER, m_layerInfoList);
	DDX_Control(pDX, IDC_LIST_FIELD, m_fieldInfoList);
	DDX_Control(pDX, IDC_LIST_LAYER_FIELD, m_resultList);
}

BOOL	CDlgShpToDBEx::OnInitDialog()
{
	CDialog::OnInitDialog();

	/*vgVector::LayerPtrMap*	pLayerPtrMap = 
		vgVector::VectorManager::getSingleton().getLayerPtrMap();

	if (pLayerPtrMap->empty())
	{
		MessageBox("没有任何图层！");
		OnCancel();
		return false;
	}*/
	vgShape::DataSourcePtrMap*	pDatasources = 
		vgShape::ShapeManager::getSingleton().getDataSources();
	if (pDatasources->empty())
	{
		MessageBox("没有任何图层！");
		OnCancel();
		return false;
	}


	// add by lss when 2008-12-10 15:59:03
	m_layerTypeList.AddString("已入库");
	m_layerTypeList.AddString("未入库");
	m_layerTypeList.SetCurSel(0);

	// 获取某类型（已入库或未入库的）图层列表
	OnCbnSelchangeListBoolInDb();

	UpdateData(FALSE);
	return	TRUE;
}



//BOOL CDlgShpToDBEx::OnInitDialog()
//{
//	CDialog::OnInitDialog();
//
//	vgVector::LayerPtrMap*	pLayerPtrMap = vgVector::VectorManager::getSingleton().getLayerPtrMap();
//
//	if (pLayerPtrMap->empty())
//	{
//		MessageBox("没有任何图层！");
//		OnCancel();
//		return false;
//	}
//
//	CString	strLayerName;
//	for(vgVector::LayerPtrMapItr itrMap = pLayerPtrMap->begin();
//		itrMap != pLayerPtrMap->end(); itrMap ++ )
//	{
//		vgVector::LayerPtrVector* pLayerPtrArray = itrMap->second;
//		for (vgVector::LayerPtrVectorItr itrArr = pLayerPtrArray->begin();
//			itrArr != pLayerPtrArray->end(); itrArr++)
//		{
//			(*itrArr)->setKeyField(strKeyFieldArray.at(nKeyFieldIndex));
//			m_LayerPtrVector.push_back(*itrArr);
//			strLayerName = (*itrArr)->getName().c_str();
//			m_layerInfoList.AddString( strLayerName );
//
//		}
//	}
//
//	m_layerInfoList.SetCurSel(0);
//
//	UpdateData(FALSE);
//	return	TRUE;
//}
//


BEGIN_MESSAGE_MAP(CDlgShpToDBEx, CDialog) 
	ON_CBN_SELCHANGE(IDC_LIST_LAYER, &CDlgShpToDBEx::OnCbnSelchangeListLayer)
	ON_BN_CLICKED(IDC_BTN_SUBMIT, &CDlgShpToDBEx::OnBnClickedBtnSubmit)
	ON_CBN_SELCHANGE(IDC_LIST_FIELD, &CDlgShpToDBEx::OnCbnSelchangeListField)
	ON_BN_CLICKED(IDC_BTN_SHP2DB2, &CDlgShpToDBEx::OnBnClickedBtnShp2db2)
	ON_CBN_SELCHANGE(IDC_LIST_BOOL_IN_DB, &CDlgShpToDBEx::OnCbnSelchangeListBoolInDb)
END_MESSAGE_MAP()


// CDlgShpToDBEx message handlers
// DlgSetShp2Db 消息处理程序-------------------------------------------	
void	CDlgShpToDBEx::OnCbnSelchangeListLayer()
{
	// TODO: 在此添加控件通知处理程序代码

	UpdateData(TRUE);

	m_strFieldArray.clear();
	m_fieldInfoList.ResetContent();

	if( 0 == m_layerInfoList.GetCount())
	{
		return;
	}

	m_nCurrentLayer = m_layerInfoList.GetCurSel();

	//m_pCurrentLayer = m_LayerPtrVector[m_nCurrentLayer].getPointer();
	m_pCurrentLayer = m_LayersReadyToSet[m_nCurrentLayer];

	CString	fieldName, fieldType, fieldItem, layerName;

	OGRFeatureDefn*	pFeatureDef = m_pCurrentLayer->getFeatureDefn();

	layerName.Format("%-15s", m_pCurrentLayer->getName().c_str() ) ;
	for(int  iField = 0; iField < pFeatureDef->GetFieldCount(); iField++ )
	{
		OGRFieldDefn *m_poFieldDefn = pFeatureDef->GetFieldDefn( iField );

		// Part 11：读取字段名称
		fieldName.Format("%-15s", m_poFieldDefn->GetNameRef());

		// Part 12：读取字段类型
		switch (m_poFieldDefn->GetType())
		{
		case OFTInteger:
			fieldType	= "Integer";
			break;
		case OFTReal:
			fieldType	= "Real";
			break;
		case OFTString:
			fieldType	= "String";
			break;
		case OFTDate:
			fieldType	= "Date";
			break;		
		default:
			fieldType	= "Unknown";
			break;	
		}//switch

		fieldItem = /*layerName +*/ fieldName + fieldType;

		m_fieldInfoList.AddString(fieldItem);
		m_strFieldArray.push_back(String(fieldName));

	}//for

	//m_nCurrentKeyField = m_pCurrentLayer->getIndexKeyField();
	
	if(-1 == m_nCurrentKeyField)
	{
		m_nCurrentKeyField = 0;
	}
	m_fieldInfoList.SetCurSel(m_nCurrentKeyField);

	OnCbnSelchangeListField();

	UpdateData(FALSE);

}

//---------------------------------------------------------------------	
void	CDlgShpToDBEx::OnBnClickedBtnSubmit()
{
	// TODO: 在此添加控件通知处理程序代码

	if (0==m_strFieldArray.size() )
	{
		AfxMessageBox("请先选择层并为其选定主键！");
		return;
	}

	String	strCurrentLayer = m_pCurrentLayer->getName();
	String	strCurrentField = m_strFieldArray[m_nCurrentKeyField];
	String	strListItem = strCurrentLayer + " - " + strCurrentField;

	/*if( m_pCurrentLayer->getIndexKeyField() == m_nCurrentKeyField)
	{
		AfxMessageBox("主键无修改，不需要重新入库！");
		return ;
	}*/
	
	int nLayerPos	= IsAllreadyInsert(m_pCurrentLayer);

	if(nLayerPos != -1 && nLayerPos < m_resultList.GetCount() )
	{
		
//		m_pCurrentLayer->setIndexKeyField(m_nCurrentKeyField);

		m_resultList.DeleteString( nLayerPos );
		m_resultList.InsertString( nLayerPos , strListItem.c_str());

	}
	else
	{
//		m_pCurrentLayer->setIndexKeyField(m_nCurrentKeyField);
		m_LayersReadyToDB.push_back(m_pCurrentLayer);
		//m_LayerKeyFieldMap.insert( std::make_pair(m_pCurrentLayer ,m_nCurrentKeyField ) );
		m_resultList.AddString(strListItem.c_str());
	}

	UpdateData(FALSE);
}

//---------------------------------------------------------------------	
void	CDlgShpToDBEx::OnCbnSelchangeListField()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	m_nCurrentKeyField = m_fieldInfoList.GetCurSel();
	UpdateData(FALSE);
}
//---------------------------------------------------------------------	
void	CDlgShpToDBEx::OnBnClickedBtnShp2db2()
{
	assert(0);
#if 0
	// TODO: 在此添加控件通知处理程序代码
	if (!vgDatabase::DatabaseManager::getSingleton().IsOpen())
	{
		AfxMessageBox("请先连接数据库！");
		return;
	}

//	vgUI::UIController::getSingleton().ClearSelection();

	String	strDBName;
	int		nCountSucceed = 0;

	for(vgShape::LayerPtrVector::iterator	itr = m_LayersReadyToDB.begin();
		itr != m_LayersReadyToDB.end(); itr ++)
	{

		// Step 1：将一个层的图元重命名
		renamaeLayerShapes(*itr);

		// Step 2：整个图层的属性导入到一种新表中
		writeLayerRecordsToDatabaseTable(*itr) ;
			

		nCountSucceed ++;
		strDBName += (*itr)->getName();
		strDBName += " ";
	}

	std::ostringstream oStr;
	oStr << nCountSucceed;
	strDBName += "，共";
	strDBName += oStr.str();
	strDBName += "个表入库操作已完成！";
	AfxMessageBox( strDBName.c_str() );


	char exebuf[512];
	DWORD getret = GetModuleFileName( NULL , exebuf , 512 );

	assert( getret < 512 );
	assert( getret > 0 );

	String exestr( exebuf );
	String exepath = exestr.substr( 0 , 
		exestr.find_last_of("\\/")  + 1);

	String profilePath = exepath + "profile.xml";

	std::vector<vgDatabase::QueryProfile>& queryprofilelist = vgDatabase::ProfileManager::getSingleton().GetProfiles();

	queryprofilelist.clear();

	vgDatabase::ProfileManager::getSingleton().LoadFromFile(profilePath);

	// 更新界面
	OnCbnSelchangeListBoolInDb();

	return;
#endif
}

//---------------------------------------------------------------------	
bool	CDlgShpToDBEx::writeLayerRecordsToDatabaseTable(
	vgShape::LayerPtr pCurrentLayer, bool bCreateNew/* = true*/)
{
	//if( bCreateNew && IDOK != MessageBox(
	//	"该图层对应的属性表已存在，是否覆盖？","", MB_YESNO) )
	//{
	//	return false;
	//}
	//	
	//vgDatabase::DatabaseManager::getSingleton().DeleteTable(pCurrentLayer->getName());
		

	if (!CreateShapeTable(pCurrentLayer.getPointer()))
	{
		return false;
	}

	/*char exebuf[512];
	DWORD getret = GetModuleFileName( NULL , exebuf , 512 );

	assert( getret < 512 );
	assert( getret > 0 );

	String exestr( exebuf );
	String exepath = exestr.substr( 0 , 
		exestr.find_last_of("\\/")  + 1);*/

	String savePath = vgKernel::SystemUtility::getCurrentProcessPath();

	savePath = vgKernel::StringUtility::getPathFromAbsoluteFilename(savePath);
	
	String profilePath = savePath + "profile.xml";

// 	vgDatabase::ProfileManager::getSingleton().AppendFile(
// 		pCurrentLayer.getPointer(),profilePath,-1/*nKeyField*//*m_nKeyFieldID*/);
	AppendFile(pCurrentLayer,profilePath,-1);
	return	true;
}
//---------------------------------------------------------------------	
bool	CDlgShpToDBEx::renamaeLayerShapes(vgShape::LayerPtr pCurrentLayer
										, int nKeyField/* = -1*/)
{
	return true;
	//return	vgVector::VectorManager::getSingleton().renameLayerShapesByKeyField(
	//	pCurrentLayer, nKeyField);
}

//---------------------------------------------------------------------	
int		CDlgShpToDBEx::IsAllreadyInsert(vgShape::LayerPtr pCurrentLayer)
{
	int nLayerIndex = 0, nLayerPos = -1;
	for(vgShape::LayerPtrVector::iterator	itr = m_LayersReadyToDB.begin();
		itr != m_LayersReadyToDB.end(); itr ++, nLayerIndex++)
	{
		if( itr->getPointer() == pCurrentLayer.getPointer() )
		{
			nLayerPos = nLayerIndex;
			break;
		}
	}

	return  nLayerPos;
}	
//---------------------------------------------------------------------	
void	CDlgShpToDBEx::OnCbnSelchangeListBoolInDb()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	
	m_LayersReadyToSet.clear();
	m_layerInfoList.ResetContent();

	m_LayersReadyToDB.clear();
	m_resultList.ResetContent();

	m_nCurrentLayerType = m_layerTypeList.GetCurSel();

	using namespace vgShape;
	//	Step1：过滤某类型（已入库或未入库的）图层列表
	DataSourcePtrMap*	pDatasources = ShapeManager::getSingleton().getDataSources();
	DataSourcePtrMap::iterator iterOut = pDatasources->begin();
	DataSourcePtrMap::iterator iter_endOut = pDatasources->end();

	bool	bSelectLayer = false;
	for ( ;iterOut != iter_endOut ; ++iterOut )
	{
		LayerPtrVector* pLayers = iterOut->second->getLayerPtrVector();

		LayerPtrVector::iterator iterIn = pLayers->begin();
		LayerPtrVector::iterator iter_endIn = pLayers->end();

		for ( ; iterIn != iter_endIn ; ++ iterIn )
		{
			m_LayersReadyToSet.push_back(*iterIn);
		}
	}
	//vgVector::LayerPtrMap*	pLayerPtrMap = 
	//	vgVector::VectorManager::getSingleton().getLayerPtrMap();

	////	Step1：过滤某类型（已入库或未入库的）图层列表
	//bool	bSelectLayer = false;
	//for(vgVector::LayerPtrMapItr itrMap = pLayerPtrMap->begin();
	//	itrMap != pLayerPtrMap->end(); itrMap ++ )
	//{
	//	vgVector::LayerPtrVector* pLayerPtrArray = itrMap->second;
	//	for (vgVector::LayerPtrVectorItr itrArr = pLayerPtrArray->begin();
	//		itrArr != pLayerPtrArray->end(); itrArr++)
	//	{
	//		switch(m_nCurrentLayerType)
	//		{
	//		case 0:
	//			bSelectLayer = (*itrArr)->isInDB();
	//			break;
	//		case 1:
	//			bSelectLayer = !(*itrArr)->isInDB();
	//			break;
	//		default:
	//			bSelectLayer = false;
	//			break;
	//		}

	//		if( bSelectLayer )
	//		{
	//			m_LayersReadyToSet.push_back(*itrArr);
	//		}

	//	}//for(vector)

	//}//for(type)


	//	Step2：显示图层列表
	for(LayerPtrVector::iterator	itr = m_LayersReadyToSet.begin();
		itr != m_LayersReadyToSet.end(); itr ++)
	{
		m_layerInfoList.AddString( (*itr)->getName().c_str() );
	}

	m_layerInfoList.SetCurSel(0);


	//	Step3：显示缺省图层的字段列表
	OnCbnSelchangeListLayer();

	UpdateData(FALSE);
}

//---------------------------------------------------------------------	
bool CDlgShpToDBEx::AppendFile( vgShape::LayerPtr pCurrentLayer,
							   String filename,int PrimaryId )
{
	assert(0);
#if 0
	String buffer;
	String buffer2;
	//step1:导入profile整体框架
	String profileName = pCurrentLayer->getName();

	TiXmlNode *profileNode = vgDatabase::ProfileManager::getSingleton().AppendXmlProfile(filename,profileName);

	if (profileNode == NULL)
	{
		return false;
	}

	//step2:插入表名
	vgDatabase::ProfileManager::getSingleton().InsertTable(profileNode,profileName);
	//step3:插入字段名
	OGRFeatureDefn  *m_poFeatureDefn = pCurrentLayer->getFeatureDefn();

	buffer = pCurrentLayer->getName();
	buffer += ".";
	buffer += "PRIMARYID";

	buffer2 = "PRIMARYID";

	vgDatabase::ProfileManager::getSingleton().InsertFeild(profileNode,buffer,buffer2);

	for(int  iField = 0; iField < m_poFeatureDefn->GetFieldCount(); iField++ )
	{
		OGRFieldDefn *m_poFieldDefn = m_poFeatureDefn->GetFieldDefn( iField );

		buffer = pCurrentLayer->getName();
		buffer += ".";
		buffer += m_poFieldDefn->GetNameRef();

		buffer2 = m_poFieldDefn->GetNameRef();

		vgDatabase::ProfileManager::getSingleton().InsertFeild(profileNode,buffer,buffer2);

	}
	//插入主键名
	buffer = pCurrentLayer->getName();
	buffer += ".";

	if (PrimaryId == -1)
	{
		buffer += "PRIMARYID";
	}
	else
	{		
		OGRFieldDefn *m_poFieldDefn = m_poFeatureDefn->GetFieldDefn( PrimaryId );
		buffer += m_poFieldDefn->GetNameRef();
	}

	vgDatabase::ProfileManager::getSingleton().InsertPrimaryId(profileNode,buffer);
	//step4:保存更改
	vgDatabase::ProfileManager::getSingleton().SaveXmlProfile();
#endif

	return true;
}
//---------------------------------------------------------------------	
bool CDlgShpToDBEx::CreateShapeTable(vgShape::Layer*	pCurrentLayer) //YXDB lss
{
	assert(0);
#if 0

	CADODatabase* pAdoDatabase = vgDatabase::DatabaseManager::getSingleton().GetConnectorPtr()->GetCurDatabase();
	vgDatabase::BasedConnector* connectorptr = vgDatabase::DatabaseManager::getSingleton().GetConnectorPtr();
	std::vector<String>  tablelist = connectorptr->GetTablesName();

	//创建表

	String ColumnNameList = _T("INSERT INTO ");

	String tableCommandString = _T("Create Table ");

	tableCommandString += pCurrentLayer->getName();
	ColumnNameList += pCurrentLayer->getName();

	String tablename = pCurrentLayer->getName();

	transform(tablename.begin(), tablename.end(), tablename.begin(), toupper);

	for (int i =0 ;i < tablelist.size();i++ )
	{
		if (tablename==tablelist[i])
		{
			//AfxMessageBox("此表已存在，请仔细核对!");
			//return false;

			if(!vgDatabase::DatabaseManager::getSingleton().GetStatus())
			{
				int nStatus = ::MessageBox(NULL,
					"该图层对应的属性表已存在，是否覆盖？",
					"新建表", MB_YESNO );
				if( IDNO == nStatus )
				{
					return false;
				}
				else if( IDYES == nStatus )
				{
					vgDatabase::DatabaseManager::getSingleton().SetStatus(true);
				}
			}

			vgDatabase::DatabaseManager::getSingleton().DeleteTable(tablename);
			break;
		}
	}

	tableCommandString += _T("(");
	ColumnNameList += _T("(");

	OGRFeatureDefn  *m_poFeatureDefn = 
		pCurrentLayer->getFeatureDefn();

	//==========================================================================//YXDBNAME

	tableCommandString += _T("PRIMARYID VARCHAR(100),");
	ColumnNameList += _T("PRIMARYID,");
	//==========================================================================		

	for(int  iField = 0; iField < m_poFeatureDefn->GetFieldCount(); iField++ )
	{
		OGRFieldDefn *m_poFieldDefn = m_poFeatureDefn->GetFieldDefn( iField );

		// Part 1：读取字段名称
		tableCommandString += m_poFieldDefn->GetNameRef();

		ColumnNameList += m_poFieldDefn->GetNameRef();

		tableCommandString += _T("  ");

		// Part 2：读取字段类型
		switch (m_poFieldDefn->GetType())
		{
		case OFTInteger:
			//tableCommandString += _T("FLOAT");
			tableCommandString += _T("INTEGER");
			break;
		case OFTReal:
			tableCommandString += _T("FLOAT");
			break;
		case OFTString:
			tableCommandString += _T("VARCHAR");
			break;
		case OFTDate:
			tableCommandString += _T("DATE");
			break;		
		default:
			tableCommandString += _T("VARCHAR");
			break;	
		}

		if (m_poFieldDefn->GetType() != OFTReal)
		{
			tableCommandString += _T("(");

			// Part 3：读取字段宽度
			CString temp;
			temp.Format("%d",m_poFieldDefn->GetWidth());
			tableCommandString += temp.GetString();

			tableCommandString += _T(")");
		}

		if (iField != m_poFeatureDefn->GetFieldCount()-1)
		{
			tableCommandString+=_T(",\n");
			ColumnNameList += _T(",");
		}		
	}

	tableCommandString += _T(")");
	ColumnNameList += _T(")\nVALUES\n(");

	if (!pAdoDatabase->IsOpen())
	{
		AfxMessageBox("failed open database");
		return false;
	}

	CString commandstring = tableCommandString.c_str();

	//AfxMessageBox(commandstring);

	if (pAdoDatabase->Execute(commandstring))
	{
		//AfxMessageBox("execute success!");
	}
	else
	{
		AfxMessageBox("failed");
		return false;
	}

	////////////////////////////
	//记录入库
	////////////////////////////

	String recordstring;

	using namespace vgShape;
	GeometryPointerVec* pGeometries = pCurrentLayer->getGeometries();
	GeometryPointerVec::iterator iter = pGeometries->begin();
	GeometryPointerVec::iterator iter_end= pGeometries->end();

	for ( ; iter != iter_end ; ++ iter )
	{
		Geometry* geo = *iter;

		OGRFeaturePtr pfeat = geo->getOGRFeaturePtr();

		recordstring.clear();
		recordstring += ColumnNameList;


		int iFieldNum = 0;
		char szTempBuffer[40];
		char    szFormat[40];


		//================================================================================//YXDBNAME
		recordstring += _T("'");
		recordstring += _T("'");//m_geometry->getName();
		recordstring += _T("'");
		recordstring += _T(",");
		//================================================================================


		for (int fieldIndex = 0; fieldIndex < pfeat->GetFieldCount() ; fieldIndex++)
		{
			OGRFieldDefn *poFDefn = pfeat->GetFieldDefnRef( fieldIndex );

			OGRField*	pFieldValue = pfeat->GetRawFieldRef( fieldIndex );

			switch (poFDefn->GetType())
			{
			case OFTString:
				{
					if( pFieldValue->Set.nMarker1 == OGRUnsetMarker )
					{
						recordstring += "NULL"; 
					}
					else
					{
						recordstring += _T("'");
						recordstring += pFieldValue->String ;
						recordstring += _T("'");							
					}	

				}
				break;

			case OFTInteger:
				{
					if( pFieldValue->Set.nMarker1 == OGRUnsetMarker )
					{
						recordstring += "NULL"; 
					}
					else
					{
						snprintf( szFormat, 40, "%%%dd",
							poFDefn->GetWidth());

						snprintf( szTempBuffer, 40,
							szFormat, pFieldValue->Integer );

						recordstring += szTempBuffer ;		

					}	

				}				
				break;

			case OFTReal:
				{
					if( pFieldValue->Set.nMarker1 == OGRUnsetMarker )
					{
						recordstring += "NULL"; 
					}
					else
					{
						if( poFDefn->GetWidth() != 0 )
						{
							snprintf( szFormat, 40, "%%%d.%df",
								poFDefn->GetWidth(), poFDefn->GetPrecision() );
						}
						else
							strcpy( szFormat, "%.15g" );

						snprintf( szTempBuffer, 40,
							szFormat, pFieldValue->Real );
						recordstring += szTempBuffer ;	

					}	

				}				
				break;


			case OFTDate:
				{
					if( pFieldValue->Set.nMarker1 == OGRUnsetMarker )
					{
						recordstring += "NULL"; 
					}
					else
					{
						snprintf( szTempBuffer, 40, "%04d-%02d月-%02d",
							pFieldValue->Date.Day,
							pFieldValue->Date.Month,
							pFieldValue->Date.Year);
						recordstring += szTempBuffer;

					}	

				}				
				break;

			default:
				recordstring += '\0';
				break;
			}//switch


			if (fieldIndex == pfeat->GetFieldCount()-1 )
			{
				recordstring += _T(",");
			}
		}//for

		recordstring += _T(")");

		CString commandrecord = recordstring.c_str();

		//AfxMessageBox(commandrecord);

		if ( pAdoDatabase->Execute(commandrecord))
		{
			//AfxMessageBox("insert record success!");
		}
		else
		{
			AfxMessageBox("insert record failed!");
			return false;
		}
	}//for

	AfxMessageBox("CREATE TABLE SUCCESS!");
#endif

	return true;

}//function


//---------------------------------------------------------------------	
