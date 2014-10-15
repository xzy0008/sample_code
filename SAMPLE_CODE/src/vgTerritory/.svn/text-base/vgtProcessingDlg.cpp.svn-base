
#include <vgStableHeaders.h>
#include <vgTerritory/vgtProcessingDlg.h>


namespace vgTerritory
{
	// vgProcessingDlg 对话框

	IMPLEMENT_DYNAMIC(vgtProcessingDlg, CDialog)

		vgtProcessingDlg::vgtProcessingDlg(CWnd* pParent /*=NULL*/)
		: CDialog(vgtProcessingDlg::IDD, pParent)
		, m_proccesingInfo(_T(""))
	{

	}

	vgtProcessingDlg::~vgtProcessingDlg()
	{
	}

	void vgtProcessingDlg::DoDataExchange(CDataExchange* pDX)
	{
		CDialog::DoDataExchange(pDX);
		DDX_Text(pDX, IDC_INFO, m_proccesingInfo);
		DDX_Control(pDX, IDC_PROGRESS_INDICATOR, m_progressBar);
	}


	BEGIN_MESSAGE_MAP(vgtProcessingDlg, CDialog)
	END_MESSAGE_MAP()


	// vgProcessingDlg 消息处理程序

	BOOL vgtProcessingDlg::OnInitDialog()
	{
		CDialog::OnInitDialog();

		m_proccesingInfo = "Processing ... ";
		
		m_progressBar.SetRange(0, 100);

		UpdateData(FALSE);

		// TODO:  在此添加额外的初始化

		return TRUE;  // return TRUE unless you set the focus to a control
		// 异常: OCX 属性页应返回 FALSE
	}

	void vgtProcessingDlg::setInfo(std::string info)
	{
		m_proccesingInfo = info.c_str();

		//UpdateData(FALSE);
		UpdateData(false);
	}

	void vgtProcessingDlg::setProgress(int progress)
	{
		if (progress > 100 || progress < 0)
		{
			return ;
		}

		m_progressBar.SetPos(progress);

		UpdateData(FALSE);
	}

	void vgtProcessingDlg::OnOK()
	{
		// TODO: 在此添加专用代码和/或调用基类

		CDialog::OnOK();
	}

	void vgtProcessingDlg::OnCancel()
	{
		// TODO: 在此添加专用代码和/或调用基类

		CDialog::OnCancel();
	}

	BOOL vgtProcessingDlg::DestroyWindow()
	{
		// TODO: 在此添加专用代码和/或调用基类

		return CDialog::DestroyWindow();
	}

}
