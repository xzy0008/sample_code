#pragma once

#include "Resource.h"
#include "afxcmn.h"
#include <vgPlan/vgpDefinition.h>

namespace vgPlan
{

	class VGP_EXPORT vgDlgTimeline : public CDialog
	{
		DECLARE_DYNAMIC(vgDlgTimeline)

		public:
		vgDlgTimeline(CWnd* pParent = NULL);   // 标准构造函数
		virtual ~vgDlgTimeline();

		// 对话框数据
		enum { IDD = IDD_DLG_TIMELINE };

		protected:
		virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

		DECLARE_MESSAGE_MAP()


		public:
		virtual BOOL OnInitDialog();
		afx_msg void OnDestroy();

		public:
		CSliderCtrl m_timelineSlider;

		int  m_currentPos;
		bool m_pause;

		afx_msg void OnNMCustomdrawSliderTimeline(NMHDR *pNMHDR, LRESULT *pResult);
		afx_msg void OnBnClickedPlay();
		afx_msg void OnBnClickedPause();
	
		afx_msg void OnTimer(UINT_PTR nIDEvent);
	protected:
		virtual void OnCancel();
	};

}