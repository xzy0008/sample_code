


#include <vgStableHeaders.h>
#include "vgentry/vgRendererEntry.h"


#include <vgUIController/vgUIController.h>


#if VGK_LANG_CHS
	#define VGSTR_BASIC  "基本属性" 
	#define VGSTR_renderertype   "物体种类代码"
	#define VGSTR_class   "类描述" 
	#define VGSTR_name   "物体名称" 
	#define VGSTR_isrender   "是否渲染"
	#define VGSTR_renderpri   "渲染优先级"
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
#else
	#define VGSTR_BASIC  "Basic Properties" 
	#define VGSTR_renderertype   "Object TypeCode"
	#define VGSTR_class   "Class Desc" 
	#define VGSTR_name   "Name" 
	#define VGSTR_isrender   "Is Rendering"
	#define VGSTR_renderpri   "Rendering Priority"
	#define VGSTR_numtri   "Triangles" 

	#define VGSTR_uniqid   "Unique Id"
	#define VGSTR_opengl   "OpenGL Coord" 
	#define VGSTR_openglx   "OpenGL X" 
	#define VGSTR_opengly  "OpenGL Y" 
	#define VGSTR_openglz "OpenGL Z" 

	#define VGSTR_gis "GIS Coord" 
	#define VGSTR_gisx "GIS X"  
	#define VGSTR_gisy "GIS Y" 
	#define VGSTR_gisz "GIS Z"  

	#define VGSTR_box "Box" 
	#define VGSTR_lenx "Length"  
	#define VGSTR_leny "Width"  
	#define VGSTR_lenz "Height"
#endif



//----------------------------------------------------------------
RendererEntry::RendererEntry( vgKernel::Renderer* renderer )
: vgBaseEntryEx(  renderer )
{
	_visible = true;
	_renderingPriority = 0;

	if ( renderer != NULL )
	{
		_typeidOfRenderer = typeid( *renderer ).name();
		_rendererType = renderer->getType();
		_uniqueIdStr = renderer->getUniqueID().getString();
	}
}
//----------------------------------------------------------------

//----------------------------------------------------------------
PropertiesParamVector& RendererEntry::pushPropertiesParam( 
	PropertiesParamVector& params )
{
	VG_PUSH_PROP_GROUP( params , VGSTR_BASIC );
	VG_PUSH_PROP_CONST_INT( params , VGSTR_renderertype, &_rendererType );
	VG_PUSH_PROP_CONST_STR( params , VGSTR_class , &_typeidOfRenderer );
	VG_PUSH_PROP_STR( params , VGSTR_name , &_rendererName );
	VG_PUSH_PROP_BOOL( params ,VGSTR_isrender , &_visible );
	VG_PUSH_PROP_INT( params , VGSTR_renderpri , &_renderingPriority );
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
	

	return params;
}
//----------------------------------------------------------------
void RendererEntry::updateUIFromInternal()
{
	using namespace vgKernel;

	Renderer* ren = getRender();
	assert( ren != NULL );

	vgKernel::Box box = ren->getBoundingBox();

	vgKernel::Vec3 vec = box.getSize();
	_lenX = ( vec.x );
	_lenY = ( vec.y );
	_lenZ = ( vec.z );
	
	_rendererName = ren->getName();
	_visible = ren->getVisible();
	_renderingPriority = ren->getRenderingPriority();
	_boundingBoxDetails = box.getDetails();
	_numOfTriangles = ren->getNumOfTriangles();

	_openGLPos = ren->getPosition();

	_gisCoordinate = 
		//vgCore::vgCoordinate::getSingleton().transOpenGLCoordToGisCoord( _openGLPos );
		vgKernel::CoordSystem::getSingleton().transCoordOpenGLToProj( _openGLPos );


	return;
}
//----------------------------------------------------------------
void RendererEntry::updateInternalFromUI(const String& changed_param_name )
{
	using namespace vgKernel;

	void* changed_data = getConnectPtrByName( changed_param_name );

	const String& chname = changed_param_name;

	if ( changed_data == NULL )
	{
		return;
	}

	Renderer* ren = getRender();
	assert( ren != NULL );

	vgKernel::Box box = ren->getBoundingBox();

	if ( chname == VGSTR_name)
	{
		ren->setName( _rendererName );
	}
	else if ( chname == VGSTR_isrender )
	{
		ren->setVisible( _visible );
	}
	else if ( chname == VGSTR_renderpri )
	{
		ren->setRenderingPriority( _renderingPriority );
	}
	else if ( chname == VGSTR_openglx ||
		chname == VGSTR_opengly ||
		chname == VGSTR_openglz )
	{
		ren->moveTo( _openGLPos );
	}
	else if ( chname == VGSTR_gisx ||
		chname == VGSTR_gisy ||
		chname == VGSTR_gisz  )
	{
		vgKernel::Vec3 newpos = 
			//vgCore::vgCoordinate::getSingleton().transGisCoordToOpenGLCoord( 
			//_gisCoordinate );
			vgKernel::CoordSystem::getSingleton().transCoordProjToOpenGL( _openGLPos );

		ren->moveTo( newpos );
		_openGLPos = newpos;
	}
	else if ( chname == VGSTR_lenx ||
		chname == VGSTR_leny ||
		chname == VGSTR_lenz  )
	{
		const float& tor = vgKernel::Math::ZERO_TOLERANCE;

		if ( _lenX < 0.0f || _lenY < 0.0f || _lenZ < 0.0f )
		{
			MessageBox( NULL , "参数输入错误" , "提示" , MB_OK );
			return;
		}

		vgKernel::Vec3 center = box.getCenter();
		vgKernel::Vec3 vec = box.getSize();

		vec.x = vec.x <= tor? 1.0f : vec.x ;
		vec.y = vec.y <= tor? 1.0f : vec.y ;
		vec.z = vec.z <= tor? 1.0f : vec.z ;

		float scalex = _lenX <= tor ? 1.0f : _lenX / vec.x;
		float scaley = _lenY <= tor ? 1.0f : _lenY / vec.y;
		float scalez = _lenZ <= tor ? 1.0f : _lenZ / vec.z;

		ren->scale( center.x , center.y , center.z , scalex , scaley, scalez );
	}
	 
	return;
}
//----------------------------------------------------------------
void RendererEntry::onChanged( int eventId, void *param )
{
	if (eventId == vgKernel::VG_OBS_PROPCHANGED)
	{
		updateUIFromInternal();
#if 1
		EntryUtility::invalidatePropValues( getPropertiesParamVector() );
#endif
	}
	else if (eventId == vgKernel::VG_OBS_SELECTCHAGNED)
	{
		vgUI::UIController::getSingleton().SelectNode(this);
	}
	else if (eventId == vgKernel::VG_OBS_ADDSELECTION)
	{
		vgUI::UIController::getSingleton().AddSelection(this);
	}
	else if ( eventId == vgKernel::VG_OBS_INVALIDATE_PROPERTIES )
	{
		AddNodeTabs();
	}

	return;
}
//----------------------------------------------------------------
