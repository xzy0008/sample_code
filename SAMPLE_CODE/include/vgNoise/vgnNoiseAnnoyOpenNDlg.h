#pragma once
#include <vgNoiseDLL/resource.h>


// vgnNoiseAnnoyOpenNDlg 对话框
namespace vgNoise
{
		class vgnNoiseAnnoyOpenNDlg : public CDialog
		{
			DECLARE_DYNAMIC(vgnNoiseAnnoyOpenNDlg)

		public:
			vgnNoiseAnnoyOpenNDlg(CWnd* pParent = NULL);   // 标准构造函数
			virtual ~vgnNoiseAnnoyOpenNDlg();
			BOOL m_AnnoyShowFlag;

		// 对话框数据
			enum { IDD = IDD_DIALOG_ANNOPEN };

		protected:
			virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

			DECLARE_MESSAGE_MAP()
		public:
			afx_msg void OnBnClickedButtonAnnoyopenok();
		};
}
