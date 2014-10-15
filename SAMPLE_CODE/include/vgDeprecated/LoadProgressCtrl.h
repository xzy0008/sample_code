#ifndef _LOADPROGRESSCTRL_H
#define _LOADPROGRESSCTRL_H
#include "Resource.h"



// LoadProgressCtrl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLoadProgressCtrl window

class CLoadProgressCtrl : public CProgressCtrl
{
public:
	CLoadProgressCtrl();
	virtual ~CLoadProgressCtrl();

// Implementation
public:

	void SetRange(int nLower, int nUpper);
	int  SetPos(int nPos);
	int  SetStep(int nStep);
	int  SetPosWithRange(int nLower, int nUpper, float nStep);

protected:
	//{{AFX_MSG(CProgressST)
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif
