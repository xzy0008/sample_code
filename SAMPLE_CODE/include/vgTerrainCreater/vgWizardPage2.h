#pragma once
#include "afxcmn.h"

#include "resource.h"

#include "vgImportListCtrl.h"



using namespace vgKernel;




// WizardPage2 dialog

class WizardPage2 : public CPropertyPage
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

	int m_CurrentFileID;

	afx_msg void OnBnClickedImport();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedImportImg();
	afx_msg void OnBnClickedClearAll();
	virtual BOOL OnKillActive();
	virtual LRESULT OnWizardNext();
};
