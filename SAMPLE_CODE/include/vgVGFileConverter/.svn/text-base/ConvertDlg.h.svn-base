// WizardSheetDlg.h : header file
//

#pragma once
#include "afxwin.h"
#include "vgMovingManager.h"
#include "vgTex/tvgTextureManager.h"
#include "vgTex/tvgArchiveManager.h"
#include "vgTex/tvgGpuManager.h"

// CWizardSheetDlg dialog
class CWizardSheetDlg : public CBCGPDialog
{
// Construction
public:
	CWizardSheetDlg(CWnd* pParent = NULL);	// standard constructor
	~CWizardSheetDlg();

// Dialog Data
	enum { IDD = IDD_WIZARDSHEET_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();

	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

	string m_inFile;
	string m_outFile;
	string m_folderpathOut;
public:
	afx_msg void OnBnClickedInfile();
	afx_msg void OnBnClickedOutfile();
	afx_msg void OnEnChangeInfileEdit();
	afx_msg void OnBnClickedGenerate();

	vgCore::MovingManager	*m_pMovingMgr;
	vgCore::TextureManager	*m_pTextureMgr;
	vgCore::ArchiveManager	*m_pArchiveManger;
	vgCore::GpuManager		*m_pGpuManager;

	void initializeEnvironment();
	bool initGLContext(void);
	void copyAllFilesDefault();
	void releaseGLContext(void);
	bool resetManager();
	CDC*	m_pDC;
	HGLRC	m_hGLContext;
};
