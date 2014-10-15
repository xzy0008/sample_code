#pragma once

#include <vgNoiseDLL/resource.h>
// NoiseGridPropertyDlg 对话框
namespace vgNoise
{
	class NoiseGridPropertyDlg : public CDialog
	{
		DECLARE_DYNAMIC(NoiseGridPropertyDlg)

	public:
		NoiseGridPropertyDlg(CWnd* pParent = NULL);   // 标准构造函数
		virtual ~NoiseGridPropertyDlg();
	//网格大小
		float datagridxmod;
	   float datagridzmod;
	// 对话框数据
		enum { IDD = IDD_GRID_PROPERTIES };

	protected:
		virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

		DECLARE_MESSAGE_MAP()
	public:
		afx_msg void OnBnClickedCheckGridborder();
		afx_msg void OnBnClickedOk();
	};
}
