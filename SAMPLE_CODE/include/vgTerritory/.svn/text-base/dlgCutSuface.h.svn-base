#pragma once


// CdlgCutSuface 对话框
#include "vgTerritoryResource.h"
#include "vgTerritory/CutSurfView.h"

class CdlgCutSuface : public CDialog
{
	DECLARE_DYNAMIC(CdlgCutSuface)

public:
	CdlgCutSuface(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CdlgCutSuface();

// 对话框数据
	enum { IDD = IDD_DLG_CUTSURFACE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	
	DECLARE_MESSAGE_MAP()
public:
	
	virtual BOOL OnInitDialog();
public:
	CutSurfView *pView;
	bool  m_bClosed;

	void setClosed( bool bClosed ) { m_bClosed = bClosed; }
	bool getClosed() { return m_bClosed; }

public:

	afx_msg void OnDestroy();
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	CString sHeightValue;
	afx_msg void OnBnClickedOk();
};
