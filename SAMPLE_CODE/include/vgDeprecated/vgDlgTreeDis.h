#if !defined(AFX_VGTREEDIS_H__1B7FCA0F_FBA9_479A_9833_D401711CC9D3__INCLUDED_)
#define AFX_VGTREEDIS_H__1B7FCA0F_FBA9_479A_9833_D401711CC9D3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgTreeDis.h : header file
//
#include <resource.h>
/////////////////////////////////////////////////////////////////////////////
// DlgTreeDis dialog

class  VGDEP_EXPORT DlgTreeDis : public CDialog
{
// Construction
public:
	DlgTreeDis(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(DlgTreeDis)
	enum { IDD = IDD_TREEDIS };
	float	m_treedis;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DlgTreeDis)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(DlgTreeDis)
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()


public:

	bool  createAndShowDlg();

	void  setIsClickOK( bool bClick )
	{
		m_bIsClickOK = bClick;
	}

	bool  getIsClickOK()
	{
		return m_bIsClickOK;
	}
	
	float getTreeDis()
	{
		return m_treedis;
	}
	
	Vector3Vec* getPlantPosVec()
	{
		return &m_vPlantPos;
	}

private:
	bool m_bHasTreeDisConfigDlg;  //标识是否已经创建了对话框
	bool m_bIsClickOK;

	Vector3Vec m_vPlantPos;

public:
	afx_msg void OnEnChangeEdit1();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VGTREEDIS_H__1B7FCA0F_FBA9_479A_9833_D401711CC9D3__INCLUDED_)
