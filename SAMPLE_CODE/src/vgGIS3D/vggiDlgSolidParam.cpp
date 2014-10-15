#include <vgStableHeaders.h>
#include <vgGis3d/vggiDlgSolidParam.h>

namespace vgGIS3D
{



	// vgDlgSolidParam 对话框

	IMPLEMENT_DYNAMIC(vgDlgSolidParam, CDialog)

		vgDlgSolidParam::vgDlgSolidParam(CWnd* pParent /*=NULL*/)
		: CDialog(vgDlgSolidParam::IDD, pParent)
	{

	}

	vgDlgSolidParam::~vgDlgSolidParam()
	{
	}

	void vgDlgSolidParam::DoDataExchange(CDataExchange* pDX)
	{
		CDialog::DoDataExchange(pDX);

		DDX_Text(pDX, IDC_EDIT_FLOOR, m_floor);
		DDX_Text(pDX, IDC_EDIT_HEIGHT, m_height);
	}


	BEGIN_MESSAGE_MAP(vgDlgSolidParam, CDialog)
	END_MESSAGE_MAP()


	// vgDlgSolidParam 消息处理程序

}


void vgGIS3D::vgDlgSolidParam::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类
	UpdateData(TRUE);

	CDialog::OnOK();
}
