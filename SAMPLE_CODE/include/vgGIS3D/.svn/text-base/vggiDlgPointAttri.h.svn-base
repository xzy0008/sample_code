#pragma  once

#include <vgGis/Resource.h>
// vgDlgPointAttri 对话框
#include <vgGIS/vggisDefinition.h>
#include <vgGis3d/vggiOGRPipeLineMap.h>

#include <string>

using std::string;

namespace vgGIS3D
{

	class VGG_EXPORT vgDlgPointAttri : public CDialog
	{
		DECLARE_DYNAMIC(vgDlgPointAttri)

	public:
		vgDlgPointAttri(CWnd* pParent = NULL);   // 标准构造函数
		virtual ~vgDlgPointAttri();

		// 对话框数据
		enum { IDD = IDD_POINTATTRIDLG };


		string getSelectLayerName();
	public:
		afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);

	private:
		CStatic m_wndGridLocation;
		CBCGPGridRow *sLastRow;
		CBCGPGridCtrl	m_wndGrid;

	private:
		OGRPipeLineMap *m_ogrPipeLineMap;

	public:
		std::vector<int> m_breakPointsVec;
		std::vector<int> m_impactPointVec;

	protected:
		virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持		

		string m_layerNameStr;

		DECLARE_MESSAGE_MAP()
	public:
		virtual BOOL OnInitDialog();
	protected:
		virtual void OnOK();
		void OnDestroy();
		void OnBnSetPressEidt();
		void OnTimer(UINT_PTR nIDEvent);
		void calculatePressure(int id, double preValue);
		void OnBnSetPointBreak();
		void OnTurnViewToSelect();
	public:
		afx_msg void OnClose();
	};

}