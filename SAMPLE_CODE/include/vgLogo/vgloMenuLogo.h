

#ifndef __VGMENULOGO_H__
#define __VGMENULOGO_H__

#include <vgLogo/vgloDefinition.h>
#include <vgLogo/vgloLogoHandle.h>
#include <vgLogo/vgloMenuItem.h>

#include <vgKernel/vgkInputSystem.h>
namespace vgLogo {  
	

	/**
	@date 	2009/11/27  9:53	
	@author  ZhouZY

	@brief 	

	@see    
	*/
	

	class VGL_EXPORT  MenuLogo : public LogoHandle, public vgKernel::InputHandler
	{

	public:

		MenuLogo();

		virtual ~MenuLogo();

	public:

		//从父类LogoHandle继承而来
		virtual void reset();
		virtual void render();

		//InputHandler 继承而来
		virtual void OnLButtonDown(UINT nFlags, CPoint position);
		virtual void OnMouseMove(UINT nFlags, CPoint position);

		//自己所特有
		void initMenuLogoLD();   //初始化左下角Logo
		void initMenuLogoRD();   //初始化右下角Logo


		//设置Items的状态--(包括自身的渲染状态及子项渲染状态)
		void setItemState( MenuItem* pMenuItem, bool bUpLevel = false );      

		vector<MenuItem*>* getCurrentItems();

		void clearCurrentItemVec();     

		void findCurrentItems( MenuItem* pMenuItem );    //查找当前渲染的Items

		MenuItem* getRootMenuItemPtr()
		{
			return &m_rootMenu;
		}

	private:

		//类内部使用，非公开的接口

		//重新计算Item的宽度，高度及中心坐标
		//以下两者递归调用
		void recalculate( MenuItem* pRootMenuItem );   
		void recalculateData( MenuItem* pMenuItem );

		void uninitMenuLogo( MenuItem* pRootMenuItem );  //卸载贴图数据

		//通过传入的父节点及当前子节点设置该父节点下子节点的渲染状态
		void setSubItemsState( MenuItem* pParentItem, MenuItem* pSubItem );

		void render( MenuItem* pRootMenuItem );

		void setVaryType( VaryType varyType )
		{
			m_varyType = varyType;
		}
		
#if 0   //扩展为当鼠标指向时Logo变大效果
		void largenLogo( MenuItem* pMenuItem, vector<MenuItem*>* pMenuItemVec );
		
		void reInitAllItem( MenuItem* pMenuItem );
#endif

	private:
 
		MenuItem            m_rootMenu;        //根菜单Logo

		VaryType            m_varyType;        //标记视口变化

		float               m_dWidth;          //默认平台渲染窗口宽度
		float               m_dHeight;         //默认平台渲染窗口高度

		vector<MenuItem*>   m_currentItemVec;  //当前渲染的Items

		//每个MenuLogo对象都有以下两个数据
		int                 m_lastViewWidth;
		int                 m_lastViewHeight;
		
	};

}

#endif