// MainFrm.cpp : CMainFrame 类的实现
//

#include <vgStableHeaders.h>
#include "VgimgReader.h"

#include "SaveVgimgDlg.h"

#include "MyListViewView.h"

#include "MainFrm.h"
#include "LeftView.h"
#include "VgimgReaderView.h"
#include "FileTreeView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_UPDATE_COMMAND_UI_RANGE(AFX_ID_VIEW_MINIMUM, AFX_ID_VIEW_MAXIMUM, &CMainFrame::OnUpdateViewStyles)
	ON_COMMAND_RANGE(AFX_ID_VIEW_MINIMUM, AFX_ID_VIEW_MAXIMUM, &CMainFrame::OnViewStyle)
	ON_COMMAND(ID_CREATE_VGIMG, &CMainFrame::OnCreateVgimg)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // 状态行指示器
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};


// CMainFrame 构造/析构

CMainFrame::CMainFrame()
{
	// TODO: 在此添加成员初始化代码
}

CMainFrame::~CMainFrame()
{
}


int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("未能创建工具栏\n");
		return -1;      // 未能创建
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("未能创建状态栏\n");
		return -1;      // 未能创建
	}

	m_wndToolBar.SetButtonText(0,"新建");
	m_wndToolBar.SetButtonText(1,"打开");
	m_wndToolBar.SetButtonText(3,"大图标");
	m_wndToolBar.SetButtonText(4,"小图标");
	m_wndToolBar.SetButtonText(5,"列表");
	m_wndToolBar.SetButtonText(6,"详细信息");
	m_wndToolBar.SetButtonText(8,"设置");
	m_wndToolBar.SetButtonText(9,"选项");
	m_wndToolBar.SetButtonText(10,"纹理制作");
	m_wndToolBar.SetButtonText(11,"关于");
	m_wndToolBar.SetSizes(CSize(55,45),CSize(24,24));


	// TODO: 如果不需要工具栏可停靠，则删除这三行
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);


	m_wndToolBar.SetFullColorImage(IDR_MAINFRAME_24, RGB(255, 0, 255));

	//m_ToolbarImageList.Create(24, 24, ILC_COLOR32, 1);

	//m_ToolbarImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON1));
	//m_ToolbarImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON4));
	//m_ToolbarImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON5));


	//m_wndToolBar.GetToolBarCtrl().SetImageList( &m_ToolbarImageList );

	return 0;
}

BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT /*lpcs*/,
	CCreateContext* pContext)
{
	// 创建拆分窗口
	if (!m_wndSplitter.CreateStatic(this, 1, 2))
		return FALSE;

	if (!m_wndSplitter.CreateView(0, 0, RUNTIME_CLASS(CMyListViewView), CSize(250, 100), pContext) ||
		!m_wndSplitter.CreateView(0, 1, RUNTIME_CLASS(CVgimgReaderView), CSize(100, 100), pContext))
	{
		m_wndSplitter.DestroyWindow();
		return FALSE;
	}

	return TRUE;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return TRUE;
}


// CMainFrame 诊断

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG


// CMainFrame 消息处理程序


CVgimgReaderView* CMainFrame::GetRightPane()
{
	CWnd* pWnd = m_wndSplitter.GetPane(0, 1);
	CVgimgReaderView* pView = DYNAMIC_DOWNCAST(CVgimgReaderView, pWnd);
	return pView;
}

void CMainFrame::OnUpdateViewStyles(CCmdUI* pCmdUI)
{
	if (!pCmdUI)
		return;

	// TODO: 自定义或扩展此代码以处理“视图”菜单中的选项

	CVgimgReaderView* pView = GetRightPane(); 

	// 如果右窗格尚未创建或者不是视图，
	// 则在范围内禁用命令

	if (pView == NULL)
		pCmdUI->Enable(FALSE);
	else
	{
		DWORD dwStyle = pView->GetStyle() & LVS_TYPEMASK;

		// 如果命令是 ID_VIEW_LINEUP，则只有在处于
		// LVS_ICON 或 LVS_SMALLICON 模式时才启用命令

		if (pCmdUI->m_nID == ID_VIEW_LINEUP)
		{
			if (dwStyle == LVS_ICON || dwStyle == LVS_SMALLICON)
				pCmdUI->Enable();
			else
				pCmdUI->Enable(FALSE);
		}
		else
		{
			// 否则，使用点线来反映视图的样式
			pCmdUI->Enable();
			BOOL bChecked = FALSE;

			switch (pCmdUI->m_nID)
			{
			case ID_VIEW_DETAILS:
				bChecked = (dwStyle == LVS_REPORT);
				break;

			case ID_VIEW_SMALLICON:
				bChecked = (dwStyle == LVS_SMALLICON);
				break;

			case ID_VIEW_LARGEICON:
				bChecked = (dwStyle == LVS_ICON);
				break;

			case ID_VIEW_LIST:
				bChecked = (dwStyle == LVS_LIST);
				break;

			default:
				bChecked = FALSE;
				break;
			}

			pCmdUI->SetRadio(bChecked ? 1 : 0);
		}
	}
}


void CMainFrame::OnViewStyle(UINT nCommandID)
{
	// TODO: 自定义或扩展此代码以处理“视图”菜单中的选项
	CVgimgReaderView* pView = GetRightPane();

	// 如果右窗格已创建而且是 CVgimgReaderView，
	// 则处理菜单命令...
	if (pView != NULL)
	{
		DWORD dwStyle = -1;

		switch (nCommandID)
		{
		case ID_VIEW_LINEUP:
			{
				// 要求列表控件与网格对齐
				CListCtrl& refListCtrl = pView->GetListCtrl();
				refListCtrl.Arrange(LVA_SNAPTOGRID);
			}
			break;

		// 其他命令更改列表控件上的样式
		case ID_VIEW_DETAILS:
			dwStyle = LVS_REPORT;
			break;

		case ID_VIEW_SMALLICON:
			dwStyle = LVS_SMALLICON;
			break;

		case ID_VIEW_LARGEICON:
			dwStyle = LVS_ICON;
			break;

		case ID_VIEW_LIST:
			dwStyle = LVS_LIST;
			break;
		}

		// 更改样式；窗口将自动重新绘制
		if (dwStyle != -1)
			pView->ModifyStyle(LVS_TYPEMASK, dwStyle);
	}
}


void CMainFrame::OnCreateVgimg()
{
	// TODO: Add your command handler code here
	//MessageBox("fff");

	CSaveVgimgDlg dlg;
	dlg.DoModal();

    dlg.GetDC();
	/*
	// 创建非模态对话框。这个时候，要注意，需重载
	// onOK来调用DestroyWindow函数才可以。
	CSaveVgimgDlg *pdlg = new CSaveVgimgDlg();
	pdlg->Create( IDD_SAVEVGIMGDLG );
	pdlg->ShowWindow( SW_SHOW );
	*/

}
