#pragma once
#include "afxcmn.h"

#include "resource.h"

#include "vgImportListCtrl.h"
#include "vgImportListCtrl2.h"

#include "TextProgressCtrl.h"

#include <vgKernel/vgkProcessObserver.h>

#include "TaskProgressDlg.h"

using namespace vgKernel;




// WizardPage2 dialog

class WizardPage2 : public CPropertyPage, public vgKernel::ProcessObserver
{
	DECLARE_DYNAMIC(WizardPage2)

public:
	WizardPage2();
	virtual ~WizardPage2();


// Dialog Data
	enum { IDD = IDD_WIZARDPAGE2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnSetActive();
	CImportListCtrl _importList;
	CImportListCtrl2 _importList2;


	int						m_nPos;
	int						m_nTotalTasks;
	int						m_currentTaskID;
	CStringArray			m_sTaskList;
	CTaskProgressDialog		*m_pTaskDlg;

	int m_CurrentFileID;

	afx_msg void OnBnClickedImport();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedImportImg();
	afx_msg void OnBnClickedClearAll();
	virtual BOOL OnKillActive();
	virtual LRESULT OnWizardNext();
	

	CString _progressMsg;


	virtual void onStart( const String& text , const int& range_lower , 
		const int& range_upper );

	// 显示进度.0到100之间
	virtual void onNotify( const String& msg , 
		const int& process_pos );

	virtual void onFinish( const String& msg );
	afx_msg void OnBnClickedImport2();
	afx_msg void OnBnClickedClearAll2();
	int _genMeshOverview;
	int _genTexOverview;
};
