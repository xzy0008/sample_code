#include <vgStableHeaders.h>
#include <vgGis3D/vggiDxfReader.h>
#include <vgKernel/vgkRendererManager.h>
#include <vgUIController/vgUIController.h>
#include <vgEntry/vgGisDataSourceEntry.h>
#include <vgEntry/vgGisLayerEntry.h>
#include <vgEntry/vgEntryFactory.h>

#include <vgGIS3D/vggiPoint.h>
#include <vgGIS3D/vggiLine.h>
#include <vgGIS3D/vggiPolygon.h>
#include <vgGIS3D/vggiMultiLine.h>
#include <vgGIS3D/vggiMultiPolygon.h>

#include <vgGIS3D/vggiGisDataManager.h>
#include <vgGIS3D/vggiDxfReader.h>

namespace vgGIS3D
{
	bool DxfReader::ReaderFromFile(string filePath)
	{
		OGRDataSource *poDS;

		RegisterOGRDXF();

		poDS = OGRSFDriverRegistrar::Open( filePath.c_str(), FALSE );

		if (poDS == NULL)
		{
			AfxMessageBox("Open Dxf DataSource Failed.");

			return false;
		}

		int cntOfLayer = poDS->GetLayerCount();

		OGRLayer *pLayer = poDS->GetLayerByName("entities");

		if(pLayer == NULL)
		{
			AfxMessageBox("Read error.");

			return false;
		}

		LayerPtr layerPtr = readLayerFromOGRLayer(pLayer);
		layerPtr->setLayerType(Layer_Type_DXF);

		if (pLayer == NULL)
		{
			AfxMessageBox("Process dxf Error. \n");

			OGRDataSource::DestroyDataSource( poDS );

			return false;
		}

		LayerPtrVector *pLayerPtrVec = new LayerPtrVector;
		pLayerPtrVec->push_back(layerPtr);

		DataSourcePtr dsp( new DataSource( filePath , poDS , pLayerPtrVec, DataSource_OCI , true) );
// 
 		vgGIS3D::GisDataManager::getSingleton().getDataSources()->insert(make_pair(
 			dsp->getSourcePath(), dsp));

		// 添加datasourceetnry
		GisDataSourceEntry* ds = new GisDataSourceEntry( dsp );

		vgUI::UIController::getSingleton().addEntryToRootByName("GIS Layer", ds );

		vgBaseEntry* entry = vgEntryFactory::createEntryFromRenderer( pLayerPtrVec->at(0).getPointer() );

		if (entry)
		{
			vgUI::UIController::getSingleton().AddNode(ds , entry );
		}

		//------------------------------------------
		// 向RendererManager中添加renderer
		//------------------------------------------
		vgKernel::RendererQueue* queue = 
			vgKernel::RendererManager::getSingleton().addRenderer( pLayerPtrVec->at(0).getPointer());

		// AfxMessageBox(pLayerPtrVec->at(0)->getName().c_str());

		assert( queue != NULL );

		return true;
	}


	LayerPtrVector* DxfReader::readLayersFromDataSource( 
		OGRDataSource* source , 
		const OGRGeometry* geo_filter /*= NULL*/ ,
		const bool& use_special_polygon /*= false */)
	{
		if ( source == NULL )
		{
			return NULL;
		}

		LayerPtrVector* ret = new LayerPtrVector;

		for( int iLayer = 0; iLayer < source->GetLayerCount(); 
			iLayer++ )
		{
			OGRLayer *poLayer = source->GetLayer(iLayer);

			if( poLayer == NULL )
			{
				assert(0);
				delete ret;
				return false;
			}

			VGGI_CHECK_OGR_ERROR();

			//------------------------------------------
			// 在这里都设定为25D
			//------------------------------------------
			OGRFeatureDefn* def = poLayer->GetLayerDefn();

			if ( wkbFlatten( def->GetGeomType() ) == wkbPolygon )
			{
				def->SetGeomType( wkbPolygon25D );
			}

			//------------------------------------------
			// 设定vrgis field
			//------------------------------------------
			int fieldid = def->GetFieldIndex(VG_GIS_STYLE_FIELD);
			assert( fieldid != -1 );

			VGGI_CHECK_OGR_ERROR();

			LayerPtr pLayer = readLayerFromOGRLayer( poLayer , geo_filter , use_special_polygon );

			VGGI_CHECK_OGR_ERROR();

			if ( pLayer.isNull() == true )
			{
				assert(0);
				delete ret;
				return false;
			}

			ret->push_back( pLayer );
		}

		return ret;
	}

	LayerPtr DxfReader::readLayerFromOGRLayer( OGRLayer* ogr_layer , 
		const OGRGeometry* geo_filter /*= NULL*/ ,
		const bool& use_special_polygon /*= false*/ )
	{
		if ( ogr_layer == NULL )
		{
			return LayerPtr();
		}

		//------------------------------------------
		// 设定filter
		//------------------------------------------
		ogr_layer->SetSpatialFilter( (OGRGeometry*)geo_filter );

		LayerPtr ret( new Layer );

		ret->initialise( ogr_layer );

		//------------------------------------------
		// 开始遍历每一个feature
		//------------------------------------------
		OGRFeature *poFeature = NULL;

		ogr_layer->ResetReading();

		int cnt = 0;
		while( (poFeature = ogr_layer->GetNextFeature()) != NULL )
		{
			TRACE("Process %d \n", cnt++);
			OGRGeometry* geometry = poFeature->GetGeometryRef();
			// 			unsigned char *buffer = new unsigned char[geometry->WkbSize()];
			// 			geometry->exportToWkb(wkbNDR, buffer);
			// 			delete buffer;

			assert( geometry != NULL );

			VGGI_CHECK_OGR_ERROR();

			//------------------------------------------
			// 首先只对polygon进行处理
			//------------------------------------------
			OGRwkbGeometryType geotype = geometry->getGeometryType();
			Geometry* shapegeo = NULL;

			switch( wkbFlatten( geotype ) )
			{
			case wkbPolygon:
				if ( use_special_polygon )
				{
					//shapegeo = new SpecialPolygon( poFeature , ret.getPointer() );
				}
				else
				{
					shapegeo = new Polygon( poFeature , ret.getPointer() );
				}
				break;

			case wkbMultiPolygon:
				shapegeo = new MultiPolygon( poFeature , ret.getPointer() );
				break;

			case wkbLineString:
				shapegeo = new LineString( poFeature , ret.getPointer() );
				break;

			case wkbPoint:
				shapegeo = new Point( poFeature , ret.getPointer() );
				break;

			case wkbMultiLineString:
				shapegeo = new MultiLine( poFeature , ret.getPointer() );
				break;

			case wkbMultiPoint:
				assert(0);//shapegeo = new MultiPoint( poFeature , ret.getPointer() );
				break;

			default:
				break;
			}
			// 
			// 从shp文件中读取数据
			if ( shapegeo != NULL )
			{
				VGGI_CHECK_OGR_ERROR();

				bool readok = shapegeo->readDataFromOGRFeature();

				VGGI_CHECK_OGR_ERROR();

				if ( readok == false )
				{
					assert(0);
					delete shapegeo;
					shapegeo = NULL;
				}
			}

			// 插入layer队列
			if ( shapegeo != NULL )
			{
				ret->pushGeometry( shapegeo );
			}

			VGGI_CHECK_OGR_ERROR();
			OGRFeature::DestroyFeature( poFeature );
		}

		return ret;
	}
}