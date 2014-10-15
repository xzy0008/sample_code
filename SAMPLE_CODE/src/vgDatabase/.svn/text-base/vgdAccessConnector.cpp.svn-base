#include "vgStableHeaders.h"
#include "vgDatabase/vgdAccessConnector.h"
#include <vgDatabase/vgdDatabaseManager.h>


namespace vgDatabase
{
	AccessConnector::AccessConnector()
	{
		m_recordSet = new CADORecordset;
		m_database = new CADODatabase;
	}

	AccessConnector::~AccessConnector()
	{
		this->Close();
		if ( m_recordSet != NULL )
		{
			delete m_recordSet;
			m_recordSet = NULL;
		}
		if ( m_database != NULL )
		{
			delete m_database;
			m_database = NULL;
		}
	}

	bool AccessConnector::Open()
	{
		//if (m_database.IsOpen())
		//{
		//	return true;
		//}
		if (m_database->IsOpen())
		{
			return true;
		}

		m_connectString = "Provider=Microsoft.JET.OLEDB.4.0;Data source=";
		m_connectString += m_dataSource;
		m_connectString += ";";

		//return m_database.Open(m_connectString.c_str(), m_userID.c_str(), m_password.c_str()) == TRUE;
		return m_database->Open(m_connectString.c_str(), m_userID.c_str(), m_password.c_str()) == TRUE;

	}

	bool AccessConnector::Close()
	{
		bool re = true;

		//if (m_database.IsOpen())
		//{
		//	m_database.Close();
		//}
		if (m_database->IsOpen())
		{
			m_database->Close();
		}

		//if (m_recordSet.IsOpen())
		//{
		//	m_recordSet.Close();
		//}
		if (m_recordSet->IsOpen())
		{
			m_recordSet->Close();
		}

		return true;
	}

	CADORecordset* AccessConnector::Execute(String sqlCommand)
	{
		//if (m_recordSet.Open(m_database.GetActiveConnection(), sqlCommand.c_str()))
		//{
		//	return &m_recordSet;
		//}

		if (m_recordSet->Open(m_database->GetActiveConnection(), sqlCommand.c_str()))
		{
			return m_recordSet;
		}

		return NULL;
	}


	CADORecordset* AccessConnector::GetRecordSet()
	{
		//return &m_recordSet;
		return m_recordSet;
	}

	std::vector<String> AccessConnector::GetTableColumn(String tableName)
	{
		std::vector<String> columnArray;

		return columnArray;
	}

	std::vector<String> AccessConnector::GetTablesName()
	{
		std::vector<String> tableArray;

		//CRecordset pRstSchema  =   m_database->OpenSchema(adSchemaTables);  
		_variant_t	vData;

		//_RecordsetPtr pRecordSet = m_database.m_pConnection->OpenSchema(adSchemaTables);  
		_RecordsetPtr pRecordSet = m_database->m_pConnection->OpenSchema(adSchemaTables);  

		//CADOFieldInfo fieldInfo;
		
		if (pRecordSet == NULL)
		{
			AfxMessageBox("得到列表失败");
		}

		while(!pRecordSet->ADOEOF)  
		{  			
			_bstr_t   table_name   =   pRecordSet->Fields->  
				GetItem("TABLE_NAME")->Value;     

			CString cstr = table_name;

			tableArray.push_back(cstr.GetString());
			pRecordSet->MoveNext();   
		}   

		pRecordSet->Close();

		return tableArray;
	}

	String AccessConnector::CreateQueryFromProfile(QueryProfile* profile, bool isSingleQuery)
	{
		String queryString = "select ";
		int j;

		for (j=0; j<profile->m_recordList.size(); j++)
		{
			queryString += profile->m_recordList[j];
			queryString += " as ";
			queryString += profile->m_shownNameList[j];
			if (j != profile->m_recordList.size()-1)
			{
				queryString += ", ";
			}
		}

		queryString += " from ";

		for (j=0; j<profile->m_tableList.size(); j++)
		{
			queryString += profile->m_tableList[j];
			if (j != profile->m_tableList.size()-1)
			{
				queryString += ", ";
			}
		}

		if (profile->m_connectList.size() > 0 || profile->m_primaryRecordList.size() > 0)
		{
			queryString += " where ";

			for (j=0; j<profile->m_connectList.size(); j++)
			{
				queryString += profile->m_connectList[j];
				if (j != profile->m_connectList.size()-1)
				{
					queryString += " and ";
				}
			}

			// 单个查询时 使用primary key确定唯一的行
			if (isSingleQuery)
			{
				if (profile->m_connectList.size() > 0)
				{
					queryString += " and ";
				}

				for (j=0; j<profile->m_primaryRecordList.size(); j++)
				{
					queryString += profile->m_primaryRecordList[j];
					queryString += " = ";
				}
			}
		}

		return queryString;
	}
}