#if !defined(AFX_VGTREESETDLG_H__1D56F980_DEED_47A5_B652_18F073D20D83__INCLUDED_)
#define AFX_VGTREESETDLG_H__1D56F980_DEED_47A5_B652_18F073D20D83__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgTreeSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// DlgTreeSet dialog
#include <resource.h>

class VGDEP_EXPORT	DlgTreeSet : public CDialog
{
// Construction
public:
	float GetTreeWidth();
	float GetTreeHeight();
	string GetTexturePath();
	DlgTreeSet(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(DlgTreeSet)
	enum { IDD = IDD_TREESETTING };

	enum PlantMode{ PLANT_POINT, PLANT_LINE }; //add by ZhouZY 2009-11-6 11:26

	CButton 	m_texture;
	float		m_treeheight;
	float		m_treewidth;
	//}}AFX_DATA
	string m_treepathname;

	// 临时变量存储旧参数 add by lss when 2008-11-3 20:24:01
	float	m_treeheightOld;
	float	m_treewidthOld;
	string	m_treepathnameOld;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DlgTreeSet)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(DlgTreeSet)
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnTexutre();
	afx_msg void OnBnClickedRadioPlantPoint();
	afx_msg void OnBnClickedRadioPlantLine();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	//add by ZhouZY 2009-11-6 11:26
private:
	void checkIsTga( CFileDialog &dlg );
	PlantMode   m_plantMode;        //标识植树模式

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VGTREESETDLG_H__1D56F980_DEED_47A5_B652_18F073D20D83__INCLUDED_)
