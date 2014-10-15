


#include <vgStableHeaders.h>
#include "vgBackgroundEntry.h"
#include <vgVisualEffects/vgviBackgroundManager.h>




vgBackgroundEntry::vgBackgroundEntry() :
vgBaseEntryEx( VG_ENTRY_BACKGROUND , NULL )
{
	using namespace vgVisualEffects;

	BackgroundManager::getSingleton().registerObs( this );
}
vgBackgroundEntry::~vgBackgroundEntry(void)
{

}


void vgBackgroundEntry::updateUIFromInternal()
{
	using namespace vgVisualEffects;

	_colorRef = BackgroundManager::getSingleton().getCurrentBackgroundColor().getAsColorRef();
}

void vgBackgroundEntry::updateInternalFromUI(const String& changed_param_name )
{
	using namespace vgVisualEffects;
	vgVisualEffects::ColorValu colorval;
	colorval.setAsColorRef( _colorRef );
	BackgroundManager::getSingleton().setCurrentBackgroundColor( colorval );
}

void vgBackgroundEntry::onUpdate()
{
	updateUIFromInternal();
}

PropertiesParamVector& vgBackgroundEntry::pushPropertiesParam( 
	PropertiesParamVector& params )
{
	PropertiesParam param;

#if VGK_LANG_CHS
	param.label = "基本属性";
	param.typeId = PROP_ITEM_GROUP;
	param.dataType = PROP_DATA_NONE;
	param.connectedPtr = NULL;
	param.comment = String();
	params.push_back( param );


	param.label = "背景颜色";
	param.typeId = PROP_ITEM_DATA;
	param.dataType = PROP_DATA_COLOR;
	param.connectedPtr = &_colorRef;
	param.comment = "设置背景颜色";
	params.push_back( param );
#else
	param.label = "Basic Prop";
	param.typeId = PROP_ITEM_GROUP;
	param.dataType = PROP_DATA_NONE;
	param.connectedPtr = NULL;
	param.comment = String();
	params.push_back( param );


	param.label = "Background Color";
	param.typeId = PROP_ITEM_DATA;
	param.dataType = PROP_DATA_COLOR;
	param.connectedPtr = &_colorRef;
	param.comment = "";
	params.push_back( param );
#endif

	return params;
}
