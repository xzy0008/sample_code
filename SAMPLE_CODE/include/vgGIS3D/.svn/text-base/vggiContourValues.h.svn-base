// ContourValues.h: interface for the ContourValues class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

/*=============等值线值的辅助管理类=============================*/
//
//该类辅助CContour类，用于编辑和管理所要追踪的等值线值
//
/*==============================================================*/
namespace vgGIS3D
{
	typedef CList<float,float> CValueList;

	class ContourValues  
	{
	public:
		ContourValues();
		~ContourValues();

		ContourValues& operator=(const ContourValues& rhs);

	public:
		void AddValue(float newValue);
		void DeleteValue(float oldValue);
		void RemoveAllValues();
		void ReplaceValue(float oldValue, float newValue);
		void GenerateValues(int numContours, float rangeStart, float rangeEnd);
		int  GetNumberOfValues();
		float GetValue(int i);
		void SetValue(int i, float newValue);

		CValueList& GetValueList(){ return m_Values; }

	#ifdef _DEBUG
		void TraceOutValueList();
	#endif

	private:
		CValueList m_Values;   //要追踪的值

	private:
		ContourValues(const ContourValues&);  // Not implemented.


	};

	inline int ContourValues::GetNumberOfValues() 
	{
		return m_Values.GetCount();
	}

	inline void ContourValues::RemoveAllValues()
	{
		m_Values.RemoveAll();
	}

}