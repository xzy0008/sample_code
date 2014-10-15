#pragma once


#include <vgVisualEffects/vgviDefinition.h>

#include <BCGPColorButton.h>

#ifdef VGVI_DLL
#include <vgVisualEffectsResource.h>
#else
#include <vgLibraryResource.h>
#endif

#include <vgVisualEffects/vgviColorValue.h>

// DlgVgviBackground dialog

class  VGVI_EXPORT DlgVgviBackground : public CDialog
{
	DECLARE_DYNAMIC(DlgVgviBackground)

public:
	DlgVgviBackground(CWnd* pParent = NULL);   // standard constructor
	virtual ~DlgVgviBackground();

// Dialog Data
	enum { IDD = IDD_DLG_VGVI_BG };


	CBCGPColorButton	m_ColorPicker;


public:

	vgVisualEffects::ColorValu _colorVal;


	vgVisualEffects::ColorValu  getBackgroundColor() const
	{
		return _colorVal;
	}


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	afx_msg void OnColorPicker();

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();

	void initColorPicker( const RGBQUAD& quad );
	afx_msg void OnBnClickedSetDefault();
	afx_msg void OnBnClickedApply();
};
