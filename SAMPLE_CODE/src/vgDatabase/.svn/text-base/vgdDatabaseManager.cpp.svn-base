
#include <vgstableheaders.h>
#include <vgDatabase/vgdDatabaseManager.h>
#include <vgDatabase/vgdOracleConnector.h>

#include <vgDatabase/vgdProfileManager.h>
#include <vgDatabase/vgdBasedConnector.h>
#include <vgDatabase/vgdOracleConnector.h>
#include <vgDatabase/vgdAccessConnector.h>

namespace vgDatabase
{
	DatabaseManager::DatabaseManager(): Singleton<DatabaseManager>(VGK_SIGLETON_LEFE_DATABASEMANAGER)
	{
		m_pConnector = NULL;
		m_databaseType = -1;
		m_isOpen = false;
		m_isYesToAll = false;
	}

	DatabaseManager::~DatabaseManager()
	{
		delete m_pConnector;//chunyong postil
		m_pConnector = NULL;
	}
	
	bool DatabaseManager::CreateConnector(int databaseType)
	{
		if (m_pConnector != NULL)
		{
			delete m_pConnector;
			m_pConnector = NULL;//chunyong postil
		}		
		
		if (databaseType == VG_DATABASE_ORACLE)
		{
			m_databaseType = databaseType;
			m_pConnector = new OracleConnector();
		}
		else if (databaseType == VG_DATABASE_ACCESS)
		{
			m_databaseType = databaseType;
			m_pConnector = new AccessConnector();
		}
		else
		{
			ASSERT(0 && "数据库设置为非oracle类型");//chunyong postil
		}
	
		return true;
	}

	bool DatabaseManager::OpenDatabase()
	{
		if (m_pConnector == NULL)
			return false;

		m_isOpen = m_pConnector->Open();

		return m_isOpen;
	}

	bool DatabaseManager::CloseDatabase()
	{
		if (m_pConnector == NULL)
			return false;
		
		if (! m_isOpen)
			return false;

		m_isOpen = ! m_pConnector->Close();

		return !m_isOpen;
	}

	bool DatabaseManager::DeleteTable( String tablename )
	{
		 CADODatabase* pAdoDatabase = GetConnectorPtr()->GetCurDatabase();

		 String commandstring = _T("DROP TABLE ");

		 commandstring += tablename;

		 if (!pAdoDatabase->Execute(commandstring.c_str()))
		 {
			 return false;
		 }

		 return true;
	}//  [12/11/2008 yuxin]

	void DatabaseManager::reset()
	{
		CloseDatabase();
		if ( m_pConnector != NULL )
		{
			delete m_pConnector;//chunyong postil
			m_pConnector = NULL;
		}

		m_databaseType = -1;
		m_isOpen = false;
		m_isYesToAll = false;
	}
}//namespace