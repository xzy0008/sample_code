/*
** Created by Lesky Zhou
** 
*/
#pragma once
#if 0
class CBCGPMenuBar;

typedef std::map<UINT, UINT>				CommandToMessage;


extern CWnd *								s_CommandWnd ;
extern CBCGPMenuBar*						s_pMenuBar;

extern CommandToMessage					s_CommandToMessage ;

// CCommandWnd 响应窗口事件
class CCommandWnd : public CWnd
{
	DECLARE_DYNAMIC(CCommandWnd)

public:
	CCommandWnd();
	virtual ~CCommandWnd();

protected:
	afx_msg LRESULT OnSolarTurnOn( WPARAM wParam, LPARAM lParam ) ;
	afx_msg LRESULT OnSolarTurnOff( WPARAM wParam, LPARAM lParam ) ;
	afx_msg LRESULT OnSolarSetDirection( WPARAM wParam, LPARAM lParam ) ;
	afx_msg LRESULT OnSolarAnalysis( WPARAM wParam, LPARAM lParam ) ;


	DECLARE_MESSAGE_MAP()
};


#endif