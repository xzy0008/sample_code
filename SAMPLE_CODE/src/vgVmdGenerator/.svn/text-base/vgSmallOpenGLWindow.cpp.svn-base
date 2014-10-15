

#include <vgStableHeaders.h>
#include "vgSmallOpenGLWindow.h"





SmallOpenGLWindow::SmallOpenGLWindow(void)
{
	m_fPosX = 0.0f;		// X position of model in camera view
	m_fPosY = 0.0f;		// Y position of model in camera view
	m_fZoom = 10.0f;	// Zoom on model in camera view
	m_fRotX = 0.0f;		// Rotation on model in camera view
	m_fRotY	= 0.0f;		// Rotation on model in camera view
	m_bIsMaximized = false;
	_arbMultisampleSupported = false;
	_arbMultisampleFormat = 0;

	_destroyed = false;
}

SmallOpenGLWindow::~SmallOpenGLWindow(void)
{
}

BEGIN_MESSAGE_MAP(SmallOpenGLWindow, CWnd)
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_CREATE()
	ON_WM_TIMER()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

void SmallOpenGLWindow::OnPaint()
{
	//CPaintDC dc(this); // device context for painting
	ValidateRect(NULL);
}

void SmallOpenGLWindow::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);

	if (0 >= cx || 0 >= cy || nType == SIZE_MINIMIZED) return;

	// Map the OpenGL coordinates.
	glViewport(0, 0, cx, cy);

	// Projection view
	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();

	// Set our current view perspective
	gluPerspective(45.0f, (float)cx / (float)cy, 0.01f, 100000.0f);

	// Model view
	glMatrixMode(GL_MODELVIEW);

	switch (nType)
	{
		// If window resize token is "maximize"
	case SIZE_MAXIMIZED:
		{
			assert(0&&"暂时用不到");

			// Get the current window rect
			GetWindowRect(m_rect);

			// Move the window accordingly
			MoveWindow(6, 6, cx - 14, cy - 14);

			// Get the new window rect
			GetWindowRect(m_rect);

			// Store our old window as the new rect
			m_oldWindow = m_rect;

			break;
		}

		// If window resize token is "restore"
	case SIZE_RESTORED:
		{
			// If the window is currently maximized
			if (m_bIsMaximized)
			{
				// Get the current window rect
				GetWindowRect(m_rect);

				// Move the window accordingly (to our stored old window)
				MoveWindow(m_oldWindow.left, m_oldWindow.top - 18, m_originalRect.Width() - 4, m_originalRect.Height() - 4);

				// Get the new window rect
				GetWindowRect(m_rect);

				// Store our old window as the new rect
				m_oldWindow = m_rect;
			}

			break;
		}
	}
}

int SmallOpenGLWindow::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1) return -1;

	initialize();

	return 0;
}

void SmallOpenGLWindow::OnDraw(CDC *pDC)
{
	// If the current view is perspective...
	glLoadIdentity();

	glTranslatef(0.0f, 0.0f, -m_fZoom);
	glTranslatef(m_fPosX, m_fPosY, 0.0f);
	glRotatef(m_fRotX, 1.0f, 0.0f, 0.0f);
	glRotatef(m_fRotY, 0.0f, 1.0f, 0.0f);

}

void SmallOpenGLWindow::OnTimer(UINT nIDEvent)
{
	switch (nIDEvent)
	{
	case 1:
		{

			// Clear color and depth buffer bits
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			// Draw OpenGL scene
			drawScene();

			// Swap buffers
			SwapBuffers(hdc);

			break;
		}

	default:
		break;
	}

	CWnd::OnTimer(nIDEvent);
}

void SmallOpenGLWindow::OnMouseMove(UINT nFlags, CPoint point)
{
	int diffX = (int)(point.x - m_fLastX);
	int diffY = (int)(point.y - m_fLastY);
	m_fLastX  = (float)point.x;
	m_fLastY  = (float)point.y;

	// Left mouse button
	if (nFlags & MK_LBUTTON)
	{
		m_fRotX += (float)0.5f * diffY;

		if ((m_fRotX > 360.0f) || (m_fRotX < -360.0f))
		{
			m_fRotX = 0.0f;
		}

		m_fRotY += (float)0.5f * diffX;

		if ((m_fRotY > 360.0f) || (m_fRotY < -360.0f))
		{
			m_fRotY = 0.0f;
		}
	}

	// Right mouse button
	else if (nFlags & MK_RBUTTON)
	{
		m_fZoom -= (float)0.1f * diffY;
	}

	// Middle mouse button
	else if (nFlags & MK_MBUTTON)
	{
		m_fPosX += (float)0.05f * diffX;
		m_fPosY -= (float)0.05f * diffY;
	}

	OnDraw(NULL);

	CWnd::OnMouseMove(nFlags, point);
}

void SmallOpenGLWindow::create(CRect rect, CWnd *parent)
{
	CString className = AfxRegisterWndClass(CS_HREDRAW | CS_VREDRAW | CS_OWNDC, NULL, (HBRUSH)GetStockObject(BLACK_BRUSH), NULL);

	CreateEx(0, className, "OpenGL", WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN, rect, parent, 0);

	// Set initial variables' values
	m_oldWindow	   = rect;
	m_originalRect = rect;

	hWnd = parent;
}

void SmallOpenGLWindow::initialize(void)
{
	// Initial Setup:
	//
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

	// Get device context only once.
	hdc = GetDC()->m_hDC;

	// Pixel format.
	m_nPixelFormat = ChoosePixelFormat(hdc, &pfd);
	SetPixelFormat(hdc, m_nPixelFormat, &pfd);

	// Create the OpenGL Rendering Context.
	hrc = wglCreateContext(hdc);
	wglMakeCurrent(hdc, hrc);


	//------------------------------------------
	// 检测multisample
	//------------------------------------------
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		/* Problem: glewInit failed, something is seriously wrong. */
		::MessageBox(NULL,"glewInit failed, something is seriously wrong.",
			"glew error occured.",MB_OK );
	}

	bool arbMultisampleSupported  = false;
	int arbMultisampleFormat = 0;

	if ( WGLEW_ARB_multisample  )
	{
		//------------------------------------------
		// 开启多重采样
		//------------------------------------------
		int		pixelFormat;
		int		valid;
		UINT	numFormats;
		float	fAttributes[] = {0,0};

		// These Attributes Are The Bits We Want To Test For In Our Sample
		// Everything Is Pretty Standard, The Only One We Want To 
		// Really Focus On Is The SAMPLE BUFFERS ARB And WGL SAMPLES
		// These Two Are Going To Do The Main Testing For Whether Or Not
		// We Support Multisampling On This Hardware.
		//int iAttributes[] =
		//{
		//	WGL_DRAW_TO_WINDOW_ARB,GL_TRUE,
		//	WGL_SUPPORT_OPENGL_ARB,GL_TRUE,
		//	WGL_ACCELERATION_ARB,WGL_FULL_ACCELERATION_ARB,
		//	WGL_COLOR_BITS_ARB,24,
		//	WGL_ALPHA_BITS_ARB,8,
		//	WGL_DEPTH_BITS_ARB,16,
		//	WGL_STENCIL_BITS_ARB,8,
		//	WGL_DOUBLE_BUFFER_ARB,GL_TRUE,
		//	WGL_SAMPLE_BUFFERS_ARB,GL_TRUE,
		//	WGL_SAMPLES_ARB,4,
		//	0,0
		//};
		int iAttributes[] =
		{
			WGL_DRAW_TO_WINDOW_ARB,GL_TRUE,
			WGL_SUPPORT_OPENGL_ARB,GL_TRUE,
			WGL_ACCELERATION_ARB,WGL_FULL_ACCELERATION_ARB,
			WGL_COLOR_BITS_ARB,24,
			WGL_ALPHA_BITS_ARB,8,
			WGL_DEPTH_BITS_ARB,16,
			WGL_STENCIL_BITS_ARB,8,
			WGL_DOUBLE_BUFFER_ARB,GL_TRUE,
			WGL_SAMPLE_BUFFERS_ARB,GL_TRUE,
			WGL_SAMPLES_ARB,2,
			0,0
		};

		// First We Check To See If We Can Get A Pixel Format For 4 Samples
		valid = wglChoosePixelFormatARB(hdc,iAttributes,fAttributes,1,&pixelFormat,&numFormats);

		// If We Returned True, And Our Format Count Is Greater Than 1
		if (valid && numFormats >= 1)
		{
			arbMultisampleSupported = true;
			arbMultisampleFormat = pixelFormat;	
		}
		else
		{
			// Our Pixel Format With 4 Samples Failed, Test For 2 Samples
			iAttributes[19] = 2;
			valid = wglChoosePixelFormatARB(hdc,iAttributes,fAttributes,1,&pixelFormat,&numFormats);
			if (valid && numFormats >= 1)
			{
				arbMultisampleSupported = true;
				arbMultisampleFormat = pixelFormat;	 
			}
		}
	}

	_arbMultisampleFormat = arbMultisampleFormat;
	_arbMultisampleSupported = arbMultisampleSupported;


	// Basic Setup:
	//
	// Set color to use when clearing the background.
	glClearColor(0.5f,0.6f,0.8f,1.0f);
	//glClearColor(1,0,0,1.0f);
	glClearDepth(1.0f);

	// Turn on backface culling
	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);

	// Turn on depth testing
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	// Send draw request
	OnDraw(NULL);
}

void SmallOpenGLWindow::drawScene(void)
{
	// Wireframe Mode
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glBegin(GL_QUADS);
	// Front Side
	glVertex3f( 1.0f,  1.0f, 1.0f);
	glVertex3f(-1.0f,  1.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glVertex3f( 1.0f, -1.0f, 1.0f);

	// Back Side
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f,  1.0f, -1.0f);
	glVertex3f( 1.0f,  1.0f, -1.0f);
	glVertex3f( 1.0f, -1.0f, -1.0f);

	// Top Side
	glVertex3f( 1.0f, 1.0f,  1.0f);
	glVertex3f( 1.0f, 1.0f, -1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glVertex3f(-1.0f, 1.0f,  1.0f);

	// Bottom Side
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f( 1.0f, -1.0f, -1.0f);
	glVertex3f( 1.0f, -1.0f,  1.0f);
	glVertex3f(-1.0f, -1.0f,  1.0f);

	// Right Side
	glVertex3f( 1.0f,  1.0f,  1.0f);
	glVertex3f( 1.0f, -1.0f,  1.0f);
	glVertex3f( 1.0f, -1.0f, -1.0f);
	glVertex3f( 1.0f,  1.0f, -1.0f);

	// Left Side
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f,  1.0f);
	glVertex3f(-1.0f,  1.0f,  1.0f);
	glVertex3f(-1.0f,  1.0f, -1.0f);
	glEnd();
}

bool SmallOpenGLWindow::destroy()
{
	if(::wglMakeCurrent (hdc,0) == FALSE)
	{
		AfxMessageBox(_T("Could not make RC non-current"));
	}

	::ReleaseDC (hWnd->m_hWnd, hdc);						// Release The Device Context
	hdc = 0;											// Zero The Device Context


	if(::wglDeleteContext (hrc)==FALSE)
	{
		AfxMessageBox(_T("Could not delete RC"));
	}

	hrc = NULL;

	return true;

}