// vgnNoiseGeoData.h: interface for the CNoiseGeoData class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GEODATA_H__5DFAFE72_948C_402A_B470_3721DB3DA1D8__INCLUDED_)
#define AFX_GEODATA_H__5DFAFE72_948C_402A_B470_3721DB3DA1D8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "vgNoise\vgnNoiseGeoStruct.h"
namespace vgNoise
{
	class CNoiseGeoData  
	{
	public:
		CNoiseGeoData();
		virtual ~CNoiseGeoData();

	public:
		//´ÅÅÌÎÄ¼þ²Ù×÷
		BOOL ReadData(CString pathName);
		BOOL SaveData(CString pathName);
		//BOOL CNoiseGeoData::CalculateData(int rows, int cols);
		BOOL CNoiseGeoData::CalculateData(int rows, int cols,float stepx,float stepz);
		BOOL CNoiseGeoData::WriteCalData(int i, int j, DOUBLE noiseval);
		//
		CGridDataInfo& GetDataInfo(){return m_DataInfo;}
		float** GetGridData(){return m_ppGridData;}

	private:
		CGridDataInfo m_DataInfo;
		float ** m_ppGridData;

	private:
		CNoiseGeoData(const CNoiseGeoData&);
		CNoiseGeoData& operator=(const CNoiseGeoData&);
	};
}
#endif // !defined(AFX_GEODATA_H__5DFAFE72_948C_402A_B470_3721DB3DA1D8__INCLUDED_)
