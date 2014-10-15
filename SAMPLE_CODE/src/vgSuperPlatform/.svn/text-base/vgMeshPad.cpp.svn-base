// vgMeshPad.cpp : 实现文件
//
#include <vgStableHeaders.h>
#include "stdafx.h"
#include "vgMeshPad.h"

 
 // vgMeshPad 对话框
 
 IMPLEMENT_DYNAMIC(vgMeshPad, CDialog)
 
 vgMeshPad::vgMeshPad(CWnd* pParent /*=NULL*/)
 	: CDialog(vgMeshPad::IDD, pParent)
 {
// 	 m_scrollHelper = new CScrollHelper;
// 	 m_scrollHelper->AttachWnd(this);
// // 
// // 	 // We also set the display size equal to the dialog size.
// // 	 // This is the size of the dialog in pixels as laid out
// // 	 // in the resource editor.
//  	 m_scrollHelper->SetDisplaySize(320, 320);
 }
 
 vgMeshPad::~vgMeshPad()
 {
	// delete m_scrollHelper;
 }
 
 void vgMeshPad::DoDataExchange(CDataExchange* pDX)
 {
 	CDialog::DoDataExchange(pDX);
 }
 
 
 BEGIN_MESSAGE_MAP(vgMeshPad, CDialog)
	// ON_BN_CLICKED(IDC_BUTTON2, &vgMeshPad::OnBnClickedButton2)
	 ON_BN_CLICKED(IDC_MESHPAD_BUTTON1, &vgMeshPad::OnBnClickedMeshpadButton1)
 	 ON_WM_MOUSEACTIVATE()
 	 ON_WM_HSCROLL()
 	 ON_WM_VSCROLL()
 	 ON_WM_MOUSEWHEEL()
 	 ON_WM_SIZE()

 END_MESSAGE_MAP()
 
  
 // vgMeshPad 消息处理程序
 // vgMeshPad.cpp : 实现文件
 //


void vgMeshPad::ConnectNode(vgBaseEntry* node)
{	
 	ASSERT(node->GetType() == VG_ENTRY_MESH);
	 
	p_meshEntry = dynamic_cast<vgMeshEntry*>(node);
	p_meshNode = node;
	//::MessageBox(NULL, p_meshEntry->GetName().c_str(), "Info2", MB_OK);

}
void vgMeshPad::OnBnClickedMeshpadButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	//::MessageBox(NULL, p_meshEntry->GetName().c_str(), "Info2", MB_OK);
	//p_meshNode ;
	::MessageBox(NULL, p_meshEntry->GetName().c_str(), "Info2", MB_OK);

// 	vgBaseEntry *pNode = vgUIController::GetInstance()->GetCurrentSelectedNode();
// 
// 	ASSERT (pNode->GetType() == VG_ENTRY_MESH);
// 
// 	vgMeshEntry* pMeshEntry = dynamic_cast<vgMeshEntry*>(pNode);
// 	if (NULL != pMeshEntry)
// 	{
// 		::MessageBox(NULL, pMeshEntry->GetName().c_str(), "Info", MB_OK);
// 	}
}

 
 int vgMeshPad::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message)
 {
//  	int status = CDialog::OnMouseActivate(pDesktopWnd, nHitTest, message);
//  
//  	// We handle this message so that when user clicks once in the
//  	// dialog, it will be given the focus, and this will allow
//  	// mousewheel messages to be directed to this window.
//  	SetFocus();
//  
//  	return status;
	 return TRUE;
 }


 void vgMeshPad::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
 {
 	//m_scrollHelper->OnHScroll(nSBCode, nPos, pScrollBar);
 }
 
 void vgMeshPad::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
 {
 	//m_scrollHelper->OnVScroll(nSBCode, nPos, pScrollBar);
	 int nCurPos;  
	 int nPrevPos;  
	 CRect rect;  

	 GetClientRect(&rect);  
	 nPrevPos   =   GetScrollPos(SB_VERT);  
	 nCurPos   =   nPrevPos;  
	 switch(nSBCode)  
	 {  
	 case   SB_LEFT:  
		 SetScrollPos(SB_VERT,   0);  
		 ScrollWindow(0,   0);  
		 break;  
	 case   SB_RIGHT:  
		 SetScrollPos(SB_VERT,   100);  
		 ScrollWindow(-rect.Height(),   0);  
		 break;  
	 case   SB_PAGELEFT:  
		 nCurPos   =   nPrevPos   -   10;  
		 if(nCurPos   <   0)  
			 nCurPos   =   0;  
		 SetScrollPos(SB_VERT,   nCurPos);  
		 break;  
	 case   SB_PAGERIGHT:  
		 nCurPos   =   nPrevPos   +   10;  
		 if(nCurPos   >   100)  
			 nCurPos   =   100;  
		 SetScrollPos(SB_VERT,   nCurPos);  
		 break;  
	 case   SB_THUMBPOSITION:  
		 SetScrollPos(SB_VERT,   nPos);  
		 break;  
	 case   SB_THUMBTRACK:  
		 break;  
	 case   SB_LINELEFT:  
		 nCurPos   =   nPrevPos   -   2;  
		 if(nCurPos   <   0)  
			 nCurPos   =   0;  
		 SetScrollPos(SB_VERT,   nCurPos);  
		 break;  
	 case   SB_LINERIGHT:  
		 nCurPos   =   nPrevPos   +   2;  
		 if(nCurPos   >   100)  
			 nCurPos   =   100;  
		 SetScrollPos(SB_VERT,   nCurPos);  
		 break;  
	 case   SB_ENDSCROLL:  
		 break;  
	 }  
	 nCurPos   =   GetScrollPos(SB_VERT);  
	 ScrollWindow(0,   rect.Height()   *   (nPrevPos   -   nCurPos)   /   100);  

	 CDialog::OnVScroll(nSBCode,   nPos,   pScrollBar); 
 }
 
 BOOL vgMeshPad::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
 {
 	//BOOL wasScrolled = m_scrollHelper->OnMouseWheel(nFlags, zDelta, pt);
 
 	//return wasScrolled;
	 return TRUE;
 }
 
 void vgMeshPad::OnSize(UINT nType, int cx, int cy)
 {
 	CDialog::OnSize(nType, cx, cy);
 
// 	if (cy < 320)
// 	{
// 		this->ShowScrollBar(SB_VERT, TRUE);
// 	}
// 	else
// 	{
// 		this->ShowScrollBar(SB_VERT, FALSE);
// 	}

 	//m_scrollHelper->OnSize(nType, cx, cy);
 }
 
//  void vgMeshPad::PostNcDestroy()
 //  {
 //  	m_scrollHelper->DetachWnd();
 //  
 //  	// Delete the C++ instance so the parent does not have
 //  	// to worry about it.
 //  	delete this;
 //  }
 BOOL vgMeshPad::OnInitDialog()
 {
	 __super::OnInitDialog();

	 // TODO:  在此添加额外的初始化
	 SetScrollRange(SB_VERT, 0, 100);   
	 // TODO:  在此添加额外的初始化
	 this->ShowScrollBar(SB_VERT, FALSE);

	 return TRUE;  // return TRUE unless you set the focus to a control
	 // 异常: OCX 属性页应返回 FALSE
 }
