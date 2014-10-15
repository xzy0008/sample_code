/*
** Created by Lesky Zhou
** 
*/
#pragma once
#if 0
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
	afx_msg LRESULT OnVtrLoad( WPARAM wParam, LPARAM lParam ) ;
	afx_msg LRESULT OnVtrBlend( WPARAM wParam, LPARAM lParam ) ;
	afx_msg LRESULT OnVtrCollision( WPARAM wParam, LPARAM lParam ) ;
	afx_msg LRESULT OnVtrRender( WPARAM wParam, LPARAM lParam ) ;
	afx_msg LRESULT OnVtrDropData( WPARAM wParam, LPARAM lParam ) ;
	afx_msg LRESULT OnVtrCutAla1(WPARAM wParam, LPARAM lParam) ;
	afx_msg LRESULT OnVtrCutAla2(WPARAM wParam, LPARAM lParam) ;
	afx_msg LRESULT OnVtrLeveling(WPARAM wParam, LPARAM lParam) ;
	afx_msg LRESULT OnVtrAttach(WPARAM wParam, LPARAM lParam) ;
	afx_msg LRESULT OnVtrMapOrigin(WPARAM wParam, LPARAM lParam) ;
	afx_msg LRESULT OnVtrRestore(WPARAM wParam, LPARAM lParam) ;
	afx_msg LRESULT OnVtrSaveas(WPARAM wParam, LPARAM lParam) ;

	DECLARE_MESSAGE_MAP()
};


#endif