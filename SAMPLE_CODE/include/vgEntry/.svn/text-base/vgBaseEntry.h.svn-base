#pragma once

#include <vgKernel/vgkForward.h>
#include <vgKernel/vgkRenderer.h>
#include <vgKernel/vgkRendererObserver.h>
#include <vgEntry/vgEntryType.h>

#include <vgUIController/vguiControlDefinition.h>

#include <vgKernel/vgkAbstractEntry.h>
/**
* vgBaseEntry 是所有node的父类，自定义的Node需
* 重新实现其中的虚函数
*
* @see		   vgTestNode1
*
* @author      ZSC
* @version     VRGIS FrameWork RC
* @since       VRGIS 1.0+
*/
  

class  VGUI_EXPORT vgBaseEntry : 
	public vgKernel::RendererObserver,
	public vgKernel::AbstractEntry
{
public:
	vgBaseEntry( vgKernel::Renderer* renderer )
	{
		m_Renderer = renderer;

		if ( renderer != NULL )
		{
			renderer->registerObserver( this );
		}
	}

	virtual ~vgBaseEntry(void)
	{

	}
	
	virtual String GetName()
	{
		assert( m_Renderer != NULL );
		return m_Renderer->getName();
	}
	

	virtual bool onDelete();


	virtual void AddNodeTabs() = 0;

	virtual int GetUnSelectedImage() = 0;
	
	virtual int GetSelectedImage() = 0;

	// Node 更改时通知Object
	virtual void OnPropertyChanged(String paramName) = 0;

	virtual void OnDatabasePropertyChanged(String paraName, _variant_t dataValue) {}

	//vgEntryType  GetType() { return m_typeFlag; }


	//------------------------------------------
	// 是否可以被del按键直接删除.
	// 对于像rootentry一类的entry来讲, 返回
	// true是合适的
	//  参考CEditTreeCtrlEx::DeleteSelectedNode()
	//------------------------------------------
	virtual bool canBeDeletedDirectly()
	{
		return false;
	}

	//------------------------------------------
	// 设定当按下del键时
	// entry自己调用的删除函数.
	// 当返回为true时, 表示成功删除.
	//------------------------------------------
	virtual bool onUserDefinedDeletion()
	{
		return true;
	}

	vgKernel::Renderer* getRender()
	{
		return m_Renderer;
	}

	virtual CMenu* GetContextMenu() 
	{
		return NULL;
	}

public:

	HTREEITEM hTreeItem;

protected:

	//vgEntryType    m_typeFlag;

	vgKernel::Renderer* m_Renderer;
};


// Observer 的定义移至vgKernel
