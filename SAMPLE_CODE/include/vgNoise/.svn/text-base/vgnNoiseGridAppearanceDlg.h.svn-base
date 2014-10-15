#pragma once

#include <vgNoiseDLL/resource.h>
// NoiseGridAppearance 对话框
namespace vgNoise
{
	class NoiseGridAppearanceDlg : public CDialog
	{
		DECLARE_DYNAMIC(NoiseGridAppearanceDlg)

	public:
		NoiseGridAppearanceDlg(CWnd* pParent = NULL);   // 标准构造函数
		virtual ~NoiseGridAppearanceDlg();
		int m_MapShow;
		int m_GridShow;
		BOOL m_GridShowFlag;
	// 对话框数据
		enum { IDD = IDD_GRID_APPEARANCE };

	protected:
		virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

		DECLARE_MESSAGE_MAP()
	public:
		afx_msg void OnBnClickedAppearanceok();
	};
}

