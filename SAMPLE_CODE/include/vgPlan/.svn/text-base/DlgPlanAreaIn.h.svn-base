#pragma once

#include "resource.h"
// DlgPlanAreaIn 对话框

namespace vgPlan
{

	class DlgPlanAreaIn : public CDialog
	{
		DECLARE_DYNAMIC(DlgPlanAreaIn)

	public:
		DlgPlanAreaIn(CWnd* pParent = NULL);   // 标准构造函数
		virtual ~DlgPlanAreaIn();

		// 对话框数据
		enum { IDD = IDD_PLAN_AREAIN };

	public:
		string getSchemName()
		{
			return m_schemName.GetString();
		}
	protected:
		virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

		DECLARE_MESSAGE_MAP()
	private:
		CString m_schemName;
	};

}
