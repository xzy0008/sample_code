#pragma once

#include <resource.h>
#include <vgMod/vgGisRoadMatch.h>

// vgDlgGismatch 对话框

class  VGDEP_EXPORT vgDlgGismatch : public CDialog
{
	DECLARE_DYNAMIC(vgDlgGismatch)

public:
	vgDlgGismatch(vgMod::GisRoadMatch* pmatch , CWnd* pParent = NULL);   // 标准构造函数
	virtual ~vgDlgGismatch();

// 对话框数据
	enum { IDD = IDD_GISMATCH };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
public:

	vgMod::GisRoadMatch* pMatch;
	string m_name;
	
	float m_width;
	afx_msg void OnBnClickedButton1();
	float m_luya;
	float m_height;
	float m_midu;
};
