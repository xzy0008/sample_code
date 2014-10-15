// VgimgReaderView.h : CVgimgReaderView 类的接口
//


#pragma once

#include <afxcview.h>
#include "VgimgReaderDoc.h"

#define	THUMBNAIL_WIDTH		100
#define	THUMBNAIL_HEIGHT	100


class CVgimgReaderView : public CListView
{
protected: // 仅从序列化创建
	CVgimgReaderView();
	DECLARE_DYNCREATE(CVgimgReaderView)

// 属性
public:
	CVgimgReaderDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // 构造后第一次调用

	//////////////////////////////////////////////////////////////////////////
private:
	CImageList m_LargeImageList;
	CImageList m_SmallImageList;
	CImageList m_StateImageList;

	String m_CurrentArchiveFile;

	CImageList	m_ImageListThumb;		// image list holding the thumbnails

	CMenu m_BackgroundMenu;
	//////////////////////////////////////////////////////////////////////////

// 实现
public:
	virtual ~CVgimgReaderView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	afx_msg void OnStyleChanged(int nStyleType, LPSTYLESTRUCT lpStyleStruct);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	bool updateAll(void);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);

	void setCurrentArchiveFile( const String& archive )
	{
		this->m_CurrentArchiveFile = archive;
		assert( !archive.empty() );
	}
	afx_msg void OnLeftviewRefresh();
	afx_msg void OnNMRclick(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnViewLargeicon();
	afx_msg void OnViewSmallicon();
	afx_msg void OnViewList();
	afx_msg void OnViewDetails();
};

#ifndef _DEBUG  // VgimgReaderView.cpp 中的调试版本
inline CVgimgReaderDoc* CVgimgReaderView::GetDocument() const
   { return reinterpret_cast<CVgimgReaderDoc*>(m_pDocument); }
#endif

