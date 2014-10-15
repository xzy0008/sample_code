#pragma once

#include <vgGis/resource.h>
#include <vgGis/vggisDefinition.h>

namespace vgGIS3D
{

	// vgDlgSolidParam 对话框

	class VGG_EXPORT vgDlgSolidParam : public CDialog
	{
		DECLARE_DYNAMIC(vgDlgSolidParam)

	public:
		vgDlgSolidParam(CWnd* pParent = NULL);   // 标准构造函数
		virtual ~vgDlgSolidParam();

		// 对话框数据
		enum { IDD = IDD_SEL_FIELD };
		
		string getFloorFieldName() { return m_floor.GetString(); }
		string getFloorHeightFieldName() { return m_height.GetString(); }

	protected:
		virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

		DECLARE_MESSAGE_MAP()

		CString		m_floor;
		CString		m_height; 

		virtual void OnOK();
	};


} 

