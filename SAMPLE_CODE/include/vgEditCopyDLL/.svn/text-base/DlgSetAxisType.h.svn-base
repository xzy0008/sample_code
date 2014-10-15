#pragma once

#include "vgEditCopyResource.h"

#include <vgKernel/vgkRenderer.h>

// DlgSetAxisType 对话框

class DlgSetAxisType : public CDialog
{
	DECLARE_DYNAMIC(DlgSetAxisType)

public:
	DlgSetAxisType(bool bCopyOrMirror = true, CWnd* pParent = NULL);   // 标准构造函数
	virtual ~DlgSetAxisType();

// 对话框数据
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

	BOOL m_bAxisX;
	BOOL m_bAxisY;
	BOOL m_bAxisZ;

	BOOL m_bXMinus;
	BOOL m_bYMinus;
	BOOL m_bZMinus;

	bool m_bCopyOrMirror;
	vgKernel::RendererQueue*	m_pRecentCopy;
	vgKernel::RendererQueue		m_pRenderersCancel;

public:
	afx_msg void OnBnClickedExcute();
	afx_msg void OnBnClickedBtnCancel();
	afx_msg void OnBnClickedOk();
};
