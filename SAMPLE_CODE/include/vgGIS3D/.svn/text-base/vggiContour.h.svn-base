// vgnContour.h: interface for the Contour class.
//
//////////////////////////////////////////////////////////////////////

#include <vgGIS3D/vggiContourValues.h>
#include <vgGIS3D/vggiContourGeoStruct.h>
#include <vgGIS3D/vggiContourGeoData.h>
#include <vgKernel/vgkBox.h>
#include <vgKernel/vgkColorVal.h>

#include <map>

using std::map;

//#include <vgGIS3D\vgnContourDrawer.h>

#pragma once

namespace vgGIS3D
{
	/*===================等值线类=============================*/
	//                   Contour
	//该类用于保存等值线坐标,管理等值线值，等值线追踪，等值线绘制，等等....
	//
	//管理和编辑等值线值时，引用CContourValues类来完成
	//在生成等值线时，引用CContourTracer等值线追踪类来完成追踪
	//在等值线绘制时，引用CContourDrawer绘制器来绘制
	//
	/*==============================================================*/


	typedef CArray<CGeoPoint,CGeoPoint&> CCurve;			//一条等值线曲线
	typedef CTypedPtrList<CPtrList, CCurve*> CCurveList;	//等值线曲线链表(给定某值的等值线不限于一条)
	typedef CTypedPtrArray<CPtrArray,CCurveList*> CContourArray; 
// 
// 	typedef CTypedPtrArray<CPtrArray,CContourObj*> CContourObjArray;
// 	typedef CTypedPtrArray<CPtrArray,CContourObj*> CContourFillArray;


	class Contour  
	{
	public:

		Contour(ContourGeoData* pOwner=NULL, string name="NoNameContour");

		~Contour();
		string	GetName() { return m_contoursName; }
		
		int		GetNumberOfValues();

		
		// 增加特殊点位
		void	AddContourValue(float newVal);

		// 删除特殊点位
		void	DeleteContourValue(float oldVal);
		void	DeleteAllContourValue();
		// 变更特殊点位
		void	ReplaceContourValue(float oldVal, float newVal);

		// 根据等值线数 起点值 终点值 进行等值线追踪
		void	GenerateContourValues(int numContours, float valStart, float valEnd);
	
		CValueList& GetValueList();
		
		float	GetValue(int i);

		void	SetValueList(CValueList& list);
		
		void	GenerateDefaultContourValues();

		void    GenerateContourValues(float start, float end, int num);

		void	EditContourLevels(); //编辑等值线

		void	GenerateContours(bool useUIProgressBar = false);
		
		void	RemoveAllContours();
 
		void	setBoundingBox(vgKernel::Box box) { m_boundingBox = box; }

		vgKernel::Box getBoundingBox() { return m_boundingBox; }

		void setDataDirectly(ContourGeoData* pOwner)
		{
			m_pDataOwner = pOwner;
		}
		
		ContourGeoData* getDataRef()
		{
			return m_pDataOwner;
		}

		//-----追踪结果---------
		CContourArray& getContoursArray()
		{
			return m_Contours;
		};

		BOOL IsHavingContours(){ return m_Contours.GetSize()>0;}

		void ModifyColorTable()
		{
//			m_pContourDrawer->ModifyColorTable();
		}

		BOOL IsGeneratingAgain(){return m_bReGenerated;}
		
		bool attachToTerrain();

		vgKernel::ColorVal GetColorByValue(float val);

		void SetColorByValue(float val, vgKernel::ColorVal col);

		bool GetVisiable() 
		{
			if (m_visible)
			{
				TRACE("TRUE");
			}
			else
			{
				TRACE("FALSE"); 
			}

			return m_visible; 
		}

		void SetVisiable(bool b) { m_visible = b; }

	public:
		// 同步代码

		bool useBind(bool wait = false);

		void unBind();
		
	protected:
		CRITICAL_SECTION m_editCriticalSection;

	private:
		ContourValues		m_contourValues;	//管理等值线值

		CContourArray		m_Contours;			//等值线追踪结果放在此中

		vgKernel::Box		m_boundingBox;
		
		ContourGeoData*		m_pDataOwner;

		bool				m_use3DRender;

		string				m_contoursName;
		bool				m_visible;

		BOOL m_bReGenerated;					//指示绘制器是否需要重新生成Contour绘制对象的标志

		map<float, vgKernel::ColorVal>	m_colorTable;
		vgKernel::ColorVal				m_defaultColor;

	private:
		Contour(const Contour& rhs);			//not implimented
		Contour& operator=(const Contour& rhs);	//not implimented
	};

	inline int Contour::GetNumberOfValues()
	{
		return m_contourValues.GetNumberOfValues();
	}

	inline void Contour::AddContourValue(float newVal)
	{
		m_contourValues.AddValue(newVal);
	}
	
	inline void Contour::DeleteContourValue(float oldVal)
	{
		m_contourValues.DeleteValue(oldVal);
	}

	inline void Contour::DeleteAllContourValue()
	{
		m_contourValues.RemoveAllValues();
	}
	inline void Contour::ReplaceContourValue(float oldVal, float newVal)
	{
		m_contourValues.ReplaceValue(oldVal,newVal);
	}

	inline void Contour::GenerateContourValues(int numContours, float valStart, float valEnd)
	{
		m_contourValues.GenerateValues(numContours,valStart,valEnd);
	}

	inline CValueList& Contour::GetValueList()
	{ 
		return m_contourValues.GetValueList(); 
	}

	inline float Contour::GetValue(int i)
	{
		return m_contourValues.GetValue(i);
	}

	inline void Contour::SetValueList(CValueList& list)
	{
		m_contourValues.RemoveAllValues();

		POSITION pos = list.GetHeadPosition();
		while(pos!=NULL)
		{
			m_contourValues.AddValue(list.GetNext(pos));
		}

	}
}