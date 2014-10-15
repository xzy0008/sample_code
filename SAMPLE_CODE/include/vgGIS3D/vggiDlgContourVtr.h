#pragma once

#include <vgGIS/resource.h>
#include <vgKernel/vgkVec3.h>

namespace vgGIS3D
{
	// vgDlgContourVtr 对话框

	class vgDlgContourVtr : public CDialog
	{
		DECLARE_DYNAMIC(vgDlgContourVtr)

	public:
		vgDlgContourVtr(vgKernel::Vec3 area, CWnd* pParent = NULL);   // 标准构造函数
		
		virtual ~vgDlgContourVtr();

		// 对话框数据
		enum { IDD = IDD_CONTOUR_VTR };
		
	public:
		float getStep() { return m_step; }
		
		int getNumOfLine() { return m_numOfLine; }

		string getContourName() { return m_contourName.GetString(); }
	
	protected:
		virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

		DECLARE_MESSAGE_MAP()

	protected:
		float				m_step;
		int					m_numOfLine;
		vgKernel::Vec3		m_area;
		CString				m_info;
		CString				m_contourName;

	public:
		virtual BOOL OnInitDialog();

	protected:
		virtual void OnOK();
	};

}