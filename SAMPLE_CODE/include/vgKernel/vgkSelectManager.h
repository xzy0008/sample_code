

#ifndef __VGKSELECTMANAGER222_H__
#define __VGKSELECTMANAGER222_H__

#include <vgKernel/vgkForward.h>
#include <vgKernel/vgkSingleton.h>

#include <vgKernel/vgkInputCodeDef.h>
#include <vgKernel/vgkInputSystem.h>
#include <vgKernel/vgkRenderer.h>
#include <vgKernel/vgkAxis.h>
#include <vgKernel/vgkRendererManager.h>
#include <vgKernel/vgkRendererHolder.h>
#include <vgkernel/vgkOperation.h>
#include <vgKernel/vgkPolygon2D.h>
#include <vgKernel/vgkRenderCommand.h>

#include <vgKernel/vgkPropertyManager.h>
#include <vgKernel/vgkPropertyObserver.h>
#include <vgKernel/vgkObserver.h>
#include <vgkernel/vgkVec3.h>

namespace vgKernel { 

	/**
		@date 	2008/08/21  14:00	
		@author  ZSC
	
		@brief 	
	
		@see    
	*/

	//////////////////////////////////////////////////////////////////////////
	// 选区样式 
	enum SelectRegionShape  
	{
		SRS_Rect,    /*矩形*/
		SRS_Polygon  /*多边形*/
	};

	// 选集模式
	enum SelectRegionMode
	{
		SRM_New,             /*新建选集*/
		SRM_Add,             /*增加选集*/
		SRM_Subtract,        /*减少选集*/
		SRM_Intersection,    /*相交选集*/
		SRM_Reverse          /*反向选取*/
	};

	struct SelectMode
	{
		SelectRegionShape  selectRegionShape;
		SelectRegionMode   selectRegionMode;
		bool               isInclude;
	};
	//////////////////////////////////////////////////////////////////////////


	typedef std::vector< Vec3 > Vec3Vector;

	class  VGK_EXPORT SelectManager : 
		public Singleton<SelectManager>, public InputHandler,
		public PropertyObserver,
		public ObserverTarget
	{
	friend class Singleton<SelectManager>;

	private:
		SelectManager();
	public:
		virtual~SelectManager();
	
		virtual void onEvent(unsigned int eventId, void *param);

		void addSelection( Renderer* renderer, bool reMerge = true);

		void clearSelection();

		void renderSelected();

		// 将其修改为传参，转换到顶视图时可共用
		void mergeBox( const RendererQueue& renderQuene );


		
		void updateSelectedItem();

		void updateBox();

		RendererQueue& getSelectedItems()
		{
			return m_bufferItems;
		}

		vgKernel::Box getSelectedBox()
		{
			return m_mergeBox;
		}
	
		vgKernel::Vec3 getSelectedCenter(bool update_box = false)
		{
			if (update_box)
			{
				updateBox();
			}

			return m_selectedCenter;
		}

		void translateGroup(const float& x, const float& y, const float& z);

		bool deleteSelectedRenderers( const bool& alert = true );

		// 内部使用
		void SetViewSize(int cx, int cy);
		void OnMouseMove(UINT nFlags, CPoint position);
		void OnLButtonDown(UINT nFlags, CPoint position);
		void OnLButtonUp(UINT nFlags, CPoint position);
		void OnLButtonDbClick(UINT nFlags, CPoint position);
		void OnKeyDown(int keyCode);

		void getViewSize( int& width , int& height )
		{
			width =	m_window_width;
			height = m_window_height;
		}

		bool getEnableRenderSelected() const { return _enableRenderSelected; }
		void setEnableRenderSelected( const bool& val ) { _enableRenderSelected = val; }


		void reset(){ clearSelection(); }

		Renderer* getSelectedRendererByType( RendererType type );

		// 双击鼠标左键时选择 
		void SelectDbClickObject( const CPoint &position );   
 
		// 矩形选择( 渲染窗口二维平面 )
		void SelectRectObject();  
		
		// 多边形选择( 三维坐标投影 )     
		void SelectPolygonObject( const Vec3Vector* pointsVec );
		
		// 全部选择
		void selectAllObject(); 

		// 设置选定模型的包围盒渲染状态， 切块保存时不渲染包围盒
		void setEnableRenderBoundingBox( bool bState )
		{
			_enableRenderBoundingBox = bState;
		}

		void colorbleSelectedRender( const RendererQueue& renderQueue );
		void uncolorbleSelectedRender( const RendererQueue& renderQueue );

	protected:

		void fireOnSelectChanged();

		bool initialise();
		bool shutdown();

		
		RenderCommand *m_pSelectRenderCmd;

	private:

		vgKernel::RendererPackage* _culledRenderers;

		RendererQueue		m_bufferItems;

		vgKernel::Box				    m_mergeBox;
		
		vgKernel::vgAxis				m_axis;
		
		// 包围盒初始的中点，旋转时保持不变
		vgKernel::Vec3					m_selectedCenter;
		
		vgKernel::Vec3					m_lastTran;

		bool	m_lButtonDown;

		float	m_start_x;
		float	m_start_y;
		float	m_drag_x;
		float	m_drag_y;
		float	m_end_x;
		float	m_end_y;

		int		m_window_width;
		int		m_window_height;

		// undo redo ====================================================

		std::deque<vgkOperator *> undodeque;

		std::deque<vgkOperator *> redodeque;

		vgKernel::Vec3 m_sumtrans;

		vgKernel::Vec3 m_sumrot;

		vgKernel::Vec3 m_sumscale;

		vgKernel::Vec3 m_opcenter;

		bool _hasoperator;

		bool m_bIsMenuOperate; //是否菜单操作  add by ZhouZY 2009-11-11 10:03

		// 是否开启渲染选中物体
		bool _enableRenderSelected;

		// 是否渲染选中物体的包围盒
		bool _enableRenderBoundingBox;

		
	public:
		void Undo();

		void Redo();

		void PushOperatorDeque();
		void setsumtrans( Vec3 trans);
		//void setsumrot( Vec3 rots );
		//void setsumscale( Vec3 scale );

		// add by lss
		//void selectByPolygon(Polygon2D&	polygon2D);
		void updateUI();
		
		//add by ZhouZY 2009-11-2 22:04
		void setEditMode( vgKernel::EditMode editMode )
		{
			m_axis.SetEditMode( editMode );
		}
		vgKernel::EditMode getEditMode()
		{
			return m_axis.GetEditMode();
		}

	private:
		void IniOperate();

	//***********************************************************
		// 2010.2.3软件评比临时使用，以后修改
	public:
		void renderPolygon();
		void drawLine();

		void addPolygonPt( Vec3 pt )
		{
			m_polygonVec.push_back( pt );
		}

		void setPolygonMode( bool bMode )
		{
			m_bPolygonMode = bMode;
		}
		
		void setPolygonPt( Vec3 pt )
		{
			m_polygonPt = pt;
		}

		void clearPolygonVec()
		{
			m_polygonVec.clear();
		}

	private:

		Vec3Vector m_polygonVec;
		Vec3       m_polygonPt;
		bool       m_bPolygonMode;

		////====选择方式整理 ZhouZY 2010-4-30 17:20
	public:

		// 设置默认的选择模式
		void setDefaultSelectMode();

		// 设置选择模式
		SelectMode* getSelectMode() { return m_pSelectMode; }

		// 获取选择模式
		void setSelectMode( SelectMode* pMode ){ m_pSelectMode = pMode; }

		// 是否渲染选区
		void setEnableDrawSelRegion( bool bEnable ){ m_bDrawSelRegion = bEnable; } 

		RendererQueue& getCurrentSelectedItems() { return m_currentSelectedItems; }

	private:

		//渲染选区
		void renderSelectRegion();  

		//合并选择项 
		void merageSelectedItems();

		bool                m_bSelectStop;     // 是否停止选择
		bool                m_bDrawSelRegion;  // 是否渲染选区
		Vec3                m_clickPt;         // 鼠标点击点
		Vec3Vector          m_selectRegionPts; // 多边形选区顶点
		SelectMode*         m_pSelectMode;     // 选择模式
		RendererQueue		m_lastSelectedItems;    // 上一次选择项 
		RendererQueue		m_currentSelectedItems; // 当前选择项

	//***********************************************************

	};
	
	class SelectRenderCmd : public RenderCommand
	{
	public:
		SelectRenderCmd() : RenderCommand(VG_RP_SELECT_RENDER) {}

		inline virtual bool render()
		{
			vgKernel::SelectManager::getSingleton().renderPolygon();

		 	// 渲染被选中的节点
		 	vgKernel::SelectManager::getSingleton().renderSelected();
		 	
		 	// 响应Input事件
		 	vgKernel::SelectManager::getSingleton().updateSelectedItem();
			
			return true;
		}
	};
}// end of namespace vgKernel
	


#endif // end of __VGKSELECTMANAGER_H__
