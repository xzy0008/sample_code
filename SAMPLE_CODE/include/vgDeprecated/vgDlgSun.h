#pragma once
#if 0
#include "resource.h"

// vgDlgSun 对话框

class  VGDEP_EXPORT vgDlgSun : public CDialog
{
	DECLARE_DYNAMIC(vgDlgSun)

public:
	vgDlgSun(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~vgDlgSun();

// 对话框数据
	enum { IDD = IDD_DLG_SUN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int m_year;
	int m_month;
	int m_day;
	int m_hour;
	int m_minute;
	int m_lat;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
#endif