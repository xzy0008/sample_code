/*
** Created by Lesky Zhou
** 
*/
#pragma once
#if 0
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
	afx_msg LRESULT OnGisMeasurePoint( WPARAM wParam, LPARAM lParam ) ;
	afx_msg LRESULT OnGisMeasureDistance( WPARAM wParam, LPARAM lParam ) ;
	afx_msg LRESULT OnGisMeasureArea( WPARAM wParam, LPARAM lParam ) ;
	afx_msg LRESULT OnGisMeasureVolume( WPARAM wParam, LPARAM lParam ) ;


	DECLARE_MESSAGE_MAP()
};


#endif