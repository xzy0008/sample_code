// PropertiesViewBar.h: interface for the CPropertiesViewBar class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PROPERTIESVIEWBAR_H__91E4A4A8_1AD0_450E_841C_409767044A55__INCLUDED_)
#define AFX_PROPERTIESVIEWBAR_H__91E4A4A8_1AD0_450E_841C_409767044A55__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <vgUIController/vgUIControlDefinition.h>
#include <string>

using std::string;


/**
* vgPropertiesViewBar 在vgUIController的控制下管理属性视图
*
* @see		   vgUIController	   
*
* @author      ZSC
* @version     VRGIS FrameWork RC
* @since       VRGIS 1.0
*/
/**
* 不再提供默认实现 至提供接口 所有实现由应用程序界面重写
*
* @see		   vgUIController	   
*
* @author      ZSC
* @version     VRGIS FrameWork RC
* @since       VRGIS 2.5
*/
class VGUI_EXPORT vgPropertiesViewBar  
{
// Construction
public:
	vgPropertiesViewBar();

	virtual ~vgPropertiesViewBar();

	virtual void AdjustLayout () {}

	virtual CBCGPTabWnd* GetTabControl() { return NULL; }

	virtual void AddTab(string name, CWnd *wnd) {}

	virtual void RemoveAllTab(){}
	
	virtual void ShowControlBar(BOOL bShow, BOOL bDelay, BOOL bActivate/* = TRUE*/)
	{
	}

	virtual BOOL IsVisible()
	{
		return FALSE;
	}
};


#endif // !defined(AFX_PROPERTIESVIEWBAR_H__91E4A4A8_1AD0_450E_841C_409767044A55__INCLUDED_)
