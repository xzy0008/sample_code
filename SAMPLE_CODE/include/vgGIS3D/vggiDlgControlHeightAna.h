#pragma once

#include <vgGis/Resource.h>
#include <vgGIS/vggisDefinition.h>
// vggiDlgControlHeight 对话框
namespace vgGIS3D
{
	class VGG_EXPORT vggiDlgControlHeight : public CDialog
	{
		DECLARE_DYNAMIC(vggiDlgControlHeight)

	public:
		vggiDlgControlHeight(CWnd* pParent = NULL);   // 标准构造函数
		virtual ~vggiDlgControlHeight();

		// 对话框数据
		enum { IDD = IDD_DLG_CONTROL_HEIGHT };

	protected:
		virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

		DECLARE_MESSAGE_MAP()
	public:
		float fControlHeight;
		float getControlHeight();
		void  setControlHeight( float fht );
		virtual BOOL OnInitDialog();
	};
}
