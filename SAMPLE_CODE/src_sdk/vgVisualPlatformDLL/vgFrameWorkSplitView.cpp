// vgFrameWorkView.cpp : implementation of the CvgFrameWorkSplitView class
//


 
#include <vgStableHeaders.h>
#include "res.h"
#include "vgFrameWork.h"
#include "vgFrameWorkDoc.h"
#include "vgFrameWorkSplitView.h"
#include "vgUIController/vgUIController.h"
#include "vgEntry/vgBaseEntry.h"
// #include "vgFrameWorkView.h"
#include <vgKernel/vgkGpuManager.h>

#include "vgEntry/vgTerrainEntry.h"


#include <sys/timeb.h>
#include <MainFrm.h>


#include <vgKernel/vgkOpenGLSupport.h>
#include <vgMesh/vgmMeshManager.h>
#include <vgGlobal/vggGlobalFacade.h>
#include <vgGlobal/vggGlobalConsole.h>
#include <vgKernel/vgkRenderer.h>

#include <vgKernel/vgkRay.h>
#include <vgKernel/vgkMath.h>
#include <vgKernel/vgkInputSystem.h>
#include <vgKernel/vgkSelectManager.h>

#include <vgKernel/vgkStringUtility.h>

#include <vgDlgTestMultisample.h>

#include <vgKernel/vgkAbstractTreeFacMgr.h>
#include <vgTree/vgtTreeFactory.h>

#include <vgMesh/vgmFileHandleVgm.h>

#include <vgCam/vgcaCamManager.h>
#include "vgEntry/vgEntryFactory.h"

#include <vgCam/vgcaCameraRecord.h>

#include "vgTree/vgtTreeFactory.h"
#include <vgKernel/vgkRendererManager.h>

#include <vgEffect/vgAviNode.h>
#include <vgDlgAviNode.h>


#include <vgOcc/vgoOcclusion.h>


#include <vgTerritory/vgtTerrainManager.h>
#include <vgTerritory/vgtElevationFilter.h>

#include "DlgAbout.h"
#include "DlgTranslateAll.h"
#include "DlgTranslateVector.h"
//#include "DlgShpToDBEx.h"
#include <vgShape/DlgShpToDBEx.h>

//Utiltity for separate code of view
#include <vgGlobal/vggGlobalUtility.h>
#include <vgGlobal/vggSoundUtility.h>
#include <vgGlobal/vggEffectUtility.h>
#include <vgGlobal/vggEditUtility.h>
#include <vgGlobal/vggGisUtility.h>
#include <vgGlobal/vggVgcamUtility.h>
#include <vgGlobal/vggVgmodUtility.h>
#include <vgGlobal/vggVgmeshUtility.h>
#include <vgGlobal/vggVgshpUtility.h>

#include <vgConf/vgcoExeConfigRegProxy.h>
#include <vgConf/vgcoExeConfig.h>
#include <vgConf/vgcoProjectConfig.h>
#include <vgConf/vgcoProjectConfigRegProxy.h>


#include <vgDatabase/vgdDatabaseManager.h>
#include <vgDatabase/vgdOracleConnector.h>
#include <vgDatabase/vgdBasedConnector.h>

#include <vgDatabase/vgDlgDBConnect.h>
#include <vgDatabase/vgDlgCondition.h>

#include <vgVisualEffects/vgviBackgroundManager.h>
//#include <vgScript/vgscScriptManager.h>


#include <vgScript/vgscScriptManager.h>
#include <vgGlobal/vggSystemFacade.h>
#include <vgGlobal/vggSceneFileUtility.h>

#include <vgTerritory/vgtTerrainCenterManager.h>
//#include <vgMod/vgModTerrainManager.h>

//#include "vgDlgSun.h"
#include <vgaviexportdialog.h>
#include <vgExportBMPDialog.h>


#include <vgTerritory/vgtCutSurfaceLevelling.h>


#include <vgImage/vgiCximageWrapper.h>

#include <vgShape/vgshShapeManager.h>
#include "vgVcrHeightDlg.h"
//#include "vgShapeDataSourceEntry.h"

//#include "vgShapeLayerEntry.h"

#include <vgAutoBuild/vgAutoBuildNode.h>
#include <vgAutoBuild/vgvAutoBuildManager.h>
#include <vgShape/vgshSpecialPolygon.h>
#include <vgShape/vgshPolygon.h>


#include "DlgAutoBuildInput.h"
#include "DlgAutoIn.h"
#include <vgLogo/vgloLogoManager.h>
#include "DlgTriggerConfig.h"
#include "vgDlgDynamicTexNode.h"
#include <vgPlan/vgPlanmanager.h>
#include <vgDlgTreeSet.h>
#include <DlgFindObject.h>
#include <DlgSelectFlash.h>


#include <vgKernel/vgkDynamicLibraryUtility.h>

#include "vgUserScriptSystem.h"
#include "vgUserScriptOtherModules.h"

#include <vgMod/vgTriggerManager.h>
#include <vgMod/vgModMisc.h>
#include <vgMovingManager.h>


#include <vgKernel/vgkClassFactoryManager.h>

#include <vgModel/vgmoFileHandleVmd.h>
#include <vgModel/vgmoModelManager.h>


#include <vgMod/vgGisRoadMatch.h>
#include <vgDlgGismatch.h>

#include <vgKernel/vgkPluginManager.h>

#include <vgSolar/vgsoDefinition.h>
#include <vgDatabase/vgdDefinition.h>
#include <vgKernel/vgkRenderCommandManager.h>

#include "vgClientRenderCommand.h"
#include <vgKernel/vgkPropertyManager.h>

using std::list;
using std::vector;
using namespace vgDatabase;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define VG_MSG_RENDER WM_USER + 100


#define VGMSGBOX2(A) {\
	this->SetTimer(1, 150, NULL);\
	A; \
	this->SetTimer(1, 15, NULL);}

// ---------------------------------------------------------

// CvgFrameWorkSplitView
HGLRC m_grcobserver = NULL;
HDC   m_gdcobserver = NULL;
//////////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNCREATE(CvgFrameWorkSplitView, CView)

BEGIN_MESSAGE_MAP(CvgFrameWorkSplitView, CView)
	// Standard printing commands

	
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_WM_TIMER()
		
	ON_WM_LBUTTONDBLCLK()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOVE()
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSEWHEEL()
	ON_WM_WINDOWPOSCHANGING()
	ON_WM_RBUTTONUP()
	ON_WM_RBUTTONDOWN()
	
	END_MESSAGE_MAP()

// MFC消息

CvgFrameWorkSplitView::CvgFrameWorkSplitView()
: m_pDC(NULL)
{	

}

CvgFrameWorkSplitView::~CvgFrameWorkSplitView()
{

}

BOOL CvgFrameWorkSplitView::PreCreateWindow(CREATESTRUCT& cs)
{
	return CView::PreCreateWindow(cs);
}



// CvgFrameWorkSplitView printing
void CvgFrameWorkSplitView::OnFilePrintPreview()
{
// 	BCGPPrintPreview (this);
}

BOOL CvgFrameWorkSplitView::OnPreparePrinting(CPrintInfo* pInfo)
{
// 	return DoPreparePrinting(pInfo);
	return TRUE;
}

void CvgFrameWorkSplitView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	
}

void CvgFrameWorkSplitView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	
}



void CvgFrameWorkSplitView::OnInitialUpdate()
{
// 	CView::OnInitialUpdate();
	// TODO: 在此添加专用代码和/或调用基类
}

void CvgFrameWorkSplitView::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CView::OnShowWindow(bShow, nStatus);
}


// CvgFrameWorkSplitView diagnostics
#ifdef _DEBUG
void CvgFrameWorkSplitView::AssertValid() const
{
	CView::AssertValid();
}

void CvgFrameWorkSplitView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CvgFrameWorkDoc* CvgFrameWorkSplitView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CvgFrameWorkDoc)));
	return (CvgFrameWorkDoc*)m_pDocument;
}
#endif //_DEBUG

void CvgFrameWorkSplitView::OnWindowPosChanging(WINDOWPOS* lpwndpos)
{
	CView::OnWindowPosChanging(lpwndpos);

	CRect rect;

	GetWindowRect(&rect);

	int nCenterX = rect.TopLeft().x+ rect.Width()/2;
	int nCenterY = rect.TopLeft().y+ rect.Height()/2;
	//vgCam::CamManager::getSingleton().setCenterOfScreen(nCenterX, nCenterY);
	vgGlobal::CamUtility::setCenterOfScreen(nCenterX, nCenterY);

	// TODO: 在此处添加消息处理程序代码
}

BOOL CvgFrameWorkSplitView::OnEraseBkgnd(CDC* pDC)
{
	return true;
}

//OpenGL 环境
void CvgFrameWorkSplitView::renderScene(void)
{

	VGK_CHECK_OPENGL_ERROR();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear Screen And Depth Buffer
	glLoadIdentity();	
	
	// 按优先级渲染所有插件
	vgKernel::RenderCommandFacade::RenderAll();

	HDC handledevice = m_pDC->GetSafeHdc();

	if ( handledevice == INVALID_HANDLE_VALUE )
	{
		assert( 0 );
	}

	SwapBuffers( handledevice );

	vgKernel::OpenGLSupport::makeErrorStackEmpty();

	try
	{
		VGK_CHECK_OPENGL_ERROR();
	}
	catch (...)
	{
		int dff=0;

		::MessageBox( NULL , "SwapBuffers 出错!" , "ERROR" , MB_OK );
	}

	vgGlobal::GlobalConsole::getSingleton().showFps();

	VGK_CHECK_OPENGL_ERROR();
}



bool CvgFrameWorkSplitView::initGLContext(void)
{
	GLuint PixelFormat;	

	static PIXELFORMATDESCRIPTOR pfd = { 
		sizeof(PIXELFORMATDESCRIPTOR),    // pfd结构的大小 
		1,                                // 版本号 
		PFD_DRAW_TO_WINDOW |              // 支持在窗口中绘图 
		PFD_SUPPORT_OPENGL |              // 支持 OpenGL 
		PFD_DOUBLEBUFFER,                 // 双缓存模式 
		PFD_TYPE_RGBA,                    // RGBA 颜色模式 
		24,                               // 24 位颜色深度 
		0, 0, 0, 0, 0, 0,                 // 忽略颜色位 
		1,                                // 没有非透明度缓存 
		0,                                // 忽略移位位 
		0,                                // 无累加缓存 
		0, 0, 0, 0,                       // 忽略累加位 
		32,                               // 32 位深度缓存     
		8,                                // 无模板缓存 //改动阴影
		0,                                // 无辅助缓存 
		PFD_MAIN_PLANE,                   // 主层 
		0,                                // 保留 
		0, 0, 0                           // 忽略层,可见性和损毁掩模 
	};

// 	HWND hWND = this->GetSafeHwnd();
// 	HDC hDC = ::GetDC(hWND);
	m_pDC = new CClientDC(this);
	// 选择合适的Device Context像素点格式
	if (!(PixelFormat=ChoosePixelFormat(m_pDC->GetSafeHdc(),&pfd)))		// Did Windows Find A Matching Pixel Format?
	{							
		::MessageBox(NULL,"Can't Find A Suitable PixelFormat.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;									// Return FALSE
	}

// 	if ( *(((CMainFrame *)GetParent())->test_multisample_dlg)._parbMultisampleSupported )
// 	{
// 		PixelFormat = *((((CMainFrame *)GetParent())->test_multisample_dlg)._parbMultisampleFormat);
// 	}



	// 设置新的Device Context像素点格式
	if(!SetPixelFormat(m_pDC->GetSafeHdc(),PixelFormat,&pfd))			// Are We Able To Set The Pixel Format?
	{
		::MessageBox(NULL,"Can't Set The PixelFormat.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;									// Return FALSE
	}
	// 根据当前的Device Context得到rending context
	if (!(m_hGLContext=wglCreateContext(m_pDC->GetSafeHdc())))	// Are We Able To Get A Rendering Context?
	{
		//KillGLWindow();								// Reset The Display
		::MessageBox(NULL,"Can't Create A GL Rendering Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;									// Return FALSE
	}
	// 设置当前Device context 的rendering context
	if(!wglMakeCurrent(m_pDC->GetSafeHdc(),m_hGLContext))			// Try To Activate The Rendering Context
	{
		//KillGLWindow();								// Reset The Display
		::MessageBox(NULL,"Can't Activate The GL Rendering Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;									// Return FALSE
	}

	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0.5f,0.6f,0.8f,1.0f);					// Black Background
	glClearDepth(1.0f);									// Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations


	return true;
}

void CvgFrameWorkSplitView::releaseGLContext(void)
{
	if (m_hGLContext)										// Do We Have A Rendering Context?
	{
		if (!wglMakeCurrent(NULL,NULL))							// Are We Able To Release The DC And RC Contexts?
		{
			::MessageBox(NULL,"Release Of DC And RC Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		}

		if (!wglDeleteContext(m_hGLContext))				// Are We Able To Delete The RC?
		{
			::MessageBox(NULL,"Release Rendering Context Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		}
		m_hGLContext=NULL;								// Set RC To NULL
	}

	if (m_pDC)
		delete m_pDC;
}

int  CvgFrameWorkSplitView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	this->initGLContext();


	SetTimer(1, 15, NULL);

 	return 0;
}

void CvgFrameWorkSplitView::OnDestroy()
{
	CView::OnDestroy();

	this->releaseGLContext();
}

void CvgFrameWorkSplitView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (1 == nIDEvent)
	{
		::wglMakeCurrent(m_pDC->GetSafeHdc(), m_hGLContext);
		m_hGLContext;
		m_grcobserver = ::wglGetCurrentContext();
		m_pDC->m_hDC;
		m_gdcobserver = ::wglGetCurrentDC();
		VGK_CHECK_OPENGL_ERROR();
		renderScene();
		VGK_CHECK_OPENGL_ERROR();
		::wglMakeCurrent(m_pDC->GetSafeHdc(), NULL);
	}
	CView::OnTimer(nIDEvent);
}

// CvgFrameWorkSplitView drawing
void CvgFrameWorkSplitView::OnDraw(CDC* /*pDC*/)
{
 	CvgFrameWorkDoc* pDoc = GetDocument();
 	ASSERT_VALID(pDoc);
}

void CvgFrameWorkSplitView::SwitchView()
{
//  	CRect rect;
//  	GetClientRect(&rect);
//  
//  	int cx = rect.Width();
//  	int cy = rect.Height();
//  
//  	m_wndsplitter.MoveWindow(-2,-2,cx,cy+3);
//  	m_wndsplitter.SetColumnInfo(0, cx/4, 0);
//  	m_wndsplitter.SetColumnInfo(1,cx-cx/4, 0);
//  	m_wndsplitter.RecalcLayout();
 
	return;
}

void CvgFrameWorkSplitView::OnSize(UINT nType, int cx, int cy)
{
	::wglMakeCurrent(m_pDC->GetSafeHdc(), m_hGLContext);
	
	SwitchView();
	CView::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	int height = cy;
	int width = cx;

	if (height==0)										// Prevent A Divide By Zero By
	{
		height=1;										// Making Height Equal One
	}

	glViewport(0, 0, width, height);						// Reset The Current Viewport

	//vgLogo::LogoManager::getSingleton().getMenuLogoPtr()->resetCorner();
	// vgKernel::SelectManager::getSingleton().SetViewSize(cx, cy);

	// vgCam::CamManager::getSingleton().setAspectRatioByWindowSize(cx, cy);

#if 0
	vgKernel::UnTypedPropertyPtr prop; 
	prop = vgKernel::PropertyManager::getSingleton().getProperty("PROP_SCREEN_SIZE");
	
	if (prop != NULL)
	{
		vgKernel::Property<vgKernel::Vec2>* pScreenProp 
			= (vgKernel::Property<vgKernel::Vec2>*)prop;

		assert(pScreenProp != NULL);
		pScreenProp->setValue(vgKernel::Vec2(cx, cy));
	}
	else
	{
		vgKernel::Property<vgKernel::Vec2> *pScreenProp
			= new vgKernel::Property<vgKernel::Vec2>("PROP_SCREEN_SIZE", vgKernel::Vec2(cx, cy));

		vgKernel::PropertyManager::getSingleton().addProperty(pScreenProp);
	}
#endif

	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glLoadIdentity();									// Reset The Modelview Matrix

	::wglMakeCurrent(m_pDC->GetSafeHdc(), NULL);
}

// 鼠标事件响应
void CvgFrameWorkSplitView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	//vgGlobal::SystemFacade::responseLButtonDblClk(nFlags, point, this);
	vgGlobal::GlobalUtility::responseLButtonDblClk( nFlags, point, this );

	CView::OnLButtonDblClk(nFlags, point);
}

void CvgFrameWorkSplitView::OnLButtonDown(UINT nFlags, CPoint point)
{
	//vgGlobal::SystemFacade::responseLButtonDown(nFlags, point);
	vgGlobal::GlobalUtility::responseLButtonDown( nFlags, point );

	CView::OnLButtonDown(nFlags, point);
}

void CvgFrameWorkSplitView::OnMove(int x, int y)
{
	CView::OnMove(x, y);
}

void CvgFrameWorkSplitView::OnLButtonUp(UINT nFlags, CPoint point)
{
	//vgGlobal::SystemFacade::responseLButtonUp(nFlags, point);
	vgGlobal::GlobalUtility::responseLButtonUp( nFlags, point );

	CView::OnLButtonUp(nFlags, point);
}

void CvgFrameWorkSplitView::OnMouseMove(UINT nFlags, CPoint point)
{
	vgKernel::InputSystem::getSingleton().OnMouseMove(nFlags, point);

	CView::OnMouseMove(nFlags, point);

	static bool m_bIsShow = true;		//@FengYK 2009/11/13
	int y = point.y;					//全屏浮动菜单
	CMainFrame *m_pFrame =(CMainFrame *)(this->GetParentFrame());
	BOOL m_bFullScreen = m_pFrame->IsFullScreen();
	if ( m_bFullScreen)
	{
		if (y<5)
		{
			if ( m_bIsShow)
			{
				m_pFrame->EnableFullScreenMainMenu(TRUE);
				m_pFrame->setMainMenuShowOnFullScreen();
				m_bIsShow = false;
			}
		}
		else
		{
			if (!m_bIsShow)
			{
				m_pFrame->EnableFullScreenMainMenu(FALSE);
				m_pFrame->setMainMenuShowOnFullScreen();
				m_bIsShow = true;
			}
		}
	}
}

 BOOL CvgFrameWorkSplitView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
 {
 	vgKernel::InputSystem::getSingleton().OnMouseWheel(nFlags, zDelta, pt);
 	
	return CView::OnMouseWheel(nFlags, zDelta, pt);
 }

 void CvgFrameWorkSplitView::OnRButtonUp(UINT nFlags, CPoint point)
 {
	vgKernel::InputSystem::getSingleton().OnRButtonUp(nFlags, point);
	 
	CView::OnRButtonUp(nFlags, point);
 }

 void CvgFrameWorkSplitView::OnRButtonDown(UINT nFlags, CPoint point)
 {
	 vgKernel::InputSystem::getSingleton().OnRButtonDown(nFlags, point);
	
	 CView::OnRButtonDown(nFlags, point);
 }
