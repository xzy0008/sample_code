#ifndef VG_BASEDCONNECTOR_H
#define VG_BASEDCONNECTOR_H
#include <vgDatabase/vgdDefinition.h>


#include "AdoX.h"
#include "ado.h"
#include <vgDatabase/vgdProfileManager.h>

namespace vgDatabase
{
	class BasedConnector
	{
	public:
		virtual bool Open() = 0;
		virtual bool Close() = 0;

		virtual void SetDataSource(String dataSource) = 0;
		virtual void SetUserID(String userID) { m_userID = userID; }
		virtual void SetPassword(String password) { m_password = password; }
		
		virtual String GetGridConnectString() = 0;

		virtual String GetDataSource() = 0; //{ return m_dataSource; }
		virtual String GetUserID() { return m_userID; }
		virtual String GetPassword() { return m_password; }

		virtual String CreateQueryFromProfile(QueryProfile* profile, bool isSingleQuery) = 0;

		virtual CADORecordset* Execute(String sqlCommand) = 0;
		virtual CADORecordset* GetRecordSet() = 0;
		
		virtual std::vector<String> GetTablesName() = 0;
		virtual std::vector<String> GetTableColumn(String tableName) = 0;

		//virtual CADODatabase* GetCurDatabase() {return &m_database;}
		virtual CADODatabase* GetCurDatabase() {return m_database;}

		//virtual CADODatabase& GetDatabase() { return m_database; }
		virtual CADODatabase& GetDatabase() { return *m_database; }
	protected:
		CADODatabase *m_database;
		CADORecordset *m_recordSet;

		String m_connectString;
		String m_userID;
		String m_password;
	};
}

#endif