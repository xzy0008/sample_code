#pragma once

#include "vgMeshEntry.h"
#include "resource.h"
// vgMeshPad 对话框

#include "vgScrollHelper.h"

// CDialog 要在vgBasedTabPage前面
class vgMeshPad :public CDialog, public vgBasedTabPage
{
	DECLARE_DYNAMIC(vgMeshPad)

public:
	vgMeshPad(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~vgMeshPad();

	
	string GetTitle() { return "Mesh编辑"; }

	CWnd* GetWnd() { return this; }

	void ConnectNode(vgBaseEntry* node);

	// 对话框数据
	enum { IDD = NIDD_MESHEDIT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	
	vgMeshEntry*  p_meshEntry;
	vgBaseEntry*  p_meshNode;

	CScrollHelper* m_scrollHelper;

	DECLARE_MESSAGE_MAP()
public:
// 	virtual void PostNcDestroy();

// 	afx_msg void OnBnClickedButton2();
// 
 	afx_msg int  OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
 	afx_msg void OnPaint();
 	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
 	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
 	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
 	afx_msg void OnSize(UINT nType, int cx, int cy);

private:
public:
	afx_msg void OnBnClickedMeshpadButton1();
	virtual BOOL OnInitDialog();
};
