// vgnNoiseGeoData.h: interface for the ContourGeoData class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

#include <vgGIS3D\vggiContourGeoStruct.h>

namespace vgGIS3D
{
	class ContourGeoData  
	{
	public:
		ContourGeoData();
		virtual ~ContourGeoData();

	public:
		//´ÅÅÌÎÄ¼þ²Ù×÷
		BOOL ReadData(CString pathName);
		BOOL SaveData(CString pathName);

		GridDataInfo GetDataInfo(){return m_dataInfo;}
		
		float** GetGridData(){return m_ppGridData;}
		
		void setGridData(float **pData)
		{
			m_ppGridData = pData;
		}

		void setGridDataInfo(GridDataInfo dataInfo)
		{
			m_dataInfo = dataInfo;		
		}
		
		bool destoryData();

	private:

		GridDataInfo m_dataInfo;

		float ** m_ppGridData;
	
	private:
		ContourGeoData(const ContourGeoData&);

		ContourGeoData& operator=(const ContourGeoData&);
	};
}