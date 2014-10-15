
#include <vgStableHeaders.h>
#include <vgGis/vgGisManager.h>

#include <vgGIS3D/vggiGisDataManager.h>
#include <vgGIS3D/vggiDlgOutRoute.h>
#include "vgGIS/dlgCoordTransform.h"
#include <vgGIS3D/vggiContourManager.h>
#include <vgGIS3D/vggiGisRenderCommmand.h>
#include <vgkernel/vgkRenderCommandManager.h>
#include <vgUIController/vgUIController.h>
#include <vgEntry/vgEntryFactory.h>
#include <vgKernel/vgkSelectManager.h>
#include <vgGIS3D/vggiOGRPipeLineMap.h>


namespace vgGIS3D
{


	//----------------------------------------------------------------
	GisManager::GisManager()
		:vgKernel::Singleton<GisManager>(VGK_SINGLETON_LEFE_GISCOUR)
	{
		_gisAnalysis = NULL;
		m_onEditRoute = false;
		
		m_processingDlg = new vgProcessingDlg;
		m_processingDlg->Create(vgProcessingDlg::IDD, NULL);

		reset();
	}
	
	//----------------------------------------------------------------
	GisManager::~GisManager()
	{
		if (m_processingDlg != NULL)
		{
			delete m_processingDlg;
		}
	}

	bool GisManager::initialise()
	{
		m_pGisRenderCommand = new GisRenderCommand;

		vgKernel::RenderCommandFacade::AddCommand(m_pGisRenderCommand);

		return true;
	}

	bool GisManager::shutdown()
	{
		if (m_pGisRenderCommand != NULL)
		{
			vgKernel::RenderCommandFacade::RemoveCommand(m_pGisRenderCommand);

			m_pGisRenderCommand = NULL;
		}

		return true;
	}

	void GisManager::showProcessingDlg(bool show)
	{
		assert(m_processingDlg != NULL);

		if (show)
		{
			m_processingDlg->ShowWindow(SW_SHOW);
		}
		else
		{
			m_processingDlg->ShowWindow(SW_HIDE);
		}
	}

	void GisManager::setProcessingInfo(string info)
	{
		assert(m_processingDlg != NULL);

		m_processingDlg->setInfo(info);
	}

	void GisManager::setProcessingProgress(int pos)
	{
		assert( m_processingDlg != NULL );

		m_processingDlg->setProgress(pos);
	}

	//----------------------------------------------------------------
	void GisManager::setGisAnalysis( EGisState eType )
	{
		bool bDelete = false, bCreate = false;

		if( _gisAnalysis != NULL )
		{
			bDelete = true;
		}

		if ( _gisAnalysis == NULL 
			|| _gisAnalysis->getGisState() != eType )
		{
			bCreate = true;
		}

		if (bDelete)
		{
			delete _gisAnalysis;
			_gisAnalysis = NULL;
		}

		if (bCreate)
		{
			_gisAnalysis = new GisAnalysis(eType);
		}

	}


	
	//----------------------------------------------------------------
	GisAnalysis* GisManager::getGisAnalysis()
	{
		return _gisAnalysis;
	}


	
	//----------------------------------------------------------------
	vgGIS3D::EGisState GisManager::getAnalysisType()
	{
		if (getGisAnalysis())
		{
			return	getGisAnalysis()->getGisState();
		}
		else
		{
			return	GisNone;
		}
	}

	
	//----------------------------------------------------------------
	void GisManager::uninitBeforeOpenGLDestroy()
	{
		reset();
	}

	
	//----------------------------------------------------------------
	void GisManager::renderGisElements()
	{
		GisDataManager::getSingleton().renderShapes();

		if (_gisAnalysis)
		{
			_gisAnalysis->renderGisElements();
		}

		m_ogrRouteMap.render();
		m_ogrPipeLineMap.render();

		m_routeBuilder.render();

		// vgGIS3D::ContourManager::getSingleton().render();
	}

	
	//----------------------------------------------------------------
	void GisManager::reset()
	{
		if (_gisAnalysis)
		{
			delete _gisAnalysis;
			_gisAnalysis = NULL;
		}
	}
	
	//----------------------------------------------------------------
	bool GisManager::getMeasurePointFlag()
	{
		if ( _gisAnalysis == NULL )
		{
			return false;
		}
		else
		{
			if ( _gisAnalysis->getGisState() == GisCoordinate )
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		
	}
	//----------------------------------------------------------------
	bool GisManager::getMeasureDistanceFlag()
	{
		if ( _gisAnalysis == NULL )
		{
			return false;
		}
		else
		{
			if ( _gisAnalysis->getGisState() == GisDistance )
			{
				return true;
			}
			else
			{
				return false;
			}
		}

	}

	//----------------------------------------------------------------
	bool GisManager::getMeasureAreaFlag()
	{
		if ( _gisAnalysis == NULL )
		{
			return false;
		}
		else
		{
			if ( _gisAnalysis->getGisState() == GisArea )
			{
				return true;
			}
			else
			{
				return false;
			}
		}

	}
	
	//----------------------------------------------------------------
	bool GisManager::getFaecherAnalysisFlag()
	{
		if ( _gisAnalysis == NULL )
		{
			return false;
		}
		else
		{
			if ( _gisAnalysis->getGisState() == GisFaecher )
			{
				return true;
			}
			else
			{
				return false;
			}
		}

	}

	//----------------------------------------------------------------
	bool GisManager::getBufferAnalysisFlag()
	{
		if ( _gisAnalysis == NULL )
		{
			return false;
		}
		else
		{
			if ( _gisAnalysis->getGisState() == GisBuffer )
			{
				return true;
			}
			else
			{
				return false;
			}
		}

	}

	bool GisManager::getBufferShapeAnalysisFlag()
	{
		if ( _gisAnalysis == NULL )
		{
			return false;
		}
		else
		{
			if ( _gisAnalysis->getGisState() == GisBufferShape )
			{
				return true;
			}
			else
			{
				return false;
			}
		}

	}

	bool GisManager::getBufferModelAnalysisFlag()
	{
		if ( _gisAnalysis == NULL )
		{
			return false;
		}
		else
		{
			if ( _gisAnalysis->getGisState() == GisBufferModel )
			{
				return true;
			}
			else
			{
				return false;
			}
		}

	}

	bool GisManager::getEditRouteFlag()
	{
		return m_onEditRoute;
	}

	bool GisManager::onEditRoute()
	{
		if (m_onEditRoute)
		{
			m_onEditRoute = false;
			if (_gisAnalysis)
			{
				_gisAnalysis->reset();
				_gisAnalysis->setGisState(GisNone);
			}

			vgDlgOutRoute dlg;
			if (dlg.DoModal() == IDOK)
			{
				DeleteFile(dlg.getSavePath().c_str());
				m_routeBuilder.saveToFile(dlg.getSavePath().c_str(), dlg.getLayerName());
			}
			else
			{
				m_routeBuilder.reset();
			}
		}
		else
		{
			m_onEditRoute = true;
			vgGIS3D::GisManager::getSingleton().setGisAnalysis(vgGIS3D::GisEidtRoute);
		}

		return true;
	}

	void GisManager::addRouteToBuilder(const vector<vgKernel::Vec3>& pointVec)
	{
		m_routeBuilder.addRoute(pointVec);
	}

	void GisManager::addRouteFromLayer(string layerName)
	{
		// AfxMessageBox("Add here");
		m_ogrRouteMap.constructFromBreakShapeLayer(layerName);
	}

	void GisManager::ConstructPipeFromLayer(string layerName)
	{
		// AfxMessageBox("Add here");
		m_ogrPipeLineMap.constructFromBreakShapeLayer(layerName);
	}

	OGRPipeLineMap* GisManager::addPipeLineFromLayer(string layerName)
	{
		// AfxMessageBox("Add here");
		m_ogrPipeLineMap.convertShapeLayerToPipe(layerName);
		//------------------------------------------
		// 向RendererManager中添加renderer
		//------------------------------------------
		vgKernel::RendererQueue* queue = 
			vgKernel::RendererManager::getSingleton().addRenderer( &m_ogrPipeLineMap );

		return &m_ogrPipeLineMap;		
	}

	int GisManager::addRouteStarEndPoint(vgKernel::Vec3 point)
	{
		static int invokeCnt = 0;

		if (invokeCnt == 0)
		{
			m_ogrRouteMap.setStartPoint(point);
			invokeCnt ++;

			return 1;
		}
		else
		{
			m_ogrRouteMap.setEndPoint(point);
			invokeCnt = 0;
			
			return 2;
		}
		
		return 0;
	}

	void GisManager::vgCoordinateTransform()
	{
		CdlgCoordTransform *pDlgCoordTrans = new CdlgCoordTransform;
		pDlgCoordTrans->Create(CdlgCoordTransform::IDD,NULL);
		pDlgCoordTrans->ShowWindow(SW_SHOW);

	}

	//OGRPipeLineMap* GisManager::addPipeLineEntry( vgKernel::Renderer *pRenderer )
	//{
	//	OGRPipeLineMap *pPipeLine = new OGRPipeLineMap(pRenderer);
	//	vgBaseEntry* entry = vgEntryFactory::createEntryFromRenderer( pPipeLine );
	//	HTREEITEM	hRoot = vgUI::UIController::getSingleton().getEntryRootItemByType(STATIC_ENTRY_PIPELINE);

	//	vgUI::UIController::getSingleton().AddNode(hRoot , entry );
	//	vgUI::UIController::getSingleton().GetWorkSpaceBar()->Expand(hRoot);
	//	vgUI::UIController::getSingleton().GetWorkSpaceBar()->EnsureVisible(hRoot);
	//	//m_triggerList.push_back(pTrigger);

	//	vgKernel::RendererManager::getSingleton().addRenderer(pPipeLine);

	//	return pPipeLine;

	//}

	bool GisManager::getVer_Hor_SlopeFlag()
	{
		if ( _gisAnalysis == NULL )
		{
			return false;
		}
		else
		{
			if ( _gisAnalysis->getGisState() == GisVer_Hor_Slope )
			{
				return true;
			}
			else
			{
				return false;
			}
		}

	}
	
	bool GisManager::getControlHtFlag()
	{
		if ( _gisAnalysis == NULL )
		{
			return false;
		}
		else
		{
			if ( _gisAnalysis->getGisState() == GisControlHeight )
			{
				return true;
			}
			else
			{
				return false;
			}
		}
	}


}//vgGIS3D命名空间结束

