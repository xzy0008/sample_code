

#ifndef __VGSCUSERSCRIPTCONFIG_H__
#define __VGSCUSERSCRIPTCONFIG_H__


#include <vgKernel/vgkForward.h>

#define max(a,b)            (((a) > (b)) ? (a) : (b))
#define min(a,b)            (((a) < (b)) ? (a) : (b))

#include "BCGPPropertySheet.h"
#include "vgscUserPropertyPage.h"


/////////////////////////////////////////////////////////////////////////////
// UserScriptConfig

class UserScriptConfig : public CBCGPPropertySheet
{
	DECLARE_DYNAMIC(UserScriptConfig)

// Construction
public:
	UserScriptConfig( vgKernel::StringVector input_scripts , 
		CWnd* pParentWnd );

// Attributes
public:
	UserPropertyPage m_Page1;
	//vgscUserPropertyPage2_userRenderBegin m_Page2;
	//vgscUserPropertyPage3_render m_Page3;
	//vgscUserPropertyPage4_renderEnd m_Page4;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(UserScriptConfig)
	//}}AFX_VIRTUAL

	virtual void OnDrawPageHeader (CDC* pDC, int nPage, CRect rectHeader);

// Implementation
public:
	virtual ~UserScriptConfig();

// Generated message map functions
protected:
	//{{AFX_MSG(UserScriptConfig)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:

protected:
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
};

/////////////////////////////////////////////////////////////////////////////


#endif // end of __VGSCUSERSCRIPTCONFIG_H__