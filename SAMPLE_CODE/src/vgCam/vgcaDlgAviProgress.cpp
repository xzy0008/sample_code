// D:\___visualVersion\trunkDLL\src\vgCam\vgcaDlgAviProgress.cpp : 实现文件
//

#include <vgStableHeaders.h>
#include "vgCam/vgcaDlgAviProgress.h"
#include <vgCam/vgcaCamManager.h>
#include <vgLibraryMFCDLL/vgLibraryResource.h>
namespace vgCam
{
	// vgcaDlgAviProgress 对话框

	IMPLEMENT_DYNAMIC(vgcaDlgAviProgress, CDialog)

		vgcaDlgAviProgress::vgcaDlgAviProgress(CWnd* pParent /*=NULL*/)
		: CDialog(vgcaDlgAviProgress::IDD, pParent)
	{

	}

	vgcaDlgAviProgress::~vgcaDlgAviProgress()
	{
	}

	void vgcaDlgAviProgress::DoDataExchange(CDataExchange* pDX)
	{
		CDialog::DoDataExchange(pDX);
	}


	BEGIN_MESSAGE_MAP(vgcaDlgAviProgress, CDialog)
	END_MESSAGE_MAP()


	// vgcaDlgAviProgress 消息处理程序

	BOOL vgcaDlgAviProgress::DestroyWindow()
	{
		// TODO: 在此添加专用代码和/或调用基类

		return CDialog::DestroyWindow();
	}

	void vgcaDlgAviProgress::OnOK()
	{
		// TODO: 在此添加专用代码和/或调用基类

		// 	CDialog::OnOK();
		// 	DestroyWindow();
	}

	void vgcaDlgAviProgress::OnCancel()
	{
		// TODO: 在此添加专用代码和/或调用基类

		vgCam::CamManager::getSingleton().setAviRecordCnt(0);
	}

	BOOL vgcaDlgAviProgress::OnInitDialog()
	{
		CDialog::OnInitDialog();

		//m_progressBar.SetRange(0, 100);
		//setProgress(0);
 		CProgressCtrl *pProgressCtrl = (CProgressCtrl*)GetDlgItem(IDC_AVI_PROGRESS);
 		pProgressCtrl->SetRange(0, 100);
// 		
		setProgress(0);

		return TRUE;  // return TRUE unless you set the focus to a control
		// 异常: OCX 属性页应返回 FALSE
	}

	void vgcaDlgAviProgress::setProgress(int progress)
	{
		CProgressCtrl *pProgressCtrl = (CProgressCtrl*)GetDlgItem(IDC_AVI_PROGRESS);
		pProgressCtrl->SetPos(progress);	
	}

}
