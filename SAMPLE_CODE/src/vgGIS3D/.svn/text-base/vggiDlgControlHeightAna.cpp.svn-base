// vggiDlgControlHeight.cpp : 实现文件
//

#include "vgStableHeaders.h"
#include "vgGIS3D/vggiDlgControlHeightAna.h"


// vggiDlgControlHeight 对话框
namespace vgGIS3D
{
	IMPLEMENT_DYNAMIC(vggiDlgControlHeight, CDialog)

		vggiDlgControlHeight::vggiDlgControlHeight(CWnd* pParent /*=NULL*/)
		: CDialog(vggiDlgControlHeight::IDD, pParent)
		, fControlHeight(0)
	{

	}

	vggiDlgControlHeight::~vggiDlgControlHeight()
	{
	}

	void vggiDlgControlHeight::DoDataExchange(CDataExchange* pDX)
	{
		CDialog::DoDataExchange(pDX);
		DDX_Text(pDX, IDC_EDIT_CONTROL_HEIGHT_TXT, fControlHeight);
	}


	BEGIN_MESSAGE_MAP(vggiDlgControlHeight, CDialog)
	END_MESSAGE_MAP()


	// vggiDlgControlHeight 消息处理程序

	BOOL vggiDlgControlHeight::OnInitDialog()
	{
		CDialog::OnInitDialog();

		// TODO:  在此添加额外的初始化

		return TRUE;  // return TRUE unless you set the focus to a control
		// 异常: OCX 属性页应返回 FALSE
	}

	float vggiDlgControlHeight::getControlHeight()
	{
		return fControlHeight;
	}

	void vggiDlgControlHeight::setControlHeight( float fht )
	{
		fControlHeight = fht;
	}

}// End namespace vgGIS3D