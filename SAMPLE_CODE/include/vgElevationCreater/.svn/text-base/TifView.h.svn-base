#pragma once

#include <string>
#include <vgTerritory/vgtGeoGlobalData.h>

using std::string;

// TifView 视图

struct Dataset_t
{
	string dataset_name;

	int startx;
	int starty;

	int sizex;
	int sizey;
};

class TifView : public CScrollView
{
	DECLARE_DYNCREATE(TifView)

protected:
	TifView();           // 动态创建所使用的受保护的构造函数
	virtual ~TifView();

public:
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

public:
	void SetFileVector(std::vector<string> &fileList);
	void ClearDataSet();

protected:
	virtual void OnDraw(CDC* pDC);      // 重写以绘制该视图
	virtual void OnInitialUpdate();     // 构造后的第一次

	DECLARE_MESSAGE_MAP()
	
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);

protected:
	//std::map<GDALDataset*, BYTE*> m_vdataSet;
	//std::vector<string> m_fileList;
	std::map<struct Dataset_t*, BYTE*> m_vdataSet;

	double m_orgiX;
	double m_orgiY;

	DOUBLE	m_lowRightX;
	DOUBLE  m_lowRightY;

	vgTerritory::GeoGlobalData* _globalData;

public:

	void setGlobalData( vgTerritory::GeoGlobalData* globaldata )
	{
		_globalData = globaldata;
	}

	double _interval;

public:
	afx_msg void OnDestroy();
};


