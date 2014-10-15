#pragma once
#include <vgGis/Resource.h>
#include <vgGIS/vggisDefinition.h>
#include <vgGis3d/vggiOGRPipeLineMap.h>

#include <string>

// vggiPipeInfoResearchDlg 对话框
namespace vgGIS3D
{	
	class VGG_EXPORT vggiPipeInfoResearchDlg : public CDialog
	{
		DECLARE_DYNAMIC(vggiPipeInfoResearchDlg)

	public:
		vggiPipeInfoResearchDlg(CWnd* pParent = NULL);   // 标准构造函数
		virtual ~vggiPipeInfoResearchDlg();

		// 对话框数据
		enum { IDD = IDD_DLG_PIPEINFO_SEARCH };
	public:
		enum  ChoiceMode
		{			
			MODE_IN_MATERIAL,
			MODE_IN_DATE,
			MODE_IN_HANDLINGTYPE,
			MODE_IN_REGION
		};

	protected:
		virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	private:
		CStatic m_wndGridLocation;
		//CBCGPGridRow *pRow;
		CBCGPGridCtrl	m_wndGrid;
		CComboBox m_selectTyple;

        OGRPipeLineMap *m_ogrPipeLineMap;
		ChoiceMode m_choiceMode;
	private:
		struct eachRow 
		{
			int ID;
			CString keyName;
		};		

		std::vector <eachRow> m_tripleHandlingVec;
		std::vector <eachRow> m_fourHandlingVec;
		std::vector <eachRow> m_valvesVec;
		std::vector <eachRow> m_pipeLineVec;
	public:
		//std::vector<CBCGPGridRow*> m_tripleHandlingVec;
		//std::vector<CBCGPGridRow*> m_fourHandlingVec;
		//std::vector<CBCGPGridRow*> m_valvesVec;
		//std::vector<CBCGPGridRow*> m_pipeLineVec;

		//std::vector <CString> m_tripleHandlingVec;
		//std::vector <CString> m_fourHandlingVec;
		//std::vector <CString> m_valvesVec;
		//std::vector <CString> m_pipeLineVec;

		DECLARE_MESSAGE_MAP()
	public:
		virtual BOOL OnInitDialog();
		void OnTimer(UINT_PTR nIDEvent);

	private:
		void getValue();
		void getHandlingValue(ChoiceMode mode);
		
	private:
		afx_msg void OnBnClickedRadioMaterial();
		afx_msg void OnBnClickedRadioDate();
		afx_msg void OnBnClickedRadioHandlingType();
		afx_msg void OnBnClickedRadioRegion();
		afx_msg void OnCbnSelchangeTyle();
		afx_msg void OnTurnSelectToView();
		

	};
}


