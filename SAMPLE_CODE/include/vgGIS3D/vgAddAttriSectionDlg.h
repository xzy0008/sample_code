#pragma once

#include <vgGis/Resource.h>
#include <vgGIS/vggisDefinition.h>
#include <vgGIS3D/vggiOGRPipeLineMap.h>
#include <vgGIS3D/vggiGisDataManager.h>
#include <vgGIS3D/vgPipeLayerAttriDlg.h>

#include <string>

// vgPipeAttriDlg 对话框
namespace vgGIS3D
{
	class VGG_EXPORT vgAddSectionInfoDlg : public CDialog
	{
		DECLARE_DYNAMIC(vgAddSectionInfoDlg)

	public:		
		vgAddSectionInfoDlg(CWnd* pParent = NULL);   // 标准构造函数
		virtual ~vgAddSectionInfoDlg();

		// 对话框数据
		enum { IDD = IDD_DLG_ADDSECTION };

	public:
		afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);		
	protected:
		virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

		BOOL OnInitDialog();
		void OnTimer(UINT_PTR nIDEvent);
		virtual void OnOK();
		void OnDestroy();

	private:

		OGRPipeLineMap *m_ogrPipeLineMap;	

		CADORecordset* m_pRecordsetLand;

	public:
		CString m_sectionName;
		CComboBox m_valueType;
		CString m_initValue;
		CString m_wndStr;


		

		DECLARE_MESSAGE_MAP()
		

	};

}//end namespace


