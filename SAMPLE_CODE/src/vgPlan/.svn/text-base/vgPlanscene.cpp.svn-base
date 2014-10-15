
#include <vgStableHeaders.h>

#include <vgplan/vgPlanscene.h>
#include <vgplan/vgPlanmanager.h>
#include <vgPlan/vgPlanground.h>
#include <vgPlan/vgShpPlanground.h>

#include <vgShape/vgshDefinition.h>
#include <vgShape/vgshShapeManager.h>
#include <vgShape/vgshDefinition.h>
#include <vgShape/vgshline.h>
#include <vgShape/vgshMultiLine.h>
#include <vgShape/vgshPolygon.h>

#include <vgkernel/vgkRenderer.h>
#include <vgKernel/vgkPluginManager.h>

namespace vgPlan
{
	vgPlanScene::vgPlanScene(string name) : m_sceneName(name)//, m_currentSchemFloor(0)
	{
		if (name.length() == 0)
		{
			m_sceneName = "noname";
		}

		m_gridResolveX = 0;
		m_gridResolveY = 0;

		m_maxFloor = 0;
		m_minFloor = 0;

 		m_outColorRed = 0.3f;
 		m_outColorGreen = 0.4f;
 		m_outColorBlue = 0.5f;
 		m_outColorAlpha = 0.6f;

		m_buildingAreaList.clear();

// 		m_outColorRed = 0.6f;
// 		m_outColorGreen = 0.6f;
// 		m_outColorBlue = 0.2f;
// 		m_outColorAlpha = 0.8f;
	}

	vgPlanScene::~vgPlanScene()
	{

	}

	bool vgPlanScene::addBuildingAreaFromLayer(string layerName)
	{

		//vgShape::Layer* pLayer = vgShape::ShapeManager::getSingleton().getLayerByShortName(layerName);
		using namespace vgKernel;
		vgKernel::Plugin* plug = PluginManager::getSingleton().getPluginRef( VGSH_DLL_NAME );

		if ( plug == NULL )
		{
			return false;
		}

		VGK_DLL_DECLARE_CLASSFUNC( plug, ShapeManager, getLayerByShortName, pfn1 );

		assert( pfn1 != NULL);

		vgShape::Layer* pLayer = (vgShape::Layer*)pfn1(layerName);
		if (pLayer == NULL)
		{
			return false;
		}

		vgShape::GeometryPointerVec* geovec 
			= pLayer->getGeometries();

		vgKernel::Mat4 mat = pLayer->getMatrix();


		for (int i=0; i<geovec->size(); i++)
		{
			vgBuildingAreaPtr pBuildingArea(new vgBuildingArea());

			vgShape::Geometry *pp = (*geovec)[i];
			
			// 智能指针
			vgShape::OGRFeaturePtr featureSharedPtr = pp->getOGRFeaturePtr();

			if (! featureSharedPtr.isNull())
			{
				if (featureSharedPtr->GetGeometryRef()->getGeometryType() != wkbPolygon && featureSharedPtr->GetGeometryRef()->getGeometryType() != wkbPolygon25D)
				{
					AfxMessageBox("Shp为非Polygon");
					return false;
				}

				if (featureSharedPtr->GetGeometryRef() != NULL)
				{
					// 返回的是Reference 不需要删除 clone后再赋值使用.
					OGRGeometry *pGemo = featureSharedPtr->GetGeometryRef();//->clone();
					pBuildingArea->setGeometry(pGemo, mat);
					m_buildingAreaList.push_back(pBuildingArea);
				}	
				else
				{
					AfxMessageBox("Error Geometry.");
				}
			}
		}

		return true;
	}

	void vgPlanScene::addBuildingAreaFromPointVec(const vector<vgKernel::Vec3>& vec3Vector, bool bRender)
	{
		vgBuildingAreaPtr pBuildingArea(new vgBuildingArea());

		OGRPolygon poly; 
		
		OGRLinearRing rings;


		for (int i=0; i<vec3Vector.size(); i++)
		{
			rings.addPoint(vec3Vector[i].x, -vec3Vector[i].z, vec3Vector[i].y);
		}
		
		poly.addRing(&rings);
		poly.closeRings();

		pBuildingArea->setGeometry(&poly, vgKernel::Mat4::IDENTITY);
		pBuildingArea->setRenderFlag(bRender);

		m_buildingAreaList.push_back(pBuildingArea);

		return ;
	}

// 	bool vgPlanScene::addStreetFromLayer(string layerName, float roadWidth)
// 	{
// 		vgShape::Layer* pLayer = vgShape::ShapeManager::getSingleton().getLayerByShortName(layerName);
// 
// 		if (pLayer == NULL)
// 		{
// 			return false;
// 		}
// 
// 		vgShape::GeometryPointerVec* geovec 
// 			= pLayer->getGeometries();
// 
// 		for (int i=0; i<geovec->size(); i++)
// 		{
// 			vgPlanstreetLinePtr streetSharedPtr(new vgPlanstreetLine);
// 
// 			vgShape::Geometry *pp = (*geovec)[i];
// 
// 			vgShape::LineString *pLine = dynamic_cast<vgShape::LineString*>(pp);
// 			
// 			if (pLine == NULL)
// 			{
// 				AfxMessageBox("Shp为非LineString");
// 
// 				return false;
// 			}
// 
// 			streetSharedPtr->setLinePoints(pLine->getRing(), pLine->getFatherLayer()->getMatrix());
// 			streetSharedPtr->convertLineToPoly((int)roadWidth);
// 
// 			m_streetLineList.push_back(streetSharedPtr);
// 		}
// 		return true;
// 	}
// 
// 	bool vgPlanScene::addExculsiveAreaFromLayer(string layerName)
// 	{
// 		vgShape::Layer* pLayer = vgShape::ShapeManager::getSingleton().getLayerByShortName(layerName);
// 
// 		if (pLayer == NULL)
// 		{
// 			return false;
// 		}
// 
// 		vgShape::GeometryPointerVec* geovec 
// 			= pLayer->getGeometries();
// 
// 		vgKernel::Mat4 mat = pLayer->getMatrix();
// 
// 		for (int i=0; i<geovec->size(); i++)
// 		{
// 			vgShape::Geometry *pp = (*geovec)[i];
// 			vgShape::Polygon *pPoly = dynamic_cast<vgShape::Polygon*>(pp);
// 
// 			if (pPoly == NULL)
// 			{
// 				AfxMessageBox("Shp为非Polygon");
// 
// 				return false;
// 			}
// 
// 			vgShape::OGRFeaturePtr featurePtr = pp->getOGRFeaturePtr();
// 
// 			vgExcludeAreaPtr ecldPtr(new vgExcludeArea);
// 			if (ecldPtr->setGeometry(featurePtr->GetGeometryRef(), mat))
// 			{
// 				m_excldAreaList.push_back(ecldPtr);
// 			}
// 
// 
// 		}
// 		return true;
// 	}

	void vgPlanScene::render()
	{
// 		vector<vgPlanstreetLinePtr>::iterator iter = m_streetLineList.begin();
// 		vector<vgPlanstreetLinePtr>::iterator end_iter = m_streetLineList.end();
// 
// 		while (iter != end_iter)
// 		{
// 			(*iter)->render();
// 			iter ++;
// 		}

//		m_gridMap.render();

 		vector<vgBuildingAreaPtr>::iterator buildIter = m_buildingAreaList.begin();
 		vector<vgBuildingAreaPtr>::iterator buildIterEnd = m_buildingAreaList.end();
 
 		while (buildIter != buildIterEnd)
 		{
 			(*buildIter)->render();
			buildIter ++;
 		}		

	}
// 
 	bool vgPlanScene::generateMap()
 	{
//  		for (int i=0; i<m_groundList.size(); i++)
//  		{
//  			for (int j=0; j<m_streetLineList.size(); j++)
//  			{
//  				OGRGeometry *pGemo = m_streetLineList[j]->getGeometry();
//  				m_groundList[i]->diffGemotry(pGemo);
//  			}
//  
//  			for (int k=0; k<m_excldAreaList.size(); k++)
//  			{
//  				m_groundList[i]->diffGemotry(m_excldAreaList[k]->getGeometry());
//  			}
//  		}
 
 		
 		return true;
 	}

	bool vgPlanScene::caculateGrid(int resolveX, int resolveY)
	{        
		
		for (int i=0; i<m_buildingAreaList.size(); i++)
		{
			if (! m_buildingAreaList[i]->calculateGrid(resolveX, resolveY) )
			{
				return false;
			}
		}

		return true;
	}

	bool vgPlanScene::updateGrid()
	{
// 		for (int i=0; i<m_buildingAreaList.size(); i++)
// 		{
// 			if (! m_buildingAreaList[i]->updateGrid() )
// 			{
// 				return false;
// 			}
// 		}

		return true;	
	}

	void vgPlanScene::setCurrentSchemFloor(int floor)
	{
		if (floor < m_minFloor)
		{
			floor = m_minFloor;
		}

		if (floor > m_maxFloor)
		{
			floor = m_maxFloor;
		}

		for (int i=0; i<m_buildingAreaList.size(); i++)
		{
			m_buildingAreaList[i]->setCurrentSchemFloor(floor);
		}	

		m_currentFloor = floor;
	}

	int vgPlanScene::getNumOfBuilding(int floor)
	{
		int blockNum = 0;

		vector<vgBuildingAreaPtr>::iterator buildIter = m_buildingAreaList.begin();
		vector<vgBuildingAreaPtr>::iterator buildIterEnd = m_buildingAreaList.end();

		while (buildIter != buildIterEnd)
		{
			blockNum += (*buildIter)->getNumOfBuilding(floor);

			buildIter ++;
		}

		return blockNum;
	}

	float vgPlanScene::getFloorAreaRatio(int floor)
	{
		{
			float area = 0.f;

			for (int i=0; i<m_buildingAreaList.size(); i++)
			{
				// area += m_buildingAreaList[i]->getSchemArea(floor);
				area += m_buildingAreaList[i]->getCurrentArea();
			}			

			float groundArea = 0.f;
			

			for (int i=0; i<m_buildingAreaList.size(); i++)
			{
				groundArea += m_buildingAreaList[i]->getArea();
			}

			return area / groundArea;
		}
	}

	void vgPlanScene::matchFloorAreaRatio(int method)
	{
		stringstream outStream;

		float delRat = 1.f - (float)(m_blockParam.floorAreaRatio) / getFloorAreaRatio(m_currentFloor);
		
		if (delRat < 0 || delRat > 1)
		{
			outStream << "目标容积率:"<<m_blockParam.floorAreaRatio << "当前容积率:" << getFloorAreaRatio(m_currentFloor) 
				      << "无需进行优化\n";

			VGK_SHOW(outStream.str().c_str());
			return ;
		}
		else
		{
			outStream << "删除 " << delRat * 100 << "% 体块 \n";
			VGK_SHOW(outStream.str().c_str());
		}
	
		for (int i=0; i<m_buildingAreaList.size(); i++)
		{
			m_buildingAreaList.at(i)->matchFloorAreaRatio(method, delRat);
		}
	}

	bool vgPlanScene::saveCurrentSchemToShpFile(string filename)
	{
		stringstream outString;

		const char *pszDriverName = "ESRI Shapefile";
		OGRSFDriver *poDriver;
		OGRRegisterAll();

		poDriver = OGRSFDriverRegistrar::GetRegistrar()->GetDriverByName(
			pszDriverName );

		if( poDriver == NULL )
		{
			AfxMessageBox("driver not available.");
			return false;
		}

		OGRDataSource *poDS;
		poDS = poDriver->CreateDataSource( filename.c_str(), NULL );
		if ( poDS == NULL )
		{
			// poDS = poDriver->CreateDataSource( "f:\\point_out.shp", NULL );

			AfxMessageBox( "Creation of output file failed.");
			return false;
		}

		OGRLayer *poLayer;
		poLayer = poDS->CreateLayer( this->getName().c_str(), NULL, wkbPolygon25D, NULL );
		if( poLayer == NULL )
		{
			AfxMessageBox( "Layer creation failed." );
			return false;
		}

		OGRFeatureDefn* def = poLayer->GetLayerDefn();

		OGRFieldDefn oField( "Floor", OFTInteger );

		// oField.SetWidth(32);
		if( poLayer->CreateField( &oField ) != OGRERR_NONE )
		{
			AfxMessageBox( "Creating Name field failed." );
			return false;
		}

		//ShpGroundPtrVec groundList = getActiveScene()->getShpGroundPtrVec();

		for (int i=0; i<m_buildingAreaList.size(); i++)
		{
			PlanBoxPointerVec* pVec = m_buildingAreaList.at(i)->getCurrentBlockVec();

			for (int j=0; j<pVec->size(); j++)
			{
				if (pVec->at(j)!= NULL && pVec->at(j)->getVisible())
				{
					OGRGeometry *pGeometry = pVec->at(j)->getboxgeo();
					
					if (pGeometry == NULL)
					{
						continue;
					}

					OGRFeature *poFeature;
					poFeature = new OGRFeature( poLayer->GetLayerDefn() );

					poFeature->SetField( "Floor", pVec->at(j)->getLayerNum() );

					if (poFeature->SetGeometry( pGeometry) != OGRERR_NONE)
					{
						AfxMessageBox( "Failed to set feature in shapefile.\n" );
					}

					int returnValue = poLayer->CreateFeature( poFeature );

					if( returnValue != OGRERR_NONE )
					{
						OGRwkbGeometryType gtype = pGeometry->getGeometryType();
						AfxMessageBox( "Failed to create feature in shapefile.\n" );
						return false;
					}

					// OGRFeature::DestroyFeature(pFeature);
					OGRFeature::DestroyFeature(poFeature);
				}
			}
		}

		OGRDataSource::DestroyDataSource( poDS );

		return true;
	}

	void vgPlanScene::updateGemoData()
	{
		for (int i=0; i<m_buildingAreaList.size(); i++)
		{
			if (m_buildingAreaList[i].getPointer() != NULL)
			{
				m_buildingAreaList[i]->updateGemoData();
			}
		}
	}

	void vgPlanScene::renderShadow()
	{	
		glEnable( GL_DEPTH_TEST );
		glEnable( GL_CULL_FACE );

		glClear(GL_STENCIL_BUFFER_BIT);


		glDisable(GL_LIGHTING);
		glDepthMask(GL_FALSE);
		glDepthFunc(GL_LEQUAL);

		glEnable(GL_STENCIL_TEST);
		glColorMask(0, 0, 0, 0);
		glStencilFunc(GL_ALWAYS, 1, 0xffffffff);

		// first pass, stencil operation decreases stencil value
		glFrontFace(GL_CW);
		glStencilOp(GL_KEEP, GL_KEEP, GL_INCR);

		// 渲染体块阴影
		for (int i=0; i<m_buildingAreaList.size(); i++)
		{
			m_buildingAreaList.at(i)->renderShadow();
		}

		//second pass, stencil operation increases stencil value
		glFrontFace(GL_CCW);
		glStencilOp(GL_KEEP, GL_KEEP, GL_DECR);

		// 渲染体块阴影
		for (int i=0; i<m_buildingAreaList.size(); i++)
		{
			m_buildingAreaList.at(i)->renderShadow();
		}

		glFrontFace(GL_CCW);
		glColorMask(1, 1, 1, 1);

		//draw a shadowing rectangle covering the entire screen

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glStencilFunc(GL_NOTEQUAL, 0, 0xffffffff);
		glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
		glPushMatrix();
		glLoadIdentity();

		glColor4f(0.0f, 0.0f, 0.0f, 0.4f);
		glBegin(GL_TRIANGLE_STRIP);
		{
			glVertex3f(-50, 50,-20);
			glVertex3f(-50,-50,-20);
			glVertex3f( 50, 50,-20);
			glVertex3f( 50,-50,-20);
		}
		glEnd();
		glPopMatrix();
		glDisable(GL_BLEND);

		glDepthFunc(GL_LEQUAL);
		glDepthMask(GL_TRUE);
		//glEnable(GL_LIGHTING);
		glDisable( GL_CULL_FACE );
		glDisable(GL_STENCIL_TEST);
		glShadeModel(GL_SMOOTH);

		glFlush();
	}

	
	bool vgPlanScene::collectGeometries(vector<OGRGeometry*>* pOGRGeometriesOut )
	{
		//vector<OGRGeometry*>* pTempGeometries = new vector<OGRGeometry*>;
		for (int i=0; i<m_buildingAreaList.size(); i++)
		{
			PlanBoxPointerVec* pVec = m_buildingAreaList.at(i)->getCurrentBlockVec();

			for (int j=0; j<pVec->size(); j++)
			{
				if (pVec->at(j)!= NULL && pVec->at(j)->getVisible())
				{
					OGRGeometry *pGeometry = pVec->at(j)->getboxgeo();

					if (pGeometry == NULL)
					{
						continue;
					}
					pOGRGeometriesOut->push_back(pGeometry);
				}
			}
		}

		return true;
	}

	int	vgPlanScene::getCurrentFloor()
	{
		return	m_currentFloor;
	}


}//namespace vgPlan
