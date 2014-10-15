#pragma once

#include <resource.h>
#include <vgKernel/vgkRendererManager.h>
#include "vgKernel/vgkStringUtility.h"

// CDlgFindObject dialog

class VGDEP_EXPORT CDlgFindObject : public CDialog
{
	DECLARE_DYNAMIC(CDlgFindObject)

public:
	CDlgFindObject(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgFindObject();

// Dialog Data
	enum { IDD = IDD_DLG_FINDOBJECT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CString m_SearchName;
	vgKernel::RendererQueue m_ResultQueue;
	int nIndex;
	bool initialed;
	int m_checkMatch;
	int m_checkTowardUp;
public:
	afx_msg void OnBnClickedFindNext();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnEnChangeObjectName();
	afx_msg void OnBnClickedCheckMatch();
	afx_msg void OnBnClickedCheckTowardup();
};
