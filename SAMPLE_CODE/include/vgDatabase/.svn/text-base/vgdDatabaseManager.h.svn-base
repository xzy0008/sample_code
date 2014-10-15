#ifndef VGD_DATABASEMANAGER_H
#define VGD_DATABASEMANAGER_H
#include <vgDatabase/vgdDefinition.h>


#include <vgKernel/vgkForward.h>
#include <vgkernel/vgkSingleton.h>
#include <vgkernel/vgkSingletonLifeTimeDefine.h>

#include <vgDatabase/vgdBasedConnector.h>

// #include <vgShape/vgshLayer.h>

namespace vgDatabase
{
	/**
	@date 	2008/10/7  19:21	
	@author  ZSC

	@brief 	

	@see    
	*/
	enum VG_DATABASE_TYPE
	{
		VG_DATABASE_ORACLE,
		VG_DATABASE_SQLSERVER,
		VG_DATABASE_MYSQL,
		VG_DATABASE_ACCESS,

		VG_DATABASE_SUPPORTED_NUM
	};

	class  VGD_EXPORT DatabaseManager : public vgKernel::Singleton<DatabaseManager>
	{
		friend class vgKernel::Singleton<DatabaseManager>;

	public:
		DatabaseManager();

		~DatabaseManager();
		
		int GetDataBaseType() { return m_databaseType; }

		bool CreateConnector(int databaseType);

		BasedConnector* GetConnectorPtr() { return m_pConnector; }

		bool OpenDatabase();
		
		bool CloseDatabase();

		bool IsOpen() { return m_isOpen; }

		bool GetStatus() { return m_isYesToAll; }

		void SetStatus(bool status) { m_isYesToAll = status; }

	public:

		bool DeleteTable( String tablename );

		void reset();

	protected:
		bool initialise() { return true; }

		bool shutdown() { return true; }

	private:
		 BasedConnector* m_pConnector;
		 int m_databaseType;

		 bool m_isOpen;
		 bool m_isYesToAll;
	};
}

#endif


