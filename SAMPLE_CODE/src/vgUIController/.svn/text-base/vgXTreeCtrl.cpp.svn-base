
//////////////////////////////////////////////////////////// CXTreeCtrl
#include <vgStableHeaders.h>
//#include "DragTree2.h"
#include "vgUIcontroller/vgXTreeCtrl.h"

//#ifdef _DEBUG
//#define new DEBUG_NEW

//#undef THIS_FILE
//static char THIS_FILE[] = __FILE__;
//#endif

#define DRAG_DELAY 60

vgXTreeCtrl::vgXTreeCtrl()
{
	m_bDragging = false;//开始不是处在拖拽状态
} 
vgXTreeCtrl::~vgXTreeCtrl()
{
}

BEGIN_MESSAGE_MAP(vgXTreeCtrl, CTreeCtrl)
//{{AFX_MSG_MAP(CXTreeCtrl)
ON_NOTIFY_REFLECT(TVN_BEGINDRAG, OnBegindrag)
ON_WM_MOUSEMOVE()
ON_WM_LBUTTONUP()
ON_WM_LBUTTONDOWN()
ON_WM_TIMER()
//}}AFX_MSG_MAP

END_MESSAGE_MAP()

void vgXTreeCtrl::OnBegindrag(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	*pResult = 0;
	//如果是无意拖曳，则放弃操作
	if( (GetTickCount() - m_dwDragStart) < DRAG_DELAY )   //DRAG_DELAY在前面已定义，数值为60
		return;
	m_hItemDragS = pNMTreeView->itemNew.hItem;////////// HTREEITEM m_hItemDragS; 被拖动的标签

	m_hItemDragD = NULL;                      //////HTREEITEM m_hItemDragD; 接受拖动的标签
	//得到用于拖动时显示的图象列表
	m_pDragImage = CreateDragImage( m_hItemDragS );// CImageList* m_pDragImage; 拖动时显示的图象列表
	if( !m_pDragImage )
		return;
	m_bDragging = true;                             // BOOL m_bDragging; 标识是否正在拖动过程中
	m_pDragImage->BeginDrag ( 0,CPoint(8,8) );
	CPoint pt = pNMTreeView->ptDrag;
	ClientToScreen( &pt );
	m_pDragImage->DragEnter ( this,pt ); //"this"将拖曳动作限制在该窗口
	//然后调用CImageList：：DragEnter（）函数显示拖动图象
	SetCapture();                          //设置鼠标捕获
	m_nScrollTimerID = SetTimer( 2,40,NULL );       //  UINT m_nScrollTimerID; 处理滚动的定时器
}

void vgXTreeCtrl::OnMouseMove(UINT nFlags, CPoint point) 
{
	HTREEITEM hItem;
	UINT flags;
	//检测鼠标敏感定时器是否存在,如果存在则删除,删除后再定时
	if( m_nHoverTimerID )                         // UINT m_nHoverTimerID; 鼠标敏感定时器
	{
		KillTimer( m_nHoverTimerID );
		m_nHoverTimerID = 0;
	}
	m_nHoverTimerID = SetTimer( 1,800,NULL ); //定时为 0.8 秒则自动展开
	m_HoverPoint = point;                     //CPoint m_HoverPoint; 鼠标位置
	if( m_bDragging )
	{
		CPoint pt = point;
		CImageList::DragMove( pt );
		//鼠标经过时高亮显示
		CImageList::DragShowNolock( false ); //避免鼠标经过时留下难看的痕迹
		if( (hItem = HitTest(point,&flags)) != NULL )//HitTest用来测试鼠标当前操作的位置位于
			//哪一个节点中，并且返回该节点句柄.选择此语句应同时选择下面的m_hItemDragD =GetParentItem(hItem)
		//if ((hItem =GetParentItem( HitTest(point,&flags))) != NULL) 
			//换成(hItem =GetParentItem( HitTest(point,&flags))) != NULL，就只在节点间移动，在节点内不移动了
			//同时应该选择下面的m_hItemDragD = hItem
		{
			SelectDropTarget(hItem);//接下来处理 WM_MOUSEMOVE 消息用于更新拖动图象，我们想让移动中的图象经过
			//某些项目时高亮度显示，这可以调用 CTreeCtrl ：：SelectDropTarget（） 来实现。
			m_hItemDragD = hItem;//m_hItemDragD是接受拖动的标签。只能在节点内移动，与下面选择一个
        	//m_hItemDragD =GetParentItem(hItem);  //如果换成GetParentItem(hItem)，那么就只在最后添加
		}

		CImageList::DragShowNolock( true );
		//当条目被拖曳到左边缘时，将条目放在根下 
		CRect rect;
		GetClientRect( &rect );
		if( point.x < rect.left + 20 )
			m_hItemDragD = NULL;
	}
	CTreeCtrl::OnMouseMove(nFlags, point);
}

void vgXTreeCtrl::OnLButtonUp(UINT nFlags, CPoint point) 
{
	CTreeCtrl::OnLButtonUp(nFlags, point);
	if( m_bDragging )
	{
		m_bDragging = FALSE;
		CImageList::DragLeave( this );
		CImageList::EndDrag();
		ReleaseCapture();
		delete m_pDragImage;
		SelectDropTarget( NULL );
		if( m_hItemDragS == m_hItemDragD )
		{
			KillTimer( m_nScrollTimerID );
			return;
		}
		Expand( m_hItemDragD,TVE_EXPAND );//用来展开或者收缩指定父节点的所有子节点
		HTREEITEM htiParent = m_hItemDragD;//m_hItemDragD是接受拖动的标签

		char* sItemText = new char[64];
		char* dItemText = new char[64];

		TV_ITEM item;
		item.mask = TVIF_HANDLE | TVIF_TEXT;
		item.hItem = m_hItemDragD;
		item.pszText = dItemText;
		item.cchTextMax = 64;
		VERIFY(GetItem(&item));
		//TRACE("%s \n" ,dItemText);

		item.hItem = m_hItemDragS;
		item.pszText = sItemText;
		VERIFY(GetItem(&item));
		//TRACE("%s \n", sItemText);
		
		String msg;
		// Send a message to Parent
		::SendMessage(this->GetParent()->m_hWnd,VG_MSG_TREEDRAG,(WPARAM)sItemText, (LPARAM)dItemText);		
		
		while( (htiParent = GetParentItem(htiParent)) != NULL )//此语句是如果接受拖动的标签的最终父节点不是空指针
		{
			if( htiParent == m_hItemDragS )
			{
				/*
				HTREEITEM htiNewTemp = CopyBranch( m_hItemDragS,NULL,TVI_LAST);
				HTREEITEM htiNew = CopyBranch( htiNewTemp,m_hItemDragD,TVI_LAST );
				DeleteItem( htiNewTemp );
				SelectItem( htiNew );
				KillTimer( m_nScrollTimerID );
				return;
				*/
				::MessageBox(NULL, "递归拖拽","Info", MB_OK);
				return ;
			}
		}
		HTREEITEM htiNew = CopyBranch( m_hItemDragS,m_hItemDragD,TVI_LAST );
		DeleteItem( m_hItemDragS );//把原来的节点删掉
		SelectItem( htiNew );//选中新节点
		KillTimer( m_nScrollTimerID );
	}
}	

HTREEITEM vgXTreeCtrl::CopyItem(HTREEITEM hItem,HTREEITEM htiNewParent,HTREEITEM htiAfter)
{
	TV_INSERTSTRUCT tvstruct;
	HTREEITEM hNewItem;
	CString sText;
	//得到源条目的信息
	tvstruct.item.hItem = hItem;
	tvstruct.item.mask=TVIF_CHILDREN|TVIF_HANDLE|TVIF_IMAGE|TVIF_SELECTEDIMAGE;
	GetItem( &tvstruct.item );
	sText = GetItemText( hItem );
	tvstruct.item.cchTextMax = sText.GetLength ();//tvstruct.item.cchTextMax是正文缓冲区的大小
	tvstruct.item.pszText = sText.LockBuffer ();//	tvstruct.item.pszText是表项的标题正文
	//将条目插入到合适的位置
	tvstruct.hParent = htiNewParent;
	tvstruct.hInsertAfter = htiAfter;
	tvstruct.item.mask = TVIF_IMAGE|TVIF_SELECTEDIMAGE|TVIF_TEXT;
	hNewItem = InsertItem( &tvstruct );
	sText.ReleaseBuffer ();//释放缓冲区
	//限制拷贝条目数据和条目状态
	SetItemData( hNewItem,GetItemData(hItem) );
	SetItemState( hNewItem,GetItemState(hItem,TVIS_STATEIMAGEMASK),TVIS_STATEIMAGEMASK);
	return hNewItem;
}

HTREEITEM vgXTreeCtrl::CopyBranch(HTREEITEM htiBranch, HTREEITEM htiNewParent, HTREEITEM htiAfter) //拷贝分支
{
	HTREEITEM hChild;
	HTREEITEM hNewItem = CopyItem( htiBranch,htiNewParent,htiAfter );
	hChild = GetChildItem( htiBranch );
	while( hChild != NULL )
	{
		CopyBranch( hChild,hNewItem,htiAfter );
		hChild = GetNextSiblingItem( hChild );
	}
	return hNewItem;
}

void vgXTreeCtrl::OnLButtonDown(UINT nFlags, CPoint point) //处理无意拖曳
{
	m_dwDragStart = GetTickCount();
	CTreeCtrl::OnLButtonDown(nFlags, point);
}

void vgXTreeCtrl::OnTimer(UINT nIDEvent) 
{
	//鼠标敏感节点
	if( nIDEvent == m_nHoverTimerID )
	{
		KillTimer( m_nHoverTimerID );
		m_nHoverTimerID = 0;
		HTREEITEM trItem = 0;
		UINT uFlag = 0;
		trItem = HitTest( m_HoverPoint,&uFlag );
		if( trItem && m_bDragging )
		{
			SelectItem( trItem );
			Expand( trItem,TVE_EXPAND );
		}
	}
	//处理拖曳过程中的滚动问题
	else if( nIDEvent == m_nScrollTimerID )
	{
		m_TimerTicks++;
		CPoint pt;
		GetCursorPos( &pt );
		CRect rect;
		GetClientRect( &rect );
		ClientToScreen( &rect );
		HTREEITEM hItem = GetFirstVisibleItem();
		if( pt.y < rect.top +10 )
		{
			//向上滚动
			int slowscroll = 6 - (rect.top + 10 - pt.y )/20;
			if( 0 == (m_TimerTicks % ((slowscroll > 0) ? slowscroll : 1)) )
			{
				CImageList::DragShowNolock ( false );
				SendMessage( WM_VSCROLL,SB_LINEUP );
				SelectDropTarget( hItem );
				m_hItemDragD = hItem;
				CImageList::DragShowNolock ( true );
			}
		}
		else if( pt.y > rect.bottom - 10 )
		{
			//向下滚动
			int slowscroll = 6 - (pt.y - rect.bottom + 10)/20;
			if( 0 == (m_TimerTicks % ((slowscroll > 0) ? slowscroll : 1)) )
			{
				CImageList::DragShowNolock ( false );
				SendMessage( WM_VSCROLL,SB_LINEDOWN );
				int nCount = GetVisibleCount();
				for( int i=0 ; i<nCount-1 ; i++ )
					hItem = GetNextVisibleItem( hItem );
				if( hItem )
					SelectDropTarget( hItem );
				m_hItemDragD = hItem;
				CImageList::DragShowNolock ( true );
			}
		}
	}
	else
		CTreeCtrl::OnTimer(nIDEvent);
}
