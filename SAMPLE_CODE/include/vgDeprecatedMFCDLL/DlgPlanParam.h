#pragma once

#include "resource.h"

// DlgPlanParam 对话框

class  VGDEP_EXPORT DlgPlanParam : public CDialog
{
	DECLARE_DYNAMIC(DlgPlanParam)

public:
	DlgPlanParam(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~DlgPlanParam();

// 对话框数据
	enum { IDD = IDD_DLG_PLANGRIDSIZE };

	int getGridX()
	{
		return m_gridX;
	}

	int getGridY()
	{
		return m_gridY;
	}

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
private:
	int m_gridX;
	int m_gridY;
public:
	afx_msg void OnCbnSelchangeSchemCombo();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedGenerateGrid();
};
