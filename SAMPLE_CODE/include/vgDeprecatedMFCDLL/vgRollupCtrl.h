
#pragma once

#include <afxtempl.h>
#include "vgBasedTabPage.h"
#include "vgBaseEntry.h"
#include "vgMeshDialogs.h"

/////////////////////////////////////////////////////////////////////////////
// CRollupCtrl structures and defines

	struct RC_PAGEINFO {
		CString		cstrCaption;
		CWnd*			pwndTemplate;
		CButton*	pwndButton;
		CButton*	pwndGroupBox;
		BOOL			bExpanded;
		BOOL			bEnable;
		BOOL			bAutoDestroyTpl;
		WNDPROC 	pOldDlgProc;		//Old wndTemplate(Dialog) window proc
		WNDPROC 	pOldButProc;		//Old wndTemplate(Button) window proc
	};

	#define	RC_PGBUTTONHEIGHT				18
	#define	RC_SCROLLBARWIDTH				6
	#define RC_CURSOR								MAKEINTRESOURCE(IDC_SIZENS)
	#define RC_MINCOLUMNWIDTH				16
	#define	RC_GRPBOXINDENT					6
	#define	RC_SCROLLBARCOLOR				RGB(150,180,180)

	//TrackMenu IDs
	#define RC_MID_EXPANDALL				0x100
	#define RC_MID_COLLAPSEALL			0x101
	#define RC_MID_STARTPAGES				0x102

/////////////////////////////////////////////////////////////////////////////
// CRollupCtrl window

class CRollupCtrl : public CWnd, public vgBasedTabPage
{
	DECLARE_DYNCREATE(CRollupCtrl)

public:

	// Constructor-Destructor
	CRollupCtrl();
	virtual ~CRollupCtrl();

	
	// extends from vgBasedTabPage
	string GetTitle() { return "3d max"; };

	virtual CWnd* GetWnd() { return this; }

	virtual void ConnectNode(vgBaseEntry* node)  {}

	// Methods
	BOOL	Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID);

	int		InsertPage(const char* caption, CDialog* pwndTemplate, BOOL bAutoDestroyTpl=TRUE, int idx=-1);	//Return page zero-based index
	int		InsertPage(const char* caption, UINT nIDTemplate, int idx=-1);	//Return page zero-based index
	int		InsertPage(const char* caption, UINT nIDTemplate, CRuntimeClass* rtc, int idx=-1);	//Return page zero-based index

	void	RemovePage(int idx);	//idx is a zero-based index
	void	RemoveAllPages();

	void	ExpandPage(int idx, BOOL bExpand=TRUE, BOOL bScrollToPage=TRUE);	//idx is a zero-based index
	void	ExpandAllPages(BOOL bExpand=TRUE);

	void	EnablePage(int idx, BOOL bEnable=TRUE);	//idx is a zero-based index
	void	EnableAllPages(BOOL bEnable=TRUE);

	const RC_PAGEINFO*	GetPageInfo(int idx);

	// New v1.01 Methods
	void	ScrollToPage(int idx, BOOL bAtTheTop=TRUE);
	int		MovePageAt(int idx, int newidx);	//newidx can be equal to -1 (move at end)

	BOOL	IsPageExpanded(int idx);
	BOOL	IsPageEnabled(int idx);
	int		GetPagesCount()		{ return (int)m_PageList.GetSize(); }

	// New v1.02 Methods
	BOOL	IsAutoColumnsEnabled()								{ return m_bEnabledAutoColumns;	}
	void	EnableAutoColumns(BOOL bEnable=TRUE);
	BOOL	SetColumnWidth(int nWidth);						//nWidth must be superior to RC_MINCOLUMNWIDTH
	BOOL	SetPageCaption(int idx, LPCSTR caption);

	//Helpers
	void	RecalLayout();

protected:

	// Internal methods
	int		GetPageIdxFromButtonHWND(HWND hwnd);
	void	_ExpandPage(RC_PAGEINFO* pi, BOOL bExpand);
	void	_EnablePage(RC_PAGEINFO* pi, BOOL bEnable);
	int		_InsertPage(const char* caption, CDialog* dlg, int idx, BOOL bAutoDestroyTpl);
	void	_RemovePage(int idx);

	// Datas
	CString	m_strMyClass;
	CArray	<RC_PAGEINFO*,RC_PAGEINFO*>		m_PageList;
	int			m_StartYPos, m_PageHeight;
	int			m_OldMouseYPos, m_SBOffset;
	CBrush	m_cbrush;
	CMenu		m_cmenuCtxt;
	int			m_nColumnWidth;
	BOOL		m_bEnabledAutoColumns;

	// Window proc
	static LRESULT CALLBACK DlgWindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK ButWindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

public:

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRollupCtrl)
	protected:
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

	// Generated message map functions
protected:
	//{{AFX_MSG(CRollupCtrl)
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnContextMenu( CWnd* pWnd, CPoint pos );
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
protected:
	CDispColorDlg* pwndHide;
	CDispPropDlg*  pPropDlg;
};

