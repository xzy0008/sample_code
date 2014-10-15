#ifndef __VGDYDLGNAMICBILLBOARDNODE_H__
#define __VGDYDLGNAMICBILLBOARDNODE_H__



#include <vgEffect/vgDynamicBillboardNode.h>

/////////////////////////////////////////////////////////////////////////////
// DlgBrightfloor dialog
#include <resource.h>
class VGDEP_EXPORT DlgDynamicBillboardNode : public CDialog
{
// Construction
public:

	DlgDynamicBillboardNode( std::vector<vgMod::DynamicBillboardNode*>& node_list , CWnd* pParent = NULL);
	std::vector<vgMod::DynamicBillboardNode*> _nodeList;
	vgMod::DynamicBillboardNode* _currentNode;

	DlgDynamicBillboardNode(CWnd* pParent = NULL);
	//------------------------------------------
	// 编辑模式时
	// _waterNode != NULL
	// 于是,当_waterNode为NULL时,为创建water模式
	//------------------------------------------

// Dialog Data
	//{{AFX_DATA(DlgBrightfloor)
	enum { IDD = IDD_DYNAMICBILLBOARD_DLG };

	CString	m_watermodpath;
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
	int m_autoGenerateCubeMap;

	float		m_dynheight;
	float		m_dynwidth;
	CString	    m_DtxFilePath;

	float		m_dynheight_old;
	float		m_dynwidth_old;
	CString	    m_DtxFilePath_old;

	afx_msg void OnBnClickedCancel();
	afx_msg void OnEnChangeEditHeight();
	afx_msg void OnEnChangeEditWidth();
};

#endif // end of __VGDLGAVINODE_H__
