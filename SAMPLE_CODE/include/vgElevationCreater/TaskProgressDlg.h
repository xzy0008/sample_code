#if !defined(AFX_TASKPROGRESSDLG_H__0382CDF5_1D0E_4735_827F_A9C342591617__INCLUDED_)
#define AFX_TASKPROGRESSDLG_H__0382CDF5_1D0E_4735_827F_A9C342591617__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TaskProgressDlg.h : header file
//
/////////////////////////////////////////////////////////////////////////////
// CTaskProgressDialog dialog

#include "TextProgressCtrl.h"

class CTaskProgressDialog : public CDialog
{
// Construction / Destruction
public:
    CTaskProgressDialog(UINT nCaptionID = 0);   // standard constructor
    ~CTaskProgressDialog();
public:
	BOOL IsSelectMode() const;
	void SetSelectMode(BOOL bSel = TRUE);
	void SetCurTask(int ID);
	void SetTasks(const CStringArray &sTaskList);

    BOOL Create(CWnd *pParent=NULL);

	void enableCanelButton( const bool& enable_it );

    // Checking for Cancel button
    BOOL CheckCancelButton();
    // Progress Dialog manipulation
    void SetStatus(LPCTSTR lpszMessage);
    void SetRange(int nLower,int nUpper);
	void getRange(int& nLower, int& nUpper);
    int  SetStep(int nStep);
    int  SetPos(int nPos);
	void setPosToMax();

    int  OffsetPos(int nPos);
    int  StepIt();
        
// Dialog Data
    //{{AFX_DATA(CTaskProgressDialog)
	enum { IDD = IDD_TASKPROGRESS_DLG };
	CListCtrl	m_TaskListCtrl;
    CTextProgressCtrl	m_Progress;
	//}}AFX_DATA

// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CTaskProgressDialog)
    public:
    virtual BOOL DestroyWindow();
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

// Implementation
protected:
	void InitTasks();
	void UpdateTasks();
	UINT			m_nCaptionID;
	int				m_nCurTaskID;
    int				m_nLower;
    int				m_nUpper;
    int				m_nStep;
    
    BOOL			m_bCancel;
    BOOL			m_bParentDisabled;
	BOOL			m_bSelMode;				// Selection mode or hot mode
	COLORREF		m_HilightColor;			// Color for the current task text
	COLORREF		m_TaskDoneColor;		// Color for the performed task text;
	COLORREF		m_TaskToDoColor;		// Color for the to-do task text;
	CStringArray	m_sTaskList;
	CImageList		m_ImageList;

    void ReEnableParent();

    virtual void OnCancel();
    virtual void OnOK() {}; 
    void UpdatePercent(int nCurrent);
    void PumpMessages();

    // Generated message map functions
    //{{AFX_MSG(CTaskProgressDialog)
    virtual BOOL OnInitDialog();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TASKPROGRESSDLG_H__0382CDF5_1D0E_4735_827F_A9C342591617__INCLUDED_)
