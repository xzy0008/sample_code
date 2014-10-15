#pragma once
#include "resource.h"
#include <string>

using std::string;

// DlgPlanShpIn 对话框

class DlgPlanShpIn : public CDialog
{
	DECLARE_DYNAMIC(DlgPlanShpIn)

public:
	DlgPlanShpIn(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~DlgPlanShpIn();

	string getPlanName()
	{
		return m_cplanName.GetString();
	}

	string getAreaFilePath()
	{
		return m_areaFileName;
	}

	string getRoadFilePath()
	{
		return m_roadFileName;
	}

	string getExlcFilePath()
	{
		return m_exlcFileName;
	}

	string getRegionFilePath()
	{
		return m_regionFileName;
	}

	string getAreaFileName()
	{
		string area = m_areaFileName.substr(m_areaFileName.find_last_of("\\") + 1, 
			m_areaFileName.length()-m_areaFileName.find_last_of("\\")-5);
		
		// AfxMessageBox(area.c_str());

		return area;
	}

	string getRoadFileName()
	{
		string road = m_roadFileName.substr(m_roadFileName.find_last_of("\\") + 1, 
			m_roadFileName.length()-m_roadFileName.find_last_of("\\")-5);
		
		return road;
	}

	string getExlcFileName()
	{
		string exlc = m_exlcFileName.substr(m_exlcFileName.find_last_of("\\") + 1, 
			m_exlcFileName.length()-m_exlcFileName.find_last_of("\\")-5);

		return exlc;
	}

	string getRegionFileName()
	{
		string region = m_regionFileName.substr(m_regionFileName.find_last_of("\\") + 1, 
			m_regionFileName.length()-m_regionFileName.find_last_of("\\")-5);

		return region;
	}

	string getAreaShpName()
	{
		return m_areaFileName;
	}

	string getRegionShpName()
	{
		return m_regionFileName;
	}

	string getRoadShpName()
	{
		return m_roadFileName;
	}

	string getExlcShpName()
	{
		return m_exlcFileName;
	}

	float getRoadWidth()
	{
		return m_roadWidth;
	}

// 对话框数据
	enum { IDD = IDD_DLG_PLANIN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeEdit9();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton12();
	afx_msg void OnBnClickedButton2();

private:
	CString m_cplanName;
	CString m_careaFileName;
	CString m_croadFileName;
	CString m_cexlcFileName;
	CString m_cregionFileName;

 	string m_planName;
 	string m_areaFileName;
 	string m_roadFileName;
 	string m_exlcFileName;
	string m_regionFileName;

public:
	afx_msg void OnBnClickedButton13();
private:
	
protected:
	virtual void OnOK();
private:
	float m_roadWidth;
};
