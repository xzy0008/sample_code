


#include <vgStableHeaders.h>
#include <vgImage/vgiCximageWrapper.h>
#include <vgTerritory/vgtGeoImage.h>
#include <vgTerritory/vgtGeoDemManager.h>
#include <vgImage/vgiFreeImageWrapper.h>


namespace vgTerritory {
	

	//----------------------------------------------------------------
	GeoImage::GeoImage( String filepath , GeoGlobalData* global_data)
	{
		_globalData = global_data;
		_isValid = false;
		_filePath = filepath;

		_upperLeftX = 0.0;
		_upperLeftX = 0.0;

		_gdalDataSet = NULL;

		_pixelSizeX = 0.0;
		_pixelSizeY = 0.0;

		_lowerRightX = 0.0;
		_lowerRightY = 0.0;
		_sizeX = 0;
		_sizeY = 0;

		//_overview = NULL;
	}
	//----------------------------------------------------------------
	GeoImage::~GeoImage()
	{
		if ( _gdalDataSet != NULL )
		{
			delete _gdalDataSet;
			_gdalDataSet = NULL;
		}

		//if ( _overview != NULL )
		//{
		//	delete _overview;
		//	_overview =NULL;
		//}
	}
	//----------------------------------------------------------------
	bool GeoImage::doOpen()
	{
		//------------------------------------------
		// 得到GDALDataSet
		// 并且在本域内保证释放
		//------------------------------------------
		getGDALDataSet();
		if ( _gdalDataSet == NULL )
		{
			return false;
		}
		GdalDataSetGuide guide( &_gdalDataSet );


		_isValid = readFileAndCheckValid();

		if ( _isValid == false )
		{
			return false;
		}

		_isValid = readDataAndUpdate();

		if ( _isValid == false )
		{
			return false;
		}

		return _isValid;
	}
	//----------------------------------------------------------------
	String GeoImage::getFilePath() const
	{
		return _filePath;
	}
	//----------------------------------------------------------------
	bool GeoImage::readFileAndCheckValid()
	{
		assert( _gdalDataSet != NULL );
		assert( _filePath.empty() == false );


		if( _gdalDataSet == NULL )
		{
			return false;
		}

		int nBandCount = _gdalDataSet->GetRasterCount();

		assert( nBandCount > 0 );
		//assert( nBandCount == 3 );

		if ( nBandCount != 3 )
		{
			MessageBox( NULL , "影像文件不是标准RGB格式" , "Error" , MB_OK );
			return false;
		}

		GDALRasterBand* rasterband = _gdalDataSet->GetRasterBand(1);

		assert( rasterband != NULL );

		if ( rasterband == NULL )
		{
			return false;
		}

		return true;
	}
	//----------------------------------------------------------------
	String GeoImage::getDetails()
	{
		assert( _gdalDataSet == NULL );

		//------------------------------------------
		// 得到GDALDataSet
		// 并且在本域内保证释放
		//------------------------------------------
		getGDALDataSet();
		if ( _gdalDataSet == NULL )
		{
			return "";
		}
		GdalDataSetGuide guide( &_gdalDataSet );


		assert( _gdalDataSet != NULL );

		double		adfGeoTransform[6];
		GDALDriverH		hDriver;

		int                 bComputeMinMax = FALSE, bSample = FALSE;
		int                 bShowGCPs = TRUE, bShowMetadata = TRUE ;
		int                 bStats = FALSE, bApproxStats = TRUE;
		int                 bShowColorTable = TRUE, bComputeChecksum = FALSE;
		const char          *pszFilename = NULL;
		char              **papszExtraMDDomains = NULL;
		const char  *pszProjection = NULL;
		OGRCoordinateTransformationH hTransform = NULL;


		GDALDatasetH hDataset = _gdalDataSet;

		hDriver = GDALGetDatasetDriver( hDataset );

		std::ostringstream o;

		o << "GeoImage details:< "
			<< " FilePath: " << _filePath
			<< " , Driver: " << GDALGetDriverShortName( hDriver )  
			<< " , Size: " <<  GDALGetRasterXSize( hDataset ) << ", " << GDALGetRasterYSize( hDataset );


#if 0
		/* -------------------------------------------------------------------- */
		/*      Report projection.                                              */
		/* -------------------------------------------------------------------- */
		if( GDALGetProjectionRef( hDataset ) != NULL )
		{
			OGRSpatialReferenceH  hSRS;
			char		      *pszProjection;

			pszProjection = (char *) GDALGetProjectionRef( hDataset );

			hSRS = OSRNewSpatialReference(NULL);
			if( OSRImportFromWkt( hSRS, &pszProjection ) == CE_None )
			{
				char	*pszPrettyWkt = NULL;

				OSRExportToPrettyWkt( hSRS, &pszPrettyWkt, FALSE );
				o << "\nCoordinate System is:" << pszPrettyWkt;
				CPLFree( pszPrettyWkt );
			}
			else
				o << "\nCoordinate System is:" << GDALGetProjectionRef( hDataset );

			OSRDestroySpatialReference( hSRS );
		}
#endif


		/* -------------------------------------------------------------------- */
		/*      Report Geotransform.                                            */
		/* -------------------------------------------------------------------- */
		if( GDALGetGeoTransform( hDataset, adfGeoTransform ) == CE_None )
		{
			if( adfGeoTransform[2] == 0.0 && adfGeoTransform[4] == 0.0 )
			{
				o << "\nOrigin = (" << 
					adfGeoTransform[0]
				<< " ," << adfGeoTransform[3] << " )";

				o << "\nPixel Size = (" << 
					adfGeoTransform[1]
				<< " ," << adfGeoTransform[5] << " )";
			}
			else
				o << "\nGeoTransform =\n"
				<< adfGeoTransform[0] << " ,"
				<< adfGeoTransform[1] << " ,"
				<< adfGeoTransform[2] << " ,"
				<< adfGeoTransform[3] << " ,"
				<< adfGeoTransform[4] << " ,"
				<< adfGeoTransform[5];
		}


		/* -------------------------------------------------------------------- */
		/*      Report corners.                                                 */
		/* -------------------------------------------------------------------- */
		o << "\nCorner Coordinates:\n";
		GDALInfoReportCorner( hDataset, hTransform, "Upper Left", 
			0.0, 0.0 , o );
		GDALInfoReportCorner( hDataset, hTransform, "Lower Left", 
			0.0, GDALGetRasterYSize(hDataset), o );
		GDALInfoReportCorner( hDataset, hTransform, "Upper Right", 
			GDALGetRasterXSize(hDataset), 0.0 , o );
		GDALInfoReportCorner( hDataset, hTransform, "Lower Right", 
			GDALGetRasterXSize(hDataset), 
			GDALGetRasterYSize(hDataset) , o );
		GDALInfoReportCorner( hDataset, hTransform, "Center", 
			GDALGetRasterXSize(hDataset)/2.0, 
			GDALGetRasterYSize(hDataset)/2.0 , o );

		if( hTransform != NULL )
		{
			OCTDestroyCoordinateTransformation( hTransform );
			hTransform = NULL;
		}

		//------------------------------------------
		// Geo 自身的信息
		//------------------------------------------
		o << "\n";
		o << "_rawRect: " << _rawRect.getDetails() << "\n";
		//o << "_worldRect: " << _worldRect.getDetails() << "\n";

		return o.str();
	}
	//----------------------------------------------------------------
	int GeoImage::GDALInfoReportCorner( GDALDatasetH hDataset,
		OGRCoordinateTransformationH hTransform, 
		const char * corner_name, double x, double y , 
		std::ostringstream& o )
	{
		double	dfGeoX, dfGeoY;
		double	adfGeoTransform[6];

		o<< "\n" 
			<< corner_name;

		/* -------------------------------------------------------------------- */
		/*      Transform the point into georeferenced coordinates.             */
		/* -------------------------------------------------------------------- */
		if( GDALGetGeoTransform( hDataset, adfGeoTransform ) == CE_None )
		{
			dfGeoX = adfGeoTransform[0] + adfGeoTransform[1] * x
				+ adfGeoTransform[2] * y;
			dfGeoY = adfGeoTransform[3] + adfGeoTransform[4] * x
				+ adfGeoTransform[5] * y;
		}
		else
		{
			assert(0 && " 不应该到这里");
			o << "(" <<  x << ", "  << y << " )";
			return FALSE;
		}

		/* -------------------------------------------------------------------- */
		/*      Report the georeferenced coordinates.                           */
		/* -------------------------------------------------------------------- */
		if( ABS(dfGeoX) < 181 && ABS(dfGeoY) < 91 )
		{
			o << "(" <<  dfGeoX << ", "  << dfGeoY << " )";
		}
		else
		{
			o << "(" <<  dfGeoX << ", "  << dfGeoY << " )";

		}

		/* -------------------------------------------------------------------- */
		/*      Transform to latlong and report.                                */
		/* -------------------------------------------------------------------- */
		if( hTransform != NULL 
			&& OCTTransform(hTransform,1,&dfGeoX,&dfGeoY,NULL) )
		{

			o << "(" <<  GDALDecToDMS( dfGeoX, "Long", 2 ) << ", "
				<< GDALDecToDMS( dfGeoY, "Lat", 2 )  << " )";
		}


		return TRUE;
	}
	//----------------------------------------------------------------
	bool GeoImage::readDataAndUpdate()
	{
		assert( _gdalDataSet != NULL );
		if ( _gdalDataSet == NULL )
		{
			return false;
		}

		assert( _gdalDataSet->GetRasterCount() == 3 );
		GDALRasterBand* band = _gdalDataSet->GetRasterBand(1);
		assert( band != NULL );

		_sizeX = band->GetXSize();
		_sizeY = band->GetYSize();

#if _DEBUG

		for ( int i = 0 ; i < 3 ; ++ i )
		{
			GDALRasterBand* band = _gdalDataSet->GetRasterBand(i + 1);
			assert( band != NULL );

			assert( _sizeX == band->GetXSize() );
		}

#endif

		//------------------------------------------
		// 更新原点和cellsize
		//------------------------------------------

#define  VGT_FORCE_USE_GEOGCS 0

		OGRCoordinateTransformation *poCT = NULL;

#if VGT_FORCE_USE_GEOGCS



		//const char* proj_ref = _gdalDataSet->GetProjectionRef();
		//if ( proj_ref == NULL )
		//{

		//}
		//else
		//{
		//	OGRSpatialReference sref;
		//	sref.importFromWkt( (char**)&proj_ref );

		//	OGRErr err = sref.Validate();
		//	assert( err == OGRERR_NONE );

		//	if ( sref.IsProjected() )
		//	{
		//		
		//		// 转换成Geogcs坐标
		//		OGRSpatialReference* georef = sref.CloneGeogCS();
		//		assert( georef != NULL );

		//		poCT = OGRCreateCoordinateTransformation( &sref, georef );

		//		assert( poCT != NULL );

		//		georef->Dereference();
		//	}
		//}
#endif


		double		adfGeoTransform[6];
		if( _gdalDataSet->GetGeoTransform( adfGeoTransform ) == CE_None )
		{
			//------------------------------------------
			// 保证只是一种情况
			//------------------------------------------
			//assert( adfGeoTransform[2] == 0.0 && adfGeoTransform[4] == 0.0 );

			if ( poCT != NULL )
			{
				double projlowerrightX  = adfGeoTransform[0] + 
					adfGeoTransform[1] * _gdalDataSet->GetRasterXSize();

				double projlowerrightY = adfGeoTransform[3] + 
					+ adfGeoTransform[5] * _gdalDataSet->GetRasterYSize();

				poCT->Transform( 1 , &adfGeoTransform[0] , &adfGeoTransform[3] );
				poCT->Transform( 1 , &projlowerrightX , &projlowerrightY );

				delete poCT;

				_upperLeftX = adfGeoTransform[0];
				_upperLeftY = adfGeoTransform[3];

				_lowerRightX = projlowerrightX;

				_lowerRightY = projlowerrightY;

				_pixelSizeX = (_lowerRightX - _upperLeftX ) /
					(double)_gdalDataSet->GetRasterXSize();

				_pixelSizeY = (_lowerRightY - _upperLeftY ) /
					(double)_gdalDataSet->GetRasterYSize();
			}
			else
			{
				_upperLeftX = adfGeoTransform[0];
				_upperLeftY = adfGeoTransform[3];

				_lowerRightX = adfGeoTransform[0] + 
					adfGeoTransform[1] * _gdalDataSet->GetRasterXSize();

				_lowerRightY = adfGeoTransform[3] + 
					+ adfGeoTransform[5] * _gdalDataSet->GetRasterYSize();

				_pixelSizeX = adfGeoTransform[1];
				_pixelSizeY = adfGeoTransform[5];
			}
			


			//o << "\nOrigin = (" << 
			//	adfGeoTransform[0]
			//<< " ," << adfGeoTransform[3] << " )";

			//o << "\nPixel Size = (" << 
			//	adfGeoTransform[1]
			//<< " ," << adfGeoTransform[5] << " )";
		}
		else
		{
			return false;
		}

		//------------------------------------------
		// 更新长宽
		//------------------------------------------
		long width = band->GetXSize();
		long height = band->GetYSize();

		assert( width == _gdalDataSet->GetRasterXSize() );

		// 这里要减1. 例如,501个网格点,则应该是(0,0)到(500,500)共501个点.
		_rawRect.minPos = vgKernel::ImagePos(0,0);
		_rawRect.maxPos = vgKernel::ImagePos( width - 1, height - 1);

		return true;
	}
	//----------------------------------------------------------------
	//GeoDemOverview* GeoImage::generateOverview()
	//{
	//	//------------------------------------------
	//	// 注意!!这里应该被updateGlobalInfo了.
	//	//------------------------------------------
	//	assert(_worldRect.getCenter().x != 0 );


	//	GDALRasterBand* band = _gdalDataSet->GetRasterBand(1);
	//	assert( band != NULL );

	//	assert( _sizeX != 0 );

	//	//------------------------------------------
	//	// 设定overview都是原来的16分之一.
	//	//------------------------------------------
	//	long overview_width = _sizeX / VGT_OVERVIEW_DIVIDE;
	//	long overview_height = _sizeY / VGT_OVERVIEW_DIVIDE;

	//	float* buf_float = new float[ overview_width * overview_height ];

	//	CPLErr rasterok = band->RasterIO(GF_Read, 
	//		0, 0, _sizeX, _sizeY, 
	//		buf_float, overview_width, overview_height ,
	//		GDT_Float32, 0, 0 );

	//	if ( rasterok != CE_None )
	//	{
	//		delete buf_float;
	//		return NULL;
	//	}

	//	byte* buf_byte = new byte[ overview_width * overview_height ];

	//	//------------------------------------------
	//	// 注意,这里应该取GlobalData的信息
	//	//------------------------------------------
	//	float delta_elevation = 
	//		_globalData->_globalMaxElevation - _globalData->_globalMinElevation;

	//	assert( delta_elevation > 0.0f );

	//	for ( int i = 0 ; i < overview_width * overview_height ; ++ i )
	//	{
	//		float curvalue = buf_float[i];
	//		curvalue = curvalue * _zScale + _zOffset;

	//		// 到maxElevation与minElevation之间.
	//		curvalue -= _globalData->_globalMinElevation;

	//		// 到0.0与1.0之间.
	//		curvalue /= delta_elevation;

	//		// 到0与255之间.
	//		curvalue *= 255;

	//		buf_byte[i] = curvalue;
	//	}


	//	GeoDemOverview* ret =  new GeoDemOverview( 
	//		buf_byte , overview_width , overview_height , 
	//		vgKernel::ImageRect( _worldRect.minPos.x / VGT_OVERVIEW_DIVIDE , 
	//		_worldRect.minPos.y / VGT_OVERVIEW_DIVIDE , 
	//		overview_width , overview_height ) );

	//	// 删除缓冲区
	//	delete buf_float;
	//	delete buf_byte;

	//	return ret;
	//}

	//----------------------------------------------------------------
	GeoImageFileBlock* GeoImage::rectResize(
		const GeoDoubleRect& cut_rect )
	{
		assert( isValid() );
		assert( _gdalDataSet != NULL );

		assert( testIntersect( cut_rect ) == true );

		String tifFile = _filePath;

		GeoGlobalData* global_data = 
			GeoDemManager::getSingleton().getGlobalDataPtr();
		assert( global_data != NULL );

		GDALDataset* pDataSet = _gdalDataSet;
		
		int nBand = 3;

		if ( pDataSet->GetRasterCount() != nBand )
		{
			return NULL;
		}

		assert( nBand == pDataSet->GetRasterCount() );


		//------------------------------------------
		// 找到tif的边界信息
		//------------------------------------------
		//double adfGeoTransform[6];
		//pDataSet->GetGeoTransform( adfGeoTransform );

		//double tifTopLeftX = adfGeoTransform[0];
		//double tifTopLeftY = adfGeoTransform[3];
		//double tifLowRightX = adfGeoTransform[0] + adfGeoTransform[1] * pDataSet->GetRasterXSize()
		//	+ adfGeoTransform[2] * pDataSet->GetRasterYSize();
		//double tifLowRightY= adfGeoTransform[3] + adfGeoTransform[4] * pDataSet->GetRasterXSize()
		//	+ adfGeoTransform[5] * pDataSet->GetRasterYSize();

		//double tifPixelSizeX = adfGeoTransform[1];
		//double tifPixelSizeY = adfGeoTransform[5];

		double tifTopLeftX = _upperLeftX;
		double tifTopLeftY = _upperLeftY;
		double tifLowRightX = _lowerRightX;
		double tifLowRightY= _lowerRightY;

		double tifPixelSizeX = _pixelSizeX;
		double tifPixelSizeY = _pixelSizeY;

		long self_width = pDataSet->GetRasterXSize();
		assert( self_width > 0 );
		long self_height = pDataSet->GetRasterYSize();
		assert( self_height > 0 );

		//------------------------------------------
		// 计算本地坐标在全局中的ImageRect
		// 注意,这里是Image域,不是dem域
		//------------------------------------------
		assert( global_data->_globalCellTexSize != 0 );
		//double dx = tifTopLeftX - global_data->_globalUpperLeftX;
		//double dy = 0.0;

		//if ( _globalData->_axisLeftDown == true )
		//{
		//	dy = tifTopLeftY - global_data->_globalUpperLeftY;
		//}
		//else
		//{
		//	dy = tifTopLeftY - global_data->_globalUpperLeftY;
		//}

		//long origin_transX = dx / global_data->_globalPixelSizeX;
		//long origin_transY = dy / global_data->_globalPixelSizeY;
		//origin_transX *= ( global_data->_globalCellTexSize );
		//origin_transY *= ( global_data->_globalCellTexSize );

		//------------------------------------------
		// 转换rect信息
		//------------------------------------------
		ImageRect local_big_rect = ImageRect( 0 , 0, self_width - 1 , self_height - 1 );

		GeoDoubleRect cut_drect( _globalData );

		if ( _globalData->_axisLeftDown == true )
		{
			cut_drect = cut_rect.translateCopy( 
				tifTopLeftX * (-1.0) , tifTopLeftY * (-1.0) );

			cut_drect.setRectData( cut_drect.getTopLeftX() , 
				(-1.0) * cut_drect.getTopLeftY() , cut_drect.getLowRightX() ,
				(-1.0) * cut_drect.getLowRightY() );
		}
		else
		{
			cut_drect = cut_rect.translateCopy( 
				tifTopLeftX * (-1.0) , tifTopLeftY * (-1.0) );
		}


		ImageRect cut_irect = cut_drect.getImageRect( tifPixelSizeX , tifPixelSizeY );

		ImageRect intersect_rect;
		bool is_intersect = local_big_rect.findIntersection( cut_irect , intersect_rect );

		if ( is_intersect == false )
		{
			// 这个时候没有相交
			return NULL;
		}

		bool is_inside = local_big_rect.testInside( cut_irect );


		//////////////////////////////////////////////////////////////////////////
		//------------------------------------------
		// 计算各个resize的大小等等
		//------------------------------------------
		GeoDoubleRect selfDRect( _upperLeftX , _upperLeftY , 
			_lowerRightX , _lowerRightY , _globalData );

		GeoDoubleRect intersectDRect( _globalData );

		bool isintersect = selfDRect.findIntersection( cut_rect , intersectDRect );
		assert( isintersect == true );

		long resizedWidth = ( intersectDRect.getWidth() / 
			abs( _globalData->_globalPixelSizeX ) + 0.5f )* 
			_globalData->_globalCellTexSize;

		long resizedHeight = ( intersectDRect.getHeight() / 
			abs( _globalData->_globalPixelSizeY ) + 0.5f )* 
			_globalData->_globalCellTexSize;

		//------------------------------------------
		// 开始计算位移,相对于本block和原点
		//------------------------------------------
		double deltaX = intersectDRect.getTopLeftX() - global_data->_globalUpperLeftX;
		double deltaY = 0.0;

		if ( global_data->_axisLeftDown == true )
		{
			deltaY = global_data->_globalUpperLeftY - intersectDRect.getTopLeftY();
		}
		else
		{
			deltaY = intersectDRect.getTopLeftY() - global_data->_globalUpperLeftY;
		}

		long origin_transX = deltaX / abs( global_data->_globalPixelSizeX ) + 0.5;
		long origin_transY = deltaY / abs( global_data->_globalPixelSizeY ) + 0.5;
		origin_transX *= ( global_data->_globalCellTexSize );
		origin_transY *= ( global_data->_globalCellTexSize );

		ImageRect retAbsRect( origin_transX , origin_transY , 
			origin_transX + resizedWidth - 1, 
			origin_transY + resizedHeight - 1 );

		//////////////////////////////////////////////////////////////////////////

		//------------------------------------------
		// 开始读取相交的部分
		//------------------------------------------
		long buffer_width = intersect_rect.getWidth() + 1;
		long buffer_height = intersect_rect.getHeight() + 1;
		long buffer_size = buffer_width * buffer_height * nBand;
		byte* buffer = new byte[ buffer_size ];

		memset( buffer , 0  ,  buffer_size );

		using namespace vgThreads;

		static CriticalSection rasteriosect;

		ScopedLock locker( rasteriosect );

		CPLErr raster_ret = pDataSet->RasterIO( 
			GF_Read , intersect_rect.minPos.x , intersect_rect.minPos.y , 
			buffer_width ,  buffer_height ,
			buffer , buffer_width ,  buffer_height ,
			GDT_Byte, nBand, NULL, nBand, 0, 1 );

		if ( raster_ret != CE_None )
		{
			::AfxMessageBox("读取影像数据时失败!");
			delete[] buffer;

			return NULL;
		}

		FreeImageWrapperPtr img( new FreeImageWrapper );

		bool createok = img->createFromArray( 
			buffer , buffer_width , buffer_height , 24 );

		//img->flipVertical();
		img->swapRedAndBlueChannel();

		delete[] buffer;
		buffer = NULL;

		if ( createok == false )
		{
			assert(0);
// 			bool createok = img->createFromArray( 
// 				buffer , buffer_width , buffer_height , 24 , true , true );

			return NULL;
		}

		assert( createok == true );

		bool resizeok = img->resize( ImageSize( resizedWidth ,resizedHeight ) );

		assert( resizeok == true );


		//------------------------------------------
		// 创建输出名称
		//------------------------------------------
		std::ostringstream o;
		o << _globalData->_imageDirectory << "\\";

		o << "GeoImg_" 
			<< "_" << retAbsRect.minPos[0]
			<< "_" << retAbsRect.minPos[1]
			<< "_" << retAbsRect.maxPos[0]
			<< "_" << retAbsRect.maxPos[1]
			<< UniqueIDFactory::getUniqueID().getString() 
			<< "." << VGT_GEOMGR_TEMP_EXT;

		String out_filename = o.str();

		// 开始保存
		bool saveok = img->saveToFile( out_filename );
		if ( saveok == false )
		{
			::AfxMessageBox( "保存影像时失败!" );
			return NULL;
		}

		return new GeoImageFileBlock( out_filename , retAbsRect );
	}
	//----------------------------------------------------------------
	GeoImageFileBlockVecPtr GeoImage::cutToFileBlocks(
		GeoDoubleRectVec* input_rects )
	{
		assert( _gdalDataSet == NULL );

		//------------------------------------------
		// 得到GDALDataSet
		// 并且在本域内保证释放
		//------------------------------------------
		getGDALDataSet();
		if ( _gdalDataSet == NULL )
		{
			return GeoImageFileBlockVecPtr();
		}
		GdalDataSetGuide guide( &_gdalDataSet );

		//------------------------------------------
		// 开始切割
		//------------------------------------------
		assert( input_rects != NULL );

		GeoImageFileBlockVecPtr ret( new GeoImageFileBlockVec );

		GeoDoubleRectVec::iterator ri = input_rects->begin();
		GeoDoubleRectVec::iterator riend = input_rects->end();

		for ( ; ri != riend ; ++ ri )
		{
			if ( testIntersect( *ri ) == true )
			{
				// 如果相交,开始切割,并且保存
				GeoImageFileBlock* fileblock = rectResize( *ri );

				if ( fileblock == NULL )
				{
					continue;
				}

				assert( fileblock != NULL );

				ret->push_back( *fileblock );

				delete fileblock;
			}
		}

		if ( ret->empty() ==true )
		{
			return GeoImageFileBlockVecPtr();
		}

		return ret;
	}
	//----------------------------------------------------------------
	void GeoImage::getGDALDataSet()
	{
		assert( _gdalDataSet == NULL );

		_gdalDataSet = (GDALDataset *) GDALOpen( 
			_filePath.c_str() , GA_ReadOnly );

		if( _gdalDataSet == NULL )
		{
			std::ostringstream o ;
			o << "打开文件失败:" << _filePath;
			MessageBox( NULL , o.str().c_str() , "error", MB_OK );
		}
	}
	//----------------------------------------------------------------
	
	
	//----------------------------------------------------------------
	void GeoImageCutFileJob::doJob()
	{
		long count = _boss->getCounter()->getCount();
		_notifier->setCurrentProcessPos( _geoImg->getFilePath() ,  count );

		GeoImageFileBlockVecPtr blocks = _geoImg->cutToFileBlocks( _doubleRect );

		if ( blocks.isNull() == false )
		{
			ScopedLock locker( *_sect );
			GeoImageFileBlockVec::iterator iter = blocks->begin();
			GeoImageFileBlockVec::iterator iter_end = blocks->end();

			for ( ; iter != iter_end ; ++iter )
			{
				_geoImgVec->push_back( *iter );
			}
		}
	}
	//----------------------------------------------------------------


}// end of namespace vgTerritory
