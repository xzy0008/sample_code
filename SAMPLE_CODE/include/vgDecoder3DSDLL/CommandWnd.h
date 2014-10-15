/*
** Created by Lesky Zhou
** 
*/

#if 1


#pragma once

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
	afx_msg LRESULT onDecoder3DS( WPARAM wParam, LPARAM lParam ) ;
	afx_msg LRESULT onEncoder3DS( WPARAM wParam, LPARAM lParam ) ;

	DECLARE_MESSAGE_MAP()
};


#endif



