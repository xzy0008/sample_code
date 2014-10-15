


#ifndef __VGSMALLOPENGLWINDOW_H__
#define __VGSMALLOPENGLWINDOW_H__


#include "afxwin.h"

#include <cassert>
#include <gl/gl.h>
#include <gl/glu.h>


class SmallOpenGLWindow : public CWnd
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
	SmallOpenGLWindow(void);
	virtual ~SmallOpenGLWindow(void);

	void create(CRect rect, CWnd *parent);

	//------------------------------------------
	// 注意!暂时负责检测multisample工作
	//------------------------------------------
	void initialize(void);
	virtual void drawScene(void);

	// Added message classes:
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg	void OnDraw(CDC *pDC);
	afx_msg int  OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);

	DECLARE_MESSAGE_MAP()
};

	


#endif // end of __VGSMALLOPENGLWINDOW_H__