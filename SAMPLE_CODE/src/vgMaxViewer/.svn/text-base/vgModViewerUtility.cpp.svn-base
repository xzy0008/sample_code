
#include "vgStableHeaders.h"
#include "vgModViewerUtility.h"
#include "vgMaxViewer.h"
#include "vgUtility/vgModCommonUtility.h"
#include "vgModViewer.h"


bool	vgModViewerUtility::_bPromptDisable	= false;
uint	vgModViewerUtility::_uiExportOption = 0 ;

//Class_ID	vgModViewerUtility::_class_ID = CLASS_ID_MOD_EXPORT_JPG_DEBUG;
#ifdef _DEBUG
Class_ID	vgModViewerUtility::_class_ID = CLASS_ID_MOD_MAXPLUGIN_JPG_DEBUG;
#else
Class_ID	vgModViewerUtility::_class_ID = CLASS_ID_MOD_MAXPLUGIN_JPG_RELEASE;
#endif

CollectionClassDesc* vgModViewerUtility::_classDesc = NULL;
Collection* vgModViewerUtility::_utiObj = NULL;
bool	vgModViewerUtility::_bSelectedOnly	= false;

//----------------------------------------------------------------------------
bool vgModViewerUtility::exportMODAndCollect()
{

	return true;
}

//----------------------------------------------------------------------------
bool vgModViewerUtility::exportMODAndSave()
{

	return true;
}

//----------------------------------------------------------------------------
bool vgModViewerUtility::exportMODAndView()
{
	// 将使用自定义的导出选项
	setFlagPromptDisable(true);

	// 自定义导出选项
	uint options = FILTER_SELECTED;// | PROMPT_SETTING | PROMPT_WARNING | PROMPT_RESULT;
	setExportOption( options );

	// 导出
	exportMODCommon();

	// 计算场景包围盒
	calculateBoxBySelf();

	// 浏览
	vgModViewer::openMODByVGViewer();

	return true;
}

//----------------------------------------------------------------------------
bool vgModViewerUtility::exportMODThenView()
{
	// 将使用自定义的导出选项
	setFlagPromptDisable(false);
	
	// 自定义导出选项
	uint options = FILTER_SELECTED;// | PROMPT_SETTING | PROMPT_WARNING | PROMPT_RESULT;
	setExportOption( options );

	// 导出
	exportMODCommon();

	return true;
}

bool vgModViewerUtility::getFlagPromptDisable()
{
	return _bPromptDisable;
}

uint vgModViewerUtility::getExportOption()
{
	return _uiExportOption;
}

void vgModViewerUtility::setFlagPromptDisable( bool bPrompt )
{
	_bPromptDisable = bPrompt;
}

void vgModViewerUtility::setExportOption( uint uiExportOption )
{
	_uiExportOption = uiExportOption;
}

void vgModViewerUtility::appendExportOption( uint uiExportOption )
{
	_uiExportOption += uiExportOption;
}

//----------------------------------------------------------------------------
bool vgModViewerUtility::exportMODCommon()
{
	configSelectedOnlyDefault();

	Interface *ip;
	ip = _utiObj->ip;

	TSTR maxFilePath = ip->GetCurFilePath();
	if( maxFilePath.isNull())
	{
		vgModUtility::MessageBox(IDS_MSG_EXPORT_EMPTY, IDS_MSG_EXPORT_EMPTY_TITLE);
	}
	
	std::string modFilePathSTD(maxFilePath.data());

	modFilePathSTD = modFilePathSTD.substr(0, modFilePathSTD.find_last_of(".")+1 );
	modFilePathSTD += "mod";

	WorkFile fileHandle(modFilePathSTD.c_str());
	bool bFileExist = fileHandle.checkFileExist();
	fileHandle.Close();
	if ( !bFileExist )
	{//mod 不存在的情况
		exportByMax(modFilePathSTD);
	}
	else
	{//mod 已存在的情况
		if (IDYES == ::MessageBox(NULL,
			"已经生成预览，是否重新生成？","", MB_YESNO) )
		{
			//::remove(modFilePathSTD.c_str());
			vgModViewer::resetViewer();

			exportByMax(modFilePathSTD);
		}
	}

	vgModViewer::setFileNameMod( modFilePathSTD );

	return true;
}

//----------------------------------------------------------------------------
// ClassDesc* vgModViewerUtility::getCollectionDesc()
// {
// 	return _classDesc;
// }

//----------------------------------------------------------------------------
// void vgModViewerUtility::setCollectionDesc( CollectionClassDesc* desc )
// {
// 	_classDesc = desc;
// 	_utiObj = dynamic_cast<Collection*>(_classDesc->GetCollectionUtility());
// }

//----------------------------------------------------------------------------
Collection* vgModViewerUtility::getCollectionUtility()
{
	return _utiObj;
}

void vgModViewerUtility::setCollectionUtility( Collection* uti )
{
	_utiObj = uti;
}

void vgModViewerUtility::calculateBoxBySelf()
{
	Interface*	&ip = _utiObj->ip;

	// 选中节点
	if ( !getFlagSelectedOnly() )
	{
		SelectAllNode( ip->GetRootNode(), ip->GetTime());
	}

	// 获得包围盒
	Box3 sceneBox;
	ip->GetSelectionWorldBox( ip->GetTime(), sceneBox);

	CBox3 sceneBoxMod;
	CVector3& maxPoint = sceneBoxMod.rightTop();
	CVector3& minPoint = sceneBoxMod.leftBottom();
	maxPoint = CVector3(sceneBox.Max().x,  sceneBox.Max().y, sceneBox.Max().z );
	minPoint = CVector3(sceneBox.Min().x,  sceneBox.Min().y, sceneBox.Min().z );

	vgModViewer::setSceneBox(sceneBoxMod);

	if ( !getFlagSelectedOnly() )
	{
		ip->SelectNode(NULL);
	}
}


// Traverse the node counting polygons.  
void	vgModViewerUtility::TraverseNode(INode* node, TimeValue t)
{
	const ObjectState& os = node->EvalWorldState(t);
	Object* obj = os.obj;
	if (obj && obj->CanConvertToType(triObjectClassID)) 
	{
		 _utiObj->ip->SelectNode(node, false);
	}

	int i, numChildren = node->NumberOfChildren();
	for(i=0; i<numChildren; i++)
		TraverseNode(node->GetChildNode(i), t);
}
void	vgModViewerUtility::SelectAllNode(INode* node, TimeValue time)
{
	TraverseNode( node, time);
}

//----------------------------------------------------------------------------
bool vgModViewerUtility::exportByMax( string filepath )
{
	Interface *ip;
	ip = _utiObj->ip;

	ip->ExportToFile( filepath.c_str(),
		getFlagPromptDisable(),
		getExportOption(),
		&_class_ID);

	return true;
}

//----------------------------------------------------------------------------
bool vgModViewerUtility::getFlagSelectedOnly()
{
	return _bSelectedOnly;
}

//----------------------------------------------------------------------------
void vgModViewerUtility::setFlagSelectedOnly( bool bSelected )
{
	_bSelectedOnly = bSelected;
}

//----------------------------------------------------------------------------
void vgModViewerUtility::configSelectedOnlyDefault()
{
	Interface*	&ip = _utiObj->ip;
	bool	bHasSelection = ip->GetSelNodeCount() != 0;

	setFlagSelectedOnly( bHasSelection );
}
//----------------------------------------------------------------------------
