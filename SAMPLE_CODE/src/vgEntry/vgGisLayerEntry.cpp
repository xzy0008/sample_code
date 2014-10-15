


#include <vgStableHeaders.h>
#include "vgentry/vgGisLayerEntry.h"

#include "gdal/ogrsf_frmts.h"
#include "gdal/ogr_api.h"



//----------------------------------------------------------------
PropertiesParamVector& GisLayerEntry::pushPropertiesParam( 
	PropertiesParamVector& params )
{
	using namespace vgGIS3D;

	// RendererEntry::pushPropertiesParam( params );

#define VGSTR_BASIC  "基本属性" 
#define VGSTR_renderertype   "物体种类代码"
#define VGSTR_class   "类描述" 
#define VGSTR_name   "物体名称" 
#define VGSTR_isrender   "是否渲染"
#define VGSTR_depth		"开启深度测试"
	// #define VGSTR_renderpri   "渲染优先级"
#define VGSTR_numtri   "物体三角面数" 

#define VGSTR_uniqid   "Unique Id"
#define VGSTR_opengl   "OpenGL坐标" 
#define VGSTR_openglx   "OpenGL X坐标" 
#define VGSTR_opengly  "OpenGL Y坐标" 
#define VGSTR_openglz "OpenGL Z坐标" 

#define VGSTR_gis "GIS坐标" 
#define VGSTR_gisx "GIS X坐标"  
#define VGSTR_gisy "GIS Y坐标" 
#define VGSTR_gisz "GIS Z坐标"  

#define VGSTR_box "包围盒信息" 
#define VGSTR_lenx "长"  
#define VGSTR_leny "宽"  
#define VGSTR_lenz "高"

	VG_PUSH_PROP_GROUP( params , VGSTR_BASIC );
	VG_PUSH_PROP_CONST_INT( params , VGSTR_renderertype, &_rendererType );
	VG_PUSH_PROP_CONST_STR( params , VGSTR_class , &_typeidOfRenderer );
	VG_PUSH_PROP_STR( params , VGSTR_name , &_rendererName );
	VG_PUSH_PROP_BOOL( params ,VGSTR_isrender , &_visible );
	VG_PUSH_PROP_BOOL( params ,VGSTR_depth , &_enableDepth );

	// VG_PUSH_PROP_INT( params , VGSTR_renderpri , &_renderingPriority );
	VG_PUSH_PROP_CONST_INT( params , VGSTR_numtri , &_numOfTriangles );

	VG_PUSH_PROP_CONST_STR( params , VGSTR_uniqid, &_uniqueIdStr );

	VG_PUSH_PROP_GROUP( params ,VGSTR_opengl );
	VG_PUSH_PROP_FLOAT( params , VGSTR_openglx , &_openGLPos.x );
	VG_PUSH_PROP_FLOAT( params , VGSTR_opengly , &_openGLPos.y );
	VG_PUSH_PROP_FLOAT( params ,VGSTR_openglz , &_openGLPos.z );

	VG_PUSH_PROP_GROUP( params , VGSTR_gis );
	VG_PUSH_PROP_FLOAT( params , VGSTR_gisx , &_gisCoordinate.x );
	VG_PUSH_PROP_FLOAT( params , VGSTR_gisy, &_gisCoordinate.y );
	VG_PUSH_PROP_FLOAT( params , VGSTR_gisz , &_gisCoordinate.z );

	VG_PUSH_PROP_GROUP( params , VGSTR_box );
	VG_PUSH_PROP_FLOAT( params , VGSTR_lenx, &_lenX );
	VG_PUSH_PROP_FLOAT( params , VGSTR_leny , &_lenY );
	VG_PUSH_PROP_FLOAT( params , VGSTR_lenz , &_lenZ );

#if 1
	pushPropertiesEx( params );
#endif
	//VG_CHANGE_PROP_LABEL( params , "物体三角面数" , "物体点数" );

	//------------------------------------------
	// 注意,显示自动列表的时候不要用StringVector
	// 因为每当push_back时, c_str()或者直接取址
	// 会造成之前的指针变动
	// 所以还是用StringPointerVec比较好.
	//------------------------------------------

	using namespace vgKernel;
	
	//----------------------------------------------------------------
	typedef std::vector<void*> VoidPtrVec;

	static VoidPtrVec vptrvec;
	vptrvec.clear();
	{
		VoidPtrVec::iterator iter = vptrvec.begin();
		VoidPtrVec::iterator iter_end = vptrvec.end();

		for ( ; iter != iter_end ; ++ iter )
		{
			delete *iter;
		}
	}
	//----------------------------------------------------------------

	typedef std::vector<String*> StringPointerVec;

	//------------------------------------------
	// 暂时使用static变量 
	//------------------------------------------
	static StringPointerVec spv;

	StringPointerVec::iterator iter = spv.begin();
	StringPointerVec::iterator iter_end = spv.end();

	for ( ; iter != iter_end ; ++ iter )
	{
		delete *iter;
	}
	spv.clear();

#if 1

	GeometryPointerVec* geos = _layer->getSelectedGeometry();

	assert( geos != NULL );

	//------------------------------------------
	// 没有选中物体,直接返回
	//------------------------------------------
	if ( geos->empty() )
	{
		return params;
	}

	Geometry* geo = (*geos)[0];
	assert( geo != NULL );

	//------------------------------------------
	// 开始显示style
	//------------------------------------------
	VG_PUSH_PROP_GROUP( params , "Style" );
	

	VG_PUSH_PROP_DOUBLE( params ,VGSH_LAYER_ENTRY_PENWIDTH , & _penwidth );
	VG_PUSH_PROP_COLOR( params , VGSH_LAYER_ENTRY_PENCOL , &_pencolor );
	VG_PUSH_PROP_BOOL( params , VGSH_LAYER_ENTRY_DRAWFILL , &_drawFill );
	VG_PUSH_PROP_COLOR( params , VGSH_LAYER_ENTRY_FILLCOL , &_fillcolor );

	//------------------------------------------
	// 只对一个物体显示field属性
	//------------------------------------------
// 	if ( geos->size() != 1 )
// 	{
// 		return params;
// 	}

	//------------------------------------------
	// 开始对field进行列表显示
	//------------------------------------------
	VG_PUSH_PROP_GROUP( params , "ShapeLayer field" );

	OGRFeaturePtr pfeature = geo->getOGRFeaturePtr();
	assert( pfeature.isNull() ==false );

	OGRFeature* poFeature = pfeature.getPointer();

	OGRFeatureDefn *poFDefn = poFeature->GetDefnRef();

	assert( poFDefn != NULL );
	int fieldcount = poFDefn->GetFieldCount();

	for ( int i = 0 ; i < fieldcount ; ++ i )
	{
		OGRFieldDefn* fielddefn = poFDefn->GetFieldDefn( i );
		assert( fielddefn != NULL );

		OGRFieldType fieldtype = fielddefn->GetType();

		String fielddesc = fielddefn->GetNameRef();

		if ( fieldtype == OFTInteger )
		{
			int* ptr = new int;
			*ptr = poFeature->GetFieldAsInteger( i );
			vptrvec.push_back( ptr );
			//assert( vptrvec.size() == i + 1 );
			VG_PUSH_PROP_INT( params , fielddesc , vptrvec[i] );
		}
		else if ( fieldtype == OFTReal )
		{
			double* ptr = new double;
			*ptr = poFeature->GetFieldAsDouble( i );
			vptrvec.push_back( ptr );
			//assert( vptrvec.size() == i + 1 );
			VG_PUSH_PROP_DOUBLE( params , fielddesc , vptrvec[i] );
		}
		else /*if ( fieldtype == OFTString )*/
		{
			String* ptr = new String;
			*ptr = poFeature->GetFieldAsString( i );
			vptrvec.push_back( ptr );
			//assert( vptrvec.size() == i + 1 );
			VG_PUSH_PROP_STR( params , fielddesc , vptrvec[i] );
		}
		/*else
		{
			String typestr = OGRFieldDefn::GetFieldTypeName( fieldtype );
			MessageBox( NULL , ( typestr + "Not supported").c_str() , "Tips" , MB_OK );
		}*/
	}

#endif

	return params;
}
//----------------------------------------------------------------
void GisLayerEntry::updateUIFromInternal()
{
	RendererEntry::updateUIFromInternal();

	using namespace vgGIS3D;

	_geometriesNum = _layer->getGeometries()->size();
	_selectedGeoNum = _layer->getSelectedGeometry()->size();
	_enableDepth = _layer->getDepthEnable();

 	GeometryPointerVec* selected = _layer->getSelectedGeometry();
 
 	if ( selected->empty() == false )
 	{
 		Geometry* geo = (*selected)[0];
		DrawingDescriptor* desc = geo->getDrawingDescriptor();
 
 		_penwidth = desc->getPenWidth();
		_pencolor = desc->getPenColorRef();
		_fillcolor = desc->getFillColorRef();
		_drawFill = desc->isDrawFilling();
 	}

	return;
}
//----------------------------------------------------------------
void GisLayerEntry::updateInternalFromUI( const String& changed_param_name )
{
	RendererEntry::updateInternalFromUI( changed_param_name );
	
	void* changed_data = getConnectPtrByName( changed_param_name );

	const String& chname = changed_param_name;

	if ( chname == VGSTR_depth )
	{
		_layer->setDepthEnable( _enableDepth );
	}
#if 1
	updateInternalEx();
#endif

	const String& cname = changed_param_name;

	using namespace vgGIS3D;

	PropertiesParamVector& params = getPropertiesParamVector();

	GeometryPointerVec* geos = _layer->getSelectedGeometry();

	assert( geos != NULL );

	for ( int i = 0 ; i < geos->size() ; ++ i )
	{
		Geometry* geo = (*geos)[i];
		assert( geo != NULL );

		//------------------------------------------
		// 更新style
		//------------------------------------------
		if ( cname == VGSH_LAYER_ENTRY_PENWIDTH )
		{
			geo->getDrawingDescriptor()->setPenWidth( _penwidth );
		}
		else if ( cname == VGSH_LAYER_ENTRY_PENCOL )
		{
			geo->getDrawingDescriptor()->setPenColor( _pencolor );
		}
		else if ( cname == VGSH_LAYER_ENTRY_DRAWFILL )
		{
			geo->getDrawingDescriptor()->setDrawingFill( _drawFill );
		}
		else if ( cname == VGSH_LAYER_ENTRY_FILLCOL )
		{
			geo->getDrawingDescriptor()->setFillColor( _fillcolor );
		}


		OGRFeaturePtr pfeature = geo->getOGRFeaturePtr();
		assert( pfeature.isNull() ==false );

		if ( pfeature.isNull() == true )
		{
			continue;
		}

		OGRFeature* poFeature = pfeature.getPointer();

		OGRFeatureDefn *poFDefn = poFeature->GetDefnRef();

		assert( poFDefn != NULL );
		int fieldcount = poFDefn->GetFieldCount();

		for ( int i = 0 ; i < fieldcount ; ++ i )
		{
			OGRFieldDefn* fielddefn = poFDefn->GetFieldDefn( i );
			assert( fielddefn != NULL );

			OGRFieldType fieldtype = fielddefn->GetType();

			String fielddesc = fielddefn->GetNameRef();

			if ( cname == fielddesc )
			{
				//------------------------------------------
				// 开始set field
				//------------------------------------------
				if ( fieldtype == OFTInteger )
				{
					int val = *EntryUtility::getPtrFromProperties<int>( params , cname );
					poFeature->SetField( i, val );
					_layer->setOGRFeature( poFeature );
				}
				else if ( fieldtype == OFTReal )
				{
					double val = *EntryUtility::getPtrFromProperties<double>( params , cname );
					poFeature->SetField( i, val );
					_layer->setOGRFeature( poFeature );
				}
				else if ( fieldtype == OFTString )
				{
					String val = *EntryUtility::getPtrFromProperties<String>( params , cname );
					poFeature->SetField( i, val.c_str() );
					_layer->setOGRFeature( poFeature );
				}
				else
				{
					assert(0);
				}
			}

		}
	}

}
//----------------------------------------------------------------
void GisLayerEntry::onChanged( int eventId, void *param )
{
	RendererEntry::onChanged( eventId , param );

}
//----------------------------------------------------------------