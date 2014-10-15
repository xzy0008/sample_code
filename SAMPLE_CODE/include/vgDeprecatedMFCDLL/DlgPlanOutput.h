#pragma once

#include "resource.h"
#include "afxwin.h"
#include <vgPlan/vgPlanscene.h>

// DlgPlanOutput 对话框

class VGDEP_EXPORT DlgPlanOutput : public CDialog
{
	DECLARE_DYNAMIC(DlgPlanOutput)

public:
	DlgPlanOutput(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~DlgPlanOutput();

// 对话框数据
	enum { IDD = IDD_PLAN_OUTPUT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

public:
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
private:
	CComboBox m_floorComboBox;

	vgPlan::BlockParam m_blockParam;

	int m_minFloor;
	int m_maxFloor;
public:
	afx_msg void OnCbnSelchangeFloor();
protected:
	virtual void OnCancel();
public:
	afx_msg void OnEnChangeEdit7();
private:
	int m_blockX;
	int m_blockY;
	int m_blockCnt;
	float m_floorAreaRadio;
public:
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio3();
	afx_msg void OnBnClickedRadio2();
private:
	CString m_schemName;
public:
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnBnClickedExpShp();
};
