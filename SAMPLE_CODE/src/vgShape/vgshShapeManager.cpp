



#include <vgStableHeaders.h>
#include <vgShape/vgshShapeManager.h>
#include <vgShape/vgshDefinition.h>
#include <vgShape/vgshShapeReader.h>
#include <vgShape/vgshOgrUtility.h>
#include <vgConf/vgcoProjectConfig.h>
#include <vgConf/vgcoProjectConfigRegProxy.h>
#include <vgKernel/vgkStringUtility.h>
#include <vgKernel/vgkSelectManager.h>
#include <vgKernel/vgkSystemUtility.h>
#include <vgKernel/vgkConvertUtility.h>

#include <vgKernel/vgkOpenGLSupport.h>




namespace vgShape {

	// float类型
	vgConf::ProjectConfigRegProxy reg1( VG_SHAPE_STR , 
		VG_SHAPE_SHPPATH_STR , "" );

	vgConf::ProjectConfigRegProxy reg2( VG_SHAPE_STR , 
		VG_SHAPE_SHPMAT_STR , "" );


	void CALLBACK tessError(GLenum error);
	void CPL_STDCALL ogrErrorHandler(CPLErr eErrClass, int err_no, const char *msg);



	//----------------------------------------------------------------
	bool ShapeManager::initAfterOpenGLSetup()
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

		const char *pszDriverName = "ESRI Shapefile";
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
		//const char *pszDriverName = "ESRI Shapefile";
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
		const char *pszDriverName = "ESRI Shapefile";
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
	bool ShapeManager::uninitBeforeOpenGLDestroy()
	{

		clearAllDataSources();

		


		return true;
	}
	//----------------------------------------------------------------
	DataSourcePtr ShapeManager::openShapeFile( const String& filepath )
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
			ShapeReader::readFromShpFile( filepath ,tmppath , _filter );

		if ( psource.isNull() == true )
		{
			return DataSourcePtr();
		}

		_datasources.insert( std::make_pair( filepath , psource ) );

		return psource;
	}

	//----------------------------------------------------------------
	DataSource* ShapeManager::openShapeFile2( const String& filepath )
	{
		DataSourcePtr psource = openShapeFile(filepath);

		return psource.getPointer();
	}
	//----------------------------------------------------------------
	DataSourcePtr ShapeManager::openShapeFileSpecially( const String& filepath )
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
	DataSource* ShapeManager::openShapeFileSpecially2( const String& filepath )
	{
		DataSourcePtr psource = openShapeFileSpecially(filepath);

		return psource.getPointer();
	}
	//----------------------------------------------------------------
	bool ShapeManager::checkOpened( const String& filepath )
	{
		DataSourcePtrMap::iterator iter = _datasources.find( filepath );

		if ( iter == _datasources.end() )
		{
			return false;
		}

		return true;
	}
	//----------------------------------------------------------------
	void ShapeManager::renderShapes()
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
		if ( _querySurface != NULL )
		{
			_querySurface->render();
		}
		return;
	}
	//----------------------------------------------------------------
	void CALLBACK tessError( GLenum error )
	{
		const char *szError = (const char*)gluErrorString(error);

		assert(0&&"ShapeManager::tessError");

		VGK_CHECK_OPENGL_ERROR();

		return;
	}
	//----------------------------------------------------------------
	bool ShapeManager::onDeleteRenderer( vgKernel::Renderer *render )
	{
		if ( render->getType() != RENDERER_TYPE_SHAPE_LAYER	)
		{
			return false;
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
	void ShapeManager::clearAllDataSources()
	{
		if ( _selector != NULL )
		{
			delete _selector;
			_selector = NULL;
		}

		_datasources.clear();
	}
	//----------------------------------------------------------------
	bool ShapeManager::setSelectMode( vgKernel::Renderer* selected_layer , 
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
	bool ShapeManager::clearDataSource( const String& datasource_filepath )
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
	bool ShapeManager::clearDataSourcePtr( const DataSourcePtr& psource )
	{
		return clearDataSource( psource->getFilePath() );
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
	void ShapeManager::setShpLoadingFilter( double dfMinX,
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
	DataSourcePtr ShapeManager::getDataSourceByPathName( 
		const String& pathname )
	{
		DataSourcePtrMap::iterator iter = _datasources.begin();
		DataSourcePtrMap::iterator iter_end = _datasources.end();

		for ( ; iter != iter_end ;++iter )
		{
			DataSourcePtr pds = iter->second;
			if ( pds->getFilePath() == pathname )
			{
				return pds;
			}
		}

		return DataSourcePtr();
	}
	//----------------------------------------------------------------
	//----------------------------------------------------------------
	DataSourcePtr ShapeManager::getDataSourceByShortName( 
		const String& shortname )
	{
		DataSourcePtrMap::iterator iter = _datasources.begin();
		DataSourcePtrMap::iterator iter_end = _datasources.end();

		for ( ; iter != iter_end ;++iter )
		{
			DataSourcePtr pds = iter->second;
			if ( 
				vgKernel::StringUtility::getFilenameFromAbsolutePath(
				pds->getFilePath() ) == shortname )
			{
				return pds;
			}
		}

		return DataSourcePtr();
	}

	Layer* ShapeManager::getLayerByShortName( const String& shortname )
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
	String ShapeManager::readProject( const String& projpath )
	{
		String shps = VG_PROJCONF_GET_STRING( VG_SHAPE_STR , 
			VG_SHAPE_SHPPATH_STR );

		
		return shps;
#if 0
		//------------------------------------------
		// 首先分辨shps
		//------------------------------------------
		const String tok = ";";
		StringVector shpvec = vgKernel::StringUtility::tokenize( shps , tok , true);

		StringVector::iterator iter = shpvec.begin();
		StringVector::iterator iter_end = shpvec.end();

		for ( ; iter != iter_end ; ++ iter )
		{
			// 开始读取shp
			const String tok2 = ",";
			StringVector strs = vgKernel::StringUtility::tokenize( *iter , tok2 , true );
			if ( strs.size() > 2 || strs.size() == 0 )
			{
				continue;
			}

			String abspath = projpath + "\\" + strs[0];

			//assert(0);

#if 1

			if ( strs.size() == 1 )
			{
				if ( openShapeFile( abspath ).isNull() )
				{
					//assert(0);
#if VGK_LANG_CHS
					std::ostringstream o ;
					o << "打开文件:" << strs[0] << "时, 发生错误, 文件未打开.";
					vgKernel::SystemUtility::showModelDialog(o.str());
#else
					std::ostringstream o ;
					o << "When open:" << strs[0] << ", failed.";
					vgKernel::SystemUtility::showModelDialog(o.str());
#endif
					continue;
				}
			}
			else
			{
				if ( openShapeFileSpecially( abspath ).isNull() )
				{
					//assert(0);
#if VGK_LANG_CHS
					std::ostringstream o ;
					o << "打开文件:" << strs[0] << "时, 发生错误, 文件未打开.";
					vgKernel::SystemUtility::showModelDialog(o.str());
#else
					std::ostringstream o ;
					o << "open:" << strs[0] << ", failed.";
					vgKernel::SystemUtility::showModelDialog(o.str());
#endif
					continue;
				}
			}

#endif
		}
#endif

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
		
	}
	//----------------------------------------------------------------
	void ShapeManager::saveProject( const String& projpath )
	{
		std::ostringstream shps;
		std::ostringstream layers;

		//------------------------------------------
		// 存储shp的path信息
		//------------------------------------------
		DataSourcePtrMap::iterator iter = _datasources.begin();
		DataSourcePtrMap::iterator iter_end = _datasources.end();
		for ( ; iter != iter_end ; ++ iter )
		{
			DataSourcePtr ds = iter->second;

			if ( ds->saveToFilePath( projpath + "\\" + ds->getShortName() ) 
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
			
			if ( ds->isSpecial() )
			{	
				shps << ds->getShortName() << ",special;";
			}
			else
			{
				shps << ds->getShortName() << ";";
			}


			LayerPtrVector::iterator i = ds->getLayerPtrVector()->begin();
			LayerPtrVector::iterator i_end = ds->getLayerPtrVector()->end();

			for ( ; i != i_end ; ++ i )
			{
				LayerPtr la = *i;

				layers << la->getName() << ":";

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

		VG_PROJCONF_SET( VG_SHAPE_STR , 
			VG_SHAPE_SHPPATH_STR , shps.str() );

		VG_PROJCONF_SET( VG_SHAPE_STR , 
			VG_SHAPE_SHPMAT_STR , layers.str() );

	}

	bool ShapeManager::initialise()
	{
		OGRRegisterAll();

		CPLSetErrorHandler( ogrErrorHandler );

		return true;
	}

	bool ShapeManager::shutdown()
	{
		if ( _filter != NULL )
		{
			delete _filter;
			_filter = NULL;
		}
		if ( _querySurface != NULL )
		{
			delete _querySurface;
			_querySurface = NULL;
		}
		assert( _selector == NULL );
		assert( _querySurface == NULL );
		OGRCleanupAll();
		return true;
	}

	
#if 1
	//--分析功能------------------------------------------------------
	bool ShapeManager::setQueryRatioFlag( vgShape::QueryType qType)
	{
		if ( _querySurface != NULL )
		{
			if(_querySurface->getQueryType() == qType)
			{
				delete _querySurface;
				_querySurface = NULL;
			}
			else
			{
				_querySurface->setQueryType(qType);
				_querySurface->setKeyFieldName(_keyFieldName);
			}
		}
		else
		{	
			// 是否满足分析条件
			vgKernel::RendererQueue&	pSelectedItems = vgKernel::SelectManager
				::getSingleton().getSelectedItems();

			//case 1
			if (pSelectedItems.empty() || 
				vgShape::RENDERER_TYPE_SHAPE_LAYER != pSelectedItems[0]->getType() )
			{
				std::ostringstream o;
				o << "您未选中任何矢量图层，请选择！" ;
				MessageBox( NULL , o.str().c_str() , "分析条件不满足" , MB_OK );
				return false;
			}

			//case 2
			if ( 1 < pSelectedItems.size())
			{
				std::ostringstream o;
				o << "您选中了多层矢量图层，一次只能对一个图层分析，请重新选择！" ;
				MessageBox( NULL , o.str().c_str() , "分析条件不满足" , MB_OK );
				return false;
			}




			//case 3
			String layername = pSelectedItems[0]->getName();
			if (  strcmp(layername.c_str(), "green")
				&&strcmp(layername.c_str(), "GREEN")
				&&strcmp(layername.c_str(), "house")
				&&strcmp(layername.c_str(), "HOUSE"))
			{
				std::ostringstream o;
				o << "当前选择的图层是绿化或楼房吗？请确认，若不是请重新选择！" ;
				if ( IDNO == MessageBox( NULL , o.str().c_str() , 
					"图层是绿化层吗？" , MB_YESNO ))
				{
					return false;			
				}
			}

			_querySurface = new vgShape::vgshQuerySurface(qType/*, _keyFieldName*/);

		}

		return true;
	}

	//----------------------------------------------------------------
	vgShape::QueryType	ShapeManager::getQueryType()
	{
		if (_querySurface)
		{
			return _querySurface->getQueryType();
		}
		else
		{
			return vgShape::QUERY_NONE;
		}
	}

	//----------------------------------------------------------------
	vgShape::vgshQuerySurface* ShapeManager::getQuerySurface()
	{
		return _querySurface; 
	}

	//----------------------------------------------------------------
	void ShapeManager::setQueryRatioKeyField(String fieldName)
	{
		_keyFieldName = fieldName;
		if (_querySurface)
		{
			_querySurface->setKeyFieldName(fieldName);
		}
	}

	//----------------------------------------------------------------
	void ShapeManager::reset()
	{
		uninitBeforeOpenGLDestroy();
	}

	GeometryPointerVec* ShapeManager::getSelectGeometriesFromLayer( Layer* layer )
	{
		return layer->getSelectedGeometry();
	}

	LayerPtrVector* ShapeManager::getLayersFromDataSource( vgShape::DataSource* psource )
	{
		return psource->getLayerPtrVector();
	}

	void ShapeManager::readProjectExtra( const String& projpath )
	{

		if ( _datasources.empty() )
		{
			return;
		}

		String mats = VG_PROJCONF_GET_STRING( VG_SHAPE_STR , 
			VG_SHAPE_SHPMAT_STR );

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

	}

	vgShape::DataSourcePtr& ShapeManager::getCurrentDataSource()
	{
		return _currentDataSource;
	}
	//----------------------------------------------------------------

#endif

	bool ShapeManager::constructTopMap()
	{

		return true;
	}
}// end of namespace vgShape
