




#ifndef __VGSCUSERPROPERTYPAGE_H__
#define __VGSCUSERPROPERTYPAGE_H__

	


#include <vgKernel/vgkForward.h>

#include "resource.h"


#define max(a,b)            (((a) > (b)) ? (a) : (b))
#define min(a,b)            (((a) < (b)) ? (a) : (b))

#include <afxole.h>
#include "BCGPTabWnd.h"
#include "BCGPPropertyPage.h"

/////////////////////////////////////////////////////////////////////////////
// UserPropertyPage dialog

class UserPropertyPage : public CBCGPPropertyPage
{
	DECLARE_DYNCREATE(UserPropertyPage)

	// Construction
public:
	UserPropertyPage();
	UserPropertyPage( const std::vector<std::string>& initscript );
	~UserPropertyPage();

	// Dialog Data
	//{{AFX_DATA(UserPropertyPage)
	enum { IDD = IDD_VGSC_USER_CONFIG };
	// NOTE - ClassWizard will add data members here.
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


	// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(UserPropertyPage)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(UserPropertyPage)
	// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnBnClickedBtnEditInit();
	CStatic m_wndTabLoc;


public:

	CBCGPTabWnd	m_wndTab;

	CEdit		m_wnd1;
	CEdit		m_wnd2;
	CEdit		m_wnd3;
	CEdit		m_wnd4;
	CEdit		m_wnd5;



	std::vector<CEdit*> _cedits;

	std::vector<std::string> _initScripts;

	std::vector<std::string> _scripts;

	virtual BOOL OnInitDialog();

	afx_msg LRESULT OnMoveTab(WPARAM wp, LPARAM lp);
	afx_msg LRESULT OnChangeActiveTab(WPARAM wp, LPARAM lp);
	afx_msg LRESULT OnChangingActiveTab(WPARAM wp, LPARAM lp);
	afx_msg void OnBnClickedSaveAndRun();

	void getDataFromTabs();

	bool isStringChanged();

	vgKernel::StringVector getScripts()
	{
		getDataFromTabs();
		return _scripts;
	}

	void clearAll();

protected:
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
public:
	afx_msg void OnBnClickedClearUserScript();
};





#endif // end of __VGSCUSERPROPERTYPAGE_H__
