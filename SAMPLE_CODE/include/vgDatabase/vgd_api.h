/*! \file vglo_api.h
\brief 数据库 模块接口函数
*/
#ifdef __cplusplus
extern "C" {
#endif


	typedef void* CADODatabaseH;

	/** \fn int DatabaseManager_GetDataBaseType()
	\brief 得到当前数据库类型：VG_DATABASE_ACCESS为 Access，VG_DATABASE_ORACLE为 Oracle
	*/
	typedef int (*pfnDatabaseManager_GetDataBaseType)();
	extern VGD_EXPORT int DatabaseManager_GetDataBaseType();
	
	/** \fn bool DatabaseManager_CreateConnector(int databaseType)
	\brief 创建数据库：VG_DATABASE_ACCESS为 Access，VG_DATABASE_ORACLE为 Oracle
	\param databaseType 数据库类型
	*/
	typedef bool (*pfnDatabaseManager_CreateConnector)(int databaseType);
	extern VGD_EXPORT bool DatabaseManager_CreateConnector(int databaseType);
	
	/** \fn BasedConnectorH DatabaseManager_GetConnectorPtr()
	\brief 得到数据看指针
	*/
	typedef void* BasedConnectorH;
	typedef BasedConnectorH (*pfnDatabaseManager_GetConnectorPtr)();
	extern VGD_EXPORT BasedConnectorH DatabaseManager_GetConnectorPtr();

	/** \fn bool DatabaseManager_OpenDatabase()
	\brief 打开数据库
	*/
	typedef bool (*pfnDatabaseManager_OpenDatabase)();
	extern VGD_EXPORT bool DatabaseManager_OpenDatabase();

	/** \fn bool DatabaseManager_CloseDatabase()
	\brief 关闭数据库
	*/
	typedef bool (*pfnDatabaseManager_CloseDatabase)();
	extern VGD_EXPORT bool DatabaseManager_CloseDatabase();

	/** \fn bool DatabaseManager_IsOpen()
	\brief 判断数据库状态
	*/
	typedef bool (*pfnDatabaseManager_IsOpen)();
	extern VGD_EXPORT bool DatabaseManager_IsOpen();
	
	/** \fn bool DatabaseManager_GetStatus()
	\brief 得到数据库状态
	*/
	typedef bool (*pfnDatabaseManager_GetStatus)();
	extern VGD_EXPORT bool DatabaseManager_GetStatus();

	/** \fn void DatabaseManager_SetStatus(bool status)
	\brief 设置数据库状态
	\param status 数据库状态 TRUE为开启，FALSE为关闭
	*/
	typedef void (*pfnDatabaseManager_SetStatus)(bool status);
	extern VGD_EXPORT void DatabaseManager_SetStatus(bool status);

	/** \fn bool DatabaseManager_DeleteTable(String tablename)
	\brief 删除数据库中已有表
	\param tablename 表名
	*/
	typedef bool (*pfnDatabaseManager_DeleteTable)(String tablename);
	extern VGD_EXPORT bool DatabaseManager_DeleteTable(String tablename);

	/** \fn void DatabaseManager_reset()
	\brief 重设数据库
	*/
	typedef void (*pfnDatabaseManager_reset)();
	extern VGD_EXPORT void DatabaseManager_reset();


	/** \fn bool ProfileManager_LoadFromFile(String filepath)
	\brief 加载数据库profile
	\param filepath 路径
	*/
	typedef bool (*pfnProfileManager_LoadFromFile)(String filepath);
	extern VGD_EXPORT bool ProfileManager_LoadFromFile(String filepath);
	/** \fn bool ProfileManager_IsProfileLoaded()
	\brief 判断profile加载状态
	*/
	typedef bool (*pfnProfileManager_IsProfileLoaded)();
	extern VGD_EXPORT bool ProfileManager_IsProfileLoaded();
	/** \fn String ProfileManager_CreateQuery(const String& profileName, bool isSingleQuery)
	\brief 生成查询语句
	\param isSingleQuery 是否是单查询 
	*/
	typedef String (*pfnProfileManager_CreateQuery)(const String& profileName, bool isSingleQuery);
	extern VGD_EXPORT String ProfileManager_CreateQuery(const String& profileName, bool isSingleQuery);
	
	/** \fn String ProfileManager_CreateQueryWithWhere(String profileName, bool isSingleQuery)
	\brief 生成查询语句，带where
	\param isSingleQuery 是否是单查询 
	*/
	typedef String (*pfnProfileManager_CreateQueryWithWhere)(String profileName, bool isSingleQuery);
	extern VGD_EXPORT String ProfileManager_CreateQueryWithWhere(String profileName, bool isSingleQuery);

	/** \fn QueryProfileH ProfileManager_GetProfile(String profileName)
	\brief 得到当前profile
	\param profileName profile名称
	*/
 	typedef void* QueryProfileH;
  	typedef QueryProfileH (*pfnProfileManager_GetProfile)(String profileName);
  	extern VGD_EXPORT QueryProfileH ProfileManager_GetProfile(String profileName);

	/** \fn long ProfileManager_GetProfileIdByName(String profileName) 
	\brief 通过名称得到profile
	\param profileName profile名称
	*/
	typedef long (*pfnProfileManager_GetProfileIdByName)(String profileName);
	extern VGD_EXPORT long ProfileManager_GetProfileIdByName(String profileName);

	/** \fn String ProfileManager_GetProfileNameByIndex(int index)
	\brief 通过索引得到profile
	\param index 索引
	*/
	typedef String (*pfnProfileManager_GetProfileNameByIndex)(int index);
	extern VGD_EXPORT String ProfileManager_GetProfileNameByIndex(int index);

	/** \fn int ProfileManager_GetProfileListSize()
	\brief 得到profile列表数
	*/
	typedef int (*pfnProfileManager_GetProfileListSize)();
	extern VGD_EXPORT int ProfileManager_GetProfileListSize();

	/** \fn bool ProfileManager_InitRendererProfile(RendererH pRenderer)
	\brief 初始化渲染profile
	\param pRenderer 渲染模型指针
	*/
	typedef void* RendererH;
	typedef bool (*pfnProfileManager_InitRendererProfile)(RendererH pRenderer);
	extern VGD_EXPORT bool ProfileManager_InitRendererProfile(RendererH pRenderer);

	/** \fn long ProfileManager_SaveRendererProfile(String filepath)
	\brief 保存渲染profile
	\param filepath 路径
	*/
	typedef long (*pfnProfileManager_SaveRendererProfile)(String filepath);
	extern VGD_EXPORT long ProfileManager_SaveRendererProfile(String filepath);

	/** \fn long ProfileManager_loadRenderProfile(String filepath)
	\brief 加载渲染profile
	\param filepath 路径
	*/
	typedef long (*pfnProfileManager_loadRenderProfile)(String filepath);
	extern VGD_EXPORT long ProfileManager_loadRenderProfile(String filepath);

	/** \fn void ProfileManager_SetCurProfile(CString profileName)
	\brief 设置当前渲染profile
	\param profileName profile文件名
	*/
	typedef void (*pfnProfileManager_SetCurProfile)(CString profileName);
	extern VGD_EXPORT void ProfileManager_SetCurProfile(CString profileName);

	/** \fn TiXmlNodeH ProfileManager_AppendXmlProfile(const String &fileName, const String &profileName)
	\brief 附加信息至profile
	\param fileName profile文件名
	*/
	typedef void* TiXmlNodeH;
	typedef TiXmlNodeH (*pfnProfileManager_AppendXmlProfile)(const String &fileName, const String &profileName);
	extern VGD_EXPORT TiXmlNodeH ProfileManager_AppendXmlProfile(const String &fileName, const String &profileName);

	/** \fn void ProfileManager_InsertTable(const TiXmlNodeH profileNode, const String &tableName)
	\brief 插入表格至profile
	\param profileNode tinyxml节点
	*/
	typedef void (*pfnProfileManager_InsertTable)(const TiXmlNodeH profileNode, const String &tableName);
	extern VGD_EXPORT void ProfileManager_InsertTable(const TiXmlNodeH profileNode, const String &tableName);

	/** \fn void ProfileManager_InsertFeild(const TiXmlNodeH profileNode, const String &feildName, const String &aliasName)
	\brief 插入列至profile
	\param profileNode tinyxml节点
	*/
	typedef void (*pfnProfileManager_InsertFeild)(const TiXmlNodeH profileNode, const String &feildName, const String &aliasName);
	extern VGD_EXPORT void ProfileManager_InsertFeild(const TiXmlNodeH profileNode, const String &feildName, const String &aliasName);

	/** \fn void ProfileManager_InsertConnect(const TiXmlNodeH profileNode, const String &connectName)
	\brief 插入关联至profile
	\param profileNode tinyxml节点
	*/
	typedef void (*pfnProfileManager_InsertConnect)(const TiXmlNodeH profileNode, const String &connectName);
	extern VGD_EXPORT void ProfileManager_InsertConnect(const TiXmlNodeH profileNode, const String &connectName);

	/** \fn void ProfileManager_InsertPrimaryId(const TiXmlNodeH profileNode, const String &primaryIdName)
	\brief 插入主键至profile
	\param profileNode tinyxml节点
	*/
	typedef void (*pfnProfileManager_InsertPrimaryId)(const TiXmlNodeH profileNode, const String &primaryIdName);
	extern VGD_EXPORT void ProfileManager_InsertPrimaryId(const TiXmlNodeH profileNode, const String &primaryIdName);

	/** \fn void ProfileManager_SaveXmlProfile()
	\brief 保存profile
	*/
	typedef void (*pfnProfileManager_SaveXmlProfile)();
	extern VGD_EXPORT void ProfileManager_SaveXmlProfile();

	/** \fn void ProfileManager_IterateNode(String &profileName)
	\brief 遍历profile内节点
	\param profileName profile文件名
	*/
	typedef void (*pfnProfileManager_IterateNode)(String &profileName);
	extern VGD_EXPORT void ProfileManager_IterateNode(String &profileName);

	


#ifdef __cplusplus
}
#endif


