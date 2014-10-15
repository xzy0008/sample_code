#pragma once
#include <vgGIS/resource.h>

namespace vgGIS3D
{
	// vgDlgInputVal 对话框

	class vgDlgInputVal : public CDialog
	{
		DECLARE_DYNAMIC(vgDlgInputVal)

	public:
		vgDlgInputVal(CWnd* pParent = NULL);   // 标准构造函数
		virtual ~vgDlgInputVal();

		// 对话框数据
		enum { IDD = IDD_DIALOG_INPUT };

		float getVal();

	protected:
		virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
		DECLARE_MESSAGE_MAP()
	
	protected:

		float m_val; 

	};

}



