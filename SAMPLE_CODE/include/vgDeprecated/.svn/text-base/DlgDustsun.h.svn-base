#pragma once

#include <vgDeprecatedMFCDLL/Resource.h>
#include "afxcmn.h"

// DlgDustsun 对话框

class DlgDustsun : public CDialog
{
	DECLARE_DYNAMIC(DlgDustsun)

public:
	DlgDustsun(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~DlgDustsun();

// 对话框数据
	enum { IDD = IDD_DUSTSUN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:

	int gettime(){return m_time;}

	void settime( int _time );

	int m_time;

	CSliderCtrl timeslider;
	afx_msg void OnNMReleasedcaptureSlider1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnNMThemeChangedSlider1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
};
