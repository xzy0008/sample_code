#pragma once

#include <string>
using std::string;

/**
* vgBasedNode 是所有node的父类，自定义的Node需
* 重新实现其中的虚函数
*
* @see		   vgTestNode1
*
* @author      ZSC
* @version     VRGIS FrameWork RC
* @since       VRGIS 1.0+
*/

class vgBasedNode
{
public:
	vgBasedNode(string name);

	virtual ~vgBasedNode(void);
	
	virtual string GetNameID() { return nameId; };
	
	virtual void AddNodeTabs() = 0;

	inline virtual void Render() = 0;

	virtual int GetUnSelectedImage() = 0;
	
	virtual int GetSelectedImage() = 0;

	// read only
	HTREEITEM hTreeItem;

protected:
	string nameId;
};
