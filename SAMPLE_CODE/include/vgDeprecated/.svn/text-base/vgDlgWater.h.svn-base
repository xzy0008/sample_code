#if !defined(AFX_VGDLG_WATER_H__447DDB2E_5FF5_4159_AE74_16576B062AC8__INCLUDED_)
#define AFX_VGDLG_WATER_H__447DDB2E_5FF5_4159_AE74_16576B062AC8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgWater.h : header file
//


#include <vgEffect/vgWaterNode.h>

#include <vgMod/vgObjNode.h>

/////////////////////////////////////////////////////////////////////////////
// DlgWater dialog
#include <resource.h>
class DlgWater : public CDialog
{
// Construction
public:
	//DlgWater(vgMod::WaterNode* water_node = NULL , CWnd* pParent = NULL);   // standard constructor



	DlgWater( vgMod::ModItemPtrVec& node_list , CWnd* pParent = NULL);
	vgMod::ModItemPtrVec _nodeList;
	vgMod::WaterNode* _currentNode;

	//------------------------------------------
	// 编辑模式时
	// _waterNode != NULL
	// 于是,当_waterNode为NULL时,为创建water模式
	//------------------------------------------


	void onClickEditMode();




// Dialog Data
	//{{AFX_DATA(DlgWater)
	enum { IDD = IDD_WATERDIG };
	CString	m_watermodpath;
	CString	m_DecalMapPath;
	std::string m_DecalMapPath_s;
	std::string m_DecalMapPath_p;
	CString	m_BumpMap;
	std::string m_BumpMap_s;
	std::string m_BumpMap_p;

	CString	m_EnvMap2;
	CString	m_EnvMap1;
	CString	m_EnvMap3;
	CString	m_EnvMap4;
	CString	m_EnvMap5;
	CString	m_EnvMap6;

	// s为short,即basename
	std::string	m_EnvMap2_s;
	std::string	m_EnvMap1_s;
	std::string	m_EnvMap3_s;
	std::string	m_EnvMap4_s;
	std::string	m_EnvMap5_s;
	std::string	m_EnvMap6_s;

	// p为path,即路径
	std::string	m_EnvMap2_p;
	std::string	m_EnvMap1_p;
	std::string	m_EnvMap3_p;
	std::string	m_EnvMap4_p;
	std::string	m_EnvMap5_p;
	std::string	m_EnvMap6_p;

	float	m_BumpScale;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DlgWater)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(DlgWater)
	afx_msg void OnDecal();
	afx_msg void OnBump();
	afx_msg void OnButtonEnv1();
	afx_msg void OnButtonEnv2();
	afx_msg void OnButtonEnv3();
	afx_msg void OnButtonEnv4();
	afx_msg void OnButtonEnv5();
	afx_msg void OnButtonEnv6();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	//afx_msg void OnEnChangeEnv2();
	virtual BOOL OnInitDialog();
	CString _instruction;
	int m_autoGenerateCubeMap;
	afx_msg void OnBnClickedCheckForCubeMap();
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnEnChangeEdit7();
private:
	float m_redValue;
public:
	float m_greenValue;
private:
	float m_blueValue;
public:
	float m_alphaValue;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VGDLG_WATER_H__447DDB2E_5FF5_4159_AE74_16576B062AC8__INCLUDED_)
