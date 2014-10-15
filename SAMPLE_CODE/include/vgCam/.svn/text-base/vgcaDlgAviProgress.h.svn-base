#pragma once

#include <vgLibraryMFCDLL/vgLibraryResource.h>
#include "afxcmn.h"
#include "afxwin.h"

// vgcaDlgAviProgress 对话框
namespace vgCam
{
	class vgcaDlgAviProgress : public CDialog
	{
		DECLARE_DYNAMIC(vgcaDlgAviProgress)

	public:
		vgcaDlgAviProgress(CWnd* pParent = NULL);   // 标准构造函数
		virtual ~vgcaDlgAviProgress();

		// 对话框数据
		enum { IDD = IDD_AVI_PROGRESS };

	public:
		void setProgress(int progress);

	protected:
		virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

		DECLARE_MESSAGE_MAP()
	public:
		virtual BOOL DestroyWindow();
	protected:
		virtual void OnOK();
		virtual void OnCancel();
	public:
		virtual BOOL OnInitDialog();
	};

}
