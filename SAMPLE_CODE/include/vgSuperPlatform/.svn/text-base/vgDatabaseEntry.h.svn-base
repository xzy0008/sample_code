#pragma once


#include <vgKernel/vgkForward.h>
#include <vgKernel/vgkRenderer.h>
#include <vgKernel/vgkRendererObserver.h>
#include "vgEntryType.h"
#include <vgSuperPlatform/vgDatabasePage.h>
#include <vgDatabase/vgdDatabaseManager.h>
#include <vgDatabase/vgdProfileManager.h>
#include <vgGroupBasedEntry.h>
#include <vgKernel/vgkRendererData.h>

/**
* vgDatabaseEntry 
* 重新实现其中的虚函数
*
* @see		   vgBasedEntry
*
* @author      ZSC
* @version     VRGIS SuperPlatform SP
* @since       VRGIS 2.0+
*/

class vgDatabaseEntry : public vgGroupBasedEntry
{
public:
	vgDatabaseEntry( vgEntryType type ,vgKernel::Renderer* renderer );
	
	virtual String getSearchName()
	{
		return GetName();
	}//YXDB

/*	vgDatabaseEntry()*/
	// 子类在AddSingleTabPage中增加profile选择下拉框 参考vgMeshEntry.cpp line:182
	// 子类覆写AddSingleTabPage后，应在函数的最后调用 vgDatabaseEntry::AddSingleTabPage 实现数据库Tab的显示和更新
	virtual void AddSingleTabPage();

	virtual void OnDatabasePropertyChanged(string paraName, _variant_t dataValue);
	 
	virtual void OnSinglePropertyChanged(string paramName);

	virtual void OnGroupPropertyChanged(string paramName);
protected:
	// 数据库相关函数和数据成员
	void initDatabaseParam();

	static vgDatabasePage s_databasePage; 

	static vector<DatabaseProperties> s_databaseParam; 

	static string s_groupProfileName;

	string m_profileName;

	string m_queryString;
};