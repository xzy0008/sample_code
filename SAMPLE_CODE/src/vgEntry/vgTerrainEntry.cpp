


#include <vgStableHeaders.h>
#include <vgKernel/vgkConvertUtility.h>
#include "vgEntry/vgTerrainEntry.h"
#include <vgUIController/vgUIController.h>

//#include <vgPlugin/vgplTerritoryUtility.h>

#include <vgKernel/vgkPluginManager.h>

//#include <vgTerritory/vgtTerrainManager.h>


std::vector<PropertiesParam> vgTerrainEntry::_params;

vgTerrainEntry::vgTerrainEntry() :
vgBaseEntry( NULL )
{
	_terrainPlug = NULL;
	_pheader = NULL;
}

vgTerrainEntry::~vgTerrainEntry(void)
{

}

void vgTerrainEntry::OnPropertyChanged(string paramName)
{

	//vgCam::CamManager::getSingleton().setCurrentPosition(
	//	vgKernel::Vec3(m_eyePosX, m_eyePosY, m_eyePosZ));


	//// 更新TREEITEM
	//vgUI::UIController::getSingleton().GetWorkSpaceBar()->SetItemText(hTreeItem, m_sCaption);
}

void vgTerrainEntry::onChanged(int eventId, void *param)
{

}

void vgTerrainEntry::AddNodeTabs()
{
	updateData();

	_params.clear();

	vgUI::UIController::getSingleton().RemoveAllPages();

	vgPropertiesViewBar* pageViewBar = 
		vgUI::UIController::getSingleton().GetPropertiesViewBar();



	if ( _terrainPlug == NULL ||
		_pheader == NULL )
	{
		vgPropertyPage* propPage = vgUI::UIController::getSingleton().GetPropPage();
		propPage->Create(NIDD_PROPERTY, pageViewBar->GetTabControl());

		propPage->ConnectNode(this, NULL,  _params.size() );
		pageViewBar->AddTab("Prop", propPage);

		return;
	}


	PropertiesParam param;

#if VGK_LANG_CHS
	param.label = "基本属性";
	param.typeId = PROP_ITEM_GROUP;
	param.dataType = PROP_DATA_NONE;
	param.connectedPtr = NULL;
	param.comment = String();
	_params.push_back( param );


	param.label = "物体名称";
	param.typeId = PROP_ITEM_DATA;
	param.dataType = PROP_DATA_CONST_STR;
	param.connectedPtr = &m_sCaption;
	param.comment = "物体的名称";
	_params.push_back( param );


	param.label = "影像文件";
	param.typeId = PROP_ITEM_DATA;
	param.dataType = PROP_DATA_CONST_STR;
	param.connectedPtr = &_vginame;
	param.comment = "对应的影像文件";
	_params.push_back( param );


	param.label = "逻辑原点";
	param.typeId = PROP_ITEM_GROUP;
	param.dataType = PROP_DATA_NONE;
	param.connectedPtr = NULL;
	param.comment = String();
	_params.push_back( param );

	param.label = "X坐标";
	param.typeId = PROP_ITEM_DATA;
	param.dataType = PROP_DATA_CONST_STR;
	param.connectedPtr = &_originX;
	param.comment = "地形逻辑原点X坐标";
	_params.push_back( param );

	param.label = "Y坐标";
	param.typeId = PROP_ITEM_DATA;
	param.dataType = PROP_DATA_CONST_STR;
	param.connectedPtr = &_originY;
	param.comment = "逻辑原点Y坐标";
	_params.push_back( param );

	param.label = "Z坐标";
	param.typeId = PROP_ITEM_DATA;
	param.dataType = PROP_DATA_CONST_STR;
	param.connectedPtr = &_originZ;
	param.comment = "地形逻辑原点Z坐标";
	_params.push_back( param );

	//------------------------------------------
	// 其他只读属性
	//------------------------------------------
	param.label = "其他只读属性";
	param.typeId = PROP_ITEM_GROUP;
	param.dataType = PROP_DATA_NONE;
	param.connectedPtr = NULL;
	param.comment = String();
	_params.push_back( param );

	param.label = "N值";
	param.typeId = PROP_ITEM_DATA;
	param.dataType = PROP_DATA_CONST_STR;
	param.connectedPtr = &n;
	param.comment = "N值";
	_params.push_back( param );

	param.label = "网格数目-x轴方向";
	param.typeId = PROP_ITEM_DATA;
	param.dataType = PROP_DATA_CONST_STR;
	param.connectedPtr = &xTotalNum;
	param.comment =  "网格数目-x轴方向";
	_params.push_back( param );

	param.label = "网格数目-z轴方向";
	param.typeId = PROP_ITEM_DATA;
	param.dataType = PROP_DATA_CONST_STR;
	param.connectedPtr = &zTotalNum;
	param.comment =  "网格数目-z轴方向";
	_params.push_back( param );

	param.label = "每网格间距对应纹理大小";
	param.typeId = PROP_ITEM_DATA;
	param.dataType = PROP_DATA_CONST_STR;
	param.connectedPtr = &cellTexSize;
	param.comment =  "每网格间距对应纹理大小";
	_params.push_back( param );

#else
	param.label = "Basic Prop";
	param.typeId = PROP_ITEM_GROUP;
	param.dataType = PROP_DATA_NONE;
	param.connectedPtr = NULL;
	param.comment = String();
	_params.push_back( param );


	param.label = "Name";
	param.typeId = PROP_ITEM_DATA;
	param.dataType = PROP_DATA_CONST_STR;
	param.connectedPtr = &m_sCaption;
	param.comment = "";
	_params.push_back( param );


	param.label = "Image";
	param.typeId = PROP_ITEM_DATA;
	param.dataType = PROP_DATA_CONST_STR;
	param.connectedPtr = &_vginame;
	param.comment = "";
	_params.push_back( param );


	param.label = "Origin";
	param.typeId = PROP_ITEM_GROUP;
	param.dataType = PROP_DATA_NONE;
	param.connectedPtr = NULL;
	param.comment = String();
	_params.push_back( param );

	param.label = "X";
	param.typeId = PROP_ITEM_DATA;
	param.dataType = PROP_DATA_CONST_STR;
	param.connectedPtr = &_originX;
	param.comment = "";
	_params.push_back( param );

	param.label = "Y";
	param.typeId = PROP_ITEM_DATA;
	param.dataType = PROP_DATA_CONST_STR;
	param.connectedPtr = &_originY;
	param.comment = "";
	_params.push_back( param );

	param.label = "Z";
	param.typeId = PROP_ITEM_DATA;
	param.dataType = PROP_DATA_CONST_STR;
	param.connectedPtr = &_originZ;
	param.comment = "";
	_params.push_back( param );

	//------------------------------------------
	// 其他只读属性
	//------------------------------------------
	param.label = "Others";
	param.typeId = PROP_ITEM_GROUP;
	param.dataType = PROP_DATA_NONE;
	param.connectedPtr = NULL;
	param.comment = String();
	_params.push_back( param );

	param.label = "N";
	param.typeId = PROP_ITEM_DATA;
	param.dataType = PROP_DATA_CONST_STR;
	param.connectedPtr = &n;
	param.comment = "N";
	_params.push_back( param );

	param.label = "Points-X";
	param.typeId = PROP_ITEM_DATA;
	param.dataType = PROP_DATA_CONST_STR;
	param.connectedPtr = &xTotalNum;
	param.comment =  "";
	_params.push_back( param );

	param.label = "Points-Z";
	param.typeId = PROP_ITEM_DATA;
	param.dataType = PROP_DATA_CONST_STR;
	param.connectedPtr = &zTotalNum;
	param.comment =  "";
	_params.push_back( param );

	param.label = "texture size per mesh";
	param.typeId = PROP_ITEM_DATA;
	param.dataType = PROP_DATA_CONST_STR;
	param.connectedPtr = &cellTexSize;
	param.comment =  "";
	_params.push_back( param );
#endif

	vgPropertyPage* propPage = vgUI::UIController::getSingleton().GetPropPage();
	propPage->Create(NIDD_PROPERTY, pageViewBar->GetTabControl());

	propPage->ConnectNode(this, &_params[0],  _params.size() );
	pageViewBar->AddTab("Properties", propPage);

}

void vgTerrainEntry::updateData()
{
	using namespace vgKernel;
	_terrainPlug = PluginManager::getSingleton().getPluginRef( VGT_DLL_NAME );

	if ( _terrainPlug == NULL )
	{
		return;
	}
	
	//add by ZhouZY 2009-11-4 9:36 
	//edit by lss 2009-11-9 20:30:06
	VGK_DLL_DECLARE_CLASSFUNC( _terrainPlug, TerrainManager, hasTerrainData, pfn1 );

	assert( pfn1 != NULL);

	if ( pfn1() == false ) 
	{
		return;
	}

	VGK_DLL_DECLARE_FUNC( _terrainPlug , 
		getMainFileHandleVtrHeader,  get_fun );

	assert( get_fun != NULL );

	_pheader = (*get_fun)();


	if ( _pheader != NULL )
	{
		m_sCaption = _pheader->name;

		_vginame = _pheader->imageFilename;


		n = vgKernel::ConvertUtility::textCast<String>( _pheader->N );

		xTotalNum = vgKernel::ConvertUtility::textCast<String>(_pheader->xTotalNum);			
		zTotalNum = vgKernel::ConvertUtility::textCast<String>(_pheader->zTotalNum);


		cellTexSize = vgKernel::ConvertUtility::textCast<String>(_pheader->cellTexSize);

		char buf[128];
		{
			sprintf( buf , "%f" , _pheader->originX );
			
			_originX = buf;
		}
		{
			sprintf( buf , "%f" , _pheader->originY );
			//std::ostringstream o;
			//o << std::fixed << pheader->originY;
			_originY = buf;
		}
		{
			sprintf( buf , "%f" , _pheader->originZ );
			//std::ostringstream o;
			//o << std::fixed << pheader->originZ;
			_originZ = buf;
		}
	}


}