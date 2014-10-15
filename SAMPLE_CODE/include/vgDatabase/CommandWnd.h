/*
** Created by Lesky Zhou
** 
*/
#pragma once
#if 0

#include <vgDatabase/vgDlgCondition.h>

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
	afx_msg LRESULT OnDbConnect( WPARAM wParam, LPARAM lParam ) ;
	afx_msg LRESULT OnDbDisconnect( WPARAM wParam, LPARAM lParam ) ;
	afx_msg LRESULT OnDbCondition( WPARAM wParam, LPARAM lParam ) ;

	afx_msg LRESULT OnDelDlgMsg( WPARAM wParam, LPARAM lParam );

	DECLARE_MESSAGE_MAP()

public:
	DBCondition* m_dbCondition;

};


#endif