#pragma once

#include "resource.h"

#include <vgKernel/vgkProcessObserver.h>
#include "afxwin.h"

// WizardPage4 dialog

class WizardPage4 : public CPropertyPage,
	public vgKernel::ProcessObserver
{
	DECLARE_DYNAMIC(WizardPage4)

public:
	WizardPage4();
	virtual ~WizardPage4();

// Dialog Data
	enum { IDD = IDD_WIZARDPAGE4 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CProgressCtrl _processBarOfResizing;
	CProgressCtrl _processBarOfCutting;
	CProgressCtrl _processBarOfVgtr;
	CProgressCtrl _processBarOfClean;

	CString* _currentMsg;
	CProgressCtrl* _currentProcessBar;

	virtual void onStart( const String& text , const int& range_lower , 
		const int& range_upper );


	// 显示进度.0到100之间
	virtual void onNotify( const String& msg , 
		const int& process_pos );

	virtual void onFinish( const String& msg );


	virtual BOOL OnInitDialog();
	virtual BOOL OnSetActive();
	afx_msg void OnBnClickedProcessStart();
	CButton _startBtn;
	CString _processMsg;
	CString _showMsgResize;
	CString _showMsgCut;
	CString _showMsgVgtr;
	CString _showMsgClean;
};
