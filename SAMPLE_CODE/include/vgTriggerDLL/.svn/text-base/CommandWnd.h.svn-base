/*
** Created by kinghj
** date 2009/12/7	19:25
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

	afx_msg LRESULT OnTriggerConvert(WPARAM wparam, LPARAM lparam);
	afx_msg LRESULT OnTriggerEnable(WPARAM wparam, LPARAM lparam);
	afx_msg LRESULT OnTriggerEditEvent(WPARAM wparam, LPARAM lparam);

	DECLARE_MESSAGE_MAP()
};


