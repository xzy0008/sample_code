// outputbar.h : interface of the COutputBar class
//
/////////////////////////////////////////////////////////////////////////////

#pragma once

#include <vgUIController/vgColorEdit.h>
#include <vgKernel/vgkLogManager.h>
#include <vgKernel/vgkLog.h>
#include <vgKernel/vgkSharePtr.h>

class AFX_EXT_CLASS vgOutputBar : public CBCGPDockingControlBar, public vgKernel::LogListener
{
public:
	vgOutputBar();

// Attributes
protected:

	//CListCtrl				m_wndList;
	CColorEdit				m_editLog;

	std::deque<vgKernel::SharePtr<String>>		m_contentList;

	CFont					*m_pFont;
// Operations
public:
	
	void AddContent( const String& content);
	void ClearContent();

	void messageLogged( const String& message, vgKernel::LogMessageLevel lml, bool maskDebug, const String &logName );

	void SetBkColor(COLORREF clr)
	{
		m_editLog.SetBkColor(clr);
	}

	void SetTextColor(COLORREF clr)
	{
		m_editLog.SetTextColor(clr);
	}

	//string &replace_all(string &str, const string &old_value, const string &new_value);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COutputBar)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~vgOutputBar();

// Generated message map functions
protected:
	//{{AFX_MSG(COutputBar)
	afx_msg int		OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void	OnSize(UINT nType, int cx, int cy);
	afx_msg void	OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDestroy();
};

/////////////////////////////////////////////////////////////////////////////
