#pragma once

// vgActiveXPropPage.h : Declaration of the CvgActiveXPropPage property page class.


// CvgActiveXPropPage : See vgActiveXPropPage.cpp for implementation.

class CvgActiveXPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CvgActiveXPropPage)
	DECLARE_OLECREATE_EX(CvgActiveXPropPage)

// Constructor
public:
	CvgActiveXPropPage();

// Dialog Data
	enum { IDD = IDD_PROPPAGE_VGACTIVEX };

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Message maps
protected:
	DECLARE_MESSAGE_MAP()
};

