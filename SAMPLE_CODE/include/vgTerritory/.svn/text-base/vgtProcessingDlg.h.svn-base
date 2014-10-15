#pragma once

#include <vgTerritoryDLL/vgTerritoryResource.h>


// vgProcessingDlg 对话框
namespace vgTerritory
{
	class vgtProcessingDlg : public CDialog
	{
		DECLARE_DYNAMIC(vgtProcessingDlg)

	public:
		vgtProcessingDlg(CWnd* pParent = NULL);   // 标准构造函数
		virtual ~vgtProcessingDlg();

		// 对话框数据
		enum { IDD = IDD_PROCESSING };

	public:
		void setProgress(int progress);

		void setInfo(std::string info);

	protected:
		virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

		DECLARE_MESSAGE_MAP()
		CString m_proccesingInfo;
		CProgressCtrl m_progressBar;

	public:
		virtual BOOL OnInitDialog();


	protected:
		virtual void OnOK();
		virtual void OnCancel();
	public:
		virtual BOOL DestroyWindow();
	};

}
