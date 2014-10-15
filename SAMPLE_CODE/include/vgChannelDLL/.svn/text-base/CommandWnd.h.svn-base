/*
** Created by FengYK
** date 2009/10/24	19:25
*/
#pragma once

typedef std::map<UINT, UINT>              CommandToTheMessage;
typedef std::map<UINT, UINT>				CommandToMessage;
typedef std::map<UINT, BOOL>				CommandCheckMessage;
typedef std::map<UINT, BOOL>				CommandEnableMessage;

extern CWnd *								s_CommandWnd ;
extern CommandToMessage						s_CommandToMessage ; 
extern CommandCheckMessage					s_CommandCheckMessage;
extern CommandEnableMessage					s_CommandEnableMessage;
extern CBCGPMenuBar*						s_pMenuBar;

//extern CommandToTheMessage                  s_CommandToTheMessage;

// CCommandWnd 响应窗口事件
class CCommandWnd : public CWnd
{
	DECLARE_DYNAMIC(CCommandWnd)

public:
	CCommandWnd();
	virtual ~CCommandWnd();

protected:

	afx_msg LRESULT OnChannelLeft( WPARAM wParam, LPARAM lParam ) ;
	afx_msg LRESULT OnChannelServer( WPARAM wParam, LPARAM lParam ) ;
	afx_msg LRESULT OnChannelCancel( WPARAM wParam, LPARAM lParam ) ;
	afx_msg LRESULT OnChannelParam( WPARAM wParam, LPARAM lParam ) ;
	
	afx_msg LRESULT OnBlendonoff( WPARAM wParam, LPARAM lParam ) ;
	afx_msg LRESULT OnEdgeBlend( WPARAM wParam, LPARAM lParam ) ;

	afx_msg LRESULT OnNurbs( WPARAM wParam, LPARAM lParam ) ;
	afx_msg LRESULT OnLittlecorrect( WPARAM wParam, LPARAM lParam ) ;//ID_littleCorrect
	afx_msg LRESULT OnBlend( WPARAM wParam, LPARAM lParam ) ;

	//afx_msg LRESULT onMessageBox(WPARAM wParam, LPARAM lParam);


	DECLARE_MESSAGE_MAP()
	

};


