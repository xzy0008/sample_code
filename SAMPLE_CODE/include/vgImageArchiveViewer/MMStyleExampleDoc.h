//*******************************************************************************
// COPYRIGHT NOTES
// ---------------
// This is a sample for BCGControlBar Library Professional Edition
// Copyright (C) 1998-2008 BCGSoft Ltd.
// All rights reserved.
//
// This source code can be used, distributed or modified
// only under terms and conditions 
// of the accompanying license agreement.
//*******************************************************************************
//
// MMStyleExampleDoc.h : interface of the CMMStyleExampleDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MMSTYLEEXAMPLEDOC_H__9D665688_4062_45C0_B8EA_5C2572AA5B6D__INCLUDED_)
#define AFX_MMSTYLEEXAMPLEDOC_H__9D665688_4062_45C0_B8EA_5C2572AA5B6D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define MMS_PLAY	1
#define MMS_PAUSE	2
#define MMS_OPEN	3
#define MMS_STOP	4

class CMMStyleExampleDoc : public CDocument
{
protected: // create from serialization only
	CMMStyleExampleDoc();
	DECLARE_DYNCREATE(CMMStyleExampleDoc)

	// Attributes
public:

	// Operations
public:

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMMStyleExampleDoc)
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

	// Implementation
public:
	virtual ~CMMStyleExampleDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

	// Generated message map functions
protected:
	//{{AFX_MSG(CMMStyleExampleDoc)
	// NOTE - the ClassWizard will add and remove member functions here.
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnFileOpen();
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MMSTYLEEXAMPLEDOC_H__9D665688_4062_45C0_B8EA_5C2572AA5B6D__INCLUDED_)
