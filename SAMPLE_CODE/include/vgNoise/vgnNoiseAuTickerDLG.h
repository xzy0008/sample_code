#pragma once
#include <vgNoiseDLL/resource.h>


// vgnNoiseAuTickerDLG 对话框
namespace vgNoise
{
		class vgnNoiseAuTickerDLG : public CDialog
		{
			DECLARE_DYNAMIC(vgnNoiseAuTickerDLG)

		public:
			vgnNoiseAuTickerDLG(CWnd* pParent = NULL);   // 标准构造函数
			virtual ~vgnNoiseAuTickerDLG();

		// 对话框数据
			enum { IDD = IDD_DLG_AUTICKER };
			CSliderCtrl	m_AU9;
			CSliderCtrl	m_AU45;
			CSliderCtrl	m_AU4;
			CSliderCtrl	m_AU27;
			CSliderCtrl	m_AU20;
			CSliderCtrl	m_AU2;
			CSliderCtrl	m_AU18;
			CSliderCtrl	m_AU17;
			CSliderCtrl	m_AU1625;
			CSliderCtrl	m_AU12;
			CSliderCtrl	m_AU10;
			CSliderCtrl	m_AU1;



		protected:
			virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
			void UpdateSliderValue(void);
			afx_msg void OnClose();
			virtual BOOL OnInitDialog();
			afx_msg void OnAUTickerClose();
			afx_msg void OnAUTickerReset();
			afx_msg void OnReleasedCaptureAU(UINT id, NMHDR* pNMHDR, LRESULT* pResult);
			DECLARE_MESSAGE_MAP()
		};
}
