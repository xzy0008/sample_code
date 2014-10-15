
#include <vgStableHeaders.h>
#include <vgPlan/vgPlanmanager.h>
#include <vgKernel/vgkRendererManager.h>
#include <vgPlan/DlgPlanAreaIn.h>
/*#include <DlgPlanAreaIn.h>*/
#include <vgTerritory/vgtTerrainManager.h>
#include <vgKernel/vgkPluginManager.h>
#include <vgPlan/vgDlgTimeline.h>

namespace vgPlan
{
	vgKernel::Vec3 convertToOpenGLCoordinate(vgKernel::Vec2 point)
	{
		vgKernel::Vec3 p(point.x, 0, -point.y);
		
		return p;
	}

	vgKernel::Vec3 convertToCeometryCoordinate25D(vgKernel::Vec3 point)
	{
		vgKernel::Vec3 p(point.x, -point.z, 0);
		
		return p;
	}

	vgKernel::Vec2 convertToGeometryCoordinate(vgKernel::Vec3 point)
	{	
		return vgKernel::Vec2(point.x, -point.z);
	}

	vgPlanManager::~vgPlanManager()
	{
		for (int i=0; i<m_sceneList.size(); ++i)
		{
			if (m_sceneList[i] != NULL)
			{
				delete m_sceneList[i];

				m_sceneList[i] = NULL;
			}
		}

		m_sceneList.clear();
	}

	bool vgPlanManager::addNewScene(string name)
	{
		vgPlanScene* pNewScene = new vgPlanScene(name);
		
		if (pNewScene == NULL)
		{
			return false;
		}
		m_sceneList.push_back(pNewScene);

		m_activeSceneName = name;

		return true;
	}

	int vgPlanManager::getNumOfScene()
	{
		return m_sceneList.size();
	}

	vgPlanScene* vgPlanManager::getLastScenePtr()
	{
// 		if (m_sceneList.size() == 0)
// 		{
// 			return NULL;
// 		}
// 
// 		return m_sceneList[m_sceneList.size()-1];
		return getActiveScene();
	}

	vgPlanScene* vgPlanManager::getScenePtrByName(string name)
	{
		for (int i=0; i<m_sceneList.size(); i++)
		{
			if (m_sceneList.at(i)->getName() == name)
			{
				return m_sceneList.at(i);
			}
		}

		return NULL;
	}

	void vgPlanManager::render()
	{
 		for (int i=0; i<m_sceneList.size(); i++)
 		{
 			m_sceneList[i]->render();
 		}

		if (m_renderShadow)
		{
			for (int i=0; i<m_sceneList.size(); i++)
			{
				m_sceneList[i]->renderShadow();
			}
		}

		if (m_pSelector != NULL)
		{
			m_pSelector->render();
		}
	}

	void vgPlanManager::updateShadowData()
	{
		m_renderShadow = false;

		for (int i=0; i<m_sceneList.size(); i++)
		{
			m_sceneList.at(i)->updateShadowData();
		}
		
		m_renderShadow = true;
	}
	
	void vgPlanManager::updateGemoData()
	{
		for (int i=0; i<m_sceneList.size(); i++)
		{
			m_sceneList.at(i)->updateGemoData();
		}
	}

	bool vgPlanManager::generateMap()
	{
		return getActiveScene()->generateMap();
	}
// 
// 	bool vgPlanManager::exportAllSceneToShpFile(CString filename)
// 	{
// 		stringstream outString;
// 
// 		const char *pszDriverName = "ESRI Shapefile";
// 		OGRSFDriver *poDriver;
// 		OGRRegisterAll();
// 
// 		poDriver = OGRSFDriverRegistrar::GetRegistrar()->GetDriverByName(
// 			pszDriverName );
// 
// 		if( poDriver == NULL )
// 		{
// 			AfxMessageBox("driver not available.");
// 			return false;
// 		}
// 
// 		OGRDataSource *poDS;
// 		poDS = poDriver->CreateDataSource( "f:\\point_out.shp", NULL );
// 		if ( poDS == NULL )
// 		{
// 			poDS = poDriver->CreateDataSource( "f:\\point_out.shp", NULL );
// 
// 			AfxMessageBox( "Creation of output file failed.");
// 			return false;
// 		}
// 
// 		OGRLayer *poLayer;
// 		poLayer = poDS->CreateLayer( "shpinfo", NULL, wkbPolygon25D, NULL );
// 		if( poLayer == NULL )
// 		{
// 			AfxMessageBox( "Layer creation failed." );
// 			return false;
// 		}
// 
// 		OGRFeatureDefn* def = poLayer->GetLayerDefn();
// 
// 		OGRFieldDefn oField( "ID", OFTString );
// 
// 		oField.SetWidth(32);
// 		if( poLayer->CreateField( &oField ) != OGRERR_NONE )
// 		{
// 			AfxMessageBox( "Creating Name field failed." );
// 			return false;
// 		}
// 		
// 		ShpGroundPtrVec groundList = getActiveScene()->getShpGroundPtrVec();
// 
// 		for ( int i=0; i<groundList.size(); i++ )
// 		{
// 			
// 			OGRGeometry *pGeometry = groundList[i]->getGeometry();
// 
// 			if (pGeometry == NULL)
// 			{
// 				continue;
// 			}
// 
// 			//pSpoly->constructInsectVec();
// 
// 			OGRFeature *poFeature;
// 			poFeature = new OGRFeature( poLayer->GetLayerDefn() );
// 
// 			/*poFeature->SetField( "ID", id.c_str() );*/
// 
// 			if (poFeature->SetGeometry( pGeometry) != OGRERR_NONE)
// 			{
// 				AfxMessageBox( "Failed to set feature in shapefile.\n" );
// 			}
// 
// 			int returnValue = poLayer->CreateFeature( poFeature );
// 
// 			if( returnValue != OGRERR_NONE )
// 			{
// 				OGRwkbGeometryType gtype = pGeometry->getGeometryType();
// 				AfxMessageBox( "Failed to create feature in shapefile.\n" );
// 				return false;
// 			}
// 
// 			// OGRFeature::DestroyFeature(pFeature);
// 			OGRFeature::DestroyFeature(poFeature);
// 			
// 		}
// 
// 
// 		OGRDataSource::DestroyDataSource( poDS );
// 
// 		return true;
// 	}

	bool vgPlanManager::onDeleteRenderer( vgKernel::Renderer* renderer )
	{
		if (renderer->getType() != RENDERER_TYPE_PLANBLOCK)
		{
			return false;
		}

		for (int i=0; i<m_sceneList.size(); i++)
		{
			if (m_sceneList.at(i) != NULL)
			{
				if (m_sceneList.at(i)->onDeleteRenderer(renderer))
				{
					return true;
				}
			}
		}

		return false;
	}

	void vgPlanManager::addRenderer(vgKernel::Renderer *pRenderer)
	{
		vgKernel::RendererManager::getSingleton().addRenderer(pRenderer);
	}
 
 	void vgPlanManager::setSelectorFlag(bool enable)
 	{
		using namespace vgKernel;
		vgKernel::Plugin* _terrainPlug = PluginManager::getSingleton().getPluginRef( VGT_DLL_NAME );

		if ( _terrainPlug == NULL )
		{
			return;
		}

		VGK_DLL_DECLARE_CLASSFUNC( _terrainPlug, TerrainManager, hasTerrainData, pfn1 );

		assert( pfn1 != NULL);

		if ( pfn1() == false ) 
		{
			::MessageBox( AfxGetApp()->m_pMainWnd->m_hWnd, "没有加载地形，无法选择规划区域！", 
				"VR-GIS Platform V2.0", MB_OK | MB_ICONWARNING );
			return;
		}

 		if (enable)
 		{
 			if (m_pSelector != NULL)
 			{
 				delete m_pSelector;
 			}
 
 			m_pSelector = new AreaSelector;
 		}
 		else
 		{
 			if (m_pSelector != NULL)
 			{
 				Vec3Vector re = m_pSelector->getResultVec();
 
 				if (re.size() >= 3)
 				{
 
 					DlgPlanAreaIn dialogIn;
 					if ( dialogIn.DoModal() == IDOK)
 					{
 						string planName = dialogIn.getSchemName();
 
						if( planName.empty() )
						{
							::MessageBox( AfxGetApp()->m_pMainWnd->m_hWnd, "方案名不允许为空！", 
								"VR-GIS Platform V2.0", MB_OK | MB_ICONWARNING );

							return;
						}

 						vgPlanScene *pScene = this->getScenePtrByName(planName);
 						if (pScene == NULL)
 						{
 							this->addNewScene(planName);
 							pScene = this->getScenePtrByName(planName);
 							assert(pScene != NULL);
 						}
 
 						pScene->addBuildingAreaFromPointVec(re, true);
 
						VGK_SHOW("\n区域添加完成，继续进行栅格化操作.\n");

						if (vgPlan::vgPlanManager::getSingleton().calculateGridForCurrentScene(1,1))
						{
							::MessageBox( AfxGetApp()->m_pMainWnd->m_hWnd, "区域添加成功!", 
								"VR-GIS Platform V2.0", MB_OK | MB_ICONASTERISK );
						}
					}

 					/*if (vgPlan::vgPlanManager::getSingleton().calculateGridForCurrentScene(1,1))
 					{
 						AfxMessageBox("区域添加成功");
 					}*/
 				}	

				delete m_pSelector;
				m_pSelector = NULL;
 			}
 		}
 	}
	
	bool vgPlanManager::calculateGridForCurrentScene(int xResolve, int yResovle)
	{
		vgPlan::vgPlanScene *pScene = getActiveScene();
		stringstream outString;

		if (pScene != NULL)
		{
			outString << "方案："<<pScene->getName() << "生成" << xResolve << "," << yResovle <<"栅格 \n";

			VGK_SHOW(outString.str());

			return pScene->caculateGrid(xResolve, yResovle);
		}

		return false;
	}

	bool vgPlanManager::planTimeline()
	{
		bool bCreate;

		vgPlan::vgDlgTimeline *dlg = new vgDlgTimeline;
		bCreate = dlg->Create(vgDlgTimeline::IDD, NULL);
		dlg->ShowWindow(SW_SHOW);
	
		return bCreate;
	}
}
