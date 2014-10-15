////////////////////////////////////////////////////////////////////////////
//  
//		AdoX.h: 声明数据库结构操作ADOX类库(CADOXTable、CADOUser、CADOProcedure
//                                         、CADOIndex、CADOView、CADOCatalog)接口
//
///////////////////////////////////////////////////////////////////////////

#ifndef _ADOX_H_INCLUDED_
#define _ADOX_H_INCLUDED_

#include "AdoImport.h"
//using namespace ADOX;

//-------------------------------------------------------------------------/
//                    Class CADOXTable : 定义数据库表Table管理类
//-------------------------------------------------------------------------/
class CADOXIndex;
class CADOXCatalog;

class CADOXTable
{
public:
	enum DataType
	{
		typeSmallInt = ADOX::adSmallInt,
		typeInteger = ADOX::adInteger,
		typeUnsignedTinyInt = ADOX::adUnsignedTinyInt,
		typeUnsignedSmallInt = ADOX::adUnsignedSmallInt,
		typeUnsignedInt = ADOX::adUnsignedInt,
		typeUnsignedBigInt = ADOX::adUnsignedBigInt,
		typeSingle = ADOX::adSingle,
		typeDouble = ADOX::adDouble,
		typeCurrency = ADOX::adCurrency,
		typeDecimal = ADOX::adDecimal,
		typeNumeric = ADOX::adNumeric,
		typeBoolean = ADOX::adBoolean,
		typeDate = ADOX::adDate,
		typeDBDate = ADOX::adDBDate,
		typeDBTime = ADOX::adDBTime,
		typeDBTimeStamp = ADOX::adDBTimeStamp,
		typeBSTR = ADOX::adBSTR,
		typeVarChar = ADOX::adVarChar,
		typeLongVarChar = ADOX::adLongVarChar,
		typeWChar = ADOX::adWChar,
		typeVarWChar = ADOX::adVarWChar,
		typeLongVarWChar = ADOX::adLongVarWChar,
		typeBinary = ADOX::adBinary,
		typeVarBinary = ADOX::adVarBinary,
		typeLongVarBinary = ADOX::adLongVarBinary,
		typeChapter = ADOX::adChapter,
		typeFileTime = ADOX::adFileTime,
		typePropVariant = ADOX::adPropVariant,
		typeVarNumeric = ADOX::adVarNumeric
	};

	ADOX::_TablePtr m_pTable;

	//CADOXTable(CADOXCatalog* pCat);
	CADOXTable(CADOXCatalog* pCat, LPCTSTR lpstrTableName = _T(""));
	CADOXTable(CADOXCatalog* pCat, int nTableIndex);
	~CADOXTable();

	bool Create(LPCTSTR lpstrTableName);
	bool Open(LPCTSTR lpstrTableName);
	bool Open(long nTableIndex);
	bool AddField(LPCTSTR lpstrFieldName, enum DataType Type, int nLength = 0);
	bool AddIndex(CADOXIndex pIndex);
	bool DeleteField(LPCTSTR lpstrFieldName);
	void GetName(CString& strTableName);
//  扩展功能
	// 设置字段属性 
//	bool SetField(LPCTSTR lpstrFieldName,  enum CADOXTable::FieldAttributes flagAttribute);
//    bool SetField( int nFieldIndex,  enum CADOXTable::FieldAttributes flagAttributes);
protected:
	ADOX::_CatalogPtr m_pCatalog;

protected:
	void dump_com_error(_com_error &e);

};

//-------------------------------------------------------------------------/
//                    Class CADOXUser : 定义数据库用户User管理类
//-------------------------------------------------------------------------/
class CADOXUser
{
public:
	CADOXUser(CADOXCatalog* pCat);
	~CADOXUser();
	void GetName(CString& strName);
	bool Create(LPCTSTR lpstrUserName);
	bool Open(LPCTSTR lpstrUserName);
	bool ChangePassword(LPCTSTR lpstrOldPassword, LPCTSTR lpstrNewPassword);

public:
	ADOX::_UserPtr m_pUser;

protected:
	ADOX::_CatalogPtr m_pCatalog;

protected:
	void dump_com_error(_com_error &e);

};

//-------------------------------------------------------------------------/
//                    Class CADOXView : 定义数据库视图View管理类
//-------------------------------------------------------------------------/
class CADOXView
{
public:
	CADOXView(CADOXCatalog* pCat);
	~CADOXView();
	void GetCommand(CString& strCommand);
	void GetName(CString& strName);
	bool Open(LPCTSTR lpstrViewName);
	bool Create(CString strName, CString strCommand);

public:
	ADOX::ViewPtr m_pView;

protected:
	ADOX::_CatalogPtr m_pCatalog;

protected:
	void dump_com_error(_com_error &e);
};

//-------------------------------------------------------------------------/
//                    Class CADOXProcedure : 定义数据库存储过程Procedure管理类
//-------------------------------------------------------------------------/
class CADOXProcedure
{
public:
	CADOXProcedure(CADOXCatalog* pCat);
	~CADOXProcedure();
	void GetName(CString& strName);
	bool Open(LPCTSTR lpstrProcedureName);
	bool Create(CString strName, CString strCommand);
	void GetCommand(CString &strCommand);

public:
	ADOX::ProcedurePtr m_pProcedure;

protected:
	ADOX::_CatalogPtr m_pCatalog;

protected:
	void dump_com_error(_com_error &e);

};


//-------------------------------------------------------------------------/
//                    Class CADOXIndex : 定义数据库索引Index管理类
//-------------------------------------------------------------------------/
class CADOXIndex
{
public:
	enum DataType
	{
		typeSmallInt = ADOX::adSmallInt,
		typeInteger = ADOX::adInteger,
		typeUnsignedTinyInt = ADOX::adUnsignedTinyInt,
		typeUnsignedSmallInt = ADOX::adUnsignedSmallInt,
		typeUnsignedInt = ADOX::adUnsignedInt,
		typeUnsignedBigInt = ADOX::adUnsignedBigInt,
		typeSingle = ADOX::adSingle,
		typeDouble = ADOX::adDouble,
		typeCurrency = ADOX::adCurrency,
		typeDecimal = ADOX::adDecimal,
		typeNumeric = ADOX::adNumeric,
		typeBoolean = ADOX::adBoolean,
		typeDate = ADOX::adDate,
		typeDBDate = ADOX::adDBDate,
		typeDBTime = ADOX::adDBTime,
		typeDBTimeStamp = ADOX::adDBTimeStamp,
		typeBSTR = ADOX::adBSTR,
		typeVarChar = ADOX::adVarChar,
		typeLongVarChar = ADOX::adLongVarChar,
		typeWChar = ADOX::adWChar,
		typeVarWChar = ADOX::adVarWChar,
		typeLongVarWChar = ADOX::adLongVarWChar,
		typeBinary = ADOX::adBinary,
		typeVarBinary = ADOX::adVarBinary,
		typeLongVarBinary = ADOX::adLongVarBinary,
		typeChapter = ADOX::adChapter,
		typeFileTime = ADOX::adFileTime,
		typePropVariant = ADOX::adPropVariant,
		typeVarNumeric = ADOX::adVarNumeric
	};
	
	ADOX::_IndexPtr m_pIndex;

	CADOXIndex();

	~CADOXIndex();

	bool Create(LPCTSTR lpstrIndexName);
	bool AddField(LPCTSTR lpstrIndexName, enum DataType Type, int nLength = 0);
	void SetPrimarKey(bool bPrimary = true);
protected:
	void dump_com_error(_com_error &e);
};

//-------------------------------------------------------------------------/
//                    Class CADOXCatalog : 定义数据库目录表Catalog管理类
//-------------------------------------------------------------------------/
class CADOXCatalog
{
public:
	bool Open(LPCTSTR lpstrConnection);
	bool CreateDatabase(LPCTSTR lpstrCreate);
	bool AddTable(CADOXTable pTable);
	bool AddUser(CADOXUser pUser, LPCTSTR lpstrPassword);

	long GetProcedureCount()
		{return m_pCatalog->Procedures->GetCount();};
	long GetTableCount()
		{return m_pCatalog->Tables->GetCount();};
	long GetViewCount();
	long GetUserCount()
		{return m_pCatalog->Users->GetCount();};
	long GetGroupCount()
		{return m_pCatalog->Groups->GetCount();};

	void GetTableName(long nTableIndex, CString &strTableName);
	void GetProcedureName(long nProcedureIndex, CString &strProcedureName);
	void GetViewName(long nViewIndex, CString &strViewName);
	void GetUserName(long nUserIndex, CString &strUserName);
	void GetGroupName(long nGroupIndex, CString &strGroupName);
	bool DeleteTable(LPCTSTR lpstrTableName);
	bool DeleteTable(long nTableIndex);
	bool DeleteProcedure(long nProcedureIndex);
	bool DeleteProcedure(LPCTSTR lpstrProcedureName);
	bool DeleteView(LPCTSTR lpstrViewName);
	bool DeleteView(long nViewIndex);
	bool DeleteGroup(LPCTSTR lpstrGroupName);
	bool DeleteGroup(long nGroupIndex);
	bool DeleteUser(LPCTSTR lpstrUserName);
	bool DeleteUser(long nViewIndex);

	ADOX::_CatalogPtr m_pCatalog;	
	ADODB::_ConnectionPtr m_pConn;

	CADOXCatalog();

	~CADOXCatalog()
	{
		m_pCatalog.Release();
		m_pCatalog = NULL;
		if (m_pConn)
		{
			m_pConn.Release();
			m_pConn=NULL;
		}
		::CoUninitialize();
	}



protected:
	void dump_com_error(_com_error &e);
	
};

#endif// #ifndef _ADOX_H_INCLUDED_