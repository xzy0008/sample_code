#pragma once
#include "Resource.h"
#include "afxwin.h"

#include "vgKernel/vgkSystemUtility.h"
#include "vgDatabase/vgdDatabaseManager.h"
#include "vgDatabase/vgdAccessConnector.h"
#include "vgConf/vgcoExeConfig.h"
#include <vgAutoBuild/vgMarkBuildNode.h>

// CCommentDlg 对话框
namespace vgAutoBuild
{
	using namespace vgDatabase;
	// CCommentDlg 对话框

	class CInforCommentDlg : public CDialog
	{
		DECLARE_DYNAMIC(CInforCommentDlg)

	public:
		CInforCommentDlg(MarkBuildNode* pRenderer = NULL);   // 标准构造函数
		virtual ~CInforCommentDlg();

		// 对话框数据
		enum { IDD = IDD_COMMENT_DLG };

	protected:
		virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

		DECLARE_MESSAGE_MAP()


	public:
		String m_DBFileName;
		String m_UniqueId;
		CEdit m_CommentInput;
		CEdit m_CommentShow;
		CEdit m_UserName;
		BasedConnector *pConnector;

		MarkBuildNode* m_pRenderer;

		afx_msg void OnBnClickedPublishComment();
		BOOL OpenDB(String DBFileName);
		BOOL CloseDB();
		int GetNumber();
		void ShowComment();

		virtual BOOL OnInitDialog();
	
		afx_msg void OnDestroy();

	protected:
		virtual void OnCancel();
	};

}
