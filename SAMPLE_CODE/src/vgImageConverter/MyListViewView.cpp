// MyListViewView.cpp : implementation of the CMyListViewView class
//

#include <vgStableHeaders.h>

#include "MyListViewView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define IDC_LIST1                  1001

/////////////////////////////////////////////////////////////////////////////
// CMyListViewView

IMPLEMENT_DYNCREATE(CMyListViewView, CView)

BEGIN_MESSAGE_MAP(CMyListViewView, CView)
	//{{AFX_MSG_MAP(CMyListViewView)
	ON_WM_CREATE()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyListViewView construction/destruction

CMyListViewView::CMyListViewView():CView()
{
	// TODO: add construction code here

}

CMyListViewView::~CMyListViewView()
{
}

/////////////////////////////////////////////////////////////////////////////
// CMyListViewView drawing

void CMyListViewView::OnDraw(CDC* pDC)
{
	CVgimgReaderDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CMyListViewView diagnostics

#ifdef _DEBUG
void CMyListViewView::AssertValid() const
{
	CView::AssertValid();
}

void CMyListViewView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CVgimgReaderDoc* CMyListViewView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CVgimgReaderDoc)));
	return (CVgimgReaderDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMyListViewView message handlers

// When OnCreate is called for the view, we create the
// CMyListCtrl instance that will occupy the client area of
// the view.

int CMyListViewView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// Create the style
	DWORD dwStyle = WS_CHILD | WS_VISIBLE | WS_TABSTOP |
		LVS_REPORT  |  TVS_HASLINES   |   TVS_LINESATROOT   |   TVS_HASBUTTONS ;
	// Create the list control.  Don't worry about specifying
	// correct coordinates.  That will be handled in OnSize()


	m_ListCtrl.setCheckState( false );

	CTreeCtrl* listctrl = (CTreeCtrl*)&m_ListCtrl;

	BOOL bResult = listctrl->Create(dwStyle,
		CRect(0,0,0,0),
		this,
		IDC_LIST1);


	
	return (bResult ? 0 : -1);
	//return true;
}//OnCreate


// Override OnSize to resize the control to match the view
void CMyListViewView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	if (::IsWindow(m_ListCtrl.m_hWnd))
		m_ListCtrl.MoveWindow(0, 0, cx, cy, TRUE);

}//OnSize

void CMyListViewView::OnInitialUpdate() 
{
	CView::OnInitialUpdate();

	//m_ListCtrl.Init();

	m_ListCtrl.AddHidFolder(CSIDL_BITBUCKET);
	m_ListCtrl.AddHidFolder(CSIDL_CONTROLS);

	//m_ListCtrl.DisplayTree2();

}//OnInitialUpdate

BOOL CMyListViewView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Add your specialized code here and/or call the base class
	//cs.style   |=   TVS_HASLINES   |   TVS_LINESATROOT   |   TVS_HASBUTTONS ; 

	cs.style |= WS_DLGFRAME   ;

	return CView::PreCreateWindow(cs);
}
