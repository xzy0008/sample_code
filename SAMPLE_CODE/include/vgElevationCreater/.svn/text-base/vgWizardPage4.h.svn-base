#pragma once

#include "resource.h"

#include <vgKernel/vgkProcessObserver.h>
#include <vgThreads/CriticalSection.h>
#include <vgThreads/ScopedLock.h>
#include "TaskProgressDlg.h"
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


	//----------------------------------------------------------------
	// 进度条

	int						m_nPos;
	int						m_nTotalTasks;
	int						m_curTaskID;
	CStringArray			m_sTaskList;
	CTaskProgressDialog		*m_pTaskDlg;

	//----------------------------------------------------------------


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


	int _genMesh;

	int _genImage;

	int _deleteTempFiles;

	int _genTexUseMesh;

	vgThreads::CriticalSection _taskDlgSect;
};
