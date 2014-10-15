#pragma once

#include "resource.h"
// DlgAutoIn 对话框

class DlgAutoIn : public CDialog
{
	DECLARE_DYNAMIC(DlgAutoIn)

public:
	DlgAutoIn(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~DlgAutoIn();

// 对话框数据
	enum { IDD = IDD_AUTOBUILD_IN };

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
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

	CString m_schem;
	int m_years;
};
