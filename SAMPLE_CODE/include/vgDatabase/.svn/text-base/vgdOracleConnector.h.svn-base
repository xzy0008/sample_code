#ifndef VG_ORACLECONNECTOR_H
#define VG_ORACLECONNECTOR_H
#include <vgDatabase/vgdDefinition.h>


#include <vgDatabase/vgdBasedConnector.h>

namespace vgDatabase
{
	class  VGD_EXPORT OracleConnector : public BasedConnector
	{
	public:
		OracleConnector();
		~OracleConnector();
  
	public:
		virtual bool Open();
		virtual bool Close();
		
		virtual String CreateQueryFromProfile(QueryProfile* profile, bool isSingleQuery);

		virtual String GetDataSource()
		{
			return m_dataSource;
		}

		virtual CADORecordset* Execute(String sqlCommand);
		virtual CADORecordset* GetRecordSet();

		virtual std::vector<String> GetTablesName();
		virtual std::vector<String> GetTableColumn(String tableName);
		virtual void SetDataSource(String dataSource) { m_dataSource = dataSource; }

		virtual String GetGridConnectString() 
		{
			String connectString = "Provider=OraOLEDB.Oracle;Data Source=";
			connectString += m_dataSource;

			return connectString; 
		}
	
	public:

	private:
		String m_dataSource;

	};
}

#endif // VG_ORACLECONNECTOR_H