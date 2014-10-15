#include <vgStableHeaders.h>
#include <vgGIS3D/vggiContourCreateFacade.h>

#include <vgGIS3D/vggiContour.h>
#include <vgGIS3D/vggiContourManager.h>

#include <vgkernel/vgkBox.h>
#include <vgKernel/vgkPluginManager.h>
#include <vgTerritory/vgtDefinition.h>
#include <limits>
#include <vgGIS3D/vggiDlgContourVtr.h>
#include <vgGIS/vgGisManager.h>
#include <vgGIS3D/vggiProcessingDlg.h>

namespace vgGIS3D
{

	bool ContourCreateFacade::createFromGrdFile(string name, const vector<vgKernel::Vec3>& boundPoints)
	{
		vgKernel::Box area = vgKernel::Box::NULL_BOX;

		// 根据点生成边界
		for (int i=0; i<boundPoints.size(); i++)
		{
			area.merge(boundPoints.at(i));
		}

		CString szFilterFDlg = "噪声格网 (*.grd)|*.grd||";
		CFileDialog fileDlg(TRUE, NULL, NULL, NULL,szFilterFDlg, NULL); 
		
		
		if(fileDlg.DoModal() == IDOK) 
		{
			ContourGeoData *pGeoData = new ContourGeoData;
			GridDataInfo   dataInfo;
			Contour *pContour = new Contour(NULL, name);

			CString  filepath = fileDlg.GetPathName();//获得文件  MessageBox(filepath);//路径名没有包括扩展名
			if( pGeoData->ReadData(filepath) == FALSE )
				return FALSE;
			
			dataInfo = pGeoData->GetDataInfo();

			dataInfo.xMin = area.getMinimum().x;
			dataInfo.xMax = area.getMaximum().x;
			dataInfo.yMin = area.getMinimum().z;
			dataInfo.yMax = area.getMaximum().z;
			pGeoData->setGridDataInfo(dataInfo);

			pContour->setDataDirectly(pGeoData);
			
			pContour->GenerateDefaultContourValues();
			pContour->GenerateContours();
			pContour->setBoundingBox(area);

			ContourManager::getSingleton().addContour(pContour);
			ContourManager::getSingleton().traceAllContour();
		} 

		return TRUE;
	}

	bool ContourCreateFacade::createFromVtrArea(const vector<vgKernel::Vec3>& boundPoints)
	{
//		vgUserInterface::GuiManager::getSingleton().showProcessingDlg(true);
		
// 		vgProcessingDlg dlg1;
// 		dlg1.DoModal();
		vgKernel::Box area = vgKernel::Box::NULL_BOX;
		
		// 根据点生成边界
		for (int i=0; i<boundPoints.size(); i++)
		{
			area.merge(boundPoints.at(i));
		}

		vgDlgContourVtr dlg(area.getSize());
		
		// Edit By FengYK @2010-03-26 22:13
		// 修改了大场景下对话框在双击后等一段时间才弹出的问题
		CWnd* pCWnd = vgKernel::SystemUtility::getCurrentViewWnd();
		pCWnd->SetTimer( 1, 150, NULL );
		
		if (dlg.DoModal() != IDOK)
		{
			pCWnd->SetTimer( 1, 15, NULL );
			return false;
		}
		pCWnd->SetTimer( 1, 15, NULL );

		GisManager::getSingleton().showProcessingDlg(true);
		GisManager::getSingleton().setProcessingInfo("正在进行地形网格采样...");

		vgGIS3D::GisManager::getSingleton().showProcessingDlg(true);

		string name = dlg.getContourName();

		float slice = dlg.getStep();

		int numOfLine = dlg.getNumOfLine();

		// 采样地形
	
		vgKernel::Plugin *pTerrainPlugin 
			= vgKernel::PluginManager::getSingleton().getPluginRef(VGT_DLL_NAME);

		if ( pTerrainPlugin == NULL )
		{
			AfxMessageBox("没有加载地形模块.操作被终止");
			vgGIS3D::GisManager::getSingleton().showProcessingDlg(false);
			return false;
		}

		// 因为使用插件式调用，GIS模块不必依赖地形模块
		pfnTerrainManager_hasTerrainData pfHasTData 
			= (pfnTerrainManager_hasTerrainData)GetProcAddress(pTerrainPlugin->getPluginHandle(), "TerrainManager_hasTerrainData");

		bool haveterrain = (*pfHasTData)();
		if ( haveterrain == false )
		{
			AfxMessageBox("没有加载地形数据.操作被终止");
			vgGIS3D::GisManager::getSingleton().showProcessingDlg(false);
			return false;
		}

		pfnTerrainManager_getElevationByPosition pfGetElevation 
			= (pfnTerrainManager_getElevationByPosition)GetProcAddress(pTerrainPlugin->getPluginHandle(), "TerrainManager_getElevationByPosition");

		GridDataInfo   dataInfo;

		int rows, cols;
			
		rows = area.getSize().z / slice;
		cols = area.getSize().x / slice;
		
		dataInfo.cols = cols;
		dataInfo.rows = rows;
		dataInfo.xMin = area.getMinimum().x;
		dataInfo.xMax = area.getMaximum().x;
		dataInfo.yMin = area.getMinimum().z;
		dataInfo.yMax = area.getMaximum().z;
		dataInfo.maxVal = -std::numeric_limits<float>::infinity();
		dataInfo.minVal = std::numeric_limits<float>::infinity();

		float **ppRawData = new float*[rows];

		TRACE("%d %d \n", rows, cols);

		for (int i=0; i<rows; i++)
		{
			ppRawData[i] = new float[cols];
			float elva;
		
			GisManager::getSingleton().setProcessingProgress((int)(((float)i/rows) * 100));

			for (int j=0; j<cols; j++)
			{
				vgKernel::Vec3 pos(area.getMinimum().x + slice*j, 0, area.getMinimum().z +slice*i);

				bool getok = pfGetElevation(pos, elva , true );

				ppRawData[i][j] = elva;
				TRACE("%f ", elva);
				if (elva < dataInfo.minVal)
				{
					dataInfo.minVal = elva;
				}
				else if (elva > dataInfo.maxVal)
				{
					dataInfo.maxVal = elva;
				}
			}
			TRACE("\n");

		}

		GisManager::getSingleton().setProcessingInfo("开始等值线追踪...");

		createContour(name, area, numOfLine, dataInfo, ppRawData, NULL, true);
	
//		vgUserInterface::GuiManager::getSingleton().showProcessingDlg(false);
		GisManager::getSingleton().showProcessingDlg(false);

		return true;
	}

	bool ContourCreateFacade::createContour(string name, vgKernel::Box area, int numOfLine, GridDataInfo info, float **ppRawData, float* specialVal, bool use3dCoord)
	{
		// Raw数据
		ContourGeoData *pGeoData = new ContourGeoData;
		GridDataInfo   dataInfo = info;
		Contour *pContour = new Contour(NULL, name);
		
		pGeoData->setGridData(ppRawData);
		pGeoData->setGridDataInfo(dataInfo);

		// pGeoData->setGridData(ppRawData);
		pContour->setDataDirectly(pGeoData);


//		pContour->GenerateDefaultContourValues();

		pContour->GenerateContourValues(dataInfo.minVal, dataInfo.maxVal, numOfLine);

		pContour->GenerateContours(true);

		pContour->setBoundingBox(area);

		if (use3dCoord)
		{
			pContour->attachToTerrain();
		}

		ContourManager::getSingleton().addContour(pContour);
		// ContourManager::getSingleton().traceAllContour();

		// vgGIS3D::GisManager::getSingleton().showProcessingDlg(false);

		return true;
	}
}