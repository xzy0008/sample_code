
#include <vgStableHeaders.h>
#include <vgGIS3D/vggiDlgInputval.h>

namespace vgGIS3D
{
	// vgDlgInputVal 对话框
	IMPLEMENT_DYNAMIC(vgDlgInputVal, CDialog)

		vgDlgInputVal::vgDlgInputVal(CWnd* pParent /*=NULL*/)
		: CDialog(vgDlgInputVal::IDD, pParent)
	{
		m_val = 0;
	}

	vgDlgInputVal::~vgDlgInputVal()
	{
	}

	void vgDlgInputVal::DoDataExchange(CDataExchange* pDX)
	{
		CDialog::DoDataExchange(pDX);
		DDX_Text(pDX, IDC_EDIT_VAL, m_val);
	}


	BEGIN_MESSAGE_MAP(vgDlgInputVal, CDialog)
	END_MESSAGE_MAP()

	float vgDlgInputVal::getVal()
	{
		return m_val;
	}
	// vgDlgInputVal 消息处理程序

}
