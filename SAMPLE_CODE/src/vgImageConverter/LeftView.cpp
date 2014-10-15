// LeftView.cpp : CLeftView 类的实现
//

#include <vgStableHeaders.h>
#include "VgimgReader.h"

#include "VgimgReaderDoc.h"
#include "LeftView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CLeftView

IMPLEMENT_DYNCREATE(CLeftView, CTreeView)

BEGIN_MESSAGE_MAP(CLeftView, CTreeView)
	ON_NOTIFY_REFLECT(NM_RCLICK, &CLeftView::OnNMRclick)
	ON_NOTIFY_REFLECT(TVN_SELCHANGED, &CLeftView::OnTvnSelchanged)
END_MESSAGE_MAP()


// CLeftView 构造/析构

CLeftView::CLeftView()
{
	// TODO: 在此处添加构造代码
}

CLeftView::~CLeftView()
{
}

BOOL CLeftView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改 CREATESTRUCT cs 来修改窗口类或样式

	cs.style   |=   TVS_HASLINES   |   TVS_LINESATROOT   |   TVS_HASBUTTONS;   

	return CTreeView::PreCreateWindow(cs);
}

void CLeftView::OnInitialUpdate()
{
	CTreeView::OnInitialUpdate();

	// TODO: 调用 GetTreeCtrl() 直接访问 TreeView 的树控件，
	//  从而可以用项填充 TreeView。

	CTreeCtrl &m_TreeCtrl = this->GetTreeCtrl();

	//m_TreeCtrl.Create(WS_VISIBLE | WS_TABSTOP | WS_CHILD | WS_BORDER
	//	| TVS_HASBUTTONS | TVS_LINESATROOT | TVS_HASLINES
	//	| TVS_DISABLEDRAGDROP,
	//	CRect(0, 0, 5, 5), this, 0x1005 );

	m_TreeCtrl.DeleteAllItems();
	m_TreeCtrl.EnableAutomation();
	m_TreeCtrl.EnableToolTips();
	//m_TreeCtrl.EnableTypeLib();
	m_TreeCtrl.EnableTrackingToolTips();


	CString str, sText;

	HTREEITEM hRoot = m_TreeCtrl.InsertItem( "Root", 1, 1 );
	int i;

	for ( i = 0; i < 10; i++ )
	{
		str.Format("%s%d", "Tree_Item_", i+1);   
		m_TreeCtrl.InsertItem( str, 0, 1, hRoot );
	}

	CTreeCtrl* pCtrl = &m_TreeCtrl;
	ASSERT(pCtrl != NULL);

	// Insert a root item using the structure. We must
	// initialize a TVINSERTSTRUCT structure and pass its
	// address to the call. 

	TVINSERTSTRUCT tvInsert;
	tvInsert.hParent = NULL;
	tvInsert.hInsertAfter = NULL;
	tvInsert.item.mask = TVIF_TEXT;
	tvInsert.item.pszText = _T("United States");

	HTREEITEM hCountry = pCtrl->InsertItem(&tvInsert);

	// Insert subitems of that root. Pennsylvania is
	// a state in the United States, so its item will be a child
	// of the United States item. We won't set any image or states,
	// so we supply only the TVIF_TEXT mask flag. This
	// override provides nearly complete control over the
	// insertion operation without the tedium of initializing
	// a structure. If you're going to add lots of items
	// to a tree, you might prefer the structure override
	// as it affords you a performance win by allowing you
	// to initialize some fields of the structure only once,
	// outside of your insertion loop.

	HTREEITEM hPA = pCtrl->InsertItem(TVIF_TEXT,
		_T("Pennsylvania"), 0, 0, 0, 0, 0, hCountry, NULL);

	// Insert the "Washington" item and assure that it is
	// inserted after the "Pennsylvania" item. This override is 
	// more appropriate for conveniently inserting items with 
	// images.

	HTREEITEM hWA = pCtrl->InsertItem(_T("Washington"),
		0, 0, hCountry, hPA);

	// We'll add some cities under each of the states.
	// The override used here is most appropriate
	// for inserting text-only items.

	pCtrl->InsertItem(_T("Pittsburgh"), hPA, TVI_SORT);
	pCtrl->InsertItem(_T("Harrisburg"), hPA, TVI_SORT);
	pCtrl->InsertItem(_T("Altoona"), hPA, TVI_SORT);

	pCtrl->InsertItem(_T("Seattle"), hWA, TVI_SORT);
	pCtrl->InsertItem(_T("Kalaloch"), hWA, TVI_SORT);
	pCtrl->InsertItem(_T("Yakima"), hWA, TVI_SORT);
}


// CLeftView 诊断

#ifdef _DEBUG
void CLeftView::AssertValid() const
{
	CTreeView::AssertValid();
}

void CLeftView::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}

CVgimgReaderDoc* CLeftView::GetDocument() // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CVgimgReaderDoc)));
	return (CVgimgReaderDoc*)m_pDocument;
}
#endif //_DEBUG


// CLeftView 消息处理程序

void CLeftView::OnNMRclick(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	*pResult = 0;

	////MessageBox("sdfsa");

	//CMenu   menuPopup;   
	//menuPopup.LoadMenu(IDR_MENU1);   

	//CMenu*   pMenu=menuPopup.GetSubMenu(0);
	//CPoint   pos;   
	//GetCursorPos(&pos);//   获取鼠标位置   
	//SetForegroundWindow(); 
	//pMenu->TrackPopupMenu(TPM_LEFTALIGN|TPM_LEFTBUTTON,  
	//	pos.x,   pos.y,   this,   NULL);   


	CPoint point;
	
	GetCursorPos(&point);   //   当前鼠标坐标   
	CPoint original_point = point;

	CTreeCtrl&   m_tree   =   GetTreeCtrl();   
	m_tree.ScreenToClient( &point);   

	CMenu   menu;   
	CMenu   *ptrMenu;   
	HTREEITEM   Item;   
	UINT   nFlag   =   TVHT_ONITEM;   //   当在   Item   上右击时   

	Item   =   m_tree.HitTest(   point,   &nFlag   );   
	//如果鼠标在被选项上右击，那么就会弹出一个菜单   
	if   (   Item   !=   NULL)   
	{     
		m_tree.SelectItem(Item);   
		menu.LoadMenu(IDR_MENU1);   
		ptrMenu=menu.GetSubMenu(0);   
		ptrMenu->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON,   
			original_point.x,   
			original_point.y,   
			this,   
			NULL);   
	}   

}

void CLeftView::OnTvnSelchanged(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;
}
