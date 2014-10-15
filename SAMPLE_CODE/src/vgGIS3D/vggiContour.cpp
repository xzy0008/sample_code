// Contour.cpp: implementation of the Contour class.
//
//////////////////////////////////////////////////////////////////////

#include <vgStableHeaders.h>
#include <vgGIS3D/vggiContourTracer.h>
#include <vgGIS3D/vggiContourValues.h>
#include <vgGIS3D/vggiContour.h>
#include <vgTerritory/vgtDefinition.h>
#include <vgKernel/vgkPluginManager.h>
#include <vgGIS/vgGisManager.h>

namespace vgGIS3D
{
	//////////////////////////////////////////////////////////////////////
	// Construction/Destruction
	//////////////////////////////////////////////////////////////////////

	Contour::Contour(ContourGeoData* pOwner, string name) : m_defaultColor(vgKernel::ColorVal::Yellow)
	{
		m_pDataOwner = pOwner;
		//m_pContourDrawer = NULL;
		m_Contours.RemoveAll();
		m_bReGenerated = FALSE;

		m_contoursName = name;
		m_use3DRender = false;

		m_visible = true;

		InitializeCriticalSection(&m_editCriticalSection);
	}


	Contour::~Contour()
	{
		RemoveAllContours();

		if (m_pDataOwner != NULL)
		{
			delete m_pDataOwner;
		}

		DeleteCriticalSection(&m_editCriticalSection);
// 		if( m_pContourDrawer != NULL )
// 			delete m_pContourDrawer;
	}

	void Contour::GenerateContours(bool useUIProgressBar)
	{//生成等值线

		int numContours = GetNumberOfValues();
		if( numContours <= 0 )
			return;


		if( this->IsHavingContours() )
		{
			this->RemoveAllContours();
		}

		CContourTracer Tracer;

		
		//给等值线追踪器设置网格数据信息，其值已由读数据时读入结构体CGridDataInfo。
		Tracer.SetGridDataInfo(m_pDataOwner->GetDataInfo());// CGeoData*  m_pDataOwner;GetDataInfo返回的是CGridDataInfo m_DataInfo;
		//给等值线追踪器设置输入，设置追踪器的网格数据为读入的网格数据
		Tracer.SetInput(m_pDataOwner->GetGridData());
		//给等值线追踪器设置输入
		CCurveList *pCurveList;
		for(int i=0; i<numContours; i++)
		{
			if (useUIProgressBar)
			{
				GisManager::getSingleton().setProcessingProgress((int)((float)i / numContours * 100));
			}
			pCurveList = new CCurveList;
			if(pCurveList==NULL)
			{
				AfxMessageBox("内存分配失败!");
				return;
			}

			Tracer.SetOutput(pCurveList);
			if( !Tracer.ExecuteTracing(m_contourValues.GetValue(i)) )
			{
				delete pCurveList;
			}
			else
			{
				m_Contours.Add(pCurveList);
			}		

		}

		m_bReGenerated = TRUE; //重新生成了等值线

	}

	void Contour::RemoveAllContours()
	{
		int num = m_Contours.GetSize();
		if( num > 0 )
		{
			CCurveList* pCurveList;
			for(int i=0; i<num; i++)
			{
				pCurveList = this->m_Contours.GetAt(i);	
				ASSERT( pCurveList!=NULL );

				POSITION pos = pCurveList->GetHeadPosition();						
				while (pos!=NULL) 
				{
					delete pCurveList->GetNext(pos);
				}
				delete pCurveList;
			}

			m_Contours.RemoveAll();
		}
	}

	void Contour::GenerateContourValues(float start, float end, int num)
	{
		float inc = (end-start) / num;  

		float val;

		for(val= start; val<=end; val+=inc)
		{
			m_contourValues.AddValue(val);//将等值线值从小到大插入等值线值列表CValueList m_values;
		}

		TRACE("Value: ");

		for (int i=0; i<m_contourValues.GetNumberOfValues(); i++)
		{
			TRACE("%f - ", m_contourValues.GetValue(i));
		}
	}

#if 0
	void Contour::EditContourLevels()
	{
		CEditContourLevelDlg levelDlg(m_contourValues);


		ASSERT(m_pDataOwner!=NULL);
		levelDlg.SetNoiseMinMax(m_pDataOwner->GetDataInfo().minVal,m_pDataOwner->GetDataInfo().maxVal);

		if( levelDlg.DoModal() == IDOK )
		{
			m_contourValues = levelDlg.m_Levels;

			GenerateContours();

		}

	}

#endif

	void Contour::GenerateDefaultContourValues()
	{//产生缺省值(10等份)

		ASSERT(m_pDataOwner!=NULL);
		float NoiseMin = m_pDataOwner->GetDataInfo().minVal;
		float NoiseMax = m_pDataOwner->GetDataInfo().maxVal;

		float inc = (NoiseMax-NoiseMin)/9; //10等份

		float val;

		for(val= NoiseMin; val<=NoiseMax; val+=inc)
		{
			m_contourValues.AddValue(val);//将等值线值从小到大插入等值线值列表CValueList m_values;
		}
	}

	bool Contour::attachToTerrain()
	{

		vgKernel::Plugin *pTerrainPlugin 
			= vgKernel::PluginManager::getSingleton().getPluginRef(VGT_DLL_NAME);

		if ( pTerrainPlugin == NULL )
		{
			AfxMessageBox("没有加载地形模块.操作被终止");

			return false;
		}

		// 因为使用插件式调用，GIS模块不必依赖地形模块
		pfnTerrainManager_hasTerrainData pfHasTData 
			= (pfnTerrainManager_hasTerrainData)GetProcAddress(pTerrainPlugin->getPluginHandle(), "TerrainManager_hasTerrainData");

		bool haveterrain = (*pfHasTData)();
		if ( haveterrain == false )
		{
			AfxMessageBox("没有加载地形数据.操作被终止");
			return false;
		}

		pfnTerrainManager_getElevationByPosition pfGetElevation 
			= (pfnTerrainManager_getElevationByPosition)GetProcAddress(pTerrainPlugin->getPluginHandle(), "TerrainManager_getElevationByPosition");


		CContourArray& conArr = getContoursArray();
		//获取等值线值列表数目
		int num = GetNumberOfValues();
		if (num==0)
		{
			return false;
		}
		//获取等值线最小值
		float noisemin = GetValue(0);
		float noisemax = GetValue(num-1);
		//获取等值线值列表数目结束
		//设置颜色表最小值，最大值
		/* ColorTable.SetValueRange(pCon->GetDataOwner()->GetDataInfo().NoiseMin,pCon->GetDataOwner()->GetDataInfo().NoiseMax);*/
		// m_ColorTable.SetValueRange(noisemin,noisemax);
		if (conArr.GetCount() == 0)
		{
			return false;
		}

		m_boundingBox = vgKernel::Box::NULL_BOX;

		for (int indexCurList = 0; indexCurList < conArr.GetCount(); indexCurList ++)
		{
			/*float val = list.GetNext(valuepos);*/
			CCurveList* pCurveList = conArr.GetAt(indexCurList);
			if (!pCurveList)
			{
				continue;
			}
			//获取等值线的头位置
			POSITION pos = pCurveList->GetHeadPosition();
			//获取等值线值头位置结束
			//获取等值线的噪声值
			float noisevalue = GetValue(indexCurList);

			// 获取等值线颜色
			// COLORREF   m_LineColor=m_ColorTable.LookUpColor(noisevalue);
			// 等值线颜色结束

			while( pos != NULL )
			{
				CCurve* pCurve = pCurveList->GetNext( pos );

				if (!pCurve)
				{
					continue;
				}

				for (int indexPoint= 0; indexPoint < pCurve->GetCount(); indexPoint ++)
				{
					float elev;

					pfGetElevation(pCurve->GetAt(indexPoint), elev, true);
					pCurve->GetAt(indexPoint).y = elev;
					m_boundingBox.merge(pCurve->GetAt(indexPoint));
				}

			} 
		} 


		return true;
	}

	vgKernel::ColorVal Contour::GetColorByValue(float val)
	{
		map<float, vgKernel::ColorVal>::iterator iter = m_colorTable.begin();
		map<float, vgKernel::ColorVal>::iterator iter_end = m_colorTable.end();
		
		while (iter != iter_end)
		{
			if (iter->first == val)
			{
				return iter->second;
			}
			iter ++;
		}

		return m_defaultColor;
	}

	void Contour::SetColorByValue(float val, vgKernel::ColorVal col)
	{
		map<float, vgKernel::ColorVal>::iterator iter = m_colorTable.begin();
		map<float, vgKernel::ColorVal>::iterator iter_end = m_colorTable.end();

		while (iter != iter_end)
		{
			if (abs(iter->first - val) < 1e-5)
			{
				 iter->second = col;

				 return ;
			}

			iter ++;
		}

		m_colorTable.insert(make_pair(val, col));
	}
	
	bool Contour::useBind(bool wait)
	{
		if (TryEnterCriticalSection(&m_editCriticalSection))
		{
			return true;
		}
		else
		{
			if (wait)
			{
				EnterCriticalSection(&m_editCriticalSection);
			
				return true;
			}

			return false;
		}
	}

	void Contour::unBind()
	{
		LeaveCriticalSection(&m_editCriticalSection);
	}
}