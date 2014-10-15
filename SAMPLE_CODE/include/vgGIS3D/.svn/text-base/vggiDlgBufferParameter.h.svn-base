#pragma once

#include <vgGIS/resource.h>
#include "afxwin.h"
// DlgBufferParameter dialog

class DlgBufferParameter : public CDialog
{
	DECLARE_DYNAMIC(DlgBufferParameter)

public:
	DlgBufferParameter(CWnd* pParent = NULL);   // standard constructor
	virtual ~DlgBufferParameter();

// Dialog Data
	enum { IDD = IDD_BUFFER_PARAMETER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedCheckLeftRightBuffer();
	afx_msg void OnCbnSelchangeComboSelectLayer();

public:

	double getLeftRadius() const
	{
		return m_leftRadius;
	}

	double getRightRadius() const
	{
		return m_rightRadius;
	}

	BOOL isLeftRightBuffer() const
	{
		return m_bCheck;
	}

	void setEnableSelLayer( bool bEnable )
	{
		m_bEnableSelLayer = bEnable;
	}

	String getSelLayerName()
	{
		return m_selLayerName;
	}

private:
	double    m_leftRadius;     // ×ó»º³åÇø°ë¾¶
	double    m_rightRadius;    // ÓÒ»º³åÇø°ë¾¶
	BOOL      m_bCheck;         // ÊÇ·ñ×óÓÒ»º³å°ë¾¶²»ÏàµÈ
	CComboBox m_selectLayer;    // ·ÖÎöÍ¼²ã	

	bool      m_bEnableSelLayer;  
	String    m_selLayerName;

};
