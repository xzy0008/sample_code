#pragma once

#include "vgChannelResource.h"
// vgDlgEdgeBlend 对话框
#include <vgChannel/vgchBlendPixelImpl.h>

class vgDlgEdgeBlend : public CDialog
{
	DECLARE_DYNAMIC(vgDlgEdgeBlend)

public:
	vgDlgEdgeBlend(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~vgDlgEdgeBlend();

// 对话框数据
	enum { IDD = IDD_DIALOG_BLEND };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeEdit10();
private:
	float m_leftEdge;
	float m_rightEdge;
	float m_gamma;
	float m_red;
	float m_green;
	float m_blue;

	vgChannel::BlendPixelImpl	*m_pBlendPixelImpl;

public:
	afx_msg void OnEnChangeRightedge();
	afx_msg void OnEnChangeRed();
	afx_msg void OnEnChangeGreen();
	afx_msg void OnEnChangeBlue();
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnEnChangeLeftedge();
	afx_msg void OnEnChangeGamma2();
	afx_msg void OnEnChangeLeftGamma();
	afx_msg void OnEnChangeRightGamma();
private:
	CString Xmlfilename;	//@FengYK 2009/10/31 11:01
	CString Xmlsectionname;
	int ifLoadSuccess;

	float m_leftGamma;
	float m_rightGamma;
	float m_fullGamma;
public:
	afx_msg void OnEnChangeFgamma();

};
