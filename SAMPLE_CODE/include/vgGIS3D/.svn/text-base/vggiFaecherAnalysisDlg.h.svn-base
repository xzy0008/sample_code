#pragma once
#include "afxwin.h"
#include <vgGIS/resource.h>
#include <vgKernel/vgkSelectManager.h>
#include <vgKernel/vgkRendererManager.h>
//#include <deque>


// FaecherAnalysisDlg 对话框

class FaecherAnalysisDlg : public CDialog
{
	DECLARE_DYNAMIC(FaecherAnalysisDlg)

public:
	FaecherAnalysisDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~FaecherAnalysisDlg();

// 对话框数据
	enum { IDD = IDD_FAECHER_ANALYSIS_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	CBCGPGridCtrl m_List;
	void ShowName(std::deque<String> NameQue, int columnNum);
	virtual BOOL OnInitDialog();
	std::deque<String> GetName(vgKernel::RendererQueue  que);
	CStatic m_static;
	CList <CBCGPGridItem*, CBCGPGridItem*> ItemList;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	vgKernel::RendererQueue m_IntersectQue;
	vgKernel::RendererQueue m_ContainQue;
	vgKernel::RendererQueue m_DisjointQue;
	virtual void OnOK();
	virtual void OnCancel();
};
