#include <vgStableHeaders.h>
#include "vgUIController.h"
#include "vgObjectPropPage.h"
#include "vgTestNode1TabOne.h"
#include "vgObjectPropPage.h"
#include "vgTestNode1PropertiesTab.h"
#include "vgRootTabPage.h"

#include <vgMesh/vgmMeshManager.h>
#include <vgKernel/vgkInputCodeDef.h>


#include "vgFogEntry.h"
#include "vgRootEntry.h"
#include "vgCamMgrEntry.h"
#include "vgSoundBackgroundEntry.h"

#include <vgOcc/vgoOcclusion.h>
#include "vgFrustrumEntry.h"
#include "vgTerrainEntry.h"
#include "vgBackgroundEntry.h"

#include <vgQuadtreeSceneManager.h>
#include <vgSound/vgSoundManager.h>


vgUIController* vgUIController::s_pInstance = NULL;

vgUIController* vgUIController::GetInstance()
{
	if (s_pInstance == NULL)
		s_pInstance = new vgUIController;

	return s_pInstance;
}

void vgUIController::DestoryInstance()
{
	delete s_pInstance;

	s_pInstance = NULL;
}

vgUIController::vgUIController(void)
{	
	m_pTabView = new vgPropertiesViewBar();

	m_pWorkSpaceBar = new vgWorkSpaceBar();

	m_pOutputBar = new vgOutputBar();

	m_wndStatusBar = new CBCGPStatusBar;

	//	m_listTabPage.removeAll(); 

	// 在此构造所有需要使用的Tab页
	// 用户定义新的Tab页后需要在此添加初始化
	m_listTabPage[TAB_ROOT_TAB] = new vgRootTabPage();
	//m_listTabPage[TAB_TESTNODE_PROP] = new PropertiesTab();
	//m_listTabPage[TAB_TESTNODE_CTRL] = new TabOne();
	//m_listTabPage[TAB_OBJECT_PROP] = new vgObjectPropPage();
	//m_listTabPage[TAB_PROPERTIES_PAGE] = new vgPropertyPage();

	m_propPage = new vgPropertyPage();
	
	this->SetHandleStatus(VG_INPUTMODE_UI);
	vgKernel::InputSystem::getSingleton().registerHandle(this);
}

vgUIController::~vgUIController(void)
{
	//m_pTabView->RemoveAllTab();
	
	delete m_propPage;

	for (int i=0; i<TAB_ARRAY_SIZ; i++)
	{
		delete m_listTabPage[i];
	}

	// double delete test
	if (m_pTabView != NULL)
	{
		delete(m_pTabView);
		m_pTabView = NULL;
	}

	if (m_pWorkSpaceBar != NULL)
	{
		delete m_pWorkSpaceBar;
		m_pWorkSpaceBar = NULL;
	}

	if (m_wndStatusBar != NULL)
	{
		delete m_wndStatusBar;
		m_wndStatusBar = NULL;
	}

	vgKernel::InputSystem::getSingleton().removeHandle(this);
}

vgBasedTabPage* vgUIController::GetTabPage(long ID)
{
	return m_listTabPage[ID];
}

vgPropertyPage* vgUIController::GetPropPage()
{
	return m_propPage;
}

vgPropertiesViewBar* vgUIController::GetPropertiesViewBar()
{
	return m_pTabView;
}

vgWorkSpaceBar* vgUIController::GetWorkSpaceBar()
{
	return m_pWorkSpaceBar;
}

void vgUIController::AddTabPage(string pageName, CWnd* page)
{
	m_pTabView->AddTab(pageName, page);

	return ;
}

void vgUIController::RemoveAllPages()
{
	m_pTabView->RemoveAllTab();
}

void vgUIController::OnChar(int keyCode)
{
	//if (keyCode == vgKernel::InputCode::DEL)
	//{
	//	//TRACE("Delete pressed \n");
	//	m_pWorkSpaceBar->DeleteSelectedNode();
	//}
	switch(keyCode)
	{
	case vgKernel::InputCode::DEL:
		m_pWorkSpaceBar->DeleteSelectedNode(); 
		break;

	case vgKernel::InputCode::TAB:
		vgCore::QuadtreeSceneManager::getSingleton().vgCurrentMode = 1;
		break;
	default:
		break; 
	}
}


// 初始化过滤器
bool vgUIController::InitUIControl()
{
	// 第0层
#if VGK_LANG_CHS
	vgBaseEntry*	node = new vgRootEntry("场景");
#else
	vgBaseEntry*	node = new vgRootEntry("Scene");
#endif
	m_hRootNode = vgUIController::GetInstance()->AddNode(node);

	node = new vgCoordinateEntry();//2008.9.11
	vgUIController::GetInstance()->AddNode( m_hRootNode, node );

	//zhu
	node = new vgFrustrumEntry();//2008.9.27
	vgUIController::GetInstance()->AddNode( m_hRootNode, node );

	// 第一层
#if VGK_LANG_CHS
	node = new vgRootEntry("模型");
	m_hRootModel = vgUIController::GetInstance()->AddNode(node);

	node = new vgRootEntry("相机");
	m_hRootCamera = vgUIController::GetInstance()->AddNode(m_hRootNode, node);

	node = new vgRootEntry("特效");
	m_hRootSpecial = vgUIController::GetInstance()->AddNode(node);

	node = new vgRootEntry("动画");
	m_hRootMoving = vgUIController::GetInstance()->AddNode(node);

	node = new vgRootEntry("音效");
	m_hRootSound = vgUIController::GetInstance()->AddNode(m_hRootNode, node);

	node = new vgRootEntry("专题分析");
	m_hRootTopic = vgUIController::GetInstance()->AddNode(m_hRootNode, node);
#else
	node = new vgRootEntry("Model");
	m_hRootModel = vgUIController::GetInstance()->AddNode(node);

	node = new vgRootEntry("Camera");
	m_hRootCamera = vgUIController::GetInstance()->AddNode(m_hRootNode, node);

	node = new vgRootEntry("Effects");
	m_hRootSpecial = vgUIController::GetInstance()->AddNode(node);

	node = new vgRootEntry("Animation");
	m_hRootMoving = vgUIController::GetInstance()->AddNode(node);

	node = new vgRootEntry("Sound");
	m_hRootSound = vgUIController::GetInstance()->AddNode(m_hRootNode, node);

	node = new vgRootEntry("Subject");
	m_hRootTopic = vgUIController::GetInstance()->AddNode(m_hRootNode, node);

#endif

	// 第二层
	/// 相机
	node = new vgCamMgrEntry();
	HTREEITEM hCam = vgUIController::GetInstance()->AddNode(m_hRootCamera, node);
	if (hCam != NULL)
	{
		GetWorkSpaceBar()->Expand(hCam );
		GetWorkSpaceBar()->EnsureVisible(hCam);
	}	
	
#if VGK_LANG_CHS
	node = new vgRootEntry("定点相机");
	m_hSubStaticCamera = vgUIController::GetInstance()->AddNode(m_hRootCamera, node);
#else
	node = new vgRootEntry("Static Camera");
	m_hSubStaticCamera = vgUIController::GetInstance()->AddNode(m_hRootCamera, node);

#endif

	/// 音效
	node = new vgSoundBackgroundEntry(&vgCore::SoundManager::getSingleton().getCurrentBackgroundMusic() );
	HTREEITEM hSnd = vgUIController::GetInstance()->AddNode(m_hRootSound, node);
	if (hSnd != NULL)
	{
		GetWorkSpaceBar()->Expand(hSnd );
		GetWorkSpaceBar()->EnsureVisible(hSnd);
	}	

#if VGK_LANG_CHS
	node = new vgRootEntry("立体声源");
	m_hSub3DSound = vgUIController::GetInstance()->AddNode(m_hRootSound, node);
#else
	node = new vgRootEntry("Stereo Sound");
	m_hSub3DSound = vgUIController::GetInstance()->AddNode(m_hRootSound, node);

#endif

	node = new vgTerrainEntry();
	m_hTerainNode = vgUIController::GetInstance()->AddNode(node);

	node = new vgBackgroundEntry();
	m_hTerainNode = vgUIController::GetInstance()->AddNode(node);

	node = new vgFogEntry();
	m_hTerainNode = vgUIController::GetInstance()->AddNode(node);

	/// 特效
#if VGK_LANG_CHS
	node = new vgRootEntry("植被");
	m_hSubBillboard = vgUIController::GetInstance()->AddNode(m_hRootSpecial, node);

	node = new vgRootEntry("喷泉");
	m_hSubFountain = vgUIController::GetInstance()->AddNode(m_hRootSpecial, node);

	node = new vgRootEntry("火");
	m_hSubFire = vgUIController::GetInstance()->AddNode(m_hRootSpecial, node);

	node = new vgRootEntry("烟");
	m_hSubSmoke = vgUIController::GetInstance()->AddNode(m_hRootSpecial, node);

	node = new vgRootEntry("旗帜");
	m_hSubFlag = vgUIController::GetInstance()->AddNode(m_hRootSpecial, node);

	node = new vgRootEntry("水");
	m_hSubWater = vgUIController::GetInstance()->AddNode(m_hRootSpecial, node);

	node = new vgRootEntry("玻璃");
	m_hSubGlass = vgUIController::GetInstance()->AddNode(m_hRootSpecial, node);

	node = new vgRootEntry("镜面");
	m_hSubMirror = vgUIController::GetInstance()->AddNode(m_hRootSpecial, node);

	node = new vgRootEntry("金属");
	m_hSubMetal = vgUIController::GetInstance()->AddNode(m_hRootSpecial, node);

	node = new vgRootEntry("光亮地面");
	m_hSubFloor = vgUIController::GetInstance()->AddNode(m_hRootSpecial, node);

	node = new vgRootEntry("AVI视频");
	m_hSubVideotexture = vgUIController::GetInstance()->AddNode(m_hRootSpecial, node);
	
	node = new vgRootEntry("天空盒");
	m_hSubMoveskybox = vgUIController::GetInstance()->AddNode(m_hRootSpecial, node);

	node = new vgRootEntry("自动建模");
	m_hSubAutobuild = vgUIController::GetInstance()->AddNode(m_hRootSpecial, node);
	
	node = new vgRootEntry("触发器");
	m_hSubTrigger = vgUIController::GetInstance()->AddNode(m_hRootSpecial, node);

	node = new vgRootEntry("动态纹理");
	m_hSubDynamictex = vgUIController::GetInstance()->AddNode(m_hRootSpecial, node);

	/// 动画
	node = new vgRootEntry("关键帧");
	m_hSubKeyframe = vgUIController::GetInstance()->AddNode(m_hRootMoving, node);

	node = new vgRootEntry("骨骼");
	m_hSubSkeleton = vgUIController::GetInstance()->AddNode(m_hRootMoving, node);

	node = new vgRootEntry("漫游");
	m_hSubAnimation = vgUIController::GetInstance()->AddNode(m_hRootMoving, node);

	node = new vgRootEntry("VGM模型");
	m_hSubVGM = vgUIController::GetInstance()->AddNode(m_hRootModel, node);

	node = new vgRootEntry("MOD模型");
	m_hSubMOD = vgUIController::GetInstance()->AddNode(m_hRootModel, node);
	
	
	/// 专题
// 	node = new vgRootEntry("规划分析");
// 	m_hCityplan = vgUIController::GetInstance()->AddNode( m_hRootTopic, node );

	node = new vgRootEntry("道路匹配");
	m_hSubROAD = vgUIController::GetInstance()->AddNode(m_hRootTopic, node);//----- [9/23/2008 YX]

	node = new vgRootEntry("矢量集合");
	m_hSubVecString = vgUIController::GetInstance()->AddNode(m_hRootNode, node);
#else
	node = new vgRootEntry("Grass");
	m_hSubBillboard = vgUIController::GetInstance()->AddNode(m_hRootSpecial, node);

	node = new vgRootEntry("Fountain");
	m_hSubFountain = vgUIController::GetInstance()->AddNode(m_hRootSpecial, node);

	node = new vgRootEntry("Fire");
	m_hSubFire = vgUIController::GetInstance()->AddNode(m_hRootSpecial, node);

	node = new vgRootEntry("Fireworks");
	m_hSubSmoke = vgUIController::GetInstance()->AddNode(m_hRootSpecial, node);

	node = new vgRootEntry("Flag");
	m_hSubFlag = vgUIController::GetInstance()->AddNode(m_hRootSpecial, node);

	node = new vgRootEntry("Water");
	m_hSubWater = vgUIController::GetInstance()->AddNode(m_hRootSpecial, node);

	node = new vgRootEntry("Glass");
	m_hSubGlass = vgUIController::GetInstance()->AddNode(m_hRootSpecial, node);

	node = new vgRootEntry("Mirror");
	m_hSubMirror = vgUIController::GetInstance()->AddNode(m_hRootSpecial, node);

	node = new vgRootEntry("Metal");
	m_hSubMetal = vgUIController::GetInstance()->AddNode(m_hRootSpecial, node);

	node = new vgRootEntry("Bright floor");
	m_hSubFloor = vgUIController::GetInstance()->AddNode(m_hRootSpecial, node);

	node = new vgRootEntry("AVI");
	m_hSubVideotexture = vgUIController::GetInstance()->AddNode(m_hRootSpecial, node);

	node = new vgRootEntry("Skybox");
	m_hSubMoveskybox = vgUIController::GetInstance()->AddNode(m_hRootSpecial, node);

	node = new vgRootEntry("Automate model");
	m_hSubAutobuild = vgUIController::GetInstance()->AddNode(m_hRootSpecial, node);
	
	node = new vgRootEntry("Trigger");
	m_hSubTrigger = vgUIController::GetInstance()->AddNode(m_hRootSpecial, node);
	
	
	/// 动画
	node = new vgRootEntry("Keyframe");
	m_hSubKeyframe = vgUIController::GetInstance()->AddNode(m_hRootMoving, node);

	node = new vgRootEntry("Skeleton");
	m_hSubSkeleton = vgUIController::GetInstance()->AddNode(m_hRootMoving, node);

	node = new vgRootEntry("Roam");
	m_hSubAnimation = vgUIController::GetInstance()->AddNode(m_hRootMoving, node);

	node = new vgRootEntry("VGM");
	m_hSubVGM = vgUIController::GetInstance()->AddNode(m_hRootModel, node);

	node = new vgRootEntry("MOD");
	m_hSubMOD = vgUIController::GetInstance()->AddNode(m_hRootModel, node);


	/// 专题
	node = new vgRootEntry("Subject");
	m_hCityplan = vgUIController::GetInstance()->AddNode( m_hRootTopic, node );

	node = new vgRootEntry("Road");
	m_hSubROAD = vgUIController::GetInstance()->AddNode(m_hRootTopic, node);//----- [9/23/2008 YX]

	node = new vgRootEntry("Vector");
	m_hSubVecString = vgUIController::GetInstance()->AddNode(m_hRootNode, node);

#endif


#if VGK_LANG_CHS
	// 矢量图形节点第0层------------------------------------------------------------
	node = new vgRootEntry("矢量图形");
	m_hRootVector = vgUIController::GetInstance()->AddNode(m_hRootNode, node);//AddNode(node, 2);

	/// 矢量图形节点第1层
	node = new vgRootEntry("ShapeFile");
	m_hSubShape = vgUIController::GetInstance()->AddNode(m_hRootVector, node);

	node = new vgRootEntry("点型");
	m_hSubShapePoint = vgUIController::GetInstance()->AddNode(m_hSubShape, node);

	node = new vgRootEntry("线型");
	m_hSubShapeLine = vgUIController::GetInstance()->AddNode(m_hSubShape, node);

	node = new vgRootEntry("块型");
	m_hSubShapePolygon = vgUIController::GetInstance()->AddNode(m_hSubShape, node);

	node = new vgRootEntry("其它");
	m_hSubShapeUnknow = vgUIController::GetInstance()->AddNode(m_hSubShape, node);
#else
	// 矢量图形节点第0层------------------------------------------------------------
	node = new vgRootEntry("Vector");
	m_hRootVector = vgUIController::GetInstance()->AddNode(m_hRootNode, node);//AddNode(node, 2);

	/// 矢量图形节点第1层
	node = new vgRootEntry("ShapeFile");
	m_hSubShape = vgUIController::GetInstance()->AddNode(m_hRootVector, node);

	node = new vgRootEntry("Point");
	m_hSubShapePoint = vgUIController::GetInstance()->AddNode(m_hSubShape, node);

	node = new vgRootEntry("Line");
	m_hSubShapeLine = vgUIController::GetInstance()->AddNode(m_hSubShape, node);

	node = new vgRootEntry("Block");
	m_hSubShapePolygon = vgUIController::GetInstance()->AddNode(m_hSubShape, node);

	node = new vgRootEntry("Other");
	m_hSubShapeUnknow = vgUIController::GetInstance()->AddNode(m_hSubShape, node);

#endif

	// 四叉树视图第0层
	//node = new vgRootEntry("四叉树视图");
	//m_hRootQuadtree = vgUIController::GetInstance()->AddNode(node, 2);
	return true;
}

//new Status Bar ===============================================================

void vgUIController::EnableProgressBar()
{
	m_wndStatusBar->EnablePaneProgressBar(nStatusProgress, 100);
}

void vgUIController::DisableProgressBar()
{
	m_wndStatusBar->EnablePaneProgressBar(nStatusProgress, -1);
}

void vgUIController::SetProgress(UINT cnt)
{
	m_wndStatusBar->SetPaneProgress(nStatusProgress, cnt);
}

void vgUIController::SetFrameSpeed(UINT speed)
{
	char strSpeed[24];

	sprintf_s(strSpeed, 24, "%d", speed);

	m_wndStatusBar->SetPaneText(vgUIController::nStatusFrame, strSpeed);

	if (speed > 30)
	{
		m_wndStatusBar->SetPaneTextColor(nStatusFrame, GREEN);
	}
	else if (speed > 20)
	{
		m_wndStatusBar->SetPaneTextColor(nStatusFrame, LIGHTBLUE);
	}
	else
	{
		m_wndStatusBar->SetPaneTextColor(nStatusFrame, RED);
	}
}

void vgUIController::SetNewOccCnt(UINT tcnt,UINT rcnt,UINT cnt)
{

	//return ;
	char strCnt[24];

	if (vgOcclusion::vgOcclusionManager::getSingleton().GetOccState())
		//sprintf_s(strCnt, 24, "%u-%u=%u",tcnt,cnt,rcnt );
		sprintf_s(strCnt, 24, "Occ ON");
	else
		sprintf_s(strCnt, 24, "Occ OFF");

	m_wndStatusBar->SetPaneText(vgUIController::nStatusOcc, strCnt);

	if (cnt > 30)
	{
		m_wndStatusBar->SetPaneTextColor(nStatusOcc, GREEN);
	}
	else if (cnt > 20)
	{
		m_wndStatusBar->SetPaneTextColor(nStatusOcc, LIGHTBLUE);
	}
	else
	{
		m_wndStatusBar->SetPaneTextColor(nStatusOcc, RED);
	}
}

HTREEITEM& vgUIController::GetRootGpu( vgCore::IMAGETYPE EFFECT_IMAGE_TYPE )
{
	switch( EFFECT_IMAGE_TYPE )
	{
	case vgCore::IMG_WATER:
		return m_hSubWater;
		break;
	case vgCore::IMG_GLASS:
		return m_hSubGlass;
		break;
	case vgCore::IMG_METAL:
		return m_hSubMetal;
		break;
	case vgCore::IMG_MIRROR:
		return m_hSubMirror;
		break;
	case vgCore::IMG_BRIGHTFLOOR:
		return m_hSubFloor;
		break;
	case vgCore::IMG_SKYBOX:
		return m_hSubMoveskybox;
		break;
	case vgCore::IMG_AVINODE:
		return m_hSubVideotexture;
		break;
	case vgCore::IMG_AUTOBUILD:
		return m_hSubAutobuild;
		break;
	case vgCore::IMG_TRIGGER:
		return m_hSubTrigger;
		break;
	case vgCore::IMG_DYNAMICTEX:
		return m_hSubDynamictex;
		break;

	default:
		return m_hSubWater;
		break;
	}
}
//----------------------------------------------------------------
bool vgUIController::addEntryToRootByName( const String& root_name , 
										  vgBaseEntry* entry , const bool& add_if_need /*= true */ )
{
	TreeItemMap::iterator findres = _rootItems.find( root_name );

	if ( findres == _rootItems.end() )
	{
		if ( add_if_need )
		{
			vgBaseEntry* base = new vgRootEntry( root_name );
			HTREEITEM hitem = AddNode( base );

			TreeItemMapInsertRes ins = 
				_rootItems.insert( std::make_pair( root_name , HTreeItemWrap( hitem ) ));

			assert( ins.second == true );

			findres = ins.first;
		}
		else
		{
			return false;
		}
	}

	HTREEITEM itm = findres->second._hTreeItem;

	AddNode( itm , entry );

	if ( itm != NULL )
	{
		GetWorkSpaceBar()->Expand( itm  );
		GetWorkSpaceBar()->EnsureVisible( itm );
	}
	
	return true;
}