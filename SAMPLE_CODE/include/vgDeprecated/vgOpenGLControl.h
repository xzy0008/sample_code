#pragma once
#include "afxwin.h"

#include <cassert>
#include <gl/glew.h>
#include <gl/wglew.h>

namespace vgCore{ 

	class  VGDEP_EXPORT OpenGLControl : public CWnd
	{
	public:
		bool destroy();
	private:
		// leven add
		bool _destroyed;

	public:
		/******************/
		/* Public Members */
		/******************/
		UINT_PTR m_unpTimer;
		// View information variables
		float	 m_fLastX;
		float	 m_fLastY;
		float	 m_fPosX;
		float	 m_fPosY;
		float	 m_fZoom;
		float	 m_fRotX;
		float	 m_fRotY;
		bool	 m_bIsMaximized;

	private:
		/*******************/
		/* Private Members */
		/*******************/
		// Window information
		CWnd  *hWnd;
		HDC   hdc;			
		HGLRC hrc;			
		int   m_nPixelFormat;
		CRect m_rect;
		CRect m_oldWindow;
		CRect m_originalRect;

	public:

		bool _arbMultisampleSupported;
		int _arbMultisampleFormat;

	public:
		OpenGLControl(void);
		virtual ~OpenGLControl(void);

		void create(CRect rect, CWnd *parent);

		//------------------------------------------
		// 注意!暂时负责检测multisample工作
		//------------------------------------------
		void initialize(void);
		virtual void drawScene(void);
/////////////////////////////////////////////////////		
		struct htime
		{
			LARGE_INTEGER start, hfreq;
		};
	
		
		int gl_data( void );
		int gl_init( void );
		void gl_draw( void );
		float timer( struct htime *t, int reset );


		int width, height;
		int info;
		int bmode;
		int rdown;
		int _done;
		int frames;
		GLuint font;
		GLfloat fps;
		GLfloat alpha;
		GLfloat rx, ry;
		GLfloat vx, vy;
		GLfloat dir[8][3];
		GLfloat phi[8][3];
		htime tv;
	
	private:

		GLuint m_2DTextList2;
		GLuint m_2DTextList;
//////////////////////////////////////////////////////////
	public:	
		// Added message classes:
		afx_msg void OnPaint();
		afx_msg void OnSize(UINT nType, int cx, int cy);
		afx_msg	void OnDraw(CDC *pDC);
		afx_msg int  OnCreate(LPCREATESTRUCT lpCreateStruct);
		afx_msg void OnTimer(UINT nIDEvent);
		afx_msg void OnMouseMove(UINT nFlags, CPoint point);

		DECLARE_MESSAGE_MAP()
////////////////////////////////////////////////////////////
	private:

		void Create2DTextLists2();
		void Create2DTextLists();

		void RenderScene();			//Render the Scene
	
	
	};

}