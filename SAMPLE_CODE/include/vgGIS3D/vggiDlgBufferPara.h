

#pragma once

#include <vgGIS/resource.h>
#include <vgGIS/vggisDefinition.h>
#include "afxwin.h"

// DlgBufferPara dialog


class VGG_EXPORT DlgBufferPara : public CDialog
{
	DECLARE_DYNAMIC(DlgBufferPara)

public:
	DlgBufferPara(CWnd* pParent = NULL);   // standard constructor
	virtual ~DlgBufferPara();

// Dialog Data
	enum { IDD = IDD_BUFFER_PARA };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()


public:
	virtual BOOL OnInitDialog();

	afx_msg void OnBnClickedCheckLeftRightBuffer();
	afx_msg void OnCbnSelchangeComboSelectLayer();

protected:
	virtual void OnOK();

public:

	double getRadius() const
	{
		return m_radius;
	}

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

	String getSelLayerName();

private:

	double m_radius;         // »º³å°ë¾¶

	double m_leftRadius;     // ×ó»º³å°ë¾¶
	
	double m_rightRadius;    // ÓÒ»º³å°ë¾¶

	BOOL m_bCheck;           // ÊÇ·ñÎª×óÓÒ»º³åÇøÄ£Ê½
	
	CComboBox m_selectLayer; // Ñ¡Ôñ·ÖÎöÍ¼²ã

	bool m_bEnableSelLayer;  

	String m_selLayerName;

};


