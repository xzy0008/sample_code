#include <vgStableHeaders.h>
#include <vgDatabase/vgdDatabaseManager.h>
#include <vgDatabase/vgdProfileManager.h>
#include <vgDatabase/tinyxml.h>
#include <vgKernel/vgkRenderer.h>

using namespace vgDatabase;


int DatabaseManager_GetDataBaseType()
{
	return DatabaseManager::getSingleton().GetDataBaseType();
}

bool DatabaseManager_CreateConnector(int databaseType)
{
	return DatabaseManager::getSingleton().CreateConnector(databaseType);
}

 BasedConnectorH DatabaseManager_GetConnectorPtr()
 {
 	return (BasedConnectorH)DatabaseManager::getSingleton().GetConnectorPtr();
 }
 
bool DatabaseManager_OpenDatabase()
{
	return DatabaseManager::getSingleton().OpenDatabase();
}

bool DatabaseManager_CloseDatabase()
{
	return DatabaseManager::getSingleton().CloseDatabase();
}

bool DatabaseManager_IsOpen()
{
	return DatabaseManager::getSingleton().IsOpen();
}

bool DatabaseManager_GetStatus()
{
	return DatabaseManager::getSingleton().GetStatus();
}

void DatabaseManager_SetStatus(bool status)
{
	return DatabaseManager::getSingleton().SetStatus(status);
}

bool DatabaseManager_DeleteTable(String tablename)
{
	return DatabaseManager::getSingleton().DeleteTable(tablename);
}

void DatabaseManager_reset()
{
	return DatabaseManager::getSingleton().reset();
}

bool ProfileManager_LoadFromFile(String filepath)
{
	return ProfileManager::getSingleton().LoadFromFile(filepath);
}

bool ProfileManager_IsProfileLoaded()
{
	return ProfileManager::getSingleton().IsProfileLoaded();
}

String ProfileManager_CreateQuery(const String& profileName, bool isSingleQuery /* = true */)
{
	return ProfileManager::getSingleton().CreateQuery(profileName,isSingleQuery);
}

String ProfileManager_CreateQueryWithWhere(String profileName, bool isSingleQuery /* = true */)
{
	return ProfileManager::getSingleton().CreateQueryWithWhere(profileName, isSingleQuery);
}

QueryProfileH ProfileManager_GetProfile(String profileName)
{
	return (QueryProfileH)ProfileManager::getSingleton().GetProfile(profileName);
}
 
long ProfileManager_GetProfileIdByName(String profileName)
{
	return ProfileManager::getSingleton().GetProfileIdByName(profileName);
}

String ProfileManager_GetProfileNameByIndex(int index)
{
	return ProfileManager::getSingleton().GetProfileNameByIndex(index);
}

int ProfileManager_GetProfileListSize()
{
	return ProfileManager::getSingleton().GetProfileListSize();
}

bool ProfileManager_InitRendererProfile(RendererH pRenderer)
{
	vgKernel::Renderer* renderer = (vgKernel::Renderer*)pRenderer;
	return ProfileManager::getSingleton().InitRendererProfile(renderer);
}

long ProfileManager_SaveRendererProfile(String filepath)
{
	return ProfileManager::getSingleton().SaveRendererProfile(filepath);
}

long ProfileManager_loadRenderProfile(String filepath)
{
	return ProfileManager::getSingleton().loadRenderProfile(filepath);
}

void ProfileManager_SetCurProfile(CString profileName)
{
	return ProfileManager::getSingleton().SetCurProfile(profileName);
}

TiXmlNodeH ProfileManager_AppendXmlProfile(const String &fileName, const String &profileName)
{
	return (TiXmlNodeH)ProfileManager::getSingleton().AppendXmlProfile(fileName, profileName);
}

void ProfileManager_InsertTable(const TiXmlNodeH profileNode, const String &tableName)
{
	TiXmlNode *para = (TiXmlNode*)profileNode;
	return ProfileManager::getSingleton().InsertTable(para, tableName);
}

void ProfileManager_InsertFeild(const TiXmlNodeH profileNode, const String &feildName, const String &aliasName)
{
	TiXmlNode *para = (TiXmlNode*)profileNode;

	return ProfileManager::getSingleton().InsertFeild(para, feildName, aliasName);
}

void ProfileManager_InsertConnect(const TiXmlNodeH profileNode, const String &connectName)
{	
	TiXmlNode *para = (TiXmlNode*)profileNode;

	return ProfileManager::getSingleton().InsertConnect(para, connectName);
}

void ProfileManager_InsertPrimaryId(const TiXmlNodeH profileNode, const String &primaryIdName)
{
	TiXmlNode *para = (TiXmlNode*)profileNode;

	return ProfileManager::getSingleton().InsertPrimaryId(para, primaryIdName);
}

void ProfileManager_SaveXmlProfile()
{
	return ProfileManager::getSingleton().SaveXmlProfile();
}

void ProfileManager_IterateNode(String &profileName)
{
	return ProfileManager::getSingleton().IterateNode(profileName);
}


