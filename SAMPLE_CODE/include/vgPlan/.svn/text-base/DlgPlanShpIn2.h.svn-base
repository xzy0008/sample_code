#pragma once

#include <vgPlanDLL/resource.h>
#include <vgplan/vgpDefinition.h>

// DlgPlanShpIn2 对话框

namespace vgPlan
{
	class VGP_EXPORT DlgPlanShpIn2 : public CDialog
	{
		DECLARE_DYNAMIC(DlgPlanShpIn2)

	public:
		DlgPlanShpIn2(CWnd* pParent = NULL);   // 标准构造函数
		virtual ~DlgPlanShpIn2();

		// 对话框数据
		enum { IDD = IDD_DLG_PLANIN };

		string getPlanName();

		string getShpName();

	protected:
		virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

		DECLARE_MESSAGE_MAP()
	private:
		CString m_planName;
		CString m_planShpName;
	public:
		virtual BOOL OnInitDialog();
		afx_msg void OnBnClickedOk();
	};
}