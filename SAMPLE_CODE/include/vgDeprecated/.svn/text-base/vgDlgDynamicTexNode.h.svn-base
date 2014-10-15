#ifndef __VGDYDLGNAMICTEXTURENODE_H__
#define __VGDYDLGNAMICTEXTURENODE_H__



#include <vgEffect/vgDynamicTexNode.h>

/////////////////////////////////////////////////////////////////////////////
// DlgBrightfloor dialog
#include <resource.h>
class  VGDEP_EXPORT DlgDynamicTexNode : public CDialog
{
// Construction
public:

	DlgDynamicTexNode( vgMod::ModItemPtrVec& node_list , CWnd* pParent = NULL);
	vgMod::ModItemPtrVec _nodeList;
	vgMod::DynamicTexNode* _currentNode;

	//------------------------------------------
	// 编辑模式时
	// _waterNode != NULL
	// 于是,当_waterNode为NULL时,为创建water模式
	//------------------------------------------

// Dialog Data
	//{{AFX_DATA(DlgBrightfloor)
	enum { IDD = IDD_DYNAMICTEX_DLG };

	CString	m_watermodpath;
	CString	m_DecalMapPath;
	std::string m_DecalMapPath_s;
	std::string m_DecalMapPath_p;
	CString	m_BumpMap;
	std::string m_BumpMap_s;
	std::string m_BumpMap_p;

	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DlgBrightfloor)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(DlgBrightfloor)
	afx_msg void OnDecal();

	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();

	virtual BOOL OnInitDialog();
	CString _instruction;
	bool m_autoGenerateCubeMap;

	afx_msg void OnBnClickedCancel();
};

#endif // end of __VGDLGAVINODE_H__
