/*
** Created by Lesky Zhou
** 
*/
#pragma once
#if 0
#include <BCGPMenuBar.h>

typedef std::map<UINT, UINT>				CommandToMessage;
typedef std::map<UINT, BOOL>				CommandCheckMessage;
typedef std::map<UINT, BOOL>				CommandEnableMessage;

extern CWnd *								s_CommandWnd ;
extern CommandToMessage						s_CommandToMessage ; 
extern CommandCheckMessage					s_CommandCheckMessage;
extern CommandEnableMessage					s_CommandEnableMessage;
extern CBCGPMenuBar*						s_pMenuBar;

// CCommandWnd 响应窗口事件
class CCommandWnd : public CWnd
{
	DECLARE_DYNAMIC(CCommandWnd)

public:
	CCommandWnd();
	virtual ~CCommandWnd();

protected:
	afx_msg LRESULT OnVgpNewPlan( WPARAM wParam, LPARAM lParam ) ;
	afx_msg LRESULT OnVgpNewArea( WPARAM wParam, LPARAM lParam ) ;
	afx_msg LRESULT OnVgpFromPlan( WPARAM wParam, LPARAM lParam ) ;
	afx_msg LRESULT OnVgpShowPlan( WPARAM wParam, LPARAM lParam ) ;
	afx_msg LRESULT OnVgpQueryGreenRatio( WPARAM wParam, LPARAM lParam ) ;
	afx_msg LRESULT OnVgpQueryPlotRatio( WPARAM wParam, LPARAM lParam ) ;
	afx_msg LRESULT OnVgpEditMode( WPARAM wParam, LPARAM lParam ) ;

	DECLARE_MESSAGE_MAP()
};


#endif