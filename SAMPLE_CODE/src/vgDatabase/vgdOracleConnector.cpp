#include "vgStableHeaders.h"
#include "vgDatabase/vgdOracleConnector.h"
#include <vgDatabase/vgdDatabaseManager.h>

namespace vgDatabase
{
	OracleConnector::OracleConnector()
	{
		m_recordSet = new CADORecordset;
		m_database = new CADODatabase;
	}

	OracleConnector::~OracleConnector()
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

	bool OracleConnector::Open()
	{
		//if (m_database.IsOpen())
		//{
		//	return true;
		//}
		if (m_database->IsOpen())
		{
			return true;
		}

		m_connectString = "Provider=OraOLEDB.Oracle;Data Source=";
		m_connectString += m_dataSource;
		m_connectString += ";";

		//return m_database.Open(m_connectString.c_str(), m_userID.c_str(), m_password.c_str()) == TRUE;
		return m_database->Open(m_connectString.c_str(), m_userID.c_str(), m_password.c_str()) == TRUE;

	}

	bool OracleConnector::Close()
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

	CADORecordset* OracleConnector::Execute(String sqlCommand)
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
	

	CADORecordset* OracleConnector::GetRecordSet()
	{
		//return &m_recordSet;
		return m_recordSet;
	}

	std::vector<String> OracleConnector::GetTableColumn(String tableName)
	{
		std::vector<String> columnArray;

		return columnArray;
	}

	std::vector<String> OracleConnector::GetTablesName()
	{
		std::vector<String> tableArray;

		String m_queryString = "SELECT * FROM CAT";
		CADORecordset* recordSet = vgDatabase::DatabaseManager::getSingleton().GetConnectorPtr()->Execute(m_queryString);
		
		if (recordSet == NULL)
		{
			AfxMessageBox("查询未能成功执行 请检查Profile是否正确");
			return tableArray;
		}
		
		//CADOFieldInfo fieldInfo;
		_variant_t data;
		CString temp;
		String tablename;

		recordSet->MoveFirst();

		for (int i=0; i<recordSet->GetRecordCount(); i++)
		{
			recordSet->GetFieldValue(0, data);

			temp = data;

			tablename = temp.GetString();

			tableArray.push_back(tablename);

			recordSet->MoveNext();
		}

		recordSet->Close();

		return tableArray;
	}//YX

	String OracleConnector::CreateQueryFromProfile(QueryProfile* profile, bool isSingleQuery)
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