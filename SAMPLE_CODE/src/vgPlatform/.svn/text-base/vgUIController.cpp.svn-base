#include <vgStableHeaders.h>
#include "vgUIController.h"
#include "vgObjectPropPage.h"
#include "vgTestNode1TabOne.h"
#include "vgObjectPropPage.h"
#include "vgTestNode1PropertiesTab.h"
#include "vgRootTabPage.h"

#include <vgKernel/vgkUniqueID.h>
#include <vgMesh/vgmMeshManager.h>

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

	//	m_listTabPage.removeAll(); 

	// 在此构造所有需要使用的Tab页
	// 用户定义新的Tab页后需要在此添加初始化
	m_listTabPage[TAB_ROOT_TAB] = new vgRootTabPage();
	m_listTabPage[TAB_TESTNODE_PROP] = new PropertiesTab();
	m_listTabPage[TAB_TESTNODE_CTRL] = new TabOne();
	m_listTabPage[TAB_OBJECT_PROP] = new vgObjectPropPage();
	//m_listTabPage[TAB_PROPERTIES_PAGE] = new vgPropertyPage();

	m_propPage = new vgPropertyPage();
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

bool vgUIController::InitUIControl(void)
{

	// vgTestNode1 node("World"); // 导致无效的引用
	// 不必担心内存泄露，UIController会负责释放内存

	vgBasedNode *node = new vgRootNode("VG-Scene");
	m_hRootNode = vgUIController::GetInstance()->AddNode(node);

	node = new vgRootNode("VGM-MODULE");
	m_hRootVGM = vgUIController::GetInstance()->AddNode(m_hRootNode, node);

	node = new vgCameraNode("Camera1");
	vgUIController::GetInstance()->AddNode(m_hRootVGM, node);

	node = new vgTestNode1("TestNodo1");
	vgUIController::GetInstance()->AddNode(m_hRootVGM, node);

	node = new vgTestNode1("TestNode2");
	vgUIController::GetInstance()->AddNode(m_hRootVGM, node);


	node = new vgRootNode("VG-MODULE");
	m_hRootVG = vgUIController::GetInstance()->AddNode(m_hRootNode, node);

	node = new vgRootNode("VG-CAMERA");
	m_hRootCamera = vgUIController::GetInstance()->AddNode(m_hRootNode, node);
	
	m_pWorkSpaceBar->SetRootNodeCount(m_pWorkSpaceBar->GetNodeList().size());

	//node = new vgKernel::CameraAdapter("VG-CameraCurrent");
	//vgKernel::Camera*	pCurrentCam = vgMesh::MeshManager::getSingleton().getCurrentCamera();
	//((vgKernel::CameraAdapter*)node)->SetCameraPtr(pCurrentCam);
	//vgUIController::GetInstance()->AddNode(m_hRootCamera, node);


	return true;
}

