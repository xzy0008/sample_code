

#include <vgStableHeaders.h>

#include <vgKernel/vgkTimelineManager.h>
#include <vgPlan\vgDlgTimeline.h>



// vgDlgTimeline 对话框
namespace vgPlan
{
	IMPLEMENT_DYNAMIC(vgDlgTimeline, CDialog)

	vgDlgTimeline::vgDlgTimeline(CWnd* pParent /*=NULL*/)
		: CDialog(vgDlgTimeline::IDD, pParent)
	{
		m_currentPos = TIMELINE_START;
		m_pause = false;
	}

	vgDlgTimeline::~vgDlgTimeline()
	{
	}

	void vgDlgTimeline::DoDataExchange(CDataExchange* pDX)
	{
		CDialog::DoDataExchange(pDX);

		DDX_Control(pDX, IDC_SLIDER_TIMELINE, m_timelineSlider);
	}


	BEGIN_MESSAGE_MAP(vgDlgTimeline, CDialog)
		ON_WM_DESTROY()
		ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_TIMELINE, &vgDlgTimeline::OnNMCustomdrawSliderTimeline)
		ON_BN_CLICKED(IDC_BUTTON_PLAY, &vgDlgTimeline::OnBnClickedPlay)
		ON_BN_CLICKED(IDC_BUTTON_PAUSE, &vgDlgTimeline::OnBnClickedPause)
		ON_WM_TIMER()

	END_MESSAGE_MAP()


	// vgDlgEdgeBlend 消息处理程序

	BOOL vgDlgTimeline::OnInitDialog()
	{
		CDialog::OnInitDialog();
		
		m_timelineSlider.SetRange(TIMELINE_START, TIMELINE_END);
		m_timelineSlider.SetPos(TIMELINE_START);
		m_timelineSlider.SetTicFreq(5);
		m_timelineSlider.SetPageSize(1);		// 每次单击鼠标改变的大小
		m_timelineSlider.SetLineSize(50);		// 每次按下左右方向键时改变的大小

		UpdateData(FALSE);

		// TODO:  在此添加额外的初始化

		return TRUE;  // return TRUE unless you set the focus to a control
		// 异常: OCX 属性页应返回 FALSE
	}

	void vgDlgTimeline::OnDestroy()
	{
		CDialog::OnDestroy();
		// TODO: 在此处添加消息处理程序代码
		delete this;
	}

	void vgPlan::vgDlgTimeline::OnCancel()
	{
		// TODO: 在此添加专用代码和/或调用基类

		CDialog::OnCancel();
		DestroyWindow();

	}

	void vgDlgTimeline::OnNMCustomdrawSliderTimeline(NMHDR *pNMHDR, LRESULT *pResult)
	{
		LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
		// TODO: 在此添加控件通知处理程序代码
		*pResult = 0;

		UpdateData(TRUE);

		int curPos = m_timelineSlider.GetPos();
		vgKernel::TimelineManager::getSingleton().setCurrentTime(curPos);
	}

	void vgDlgTimeline::OnBnClickedPlay()
	{
		m_currentPos = TIMELINE_START;
		m_pause = false;
		this->SetTimer(1, 40, NULL);
		return;
	}

	void vgDlgTimeline::OnTimer(UINT_PTR nIDEvent)
	{
		if (nIDEvent == 1)
		{
			if (m_pause)
			{
				return;
			}

			if ((m_currentPos >= TIMELINE_START) && (m_currentPos <= TIMELINE_END) )
			{
				m_timelineSlider.SetPos(m_currentPos);
				m_currentPos++;
			}
			else 
			{
				this->KillTimer(1);
				m_currentPos = TIMELINE_START;
				m_timelineSlider.SetPos(m_currentPos);
				m_pause = false;
			}
		}

		CDialog::OnTimer(nIDEvent);
	}

	void vgDlgTimeline::OnBnClickedPause()
	{
		if ((m_currentPos > TIMELINE_START) && (m_currentPos < TIMELINE_END) )
		{
			m_pause = !m_pause;
		}
	}

}

