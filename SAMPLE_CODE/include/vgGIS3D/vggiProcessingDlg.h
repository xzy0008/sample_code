#pragma once

#include <vgGIS/resource.h>
#include <vgGIS/vggisDefinition.h>

// vgProcessingDlg 对话框
namespace vgGIS3D
{
	class VGG_EXPORT vgProcessingDlg : public CDialog
	{
		DECLARE_DYNAMIC(vgProcessingDlg)

	public:
		vgProcessingDlg(CWnd* pParent = NULL);   // 标准构造函数
		virtual ~vgProcessingDlg();

		// 对话框数据
		enum { IDD = IDD_PROCESSING };

	public:
		void setProgress(int progress);

		void setInfo(string info);

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
