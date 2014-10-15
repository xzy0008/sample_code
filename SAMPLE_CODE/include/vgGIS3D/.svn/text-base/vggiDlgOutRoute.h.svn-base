#pragma once

#include <vgGis/Resource.h>


// vgDlgOutRoute 对话框

class vgDlgOutRoute : public CDialog
{
	DECLARE_DYNAMIC(vgDlgOutRoute)

public:
	vgDlgOutRoute(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~vgDlgOutRoute();

// 对话框数据
	enum { IDD = IDD_EDIT_ROUTE };

	string getLayerName() 
	{
		return m_layerName.GetString();
	}

	string getSavePath()
	{
		return m_savePath.GetString();
	}

protected:
	
	CString m_layerName;

	CString m_savePath;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedSelFile();
	afx_msg void OnBnClickedOk();
};
