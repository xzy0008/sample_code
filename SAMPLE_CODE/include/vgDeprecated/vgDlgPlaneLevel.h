#pragma once
//#include "vgStableHeaders.h"
#include "resource.h"
// CPlaneLevel 对话框

class  VGDEP_EXPORT CPlaneLevel : public CDialog
{
	DECLARE_DYNAMIC(CPlaneLevel)

public:
	CPlaneLevel(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CPlaneLevel();

// 对话框数据
	enum { IDD = IDD_WATER_LEVEL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	float m_plane_level;
	afx_msg void OnBnClickedOk();
	afx_msg void OnDestroy();
};
