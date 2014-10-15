





#include <vgStableHeaders.h>
#include <vgShape/vgshDrawingDescriptor.h>
#include <vgShape/vgshDefinition.h>

#include <vgShape/vgshGeometry.h>
#include <gdal/ogrsf_frmts.h>
#include <gdal/ogr_api.h>



namespace vgShape {
	
	
	//----------------------------------------------------------------
	DrawingDescriptor::DrawingDescriptor( Geometry* father )
	{
		_penWidth = 2.0;
		_drawFilling = true;

		_penColor = RGB( 0 , 255 , 0 );
		_fillColor = RGB( 0 , 51 , 51 );

		_styleMgr = new OGRStyleMgr;

		_father = father;
	}
	//----------------------------------------------------------------
	DrawingDescriptor::~DrawingDescriptor()
	{
		if ( _styleMgr == NULL )
		{
			delete _styleMgr;
			_styleMgr = NULL;
		}
	}
	//----------------------------------------------------------------
	bool DrawingDescriptor::importFromOGRFeature( OGRFeature* feature )
	{
		const char* stylestr = 
			feature->GetFieldAsString( VG_SHAPE_STYLE_FIELD );

		if ( stylestr == NULL )
		{
			return false;
		}

		return importFromString( String( stylestr ) );
	}
	//----------------------------------------------------------------
	bool DrawingDescriptor::importFromString( const String& str )
	{
		if ( str.empty() == true )
		{
			return false;
		}

		//------------------------------------------
		// 开始读取style
		//------------------------------------------
		// Reading a style;
		OGRStyleMgr   *poStyleMgr = _styleMgr;

		OGRStyleTool  *poStyleTool;

		GBool initok = poStyleMgr->InitStyleString( str.c_str() );
		assert( initok == TRUE );
		if ( initok == FALSE )
		{
			return false;
		}

		int partcount = poStyleMgr->GetPartCount();

		for ( int i = 0; i < partcount ; i ++ )
		{
			poStyleTool = poStyleMgr->GetPart( i );

			if ( poStyleTool == NULL )
			{
				continue;
			}

			OGRSTClassId type = poStyleTool->GetType();

			if ( type == OGRSTCPen )
			{
				OGRStylePen* poStylePen = (OGRStylePen *)poStyleTool;

				GBool bDefault = TRUE;
				const char *pszColor = poStylePen->Color(bDefault);

				if ( bDefault == FALSE )
				{
					int nCol[4];

					GBool rgbok = poStylePen->GetRGBFromString(
						pszColor, nCol[0], nCol[1], 
						nCol[2], nCol[3]);

					assert( rgbok == TRUE );
					_penColor = RGB( nCol[0] , nCol[1] , nCol[2] );
				}

				double dfWidth = poStylePen->Width(bDefault);
				if (bDefault == FALSE)
				{
					_penWidth = dfWidth;
				}
			}
			else if ( type == OGRSTCBrush )
			{
				OGRStyleBrush* poStyleBrush = (OGRStyleBrush *)poStyleTool;

				GBool bDefault = TRUE;
				const char *pszColor = poStyleBrush->ForeColor(bDefault);

				if ( bDefault == FALSE )
				{
					int nCol[4];

					GBool rgbok = poStyleBrush->GetRGBFromString(
						pszColor, nCol[0], nCol[1], 
						nCol[2], nCol[3]);

					assert( rgbok == TRUE );
					_fillColor = RGB( nCol[0] , nCol[1] , nCol[2] );
				}

				int pri = poStyleBrush->Priority( bDefault );

				if ( bDefault == FALSE )
				{
					_drawFilling = ( pri == 0 ? false : true );
				}
			}
		}

		return true;
	}
	//----------------------------------------------------------------
	vgKernel::ColorVal DrawingDescriptor::getFillingColorVal()
	{
		vgKernel::ColorVal ret;
		ret.setAsColorRef( _fillColor , false );
		return ret;
	}
	//----------------------------------------------------------------
	vgKernel::ColorVal DrawingDescriptor::getPenColorVal()
	{
		vgKernel::ColorVal ret;
		ret.setAsColorRef( _penColor , false );
		return ret;
	}
	//----------------------------------------------------------------
	double DrawingDescriptor::getPenWidth()
	{
		return _penWidth;
	}
	//----------------------------------------------------------------
	bool DrawingDescriptor::isDrawFilling()
	{
		return _drawFilling;
	}
	//----------------------------------------------------------------
	void DrawingDescriptor::updateOGRStyleMgrFromParams()
	{
		OGRStyleMgr   *poStyleMgr = new OGRStyleMgr();

		//------------------------------------------
		// 添加pen
		//------------------------------------------
		OGRStylePen  *poStylePen = new OGRStylePen;

		poStylePen->SetColor( getStringFromColorRef(_penColor).c_str() );
		//poStylePen->SetUnit(OGRSTUPixel);
		poStylePen->SetWidth( _penWidth );
		poStyleMgr->AddPart( poStylePen );

		delete poStylePen;

		//------------------------------------------
		// 添加brush
		//------------------------------------------
		OGRStyleBrush  *poStyleBrush = new OGRStyleBrush;

		poStyleBrush->SetForeColor( getStringFromColorRef( _fillColor ).c_str() );
		int pri = (_drawFilling == true ? 1 : 0 );
		poStyleBrush->SetPriority( pri );

		poStyleMgr->AddPart( poStyleBrush );

		delete poStyleBrush;


		const char* stylestr = poStyleMgr->GetStyleString();

		assert( stylestr != NULL );

		//------------------------------------------
		// 更新style mgr
		//------------------------------------------
		delete _styleMgr;
		_styleMgr = poStyleMgr;

		return;
	}
	//----------------------------------------------------------------
	String DrawingDescriptor::getStringFromColorRef( COLORREF col )
	{
		char szBuffer[16];
		sprintf (szBuffer, ("#%02X%02X%02X"),
			GetRValue(col), GetGValue(col), GetBValue(col));

		return szBuffer;
	}
	//----------------------------------------------------------------
	void DrawingDescriptor::dumpOGRStyleStringToOGRFeature()
	{
		OGRFeaturePtr pfeature = _father->getOGRFeaturePtr();
		assert( pfeature.isNull() == false );

		OGRFeature* feat = pfeature.getPointer();

		const char* stylestr = _styleMgr->GetStyleString();

		feat->SetField( VG_SHAPE_STYLE_FIELD , stylestr );

		_father->setFeature( feat );

		return;
	}
	//----------------------------------------------------------------
	void DrawingDescriptor::setPenWidth( const double& wid )
	{
		_penWidth = wid;
		updateOGRStyleMgrFromParams();
		_father->invalidateRendering();
		dumpOGRStyleStringToOGRFeature();
	}
	//----------------------------------------------------------------
	void DrawingDescriptor::setPenColor( COLORREF col )
	{
		_penColor = col;
		updateOGRStyleMgrFromParams();
		_father->invalidateRendering();
		dumpOGRStyleStringToOGRFeature();
	}
	//----------------------------------------------------------------
	void DrawingDescriptor::setDrawingFill( bool draw )
	{
		_drawFilling = draw;
		updateOGRStyleMgrFromParams();
		_father->invalidateRendering();
		dumpOGRStyleStringToOGRFeature();
	}
	//----------------------------------------------------------------
	void DrawingDescriptor::setFillColor( COLORREF col )
	{
		_fillColor = col;
		updateOGRStyleMgrFromParams();
		_father->invalidateRendering();
		dumpOGRStyleStringToOGRFeature();
	}
	//----------------------------------------------------------------




}// end of namespace vgShape
