// MainFrm.h : CMainFrame 类的接口
//



#include <vgStableHeaders.h>
#include "EnBitmap.h"

class CVgimgReaderView;

class CMainFrame : public CFrameWnd
{
	
protected: // 仅从序列化创建
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// 属性
protected:
	CSplitterWnd m_wndSplitter;
public:

// 操作
public:

// 重写
public:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// 实现
public:
	virtual ~CMainFrame();
	CVgimgReaderView* GetRightPane();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // 控件条嵌入成员
	CStatusBar  m_wndStatusBar;
	CToolBar24    m_wndToolBar;

	//////////////////////////////////////////////////////////////////////////
	CImageList m_ToolbarImageList;
	//////////////////////////////////////////////////////////////////////////

// 生成的消息映射函数
protected:
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnUpdateViewStyles(CCmdUI* pCmdUI);
	afx_msg void OnViewStyle(UINT nCommandID);
	DECLARE_MESSAGE_MAP()
	afx_msg void OnCreateVgimg();
};


