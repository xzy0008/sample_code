// vgviDlgVgviBackground.cpp : implementation file
//

#include <vgStableHeaders.h>
#include <vgVisualEffects/vgviBackgroundManager.h>
#include "vgVisualEffects/vgviDlgVgviBackground.h"


// DlgVgviBackground dialog

IMPLEMENT_DYNAMIC(DlgVgviBackground, CDialog)

DlgVgviBackground::DlgVgviBackground(CWnd* pParent /*=NULL*/)
	: CDialog(DlgVgviBackground::IDD, pParent)
{

}

DlgVgviBackground::~DlgVgviBackground()
{
}

void DlgVgviBackground::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COLOR_PICKER, m_ColorPicker);
}


BEGIN_MESSAGE_MAP(DlgVgviBackground, CDialog)
	ON_BN_CLICKED(IDC_COLOR_PICKER, OnColorPicker)
	ON_BN_CLICKED(IDC_SET_DEFAULT, &DlgVgviBackground::OnBnClickedSetDefault)
	ON_BN_CLICKED(IDC_APPLY, &DlgVgviBackground::OnBnClickedApply)
END_MESSAGE_MAP()


// DlgVgviBackground message handlers

BOOL DlgVgviBackground::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	initColorPicker(vgVisualEffects::BackgroundManager::getSingleton().getCurrentBackgroundColor().getAsRGBQUAD());



	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void DlgVgviBackground::OnColorPicker()
{
	COLORREF color = m_ColorPicker.GetColor ();

	//m_strRGB.Format (_T("%d,%d,%d"), 
	//	GetRValue (color),
	//	GetGValue (color),
	//	GetBValue (color));

	RGBQUAD quad;
	quad.rgbRed = GetRValue( color );
	quad.rgbGreen = GetGValue( color );
	quad.rgbBlue = GetBValue( color );
	quad.rgbReserved = 255;

	_colorVal.setAsRGBQUAD( quad );
}
void DlgVgviBackground::OnBnClickedSetDefault()
{
	// TODO: Add your control notification handler code here

	initColorPicker( vgVisualEffects::ColorValu::DEFAULT.getAsRGBQUAD());

	OnColorPicker();
}

void DlgVgviBackground::initColorPicker( const RGBQUAD& quad )
{
	// Create color picker:
	//m_ColorPicker.EnableAutomaticButton (_T("自动"), 
	//	RGB ( quad.rgbRed,  quad.rgbGreen, quad.rgbBlue ));
	m_ColorPicker.EnableOtherButton (_T("其他"));
	m_ColorPicker.SetColor ( RGB ( quad.rgbRed,  quad.rgbGreen, quad.rgbBlue ) );
	m_ColorPicker.SetColumnsNumber (15);

	UpdateData();
}
void DlgVgviBackground::OnBnClickedApply()
{
	vgVisualEffects::BackgroundManager::getSingleton().setCurrentBackgroundColor(
		getBackgroundColor() );
}
