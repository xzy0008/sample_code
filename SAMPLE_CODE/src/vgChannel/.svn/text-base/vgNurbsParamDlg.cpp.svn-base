// D:\___NewVersion\vrgis1010\VisualStudio\vgSuperPlatform\vgNurbsParamDlg.cpp : 实现文件
//

#include <vgStableHeaders.h>
#include "vgChannel/vgNurbsParamDlg.h"
#include "vgChannel/vgcChannelManager.h"
#include <vgChannel/vgchNurbsCorrectImpl.h>

#include <vgKernel/vgkTrace.h>
#include <sstream>

using namespace std;
// vgNurbsParamDlg 对话框

IMPLEMENT_DYNAMIC(vgNurbsParamDlg, CDialog)

vgNurbsParamDlg::vgNurbsParamDlg(CWnd* pParent /*=NULL*/)
	: CDialog(vgNurbsParamDlg::IDD, pParent)
	, m_comboX(0)
	, m_comboY(0)
	, m_x(0)
	, m_y(0)
	, m_z(0)
	, m_w(0)
	, m_right(0)
	, m_top(0)
	, m_bottom(0)
	, m_left(0)
	,m_ctrlcorrect(0.005)
	,m_clipplane(0)
{

}

vgNurbsParamDlg::~vgNurbsParamDlg()
{
}

void vgNurbsParamDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_CBIndex(pDX, IDC_COMBO_X, m_comboX);
	DDX_CBIndex(pDX, IDC_COMBO_Y, m_comboY);
	DDX_Text(pDX, IDC_EDIT_X, m_x);
	DDX_Text(pDX, IDC_EDIT_Y, m_y);
	DDX_Text(pDX, IDC_EDIT_Z, m_z);
	DDX_Text(pDX, IDC_EDIT_W, m_w);
	DDX_Text(pDX, IDC_EDIT_RIGHT, m_right);
	DDX_Text(pDX, IDC_EDIT_TOP, m_top);
	DDX_Text(pDX, IDC_EDIT_BOTTOM, m_bottom);
	DDX_Text(pDX, IDC_EDIT_LEFT, m_left);
	DDX_Text(pDX, IDC_EDIT_CTRLCORRECT, m_ctrlcorrect);
	DDX_Text(pDX, IDC_EDIT_CLIPPLANE, m_clipplane);
}


BEGIN_MESSAGE_MAP(vgNurbsParamDlg, CDialog)
	ON_WM_DESTROY()
	ON_CBN_SELCHANGE(IDC_COMBO_X, &vgNurbsParamDlg::OnCbnSelchangeComboX)
	ON_CBN_SELCHANGE(IDC_COMBO_Y, &vgNurbsParamDlg::OnCbnSelchangeComboY)
	ON_EN_CHANGE(IDC_EDIT_X, &vgNurbsParamDlg::OnEnChangeEditX)
	ON_EN_CHANGE(IDC_EDIT_Y, &vgNurbsParamDlg::OnEnChangeEditY)
	ON_EN_CHANGE(IDC_EDIT_Z, &vgNurbsParamDlg::OnEnChangeEditZ)
	ON_EN_CHANGE(IDC_EDIT_W, &vgNurbsParamDlg::OnEnChangeEditW)
	ON_EN_CHANGE(IDC_EDIT_LEFT, &vgNurbsParamDlg::OnEnChangeEditLeft)
	ON_EN_CHANGE(IDC_EDIT_RIGHT, &vgNurbsParamDlg::OnEnChangeEditRight)
	ON_EN_CHANGE(IDC_EDIT_TOP, &vgNurbsParamDlg::OnEnChangeEditTop)
	ON_EN_CHANGE(IDC_EDIT_BOTTOM, &vgNurbsParamDlg::OnEnChangeEditBottom)
	ON_EN_CHANGE(IDC_EDIT_CTRLCORRECT, &vgNurbsParamDlg::OnEnChangeEditCtrlCorrect)
	ON_EN_CHANGE(IDC_EDIT_CLIPPLANE, &vgNurbsParamDlg::OnEnChangeEditClipplane)
	


END_MESSAGE_MAP()


void vgNurbsParamDlg::updateToNurbs()
{
	UpdateData(TRUE);

	vgChannel::NurbsCorrectImpl* nurbsPtr = vgChannel::ChannelManager::getSingleton().getNurbsPtr();
	
	vgChannel::FurstumVal fVal;
	vgChannel::CtrlPt     cVal;
	
	fVal.bottom = m_bottom;
	fVal.top = m_top;
	fVal.left = m_left;
	fVal.right = m_right;

	cVal.x = m_x;
	cVal.y = m_y;
	cVal.z = m_z;
	cVal.w = m_w;

	nurbsPtr->setControlPoint(m_comboX, m_comboY, cVal);
	nurbsPtr->GetCorrectParam(m_ctrlcorrect, m_clipplane);
	nurbsPtr->setFrustum(fVal);
}

// vgNurbsParamDlg 消息处理程序

void vgNurbsParamDlg::OnCbnSelchangeComboX()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);

	vgChannel::NurbsCorrectImpl* nurbsPtr = vgChannel::ChannelManager::getSingleton().getNurbsPtr();

	if (m_comboX >= 0 && m_comboX < 3 && m_comboY >=0 && m_comboY < 3)
	{
		vgChannel::CtrlPt pt = nurbsPtr->getControlPoint(m_comboX, m_comboY);
		
		m_x = pt.x;
		m_y = pt.y;
		m_z = pt.z;
		m_w = pt.w;

		std::stringstream outString;
		outString << m_x <<" "<< m_y <<" "<< m_z << "\n";

		VGK_SHOW(outString.str());

		UpdateData(FALSE);
	}
}

void vgNurbsParamDlg::OnCbnSelchangeComboY()
{
	// TODO: 在此添加控件通知处理程序代码

	UpdateData(TRUE);

	vgChannel::NurbsCorrectImpl* nurbsPtr = vgChannel::ChannelManager::getSingleton().getNurbsPtr();

	if (m_comboX >= 0 && m_comboX < 3 && m_comboY >=0 && m_comboY < 3)
	{
		vgChannel::CtrlPt pt = nurbsPtr->getControlPoint(m_comboX, m_comboY);

		m_x = pt.x;
		m_y = pt.y;
		m_z = pt.z;
		m_w = pt.w;

		std::stringstream outString;
		outString << m_x <<" "<< m_y <<" "<< m_z << "\n";

		VGK_SHOW(outString.str());

		UpdateData(FALSE);
	}
}

void vgNurbsParamDlg::OnEnChangeEditX()
{
	// TODO:  如果该控件是 RICHEDIT 控件，则它将不会
	// 发送该通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	updateToNurbs();
}

void vgNurbsParamDlg::OnEnChangeEditY()
{
	// TODO:  如果该控件是 RICHEDIT 控件，则它将不会
	// 发送该通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	updateToNurbs();
}

void vgNurbsParamDlg::OnEnChangeEditZ()
{
	// TODO:  如果该控件是 RICHEDIT 控件，则它将不会
	// 发送该通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	updateToNurbs();
}

void vgNurbsParamDlg::OnEnChangeEditW()
{
	// TODO:  如果该控件是 RICHEDIT 控件，则它将不会
	// 发送该通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	updateToNurbs();
}

void vgNurbsParamDlg::OnEnChangeEditLeft()
{
	// TODO:  如果该控件是 RICHEDIT 控件，则它将不会
	// 发送该通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	updateToNurbs();
}

void vgNurbsParamDlg::OnEnChangeEditRight()
{
	// TODO:  如果该控件是 RICHEDIT 控件，则它将不会
	// 发送该通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	updateToNurbs();
}

void vgNurbsParamDlg::OnEnChangeEditTop()
{
	// TODO:  如果该控件是 RICHEDIT 控件，则它将不会
	// 发送该通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	updateToNurbs();
}

void vgNurbsParamDlg::OnEnChangeEditBottom()
{
	// TODO:  如果该控件是 RICHEDIT 控件，则它将不会
	// 发送该通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	updateToNurbs();
}
void vgNurbsParamDlg::OnEnChangeEditCtrlCorrect()
{
	updateToNurbs();
}
void vgNurbsParamDlg::OnEnChangeEditClipplane()
{
	updateToNurbs();
}

BOOL vgNurbsParamDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	vgChannel::NurbsCorrectImpl* nurbsPtr = vgChannel::ChannelManager::getSingleton().getNurbsPtr();
	
	m_comboX = 1;
	m_comboY = 1;

	vgChannel::CtrlPt pt = nurbsPtr->getControlPoint(m_comboX, m_comboY);

	m_x = pt.x;
	m_y = pt.y;
	m_z = pt.z;
	m_w = pt.w;

	vgChannel::FurstumVal fval = nurbsPtr->getFrustumVal();
	
	m_top = fval.top;
	m_bottom = fval.bottom;
	m_left = fval.left;
	m_right = fval.right;

	std::stringstream outString;
	outString << m_x <<" "<< m_y <<" "<< m_z << "\n";

	VGK_SHOW(outString.str());

	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void vgNurbsParamDlg::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类
	//@FengYK 2009/10/31 11:11
	vgChannel::NurbsCorrectImpl* nurbsPtr = vgChannel::ChannelManager::getSingleton().getNurbsPtr();
	nurbsPtr->SavePramaToXml();
	CDialog::OnOK();
	DestroyWindow();
}

void vgNurbsParamDlg::OnCancel()
{
	vgChannel::NurbsCorrectImpl* nurbsPtr = vgChannel::ChannelManager::getSingleton().getNurbsPtr();
	nurbsPtr->ReturnToOriPrama();

	CDialog::OnCancel();
	DestroyWindow();
}

 void vgNurbsParamDlg::OnDestroy()
{
	CDialog::OnDestroy();
	
	delete this;
 }
