#pragma once

#include "resource.h"
// DlgAutoBuildInput 对话框

class  VGDEP_EXPORT DlgAutoBuildInput : public CDialog
{
	DECLARE_DYNAMIC(DlgAutoBuildInput)

public:
	DlgAutoBuildInput(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~DlgAutoBuildInput();

	int getYear()
	{
		return m_years;
	}

	CString getSchem()
	{
		return m_schem;
	}

	int getSchemId()
	{
		if (m_schem == "GS")
		{
			return 0;
		}
		else if (m_schem == "LS")
		{
			return 1;
		}
		else if (m_schem == "NE")
		{
			return 2;
		}
		else
		{
			return 3;
		}
	}

// 对话框数据
	enum { IDD = IDD_AUTOBUILD_INPUT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_schem;
	int m_years;
};
