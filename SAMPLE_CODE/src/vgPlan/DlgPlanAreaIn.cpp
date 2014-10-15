#include "vgStableHeaders.h"
#include "vgplan/DlgPlanAreaIn.h"
// DlgPlanAreaIn 对话框

namespace vgPlan
{

	IMPLEMENT_DYNAMIC(DlgPlanAreaIn, CDialog)

		DlgPlanAreaIn::DlgPlanAreaIn(CWnd* pParent /*=NULL*/)
		: CDialog(DlgPlanAreaIn::IDD, pParent)
		, m_schemName(_T("新方案"))
	{

	}

	DlgPlanAreaIn::~DlgPlanAreaIn()
	{
	}

	void DlgPlanAreaIn::DoDataExchange(CDataExchange* pDX)
	{
		CDialog::DoDataExchange(pDX);
		DDX_Text(pDX, IDC_SCHEM, m_schemName);
	}


	BEGIN_MESSAGE_MAP(DlgPlanAreaIn, CDialog)
	END_MESSAGE_MAP()


	// DlgPlanAreaIn 消息处理程序

}
