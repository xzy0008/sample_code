#pragma once

#include <vgGis/Resource.h>
// vgDlgSelLayer 对话框
#include <vgGIS/vggisDefinition.h>

#include <string>

using std::string;

namespace vgGIS3D
{

	class VGG_EXPORT vgDlgSelLayer : public CDialog
	{
		DECLARE_DYNAMIC(vgDlgSelLayer)

	public:
		vgDlgSelLayer(CWnd* pParent = NULL);   // 标准构造函数
		virtual ~vgDlgSelLayer();

		// 对话框数据
		enum { IDD = IDD_ROUTE_LAYER_SEL };


		string getSelectLayerName();

	protected:
		virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

		CComboBox m_layerNameCombo;

		string m_layerNameStr;

		DECLARE_MESSAGE_MAP()
	public:
		virtual BOOL OnInitDialog();
	protected:
		virtual void OnOK();
	};

}
