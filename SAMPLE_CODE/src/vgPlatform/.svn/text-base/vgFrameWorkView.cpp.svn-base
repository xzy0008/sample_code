// vgFrameWorkView.cpp : implementation of the CvgFrameWorkView class
//

#include <vgStableHeaders.h>
#include "vgFrameWork.h"
#include "vgFrameWorkDoc.h"
#include "vgFrameWorkView.h"
#include "vgUIController.h"
#include "vgBasedNode.h"

#include "vgTestNode1.h"



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

using std::list;
using std::vector;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define VG_MSG_RENDER WM_USER + 100

void TestData();

struct THREADFLAG g_threadFlag;

static UINT RenderThread(LPVOID pParam);
CCriticalSection g_renderCriticalArea;



// ---------------------------------------------------------

// CvgFrameWorkView

IMPLEMENT_DYNCREATE(CvgFrameWorkView, CView)

BEGIN_MESSAGE_MAP(CvgFrameWorkView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, OnFilePrintPreview)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_WM_TIMER()
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_VGM_IMPORT_VGM, &CvgFrameWorkView::OnVgmImportVgm)
	ON_COMMAND(ID_VGI_IMPORT_VGI, &CvgFrameWorkView::OnVgiImportVgi)
	ON_COMMAND(ID_VGM_SAVE_VGM, &CvgFrameWorkView::OnVgmSaveVgm)
	ON_COMMAND(ID_VGMI_SAVE_VGM_VGI, &CvgFrameWorkView::OnVgmiSaveVgmVgi)
	ON_WM_LBUTTONDBLCLK()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOVE()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_VGTERRAIN_WIREFRAME, &CvgFrameWorkView::OnVgterrainWireframe)
	ON_COMMAND(ID_VGTERRAIN_NOWIREFRAME, &CvgFrameWorkView::OnVgterrainNowireframe)
	ON_COMMAND(ID_VGTERRAIN_TURNON, &CvgFrameWorkView::OnVgterrainTurnon)
	ON_WM_ACTIVATEAPP()

	ON_MESSAGE(VG_MSG_RENDER, &CvgFrameWorkView::OnRender)
	ON_COMMAND(ID_VGTERRAIN_CONVERT_DEM_TO_VGTR, &CvgFrameWorkView::OnVgterrainConvertDemToVgtr)
	ON_COMMAND(ID_VGTERRAIN_CONVERT_VGTR_HEIGHTMAP, &CvgFrameWorkView::OnVgterrainConvertVgtrHeightmap)
END_MESSAGE_MAP()

// CvgFrameWorkView construction/destruction

CvgFrameWorkView::CvgFrameWorkView()
: m_pDC(NULL), testVector(100000), pNodeList(vgUIController::GetInstance()->GetNodeList())
{
	// TODO: add construction code here
}

CvgFrameWorkView::~CvgFrameWorkView()
{
}

BOOL CvgFrameWorkView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CvgFrameWorkView drawing

void CvgFrameWorkView::OnDraw(CDC* /*pDC*/)
{
	CvgFrameWorkDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);


	RenderScene();



}

// CvgFrameWorkView printing

void CvgFrameWorkView::OnFilePrintPreview()
{
	BCGPPrintPreview (this);
}

BOOL CvgFrameWorkView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CvgFrameWorkView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CvgFrameWorkView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CvgFrameWorkView diagnostics

#ifdef _DEBUG
void CvgFrameWorkView::AssertValid() const
{
	CView::AssertValid();
}

void CvgFrameWorkView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CvgFrameWorkDoc* CvgFrameWorkView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CvgFrameWorkDoc)));
	return (CvgFrameWorkDoc*)m_pDocument;
}
#endif //_DEBUG


// CvgFrameWorkView message handlers

bool CvgFrameWorkView::InitGLContext(void)
{
	GLuint PixelFormat;	

	static	PIXELFORMATDESCRIPTOR pfd=				// pfd Tells Windows How We Want Things To Be
	{
		sizeof(PIXELFORMATDESCRIPTOR),				// Size Of This Pixel Format Descriptor
		1,											// Version Number
		PFD_DRAW_TO_WINDOW |						// Format Must Support Window
		PFD_SUPPORT_OPENGL |						// Format Must Support OpenGL
		PFD_DOUBLEBUFFER,  							// Must Support Double Buffering
		PFD_TYPE_RGBA,								// Request An RGBA Format
		24,											// Select Our Color Depth
		0, 0, 0, 0, 0, 0,							// Color Bits Ignored
		0,											// No Alpha Buffer
		0,											// Shift Bit Ignored
		0,											// No Accumulation Buffer
		0, 0, 0, 0,									// Accumulation Bits Ignored
		32,											// 32Bit Z-Buffer (Depth Buffer)  
		0,											// No Stencil Buffer
		0,											// No Auxiliary Buffer
		PFD_MAIN_PLANE,								// Main Drawing Layer
		0,											// Reserved
		0, 0, 0										// Layer Masks Ignored
	};

	HWND hWND = this->GetSafeHwnd();
	HDC hDC = ::GetDC(hWND);
	m_pDC = new CClientDC(this);
	// 选择合适的Device Context像素点格式
	if (!(PixelFormat=ChoosePixelFormat(hDC,&pfd)))		// Did Windows Find A Matching Pixel Format?
	{							
		::MessageBox(NULL,"Can't Find A Suitable PixelFormat.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;									// Return FALSE
	}
	// 设置新的Device Context像素点格式
	if(!SetPixelFormat(hDC,PixelFormat,&pfd))			// Are We Able To Set The Pixel Format?
	{
		::MessageBox(NULL,"Can't Set The PixelFormat.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;									// Return FALSE
	}
	// 根据当前的Device Context得到rending context
	if (!(this->m_hGLContext=wglCreateContext(hDC)))	// Are We Able To Get A Rendering Context?
	{
		//KillGLWindow();								// Reset The Display
		::MessageBox(NULL,"Can't Create A GL Rendering Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;									// Return FALSE
	}
	// 设置当前Device context 的rendering context
	if(!wglMakeCurrent(hDC,this->m_hGLContext))			// Try To Activate The Rendering Context
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

int CvgFrameWorkView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码

	this->InitGLContext();

	vgKernel::OpenGLSupport::initialiseOpenGLExtension();

	vgGlobal::GlobalConsole::getSingleton().initAfterOpenGLSetup();

	this->SetTimer(1, 15, NULL);

	vgKernel::SelectManager::getSingleton();

	return 0;
}

void CvgFrameWorkView::OnDestroy()
{
	CView::OnDestroy();

	vgGlobal::GlobalConsole::getSingleton().uninitBeforeOpenGLDestroy();


	this->ReleaseGLContext();
	// TODO: 在此处添加消息处理程序代码
}

void CvgFrameWorkView::ReleaseGLContext(void)
{
	if (this->m_hGLContext)										// Do We Have A Rendering Context?
	{
		if (!wglMakeCurrent(NULL,NULL))							// Are We Able To Release The DC And RC Contexts?
		{
			::MessageBox(NULL,"Release Of DC And RC Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		}

		if (!wglDeleteContext(this->m_hGLContext))				// Are We Able To Delete The RC?
		{
			::MessageBox(NULL,"Release Rendering Context Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		}
		this->m_hGLContext=NULL;								// Set RC To NULL
	}

	if (m_pDC)
		delete m_pDC;
}

void CvgFrameWorkView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	int height = cy;
	int width = cx;

	if (height==0)										// Prevent A Divide By Zero By
	{
		height=1;										// Making Height Equal One
	}

	glViewport(0, 0, width, height);						// Reset The Current Viewport

	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix

	// Calculate The Aspect Ratio Of The Window
	gluPerspective(45.0f,(GLfloat)width/(GLfloat)height,0.1f,10000.0f);

// 	s_window_width = width;
// 	s_window_height = height;

	vgKernel::SelectManager::getSingleton().SetViewSize(cx, cy);

	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glLoadIdentity();									// Reset The Modelview Matrix
	//glDrawBuffer(GL_BACK);
}

BOOL CvgFrameWorkView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	//return CView::OnEraseBkgnd(pDC);
	return true;
}

void CvgFrameWorkView::RenderScene(void)
{
// 	AfxGetApp()->m_hInstance;
// 	AfxGetMainWnd()->PostMessage(WM_CLOSE, 0, 0);
	vgKernel::InputSystem::getSingleton().UpdateInput();

	vgGlobal::GlobalConsole::getSingleton().renderBegin();

	static float SunSlfRot;
	static float EarthCommonRot;
	static float EarthSlfRot;
	static float MoonCommonRot;
	static float MoonSlfRot;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear Screen And Depth Buffer
	glLoadIdentity();	

	// Reset The Current Modelview Matrix
	//gluLookAt(0,0,0, 10, 10, 10, 0, 1, 0);
	//glColor3f(1.0f, 0.0f, 0.0f);
	//glTranslatef(0.f, 0.f, -6.0f);


	vgGlobal::GlobalConsole::getSingleton().setupRenderEnvironment();

	vgGlobal::GlobalConsole::getSingleton().renderPrimitives();

	vgKernel::SelectManager::getSingleton().RenderSelected();



	glLineWidth(0.1f);

	//GLfloat fExtent = 20.f;
	//GLfloat fStep	= 1.f;
	//GLint	iLine;

	//glPushMatrix();
	glDisable(GL_TEXTURE_2D);
	//glBegin(GL_LINES);

	//// floor
	//for (iLine=-fExtent; iLine<=fExtent; iLine+=fStep)
	//{
	//	glVertex3f(iLine, -4.f, fExtent);
	//	glVertex3f(iLine, -4.f, -fExtent);

	//	//glVertex3f(fExtent, -4.f, iLine);
	//	//glVertex3f(-fExtent, -4.f, iLine);
	//}

	//glEnd();
	//glPopMatrix();



	vgGlobal::GlobalConsole::getSingleton().renderEnd();





	glFinish();
	SwapBuffers(m_pDC->GetSafeHdc());

}

void CvgFrameWorkView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	RenderScene();
	CView::OnTimer(nIDEvent);
}

void CvgFrameWorkView::OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/)
{
	// TODO: 在此处添加消息处理程序代码
}

void TestData()
{
// 	float i, j;
// 	GLfloat rad  = 10;
// 	GLfloat space = 10;
// 	int pa = 100;
// 
// 	glTranslated(0.f, 0.f, -pa);
// 
// 	for(j=-pa; j<=pa; j+=5)
// 	{
// 		glTranslatef(0.f, 0.f, 10);
// 		glPushMatrix();
// 		glTranslatef(-pa, 0.f, 0.f);
// 		for (i=-pa; i<=pa; i+=5)
// 		{
// 			//glutSolidSphere(2.0, 20.0, 20.0);
// 			glTranslatef(5, 0.0f, 0.f);		//平台的定位
// 		}
// 		glPopMatrix();
// 
// 	}
}

void CvgFrameWorkView::OnVgmImportVgm()
{
	vgGlobal::GlobalFacade::getSingleton().importModelFile();
}

void CvgFrameWorkView::OnVgiImportVgi()
{
	vgGlobal::GlobalFacade::getSingleton().importImageFile();
}

void CvgFrameWorkView::OnVgmSaveVgm()
{
	vgGlobal::GlobalFacade::getSingleton().saveModelFileOnly();
}

void CvgFrameWorkView::OnVgmiSaveVgmVgi()
{
	vgGlobal::GlobalFacade::getSingleton().saveModelAndImage();
}

void CvgFrameWorkView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	TRACE("On mouse db click position -- %d %d \n", point.x, point.y);
	vgKernel::InputSystem::getSingleton().OnLButtonDbClick(nFlags,point);

	CView::OnLButtonDblClk(nFlags, point);
}

void CvgFrameWorkView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	vgKernel::InputSystem::getSingleton().OnLButtonDown(nFlags,point);

	CView::OnLButtonDown(nFlags, point);
}

void CvgFrameWorkView::OnMove(int x, int y)
{
	CView::OnMove(x, y);
	// TODO: 在此处添加消息处理程序代码
}

void CvgFrameWorkView::OnLButtonUp(UINT nFlags, CPoint point)
{
	vgKernel::InputSystem::getSingleton().OnLButtonUp(nFlags,point);

	CView::OnLButtonUp(nFlags, point);
}

void CvgFrameWorkView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	vgKernel::InputSystem::getSingleton().OnMouseMove(nFlags,point);
	CView::OnMouseMove(nFlags, point);
}

void CvgFrameWorkView::OnVgterrainWireframe()
{
	glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
}

void CvgFrameWorkView::OnVgterrainNowireframe()
{
	glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
}

void CvgFrameWorkView::OnVgterrainTurnon()
{
	vgTerrain::TerrainManager::getSingleton().turnOnRenderFlag();
}

void CvgFrameWorkView::OnActivateApp(BOOL bActive, DWORD dwThreadID)
{
	CView::OnActivateApp(bActive, dwThreadID);
	
	if (bActive)
	{
		VGK_TRACE("View 获得焦点");
	}
	else
	{
		VGK_TRACE("View 失去焦点");
	}
	// TODO: 在此处添加消息处理程序代码
}


LRESULT CvgFrameWorkView::OnRender(WPARAM wParam, LPARAM lParam)
{
	// TODO: 处理用户自定义消息
	RenderScene();
	TRACE("Render \n");
	SendMessage(VG_MSG_RENDER, 0, 0);
	return 0;
} 
void CvgFrameWorkView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类
}

static UINT RenderThread(LPVOID pParam)
{
	while (true)
	{
		g_renderCriticalArea.Lock();
		if (g_threadFlag.bModifyFlag)
		{
			if (g_threadFlag.bResize)
			{

			}

			if (g_threadFlag.bTerminate)
			{
				g_renderCriticalArea.Unlock();
				return 0;
			}
		}
		g_renderCriticalArea.Unlock();

		//RenderScene();
	}
	
}
void CvgFrameWorkView::OnVgterrainConvertDemToVgtr()
{
	vgTerrain::TerrainManager::getSingleton().selectDemsToVgtr();
}

void CvgFrameWorkView::OnVgterrainConvertVgtrHeightmap()
{
	vgTerrain::TerrainManager::getSingleton().convertVgtrToHeightImage();
}
