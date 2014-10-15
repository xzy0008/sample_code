


#include <vgStableHeaders.h>
#include <vgKernel/vgkConvertUtility.h>
#include "vgTerrainEntry.h"
#include <vgUIController.h>


std::vector<PropertiesParam> vgTerrainEntry::_params;

vgTerrainEntry::vgTerrainEntry() :
vgBaseEntry( VG_ENTRY_TERRAIN , NULL )
{
	_terrMgr = vgTerritory::TerrainManager::getSingletonPtr();

	//assert( _terrMgr->hasTerrainData() == true );



	_terrMgr->registerObs( this );
}
vgTerrainEntry::~vgTerrainEntry(void)
{

}

void vgTerrainEntry::OnPropertyChanged(string paramName)
{

	//vgCam::CamManager::getSingleton().setCurrentPosition(
	//	vgKernel::Vec3(m_eyePosX, m_eyePosY, m_eyePosZ));


	//// 更新TREEITEM
	//vgUIController::GetInstance()->GetWorkSpaceBar()->SetItemText(hTreeItem, m_sCaption);
}

void vgTerrainEntry::onChanged(int eventId, void *param)
{

}

void vgTerrainEntry::AddNodeTabs()
{

	updateData();

	_params.clear();

	vgUIController::GetInstance()->RemoveAllPages();

	vgPropertiesViewBar* pageViewBar = 
		vgUIController::GetInstance()->GetPropertiesViewBar();


	if ( _terrMgr->hasTerrainData() == false )
	{
		vgPropertyPage* propPage = vgUIController::GetInstance()->GetPropPage();
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

	vgPropertyPage* propPage = vgUIController::GetInstance()->GetPropPage();
	propPage->Create(NIDD_PROPERTY, pageViewBar->GetTabControl());

	propPage->ConnectNode(this, &_params[0],  _params.size() );
	pageViewBar->AddTab("Properties", propPage);
}

void vgTerrainEntry::updateData()
{



	if ( vgTerritory::TerrainManager::getSingleton().hasTerrainData() )
	{
		vgTerritory::FileHandleVtr* vtrhandle =
			vgTerritory::ElevationManager::getSingleton().getMainFileHandleVtr();


		assert( vtrhandle != NULL );

		vgTerritory::VtrHeaderPtr pheader = vtrhandle->getHeader();

		m_sCaption = pheader->name;

		_vginame = pheader->imageFilename;


		n = vgKernel::ConvertUtility::textCast<String>( pheader->N );

		xTotalNum = vgKernel::ConvertUtility::textCast<String>(pheader->xTotalNum);			
		zTotalNum = vgKernel::ConvertUtility::textCast<String>(pheader->zTotalNum);


		cellTexSize = vgKernel::ConvertUtility::textCast<String>(pheader->cellTexSize);

		char buf[128];
		{
			sprintf( buf , "%f" , pheader->originX );
			
			_originX = buf;
		}
		{
			sprintf( buf , "%f" , pheader->originY );
			//std::ostringstream o;
			//o << std::fixed << pheader->originY;
			_originY = buf;
		}
		{
			sprintf( buf , "%f" , pheader->originZ );
			//std::ostringstream o;
			//o << std::fixed << pheader->originZ;
			_originZ = buf;
		}
	}
	else
	{
		//n = 0;

		//xTotalNum = 0;		
		//zTotalNum = 0;	


		//cellTexSize = 0;	

		//_originX = NULL;
		//_originY = NULL;
		//_originZ = NULL;

	}

}