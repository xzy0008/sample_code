#pragma once

#include "resource.h"
// DlgAutobuildImportTxt 对话框

class DlgAutobuildImportTxt : public CDialog
{
	DECLARE_DYNAMIC(DlgAutobuildImportTxt)

public:
	DlgAutobuildImportTxt(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~DlgAutobuildImportTxt();

// 对话框数据
	enum { IDD = IDD_AUTOBUILD_IMPORTTXT };
	
	CString getSchemName()
	{
		return m_schemName;
	}

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_schemName;
};
