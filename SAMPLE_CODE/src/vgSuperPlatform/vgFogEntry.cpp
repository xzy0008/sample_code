


#include <vgStableHeaders.h>
#include <vgVisualEffects/vgviFogManager.h>
#include "vgFogEntry.h"


vgFogEntry::vgFogEntry() :
vgBaseEntryEx( VG_ENTRY_FOG , NULL )
{
	using namespace vgVisualEffects;

	FogManager::getSingleton().registerObs( this );

}
vgFogEntry::~vgFogEntry(void)
{

}


void vgFogEntry::updateUIFromInternal()
{
	using namespace vgVisualEffects;

	_turnedOn = FogManager::getSingleton().getEnabledFlag();

	vgVisualEffects::ColorValu color;
	FogManager::FogMode mod;

	FogManager::getSingleton().getFogParams(
		_fogStart , _fogEnd , _fogDensity , mod , color );

	_fogColorRef = color.getAsColorRef();

	_fogMod = getDescriptionFromFogMode( mod );
}

void vgFogEntry::updateInternalFromUI(const String& changed_param_name )
{
	using namespace vgVisualEffects;

	FogManager::FogMode mod = getFogModeFromDescription( _fogMod );

	vgVisualEffects::ColorValu color;
	color.setAsColorRef( _fogColorRef );

	FogManager::getSingleton().setFogParams( 
		_fogStart , _fogEnd , _fogDensity , mod , color );

	FogManager::getSingleton().setEnabledFlag( _turnedOn );

}

void vgFogEntry::onUpdate()
{
	updateUIFromInternal();
}

PropertiesParamVector& vgFogEntry::pushPropertiesParam( 
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

	param.label = "开启雾效";
	param.typeId = PROP_ITEM_DATA;
	param.dataType = PROP_DATA_BOOL;
	param.connectedPtr = &_turnedOn;
	param.comment = "是否开启雾效";
	params.push_back(param);

	param.label = "雾颜色";
	param.typeId = PROP_ITEM_DATA;
	param.dataType = PROP_DATA_COLOR;
	param.connectedPtr = &_fogColorRef;
	param.comment = "设置雾颜色";
	params.push_back( param );

	param.label = "雾起始处";
	param.typeId = PROP_ITEM_DATA;
	param.dataType = PROP_DATA_FLOAT;
	param.connectedPtr = &_fogStart;
	param.comment = "雾起始处";
	params.push_back( param );

	param.label = "雾结束处";
	param.typeId = PROP_ITEM_DATA;
	param.dataType = PROP_DATA_FLOAT;
	param.connectedPtr = &_fogEnd;
	param.comment = "雾结束处";
	params.push_back( param );
#else
	param.label = "Basic Props";
	param.typeId = PROP_ITEM_GROUP;
	param.dataType = PROP_DATA_NONE;
	param.connectedPtr = NULL;
	param.comment = String();
	params.push_back( param );

	param.label = "Turn on";
	param.typeId = PROP_ITEM_DATA;
	param.dataType = PROP_DATA_BOOL;
	param.connectedPtr = &_turnedOn;
	param.comment = "";
	params.push_back(param);

	param.label = "Color";
	param.typeId = PROP_ITEM_DATA;
	param.dataType = PROP_DATA_COLOR;
	param.connectedPtr = &_fogColorRef;
	param.comment = "";
	params.push_back( param );

	param.label = "Begin";
	param.typeId = PROP_ITEM_DATA;
	param.dataType = PROP_DATA_FLOAT;
	param.connectedPtr = &_fogStart;
	param.comment = "";
	params.push_back( param );

	param.label = "End";
	param.typeId = PROP_ITEM_DATA;
	param.dataType = PROP_DATA_FLOAT;
	param.connectedPtr = &_fogEnd;
	param.comment = "";
	params.push_back( param );
#endif


	return params;
}

String vgFogEntry::getDescriptionFromFogMode( const vgVisualEffects::FogManager::FogMode& mode )
{
	using namespace vgVisualEffects;
	switch( mode )
	{
#if VGK_LANG_CHS
	case FogManager::FOG_MOD_LINEAR:
		return "线性";
	case FogManager::FOG_MOD_EXP:
		return "指数";
	case FogManager::FOG_MOD_EXP2:
		return "指数平方";
#else
	case FogManager::FOG_MOD_LINEAR:
		return "Linear";
	case FogManager::FOG_MOD_EXP:
		return "exp";
	case FogManager::FOG_MOD_EXP2:
		return "exp2";
#endif
	default:
		assert(0);
		return "线性";
	}
}

vgVisualEffects::FogManager::FogMode vgFogEntry::getFogModeFromDescription(
	const String& des )
{
	using namespace vgVisualEffects;

#if VGK_LANG_CHS
	if ( des == "线性")
	{
		return FogManager::FOG_MOD_LINEAR;
	}
	else if ( des == "指数" )
	{
		return FogManager::FOG_MOD_EXP;
	}
	else if ( des == "指数平方" )
	{
		return FogManager::FOG_MOD_EXP2;
	}
#else
	if ( des == "Linear")
	{
		return FogManager::FOG_MOD_LINEAR;
	}
	else if ( des == "exp" )
	{
		return FogManager::FOG_MOD_EXP;
	}
	else if ( des == "exp2" )
	{
		return FogManager::FOG_MOD_EXP2;
	}
#endif

	assert(0);
	return FogManager::FOG_MOD_LINEAR;
}