#pragma once

#include "resource.h"
#include "afxwin.h"
#include "TifView.h"
#include <vgTerritory/vgtDemAreaBag.h>




// WizardPage3 dialog

class WizardPage3 : public CPropertyPage
{
	DECLARE_DYNAMIC(WizardPage3)

public:
	WizardPage3();
	virtual ~WizardPage3();



// Dialog Data
	enum { IDD = IDD_WIZARDPAGE3 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnKillActive();
	virtual BOOL OnSetActive();
	CString _selectedFolder;
	afx_msg void OnBnClickedBtnSelectFolder();
	CString _selectOuputFolder;
	afx_msg void OnBnClickedBtnSelectOutputFolder();
//	afx_msg void OnCbnSelchangeComboScaleDemToImg();
	int _scaleDemToImgID;


public:


	TifView* pView;
	

	void checkAndSetNextBtn();

	int _scaleDemToImg;
	CComboBox _btnScaleDemToImg;
	virtual BOOL OnInitDialog();
	virtual LRESULT OnWizardNext();
	virtual LRESULT OnWizardBack();
	CString _terrainName;
	int _terrainNComboxID;

	int _terrainN;
	afx_msg void OnEnChangeTerrainName();
	afx_msg void OnCbnSelchangeComboScaleDemToImg();
	afx_msg void OnCbnSelchangeComboTerrainN();
	float _adjustCellsize;
	int _globalXNum;
};
