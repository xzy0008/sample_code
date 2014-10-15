#pragma once

#include <vgDatabase/vgdBasedConnector.h>

namespace vgDatabase
{
	class  VGD_EXPORT AccessConnector : public BasedConnector
	{
	public:
		AccessConnector();
		~AccessConnector();

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
			String connectString = "Provider=Microsoft.JET.OLEDB.4.0;Data source=";
			connectString += m_dataSource;

			return connectString; 
		}

	public:

	private:
		String m_dataSource;

	};
}
