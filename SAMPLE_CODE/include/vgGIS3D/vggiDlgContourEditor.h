#pragma once

#include <vgGIS/resource.h>
#include <vgGis/vggisDefinition.h>

namespace vgGIS3D
{
	// vgDlgContourEditor 对话框

	class VGG_EXPORT vgDlgContourEditor : public CDialog
	{
		DECLARE_DYNAMIC(vgDlgContourEditor)

	public:
		vgDlgContourEditor(CWnd* pParent = NULL);   // 标准构造函数
		virtual ~vgDlgContourEditor();

		// 对话框数据
		enum { IDD = IDD_CONTOUR_EDITOR };

		afx_msg void vgDlgContourEditor::OnCbnSelNameCombo();
		afx_msg void OnTimer(UINT_PTR nIDEvent);
		afx_msg void OnCheckRender();
		afx_msg void OnBnClickedBtnAdd();
		afx_msg void OnBnClickedBtnDelete();
		afx_msg void OnBnClickedBtnRebuild();
		afx_msg void OnBnClickedBtnAutoColor();
		afx_msg void OnBnClickedBtnGenColor();

		void OnColorBar();

	protected:
		virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
		CButton	m_btnAutoColor;

		DECLARE_MESSAGE_MAP()

	private:
		CStatic m_wndGridLocation;
		CStatic m_colorGridLocation;
		CStatic m_colorBar1;
		CStatic m_colorBar2;

		CBCGPGridCtrl	m_wndGrid;
		CBCGPGridCtrl	m_colorGrid;

		CBCGPColorBar	m_wndColorBar1;
		CBCGPColorBar	m_wndColorBar2;

		CComboBox		m_nameCombo;

		CString			m_info;

		BOOL			m_enableRender;
		
		CButton			m_checker;
		CButton			m_autoColor;

	public:
		virtual BOOL OnInitDialog();
	};

}
