// D:\___NewVersion\vrgis1010\src\vgSuperPlatform\vgDlgEdgeBlend.cpp : 实现文件
//

#include <vgStableHeaders.h> 
#include "vgChannel/vgDlgEdgeBlend.h"
#include <vgChannel/vgcChannelManager.h>

// vgDlgEdgeBlend 对话框

IMPLEMENT_DYNAMIC(vgDlgEdgeBlend, CDialog)

vgDlgEdgeBlend::vgDlgEdgeBlend(CWnd* pParent /*=NULL*/)
	: CDialog(vgDlgEdgeBlend::IDD, pParent)
	, m_leftEdge(0)
	, m_rightEdge(0)
	, m_red(0)
	, m_green(0)
	, m_blue(0)
	, m_leftGamma(0)
	, m_rightGamma(0)
	, m_fullGamma(0)
{

}

vgDlgEdgeBlend::~vgDlgEdgeBlend()
{
}

void vgDlgEdgeBlend::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_LEFTEDGE, m_leftEdge);
	DDX_Text(pDX, IDC_RIGHTEDGE, m_rightEdge);
	DDX_Text(pDX, IDC_RED, m_red);
	DDX_Text(pDX, IDC_GREEN, m_green);
	DDX_Text(pDX, IDC_BLUE, m_blue);
	DDX_Text(pDX, IDC_LEFT_GAMMA, m_leftGamma);
	DDX_Text(pDX, IDC_RIGHT_GAMMA, m_rightGamma);
	DDX_Text(pDX, IDC_FGAMMA, m_fullGamma);
}


BEGIN_MESSAGE_MAP(vgDlgEdgeBlend, CDialog)
	ON_EN_CHANGE(IDC_RIGHTEDGE, &vgDlgEdgeBlend::OnEnChangeRightedge)
	ON_EN_CHANGE(IDC_RED, &vgDlgEdgeBlend::OnEnChangeRed)
	ON_EN_CHANGE(IDC_GREEN, &vgDlgEdgeBlend::OnEnChangeGreen)
	ON_EN_CHANGE(IDC_BLUE, &vgDlgEdgeBlend::OnEnChangeBlue)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDOK, &vgDlgEdgeBlend::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &vgDlgEdgeBlend::OnBnClickedCancel)
	ON_EN_CHANGE(IDC_LEFTEDGE, &vgDlgEdgeBlend::OnEnChangeLeftedge) 
	ON_EN_CHANGE(IDC_LEFT_GAMMA, &vgDlgEdgeBlend::OnEnChangeLeftGamma)
	ON_EN_CHANGE(IDC_RIGHT_GAMMA, &vgDlgEdgeBlend::OnEnChangeRightGamma)
	ON_EN_CHANGE(IDC_FGAMMA, &vgDlgEdgeBlend::OnEnChangeFgamma)
END_MESSAGE_MAP()


// vgDlgEdgeBlend 消息处理程序

void vgDlgEdgeBlend::OnEnChangeRightedge()
{
	// TODO:  如果该控件是 RICHEDIT 控件，则它将不会
	// 发送该通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码

	UpdateData(TRUE);

	m_pBlendPixelImpl->setRightEdge(m_rightEdge);
}

// void vgDlgEdgeBlend::OnEnChangeGamma()
// {
// 	// TODO:  如果该控件是 RICHEDIT 控件，则它将不会
// 	// 发送该通知，除非重写 CDialog::OnInitDialog()
// 	// 函数并调用 CRichEditCtrl().SetEventMask()，
// 	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。
// 
// 	// TODO:  在此添加控件通知处理程序代码
// 
// 	UpdateData(TRUE);
// 
// 	m_pBlendPixelImpl->setGamma(m_gamma);
// }

void vgDlgEdgeBlend::OnEnChangeRed()
{
	// TODO:  如果该控件是 RICHEDIT 控件，则它将不会
	// 发送该通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码

	UpdateData(TRUE);

	m_pBlendPixelImpl->setRedGamma(m_red);
}

void vgDlgEdgeBlend::OnEnChangeGreen()
{
	// TODO:  如果该控件是 RICHEDIT 控件，则它将不会
	// 发送该通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码

	UpdateData(TRUE);

	m_pBlendPixelImpl->setGreenGamma(m_green);
}

void vgDlgEdgeBlend::OnEnChangeBlue()
{
	// TODO:  如果该控件是 RICHEDIT 控件，则它将不会
	// 发送该通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码

	UpdateData();

	m_pBlendPixelImpl->setBlueGamma(m_blue);
}

BOOL vgDlgEdgeBlend::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	m_pBlendPixelImpl = vgChannel::ChannelManager::getSingleton().getBlenderPtr();

	m_leftEdge = m_pBlendPixelImpl->getLeftEdge();
	m_rightEdge = m_pBlendPixelImpl->getRightEdge();

	m_leftGamma = m_pBlendPixelImpl->getLeftGama();
	m_rightGamma = m_pBlendPixelImpl->getRightGama();

	m_red = m_pBlendPixelImpl->getRedGamma();
	m_green = m_pBlendPixelImpl->getGreenGama();
	m_blue = m_pBlendPixelImpl->getBlueGamma();
	
	m_fullGamma = m_pBlendPixelImpl->getFullScreenGamma();

	UpdateData(FALSE);

	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void vgDlgEdgeBlend::OnDestroy()
{
	CDialog::OnDestroy();
	
	delete this;
	// TODO: 在此处添加消息处理程序代码
}

void vgDlgEdgeBlend::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	m_pBlendPixelImpl->SaveToXml();	//@FengYK 2009/10/31 11:05
	OnOK();
	DestroyWindow();
}

void vgDlgEdgeBlend::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strExtension = _T(".xml");

	char exebuf[512];
	DWORD getret = GetModuleFileName( NULL , exebuf , 512 );

	assert( getret < 512 );
	assert( getret > 0 );

	String exestr( exebuf );
	String exepath = exestr.substr( 0 , 
		exestr.find_last_of("\\/")  + 1);

	CString path;
	path.Format("%s", exepath.c_str());

	Xmlfilename =  _T("Channel");		//@FengYK	2009/10/31 10:21
	CString sFileName = path + Xmlfilename + strExtension ;
	Xmlsectionname = _T("Edge blending correction");
	if (vgConfig::XMLConfigManager::getSingleton().LoadXmlDocument(sFileName)&&
		vgConfig::XMLConfigManager::getSingleton().FindSection(Xmlsectionname))
	{
		m_pBlendPixelImpl->initBlendParam();
	}
	OnCancel();
	DestroyWindow();
}

void vgDlgEdgeBlend::OnEnChangeLeftedge()
{
	// TODO:  如果该控件是 RICHEDIT 控件，则它将不会
	// 发送该通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);

	m_pBlendPixelImpl->setLeftEdge(m_leftEdge);
}

void vgDlgEdgeBlend::OnEnChangeLeftGamma()
{
	// TODO:  如果该控件是 RICHEDIT 控件，则它将不会
	// 发送该通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);

	m_pBlendPixelImpl->setLeftGama(m_leftGamma);
}

void vgDlgEdgeBlend::OnEnChangeRightGamma()
{
	// TODO:  如果该控件是 RICHEDIT 控件，则它将不会
	// 发送该通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码

	UpdateData(TRUE);

	m_pBlendPixelImpl->setRightGama(m_rightGamma);
}

void vgDlgEdgeBlend::OnEnChangeFgamma()
{
	// TODO:  如果该控件是 RICHEDIT 控件，则它将不会
	// 发送该通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);

	m_pBlendPixelImpl->setFullScreenGamma(m_fullGamma);
}
