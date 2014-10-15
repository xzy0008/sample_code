#pragma once
#include <vgGIS/resource.h>
#include <vgGIs/vggisDefinition.h>

namespace vgGIS3D
{
	// vgDlgOracleConfig 对话框

	class VGG_EXPORT vgDlgOracleConfig : public CDialog
	{
		DECLARE_DYNAMIC(vgDlgOracleConfig)

	public:
		vgDlgOracleConfig(CWnd* pParent = NULL);   // 标准构造函数
		virtual ~vgDlgOracleConfig();

		// 对话框数据
		enum { IDD = IDD_ORACLE_CONFIG };
		
		string getUser() {  return m_oraUser.GetString(); }
		string getPwd()  { return m_oraPwd.GetString(); }
		string getServ() { return m_oraServ.GetString(); }
		string getSql() { return m_sql.GetString(); }

	protected:
		virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

		DECLARE_MESSAGE_MAP()

		CString m_oraUser;
		CString m_oraPwd;
		CString m_oraServ;
		CString m_sql;

		BOOL	m_remeberInfo;

		virtual void OnOK();
	public:
		virtual BOOL OnInitDialog();
	};

}
