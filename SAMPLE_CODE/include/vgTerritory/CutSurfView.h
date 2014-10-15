#pragma once

#include <vector>
#include <stack>
#include <GdiPlus.h>
using namespace Gdiplus;
// CutSurfView视图
typedef std::vector< vgKernel::Vec3 > Vec3Vector;

class CutSurfView : public CView
{
	DECLARE_DYNCREATE(CutSurfView)

protected:
	CutSurfView();           // 动态创建所使用的受保护的构造函数
public:
	virtual ~CutSurfView();


#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif


protected:
	//virtual void OnInitialUpdate();     // 构造后的第一次

	DECLARE_MESSAGE_MAP()
	
public:

protected:

public:
	HGLRC m_hRC;	//Rendering Context
	//CDC* m_pDC;		//Device Context
	float fLeft;
	float fRight;
	float fButtom;
	float fTop;
	BOOL drawMouseLine;
	int mousPosX;
	int mousPosY;
	
	ULONG_PTR   m_nGdiplusToken;
	CFont m_font;
	typedef std::vector <vgKernel::Vec3*> htPoint;
	htPoint vec_htPoint;
	std::stack <vgKernel::Vec3*> m_tempPoint_stck;

	Vec3Vector* heightPoint;

	float lineLength;

public:
	void Render();
	void setCoordinate();
	void render_Height();
	
	


public:
	afx_msg void OnDestroy();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
protected:
	virtual void OnDraw(CDC* pDC);
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnOpendlg();
	afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnMButtonDblClk(UINT nFlags, CPoint point);
};


