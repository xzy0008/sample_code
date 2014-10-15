// vgAviExportDialog.cpp : 实现文件
//

#include "vgStableHeaders.h"
#include "vgAviExportDialog.h"

const int  AviExportDialog::s_dValue[11] = {0, 1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000};

// AviExportDialog 对话框

IMPLEMENT_DYNAMIC(AviExportDialog, CDialog)

AviExportDialog::AviExportDialog(CWnd* pParent /*=NULL*/)
	: CDialog(AviExportDialog::IDD, pParent)
	, m_aviFilePath(_T(""))
	, m_cameraName(_T(""))
	, m_aviFrameWidth(1024)
	, m_aviFrameHeight(768)
	, m_compressId(0)
	, m_quality(0)
	, m_qualityValue(0)
	, m_quaStatic(0)
{

}

AviExportDialog::~AviExportDialog()
{
}

void AviExportDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_AVIPATH, m_aviFilePath);
	DDX_Text(pDX, IDC_EDIT_CAMERA, m_cameraName);
	DDX_Text(pDX, IDC_EDIT_AVIWIDTH, m_aviFrameWidth);
	DDX_Text(pDX, IDC_EDIT_AVIHEIGHT, m_aviFrameHeight);
	DDV_MinMaxInt(pDX, m_aviFrameWidth, 4, INT_MAX);
	DDV_MinMaxInt(pDX, m_aviFrameHeight, 4, INT_MAX);
	DDX_CBIndex(pDX, IDC_COMPRESS_COMBO, m_compressId);
	DDX_Slider(pDX, IDC_SLIDER1, m_quality);
	DDV_MinMaxInt(pDX, m_quality, 0, 10000);
	DDX_Text(pDX, IDC_STATIC_QUA, m_quaStatic);
}


BEGIN_MESSAGE_MAP(AviExportDialog, CDialog)
	ON_BN_CLICKED(IDC_EXPAVI_PATH, &AviExportDialog::OnBnClickedExpaviPath)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER1, &AviExportDialog::OnNMCustomdrawSlider1)
	ON_WM_HSCROLL()
	ON_WM_CREATE()
END_MESSAGE_MAP()


void AviExportDialog::OnBnClickedExpaviPath()
{
	// TODO: 在此添加控件通知处理程序代码
	char szFilters[]=
		"(*.avi)|*.avi|All Files (*.*)|*.*||";

	CFileDialog dlg (FALSE, "avi", "*.avi",
		OFN_FILEMUSTEXIST| OFN_HIDEREADONLY, szFilters, this);

	if( dlg.DoModal ()==IDOK )
	{
		m_aviFilePath = dlg.GetPathName();

		UpdateData(false);
	}
}

void AviExportDialog::OnNMCustomdrawSlider1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}

void AviExportDialog::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	UpdateData(true);
	m_qualityValue = s_dValue[m_quality];
 	m_quaStatic = m_qualityValue;
 	UpdateData(false);
 	

	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

int AviExportDialog::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码

	return 0;
}

BOOL AviExportDialog::OnInitDialog()
{
	CSliderCtrl *pSlide = (CSliderCtrl*)GetDlgItem(IDC_SLIDER1);

	if (pSlide != NULL)
	{
		pSlide->SetRange(0, 10);
	}

	return CDialog::OnInitDialog();
}