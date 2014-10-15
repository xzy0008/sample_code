#pragma once
#include "resource.h"
#include <vgAutoBuild/vgAutoBuildNode.h>

// vgDlgAutoBuild 对话框

class  VGDEP_EXPORT vgDlgAutoBuild : public CDialog
{
	DECLARE_DYNAMIC(vgDlgAutoBuild)

public:
	vgDlgAutoBuild(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~vgDlgAutoBuild();

// 对话框数据
	enum { IDD = IDD_AUTOBUILD_DLG };

public:
	float GetUnit()
	{
		return m_unit;
	}

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	float m_unit;
};
