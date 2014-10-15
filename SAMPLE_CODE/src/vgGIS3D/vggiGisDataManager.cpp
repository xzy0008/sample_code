



#include <vgStableHeaders.h>
#include <vgGIS3D/vggiGisDataManager.h>
#include <vggis/vggisDefinition.h>
#include <vgGIS3D/vggiShapeReader.h>
#include <vgGIS3D/vggiOgrUtility.h>
#include <vgConf/vgcoProjectConfig.h>
#include <vgConf/vgcoProjectConfigRegProxy.h>
#include <vgKernel/vgkStringUtility.h>
#include <vgKernel/vgkSelectManager.h>
#include <vgKernel/vgkSystemUtility.h>
#include <vgKernel/vgkConvertUtility.h>
 
#include "vgUIcontroller/vgEditTreeCtrlEx.h"
#include <vgUIController/vgUIController.h>


#include <vgKernel/vgkOpenGLSupport.h>

#include <vgGIS3D/vggiOracleSpatialReader.h>
#include <vgGIS3D/vggiOGRPipeLineMap.h>
#include <vgGIS3D/vgPipeLineEntry.h>
#include <vgGIS3D/vggiDxfReader.h>

namespace vgGIS3D {

	// float类型
	vgConf::ProjectConfigRegProxy reg1( VG_GIS_STR , 
		VG_GIS_SHPPATH_STR , "" );

	vgConf::ProjectConfigRegProxy reg2( VG_GIS_STR , 
		VG_GIS_SHPMAT_STR , "" );


	void CALLBACK tessError(GLenum error);
	void CPL_STDCALL ogrErrorHandler(CPLErr eErrClass, int err_no, const char *msg);



	//----------------------------------------------------------------
	bool GisDataManager::initAfterOpenGLSetup()
	{
		
		//int* aa = new int;
		//*aa = 323;

		//void* pp = aa;

		//delete pp;



#if 0

		std::vector<long> deleteVec;



		OGRDataSource       *poDS = NULL;

		poDS = OGRSFDriverRegistrar::Open( "d:\\altitude.shp", FALSE );
		if( poDS == NULL )
		{
			return false;
		}

		//typedef std::map<int, std::set<int> >  NPMAP;

		//typedef std::pair<NPMAP::iterator , bool> NPMAP_insertRes;
		//
		//NPMAP nps;
		//std::fstream file;
		//file.open( "d:\\outlines___building.txt" , std::fstream::ios_base::out );

		//assert( file.fail() == false );

		//VGSH_CHECK_OGR_ERROR();



		//----------------------------------------------------------------
		String ddd = poDS->GetName();
		int dd = poDS->GetLayerCount();
		int baf = poDS->GetRefCount();
		int badf = poDS->GetSummaryRefCount();

		OGRLayer  *poLayer = NULL;

		for ( int i = 0 ; i < poDS->GetLayerCount() ; ++ i )
		{
			poLayer = poDS->GetLayer( i );

			int dd = poLayer->GetRefCount();


			OGRFeatureDefn* def = poLayer->GetLayerDefn();
			String ddd = def->GetName();
			int dgfasdf = def->GetReferenceCount();
			int dgg =  def->GetFieldCount();


			OGRwkbGeometryType ee = def->GetGeomType();

			//def->SetGeomType( wkbPolygon25D );


			for ( int i = 0 ; i < def->GetFieldCount() ; ++ i )
			{	
				OGRFieldDefn* f = def->GetFieldDefn( i );


				String ddd = f->GetNameRef();
			}
			

			int bbb = poLayer->GetFeatureCount();

			//------------------------------------------
			// read
			//------------------------------------------

			poLayer->ResetReading();
			OGRFeature* feat = NULL;

			do
			{

				feat = poLayer->GetNextFeature();

				if ( feat == NULL )
				{
					break;
				}
				int gggg = feat->GetFID();

				OGRFeature* poFeature = feat;

				OGRFeatureDefn *poFDefn = poFeature->GetDefnRef();
				int iField;

				assert( poFDefn != NULL );
				int fieldcount = poFDefn->GetFieldCount();
				

				OGRGeometry* geo = poFeature->GetGeometryRef();

	
				//const char* ssdfsf = poFeature->GetStyleString();


				//int dd = 434;
				//for ( int i = 0 ; i < fieldcount ; ++ i )
				//{
				//	OGRFieldDefn* fielddefn = poFDefn->GetFieldDefn( i );
				//	assert( fielddefn != NULL );

				//	OGRFieldType fieldtype = fielddefn->GetType();

				//	String typestr = OGRFieldDefn::GetFieldTypeName( fieldtype );

				//	String fielddesc = fielddefn->GetNameRef();

				//	String filedcontent = feat->GetFieldAsString( i );

				//}

				//poFeature->SetField( "System" , "111221" );

				//poLayer->SetFeature( poFeature );

				//OGRStyleTable* tt = poLayer->GetStyleTable();
				////assert( tt != NULL );

				//const char* ss  = poFeature->GetStyleString();

				//if ( ss == NULL )
				//{
				//	assert(0);
				//}


				//String field1 = poFeature->GetFieldAsString( "Legend" );

				//if ( field1 == "0321 Building" )
				//{
				//	deleteVec.push_back( poFeature->GetFID() );
				//	//int nptype = poFeature->GetFieldAsInteger("Np_type");

				//	//int floor = poFeature->GetFieldAsInteger("Floors");

				//	//std::set<int> ss;

				//	//ss.insert( floor );

				//	//NPMAP_insertRes rr = 
				//	//	nps.insert( std::make_pair( nptype , ss ) );

				//	//if ( rr.second == false )
				//	//{
				//	//	rr.first->second.insert( floor );
				//	//}
				//}

				//for( iField = 0; iField < poFeature->GetFieldCount(); iField++ )
				//{
				//	OGRFieldDefn *poFieldDefn = poFeature->GetFieldDefnRef( iField );

				//	if( poFieldDefn->GetType() == OFTString )
				//		String ddd= poFeature->GetFieldAsString(iField);
				//}

				//OGRGeometry *poGeometry;

				//OGRwkbGeometryType t= poFDefn->GetGeomType();

				//String dddd = OGRGeometryTypeToName( t );


				//poGeometry = poFeature->StealGeometry();
				//poGeometry = poFeature->GetGeometryRef();
				//poGeometry = poGeometry->clone();

				//if( wkbFlatten(poGeometry->getGeometryType() ) != wkbPolygon )
				//{
				//	
				//}
				//else if( poGeometry != NULL )
				//{

				//	//poFDefn->SetGeomType( wkbPolygon25D );


				//	//poGeometry->setCoordinateDimension(3);


				//	OGRPolygon* poly = ( OGRPolygon* )poGeometry;

				//	////assert( poly->getDimension() == 3 );

				//	poly->setCoordinateDimension(3);
				//	
				//	OGRLinearRing* r1 = poly->getExteriorRing();
				//	assert( r1 != NULL );

				//	r1->setCoordinateDimension(3);

				//	for ( int i = 0 ; i < r1->getNumPoints() ; ++ i )
				//	{
				//		OGRPoint p;
				//		

				//		r1->getPoint( i , &p );

				//		//p.setCoordinateDimension(3);

				//		//p.setZ( (i+1) * 0.1 );

				//		//r1->setPoint( i , &p );

				//	}

				//	//for ( int i = 0 ; i < poly->getNumInteriorRings() ; ++ i )
				//	//{
				//	//	OGRLinearRing* r2 = poly->getInteriorRing(i);

				//	//	r2->setCoordinateDimension(3);
				//	//}

				//	//------------------------------------------
				//	// 开始set
				//	//------------------------------------------
				//	//poFeature->SetGeometry( poGeometry );
				//	

				//	//int siz = poGeometry->WkbSize();

				//	//assert( siz != 0 );

				//	//char * buf = new char[siz ];

				//	//memset(buf,  0 , siz );

				//	//OGRErr err = poGeometry->exportToWkb( wkbNDR ,(unsigned char*) buf );

				//	//assert( err == OGRERR_NONE );

				//	//delete[] buf;

				//	//String ddfafd = poGeometry->exportToKML();

				//	delete poGeometry;
				//}
  
				//poLayer->SetFeature( poFeature );


				OGRFeature::DestroyFeature( poFeature );

			}
			while ( feat != NULL );
		}


		////------------------------------------------
		//// 开始遍历,删掉没用的
		////------------------------------------------
		//{
		//	OGRLayer* layer = poDS->GetLayer(0);

		//	std::vector<long>::iterator iter = deleteVec.begin();
		//	std::vector<long>::iterator iter_end = deleteVec.end();
		//	for ( ; iter != iter_end ; ++ iter )
		//	{
		//		OGRErr ee = layer->DeleteFeature( *iter );

		//		assert( ee == OGRERR_NONE );
		//	}
		//}


		//------------------------------------------
		// 开始输出
		//------------------------------------------
		//{
		//	NPMAP::iterator iter = nps.begin();
		//	NPMAP::iterator iter_end = nps.end();

		//	for ( ; iter != iter_end ; ++ iter )
		//	{
		//		file << "nptype:\t" << iter->first << "   floor: ";

		//		std::set<int>::iterator it = iter->second.begin();
		//		std::set<int>::iterator it_end = iter->second.end();

		//		for ( ; it != it_end ; ++ it )
		//		{
		//			file << "  " << *it;
		//		}

		//		file << std::endl;
		//	}
		//}

		//file.close();

		//OGRErr dfd = poDS->SyncToDisk();

		//assert( dfd == OGRERR_NONE );
		//delete poDS;


	

#if 0
		//------------------------------------------
		// 开始复制
		//------------------------------------------

		const char *pszDriverName = "AutoCAD DXF";
		OGRSFDriver *poDriver;

		OGRRegisterAll();

		poDriver = OGRSFDriverRegistrar::GetRegistrar()->GetDriverByName(
			pszDriverName );
		if( poDriver == NULL )
		{
			assert(0);
		}

		OGRDataSource *poDS2;

		poDS2 = poDriver->CreateDataSource( "d:\\outlines_25D2222222.shp", NULL );
		if( poDS2 == NULL )
		{
			assert(0);
		}

		bool dfffd = OgrUtility::copyDataSource( poDS , poDS2 );

		assert( dfffd == true );


		//////////////////////////////////////////////////////////////////////////





		//------------------------------------------
		// 结束
		//------------------------------------------
		delete poDS2;
#endif

		delete poDS;
		


		////------------------------------------------
		//// 尝试写入
		////------------------------------------------
		//const char *pszDriverName = "AutoCAD DXF";
		//OGRSFDriver *poDriver;

		//OGRRegisterAll();

		//poDriver = OGRSFDriverRegistrar::GetRegistrar()->GetDriverByName(
		//	pszDriverName );
		//if( poDriver == NULL )
		//{
		//	assert(0);
		//}

		//OGRDataSource *poDS2;

		//poDS2 = poDriver->CreateDataSource( "d:\\point_out.shp", NULL );
		//if( poDS2 == NULL )
		//{
		//	assert(0);
		//}



#endif

#if 0

		//------------------------------------------
		//创建wbk polyon

		//vgWkb::WKBPolygon poly;

		//------------------------------------------
		const char *pszDriverName = "AutoCAD DXF";
		OGRSFDriver *poDriver;

		OGRRegisterAll();

		poDriver = OGRSFDriverRegistrar::GetRegistrar()->GetDriverByName(
			pszDriverName );
		if( poDriver == NULL )
		{
			assert(0);
		}

		OGRDataSource *poDS;

		poDS = poDriver->CreateDataSource( "c:\\point_out.shp", NULL );
		if( poDS == NULL )
		{
			assert(0);
		}

		OGRLayer *poLayer;

		poLayer = poDS->CreateLayer( "ppp");
		if( poLayer == NULL )
		{
			assert(0);
		}

		OGRFieldDefn oField( "Name", OFTString );

		oField.SetWidth(32);

		if( poLayer->CreateField( &oField ) != OGRERR_NONE )
		{
			assert(0);
		}

		double x, y;
		char szName[33];


		{
			OGRFeature *poFeature;

			poFeature = OGRFeature::CreateFeature( poLayer->GetLayerDefn() );
			poFeature->SetField( "Name", "11111111111111" );

			OGRPolygon pol;
			OGRPolygon pol2;

			pol2.setCoordinateDimension(3);

			OGRLinearRing ring;
			ring.addPoint( 0.0, 0.0 , 1.0 );
			ring.addPoint( 1.0, 0.0 , 1.0);
			ring.addPoint( 1.0, 1.0 , 1.0);
			ring.addPoint( 0.0, 1.0 , 1.0);
			ring.addPoint( 0.0, 0.0, 1.0 );
			pol.addRing( &ring );

			OGRLinearRing ring2;
			ring2.setCoordinateDimension(3);
			ring2.addPoint( 0.5, 0.0 , 1.0);
			ring2.addPoint( 1.5, 0.0 , 1.0);
			ring2.addPoint( 1.5, 0.5 , 1.0);
			ring2.addPoint( 0.5, 0.5, 1.0 );
			ring2.addPoint( 0.5, 0.0 , 1.0);
			pol2.addRing( &ring2 );

			

			OGRGeometry* geo = pol.Union( &pol2 );

			//pol.addRing( geo );

			assert( geo != NULL );
			//delete geo;

			OGRwkbGeometryType t2t = pol2.getGeometryType();
			OGRwkbGeometryType tt = geo->getGeometryType();


			poFeature->SetGeometry( &pol2 ); 

			//------------------------------------------
			// 创建style
			//------------------------------------------
			////poFeature->SetStyleTable();
			//OGRStyleMgr   *poStyleMgr = new OGRStyleMgr();

			//// Create a New style in the style table
			//OGRStylePen  *poStylePen = new OGRStylePen;
			//poStylePen->SetColor("#123456");
			//poStylePen->SetUnit(OGRSTUPixel);
			//poStylePen->SetWidth(10.0);

			//poStyleMgr->AddPart(poStylePen);

			//poFeature->SetStyleString( poStyleMgr->GetStyleString( ) );
			////GBool ret = poStyleMgr->SetFeatureStyleString( poFeature );
			////assert( ret == TRUE );

			//delete poStylePen;
			//delete poStyleMgr;




			OGRStyleTable oStyleTable;

			OGRStyleMgr   *poStyleMgr = new OGRStyleMgr(&oStyleTable);

			// Create a New style in the style table

			if (poStyleMgr->AddStyle("@Name","PEN(c:#123456;w:10px);BRUSH(c:345678)"))
			{
				poStyleMgr->SetFeatureStyleString(poFeature,"@Name",TRUE);
					//poStyleMgr->SetFeatureStyleString(poFeature,"PEN(c:#123456,w:10px);BRUSH(c:345678)",FALSE)
			}

			oStyleTable.SaveStyleTable("ttt.tbl");


			// Create a New style in the style table

			poStyleMgr->InitStyleString();
			poStyleMgr->AddPart("PEN(c:#123456,w:10px)");
			poStyleMgr->AddPart("BRUSH(c:345678)");
			poStyleMgr->AddStyle("@Name");
			poStyleMgr->SetFeatureStyleString(poFeature,"@Name",TRUE);
			oStyleTable.SaveStyleTable("ttt.tbl");


			// Create a New style in the style table

			OGRStylePen  *poStylePen = new OGRStylePen;

			poStylePen->SetColor("#123456");
			poStylePen->SetUnit(OGRSTUPixel);
			poStylePen->SetWidth(10.0);
			poStyleMgr->AddPart(poStylePen);

			delete poStylePen;



			const char* ddddfasf =  poFeature->GetStyleString();

			if( poLayer->CreateFeature( poFeature ) != OGRERR_NONE )
			{
				assert(0);
			}

			OGRFeature::DestroyFeature( poFeature );
		}




		OGRDataSource::DestroyDataSource( poDS );



#endif


		return true;
	}
	//----------------------------------------------------------------
	bool GisDataManager::uninitBeforeOpenGLDestroy()
	{

		clearAllDataSources();

		


		return true;
	}

	bool GisDataManager::importDataFromOCI(string user, string passWord, string server, string sql)
	{
		return vgGIS3D::OracleSpatialReader::ReaderFromOracle(user, passWord, server, sql);
	}

	bool GisDataManager::importDataFromDxfFile(string filePath)
	{
		return vgGIS3D::DxfReader::ReaderFromFile(filePath);
	}

	//----------------------------------------------------------------
	DataSourcePtr GisDataManager::openShapeFile( const String& filepath )
	{
		if ( checkOpened( filepath ) == true )
		{
			return DataSourcePtr();
		}

		//------------------------------------------
		// 创建临时的文件
		//------------------------------------------
		String tmppath = vgKernel::SystemUtility::getSystemTempPath();
		tmppath += "\\";
		tmppath += vgKernel::StringUtility::getFilenameFromAbsolutePath( filepath );


		//------------------------------------------
		// 开始读取shp文件
		//------------------------------------------
		// Edit By FengYK @2010-04-01 10:16
		DataSourcePtr psource = 
			ShapeReader::readFromShpFile( filepath ,tmppath , _filter );

		if ( psource.isNull() == true )
		{
			return DataSourcePtr();
		}

		_datasources.insert( std::make_pair( filepath , psource ) );

		return psource;
	}

	//----------------------------------------------------------------
	DataSource* GisDataManager::openShapeFile2( const String& filepath )
	{
		DataSourcePtr psource = openShapeFile(filepath);

		return psource.getPointer();
	}
	//----------------------------------------------------------------
	DataSourcePtr GisDataManager::openShapeFileSpecially( const String& filepath )
	{
		if ( checkOpened( filepath ) == true )
		{
			return DataSourcePtr();
		}

		//------------------------------------------
		// 创建临时的文件
		//------------------------------------------
		String tmppath = vgKernel::SystemUtility::getSystemTempPath();
		tmppath += "\\";
		tmppath += vgKernel::StringUtility::getFilenameFromAbsolutePath( filepath );


		//------------------------------------------
		// 开始读取shp文件
		//------------------------------------------
		DataSourcePtr psource = 
			ShapeReader::readFromShpFile( filepath ,tmppath , _filter , true );

		if ( psource.isNull() == true )
		{
			return DataSourcePtr();
		}

		_datasources.insert( std::make_pair( filepath , psource ) );

		return psource;
	}

	//----------------------------------------------------------------
	DataSource* GisDataManager::openShapeFileSpecially2( const String& filepath )
	{
		DataSourcePtr psource = openShapeFileSpecially(filepath);

		return psource.getPointer();
	}
	//----------------------------------------------------------------
	bool GisDataManager::checkOpened( const String& filepath )
	{
		DataSourcePtrMap::iterator iter = _datasources.find( filepath );

		if ( iter == _datasources.end() )
		{
			return false;
		}

		return true;
	}
	//----------------------------------------------------------------
	void GisDataManager::renderShapes()
	{

		//------------------------------------------
		// 注意,渲染是在renderermanager中进行.
		//------------------------------------------
#if 0
		DataSourcePtrMap::iterator iter = _datasources.begin();
		DataSourcePtrMap::iterator iter_end = _datasources.end();

		for ( ;iter != iter_end ; ++iter )
		{
			iter->second->renderLayers();
		}
#endif

		if ( _selector != NULL )
		{
			_selector->render();
		}

		if (_pipeLineSelector != NULL)
		{
			_pipeLineSelector->render();
		}

		if (_pipeAnalysisSelector != NULL)
		{
			_pipeAnalysisSelector->render();
		}

		return;
	}
	//----------------------------------------------------------------
	void CALLBACK tessError( GLenum error )
	{
		const char *szError = (const char*)gluErrorString(error);

		assert(0&&"GisDataManager::tessError");

		VGK_CHECK_OPENGL_ERROR();

		return;
	}
	//----------------------------------------------------------------
	bool GisDataManager::onDeleteRenderer( vgKernel::Renderer *render )
	{
		if ( render->getType() != RENDERER_TYPE_GIS_LAYER &&	render->getType() != RENDERER_TYPE_PIPELINE_LAYER)
		{
			return false;
		}

		// add by KingHJ @2010.03.24  如果是管线图层的话就只是停止管线的渲染然后返回
		if (render->getType() == RENDERER_TYPE_PIPELINE_LAYER)
		{
			OGRPipeLineMap *pPipeLine = (OGRPipeLineMap*)render;			
			pPipeLine->setPipeLineVisible(false);						

            //因为在绘制管线的时候关掉了shap的渲染，现在将其开启。
			string layerName = render->getName();
			Layer *pLayer = GisDataManager::getSingleton().getLayerByShortName(layerName);			
			if (pLayer != NULL)
			{
				pLayer->setVisible(true);
			}

			//delete pPipeLine;
			//pPipeLine = NULL;

			return true;

		}

		if ( _selector != NULL )
		{
			delete _selector;
			_selector = NULL;
		}


		Layer* la = ( Layer * ) render;

		DataSourcePtrMap::iterator iter = _datasources.begin();
		DataSourcePtrMap::iterator iter_end = _datasources.end();

		for ( ; iter != iter_end ; ++ iter )
		{
			DataSourcePtr pd = iter->second;
			assert( pd.isNull() == false );

			bool deleteok = pd->deleteLayer( la );

			if ( deleteok == true )
			{
				return true;
			}
		}

		return true;
	}
	//----------------------------------------------------------------
	void GisDataManager::clearAllDataSources()
	{
		if ( _selector != NULL )
		{
			delete _selector;
			_selector = NULL;
		}

		if (_pipeLineSelector != NULL)
		{
			delete _pipeLineSelector;
			_pipeLineSelector = NULL;
		}

		if (_pipeAnalysisSelector != NULL)
		{
			delete _pipeAnalysisSelector;
			_pipeAnalysisSelector = NULL;
		}

		_datasources.clear();
	}
	//----------------------------------------------------------------
	bool GisDataManager::setSelectMode( vgKernel::Renderer* selected_layer , 
		const bool& enable )
	{
		Layer* pLayer = dynamic_cast<Layer*>(selected_layer);
		assert( pLayer!=0 );
		
		if ( pLayer->isInEditMode() && enable == true  )
		{
			assert(  _selector != NULL  );
			// 直接返回, 目标达到
			return true;
		}
		else if ( pLayer->isInEditMode() && enable == false )
		{
			assert(  _selector != NULL );
			//------------------------------------------
			// 此时卸载即可
			//------------------------------------------
			if ( _selector != NULL )
			{
				delete _selector;
				_selector = NULL;
			}
			// 虽然selector会自动置位,但是这里还是保证一下.
			pLayer->setEditMode( false );
			//------------------------------------------
			// 将其他的都设置为false
			//------------------------------------------
			DataSourcePtrMap::iterator iter = _datasources.begin();
			DataSourcePtrMap::iterator iter_end = _datasources.end();
			for ( ; iter != iter_end ; ++ iter )
			{
				DataSourcePtr ds = iter->second;
				LayerPtrVector::iterator i = ds->getLayerPtrVector()->begin();
				LayerPtrVector::iterator i_end = ds->getLayerPtrVector()->end();

				for ( ; i != i_end ; ++ i )
				{
					LayerPtr la = *i;

					if ( la.getPointer() == pLayer )
					{
						continue;
					}
					la->setEditMode( false );
				}
			}
			return true;
		}
		else
		{
			assert( pLayer->isInEditMode() == false );

			if ( enable == false )
			{
				//------------------------------------------
				// 将所有的都设置为false
				//------------------------------------------
				DataSourcePtrMap::iterator iter = _datasources.begin();
				DataSourcePtrMap::iterator iter_end = _datasources.end();
				for ( ; iter != iter_end ; ++ iter )
				{
					DataSourcePtr ds = iter->second;
					LayerPtrVector::iterator i = ds->getLayerPtrVector()->begin();
					LayerPtrVector::iterator i_end = ds->getLayerPtrVector()->end();

					for ( ; i != i_end ; ++ i )
					{
						LayerPtr la = *i;
						la->setEditMode( false );
					}
				}

				if ( _selector != NULL )
				{
					delete _selector;
					_selector = NULL;
				}

				return true;
			}
			else
			{
				//------------------------------------------
				// 将其他的都设置为false
				//------------------------------------------
				DataSourcePtrMap::iterator iter = _datasources.begin();
				DataSourcePtrMap::iterator iter_end = _datasources.end();
				for ( ; iter != iter_end ; ++ iter )
				{
					DataSourcePtr ds = iter->second;
					LayerPtrVector::iterator i = ds->getLayerPtrVector()->begin();
					LayerPtrVector::iterator i_end = ds->getLayerPtrVector()->end();

					for ( ; i != i_end ; ++ i )
					{
						LayerPtr la = *i;

						if ( la.getPointer() == pLayer )
						{
							continue;
						}
						la->setEditMode( false );
					}
				}

				if ( _selector != NULL )
				{
					delete _selector;
					_selector = NULL;
				}

				assert( _selector == NULL );
				_selector = new Selector( pLayer );

				return true;
			}

		}

	}
	//----------------------------------------------------------------
	bool GisDataManager::clearDataSource( const String& datasource_filepath )
	{
		DataSourcePtrMap::iterator findres = 
			_datasources.find( datasource_filepath );

		if ( findres == _datasources.end() )
		{
			return false;
		}

		_datasources.erase( findres );
		return true;
	}
	//----------------------------------------------------------------
	bool GisDataManager::clearDataSourcePtr( const DataSourcePtr& psource )
	{
		return clearDataSource( psource->getSourcePath() );
	}

	void CPL_STDCALL ogrErrorHandler( CPLErr eErrClass, int err_no, const char *msg )
	{
		if ( eErrClass == CE_Fatal )
		{
			std::ostringstream o;
			o << "CPLErr: " << eErrClass << " , err_no:" << err_no
				<< " , msg: " << msg;
			VGK_TRACE( o.str() );

			MessageBox( NULL , o.str().c_str() , "Error" , MB_OK );
		}
		else 
		{
			std::ostringstream o;
			o << "CPLErr: " << eErrClass << " , err_no:" << err_no
				<< " , msg: " << msg;
			VGK_TRACE( o.str() );
		}
	}
	//----------------------------------------------------------------
	void GisDataManager::setShpLoadingFilter( double dfMinX,
		double dfMinY, double dfMaxX, double dfMaxY , 
		double shrink_param /*= 0.0*/ )
	{
		dfMinY += shrink_param;
		dfMinX += shrink_param;
		dfMaxX -= shrink_param;
		dfMaxY -= shrink_param;

		assert( dfMinX < dfMaxX );
		assert( dfMinY < dfMaxY );

		OGRGeometry* geo = OGRGeometryFactory::createGeometry( wkbPolygon );
		assert( geo != NULL );

		OGRPolygon* poly = ( OGRPolygon* )geo;

		OGRLinearRing ring;

		ring.addPoint( dfMinX , dfMinY );
		ring.addPoint( dfMaxX , dfMinY );
		ring.addPoint( dfMaxX , dfMaxY );
		ring.addPoint( dfMinX , dfMaxY );
		ring.addPoint( dfMinX , dfMinY );

		poly->addRing( &ring );

		setShpLoadingFilterByOGRGeometry( geo );

		return;
	}
	//----------------------------------------------------------------
	DataSourcePtr GisDataManager::getDataSourceByPathName( 
		const String& pathname )
	{
		DataSourcePtrMap::iterator iter = _datasources.begin();
		DataSourcePtrMap::iterator iter_end = _datasources.end();

		for ( ; iter != iter_end ;++iter )
		{
			DataSourcePtr pds = iter->second;
			if ( pds->getSourcePath() == pathname )
			{
				return pds;
			}
		}

		return DataSourcePtr();
	}
	//----------------------------------------------------------------
	//----------------------------------------------------------------
	DataSourcePtr GisDataManager::getDataSourceByShortName( 
		const String& shortname )
	{
		DataSourcePtrMap::iterator iter = _datasources.begin();
		DataSourcePtrMap::iterator iter_end = _datasources.end();

		for ( ; iter != iter_end ;++iter )
		{
			DataSourcePtr pds = iter->second;
			if ( 
				vgKernel::StringUtility::getFilenameFromAbsolutePath(
				pds->getSourcePath() ) == shortname )
			{
				return pds;
			}
		}

		return DataSourcePtr();
	}

	Layer* GisDataManager::getLayerByShortName( const String& shortname )
	{
		DataSourcePtrMap::iterator iter = _datasources.begin();
		DataSourcePtrMap::iterator iter_end = _datasources.end();
		for ( ; iter != iter_end ; ++ iter )
		{
			DataSourcePtr ds = iter->second;
			LayerPtrVector::iterator i = ds->getLayerPtrVector()->begin();
			LayerPtrVector::iterator i_end = ds->getLayerPtrVector()->end();

			for ( ; i != i_end ; ++ i )
			{
				LayerPtr la = *i;

				if ( la->getName() == shortname )
				{
					return la.getPointer();
				}
			}
		}

		return NULL;
	}
	//----------------------------------------------------------------
	String GisDataManager::readProject( const String& projpath )
	{
		String shps = VG_PROJCONF_GET_STRING( VG_GIS_STR , 
			VG_GIS_SHPPATH_STR );

		String floorPorps = VG_PROJCONF_GET_STRING( VG_GIS_STR, VG_GIS_FLOORPROP);

		const String mtok = ";";
		StringVector matvec = vgKernel::StringUtility::tokenize( floorPorps , mtok , true );

		for ( int i = 0 ; i < matvec.size() ; ++ i )
		{
			String onemat = matvec[i];

			TRACE("Floor prop name : %s \n", onemat.c_str());

			ShapeReader::addFloorProp(onemat);
		}

		String floorHeightPorps = VG_PROJCONF_GET_STRING( VG_GIS_STR, VG_GIS_FOOLHEIGHTROP);

		StringVector matvec2 = vgKernel::StringUtility::tokenize( floorHeightPorps , mtok , true );

		for ( int i = 0 ; i < matvec2.size() ; ++ i )
		{
			String onemat = matvec2[i];

			TRACE("Floor prop height name : %s \n", onemat.c_str());

			ShapeReader::addFloorHeightProp(onemat);
		}

		return shps;

#if 0
		//------------------------------------------
		// 其次分辨layers  matrix
		//------------------------------------------
		const String mtok = ";";
		StringVector matvec = vgKernel::StringUtility::tokenize( mats , mtok , true );

		if ( matvec.size() != shpvec.size() )
		{
#if VGK_LANG_CHS
			std::ostringstream o ;
			o << "打开xml文件,读取:" << mats << "时, 发生错误, 文件未完全加载.";
			vgKernel::SystemUtility::showModelDialog(o.str());
#else
			std::ostringstream o ;
			o << "When reading xml:" << mats << " failed.";
			vgKernel::SystemUtility::showModelDialog(o.str());
#endif
			return;
		}

		for ( int i = 0 ; i < matvec.size() ; ++ i )
		{
			String onemat = matvec[i];

			StringVector details = vgKernel::StringUtility::tokenize( onemat , ":,", true );

			if ( details.size() != 17 )
			{
#if VGK_LANG_CHS
				std::ostringstream o ;
				o << "打开xml文件,读取:" << mats << "时, 发生错误, 文件未完全加载.";
				vgKernel::SystemUtility::showModelDialog(o.str());
#else
				std::ostringstream o ;
				o << "When reading xml:" << mats << " failed.";
				vgKernel::SystemUtility::showModelDialog(o.str());
#endif
				return;
			}

			String layername = details[0];

			Layer* la = getLayerByShortName( layername );

			if ( la == NULL )
			{
#if VGK_LANG_CHS
				std::ostringstream o ;
				o << "读取层:" << layername << "时, 发生错误, 文件未完全加载.";
				vgKernel::SystemUtility::showModelDialog(o.str());
#else
				std::ostringstream o ;
				o << "Reading layer:" << layername << " failed";
				vgKernel::SystemUtility::showModelDialog(o.str());
#endif
				return;
			}

			vgKernel::Mat4 mat4;
			for ( int j = 0 ; j < 16 ; ++ j )
			{
				float val = vgKernel::ConvertUtility::textCast<float>( details[ j + 1 ] );
				mat4._m[j] = val;
			}

			la->setMatrix( mat4 );
		}
#endif
		return shps;
	}
	//----------------------------------------------------------------
	void GisDataManager::saveProject( const String& projpath )
	{
		std::ostringstream shps;
		std::ostringstream layers;
		std::ostringstream depths;
		std::ostringstream visible;

		//------------------------------------------
		// 存储shp的path信息
		//------------------------------------------
		DataSourcePtrMap::iterator iter = _datasources.begin();
		DataSourcePtrMap::iterator iter_end = _datasources.end();
		for ( ; iter != iter_end ; ++ iter )
		{
			DataSourcePtr ds = iter->second;
			
			if (ds->getType() != DataSource_SHP)
			{
				continue; 
			}

			if ( ds->dumpToShpByFilePath( projpath + "\\" + ds->getShortName() ) 
				== false )
			{
				assert(0);
#if VGK_LANG_CHS
				std::ostringstream o ;
				o << "保存文件:" << ds->getShortName() << "时, 发生错误, 文件未保存.";
				MessageBox( NULL , o.str().c_str() , "错误提示" , MB_OK );
#else
				std::ostringstream o ;
				o << "When saving:" << ds->getShortName() << " error occured.";
				MessageBox( NULL , o.str().c_str() , "Tips" , MB_OK );

#endif
				continue;
			}
			
			shps << ds->getShortName() << ";";
		


			LayerPtrVector::iterator i = ds->getLayerPtrVector()->begin();
			LayerPtrVector::iterator i_end = ds->getLayerPtrVector()->end();

			for ( ; i != i_end ; ++ i )
			{
				LayerPtr la = *i;

				layers << la->getName() << ":";
				depths << la->getName() << ":";
				depths << la->getDepthEnable() << ";";
				visible << la->getName() << ":";
				visible << la->getVisible() << ";";

				vgKernel::Mat4 mat = la->getMatrix();
				
				char buf[256];

				for ( int j = 0 ; j < 16 ; ++ j )
				{
					// 在这里去掉逗号
					sprintf(  buf , "%f" , mat._m[j] );
					String bufstr( buf );
					assert( bufstr.find( "," ) == String::npos );
					layers << String( buf );
					if ( j != 15 )
					{
						layers << ",";
					}
				}

				layers << ";";
			}
		}

		String fffff = layers.str();
		String gggg = shps.str();

		VG_PROJCONF_SET( VG_GIS_STR , 
			VG_GIS_SHPPATH_STR , shps.str() );

		VG_PROJCONF_SET( VG_GIS_STR , 
			VG_GIS_SHPMAT_STR , layers.str() );

		VG_PROJCONF_SET( VG_GIS_STR , 
			VG_GIS_DEPTH , depths.str() );

		VG_PROJCONF_SET(VG_GIS_STR,
			VG_GIS_VISIBLE, visible.str());

		string floorProps;

		for (int i=0; i<ShapeReader::m_floorProp.size(); i++)
		{
			floorProps += ShapeReader::m_floorProp[i];
			floorProps += ";";
		}

		VG_PROJCONF_SET( VG_GIS_STR, VG_GIS_FLOORPROP, floorProps.c_str());


		string floorHeightProps;

		for (int i=0; i<ShapeReader::m_floorHeightProp.size(); i++)
		{
			floorHeightProps += ShapeReader::m_floorHeightProp[i];
			floorHeightProps += ";";
		}

		VG_PROJCONF_SET( VG_GIS_STR, VG_GIS_FOOLHEIGHTROP, floorHeightProps.c_str());

	}

	bool GisDataManager::initialise()
	{
		OGRRegisterAll();

		CPLSetErrorHandler( ogrErrorHandler );

		return true;
	}

	bool GisDataManager::shutdown()
	{
		if ( _filter != NULL )
		{
			delete _filter;
			_filter = NULL;
		}
		if ( _selector != NULL )
		{
			delete _selector;
			_selector = NULL;
		}
		assert( _selector == NULL ); 
		OGRCleanupAll();
		return true;
	}


	//----------------------------------------------------------------
	void GisDataManager::reset()
	{
		uninitBeforeOpenGLDestroy();
	}

	GeometryPointerVec* GisDataManager::getSelectGeometriesFromLayer( Layer* layer )
	{
		return layer->getSelectedGeometry();
	}

	LayerPtrVector* GisDataManager::getLayersFromDataSource(  DataSource* psource )
	{
		return psource->getLayerPtrVector();
	}

	void GisDataManager::readProjectExtra( const String& projpath )
	{

		if ( _datasources.empty() )
		{
			return;
		}

		String mats = VG_PROJCONF_GET_STRING( VG_GIS_STR , 
			VG_GIS_SHPMAT_STR );

		assert( mats.empty() == false );

		//------------------------------------------
		// 其次分辨layers  matrix
		//------------------------------------------
		const String mtok = ";";
		StringVector matvec = vgKernel::StringUtility::tokenize( mats , mtok , true );


		for ( int i = 0 ; i < matvec.size() ; ++ i )
		{
			String onemat = matvec[i];

			StringVector details = vgKernel::StringUtility::tokenize( onemat , ":,", true );

			if ( details.size() != 17 )
			{
#if VGK_LANG_CHS
				std::ostringstream o ;
				o << "打开xml文件,读取:" << mats << "时, 发生错误, 文件未完全加载.";
				vgKernel::SystemUtility::showModelDialog(o.str());
#else
				std::ostringstream o ;
				o << "When reading xml:" << mats << " failed.";
				vgKernel::SystemUtility::showModelDialog(o.str());
#endif
				return;
			}

			String layername = details[0];

			Layer* la = getLayerByShortName( layername );

			if ( la == NULL )
			{
#if VGK_LANG_CHS
				std::ostringstream o ;
				o << "读取层:" << layername << "时, 发生错误, 文件未完全加载.";
				vgKernel::SystemUtility::showModelDialog(o.str());
#else
				std::ostringstream o ;
				o << "Reading layer:" << layername << " failed";
				vgKernel::SystemUtility::showModelDialog(o.str());
#endif
				return;
			}

			vgKernel::Mat4 mat4;
			for ( int j = 0 ; j < 16 ; ++ j )
			{
				float val = vgKernel::ConvertUtility::textCast<float>( details[ j + 1 ] );
				mat4._m[j] = val;
			}

			la->setMatrix( mat4 );
		}

		// 设定深度缓存信息
		String depth = VG_PROJCONF_GET_STRING( VG_GIS_STR , 
			VG_GIS_DEPTH );

		if (depth.empty())
		{
			return ;
		}
		
		StringVector depths = vgKernel::StringUtility::tokenize( depth , mtok , true );


		for ( int i = 0 ; i < matvec.size() ; ++ i )
		{
			String onemat = depths[i];

			StringVector details = vgKernel::StringUtility::tokenize( onemat , ":,", true );

			if ( details.size() != 2 )
			{
				std::ostringstream o ;
				o << "读取层时, 发生错误, 文件未完全加载.";
				vgKernel::SystemUtility::showModelDialog(o.str());
			}
			String layername = details[0];

			Layer* la = getLayerByShortName( layername );

			if ( la == NULL )
			{
				std::ostringstream o ;
				o << "读取层:" << layername << "时, 发生错误, 文件未完全加载.";
				vgKernel::SystemUtility::showModelDialog(o.str());
				return;
			}

			vgKernel::Mat4 mat4;

			bool val = vgKernel::ConvertUtility::textCast<bool>( details[1] );

			la->setDepthEnable( val );
		}


		//add by KingHJ @2010-05-11  设定渲染状态信息
		String visible = VG_PROJCONF_GET_STRING( VG_GIS_STR , 
			VG_GIS_DEPTH );

		if (visible.empty())
		{
			return ;
		}

		StringVector visibleVec = vgKernel::StringUtility::tokenize( visible , mtok , true );


		for ( int i = 0 ; i < matvec.size() ; ++ i )
		{
			String onemat = visibleVec[i];

			StringVector details = vgKernel::StringUtility::tokenize( onemat , ":,", true );

			if ( details.size() != 2 )
			{
				std::ostringstream o ;
				o << "读取层时, 发生错误, 文件未完全加载.";
				vgKernel::SystemUtility::showModelDialog(o.str());
			}
			String layername = details[0];

			Layer* la = getLayerByShortName( layername );

			if ( la == NULL )
			{
				std::ostringstream o ;
				o << "读取层:" << layername << "时, 发生错误, 文件未完全加载.";
				vgKernel::SystemUtility::showModelDialog(o.str());
				return;
			}

			vgKernel::Mat4 mat4;

			bool val = vgKernel::ConvertUtility::textCast<bool>( details[1] );

			la->setDepthEnable( val );
		}
	}

	DataSourcePtr& GisDataManager::getCurrentDataSource()
	{
		return _currentDataSource;
	}
	//----------------------------------------------------------------


	bool GisDataManager::constructTopMap()
	{

		return true;
	}

	bool GisDataManager::setSelectPipeLineMode(vgKernel::Renderer* selected_pipeline,
		const bool& enable)
	{
		OGRPipeLineMap* pPipeLine = dynamic_cast <OGRPipeLineMap*> (selected_pipeline);
		assert(pPipeLine != 0);

		if (pPipeLine->isInEditMode() && enable == true)
		{
			assert(_pipeLineSelector != NULL);
			return true;
		}
		else if (pPipeLine->isInEditMode() && enable == false)
		{
			assert( _pipeLineSelector != NULL);
			if (_pipeLineSelector != NULL)
			{
				delete _pipeLineSelector;
				_pipeLineSelector = NULL;
			}
			pPipeLine->setEditMode(false);
			return true;
		}
		else
		{
			assert (pPipeLine->isInEditMode() == false);

			if (enable == false)
			{
				pPipeLine->setEditMode(false);

				if (_pipeLineSelector != NULL)
				{
					delete _pipeLineSelector;
					_pipeLineSelector = NULL;
				}

				return true;
			}
			else
			{
				pPipeLine->setEditMode(true);

				if ( _pipeLineSelector != NULL )
				{
					delete _pipeLineSelector;
					_pipeLineSelector = NULL;
				}

				assert( _pipeLineSelector == NULL );
				_pipeLineSelector = new PipeLineSelector( pPipeLine );

				return true;

			}

		}		
	}

	bool GisDataManager::setPipeLineAnalysisMode(vgKernel::Renderer* selected_pipeline,
		const bool& enable)
	{
		OGRPipeLineMap* pPipeLine = dynamic_cast <OGRPipeLineMap*> (selected_pipeline);
		assert(pPipeLine != 0);

		if (pPipeLine->isInAnalysisMode() && enable == true)
		{
			assert(_pipeAnalysisSelector != NULL);
			return true;
		}
		else if (pPipeLine->isInAnalysisMode() && enable == false)
		{
			assert( _pipeAnalysisSelector != NULL);
			if (_pipeAnalysisSelector != NULL)
			{
				delete _pipeAnalysisSelector;
				_pipeAnalysisSelector = NULL;
			}
			pPipeLine->setAnalysisMode(false);
			return true;
		}
		else
		{
			assert (pPipeLine->isInAnalysisMode() == false);

			if (enable == false)
			{
				pPipeLine->setAnalysisMode(false);

				if (_pipeAnalysisSelector != NULL)
				{
					delete _pipeAnalysisSelector;
					_pipeAnalysisSelector = NULL;
				}

				return true;
			}
			else
			{
				pPipeLine->setAnalysisMode(true);

				if ( _pipeAnalysisSelector != NULL )
				{
					delete _pipeAnalysisSelector;
					_pipeAnalysisSelector = NULL;
				}

				assert( _pipeAnalysisSelector == NULL );
				_pipeAnalysisSelector = new PipeAnalysisSelector( pPipeLine );

				return true;

			}

		}		
	}


}// end of namespace vgShape
