#pragma once

#include <vgKernel/vgkForward.h>
#include <vgKernel/vgkRenderer.h>
#include <vgKernel/vgkRendererObserver.h>
#include <vgEntry/vgEntryType.h>


#include <vgUIController/vgPropertyPage.h>

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

using namespace std;

class  VGUI_EXPORT vgGroupBasedEntry : public vgBaseEntry
{
public:
	vgGroupBasedEntry( vgKernel::Renderer* renderer ) : vgBaseEntry(renderer) {}
	
	// 子类不需要覆写此函数 
	// 针对Group的响应覆写AddGroupTabPage
	// 针对Single的响应覆写AddSingleTabPage
	virtual void AddNodeTabs();

	// 子类不需要覆写此函数 
	// 针对Group的响应覆写OnGroupPropertyChanged
	// 针对Single的响应覆写OnSinglePropertyChanged
	virtual void OnPropertyChanged(string paramName);

	//add by KingHJ 2010-05-04
	virtual void showAttriList() {};

protected:
	virtual void AddGroupTabPage() = 0;

	virtual void AddSingleTabPage() = 0;

	virtual void OnSinglePropertyChanged(string paramName) = 0;

	virtual void OnGroupPropertyChanged(string paramName) = 0;

	static vector<vgGroupBasedEntry*> s_group_list;

	// group 属性
	static vector<PropertiesParam> s_GroupParamArray;
	
	// 单个Node属性
	static vector<PropertiesParam> s_ParamArray;
};