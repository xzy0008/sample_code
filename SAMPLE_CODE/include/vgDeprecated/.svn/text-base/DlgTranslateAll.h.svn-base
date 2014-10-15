#pragma once

#include "Resource.h"
// CDlgTranslateAll 对话框

class  VGDEP_EXPORT CDlgTranslateAll : public CDialog
{
	DECLARE_DYNAMIC(CDlgTranslateAll)

public:
	CDlgTranslateAll(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgTranslateAll();

// 对话框数据
	enum { IDD = IDD_TRANSALL };


	vgKernel::Vec3 getTranslateVec() 
	{
		return vgKernel::Vec3( m_fltTransX , m_fltTransY , m_fltTransZ );
	}

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
private:
	float m_fltTransX;
	float m_fltTransY;
	float m_fltTransZ;
	afx_msg void OnBnClickedOk();
public:
	float m_tranX;
};
