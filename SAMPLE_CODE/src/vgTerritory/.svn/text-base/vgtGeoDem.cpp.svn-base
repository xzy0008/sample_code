


#include <vgStableHeaders.h>
#include <vgTerritory/vgtGeoDem.h>
#include <vgKernel/vgkMath.h>
#include <vgImage/vgiCximageWrapper.h>
#include <vgImage/vgiImageRGBA.h>
#include <vgImage/vgiFreeImageWrapper.h>



namespace vgTerritory {
	
	
	
	
	//----------------------------------------------------------------
	GeoDem::GeoDem( String filepath , GeoGlobalData* global_data)
	{
		_globalData = global_data;
		_isValid = false;
		_filePath = filepath;

		_upperLeftX = 0.0;
		_upperLeftX = 0.0;

		_gdalDataSet = NULL;

		_zScale = 1.0f;
		_zOffset = 0.0f;

		_maxElevation = 0.0;
		_minElevation = 0.0;

		_noDataValue = 0.0;

		_pixelSizeX = 0.0;
		_pixelSizeY = 0.0;

		_lowerRightX = 0.0;
		_lowerRightY = 0.0;
		_sizeX = 0;
		_sizeY = 0;

		_overview = NULL;

		_hasReadMinAndMaxElevation = false;
		_hasReadOverview = false;
	}
	//----------------------------------------------------------------
	GeoDem::~GeoDem()
	{
		if ( _gdalDataSet != NULL )
		{
			delete _gdalDataSet;
			_gdalDataSet = NULL;
		}

		if ( _overview != NULL )
		{
			delete _overview;
			_overview =NULL;
		}
	}
	//----------------------------------------------------------------
	bool GeoDem::doOpen()
	{
		//------------------------------------------
		// 首先打开文件
		//------------------------------------------
		assert( _filePath.empty() == false );
		assert( _gdalDataSet == NULL ); 

		getGDALDataSet();

		if ( _gdalDataSet == NULL )
		{
			return false;
		}

		GdalDataSetGuide guide( &_gdalDataSet );

		int nBandCount = _gdalDataSet->GetRasterCount();
		assert( nBandCount > 0 );

		//------------------------------------------
		// 开始读取overview和高度数据
		//------------------------------------------
		_isValid = readDemDataAndUpdate();

		if ( _isValid == false )
		{
			std::ostringstream o ;
			o << "预读取文件内容时失败:" << _filePath;
			MessageBox( NULL , o.str().c_str() , "error", MB_OK );

			return false;
		}


		_isValid = true;

		return _isValid;
	}
	//----------------------------------------------------------------
	String GeoDem::getFilePath() const
	{
		return _filePath;
	}
	//----------------------------------------------------------------
	String GeoDem::getDetails()
	{
		assert(0);

		assert( _gdalDataSet == NULL );
		getGDALDataSet();

		if ( _gdalDataSet == NULL )
		{
			return "";
		}

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

		o << "GeoDem details:< "
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
		o << "_worldRect: " << _worldRect.getDetails() << "\n";
		o << "_maxElevation: " << _maxElevation << "\n";
		o << "_minElevation: " << _minElevation << "\n";
		o << "_zScale: " << _zScale << "\n";
		o << "_zOffset: " << _zOffset << "\n";



		return o.str();
	}
	//----------------------------------------------------------------
	int GeoDem::GDALInfoReportCorner( GDALDatasetH hDataset,
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
	bool GeoDem::readDemDataAndUpdate()
	{
		assert( _gdalDataSet != NULL );

		GDALRasterBand* band = _gdalDataSet->GetRasterBand(1);
		assert( band != NULL );

		_noDataValue = band->GetNoDataValue();

		_sizeX = band->GetXSize();
		_sizeY = band->GetYSize();

		//------------------------------------------
		// 更新原点和cellsize
		//------------------------------------------
		double		adfGeoTransform[6];
		if( _gdalDataSet->GetGeoTransform( adfGeoTransform ) == CE_None )
		{
			//------------------------------------------
			// 保证只是一种情况
			//------------------------------------------
			_upperLeftX = adfGeoTransform[0];
			_upperLeftY = adfGeoTransform[3];

			_lowerRightX = adfGeoTransform[0] + 
				adfGeoTransform[1] * _gdalDataSet->GetRasterXSize();

			_lowerRightY = adfGeoTransform[3] + 
				+ adfGeoTransform[5] * _gdalDataSet->GetRasterYSize();

			_pixelSizeX = adfGeoTransform[1];
			_pixelSizeY = adfGeoTransform[5];
		}
		else
		{
			return false;
		}

		//------------------------------------------
		// 设置scale和offset
		//------------------------------------------
		_zOffset = band->GetOffset();
		_zScale = band->GetScale();

		String unit = band->GetUnitType();

		if ( unit == "" )
		{
			unit = "m";
		}

		/**
			是否foot单位.如果是,需要转换为metre
			系数:FOOT_TO_METRE
		*/
		assert( unit == "ft" || unit == "m" );

		if ( unit == "ft" )
		{
			_zScale *= FOOT_TO_METRE;
		}

		//------------------------------------------
		// 更新最大值最小值
		//------------------------------------------

		if ( _globalData->_genElevationOverview )
		{
			bool readok =  readMinAndMaxElevation();

			if ( readok == false )
			{
				return false;
			}

			bool readok2 = readOverview();

			if ( readok2 == false )
			{
				return false;
			}
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
	GeoDemOverview* GeoDem::generateOverview()
	{
		assert( _gdalDataSet != NULL );

		//------------------------------------------
		// 这里没有被updateGlobalInfo!!!!!!!!!
		//------------------------------------------
		assert(_worldRect.getCenter().x == 0 );


		GDALRasterBand* band = _gdalDataSet->GetRasterBand(1);
		assert( band != NULL );

		assert( _sizeX != 0 );

		//------------------------------------------
		// 设定overview都是原来的16分之一.
		//------------------------------------------
		long overview_width = _sizeX / VGT_OVERVIEW_DIVIDE;
		long overview_height = _sizeY / VGT_OVERVIEW_DIVIDE;
		
		float* buf_float = new float[ overview_width * overview_height ];

		CPLErr rasterok = band->RasterIO(GF_Read, 
			0, 0, _sizeX, _sizeY, 
			buf_float, overview_width, overview_height ,
			GDT_Float32, 0, 0 );

		if ( rasterok != CE_None )
		{
			delete buf_float;
			return NULL;
		}

		byte* buf_byte = new byte[ overview_width * overview_height ];
		memset( buf_byte , 0 , overview_height * overview_width );

		//------------------------------------------
		// 注意,这里应该取GlobalData的信息
		// 但是为了预读,先取自身的信息.
		//------------------------------------------
		//float delta_elevation = 
		//	_globalData->_globalMaxElevation - _globalData->_globalMinElevation;

		float delta_elevation = _maxElevation - _minElevation;


		assert( delta_elevation > 0.0f );

		for ( int i = 0 ; i < overview_width * overview_height ; ++ i )
		{
			float curvalue = buf_float[i];
			curvalue = curvalue * _zScale + _zOffset;

			// 到maxElevation与minElevation之间.
			curvalue -= _minElevation;

			// 到0.0与1.0之间.
			curvalue /= delta_elevation;

			// 到0与255之间.
			curvalue *= 255;

			buf_byte[i] = curvalue;
		}


		GeoDemOverview* ret =  new GeoDemOverview( 
			buf_byte , overview_width , overview_height , 
			vgKernel::ImageRect::ZERO , _minElevation , _maxElevation );

		// 删除缓冲区
		delete buf_float;
		delete buf_byte;

		return ret;
	}
	//----------------------------------------------------------------
	void GeoDem::updateGlobalInfo()
	{
		assert( _gdalDataSet == NULL );
		//assert( _overview != NULL );
		//assert( _overview->isEmpty() == true );
		assert( _globalData != NULL );

		if ( _globalData->isValid() == false )
		{
			assert( _hasReadMinAndMaxElevation == false );
		}
		else
		{
			assert( _hasReadMinAndMaxElevation == true );
		}

		//------------------------------------------
		// 更新wordRect
		//------------------------------------------
		long tmpleftupX = abs( 
			( _globalData->_globalUpperLeftX - _upperLeftX ) / _globalData->_globalPixelSizeX );

		long tmpleftupY = abs( 
			( _globalData->_globalUpperLeftY - _upperLeftY ) / _globalData->_globalPixelSizeY );

		_worldRect = _rawRect.translateCopy( 
			vgKernel::ImagePos( tmpleftupX , tmpleftupY ) );

		/**
			生成overview
		*/
		long overview_width = _sizeX / VGT_OVERVIEW_DIVIDE;
		long overview_height = _sizeY / VGT_OVERVIEW_DIVIDE;

		if ( _overview != NULL )
		{
			_overview->setRect( 
				vgKernel::ImageRect( _worldRect.minPos.x / VGT_OVERVIEW_DIVIDE , 
				_worldRect.minPos.y / VGT_OVERVIEW_DIVIDE , 
				overview_width , overview_height ));
		}

		assert( _gdalDataSet == NULL );
		return;
	}
	//----------------------------------------------------------------
	bool GeoDem::getStatistics(  GDALRasterBand* poBand , 
		double *pdfMin, double *pdfMax )
	{
		long sizeX = poBand->GetXSize();
		long sizeY = poBand->GetYSize();
		assert( sizeX > 0 );
		assert( sizeY > 0 );
	
		float noDataVal = poBand->GetNoDataValue();

		float* buf_float = new float[ sizeX * sizeY ];

		CPLErr rasterok = poBand->RasterIO(GF_Read, 
			0, 0, sizeX, sizeY, 
			buf_float, sizeX, sizeY ,
			GDT_Float32, 0, 0 );

		if ( rasterok != CE_None )
		{
			delete buf_float;
			return false;
		}

		bool firstValue = true;
		double tmpMaxElev = 0.0;
		double tmpMinElev = 0.0;

		for ( int i = 0 ; i < sizeY * sizeX ; ++ i )
		{
			buf_float[i] = buf_float[i] * _zScale + _zOffset;

			if( buf_float[i] == noDataVal )
			{
				continue;
			}

			if ( firstValue == true )
			{
				firstValue = false;
				tmpMinElev = buf_float[i];
				tmpMaxElev = buf_float[i];
			}

			tmpMaxElev = VGT_MAX( tmpMaxElev , buf_float[i] );
			tmpMinElev = VGT_MIN( tmpMinElev , buf_float[i] );
		}

		*pdfMin = tmpMinElev;
		*pdfMax = tmpMaxElev;

		delete buf_float;



		return true;
	}
	//----------------------------------------------------------------
	fileBlock* GeoDem::saveToImage()
	{
		//------------------------------------------
		// 注意!!这里应该被updateGlobalInfo了.
		//------------------------------------------
		assert( _hasReadMinAndMaxElevation == true );

		assert( _gdalDataSet == NULL );

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


		//////////////////////////////////////////////////////////////////////////
		assert( _gdalDataSet != NULL );

		assert(_worldRect.getCenter().x != 0 );

		GDALRasterBand* band = _gdalDataSet->GetRasterBand(1);
		assert( band != NULL );
		assert( _sizeX != 0 );

		float* buf_float = new float[ _sizeX * _sizeY ];

		using namespace vgThreads;

		static CriticalSection gdalCriticalSect;

		gdalCriticalSect.enter();

		CPLErr rasterok = band->RasterIO(GF_Read, 
			0, 0, _sizeX, _sizeY, 
			buf_float, _sizeX, _sizeY ,
			GDT_Float32, 0, 0 );

		gdalCriticalSect.leave();

		if ( rasterok != CE_None )
		{
			delete buf_float;
			return NULL;
		}

		//------------------------------------------
		// 注意，提前释放GDAL!!!!!
		//------------------------------------------
		guide.setNull();

		//------------------------------------------
		// 注意,这里应该取GlobalData的信息
		//------------------------------------------
		float delta_elevation = 
			_globalData->_globalMaxElevation - _globalData->_globalMinElevation;

		assert( delta_elevation > 0.0f );

		for ( int i = 0 ; i < _sizeX * _sizeY ; ++ i )
		{
			float curvalue = buf_float[i];


			if ( vgKernel::Math::floatEqual( curvalue , 
				_noDataValue , 1e-3 ) )
			{
				curvalue = _globalData->_globalMinElevation;
			}
			else
			{
				curvalue = curvalue * _zScale + _zOffset;
			}

			// 到maxElevation与minElevation之间.
			curvalue -= _globalData->_globalMinElevation;

			// 到0.0与1.0之间.
			curvalue /= delta_elevation;

			buf_float[i] = curvalue;
		}

		//------------------------------------------
		// 设置需要保存图片的路径.
		//------------------------------------------
		String metafilename = 
			vgKernel::StringUtility::getFilenameFromAbsolutePath( _filePath );

		String prefix = vgKernel::StringUtility::getFilenameWithoutExtension( metafilename );

		assert( _globalData->_demDirectory.empty() == false );

		String imgname = _globalData->_demDirectory + "\\" + prefix + "." + 
			VGT_GEOMGR_TEMP_EXT;

		bool fileexist = vgKernel::SystemUtility::checkFileExist( imgname );

		// 如果文件存在,换一个名称
		if ( fileexist == true )
		{
			prefix = vgKernel::UniqueIDFactory::getUniqueID().getString();
			imgname = _globalData->_demDirectory + "\\" + prefix + "." + 
				VGT_GEOMGR_TEMP_EXT;

			assert( vgKernel::SystemUtility::checkFileExist( imgname) == false );
		}

		// 赋值.
		_imagePath = imgname;

		//------------------------------------------
		// 利用cximage创建文件,保存读出来的高度信息
		//------------------------------------------
#if 0
		CximageWrapperPtr cximage( new CximageWrapper );

#if 1	
		bool createok = cximage->cxCreateFromArray( (BYTE*)buf_float, _sizeX , _sizeY , 
			32 , _sizeX * 4 , true );
#else

		bool createok = cximage->cxCreateFromArray( (BYTE*)(buf_float + _sizeX ) , _sizeX , _sizeY -1 , 
			32 , _sizeX * 4 , true );

#endif
		assert( createok == true );

		bool saveok = cximage->saveToFile( _imagePath );
		assert( saveok == true );

		if ( saveok == false )
		{
			return NULL;
		}
#else

		//vgKernel::StreamWriterPtr pw = 
		//	vgKernel::StreamWriterFactory::createFromFile( _imagePath );

		//ImageRGBA rbga( (char*)buf_float , _sizeX , _sizeY , true , true );
		//bool ok = rbga.writeToBmpStream( pw );
		//if ( ok == false )
		//{
		//	return NULL;
		//}

		//assert( ok == true );

		vgImage::FreeImageWrapper freeimg;
		bool createok = 
			freeimg.createFromArray( buf_float , _sizeX , _sizeY, 32 , true );

		delete buf_float;

		if ( createok == false )
		{
			return NULL;
		}

		gdalCriticalSect.enter();
		bool saveok = freeimg.saveToFile( _imagePath );

		if ( saveok == false )
		{
			int counter = 0;
			while ( counter < 100 && saveok == false )
			{
				saveok = freeimg.saveToFile( _imagePath );
				counter ++;
				Sleep(100);
			}

			if ( saveok == false )
			{
				assert( 0&& "loadok == true" );
				gdalCriticalSect.leave();
				return NULL;
			}
		}

		gdalCriticalSect.leave();

#endif

		fileBlock* ret = new fileBlock;

		ret->fileSrcName = _imagePath;

#if 1
		ret->fileAbsoluteRect = _worldRect;
#else
		ImageRect tmprect = _worldRect;
		tmprect.minPos.y += 1;
		ret->fileAbsoluteRect = tmprect;
#endif
		// 删除缓冲区
		//delete buf_float;

		return ret;
	}
	//----------------------------------------------------------------
	fileBlock* GeoDem::saveToDebugImage()
	{
		//------------------------------------------
		// 注意!!这里应该被updateGlobalInfo了.
		//------------------------------------------
		assert( _gdalDataSet == NULL );

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


		assert(_worldRect.getCenter().x != 0 );

		GDALRasterBand* band = _gdalDataSet->GetRasterBand(1);
		assert( band != NULL );
		assert( _sizeX != 0 );

		float* buf_float = new float[ _sizeX * _sizeY ];

		CPLErr rasterok = band->RasterIO(GF_Read, 
			0, 0, _sizeX, _sizeY, 
			buf_float, _sizeX, _sizeY ,
			GDT_Float32, 0, 0 );

		if ( rasterok != CE_None )
		{
			delete buf_float;
			return NULL;
		}

		byte* buf_byte = new byte[ _sizeX * _sizeY * 4 ];

		//------------------------------------------
		// 注意,这里应该取GlobalData的信息
		//------------------------------------------
		float delta_elevation = 
			_globalData->_globalMaxElevation - _globalData->_globalMinElevation;

		assert( delta_elevation > 0.0f );

		for ( int i = 0 ; i < _sizeX * _sizeY ; ++ i )
		{
			double curvalue = buf_float[i];
			curvalue = curvalue * _zScale + _zOffset;

			// 到maxElevation与minElevation之间.
			curvalue -= _globalData->_globalMinElevation;

			// 到0.0与1.0之间.
			curvalue /= delta_elevation;

			curvalue *= 10.0;

			uchar r = 0;
			uchar g = 0;
			uchar b = 0;

			if ( curvalue < 1.0 )
			{
				r = (curvalue) * 255;
			}
			else if( curvalue < 2.0 )
			{
				g = (curvalue - 1.0) * 255;
			}
			else if( curvalue < 3.0 )
			{
				b = (curvalue - 2.0) * 255;
			}
			else if( curvalue < 4.0 )
			{
				r = (curvalue - 3.0) * 255;
				g = 255;
			}
			else if( curvalue < 5.0 )
			{
				g = (curvalue - 4.0) * 255;
				b = 255;
			}
			else if( curvalue < 6.0 )
			{
				b = (curvalue - 5.0) * 255;
				g = 128;
			}
			else if( curvalue < 7.0 )
			{
				r = (curvalue - 6.0) * 255;
				g = 64;
			}
			else if( curvalue < 8.0 )
			{
				g = (curvalue - 7.0) * 255;
				b = 128;
			}
			else if( curvalue < 9.0 )
			{
				b = (curvalue - 8.0) * 255;
				r = 64;
			}
			else
			{
				r = (curvalue - 9.0) * 255;
				g = 128;
				b = 64;
			}



			buf_byte[ i * 4 ] =   r;		// R
			buf_byte[ i * 4 + 1 ] =  g;// G
			buf_byte[ i * 4 + 2  ] =   b;		// B
			buf_byte[ i * 4 + 3  ] =   255;		// A
		}

		//------------------------------------------
		// 设置需要保存图片的路径.
		//------------------------------------------
		String metafilename = 
			vgKernel::StringUtility::getFilenameFromAbsolutePath( _filePath );

		String prefix = vgKernel::StringUtility::getFilenameWithoutExtension( metafilename );

		assert( _globalData->_debugImageDirectory.empty() == false );

		String imgname = _globalData->_debugImageDirectory + "\\" + prefix + "_debug." + VGT_GEOMGR_TEMP_EXT;

		bool fileexist = vgKernel::SystemUtility::checkFileExist( imgname );

		// 如果文件存在,换一个名称
		if ( fileexist == true )
		{
			prefix = vgKernel::UniqueIDFactory::getUniqueID().getString();
			imgname = _globalData->_debugImageDirectory + "\\" + prefix + "_debug." + VGT_GEOMGR_TEMP_EXT;

			assert( vgKernel::SystemUtility::checkFileExist( imgname) == false );
		}

		// 赋值.
		_debugImgPath = imgname;

		//------------------------------------------
		// 利用cximage创建文件,保存读出来的高度信息
		//------------------------------------------
		CximageWrapperPtr cximage( new CximageWrapper );

		bool createok = cximage->cxCreateFromArray( (BYTE*)buf_byte, _sizeX , _sizeY , 
			32 , _sizeX * 4 , true );

		assert( createok == true );
		bool saveok = cximage->saveToFile( _debugImgPath );
		assert( saveok == true );

		if ( saveok == false )
		{
			return NULL;
		}

		fileBlock* ret = new fileBlock;

		ret->fileSrcName = _debugImgPath;
		ret->fileAbsoluteRect = _worldRect;

		// 删除缓冲区
		delete buf_float;
		delete buf_byte;

		return ret;
	}
	//----------------------------------------------------------------
	void GeoDem::getGDALDataSet()
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
	//-----------------------------------------------------------------------------------
	bool GeoDem::readMinAndMaxElevation()
	{
		if ( _hasReadMinAndMaxElevation == true )
		{
			return true;
		}

		assert( _gdalDataSet != NULL );

		double min;
		double max;

		/**
			注意!!!更新 Statistics之后需要重置一下band!!
		*/
		bool statistics = getStatistics( _gdalDataSet->GetRasterBand(1) ,
			&min , &max );

		if ( statistics == false )
		{ 
			return false;
		}

		assert( min != _noDataValue );
		assert( max != _noDataValue );

		_maxElevation = max * _zScale + _zOffset;
		_minElevation = min * _zScale + _zOffset;

		
		_hasReadMinAndMaxElevation = true;

		return true;
	}

	bool GeoDem::readOverview()
	{
		if ( _hasReadOverview == true )
		{
			return true;
		}

		assert( _gdalDataSet != NULL );


		//------------------------------------------
		// 得到overview
		//------------------------------------------
		_overview = generateOverview();

		if ( _overview == NULL )
		{
			return false;
		}

		_hasReadOverview = true;

		return true;
	}
	//  [10/8/2008 Administrator]
	bool GeoDem::readGlobalInfo(const bool& unload_gdal_dataset )
	{
		if ( _hasReadMinAndMaxElevation == true )
		{
			return true;
		}

		assert( _filePath.empty() == false );
		assert( _gdalDataSet == NULL ); 

		getGDALDataSet();

		if ( _gdalDataSet == NULL )
		{
			return false;
		}

		bool readok = readMinAndMaxElevation();

		assert( readok == true );
		if ( readok == false )
		{
			delete _gdalDataSet;
			_gdalDataSet = NULL;
			return false;
		}

		if ( unload_gdal_dataset == true )
		{
			delete _gdalDataSet;
			_gdalDataSet = NULL;
		}

		return true;
	}
	//----------------------------------------------------------------


	//----------------------------------------------------------------
	void GeoDemSaveImgJob::doJob()
	{
		long count = _boss->getCounter()->getCount();
		_notifier->setCurrentProcessPos( _dem->getFilePath() ,  count );

		fileBlock* block = _dem->saveToImage();

		if ( block != NULL )
		{
			ScopedLock locker( *_sect );

			_fileBlockVec->push_back( *block );

			delete block;
		}
	}
	//----------------------------------------------------------------


}// end of namespace vgTerritory
