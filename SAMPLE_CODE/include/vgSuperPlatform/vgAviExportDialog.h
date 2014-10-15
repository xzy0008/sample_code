#pragma once
#include "resource.h"

// AviExportDialog 对话框

class AviExportDialog : public CDialog
{
	DECLARE_DYNAMIC(AviExportDialog)        
private:
	static const int s_dValue[11];

public:
	AviExportDialog(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~AviExportDialog();

// 对话框数据
	enum { IDD = IDD_AVIEXPORT_DIALOG };

public:
	CString getFilePath()
	{
		return m_aviFilePath;
	}

	CString getCameraName()
	{
		return m_cameraName;
	}

	int getFrameWidth()
	{
		return m_aviFrameWidth;
	}

	int getFrameHeight()
	{
		return m_aviFrameHeight;
	}

	int getCompressId()
	{
		return m_compressId;
	}

	int getQuality()
	{
		return m_qualityValue;
	}

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_aviFilePath;
	CString m_cameraName;
	int m_aviFrameWidth;
	int m_aviFrameHeight;
	afx_msg void OnBnClickedExpaviPath();

	virtual BOOL OnInitDialog();

private:
	int m_compressId;
	int m_qualityValue;
	int m_quality;

public:
	afx_msg void OnNMCustomdrawSlider1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
private:
	int m_quaStatic;
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};