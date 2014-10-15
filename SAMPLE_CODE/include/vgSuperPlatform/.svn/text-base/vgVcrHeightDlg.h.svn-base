#pragma once
#include <resource.h>

// vgVcrHeightDlg 对话框

class vgVcrHeightDlg : public CDialog
{
	DECLARE_DYNAMIC(vgVcrHeightDlg)

public:
	vgVcrHeightDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~vgVcrHeightDlg();

// 对话框数据
	enum { IDD = IDD_CAMRECORD_HEIGHT };

public:
	float getTransHeight()
	{
		return m_translateHeight;
	}
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	float m_translateHeight;
};
