#pragma once

#include <vgGis/Resource.h>
#include <vgGIS/vggisDefinition.h>
#include <vgGis3d/vggiOGRPipeLineMap.h>

#include <string>

// vgPipeAttriDlg 对话框
namespace vgGIS3D
{
	class VGG_EXPORT vgPipeAttriDlg : public CDialog
	{
		DECLARE_DYNAMIC(vgPipeAttriDlg)

	public:
		vgPipeAttriDlg(CWnd* pParent = NULL);   // 标准构造函数
		virtual ~vgPipeAttriDlg();

		// 对话框数据
		enum { IDD = IDD_DLG_PIPELINE_ATTRI };

	public:
		afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);		
	protected:
		virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

		BOOL OnInitDialog();
		void OnTimer(UINT_PTR nIDEvent);
		virtual void OnOK();
		void OnDestroy();
		void OnBnSetFault();
		void OnTurnSelectToView();

	private:
		CStatic m_wndGridLocation;
		CBCGPGridRow *sLastRow;
		CBCGPGridCtrl	m_wndGrid;

		OGRPipeLineMap *m_ogrPipeLineMap;

		DECLARE_MESSAGE_MAP()
		
	};

}//end namespace


