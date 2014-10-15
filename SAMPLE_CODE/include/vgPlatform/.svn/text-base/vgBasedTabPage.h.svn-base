#pragma once

#include <string>
#include "vgBasedNode.h"

using std::string;

/**
* vgBasedTabPage 是所有自定义属性页的父类，通过
* ConnectNode函数与某个特定节点的数据进行绑定来
* 实现数据显示和更新
*
* @see		   vgTestNode1
*
* @author      ZSC
* @version     VRGIS FrameWork RC
* @since       VRGIS 1.0+
*/

class vgBasedTabPage
{
public:
	vgBasedTabPage(void);

	virtual ~vgBasedTabPage(void);

	virtual string GetTitle() = 0;

	virtual CWnd* GetWnd() = 0;
	
	virtual void ConnectNode(vgBasedNode* node) = 0;

	// virtual int GetIconIndex() = 0;
protected:
	string m_sTitle;
	int m_nIconIndex;
};
