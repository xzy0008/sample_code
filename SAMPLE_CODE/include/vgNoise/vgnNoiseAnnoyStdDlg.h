#pragma once
#include <vgNoiseDLL/resource.h>


// vgnNoiseAnnoyStdDlg 对话框
namespace vgNoise
{
	class vgnNoiseAnnoyStdDlg : public CDialog
	{
		DECLARE_DYNAMIC(vgnNoiseAnnoyStdDlg)

	public:
		vgnNoiseAnnoyStdDlg(CWnd* pParent = NULL);   // 标准构造函数
		virtual ~vgnNoiseAnnoyStdDlg();
		int m_stdface;

	// 对话框数据
		enum { IDD = IDD_DIALOG_ANNOYSTD };

	protected:
		virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

		DECLARE_MESSAGE_MAP()
	public:
		afx_msg void OnBnClickedOk();
		afx_msg void OnChangeStdFace();
	};
}
